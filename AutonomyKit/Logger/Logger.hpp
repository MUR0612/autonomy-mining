//
// Created by user on 2025/7/1.
//

#ifndef AUTONOMYKIT_LOGGER_HPP
#define AUTONOMYKIT_LOGGER_HPP

#include <string>
#include <fstream>

class Logger {
public:
    Logger(const std::string& filename);
    ~Logger();

    void log(const std::string& message);
    void logStep(int step, const std::string& state, double distance, int x, int y);

private:
    std::ofstream file;
};

#endif // AUTONOMYKIT_LOGGER_HPP

