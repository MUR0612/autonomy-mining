//
// Created by user on 2025/7/1.
//

#include "FSMController.hpp"
#include <iostream>

FSMController::FSMController()
    : currentState(RobotState::IDLE) {}

void FSMController::update(bool obstacleDetected) {
    switch (currentState) {
        case RobotState::IDLE:
            transitionTo(RobotState::MOVE_FORWARD);
        break;
        case RobotState::MOVE_FORWARD:
            if (obstacleDetected)
                transitionTo(RobotState::OBSTACLE_DETECTED);
        break;
        case RobotState::OBSTACLE_DETECTED:
            transitionTo(RobotState::TURN_LEFT);
        break;
        case RobotState::TURN_LEFT:
            transitionTo(RobotState::MOVE_FORWARD);
        break;
        case RobotState::STOP:
            // 停止狀態不做變更
                break;
    }
}

std::string FSMController::getCurrentStateName() const {
    switch (currentState) {
        case RobotState::IDLE: return "IDLE";
        case RobotState::MOVE_FORWARD: return "MOVE_FORWARD";
        case RobotState::OBSTACLE_DETECTED: return "OBSTACLE_DETECTED";
        case RobotState::TURN_LEFT: return "TURN_LEFT";
        case RobotState::STOP: return "STOP";
        default: return "UNKNOWN";
    }
}

RobotState FSMController::getCurrentState() const {
    return currentState;
}

void FSMController::transitionTo(RobotState newState) {
    std::cout << "[FSM] Transitioning from " << getCurrentStateName()
              << " to ";
    currentState = newState;
    std::cout << getCurrentStateName() << std::endl;
}

