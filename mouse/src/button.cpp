#include <Arduino.h>
#include <Mouse.h>

#include "pin.h"
#include "logger.h"
#include "button.h"
#include "sensor.h"
#include "led.h"

namespace button
{
#define BUTTON_DEBOUNCE 50 // milliseconds

#define PRESSED true
#define RELEASED false

    volatile byte LEFT_FLAG = RELEASED;
    volatile byte RIGHT_FLAG = RELEASED;
    volatile byte MIDDLE_FLAG = RELEASED;
    volatile byte SIDE_LEFT_FLAG = RELEASED;
    volatile byte SIDE_RIGHT_FLAG = RELEASED;

    byte LAST_LEFT_FLAG = LEFT_FLAG;
    byte LAST_RIGHT_FLAG = RIGHT_FLAG;
    byte LAST_MIDDLE_FLAG = MIDDLE_FLAG;
    byte LAST_SIDE_LEFT_FLAG = SIDE_LEFT_FLAG;
    byte LAST_SIDE_RIGHT_FLAG = SIDE_RIGHT_FLAG;

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
            if (LEFT_FLAG != PRESSED && ((millis() - leftLastFalling) > BUTTON_DEBOUNCE))
            {
                LEFT_FLAG = PRESSED;
                leftLastRising = millis();
            }
        }
        else
        {
            if (LEFT_FLAG != RELEASED && ((millis() - leftLastRising) > BUTTON_DEBOUNCE))
            {
                LEFT_FLAG = RELEASED;
                leftLastFalling = millis();
            }
        }
    }

    void rightInterrupt()
    {
        if (digitalRead(pin::BUTTON_RIGHT) == HIGH)
        {
            if (RIGHT_FLAG != PRESSED && ((millis() - rightLastFalling) > BUTTON_DEBOUNCE))
            {
                RIGHT_FLAG = PRESSED;
                rightLastRising = millis();
            }
        }
        else
        {
            if (RIGHT_FLAG != RELEASED && ((millis() - rightLastRising) > BUTTON_DEBOUNCE))
            {
                RIGHT_FLAG = RELEASED;
                rightLastFalling = millis();
            }
        }
    }

    void middleInterrupt()
    {
        if (digitalRead(pin::BUTTON_MIDDLE) == HIGH)
        {
            if (MIDDLE_FLAG != PRESSED && ((millis() - middleLastFalling) > BUTTON_DEBOUNCE))
            {
                MIDDLE_FLAG = PRESSED;
                middleLastRising = millis();
            }
        }
        else
        {
            if (MIDDLE_FLAG != RELEASED && ((millis() - middleLastRising) > BUTTON_DEBOUNCE))
            {
                MIDDLE_FLAG = RELEASED;
                middleLastFalling = millis();
            }
        }
    }

    void sideLeftInterrupt()
    {
        if (digitalRead(pin::BUTTON_SIDE_LEFT) == HIGH)
        {
            if (SIDE_LEFT_FLAG != PRESSED && ((millis() - sideLeftLastFalling) > BUTTON_DEBOUNCE))
            {
                SIDE_LEFT_FLAG = PRESSED;
                sideLeftLastRising = millis();
            }
        }
        else
        {
            if (SIDE_LEFT_FLAG != RELEASED && ((millis() - sideLeftLastRising) > BUTTON_DEBOUNCE))
            {
                SIDE_LEFT_FLAG = RELEASED;
                sideLeftLastFalling = millis();
            }
        }
    }

    void sideRightInterrupt()
    {
        if (digitalRead(pin::BUTTON_SIDE_RIGHT) == HIGH)
        {
            if (SIDE_RIGHT_FLAG != PRESSED && ((millis() - sideRightLastFalling) > BUTTON_DEBOUNCE))
            {
                SIDE_RIGHT_FLAG = PRESSED;
                sideRightLastRising = millis();
            }
        }
        else
        {
            if (SIDE_RIGHT_FLAG != RELEASED && ((millis() - sideRightLastRising) > BUTTON_DEBOUNCE))
            {
                SIDE_RIGHT_FLAG = RELEASED;
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
        if (LEFT_FLAG != LAST_LEFT_FLAG)
        {
            if (LEFT_FLAG == PRESSED)
            {
                logger::debug("Left button pressed");

                if (!Mouse.isPressed(MOUSE_LEFT))
                    Mouse.press(MOUSE_LEFT);
            }
            else if (LEFT_FLAG == RELEASED)
            {
                logger::debug("Left button released");

                if (Mouse.isPressed(MOUSE_LEFT))
                    Mouse.release(MOUSE_LEFT);
            }

            LAST_LEFT_FLAG = LEFT_FLAG;
        }

        if (RIGHT_FLAG != LAST_RIGHT_FLAG)
        {
            if (RIGHT_FLAG == PRESSED)
            {
                logger::debug("Right button pressed");

                if (!Mouse.isPressed(MOUSE_RIGHT))
                    Mouse.press(MOUSE_RIGHT);
            }
            else if (RIGHT_FLAG == RELEASED)
            {
                logger::debug("Right button released");

                if (Mouse.isPressed(MOUSE_RIGHT))
                    Mouse.release(MOUSE_RIGHT);
            }

            LAST_RIGHT_FLAG = RIGHT_FLAG;
        }

        if (MIDDLE_FLAG != LAST_MIDDLE_FLAG)
        {
            if (MIDDLE_FLAG == PRESSED)
            {
                logger::debug("Middle button pressed");

                if (!Mouse.isPressed(MOUSE_MIDDLE))
                    Mouse.press(MOUSE_MIDDLE);
            }
            else if (MIDDLE_FLAG == RELEASED)
            {
                logger::debug("Middle button released");

                if (Mouse.isPressed(MOUSE_MIDDLE))
                    Mouse.release(MOUSE_MIDDLE);
            }

            LAST_MIDDLE_FLAG = MIDDLE_FLAG;
        }

        if (SIDE_LEFT_FLAG != LAST_SIDE_LEFT_FLAG)
        {
            if (SIDE_LEFT_FLAG == PRESSED)
            {
                logger::debug("Side left button pressed");

                led::changeAnimation();
            }
            else if (SIDE_LEFT_FLAG == RELEASED)
            {
                logger::debug("Side left button released");
            }

            LAST_SIDE_LEFT_FLAG = SIDE_LEFT_FLAG;
        }

        if (SIDE_RIGHT_FLAG != LAST_SIDE_RIGHT_FLAG)
        {
            if (SIDE_RIGHT_FLAG == PRESSED)
            {
                logger::debug("Side right button pressed");

                sensor::changeCpi();
            }
            else if (SIDE_RIGHT_FLAG == RELEASED)
            {
                logger::debug("Side right button released");
            }

            LAST_SIDE_RIGHT_FLAG = SIDE_RIGHT_FLAG;
        }
    }
}
