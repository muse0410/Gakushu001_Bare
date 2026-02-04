#include <gtest/gtest.h>
#include "SensorBase.h"

// テスト用の「身代わり」クラス
class MockSensor : public SensorBase {
public:
    SensorData read() override {
        return {25.5f, 60.0f, true}; // 常に25.5度を返す
    }
};

TEST(SensorTest, DisplayFormat) {
    MockSensor mock;
    SensorData data = mock.read();
    
    char buffer[20];
    sprintf(buffer, "Temp: %.1f C", data.temperature);
    
    // 期待通りかチェック
    EXPECT_STREQ(buffer, "Temp: 25.5 C");
}