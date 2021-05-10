#ifndef __OPENWEATHERMAP__
#define __OPENWEATHERMAP__

#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

class OpenWeatherMap
{
public:
    OpenWeatherMap();
    ~OpenWeatherMap();

    bool setup();
    bool onecall(const String &query);
    bool forecast(const String &query);
    DynamicJsonDocument json;

private:
    bool get(String &url);
    HTTPClient http;
};

#endif //__OPENWEATHERMAP__
