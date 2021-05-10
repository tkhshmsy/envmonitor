# envmonitor

environment monitor for M5Stack
M5Stackを使用した環境モニタ

## What's this ?

以下の表示を繰り返す。

- 環境センサの測定値表示
  - 気温
  - 湿度
- 天気予報表示

## Require

this project is built on platformio

### using H/W

- [M5Stack Basic]( https://www.switch-science.com/catalog/3647/ )
- [BTC stand]( https://www.switch-science.com/catalog/3993/ )
- SDCard
  - KANJI fonts
  - weather icons

### using API

- [OpenWeatherMap]( https://openweathermap.org/ )

### using Libraries

- [M5Stack]( https://github.com/m5stack/M5Stack )
- [ArduinoJson]( https://github.com/bblanchon/ArduinoJson )
- [Arduino用漢字フォントライブラリ SDカード版]( https://github.com/Tamakichi/Arduino-KanjiFont-Library-SD )

## TODO

- support [Ambient]( https://ambidata.io/ )
- support BME280
- support CO2 NDIR

## Author

tkhshmsy@gmail.com
