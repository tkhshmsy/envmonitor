#include <mhz19.h>

MHZ19::MHZ19()
{
}

MHZ19::~MHZ19()
{
}

bool MHZ19::setup(int rx, int tx)
{
    mhz.begin(rx, tx);
    mhz.setAutoCalibration(false);
    return true;
}

bool MHZ19::calibrate()
{
    mhz.calibrateZero();
    return true;
}

bool MHZ19::get(int *co2ppm)
{
    if (co2ppm == nullptr) {
        return false;
    }
    *co2ppm = mhz.getCO2PPM();
    return true;
}
