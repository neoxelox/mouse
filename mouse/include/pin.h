#ifndef Pin_h
#define Pin_h

namespace pin
{
    static const uint8_t ADNS_NCS = 17;
    static const uint8_t ADNS_NRESET = 13;
    static const uint8_t ADNS_SCLK = 15;
    static const uint8_t ADNS_SDI = 16;
    static const uint8_t ADNS_SDO = 14;

    static const uint8_t BUTTON_LEFT = 7;
    static const uint8_t BUTTON_RIGHT = 3;
    static const uint8_t BUTTON_MIDDLE = 2;
    static const uint8_t BUTTON_SIDE_LEFT = 1;
    static const uint8_t BUTTON_SIDE_RIGHT = 0;

    static const uint8_t ENCODER_A = 6;
    static const uint8_t ENCODER_B = 5;

    static const uint8_t LED_RED = 9;
    static const uint8_t LED_GREEN = 10;
    static const uint8_t LED_BLUE = 11;
}

#endif /* Pin_h */
