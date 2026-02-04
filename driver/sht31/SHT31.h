#include "SensorBase_Temp.h"
#include "hardware/i2c.h"

class SHT31 : public SensorBase_Temp {
private:
    i2c_inst_t* _i2c;
    uint8_t _addr;

public:
    SHT31(i2c_inst_t* i2c, uint8_t addr = 0x44);

    // 共通ルールである read() を具体的に実装する
    SensorData read() override;
};