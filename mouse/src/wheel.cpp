#include <Arduino.h>
#include <Mouse.h>
#include <NoDelay.h>

#include "pin.h"
#include "logger.h"
#include "wheel.h"

namespace wheel
{
#define WHEEL_SAMPLE_RATE 1 // milliseconds
#define WHEEL_SENSITIVY 2   // factor
#define WHEEL_DEBOUNCE 1    // milliseconds

    byte state = 0;
    byte lastState = 0;
    unsigned long lastChange = 0;

    noDelay timer(WHEEL_SAMPLE_RATE, []()
                  {
                      state = digitalRead(pin::ENCODER_A) | (digitalRead(pin::ENCODER_B) << 1);

                      if (state != lastState && ((millis() - lastChange) > WHEEL_DEBOUNCE))
                      {
                          lastChange = millis();

                          switch (state)
                          {
                          case 0:
                              if (lastState == 2)
                                  Mouse.move(0, 0, 1 * WHEEL_SENSITIVY);
                              else if (lastState == 1)
                                  Mouse.move(0, 0, -1 * WHEEL_SENSITIVY);
                              break;
                          case 1:
                              if (lastState == 0)
                                  Mouse.move(0, 0, 1 * WHEEL_SENSITIVY);
                              else if (lastState == 3)
                                  Mouse.move(0, 0, -1 * WHEEL_SENSITIVY);
                              break;
                          case 2:
                              if (lastState == 3)
                                  Mouse.move(0, 0, 1 * WHEEL_SENSITIVY);
                              else if (lastState == 0)
                                  Mouse.move(0, 0, -1 * WHEEL_SENSITIVY);
                              break;
                          case 3:
                              if (lastState == 1)
                                  Mouse.move(0, 0, 1 * WHEEL_SENSITIVY);
                              else if (lastState == 2)
                                  Mouse.move(0, 0, -1 * WHEEL_SENSITIVY);
                              break;
                          }
                      }

                      lastState = state;
                  });

    void setup()
    {
        pinMode(pin::ENCODER_A, INPUT);
        pinMode(pin::ENCODER_B, INPUT);
    }

    void loop()
    {
        timer.update();
    }
}
