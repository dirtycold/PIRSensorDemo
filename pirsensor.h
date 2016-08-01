#ifndef PIRSENSOR_H
#define PIRSENSOR_H

class PIRSensor
{
public:
    PIRSensor();
    float value (int channel) const;
};

#endif // PIRSENSOR_H
