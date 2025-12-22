// Button Mappings:
// - Button 0: Off Button
// - Button 1: On Button
// - Button 2: Button 2
// - Button 3: Button 1
// - Button 4: Button 4
// - Button 5: Button 3
// - Button 6: Brightness Up
// - Button 7: Brightness Down
// - Button 8: Moon Button
//                               |---Button Pressed--|   HO   REP
//                               1   2   3   4   5   6   LD   EAT
#ifndef BUTTON_CODES_ON
    #define BUTTON_CODES_ON     {0,  0,  0,  0,  0,  0,  0  , 0}
#endif
#ifndef BUTTON_CODES_OFF
    #define BUTTON_CODES_OFF    {0,  0,  0,  0,  0,  0,  0  , 0}
#endif
#ifndef BUTTON_CODES_UP
    #define BUTTON_CODES_UP     {0,  0,  0,  0,  0,  0,  0  , 9}
#endif
#ifndef BUTTON_CODES_DOWN
    #define BUTTON_CODES_DOWN   {0,  0,  0,  0,  0,  0,  0  , 8}
#endif
#ifndef BUTTON_CODES_1
    #define BUTTON_CODES_1      {0,  0,  0,  0,  0,  0,  0 , 0}
#endif
#ifndef BUTTON_CODES_2
    #define BUTTON_CODES_2      {0,  0,  0,  0,  0,  0,  0 , 0}
#endif
#ifndef BUTTON_CODES_3
    #define BUTTON_CODES_3      {0,  0,  0,  0,  0,  0,  0 , 0}
#endif
#ifndef BUTTON_CODES_4
    #define BUTTON_CODES_4      {0,  0,  0,  0,  0,  0,  0 , 0}
#endif
#ifndef BUTTON_CODES_MOON
    #define BUTTON_CODES_MOON   {0,   0,  0,  0,  0,  0,  0  ,0}
#endif

/*
#define BUTTON_CODES_ON     {1,  0,  0,  0,  0,  0,  0  , 0}
#define BUTTON_CODES_OFF    {2,  0,  0,  0,  0,  0,  0  , 0}
#define BUTTON_CODES_UP     {9,  0,  0,  0,  0,  0,  0  , 9}
#define BUTTON_CODES_DOWN   {8,  0,  0,  0,  0,  0,  0  , 8}
#define BUTTON_CODES_1      {16, 26, 36, 46, 56, 66, 116, 0}
#define BUTTON_CODES_2      {17, 27, 37, 47, 57, 67, 117, 0}
#define BUTTON_CODES_3      {18, 28, 38, 48, 58, 68, 118, 0}
#define BUTTON_CODES_4      {19, 29, 39, 49, 59, 69, 119, 0}
#define BUTTON_CODES_MOON   {3,  0,  0,  0,  0,  0,  0  , 0}
*/

#ifndef DOUBLE_PRESS_TIME
    #define DOUBLE_PRESS_TIME                   300
#endif
#ifndef TRIPLE_PRESS_TIME
    #define TRIPLE_PRESS_TIME                   600
#endif
#ifndef LONG_PRESS_THRESHOLD
    #define LONG_PRESS_THRESHOLD                1000
#endif
#ifndef DEBOUNCE_DELAY
    #define DEBOUNCE_DELAY                      50
#endif
#ifndef REPEAT_PRESS_TIME
    #define REPEAT_PRESS_TIME                   300
#endif

#ifndef BUTTON_TIMEOUT
    #define BUTTON_TIMEOUT                      1000
#endif