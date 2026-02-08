#pragma once
#include <stdint.h>
#include <stddef.h>

class I2CInterface {
public:
    virtual ~I2CInterface() {}
    // Pico SDKの関数に近い形で定義
    virtual int write(uint8_t addr, const uint8_t* src, size_t len, bool nostop) = 0;
    virtual int read(uint8_t addr, uint8_t* dst, size_t len, bool nostop) = 0;
};