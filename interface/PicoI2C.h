#ifndef PICO_I2C_H
#define PICO_I2C_H

#include "hardware/i2c.h"
#include "I2CInterface.h" // 共通インターフェース

class PicoI2C : public I2CInterface {
public:
    PicoI2C(i2c_inst_t* i2c) : _i2c(i2c) {}

    int write(uint8_t addr, const uint8_t* src, size_t len, bool nostop) override {
        return i2c_write_blocking(_i2c, addr, src, len, nostop);
    }

    int read(uint8_t addr, uint8_t* dst, size_t len, bool nostop) override {
        return i2c_read_blocking(_i2c, addr, dst, len, nostop);
    }

private:
    i2c_inst_t* _i2c;
};

#endif