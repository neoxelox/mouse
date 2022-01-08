#include <Arduino.h>
#include <Mouse.h>

#include "pin.h"
#include "logger.h"
#include "button.h"
#include "sensor.h"
#include "led.h"

namespace button
{
#define BUTTON_DEBOUNCE_CLICK 150 // milliseconds
#define BUTTON_DEBOUNCE_HOLD 75   // milliseconds

    volatile byte LEFT_FLAG_PRESSED = false;
    volatile byte LEFT_FLAG_RELEASED = false;
    volatile byte RIGHT_FLAG_PRESSED = false;
    volatile byte RIGHT_FLAG_RELEASED = false;
    volatile byte MIDDLE_FLAG_PRESSED = false;
    volatile byte MIDDLE_FLAG_RELEASED = false;
    volatile byte SIDE_LEFT_FLAG_PRESSED = false;
    volatile byte SIDE_LEFT_FLAG_RELEASED = false;
    volatile byte SIDE_RIGHT_FLAG_PRESSED = false;
    volatile byte SIDE_RIGHT_FLAG_RELEASED = false;

    unsigned long leftLastRising = 0;
    unsigned long leftLastFalling = 0;
    unsigned long rightLastRising = 0;
    unsigned long rightLastFalling = 0;
    unsigned long middleLastRising = 0;
    unsigned long middleLastFalling = 0;
    unsigned long sideLeftLastRising = 0;
    unsigned long sideLeftLastFalling = 0;
    unsigned long sideRightLastRising = 0;
    unsigned long sideRightLastFalling = 0;

    void leftInterrupt()
    {
        if (digitalRead(pin::BUTTON_LEFT) == HIGH)
        {
            if ((millis() - leftLastRising) > BUTTON_DEBOUNCE_CLICK)
            {
                LEFT_FLAG_PRESSED = true;
                leftLastRising = millis();
            }
        }
        else
        {
            if (((millis() - leftLastRising) > BUTTON_DEBOUNCE_HOLD) && ((millis() - leftLastFalling) > BUTTON_DEBOUNCE_CLICK))
            {
                LEFT_FLAG_RELEASED = true;
                leftLastFalling = millis();
            }
        }
    }

    void rightInterrupt()
    {
        if (digitalRead(pin::BUTTON_RIGHT) == HIGH)
        {
            if ((millis() - rightLastRising) > BUTTON_DEBOUNCE_CLICK)
            {
                RIGHT_FLAG_PRESSED = true;
                rightLastRising = millis();
            }
        }
        else
        {
            if (((millis() - rightLastRising) > BUTTON_DEBOUNCE_HOLD) && ((millis() - rightLastFalling) > BUTTON_DEBOUNCE_CLICK))
            {
                RIGHT_FLAG_RELEASED = true;
                rightLastFalling = millis();
            }
        }
    }

    void middleInterrupt()
    {
        if (digitalRead(pin::BUTTON_MIDDLE) == HIGH)
        {
            if ((millis() - middleLastRising) > BUTTON_DEBOUNCE_CLICK)
            {
                MIDDLE_FLAG_PRESSED = true;
                middleLastRising = millis();
            }
        }
        else
        {
            if (((millis() - middleLastRising) > BUTTON_DEBOUNCE_HOLD) && ((millis() - middleLastFalling) > BUTTON_DEBOUNCE_CLICK))
            {
                MIDDLE_FLAG_RELEASED = true;
                middleLastFalling = millis();
            }
        }
    }

    void sideLeftInterrupt()
    {
        if (digitalRead(pin::BUTTON_SIDE_LEFT) == HIGH)
        {
            if ((millis() - sideLeftLastRising) > BUTTON_DEBOUNCE_CLICK)
            {
                SIDE_LEFT_FLAG_PRESSED = true;
                sideLeftLastRising = millis();
            }
        }
        else
        {
            if (((millis() - sideLeftLastRising) > BUTTON_DEBOUNCE_HOLD) && ((millis() - sideLeftLastFalling) > BUTTON_DEBOUNCE_CLICK))
            {
                SIDE_LEFT_FLAG_RELEASED = true;
                sideLeftLastFalling = millis();
            }
        }
    }

