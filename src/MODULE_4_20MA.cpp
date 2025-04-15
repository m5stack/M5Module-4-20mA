/*
 *SPDX-FileCopyrightText: 2025 M5Stack Technology CO LTD
 *
 *SPDX-License-Identifier: MIT
 */

#include "MODULE_4_20MA.h"

void MODULE_4_20MA::writeBytes(uint8_t addr, uint8_t reg, uint8_t *buffer,
                               uint8_t length) {
    _wire->beginTransmission(addr);
    _wire->write(reg);
    for (int i = 0; i < length; i++) {
        _wire->write(*(buffer + i));
    }
    _wire->endTransmission();
}

bool MODULE_4_20MA::begin(TwoWire *wire, uint8_t addr, uint8_t sda, uint8_t scl,
                          uint32_t speed) {
    _wire  = wire;
    _addr  = addr;
    _sda   = sda;
    _scl   = scl;
    _speed = speed;
    _wire->begin(_sda, _scl, _speed);
    delay(10);
    _wire->beginTransmission(_addr);
    uint8_t error = _wire->endTransmission();
    if (error == 0) {
        return true;
    } else {
        return false;
    }
}

void MODULE_4_20MA::readBytes(uint8_t addr, uint8_t reg, uint8_t *buffer,
                              uint8_t length) {
    uint8_t index = 0;
    _wire->beginTransmission(addr);
    _wire->write(reg);
    _wire->endTransmission(false);
    _wire->requestFrom(addr, length);
    for (int i = 0; i < length; i++) {
        buffer[index++] = _wire->read();
    }
}

uint16_t MODULE_4_20MA::getADC12BitsValue(uint8_t channel) {
    uint8_t data[4];
    if (channel > 3) return 0;
    uint8_t reg = channel * 2 + MODULE_4_20MA_ADC_12BIT_REG;
    readBytes(_addr, reg, data, 2);
    uint32_t value = data[0] | (data[1] << 8);
    return value;
}

uint16_t MODULE_4_20MA::getCurrentValue(uint8_t channel) {
    uint8_t data[4];
    if (channel > 3) return 0;
    uint8_t reg = channel * 2 + MODULE_4_20MA_CURRENT_REG;
    readBytes(_addr, reg, data, 2);
    uint32_t value = data[0] | (data[1] << 8);
    return value;
}

void MODULE_4_20MA::setCalCurrent(uint8_t channel, uint16_t value) {
    uint8_t data[4];
    uint8_t reg = MODULE_4_20MA_CAL_REG + channel * 2;

    data[0] = (value & 0xff);
    data[1] = ((value >> 8) & 0xff);
    writeBytes(_addr, reg, data, 2);
    delay(500);
}

uint8_t MODULE_4_20MA::setI2CAddress(uint8_t addr) {
    _wire->beginTransmission(_addr);
    _wire->write(I2C_ADDRESS_REG);
    _wire->write(addr);
    _wire->endTransmission();
    _addr = addr;
    return _addr;
}

uint8_t MODULE_4_20MA::getI2CAddress(void) {
    _wire->beginTransmission(_addr);
    _wire->write(I2C_ADDRESS_REG);
    _wire->endTransmission();

    uint8_t RegValue;

    _wire->requestFrom(_addr, 1);
    RegValue = Wire.read();
    return RegValue;
}

uint8_t MODULE_4_20MA::getFirmwareVersion(void) {
    _wire->beginTransmission(_addr);
    _wire->write(FIRMWARE_VERSION_REG);
    _wire->endTransmission();

    uint8_t RegValue;

    _wire->requestFrom(_addr, 1);
    RegValue = Wire.read();
    return RegValue;
}