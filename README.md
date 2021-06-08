# envmonitor

M5Stackを使用した環境モニタ

## What's this ?

以下の表示を繰り返す。

- 環境センサ計測値表示
  - 気温
  - 湿度
  - 不快指数
- CO2モニタ計測値表示
  - CO2濃度
- 簡易天気予報表示
  - 当日
  - 翌日

また計測値はAmbient.ioに送信する。

## Require

this project is built on platformio

### H/W

- [M5Stack Basic]( https://www.switch-science.com/catalog/3647/ )
- [BTC Ticker]( https://www.switch-science.com/catalog/3993/ )
- [CO2センサMH-Z19接続基板（M5Stack用）]( https://www.switch-science.com/catalog/7167/ )
- SDCard

### Resources

一部ライブラリはハードインポートしています。

- API
  - [OpenWeatherMap]( https://openweathermap.org/ )
  - [Ambient]( https://ambidata.io/ )
- Libs
  - [M5Stack]( https://github.com/m5stack/M5Stack )
  - [ArduinoJson]( https://github.com/bblanchon/ArduinoJson )
  - [Arduino用漢字フォントライブラリ SDカード版]( https://github.com/Tamakichi/Arduino-KanjiFont-Library-SD )
  - [MHZ19_uart]( https://github.com/nara256/mhz19_uart )
- KANJI fonts
- Weather icons

## Author

tkhshmsy@gmail.com
