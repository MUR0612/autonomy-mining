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

    int directionX; // 車頭方向X
    int directionY; // 車頭方向Y
    int goalX, goalY;
};

#endif  // AUTONOMYKIT_SIMULATOR_HPP