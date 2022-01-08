#include <Arduino.h>
#include <Adns5050.h>

#include "pin.h"

#define SENSOR_ORIGINAL_PRODUCT_ID 0x12                            // ADNS5050 Product ID
#define SENSOR_ALTERNATIVE_PRODUCT_ID 0x26                         // ADNS5050 Product ID2
#define SENSOR_REVISION_ID 0x01                                    // ADNS5050 Revision ID
#define SENSOR_INVERTED_REVISION_ID ((~SENSOR_REVISION_ID) & 0xFF) // ADNS5050 Inverted Revision ID
#define SENSOR_WIDTH 19                                            // ADNS5050 Sensor width
#define SENSOR_HEIGHT 19                                           // ADNS5050 Sensor height

Adns5050 sensor(pin::ADNS_NCS, pin::ADNS_NRESET);

byte frame[SENSOR_WIDTH][SENSOR_HEIGHT];
byte pixel;
int x = 0, y = SENSOR_HEIGHT - 1;

void sendFrame()
{
    for (int i = 0; i < SENSOR_WIDTH; i++)
        for (int j = 0; j < SENSOR_HEIGHT; j++)
            Serial.write(frame[i][j]);

    Serial.write('\n'); // Needed to sincronize Arduino and Computer
}

void setup()
{
    Serial.begin(115200);

    bool ok = sensor.begin();

    ok = ok && (sensor.read(ADNS_5050_reg::Product_ID) == SENSOR_ORIGINAL_PRODUCT_ID);
    ok = ok && (sensor.read(ADNS_5050_reg::Product_ID2) == SENSOR_ALTERNATIVE_PRODUCT_ID);
    ok = ok && (sensor.read(ADNS_5050_reg::Revision_ID) == SENSOR_REVISION_ID);
    ok = ok && (sensor.read(ADNS_5050_reg::Inv_Rev_ID) == SENSOR_INVERTED_REVISION_ID);

    if (!ok)
        Serial.println("ADNS5050 is unreachable!");

    sensor.write(ADNS_5050_reg::Pixel_Grab, 0);
}

void loop()
{
    pixel = sensor.read(ADNS_5050_reg::Pixel_Grab);

    if (pixel & 0x80)
    {
        frame[x][y] = pixel;
        y--;

        if (y < 0)
        {
            x++;
            y = SENSOR_HEIGHT - 1;

            if (x > (SENSOR_WIDTH - 1))
            {
                sendFrame();
                x = 0;
                y = SENSOR_HEIGHT - 1;
                sensor.write(ADNS_5050_reg::Pixel_Grab, 0);
            }
        }
    }
}
