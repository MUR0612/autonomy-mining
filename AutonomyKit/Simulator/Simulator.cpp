//
// Created by user on 2025/7/1.
//

#include "Simulator.hpp"
#include <iostream>
#include <thread>
#include <chrono>

Simulator::Simulator()
    : map (7, 5), //地圖 7x5
    distanceSensor(map),  //感測器連到地圖
    logger("simulation_log.csv")
{
    std::cout << "[AutonomyKit] Simulator initialized." << std::endl;

    //設定障礙物
    map.addObstacle(3, 2);
    map.addObstacle(6, 1);
    //設定初始位置
    map.setVehiclePosition(0,2);
    //感知器方向往右
    distanceSensor.setDirection(1, 0);
}

Simulator::~Simulator() {
    std::cout << "[AutonomyKit] Simulator shutting down..." << std::endl;
}

void Simulator::run() {
    std::cout << "[AutonomyKit] Simulation system starting..." << std::endl;

    // Main simulation loop (placeholder)
    for (int i = 0; i < 7; ++i) {
        std::cout << "\n[Simulator] Step " << i + 1 << std::endl;
        map.print();

        double distance = distanceSensor.getReading();
        std::cout << "[Sensor] DistanceSensor reading: " << distance << " units\n";

        // 設定 1 為避障門檻
        bool obstacleDetected = (distance == 1);

        // 更新狀態
        fsm.update(obstacleDetected);

        // ---- 加這段 ----
        if (fsm.getCurrentState() == RobotState::TURN_LEFT) {
            directionX = 0;
            directionY = -1;
            distanceSensor.setDirection(directionX, directionY);
        }
        // ----------------

        // 印出目前狀態
        std::cout << "[Simulator] Current state: " << fsm.getCurrentStateName() << std::endl;

        // 模擬移動 (只要不是obstacle 或停止就往右走)
        auto [x, y] = map.getVehiclePosition();
        int newX = x + directionX;
        int newY = y + directionY;
        if (fsm.getCurrentState() == RobotState::MOVE_FORWARD &&
            newX >= 0 && newX < map.getWidth() &&
            newY >= 0 && newY < map.getHeight() &&
            !map.isObstacle(newX, newY)) {
            map.setVehiclePosition(newX, newY);
        }

        // **這裡記錄 log**（更新完狀態和座標之後！）
        auto [logX, logY] = map.getVehiclePosition(); // 若移動後要記錄新位置
        logger.logStep(i + 1, fsm.getCurrentStateName(), distance, logX, logY);

        // 模擬時間延遲
        std::this_thread::sleep_for(std::chrono::milliseconds(800));
    }

    std::cout << "[AutonomyKit] Simulation system terminated." << std::endl;
}

