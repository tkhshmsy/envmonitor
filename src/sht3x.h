#ifndef __SHT3X__
#define __SHT3X__

#include <Arduino.h>

class SHT3X
{
public:
    SHT3X();
    ~SHT3X();

    bool setup(uint8_t addr = 0x44);
    bool get(float* temp, float* humidity);

private:
    int addr;
};

#endif //__SHT3X__
