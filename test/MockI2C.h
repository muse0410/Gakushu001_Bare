#include <gmock/gmock.h>
#include "I2CInterface.h"

class MockI2C : public I2CInterface {
public:
    // MOCK_METHOD(戻り値, 関数名, (引数), (修飾子))
    MOCK_METHOD(int, write, (uint8_t addr, const uint8_t* src, size_t len, bool nostop), (override));
    MOCK_METHOD(int, read, (uint8_t addr, uint8_t* dst, size_t len, bool nostop), (override));
};