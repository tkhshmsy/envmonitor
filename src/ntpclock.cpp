#include <ntpclock.h>
#include <Arduino.h>

static const char* ntpServer = "ntp.nict.jp";
static const long offsetJST = 9 * 3600;

NTPClock::NTPClock()
{
}

NTPClock::~NTPClock()
{
}

bool NTPClock::setup()
{
    return sync();
}

bool NTPClock::sync()
{
    configTime(offsetJST, 0, ntpServer);
    return true;
}

bool NTPClock::getTime(struct tm *timeinfo)
{
    if (timeinfo == nullptr) {
        return false;
    }
    if (!getLocalTime(timeinfo)) {
        Serial.println("NTPClock: getTime failed.");
        return false;
    }
    return true;
}
