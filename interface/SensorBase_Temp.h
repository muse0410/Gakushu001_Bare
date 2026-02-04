#ifndef SENSOR_BASE_H
#define SENSOR_BASE_H

// 共通のデータ型
struct SensorData {
    float temperature;
    float humidity;
    bool success;
};

// 抽象クラス（これ自体は実体を持たない「型」）
class SensorBase_Temp {
public:
    virtual ~SensorBase_Temp() {} // デストラクタ
    virtual SensorData read() = 0; // 「= 0」は、継承先で必ず実装せよという意味
};

#endif