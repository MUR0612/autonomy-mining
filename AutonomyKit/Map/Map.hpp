//
// Created by user on 2025/7/1.
//

#ifndef AUTONOMYKIT_MAP_HPP
#define AUTONOMYKIT_MAP_HPP

#include <vector>
#include <utility>

class Map {
public:
    Map(int width, int height);

    void addObstacle(int x, int y);
    bool isObstacle(int x, int y) const;

    void setVehiclePosition(int x, int y);
    std::pair<int, int> getVehiclePosition() const;

    int getWidth() const;
    int getHeight() const;

    void print() const;

    // 根據座標回傳距離前方最近障礙物的距離
    double getDistanceToObstacle(int x, int y, int dx, int dy) const;

    // 加入 toGrid() 函式
    std::vector<std::vector<int>> toGrid() const;

private:
    int width, height;
    std::vector<std::vector<int>> grid;
    std::pair<int, int> vehiclePosition; // (x, y)
};

#endif // AUTONOMYKIT_MAP_HPP

