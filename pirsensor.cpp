#include "pirsensor.h"

#include <cmath>

#include <ads1115.h>
#include <wiringPi.h>

// Just works, I don't know why ;-)
static const int base = 100;

PIRSensor::PIRSensor()
{
    ads1115Setup (base, 0x48);
}

float PIRSensor::value(int channel) const
{
    float voltage (NAN);

    do
    {
        if (channel < 0 || channel > 3)
        {
            break;
        }

        float value = analogRead (base + channel);
        voltage = (float) value * 4.096 / 32768.0;
    }
    while (false);

    return voltage;
}
