#define PRODUCT                             "ESP!NOW Remote"
#define PRODUCT_FAMILY_KEY                  0x03
#define VERSION                             0x001007
#define OWNER                               "gea"

#define ESPNOW_TELEGRAM_WIZMOTE
#define TELEGRAM_PROGRAM_WIZMOTE_COMPATIBLE       //use 0x91 Button=1 and 0x81 Button!=1
#define DPID_STATE                          32
#define DPID_BATTERY                        1
#define ESPNOW_SEND_DATA_COMPLETE

    #ifdef WIZMOTE_PCA6416A
        #define PRODUCT_ID                  "WIZMOTE"
        #define PRODUCT_KEY                 0x02
        #define DESCRIPTION                 "Wiz Smart Remote - PCA6416A"
        #define SDA_PIN                     14
        #define SCL_PIN                     2
        #define PCA6416A_I2C_ADDR           0x20
        #define PCA6416A_INPORT0            0x00
        #define VOLTAGE_REGULATOR_PIN       16
        #define BATTERY_VOLTAGE_ADC_PIN         A0
        // PCA6416A - Low-voltage translating 16-bit I2C-bus/SMBus I/O expander
        //   Datasheet: https://www.nxp.com/docs/en/data-sheet/PCA6416A.pdf
    #endif

    #ifdef WIZMOTE_HC165
        #define PRODUCT_ID                  "WIZMOTE"
        #define PRODUCT_KEY                 0x01
        #define DESCRIPTION                 "Wiz Smart Remote - HC165"
        #define SDA_PIN                     5
        #define SCL_PIN                     4
        #define LOAD_PIN                    13
        #define IO_BUTTON_MOON_PIN         14   
        #define IO_BUTTON_POLARITY          LOW
        #ifdef WIZMOTE_ACTIVE_LED_MOD
            #define ACTIVE_PIN              2
            #define ACTIVE_PIN_POLARITY     LOW
        #endif
        #define POWER_OFF_VOLTAGE_REGULATOR
        #define VOLTAGE_REGULATOR_PIN       16
        #define BATTERY_2AAA
        #define BATTERY_VOLTAGE_ADC_PIN     A0
        #define BATTERY_VOLTAGE_DIVIDER     3.5
        #define CONFIG_ENTER_BUTTON_CODE    71  
        #define CONFIG_LEAVE_BUTTON_CODE    72
        #define BUTTON_CODES_ON             {1,  0,  0,  0,  0,  0,  71, 0}
        #define BUTTON_CODES_OFF            {2,  0,  0,  0,  0,  0,  72, 0}
        #define BUTTON_CODES_UP             {9,  0,  0,  0,  0,  0,  0 , 9}
        #define BUTTON_CODES_DOWN           {8,  0,  0,  0,  0,  0,  0 , 8}
        #define BUTTON_CODES_1              {16, 0,  0,  0,  0,  0,  76, 0}
        #define BUTTON_CODES_2              {17, 0,  0,  0,  0,  0,  77, 0}
        #define BUTTON_CODES_3              {18, 0,  0,  0,  0,  0,  78, 0}
        #define BUTTON_CODES_4              {19, 0,  0,  0,  0,  0,  79, 0}
        #define BUTTON_CODES_MOON           {3,  0,  0,  0,  0,  0,  0 , 0}
    #endif

    #if (defined WEMOS_MOTE_ON_UP_DOWN_OFF || defined WEMOS_MOTE_ON_OFF_1_2 || defined WEMOS_MOTE_1_2_3_4)
        #define PRODUCT_ID                  "WEMOSMOTE"
        #define PRODUCT_KEY                 0x03
        #define DESCRIPTION_TYPE            "Wemos Remote " 
        #define BUTTON_IO
        #define IO_BUTTON_POLARITY          LOW
        #define IO_BUTTON_MODE              INPUT_PULLUP    
        #define ACTIVE_PIN                  15
        #define ACTIVE_PIN_POLARITY         HIGH
        #define POWER_OFF_DEEPSLEEP
        #ifdef WEMOS_MOTE_ON_UP_DOWN_OFF
            #define DESCRIPTION                 DESCRIPTION_TYPE "(ON-UP-DOWN-OFF)" 
            #define IO_BUTTON_ON_PIN            14
            #define IO_BUTTON_OFF_PIN           12
            #define IO_BUTTON_UP_PIN            4
            #define IO_BUTTON_DOWN_PIN          13
            #define CONFIG_MODE_ON_OFF 
            #define CONFIG_LEAVE_BUTTON_CODE    2 
            #define BUTTON_CODES_ON             {1,  0,  0,  0,  0,  0,  16 , 0}
            #define BUTTON_CODES_OFF            {2,  0,  0,  0,  0,  0,  17 , 0}
            #define BUTTON_CODES_UP             {9,  0,  0,  0,  0,  0,  0  , 9}
            #define BUTTON_CODES_DOWN           {8,  0,  0,  0,  0,  0,  0  , 8}
        #endif
        #ifdef WEMOS_MOTE_ON_OFF_1_2
            #define DESCRIPTION                 DESCRIPTION_TYPE "(ON-OFF-1-2)"  
            #define IO_BUTTON_ON_PIN            14
            #define IO_BUTTON_OFF_PIN           12
            #define IO_BUTTON_1_PIN             13
            #define IO_BUTTON_2_PIN             4
            #define CONFIG_MODE_ON_OFF 
            #define CONFIG_LEAVE_BUTTON_CODE    2 
            #define BUTTON_CODES_ON             {1,  0,  0,  0,  0,  0,  0,  9}
            #define BUTTON_CODES_OFF            {2,  0,  0,  0,  0,  0,  0,  8}
            #define BUTTON_CODES_1              {16, 0,  0,  0,  0,  0,  18 , 0}
            #define BUTTON_CODES_2              {17, 0,  0,  0,  0,  0,  19 , 0}
        #endif  
        #ifdef WEMOS_MOTE_1_2_3_4
            #define DESCRIPTION                 DESCRIPTION_TYPE "(1-2-3-4)"   
            #define IO_BUTTON_1_PIN             14
            #define IO_BUTTON_2_PIN             12
            #define IO_BUTTON_3_PIN             13
            #define IO_BUTTON_4_PIN             4
            #define CONFIG_MODE_1_2
            #define CONFIG_LEAVE_BUTTON_CODE    17
            #define BUTTON_CODES_1              {16, 0,  0,  0,  0,  0,  76 , 0}
            #define BUTTON_CODES_2              {17, 0,  0,  0,  0,  0,  77 , 0}
            #define BUTTON_CODES_3              {18, 0,  0,  0,  0,  0,  78 , 0}
            #define BUTTON_CODES_4              {19, 0,  0,  0,  0,  0,  79 , 0}
        #endif  
    #endif


    #if (defined WIFI_4BUTTON_REMOTE_ON_UP_DOWN_OFF || defined WIFI_4BUTTON_REMOTE_ON_1_2_OFF || defined WIFI_4BUTTON_REMOTE_1_2_3_4 || defined WIFI_4BUTTON_REMOTE_1_2_3_OFF)
        #define PRODUCT_ID                      "4BWIFIREMOTE"
        #define PRODUCT_KEY                     0x04
        #define DESCRIPTION_TYPE                "4 Button Wifi Remote " 
        #define BUTTON_IO
        #define IO_BUTTON_POLARITY              HIGH
        #define IO_BUTTON_MODE                  INPUT    
        #define ACTIVE_PIN                      2
        #define ACTIVE_PIN_POLARITY             LOW
        #define BATTERY_LIPO
        #define BATTERY_VOLTAGE_ADC_PIN         A0
        #define BATTERY_VOLTAGE_DIVIDER         5.4
        #define POWER_OFF_DEEPSLEEP
        #ifdef WIFI_4BUTTON_REMOTE_ON_UP_DOWN_OFF
            #define DESCRIPTION                 DESCRIPTION_TYPE "(ON-UP-DOWN-OFF)"
            #define IO_BUTTON_ON_PIN            14
            #define IO_BUTTON_UP_PIN            4
            #define IO_BUTTON_DOWN_PIN          12
            #define IO_BUTTON_OFF_PIN           13
            #define CONFIG_MODE_ON_OFF 
            #define CONFIG_LEAVE_BUTTON_CODE    2 
            #define BUTTON_CODES_ON             {1,  0,  0,  0,  0,  0,  16 , 0}
            #define BUTTON_CODES_OFF            {2,  0,  0,  0,  0,  0,  17 , 0}
            #define BUTTON_CODES_UP             {9,  0,  0,  0,  0,  0,  0  , 9}
            #define BUTTON_CODES_DOWN           {8,  0,  0,  0,  0,  0,  0  , 8}
        #endif
        #ifdef WIFI_4BUTTON_REMOTE_ON_1_2_OFF
            #define DESCRIPTION                 DESCRIPTION_TYPE "(ON-1-2-OFF)"
            #define IO_BUTTON_ON_PIN            14
            #define IO_BUTTON_1_PIN             4
            #define IO_BUTTON_2_PIN             12
            #define IO_BUTTON_OFF_PIN           13
            #define CONFIG_MODE_ON_OFF 
            #define CONFIG_LEAVE_BUTTON_CODE    2 
            #define BUTTON_CODES_ON             {1,  0,  0,  0,  0,  0,  0  , 9}
            #define BUTTON_CODES_OFF            {2,  0,  0,  0,  0,  0,  0  , 8}
            #define BUTTON_CODES_1              {16, 0,  0,  0,  0,  0,  18 , 0}
            #define BUTTON_CODES_2              {17, 0,  0,  0,  0,  0,  19 , 0}
        #endif
        #ifdef WIFI_4BUTTON_REMOTE_1_2_3_4
            #define DESCRIPTION                 DESCRIPTION_TYPE "(1-2-3-4)"
            #define IO_BUTTON_1_PIN             14
            #define IO_BUTTON_2_PIN             4
            #define IO_BUTTON_3_PIN             12
            #define IO_BUTTON_4_PIN             13
            #define CONFIG_MODE_1_2
            #define CONFIG_LEAVE_BUTTON_CODE    17
            #define BUTTON_CODES_1              {16, 0,  0,  0,  0,  0,  76 , 0}
            #define BUTTON_CODES_2              {17, 0,  0,  0,  0,  0,  77 , 0}
            #define BUTTON_CODES_3              {18, 0,  0,  0,  0,  0,  78 , 0}
            #define BUTTON_CODES_4              {19, 0,  0,  0,  0,  0,  79 , 0}
        #endif
        #ifdef WIFI_4BUTTON_REMOTE_1_2_3_OFF
            #define DESCRIPTION                 DESCRIPTION_TYPE "(1-2-3-OFF)"
            #define IO_BUTTON_1_PIN             14
            #define IO_BUTTON_2_PIN             4
            #define IO_BUTTON_3_PIN             12
            #define IO_BUTTON_OFF_PIN           13
            #define CONFIG_MODE_1_2
            #define CONFIG_LEAVE_BUTTON_CODE    17
            #define BUTTON_CODES_1              {16, 0,  0,  0,  0,  0,  0  , 0}
            #define BUTTON_CODES_2              {17, 0,  0,  0,  0,  0,  0  , 0}
            #define BUTTON_CODES_3              {18, 0,  0,  0,  0,  0,  0  , 0}
            #define BUTTON_CODES_OFF            {2,  0,  0,  0,  0,  0,  1  , 0}
        #endif
    #endif

    #ifdef TUYA_2BUTTON_SCENE_SWITCH
        #define PRODUCT_ID                  "2BUTTONSCENE"
        #define PRODUCT_KEY                 0x05
        #define DESCRIPTION_TYPE            "Tuya 2 Button Scene switch "
        #define DESCRIPTION                 DESCRIPTION_TYPE "(ON-OFF)"
        #define BUTTON_IO
        #define IO_BUTTON_POLARITY          LOW
        #define IO_BUTTON_MODE              INPUT_PULLUP    
        #define IO_BUTTON_ON_PIN            1
        #define IO_BUTTON_OFF_PIN           2
        #define ACTIVE_PIN                  4
        #define ACTIVE_PIN_POLARITY         HIGH
        #define BATTERY_VOLTAGE_ADC_PIN     0   
        #define BATTERY_VOLTAGE_ON_PIN      5
        #define BATTERY_2AAA
        #define BATTERY_VOLTAGE_DIVIDER     2.509
        #define CONFIG_MODE_ON_OFF 
        #define CONFIG_LEAVE_BUTTON_CODE    2 
        #define POWER_OFF_DEEPSLEEP
        #define DEEPSLEEP_WAKEUP_GPIO_PIN1  1
        #define DEEPSLEEP_WAKEUP_GPIO_PIN2  2
        #ifdef WIZ_SMART_BUTTON_CODES
            #define BUTTON_CODES_ON             {100,  0,  0,  0,  0,  0,  0,  102}
            #define BUTTON_CODES_OFF            {101,  0,  0,  0,  0,  0,  0,  103}
        #else
            #define BUTTON_CODES_ON             {1,  16,  18,  0,  0,  0,  0,  9}
            #define BUTTON_CODES_OFF            {2,  17,  19,  0,  0,  0,  0,  8}
        #endif

        #define BUTTON_TIMEOUT_EVENT        0

        #define SERIAL_DEBUG_TX_PIN         18
        #define SERIAL_DEBUG_RX_PIN         10
        #define SERIAL_DEBUG_PORT           0 
        #define BAUD_RATE_DEBUG             115200
    #endif  

    #ifdef BUTTON_RESET
        #define PRODUCT_ID                      "BUTTONRESET"    
        #define PRODUCT_KEY                     0x06  
        #define DESCRIPTION_TYPE                "Wifi Button Reset" 
        #if BUTTON_RESET==1
            #define DESCRIPTION_FUNC            "(on)"
        #elif BUTTON_RESET==2
            #define DESCRIPTION_FUNC            "(off)"        
        #elif BUTTON_RESET==3
            #define DESCRIPTION_FUNC            "(moon)"  
        #elif BUTTON_RESET==16
            #define DESCRIPTION_FUNC            "(1)"  
        #elif BUTTON_RESET==17
            #define DESCRIPTION_FUNC            "(2)"  
        #elif BUTTON_RESET==18
            #define DESCRIPTION_FUNC            "(3)"  
        #elif BUTTON_RESET==19
            #define DESCRIPTION_FUNC            "(4)"  
        #else
            #define DESCRIPTION_FUNC            "(custom)"  
        #endif
        #define DESCRIPTION                     DESCRIPTION_TYPE " " DESCRIPTION_FUNC
        #define ACTIVE_PIN                      2
        #define ACTIVE_PIN_POLARITY             HIGH
        #define BATTERY_VOLTAGE_ADC_PIN         A0
        #define POWER_OFF_DEEPSLEEP
        #define BUTTON_CODES_ON                 {BUTTON_RESET,  0,  0,  0,  0,  0,  0  , 0}
    #endif

#ifndef PRODUCT_ID
    #define PRODUCT_ID                          "REMOTE"
#endif
#ifndef PRODUCT_KEY
    #define PRODUCT_KEY                         0x00
#endif
#ifndef DESCRIPTION
    #define DESCRIPTION                         "Generic Remote"
#endif
// Enter Project configuration above this line
#include <lib/configuration_defaults.h>
#include <configuration_buttons_defaults.h>