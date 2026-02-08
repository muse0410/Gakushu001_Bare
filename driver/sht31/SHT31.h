#pragma once
#include "SensorBase_Temp.h"
#include "I2CInterface.h"

class SHT31 : public SensorBase_Temp {
private:
    I2CInterface* _i2c; // インターフェースを使う
    uint8_t _addr;

public:
    SHT31(I2CInterface* i2c, uint8_t addr = 0x44);
    SensorData read() override;
};