    void sideRightInterrupt()
    {
        if (digitalRead(pin::BUTTON_SIDE_RIGHT) == HIGH)
        {
            if ((millis() - sideRightLastRising) > BUTTON_DEBOUNCE_CLICK)
            {
                SIDE_RIGHT_FLAG_PRESSED = true;
                sideRightLastRising = millis();
            }
        }
        else
        {
            if (((millis() - sideRightLastRising) > BUTTON_DEBOUNCE_HOLD) && ((millis() - sideRightLastFalling) > BUTTON_DEBOUNCE_CLICK))
            {
                SIDE_RIGHT_FLAG_RELEASED = true;
                sideRightLastFalling = millis();
            }
        }
    }

    void setup()
    {
        pinMode(pin::BUTTON_LEFT, INPUT);
        pinMode(pin::BUTTON_RIGHT, INPUT);
        pinMode(pin::BUTTON_MIDDLE, INPUT);
        pinMode(pin::BUTTON_SIDE_LEFT, INPUT);
        pinMode(pin::BUTTON_SIDE_RIGHT, INPUT);

        attachInterrupt(digitalPinToInterrupt(pin::BUTTON_LEFT), leftInterrupt, CHANGE);
        attachInterrupt(digitalPinToInterrupt(pin::BUTTON_RIGHT), rightInterrupt, CHANGE);
        attachInterrupt(digitalPinToInterrupt(pin::BUTTON_MIDDLE), middleInterrupt, CHANGE);
        attachInterrupt(digitalPinToInterrupt(pin::BUTTON_SIDE_LEFT), sideLeftInterrupt, CHANGE);
        attachInterrupt(digitalPinToInterrupt(pin::BUTTON_SIDE_RIGHT), sideRightInterrupt, CHANGE);
    }

    void loop()
    {
        if (LEFT_FLAG_PRESSED)
        {
            LEFT_FLAG_PRESSED = false;
            logger::debug("Left button pressed");

            if (!Mouse.isPressed(MOUSE_LEFT))
                Mouse.press(MOUSE_LEFT);
        }

        if (LEFT_FLAG_RELEASED)
        {
            LEFT_FLAG_RELEASED = false;
            logger::debug("Left button released");

            if (Mouse.isPressed(MOUSE_LEFT))
                Mouse.release(MOUSE_LEFT);
        }

        if (RIGHT_FLAG_PRESSED)
        {
            RIGHT_FLAG_PRESSED = false;
            logger::debug("Right button pressed");

            if (!Mouse.isPressed(MOUSE_RIGHT))
                Mouse.press(MOUSE_RIGHT);
        }

        if (RIGHT_FLAG_RELEASED)
        {
            RIGHT_FLAG_RELEASED = false;
            logger::debug("Right button released");

            if (Mouse.isPressed(MOUSE_RIGHT))
                Mouse.release(MOUSE_RIGHT);
        }

        if (MIDDLE_FLAG_PRESSED)
        {
            MIDDLE_FLAG_PRESSED = false;
            logger::debug("Middle button pressed");

            if (!Mouse.isPressed(MOUSE_MIDDLE))
                Mouse.press(MOUSE_MIDDLE);
        }

        if (MIDDLE_FLAG_RELEASED)
        {
            MIDDLE_FLAG_RELEASED = false;
            logger::debug("Middle button released");

            if (Mouse.isPressed(MOUSE_MIDDLE))
                Mouse.release(MOUSE_MIDDLE);
        }

        if (SIDE_LEFT_FLAG_PRESSED)
        {
            SIDE_LEFT_FLAG_PRESSED = false;
            logger::debug("Side left button pressed");
        }

        if (SIDE_LEFT_FLAG_RELEASED)
        {
            SIDE_LEFT_FLAG_RELEASED = false;
            logger::debug("Side left button released");

            led::changeAnimation();
        }

        if (SIDE_RIGHT_FLAG_PRESSED)
        {
            SIDE_RIGHT_FLAG_PRESSED = false;
            logger::debug("Side right button pressed");
        }

        if (SIDE_RIGHT_FLAG_RELEASED)
        {
            SIDE_RIGHT_FLAG_RELEASED = false;
            logger::debug("Side right button released");

            sensor::changeCpi();
        }
    }
}
