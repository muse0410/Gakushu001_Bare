#include "SHT31.h"

// コンストラクタ（初期設定）
SHT31::SHT31(i2c_inst_t* i2c, uint8_t addr) : _i2c(i2c), _addr(addr) {
    // 必要ならここでI2Cの初期化チェックなどを行う
}

// SensorBase_Tempで約束した read() メソッドの実装
SensorData SHT31::read() {
    SensorData data = {0.0f, 0.0f, false};
    uint8_t command[2] = {0x24, 0x00};
    uint8_t buffer[6];

    // _i2c や _addr はクラスのメンバ変数を使用する
    if (i2c_write_blocking(_i2c, _addr, command, 2, false) < 0) return data;
    
    sleep_ms(20);

    if (i2c_read_blocking(_i2c, _addr, buffer, 6, false) < 0) return data;

    // 計算処理（中身は前と同じ）
    uint16_t rawTemp = (buffer[0] << 8) | buffer[1];
    data.temperature = -45.0f + 175.0f * (float)rawTemp / 65535.0f;

    uint16_t rawHum = (buffer[3] << 8) | buffer[4];
    data.humidity = 100.0f * (float)rawHum / 65535.0f;

    data.success = true;
    return data;
}