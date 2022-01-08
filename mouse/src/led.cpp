#include <Arduino.h>
#include <AlaLedRgb.h>

#include "pin.h"
#include "logger.h"
#include "led.h"

namespace led
{
#define LED_REFRESH_RATE 60     // hertzs
#define LED_BRIGHTNESS 0xFFFFFF // pwm per led
#define LED_DEFAULT_ANIMATION 0 // animations index

    struct Animation
    {
        const char *name;
        long duration;
        int mode;
        AlaPalette colors;
    };

    Animation animations[5] = {
        {
            "FADE_RAINBOW_LOOP",
            10000,
            ALA_FADECOLORSLOOP,
            alaPalParty,
        },
        {
            "GLOW_RED",
            5000,
            ALA_GLOW,
            alaPalRed,
        },
        {
            "GLOW_GREEN",
            5000,
            ALA_GLOW,
            alaPalGreen,
        },
        {
            "GLOW_BLUE",
            5000,
            ALA_GLOW,
            alaPalBlue,
        },
        {
            "NO_ANIMATION",
            0,
            ALA_OFF,
            alaPalNull,
        },
    };

    int animationsIterator = LED_DEFAULT_ANIMATION - 1;

    AlaLedRgb leds;

    void changeAnimation()
    {
        animationsIterator++;
        if (animationsIterator >= 5)
            animationsIterator = 0;

        logger::debug("Changed led animation to %s", animations[animationsIterator].name);

        leds.setAnimation(animations[animationsIterator].mode, animations[animationsIterator].duration, animations[animationsIterator].colors);
    }

    void setup()
    {
        leds.setRefreshRate(LED_REFRESH_RATE);
        leds.setBrightness(LED_BRIGHTNESS);
        changeAnimation();
        leds.initPWM(pin::LED_RED, pin::LED_GREEN, pin::LED_BLUE);
    }

    void loop()
    {
        leds.runAnimation();
    }
}
