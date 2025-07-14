//
// Created by user on 2025/7/1.
//

#ifndef AUTONOMYKIT_DISTANCESENSOR_HPP
#define AUTONOMYKIT_DISTANCESENSOR_HPP

#include "SensorBase.hpp"
#include <random>
#include "../Map/Map.hpp"

class DistanceSensor : public SensorBase {
public:
    DistanceSensor(Map& map);
    double getReading() override;   // 回傳距離
    void setDirection(int dx, int dy); // 可選：設定感測方向
private:
    Map& map;
    int directionX = 1; // 預設朝右
    int directionY = 0;
};

#endif // AUTONOMYKIT_DISTANCESENSOR_HPP
