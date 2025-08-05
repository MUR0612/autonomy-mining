//
// Created by user on 2025/7/1.
//

#include "Simulator.hpp"
#include <iostream>
#include <thread>
#include <chrono>
#include <queue>
#include <vector>
#include <cmath>

struct AStarNode {
    int x, y;
    int g, h;
    std::vector<std::pair<int, int>> path;
    bool operator<(const AStarNode& rhs) const {
        return (g + h) > (rhs.g + rhs.h); // 小頂堆
    }
};

int heuristic(int x1, int y1, int x2, int y2) {
    return std::abs(x1 - x2) + std::abs(y1 - y2); // 曼哈頓距離
}

bool astar(const std::vector<std::vector<int>>& grid,
           int startX, int startY, int goalX, int goalY,
           std::vector<std::pair<int, int>>& resultPath) {
    int w = grid[0].size();
    int h = grid.size();
    std::vector<std::vector<bool>> visited(h, std::vector<bool>(w, false));
    std::priority_queue<AStarNode> pq;
    pq.push({startX, startY, 0, heuristic(startX, startY, goalX, goalY), {{startX, startY}}});

    const int dx[4] = {1, -1, 0, 0};
    const int dy[4] = {0, 0, 1, -1};

    while (!pq.empty()) {
        AStarNode node = pq.top(); pq.pop();
        if (node.x == goalX && node.y == goalY) {
            resultPath = node.path;
            return true;
        }
        if (visited[node.y][node.x]) continue;
        visited[node.y][node.x] = true;
        for (int d = 0; d < 4; ++d) {
            int nx = node.x + dx[d];
            int ny = node.y + dy[d];
            if (nx >= 0 && nx < w && ny >= 0 && ny < h &&
                grid[ny][nx] == 0 && !visited[ny][nx]) {
                auto newPath = node.path;
                newPath.emplace_back(nx, ny);
                pq.push({nx, ny, node.g + 1, heuristic(nx, ny, goalX, goalY), newPath});
                }
        }
    }
    return false;
}

Simulator::Simulator()
    : map (7, 5), //地圖 7x5
    distanceSensor(map),  //感測器連到地圖
    logger("simulation_log.csv"),
    directionX(1), //預設向右
    directionY(0)
{
    std::cout << "[AutonomyKit] Simulator initialized." << std::endl;

    // 讓使用者輸入障礙物數量
    int obstacleCount;
    std::cout << "Please enter the number of obstacles: ";
    std::cin >> obstacleCount;

    // 逐一輸入障礙物座標
    for (int i = 0; i < obstacleCount; ++i) {
        int ox, oy;
        std::cout << "Enter obstacle #" << (i + 1) << " position (x y, range: 1-" << map.getWidth() << " 1-" << map.getHeight() << "): ";
        std::cin >> ox >> oy;

        // 這裡自動-1轉成C++座標
        ox -= 1;
        oy -= 1;

        if (ox >= 0 && ox < map.getWidth() && oy >= 0 && oy < map.getHeight()) {
            map.addObstacle(ox, oy);
        } else {
            std::cout << "Invalid position! Please enter a valid coordinate.\n";
            --i; // 重複這個回合
        }

        // 檢查範圍合法
        if (ox >= 0 && ox < map.getWidth() && oy >= 0 && oy < map.getHeight()) {
            map.addObstacle(ox, oy);
        } else {
            std::cout << "Invalid position! Please enter a valid coordinate.\n";
            --i; // 重複這個回合
        }
    }

    // 讓使用者輸入車輛起始座標
    int startX, startY;
    while (true) {
        std::cout << "Enter vehicle starting position (x y, range: 1-" << map.getWidth() << " 1-" << map.getHeight() << "): ";
        std::cin >> startX >> startY;
        startX -= 1;
        startY -= 1;
        if (startX >= 0 && startX < map.getWidth() &&
            startY >= 0 && startY < map.getHeight() &&
            !map.isObstacle(startX, startY)) {
            map.setVehiclePosition(startX, startY);
            break;
            } else {
                std::cout << "Invalid position! Please enter a valid coordinate (not on obstacle, in map bounds).\n";
            }
    }

    // 讓使用者輸入終點
    int goalX, goalY;
    while (true) {
        std::cout << "Enter goal (target) position (x y, range: 1-" << map.getWidth() << " 1-" << map.getHeight() << "): ";
        std::cin >> goalX >> goalY;
        goalX -= 1;
        goalY -= 1;
        if (goalX >= 0 && goalX < map.getWidth() &&
            goalY >= 0 && goalY < map.getHeight() &&
            !map.isObstacle(goalX, goalY) &&
            !(goalX == startX && goalY == startY)) {
            // 你可以把 goal 存成 Simulator 成員變數
            this->goalX = goalX;
            this->goalY = goalY;
            break;
            } else {
                std::cout << "Invalid position! Please enter a valid coordinate (not on obstacle or start point, in map bounds).\n";
            }
    }

    //感知器方向往右
    distanceSensor.setDirection(directionX, directionY);
}

Simulator::~Simulator() {
    std::cout << "[AutonomyKit] Simulator shutting down..." << std::endl;
}

void Simulator::run() {
    std::cout << "[AutonomyKit] Simulation system starting..." << std::endl;

    // 取得地圖二維陣列
    std::vector<std::vector<int>> grid = map.toGrid();

    // 取得起點
    auto [startX, startY] = map.getVehiclePosition();

    // 計算路徑
    std::vector<std::pair<int, int>> path;
    if (astar(grid, startX, startY, goalX, goalY, path)) {
        std::cout << "[A*] Path found! Steps: " << path.size() - 1 << std::endl;
        int stepCount = 0;
        for (auto& p : path) {
            ++stepCount;
            map.setVehiclePosition(p.first, p.second);
            std::cout << "\n[Simulator] Step " << stepCount << std::endl;
            map.print();

            logger.logStep(stepCount, "AStarPath", 0, p.first, p.second);

            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
        std::cout << "[Simulator] Vehicle reached the goal in " << path.size() - 1 << " steps!\n";
    } else {
        std::cout << "[A*] No path found!\n";
    }

    std::cout << "[AutonomyKit] Simulation system terminated." << std::endl;
}

