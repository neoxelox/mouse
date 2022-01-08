#include <Arduino.h>

#include "logger.h"

namespace logger
{
    unsigned char level = levels::NONE;
    char buffer[128];

    void setup() {}

    void debug(const char *message)
    {
        if (levels::DEBUG >= level)
        {
            Serial.print("[DEBUG]\t");
            Serial.println(message);
            Serial.flush();
        }
    }

    void info(const char *message)
    {
        if (levels::INFO >= level)
        {
            Serial.print("[INFO]\t");
            Serial.println(message);
            Serial.flush();
        }
    }
}
