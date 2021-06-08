#ifndef __MHZ19__
#define __MHZ19__

#include <Arduino.h>
#include <MHZ19_uart.h>

class MHZ19 
{
public:
    MHZ19();
    ~MHZ19();

    bool setup(int rx, int tx);
    bool calibrate();
    bool get(int *co2ppm);

private:
    MHZ19_uart mhz;

};

#endif //__MHZ19__