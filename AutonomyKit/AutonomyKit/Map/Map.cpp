//
// Created by user on 2025/7/1.
//

#include "Map.hpp"
#include <iostream>
#include <iomanip>

Map::Map(int width_, int height_)
    : width(width_), height(height_), grid(height_, std::vector<int>(width_, 0)), vehiclePosition({0, 0}) {}

void Map::addObstacle(int x, int y) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        grid[y][x] = 1;
    }
}

bool Map::isObstacle(int x, int y) const {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        return grid[y][x] == 1;
    }
    return false;
}

void Map::setVehiclePosition(int x, int y) {
    vehiclePosition = {x, y};
}

std::pair<int, int> Map::getVehiclePosition() const {
    return vehiclePosition;
}

int Map::getWidth() const { return width; }
int Map::getHeight() const { return height; }

void Map::print() const {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (vehiclePosition.first == x && vehiclePosition.second == y)
                std::cout << "A "; // Autonomous Vehicle
            else if (grid[y][x] == 1)
                std::cout << "X ";
            else
                std::cout << ". ";
        }
        std::cout << "\n";
    }
}

// dx, dy: 前進方向, 回傳從(x, y)出發到障礙物距離，無障礙回傳很大值
double Map::getDistanceToObstacle(int x, int y, int dx, int dy) const {
    int steps = 0;
    while (true) {
        x += dx;
        y += dy;
        if (x < 0 || x >= width || y < 0 || y >= height)
            break;
        ++steps;
        if (isObstacle(x, y))
            return steps;
    }
    return 1000.0; // 表示前方很遠都沒障礙
}

