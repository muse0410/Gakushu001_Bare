#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "SHT31.h"
#include "MockI2C.h"

using ::testing::_;          // 「どんな値でもいい」というワイルドカード
using ::testing::Return;     // 戻り値を指定
using ::testing::DoAll;      // 複数のアクションを実行
using ::testing::SetArrayArgument; // 引数の配列に値を書き込む

TEST(SHT31Test, ReadTemperatureCorrect) {
    MockI2C mock_i2c;
    SHT31 sensor(&mock_i2c);

    // 偽物であるMockのふるまいを設定。
    // 1. writeが呼ばれたら「成功(0以上)」を返すように設定
    EXPECT_CALL(mock_i2c, write(0x44/*I2Cアドレス*/, _, 2, false))
        .WillOnce(Return(2));

    // 2. readが呼ばれたら、特定の「生データ」をバッファに書き込むように設定
    // 例: 25度付近になるような生データ {0x65, 0x43, ...}
    uint8_t fake_sensor_data[] = {0x65, 0x43, 0x00, 0x8A, 0x92, 0x00};
    EXPECT_CALL(mock_i2c, read(0x44, _, 6, false))
        .WillOnce(DoAll(
            SetArrayArgument<1>(fake_sensor_data, fake_sensor_data + 6),
            Return(6)
        ));

    // 実行
    auto result = sensor.read();

    // 検証：計算結果が期待通りか？
    EXPECT_TRUE(result.success);
    // -45 + 175 * (0x6543 / 65535.0) ≒ 24.16度
    EXPECT_NEAR(result.temperature, 24.22f, 0.01f); 
}
TEST(SHT31Test, DetectHighTemperatureWarning) {
    MockI2C mock_i2c;
    SHT31 sensor(&mock_i2c, 0x44);

    // 30.1度になる生データを計算して設定
    // 計算式: Raw = (Temp + 45) * 65535 / 175
    // (30.1 + 45) * 65535 / 175 ≒ 28131 (0x6DDD)
    uint8_t high_temp_data[] = {0x6D, 0xDD, 0x00, 0x00, 0x00, 0x00};

    EXPECT_CALL(mock_i2c, write(_, _, _, _)).WillOnce(Return(2));
    EXPECT_CALL(mock_i2c, read(_, _, _, _))
        .WillOnce(DoAll(SetArrayArgument<1>(high_temp_data, high_temp_data + 6), Return(6)));

    auto result = sensor.read();

    EXPECT_TRUE(result.is_high_temp_warning); // ★ここで「警告フラグが立っていること」を期待する
}
#if 0
TEST(BasicTest, SensorReadCheck) {
    DummySensor s;
    auto data = s.read();
    EXPECT_FLOAT_EQ(data.temperature, 25.0f);
    EXPECT_TRUE(data.success);
}
#endif