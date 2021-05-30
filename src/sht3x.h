#ifndef __SHT3X__
#define __SHT3X__

#include <Arduino.h>

#define SHT3X_SAMPLE_MAX (10)

class SHT3X
{
public:
    SHT3X();
    ~SHT3X();

    bool setup(uint8_t addr = 0x44);
    bool get(float* temp, float* humidity);

private:
    int addr;
    int pos;
    int count;
    float tempBuffer[SHT3X_SAMPLE_MAX];
    float humidityBuffer[SHT3X_SAMPLE_MAX];
};

#endif //__SHT3X__
