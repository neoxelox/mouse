#include <Arduino.h>
#include <Mouse.h>

#include "logger.h"
#include "sensor.h"
#include "led.h"
#include "button.h"
#include "wheel.h"

void setup()
{
    Serial.begin(9600);
    Mouse.begin();

    logger::level = logger::INFO;
    logger::setup();

    sensor::setup();
    led::setup();
    button::setup();
    wheel::setup();
}

void loop()
{
    sensor::loop();
    led::loop();
    button::loop();
    wheel::loop();
}