#include "SHT31.h"
#ifdef PICO_BOARD
#include "pico/stdlib.h"  // Picoでビルドするときだけ読み込む
#endif

// コンストラクタ
SHT31::SHT31(I2CInterface* i2c, uint8_t addr) : _i2c(i2c), _addr(addr) {}

SensorData SHT31::read() {
    SensorData data = {0.0f, 0.0f, false};
    uint8_t command[2] = {0x24, 0x00};
    uint8_t buffer[6];

    // Pico SDKの関数ではなく、インターフェースのメソッドを呼ぶ
    // Pico SDKのハードウェア操作用関数の戻り値が0以下なら失敗である
    if (_i2c->write(_addr, command, 2, false) < 0) return data;
    
    // ※注意: テスト環境（PC）では sleep_ms は何もしないダミー関数をリンクするか
    // #ifndef PICO_BOARD などで囲う必要があります
#ifdef PICO_BOARD
    sleep_ms(20);
#endif

    // Pico SDKのハードウェア操作用関数の戻り値が0以下なら失敗である
    if (_i2c->read(_addr, buffer, 6, false) < 0) return data;

    // 計算処理（ここはPCでも実機でも共通！）
    uint16_t rawTemp = (buffer[0] << 8) | buffer[1];
    data.temperature = -45.0f + 175.0f * (float)rawTemp / 65535.0f;

    // 温度異常フラグ
    if(data.temperature > 30.0f)  data.is_high_temp_warning = true;

    uint16_t rawHum = (buffer[3] << 8) | buffer[4];
    data.humidity = 100.0f * (float)rawHum / 65535.0f;

    data.success = true;
    return data;
}