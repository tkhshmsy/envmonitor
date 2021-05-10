#include <sht3x.h>

#include <Arduino.h>
#include <Wire.h>

SHT3X::SHT3X()
{
}

SHT3X::~SHT3X()
{
}

bool SHT3X::setup(uint8_t addr)
{
    Wire.begin();
    this->addr = int(addr);
    return true;
}

bool SHT3X::get(float* temp, float* humidity)
{
    Wire.beginTransmission(this->addr);
    Wire.write(0x2c);
    Wire.write(0x06);
    if (Wire.endTransmission() != 0) {
        Serial.println("SHT3X: get() failed to write");
        return false;
    }
    delay(500);
    unsigned int data[6];
    Wire.requestFrom(this->addr, 6);
    // cTemp msb, cTemp lsb, cTemp crc, humidity msb, humidity lsb, humidity crc
    for (int i = 0; i < 6; i++) {
        data[i] = Wire.read();
    };
    delay(50);  
    if (Wire.available() != 0) {
        Serial.println("SHT3X: get() failed to read");
        return false;
    }
    // Convert the data
    if (temp != nullptr) {
        *temp = ((((data[0] * 256.0) + data[1]) * 175) / 65535.0) - 45;
    }
    if (humidity != nullptr) {
        *humidity = ((((data[3] * 256.0) + data[4]) * 100) / 65535.0);
    }
    return true;
}
