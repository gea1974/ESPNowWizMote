#include <WizMote.h>

// Button Mappings:
// - Button 0: Off Button
// - Button 1: On Button
// - Button 2: Button 2 on the Wiz Remote
// - Button 3: Button 1 on the Wiz Remote
// - Button 4: Button 4 on the Wiz Remote
// - Button 5: Button 3 on the Wiz Remote
// - Button 6: Brightness Up
// - Button 7: Brightness Down
// - Button 8: Moon Button 

WizMoteClass::WizMoteClass() {}

const String buttonName[9] = { "Off", "On", "2", "1", "4", "3", "Up", "Down", "Sleep" };

// Unique integers for each button press type
uint8_t buttonPressCodes[9][8] = {
    BUTTON_CODES_OFF, 
    BUTTON_CODES_ON,  
    BUTTON_CODES_2,  
    BUTTON_CODES_1,  
    BUTTON_CODES_4,  
    BUTTON_CODES_3,  
    BUTTON_CODES_UP,  
    BUTTON_CODES_DOWN,  
    BUTTON_CODES_MOON
}; 
    /*
    {2,  0,  0,  0,  0,  0,  102, 0},    // Button 0: Off Button
    {1,  0,  0,  0,  0,  0,  101, 0},    // Button 1: On Button
    {17, 27, 37, 47, 57, 67, 117, 0},    // Button 2: Button 2 on the Wiz Remote
    {16, 26, 36, 46, 56, 66, 116, 0},    // Button 3: Button 1 on the Wiz Remote
    {19, 29, 39, 49, 59, 69, 119, 0},    // Button 4: Button 4 on the Wiz Remote
    {18, 28, 38, 48, 58, 68, 118, 0},    // Button 5: Button 3 on the Wiz Remote
    {9,  0,  0,  0,  0,  0,  109, 0},    // Button 6: Brightness Up
    {8,  0,  0,  0,  0,  0,  108, 0},    // Button 7: Brightness Down
    {3,  0,  0,  0,  0,  0,  103, 0}     // Button 8: Moon Button
    */


void WizMoteClass::begin() {
    // Prevent calling this method a second time
    if (initialized) {
        return;
    }

    initialized = true;
}

