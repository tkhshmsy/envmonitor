#include <Arduino.h>

#include <M5Stack.h>
#include <WiFi.h>
#include <time.h>
#include <ArduinoJson.h>

#include "env.h"
#include "ntpclock.h"
#include "openweathermap.h"
#include "sht3x.h"
#include "mhz19.h"
#include "display.h"

NTPClock ntp;
struct tm timeinfo;

OpenWeatherMap weather;

SHT3X sht3x;
float temp;
float humidity;

MHZ19 mhz19;
int co2ppm;

Display display;

void setup() {
    Serial.begin(115200);
    M5.begin();

    Serial.printf("Connecting to %s ", WIFI_SSID);
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("Connected");

    display.setup();
    ntp.setup();
    weather.setup();
    sht3x.setup();
    mhz19.setup(16, 17);
}

void loop() {
    static int seconds = 0;

    while (WiFi.status() != WL_CONNECTED) {
        WiFi.disconnect();
        Serial.print("re-connect WiFi.");
        WiFi.reconnect();
        while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            Serial.print(".");
        }
    }

    if (ntp.getTime(&timeinfo) == true) {
        display.setTimeInfo(timeinfo);
    }
    if (sht3x.get(&temp, &humidity) == true) {
        display.setTemperature(temp);
        display.setHumidity(humidity);
        display.setDiscomfortIndex();
    }
    if (mhz19.get(&co2ppm) == true){
        display.setCO2(co2ppm);
    }

    if (seconds % 1800 == 0) {
        ntp.sync();

        if (weather.onecall("lat=35.6996&lon=139.6217&exclude=minutely,hourly,alerts") == true) {
            {
                JsonObject current = weather.json["current"];
                uint32_t dt = current["dt"];
                JsonObject currentWeather0 = current["weather"][0];
                const char *desc = currentWeather0["description"];
                const char *icon = currentWeather0["icon"];
                Display::WeatherInfo weatherbuf;
                weatherbuf.dt = dt;
                weatherbuf.description = String(desc);
                weatherbuf.icon = String(icon);
                display.setWeatherInfo(0, weatherbuf);
            }
            {
                JsonArray daily = weather.json["daily"];
                JsonObject daily1 = daily[1];
                JsonObject daily1Weather0 = daily1["weather"][0];
                uint32_t dt = daily1Weather0["dt"];
                const char *desc = daily1Weather0["description"];
                const char *icon = daily1Weather0["icon"];
                Display::WeatherInfo weatherbuf;
                weatherbuf.dt = dt;
                weatherbuf.description = String(desc);
                weatherbuf.icon = String(icon);
                display.setWeatherInfo(1, weatherbuf);
            }
        }
    }

    if (seconds % 15 == 0) {
        static int flip = 0;
        if ( flip % 3 == 0 ) {
            display.showEnvironment();
        }
        if ( flip % 3 == 1 ) {
            display.showCO2();
        }
        if ( flip % 3 == 2 ) {
            display.showWeather();
        }
        flip++;
    }

    sleep(1);
    seconds++;
}