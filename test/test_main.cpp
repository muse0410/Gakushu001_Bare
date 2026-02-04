#include <gtest/gtest.h>
#include "SensorBase_Temp.h"

// テスト用のダミー
class DummySensor : public SensorBase_Temp {
public:
    SensorData read() override {
        return {25.0f, 50.0f, true};
    }
};

TEST(BasicTest, SensorReadCheck) {
    DummySensor s;
    auto data = s.read();
    EXPECT_FLOAT_EQ(data.temperature, 25.0f);
    EXPECT_TRUE(data.success);
}