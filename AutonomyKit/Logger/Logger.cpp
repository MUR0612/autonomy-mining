//
// Created by user on 2025/7/1.
//

#include "Logger.hpp"
#include <iostream>

Logger::Logger(const std::string& filename) {
    file.open(filename, std::ios::out);
    if (file.is_open()) {
        file << "Step,State,Distance,X,Y\n"; // CSV header
    }
}

Logger::~Logger() {
    if (file.is_open()) {
        file.close();
    }
}

void Logger::log(const std::string& message) {
    std::cout << message << std::endl;
    if (file.is_open()) {
        file << message << std::endl;
    }
}

void Logger::logStep(int step, const std::string& state, double distance, int x, int y) {
    if (file.is_open()) {
        file << step << "," << state << "," << distance << "," << x << "," << y << "\n";
    }
}
