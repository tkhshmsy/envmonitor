#include "display.h"

#include <sdfonts.h>

Display::Display()
    : temperature(0.0),
    humidity(0.0)
{
}

Display::~Display()
{
}

bool Display::setup()
{
    M5.Lcd.fillScreen(TFT_BLACK);
    M5.Lcd.setTextSize(1);
    M5.Lcd.setTextColor(TFT_WHITE, TFT_BLACK);
    return true;
}

void Display::setTimeInfo(struct tm timeinfo)
{
    this->timeinfo = timeinfo;
}

void Display::setTemperature(float temperature)
{
    this->temperature = temperature;
}

void Display::setHumidity(float humidity)
{
    this->humidity = humidity;
}

void Display::setDiscomfortIndex()
{
    this->discomfortIndex = 46.3 + (temperature * 0.81) + (humidity * (0.99 * temperature - 14.3) * 0.01);
}

void Display::setCO2(int ppm)
{
    this->co2ppm = ppm;
}

void Display::setWeatherInfo(int index, Display::WeatherInfo weatherinfo)
{
    if (index >= sizeof(weatherInfos) ) {
        return;
    }
    weatherInfos[index] = weatherinfo;
}

void Display::clear()
{
    M5.Lcd.fillScreen(TFT_BLACK);
}

void Display::drawWString(uint16_t x, uint16_t y, char* pUTF8, uint8_t size, uint32_t fgcolor, uint32_t bgcolor)
{
    uint8_t buf[MAXFONTLEN];

    SDfonts.open();
    SDfonts.setFontSize(size);
    uint16_t length = 0;
    while ( (pUTF8 = SDfonts.getFontData(buf, pUTF8)) != 0 ) {
        int xx = x + length * size;
        int yy = y;
        uint8_t bn = SDfonts.getRowLength();
        for (uint8_t i = 0; i < SDfonts.getLength(); i += bn ) {
            for (uint8_t j = 0; j < bn; j++) {
                for (uint8_t k = 0; k < 8; k++) {
                    if (buf[i + j] & 0x80 >> k) {
                    M5.Lcd.drawPixel(xx + 8 * j + k , yy + i / bn, fgcolor);
                    } else {
                    M5.Lcd.drawPixel(xx + 8 * j + k , yy + i / bn, bgcolor);
                    }
                }
            }
        }
        ++length;
    }
    SDfonts.close();
}

String Display::NumString2WString(String src)
{
    String result;
    const char *p = src.c_str();
    for (int i = 0; i < src.length(); i++) {
        switch(*p) {
            case '0':
                result += "０";
                break;
            case '1':
                result += "１";
                break;
            case '2':
                result += "２";
                break;
            case '3':
                result += "３";
                break;
            case '4':
                result += "４";
                break;
            case '5':
                result += "５";
                break;
            case '6':
                result += "６";
                break;
            case '7':
                result += "７";
                break;
            case '8':
                result += "８";
                break;
            case '9':
                result += "９";
                break;
            case '+':
                result += "＋";
                break;
            case '-':
                result += "−";
                break;
            case '.':
                result += "．";
                break;
        }
        p++;
    }
    return result;
}

void Display::drawHeader()
{
    M5.Lcd.setTextColor(TFT_CYAN, TFT_BLACK);
    M5.Lcd.setCursor(0, 0);
    char buf[12];
    sprintf(buf, "%02d/%02d %02d:%02d", timeinfo.tm_mon + 1, timeinfo.tm_mday, timeinfo.tm_hour, timeinfo.tm_min);
    M5.Lcd.drawCentreString(buf, 160, 0, 4); // font4=ascii 26px
}

void Display::showEnvironment()
{
    clear();
    drawHeader();
    int baseline = 32;
    char buf[16];

    M5.Lcd.setTextColor(TFT_GREEN, TFT_BLACK);
    drawWString(0, baseline + 48 - 24, (char *)"気温", 24);
    drawWString(320 - 24, baseline, (char *)"℃", 24);
    sprintf(buf, "%+2.1f", temperature);
    Serial.println(buf);
    M5.Lcd.drawRightString(buf, 320 - 48, baseline, 7); //font7=digit 48px
    baseline += 48 + 8;

    M5.Lcd.setTextColor(TFT_CYAN, TFT_BLACK);
    drawWString(0, baseline + 48 - 24, (char *)"湿度", 24);
    drawWString(320 - 24, baseline, (char *)"％", 24);
    sprintf(buf, "%2.1f", humidity);
    Serial.println(buf);
    M5.Lcd.drawRightString(buf, 320 - 48, baseline, 7); //font7=digit 48px
    baseline += 48 + 8;

    M5.Lcd.setTextColor(TFT_YELLOW, TFT_BLACK);
    drawWString(0, baseline + 48 - 24, (char *)"不快指数", 24);
    sprintf(buf, "%2.1f", discomfortIndex);
    Serial.println(buf);
    M5.Lcd.drawRightString(buf, 320 - 48, baseline, 7); //font7=digit 48px

}

void Display::showCO2()
{
    clear();
    drawHeader();
    int baseline = 32;
    char buf[32];

    M5.Lcd.setTextColor(TFT_GREEN, TFT_BLACK);
    drawWString(0, baseline + 48 - 24, (char *)"ＣＯ２濃度", 24);
    baseline += 48 + 8;

    sprintf(buf, "%d", co2ppm);
    Serial.println(buf);
    M5.Lcd.drawRightString(buf, 320 - 72, baseline, 7); //font7=digit 48px
    baseline += 48 + 8;

    M5.Lcd.setTextColor(TFT_WHITE, TFT_BLACK);
    sprintf(buf, "ppm");
    M5.Lcd.drawRightString(buf, 320 - 24, baseline, 4);
}

void Display::showWeather()
{
    clear();
    drawHeader();
    int baseline = 32;
    char buf[32];

    M5.Lcd.setTextColor(TFT_GREEN, TFT_BLACK);
    drawWString(0, baseline, (char *)"本日", 24);
    drawWString(160, baseline + (100 - 24) / 2, (char*)weatherInfos[0].description.c_str(), 24);
    sprintf(buf, "/weathericon/%s.jpg", weatherInfos[0].icon.c_str());
    Serial.println(buf);
    M5.Lcd.drawJpgFile(SD, buf, 60, baseline);

    baseline += 100 + 4;
    M5.Lcd.setTextColor(TFT_GREEN, TFT_BLACK);
    drawWString(0, baseline, (char *)"明日", 24);
    drawWString(160, baseline + (100 - 24) / 2, (char*)weatherInfos[1].description.c_str(), 24);
    sprintf(buf, "/weathericon/%s.jpg", weatherInfos[1].icon.c_str());
    Serial.println(buf);
    M5.Lcd.drawJpgFile(SD, buf, 60, baseline);
}
