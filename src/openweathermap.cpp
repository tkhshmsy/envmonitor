#include <openweathermap.h>
#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

#include "env.h"

#define OPENWEATHERMAP_BASEURL "https://api.openweathermap.org/data/2.5"

OpenWeatherMap::OpenWeatherMap()
: json(32768)
{
}

OpenWeatherMap::~OpenWeatherMap()
{
}

bool OpenWeatherMap::get(String &url)
{
    String dst(url);
    dst += "&units=metric";
    dst += "&lang=ja";
    dst += "&appid=";
    dst += OPENWEATHERMAP_APIKEY;
    http.begin(dst);
    Serial.println("OpenWeatherMap: " + url);
    int httpcode = http.GET();
    Serial.println(httpcode);
    if (httpcode != 200) {
        Serial.println("OpenWeatherMap: get() failed");
        Serial.println(http.getString());
        return false;
    }

    DeserializationError err = deserializeJson(json, http.getString());
    if (err) {
        Serial.println("OpenWeatherMap: get() deserialization failed");
        return false;
    }

    if (json.overflowed() == true) {
        Serial.println("OpenWeatherMap: get() overflowed");
        Serial.println(http.getString().length());
        return false;
    }
    return true;
}

bool OpenWeatherMap::setup()
{
    return true;
}

bool OpenWeatherMap::onecall(const String &query)
{
    String url(OPENWEATHERMAP_BASEURL);
    url += "/onecall?";
    url += query;
    if (get(url) == false) {
        Serial.println("OpenWeatherMap: onecall failed");
        return false;
    }
    return true;
}

bool OpenWeatherMap::forecast(const String &query)
{
    String url(OPENWEATHERMAP_BASEURL);
    url += "/forecast?";
    url += query;
    if (get(url) == false) {
        Serial.println("OpenWeatherMap: forecast failed");
        return false;
    }
    return true;
}
