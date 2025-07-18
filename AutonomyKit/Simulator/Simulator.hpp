//
// Created by user on 2025/7/1.
//

#ifndef AUTONOMYKIT_SIMULATOR_HPP
#define AUTONOMYKIT_SIMULATOR_HPP

#include "../FSM/FSMController.hpp"  // 加入 FSM 模組
#include "../Sensor/DistanceSensor.hpp" //加入 Sensor 模組
#include "../Map/Map.hpp"
#include "../Logger/Logger.hpp"

class Simulator {
public:
    Simulator();
    ~Simulator();

    void run();  // Starts the simulation loop

private:
    Map map;
    DistanceSensor distanceSensor;
    FSMController fsm;
    Logger logger;

    int directionX = 1; // 預設向右
    int directionY = 0; // 預設向右
};

#endif  // AUTONOMYKIT_SIMULATOR_HPP