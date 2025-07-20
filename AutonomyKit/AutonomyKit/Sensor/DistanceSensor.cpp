//
// Created by user on 2025/7/1.
//

#include "DistanceSensor.hpp"
#include <chrono>
#include "DistanceSensor.hpp"

DistanceSensor::DistanceSensor(Map& mapRef) : map(mapRef) {}

void DistanceSensor::setDirection(int dx, int dy) {
    directionX = dx;
    directionY = dy;
}

double DistanceSensor::getReading() {
    auto [x, y] = map.getVehiclePosition();
    return map.getDistanceToObstacle(x, y, directionX, directionY);
}

