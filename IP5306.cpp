#include <Wire.h>
#include "IP5306.h"


void IP5306::begin(uint8_t sdaPin, uint8_t sclPin) {
    Wire.begin(sdaPin, sclPin);
}

uint8_t IP5306::writeBytes(uint8_t addr, uint8_t reg, uint8_t *data, uint8_t quantity) {
    Wire.beginTransmission(addr);
    Wire.write(reg);
    Wire.write(data, quantity);
    return Wire.endTransmission() == I2C_ERROR_OK;

}
uint8_t IP5306::readBytes(uint8_t addr, uint8_t reg, uint8_t *data, uint8_t quantity) {
    Wire.beginTransmission(addr);
    Wire.write(reg);
    if (Wire.endTransmission(false) != I2C_ERROR_OK) { return 0; }

    Wire.requestFrom(addr, quantity);
    uint8_t i = 0;
    while (Wire.available() && i < quantity) {
        data[i] = Wire.read();
        i++;
    }
    while (Wire.available()) {
        Wire.read(); 
    }
    return i == quantity;
}

uint8_t IP5306::setup(uint8_t initPrms /*= IP5306_DEFAULT_SETUP*/) {
    return this->writeBytes(IP5306_ADDR, IP5306_REG_SYS_CTL0, &initPrms, 1);
}

uint8_t IP5306::isChargerConnected() {
    uint8_t data;
    this->readBytes(IP5306_ADDR, IP5306_REG_READ0, &data, 1);
    return (data & (1 << 3)) ? 1 : 0;
}

uint8_t IP5306::isChargeFull() {
    uint8_t data;
    this->readBytes(IP5306_ADDR, IP5306_REG_READ1, &data, 1);
    return (data & (1 << 3)) ? 1 : 0;
}

uint8_t IP5306::getBatteryLevel() {
    uint8_t data;
    this->readBytes(IP5306_ADDR, IP5306_REG_UNKNOW, &data, 1);
    switch (data & 0xF0) {
        case 0xE0: return 25;
        case 0xC0: return 50;
        case 0x80: return 75;
        case 0x00: return 100;
        default: return 0;
    }    
}