#ifndef __MODULE_4_20MA_H
#define __MODULE_4_20MA_H

#include "Arduino.h"
#include "Wire.h"

#define MODULE_4_20MA_ADDR          0x55
#define MODULE_4_20MA_ADC_12BIT_REG 0x00
#define MODULE_4_20MA_ADC_8BIT_REG  0x10
#define MODULE_4_20MA_CURRENT_REG   0x20
#define MODULE_4_20MA_CAL_REG       0x30
#define FIRMWARE_VERSION_REG        0xFE
#define I2C_ADDRESS_REG             0xFF

class MODULE_4_20MA {
   private:
    uint8_t _addr;
    TwoWire* _wire;
    uint8_t _scl;
    uint8_t _sda;
    uint8_t _speed;
    void writeBytes(uint8_t addr, uint8_t reg, uint8_t* buffer, uint8_t length);
    void readBytes(uint8_t addr, uint8_t reg, uint8_t* buffer, uint8_t length);

   public:
    bool begin(TwoWire* wire = &Wire, uint8_t addr = MODULE_4_20MA_ADDR,
               uint8_t sda = 21, uint8_t scl = 22, uint32_t speed = 100000L);
    uint8_t getFirmwareVersion(void);
    uint16_t getADC12BitsValue(uint8_t channel);
    uint8_t getADC8BitsValue(uint8_t channel);
    uint16_t getCurrentValue(uint8_t channel);
    void setCalCurrent(uint8_t index, uint16_t value);
    uint8_t setI2CAddress(uint8_t addr);
    uint8_t getI2CAddress(void);
};

#endif