uint8_t WizMoteClass::readButtonPress(bool timeoutCheck) {
    static uint8_t pressCounts[9] = {0};
    static unsigned long lastPressTime[9] = {0};
    static unsigned long pressStartTime[9] = {0};
    static bool buttonPressed[9] = {false};
    static bool buttonLongPressed[9] = {false};
    static bool buttonRepeatedPressed[9] = {false};
    static int lastButtonIndex = -1; // Track the last button pressed

    unsigned long loopStartTime = millis();

    while (true) {  // Loop until a button press is classified

        incomingButtonPressed =  0;
        sleepButtonPressed = false;

        #ifdef WIZMOTE_HC165
        ButtonHC165();
        #endif
        #ifdef WIZMOTE_PCA6416A
        ButtonPCA6416A();
        #endif
        #ifdef BUTTON_IO
        ButtonIO();
        #endif
        #ifdef BUTTON_RESET
        if (!ButtonResetFired) {
            incomingButtonPressed = (1<<1);
            ButtonResetFired = true;
        }
        #endif

        if ( ((millis()-loopStartTime)>=BUTTON_TIMEOUT) && timeoutCheck && (lastButtonIndex<0) )
        {
            printLogMsgTime("Button: no Button pressed Timeout\n"); 
            return 0;
        }

        // Loop through button states and classify presses
        for (int i = 0; i < 9; i++) {  // Loop includes all buttons including the Moon button (index 8)
            bool isPressed = (i < 8) ? (incomingButtonPressed & (1 << i)) : sleepButtonPressed; // Handle the Moon button separately
            bool buttonMulti = buttonPressCodes[i][1] != 0;
            bool buttonLong = buttonPressCodes[i][6] != 0;
//            bool buttonRepeat = (buttonPressCodes[i][7] != 0) && !buttonLong && !buttonMulti; //Allow multi press and repeated press
            bool buttonRepeat = (buttonPressCodes[i][7] != 0) && !buttonLong;
            bool buttonSingle = (buttonPressCodes[i][0] != 0) && !buttonRepeat && !buttonLong && !buttonMulti;

            unsigned long currentTime = millis();

            // previous pressed button was released
            if (!isPressed && !buttonPressed[i] && (lastButtonIndex==i) && (pressCounts[i]==0)) {
                printLogMsgTime("Button: Button %s released\n", buttonName[i].c_str());
                lastButtonIndex = -1;
                return 0;
            // no button pressed
            } else if (!isPressed && !buttonPressed[i] && (lastButtonIndex<0) && (i==8)  && !timeoutCheck) {
//                printLogMsgTime("Button: no Button pressed\n", buttonName[i].c_str());
                return 0;
            // Button is pressed
            } else if (isPressed && !buttonPressed[i]) {
                // If a different button is pressed, reset the count
                if (lastButtonIndex != i && lastButtonIndex >= 0 && lastButtonIndex < 9) {
                    pressCounts[lastButtonIndex] = 0; // Reset count of the previous button
                }
                if (isPressed && i!=lastButtonIndex){
                    printLogMsgTime("Button: Button %s down\n", buttonName[i].c_str());
                }

                pressStartTime[i] = currentTime;
                lastPressTime[i] = currentTime;
                lastButtonIndex = i; // Update the last pressed button

                if (buttonSingle) {
                    printLogMsgTime("Button: Button %s single pressed (single)\n", buttonName[i].c_str());
                    ButtonTimeStamp = millis();
                    return buttonPressCodes[i][0];                      // Single press code
                }
                else if (!buttonMulti && !buttonLong && !buttonRepeat)
                {
                    printLogMsgTime("Button: Button %s undefiend\n", buttonName[i].c_str());
                    return 0;                 
                }
                else {
                    buttonPressed[i] = true;
                }
            // button long pressed
            } else if (isPressed && buttonPressed[i] && buttonLong) {
                unsigned long pressDuration = currentTime - pressStartTime[i];
                if (pressDuration >= LONG_PRESS_THRESHOLD) 
                {
                    printLogMsgTime("Button: Button %s long pressed\n", buttonName[i].c_str());
                    ButtonTimeStamp = millis();
                    buttonLongPressed[i] = true;
                    return buttonPressCodes[i][6];                
                }
            // button repeated pressed
            } else if (isPressed && buttonPressed[i] && buttonRepeat) {
                unsigned long pressDuration = currentTime - pressStartTime[i];
                if (pressDuration >= REPEAT_PRESS_TIME) 
                {
                    printLogMsgTime("Button: Button %s repeated pressed\n", buttonName[i].c_str());
                    buttonRepeatedPressed[i] = true;
                    repeatingButtonCode = buttonPressCodes[i][7];      
                    ButtonTimeStamp = millis();
                    return buttonPressCodes[i][7];                
                }
            // button long or repeated pressed released         
            } else if (!isPressed && buttonPressed[i] && (buttonLongPressed[i] || buttonRepeatedPressed[i])){ 
                buttonPressed[i] = false;
                buttonLongPressed[i] = false;
                buttonRepeatedPressed[i] = false;
                printLogMsgTime("Button: Button %s released after long press.\n", buttonName[i].c_str());
                return buttonPressCodes[i][0]; // Single press code
            // button single pressed           
            } else if (!isPressed && buttonPressed[i] && !buttonMulti){ 
                    buttonPressed[i] = false;
                    printLogMsgTime("Button: Button %s single pressed (long, repeat).\n", buttonName[i].c_str());
                    ButtonTimeStamp = millis();
                    return buttonPressCodes[i][0]; // Single press code
            // multi button count presses
            } else if (!isPressed && buttonPressed[i] && buttonMulti) {
                buttonPressed[i] = false;
                unsigned long pressDuration = currentTime - pressStartTime[i];
                if (pressDuration > DEBOUNCE_DELAY) {
                    pressCounts[i]++;
                    printLogMsgTime("Button: Multi-Button %s multi press count %d.\n", buttonName[i].c_str(),pressCounts[i]);
                }
                lastPressTime[i] = currentTime;
            }

            // Check for multi-press types after a press has been completed
            if (!buttonPressed[i] && (pressCounts[i] > 0) && buttonMulti){              //FIX-ME: handle multi pressed only if configured
                unsigned long timeSinceLastPress = currentTime - lastPressTime[i];

                if (pressCounts[i] == 1 && timeSinceLastPress > DOUBLE_PRESS_TIME) {
                    printLogMsgTime("Button: Multi-Button %s single pressed.\n", buttonName[i].c_str());
                    pressCounts[i] = 0;
                    ButtonTimeStamp = millis();
                    return buttonPressCodes[i][0]; // Single press code
                } else if (pressCounts[i] == 2 && timeSinceLastPress > TRIPLE_PRESS_TIME) {
                    printLogMsgTime("Button: Multi-Button %s double pressed.\n", buttonName[i].c_str());
                    pressCounts[i] = 0;
                    ButtonTimeStamp = millis();
                    return buttonPressCodes[i][1]; // Double press code
                } else if (pressCounts[i] == 3 && timeSinceLastPress > TRIPLE_PRESS_TIME) {
                    printLogMsgTime("Button: Multi-Button %s triple pressed.\n", buttonName[i].c_str());
                    pressCounts[i] = 0;
                    ButtonTimeStamp = millis();
                    return buttonPressCodes[i][2]; // Triple press code
                } else if (pressCounts[i] == 4 && timeSinceLastPress > TRIPLE_PRESS_TIME) {
                    printLogMsgTime("Button: Multi-Button %s quadruple pressed.\n", buttonName[i].c_str());
                    pressCounts[i] = 0;
                    ButtonTimeStamp = millis();
                    return buttonPressCodes[i][3]; // Quadruple press code
                } else if (pressCounts[i] == 5 && timeSinceLastPress > TRIPLE_PRESS_TIME) {
                    printLogMsgTime("Button: Multi-Button %s quintuple pressed.\n", buttonName[i].c_str());
                    pressCounts[i] = 0;
                    ButtonTimeStamp = millis();
                    return buttonPressCodes[i][4]; // Quintuple press code
                } else if (pressCounts[i] == 6 && timeSinceLastPress > TRIPLE_PRESS_TIME) {
                    printLogMsgTime("Button: Multi-Button %s sextuple pressed.\n", buttonName[i].c_str());
                    pressCounts[i] = 0;
                    ButtonTimeStamp = millis();
                    return buttonPressCodes[i][5]; // Sextuple press code
                } else if (pressCounts[i] > 6 && timeSinceLastPress > TRIPLE_PRESS_TIME) {
                    printLogMsgTime("Button: Multi-Button %s %dx pressed.\n", buttonName[i].c_str(),pressCounts[i]);
                    pressCounts[i] = 0;
                    ButtonTimeStamp = millis();
                    return buttonPressCodes[i][5]; // Sextuple press code
                }
            }
        }

        // Add a small delay to avoid overwhelming the CPU
        delay(10);
    }
}
#ifdef WIZMOTE_PCA6416A
void WizMoteClass::ButtonPCA6416A() {
    incomingButtonPressed =  0;
    sleepButtonPressed = false;
    #ifdef WIZMOTE_PCA6416A
        uint8_t value = 0;
    #endif
}
#endif
#ifdef WIZMOTE_HC165
void WizMoteClass::ButtonHC165() {
    incomingButtonPressed =  0;
    sleepButtonPressed = false;
    uint8_t value = 0;
    const uint8_t bitOrder=MSBFIRST;
    // Ensure pins are set correctly
    pinMode(LOAD_PIN, OUTPUT);
    pinMode(SCL_PIN, OUTPUT);
    pinMode(SDA_PIN, INPUT);
    pinMode(IO_BUTTON_MOON_PIN, INPUT);

    // load data into shift register
    digitalWrite(LOAD_PIN, LOW);
    delayMicroseconds(5);
    digitalWrite(LOAD_PIN, HIGH);
    delayMicroseconds(50);

    // Read data from shift register
    for (uint8_t i = 0; i < 8; ++i) {
        digitalWrite(SCL_PIN, LOW);
        if (bitOrder == LSBFIRST) {
            value |= (digitalRead(SDA_PIN) == LOW) << i;
        } else {
            value |= (digitalRead(SDA_PIN) == LOW) << (7 - i);
        }
        digitalWrite(SCL_PIN, HIGH);
    }
    incomingButtonPressed =  value;
    #ifdef IO_BUTTON_MOON_PIN
    sleepButtonPressed = digitalRead(IO_BUTTON_MOON_PIN) == IO_BUTTON_POLARITY;
    #endif
}
#endif

