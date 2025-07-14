//
// Created by user on 2025/7/1.
//

#ifndef AUTONOMYKIT_FSMCONTROLLER_HPP
#define AUTONOMYKIT_FSMCONTROLLER_HPP

#include <string>

enum class RobotState {
    IDLE,
    MOVE_FORWARD,
    OBSTACLE_DETECTED,
    TURN_LEFT,
    STOP
};

class FSMController {
public:
    FSMController();

    void update(bool obstacleDetected);    // 更新狀態
    std::string getCurrentStateName() const; // 取得目前狀態名稱
    RobotState getCurrentState() const;    // 可用於邏輯控制

private:
    RobotState currentState;
    void transitionTo(RobotState newState);
};

#endif // AUTONOMYKIT_FSMCONTROLLER_HPP

