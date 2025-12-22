#include <configuration.h>

#include <lib/logging.h>

#include <lib/EspNowSensor.h>
#include <WizMote.h>

WizMoteClass WizMote;
uint8_t   dataButton = 0;
uint8_t   dataBatteryLevel = 0;

bool      ButtonDataSent = false;

//=============================ESP!Now
void OnDataSent(
    #ifdef ESP8266 
    uint8_t *mac, uint8_t sendStatus
    #endif
    #ifdef ESP32
    const uint8_t *mac_addr, esp_now_send_status_t status
    #endif
)
{
    #ifdef ESP32
    uint8_t sendStatus = (uint8_t)status;
    uint8_t mac[6];
    mac[0] = mac_addr[0];
    mac[1] = mac_addr[1];
    mac[2] = mac_addr[2];
    mac[3] = mac_addr[3];
    mac[4] = mac_addr[4];
    mac[5] = mac_addr[5];
    #endif

    EspNowSensor.OnDataSent(mac,sendStatus);
}
void OnDataRecv(
                #ifdef ESP8266
                uint8_t * mac, uint8_t *incomingData, uint8_t len
                #endif
                #ifdef ESP32
                const esp_now_recv_info *esp_now_info, const uint8_t *incomingData, int len
                #endif
)
{
  #ifdef ESP32
  uint8_t mac[6];
  mac[0] = esp_now_info->src_addr[0];
  mac[1] = esp_now_info->src_addr[1];
  mac[2] = esp_now_info->src_addr[2];
  mac[3] = esp_now_info->src_addr[3];
  mac[4] = esp_now_info->src_addr[4];
  mac[5] = esp_now_info->src_addr[5];
  #endif
      
  EspNowSensor.OnDataRecv(mac,incomingData,len);
}

//=============================Main
void setup() {
  EspNowSensor.begin();
  EspNowSensor.registerSendCallback(OnDataSent);
  EspNowSensor.registerRecvCallback(OnDataRecv);

  WizMote.begin();

  #ifdef CONFIG_MODE_ON_OFF 
    pinMode(IO_BUTTON_ON_PIN, IO_BUTTON_MODE);
    pinMode(IO_BUTTON_OFF_PIN, IO_BUTTON_MODE);
    if ( (digitalRead(IO_BUTTON_ON_PIN) == IO_BUTTON_POLARITY) && (digitalRead(IO_BUTTON_OFF_PIN) == IO_BUTTON_POLARITY) ) 
    {
      printLogMsgTime("Info: Entering config mode: Button ON + OFF pressed\n");
      EspNowSensor.configmodeEnter();
    }
  #endif
  #ifdef CONFIG_MODE_1_2
    pinMode(IO_BUTTON_1_PIN, IO_BUTTON_MODE);
    pinMode(IO_BUTTON_2_PIN, IO_BUTTON_MODE);
    if ( (digitalRead(IO_BUTTON_1_PIN) == IO_BUTTON_POLARITY) && (digitalRead(IO_BUTTON_2_PIN) == IO_BUTTON_POLARITY) ) 
    {
      printLogMsgTime("Info: Entering config mode: Button 1 + 2 pressed\n");
      EspNowSensor.configmodeEnter();
    }
  #endif

  //Read pressed button
  if (!EspNowSensor.configmode) {
    dataButton = WizMote.readButtonPress(true);
    printLogMsgTime("Info: Button code: %d\n", dataButton);
    #ifdef CONFIG_ENTER_BUTTON_CODE
    if (dataButton==CONFIG_ENTER_BUTTON_CODE) {
      printLogMsgTime("Info: Entering config mode: Button code %d\n", CONFIG_ENTER_BUTTON_CODE);
      EspNowSensor.configmodeEnter();
      dataButton = 0;
    }
    #endif
  }
  dataBatteryLevel = EspNowSensor.batteryLevel();
}

void loop() {
  EspNowSensor.configmodeHandle();

  if (EspNowSensor.configmode){
      #ifdef CONFIG_LEAVE_BUTTON_CODE
//      const uint32_t interval = 1000;
//      static uint32_t nextTime = millis() + interval;
//      if (millis()  >= nextTime)
//      {
//
//        nextTime += interval;
        uint8_t nextButton = WizMote.readButtonPress(false);
        if (nextButton==CONFIG_LEAVE_BUTTON_CODE)
        {        
          printLogMsgTime("Info: Leaving config mode: Button code %d\n", CONFIG_LEAVE_BUTTON_CODE);
          EspNowSensor.configmodeLeave();
          dataButton = 0;
          EspNowSensor.powerOff();
        }
//      }
      #endif
  }
  else if (EspNowSensor.broadcastSending) ;
  else if (!EspNowSensor.readyToSend) EspNowSensor.espnowAuthCheck();
  else if (!ButtonDataSent) {
    #ifdef TELEGRAM_PROGRAM_WIZMOTE_COMPATIBLE
      if (dataButton==1) EspNowSensor.espnowMessageDataSetProgram(0x91); // 0x91 for ON button  (Wiz Smart Remote)
      else if (dataButton==100) EspNowSensor.espnowMessageDataSetProgram(0x91); // 0x91 for ON button (Wiz Smart Button)
      else EspNowSensor.espnowMessageDataSetProgram(0x81); //0x81 for all others
    #endif
    uint8_t buttonEvent = dataButton;
    if (dataButton==0) 
    {
      #ifndef BUTTON_TIMEOUT_EVENT
      printLogMsgTime("Info: Button: Timeout: Nothing to send\n");
      EspNowSensor.powerOff();
      #endif
      #ifdef BUTTON_TIMEOUT_EVENT
      buttonEvent = BUTTON_TIMEOUT_EVENT;
      printLogMsgTime("Info: Button: Timeout: Event: %d\n", buttonEvent);
      #endif
    }

    EspNowSensor.espnowMessageDataAddSensorValue(DPID_STATE, buttonEvent);
    EspNowSensor.espnowMessageDataAddSensorValue(DPID_BATTERY,dataBatteryLevel);
    ButtonDataSent = true;
  }
  else if (dataButton!=WizMote.repeatingButtonCode) {                                               
    EspNowSensor.powerOff();
  }
  else if ((millis()>=(WizMote.ButtonTimeStamp+REPEAT_PRESS_TIME)) ) {  
    uint8_t nextButton = WizMote.readButtonPress(false);
    if ( (nextButton==dataButton) ) {
      printLogMsgTime("Info: Button code: %d ..repeating\n", dataButton);
      #ifdef ACTIVE_PIN
        digitalWrite(ACTIVE_PIN, !ACTIVE_PIN_POLARITY);
        delay(100); 
        digitalWrite(ACTIVE_PIN, ACTIVE_PIN_POLARITY);
      #endif
      ButtonDataSent = false;
    }
    dataButton = nextButton;
  }

  EspNowSensor.shutDownCheck();
  printLogMsgIdle();
  delay(10);    // Add a small delay to avoid overwhelming the CPU
}
