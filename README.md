# envmonitor

M5Stackを使用した環境モニタ

## What's this ?

以下の表示を繰り返す。

- 環境センサ測定値表示
  - 気温
  - 湿度
  - 不快指数
- 簡易天気予報表示
  - 当日
  - 翌日

## Require

this project is built on platformio

### H/W

- [M5Stack Basic]( https://www.switch-science.com/catalog/3647/ )
- [BTC stand]( https://www.switch-science.com/catalog/3993/ )
- SDCard

### Resources

- API
  - [OpenWeatherMap]( https://openweathermap.org/ )
- Libs
  - [M5Stack]( https://github.com/m5stack/M5Stack )
  - [ArduinoJson]( https://github.com/bblanchon/ArduinoJson )
  - [Arduino用漢字フォントライブラリ SDカード版]( https://github.com/Tamakichi/Arduino-KanjiFont-Library-SD )
- KANJI fonts
- Weather icons

## TODO

- support [Ambient]( https://ambidata.io/ )
- support BME280
- support CO2 NDIR

## Author

tkhshmsy@gmail.com
