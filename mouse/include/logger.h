#ifndef Logger_h
#define Logger_h

namespace logger
{
    enum levels : unsigned char
    {
        NONE,
        DEBUG,
        INFO,
    };

    extern unsigned char level;
    extern char buffer[128];

    void setup();

    void debug(const char *message);
    template <typename... Args>
    void debug(const char *message, Args... args)
    {
        if (levels::DEBUG >= level)
        {
            sprintf(buffer, message, args...);
            Serial.print("[DEBUG]\t");
            Serial.println(buffer);
            Serial.flush();
        }
    }

    void info(const char *message);
    template <typename... Args>
    void info(const char *message, Args... args)
    {
        if (levels::INFO >= level)
        {
            sprintf(buffer, message, args...);
            Serial.print("[INFO]\t");
            Serial.println(buffer);
            Serial.flush();
        }
    }
}

#endif /* Logger_h */