#ifdef BUTTON_IO
void WizMoteClass::ButtonIO() {
    incomingButtonPressed =  0;
    sleepButtonPressed = false;

    // Ensure pins are set correctly
    #ifdef IO_BUTTON_ON_PIN
        pinMode(IO_BUTTON_ON_PIN, IO_BUTTON_MODE);
        incomingButtonPressed += 2 * (digitalRead(IO_BUTTON_ON_PIN) == IO_BUTTON_POLARITY);
    #endif
    #ifdef IO_BUTTON_OFF_PIN
        pinMode(IO_BUTTON_OFF_PIN, IO_BUTTON_MODE);
        incomingButtonPressed += 1 * (digitalRead(IO_BUTTON_OFF_PIN) == IO_BUTTON_POLARITY);
    #endif
    #ifdef IO_BUTTON_1_PIN
        pinMode(IO_BUTTON_1_PIN, IO_BUTTON_MODE);
        incomingButtonPressed += 8 * (digitalRead(IO_BUTTON_1_PIN) == IO_BUTTON_POLARITY);
    #endif
    #ifdef IO_BUTTON_2_PIN
        pinMode(IO_BUTTON_2_PIN, IO_BUTTON_MODE);
        incomingButtonPressed += 4 * (digitalRead(IO_BUTTON_2_PIN) == IO_BUTTON_POLARITY);
    #endif
    #ifdef IO_BUTTON_3_PIN
        pinMode(IO_BUTTON_3_PIN, IO_BUTTON_MODE);
        incomingButtonPressed += 32 * (digitalRead(IO_BUTTON_3_PIN) == IO_BUTTON_POLARITY);
    #endif
    #ifdef IO_BUTTON_4_PIN
        pinMode(IO_BUTTON_4_PIN, IO_BUTTON_MODE);
        incomingButtonPressed += 16 * (digitalRead(IO_BUTTON_4_PIN) == IO_BUTTON_POLARITY);
    #endif
    #ifdef IO_BUTTON_UP_PIN
        pinMode(IO_BUTTON_UP_PIN, IO_BUTTON_MODE);
        incomingButtonPressed += 64 * (digitalRead(IO_BUTTON_UP_PIN) == IO_BUTTON_POLARITY);
    #endif
    #ifdef IO_BUTTON_DOWN_PIN
        pinMode(IO_BUTTON_DOWN_PIN, IO_BUTTON_MODE);
        incomingButtonPressed += 128 * (digitalRead(IO_BUTTON_DOWN_PIN) == IO_BUTTON_POLARITY);
    #endif
    #ifdef IO_BUTTON_MOON_PIN
        pinMode(IO_BUTTON_MOON_PIN, IO_BUTTON_MODE);
        sleepButtonPressed = digitalRead(IO_BUTTON_MOON_PIN) == IO_BUTTON_POLARITY;
    #endif
}
#endif