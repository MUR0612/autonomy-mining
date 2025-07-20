// C++17 AutonomyKit 初始專案架構
// 專案目標：模擬礦場與倉庫場景的自駕控制系統（FSM + Sensor + 模擬器）

#include <iostream>
#include <memory>
#include "Simulator/Simulator.hpp"

int main() {
    std::cout << "[AutonomyKit] Simulation system starting...\n";

    std::unique_ptr<Simulator> sim = std::make_unique<Simulator>();
    sim->run();

    std::cout << "[AutonomyKit] Simulation system terminated.\n";
    return 0;
}