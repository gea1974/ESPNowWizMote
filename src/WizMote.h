#ifndef WizMote_h
#define WizMote_h

#include <Arduino.h>
#include <Wire.h>

#include <configuration.h>
#include <lib/logging.h>

class WizMoteClass {

public:

    WizMoteClass();

    void begin();

    uint8_t readButtonPress(bool timeoutCheck);

    uint8_t repeatingButtonCode = 255;
    bool broadcastSent = false;
    uint32_t ButtonTimeStamp = 0;

private:
    #ifdef WIZMOTE_PCA6416A
    void ButtonPCA6416A();
    #endif
    #ifdef WIZMOTE_HC165
    void ButtonHC165();
    #endif
    #ifdef BUTTON_IO
    void ButtonIO();
    #endif

    bool initialized = false;
    bool ButtonResetFired = false;

    uint8_t incomingButtonPressed;
    bool sleepButtonPressed;
};

#endif