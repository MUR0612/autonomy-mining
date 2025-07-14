//
// Created by user on 2025/7/1.
//

#ifndef AUTONOMYKIT_SENSORBASE_HPP
#define AUTONOMYKIT_SENSORBASE_HPP

class SensorBase {
public:
    virtual ~SensorBase() = default;
    virtual double getReading() = 0; // 每次呼叫返回感測資料
};

#endif // AUTONOMYKIT_SENSORBASE_HPP

