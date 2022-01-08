#include <Arduino.h>
#include <Mouse.h>
#include <Adns5050.h>
#include <NoDelay.h>

#include "pin.h"
#include "logger.h"
#include "sensor.h"

namespace sensor
{
#define SENSOR_SAMPLE_RATE 1                                       // milliseconds
#define SENSOR_DEFAULT_CPI 7                                       // cpis index
#define SENSOR_ORIGINAL_PRODUCT_ID 0x12                            // ADNS5050 Product ID
#define SENSOR_ALTERNATIVE_PRODUCT_ID 0x26                         // ADNS5050 Product ID2
#define SENSOR_REVISION_ID 0x01                                    // ADNS5050 Revision ID
#define SENSOR_INVERTED_REVISION_ID ((~SENSOR_REVISION_ID) & 0xFF) // ADNS5050 Inverted Revision ID

    Adns5050 sensor(pin::ADNS_NCS, pin::ADNS_NRESET);

    noDelay timer(SENSOR_SAMPLE_RATE, []()
                  {
                      if (sensor.read(ADNS_5050_reg::Motion) == 0x80)
                          Mouse.move(sensor.read(ADNS_5050_reg::Delta_X), -sensor.read(ADNS_5050_reg::Delta_Y), 0);
                  });

    struct CPI
    {
        const char *name;
        unsigned char value;
    };

    CPI cpis[11] = {
        {
            "125",
            0x11,
        },
        {
            "250",
            0x12,
        },
        {
            "375",
            0x13,
        },
        {
            "500",
            0x14,
        },
        {
            "625",
            0x15,
        },
        {
            "750",
            0x16,
        },
        {
            "875",
            0x17,
        },
        {
            "1000",
            0x18,
        },
        {
            "1125",
            0x19,
        },
        {
            "1250",
            0x1A,
        },
        {
            "1375",
            0x1B,
        },
    };

    int cpisIterator = SENSOR_DEFAULT_CPI - 1;

    void changeCpi()
    {
        cpisIterator++;
        if (cpisIterator >= 11)
            cpisIterator = 0;

        logger::debug("Changed sensor cpi to %s", cpis[cpisIterator].name);

        sensor.write(ADNS_5050_reg::Mouse_Control2, cpis[cpisIterator].value);
    }

    void setup()
    {
        bool ok = sensor.begin();

        ok = ok && (sensor.read(ADNS_5050_reg::Product_ID) == SENSOR_ORIGINAL_PRODUCT_ID);
        ok = ok && (sensor.read(ADNS_5050_reg::Product_ID2) == SENSOR_ALTERNATIVE_PRODUCT_ID);
        ok = ok && (sensor.read(ADNS_5050_reg::Revision_ID) == SENSOR_REVISION_ID);
        ok = ok && (sensor.read(ADNS_5050_reg::Inv_Rev_ID) == SENSOR_INVERTED_REVISION_ID);

        if (ok)
            changeCpi();
        else
            logger::info("Sensor startup FAIL");
    }

    void loop()
    {
        timer.update();
    }
}
