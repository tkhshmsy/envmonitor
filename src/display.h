#ifndef __DISPLAY__
#define __DISPLAY__

#include <Arduino.h>
#include <time.h>
#include <M5Stack.h>

class Display
{
public:
    Display();
    ~Display();
    bool setup();

    typedef struct _WeatherInfo {
        uint32_t dt;
        String description;
        String icon;
    } WeatherInfo;

    void setTimeInfo(struct tm timeinfo);
    void setTemperature(float temperature);
    void setHumidity(float humidity);
    void setDiscomfortIndex();
    void setCO2(int ppm);
    void setWeatherInfo(int index, Display::WeatherInfo weatherinfo);

    void showEnvironment();
    void showCO2();
    void showWeather();

private:
    void drawWString(uint16_t x, uint16_t y, char* pUTF8, uint8_t size,
                    uint32_t fgcolor = TFT_WHITE,
                    uint32_t bgcolor = TFT_BLACK);
    String NumString2WString(String src);
    void clear();
    void drawHeader();

    struct tm timeinfo;
    float temperature;
    float humidity;
    float discomfortIndex;
    int co2ppm;
    WeatherInfo weatherInfos[2];

};

#endif //__DISPLAY__
