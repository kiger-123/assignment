#include "Environment.hpp"
#include <iostream>
#include <string>

int Environment::envCount = 0;

Environment::Environment(int count) : robots(nullptr), robotNum(count) {
    if (robotNum < 2) robotNum = 2;

    robots = new Robot[robotNum];
    for (int i = 0; i < robotNum; ++i) {
        std::string n = "R" + std::to_string(i + 1);
        robots[i] = Robot(n, i * 2, i * 2);
    }

    ++envCount;
}

Environment::Environment(const Environment& other) : robots(nullptr), robotNum(other.robotNum) {
    robots = new Robot[robotNum];
    for (int i = 0; i < robotNum; ++i) {
        robots[i] = other.robots[i];
    }
    ++envCount;
}

Environment& Environment::operator=(const Environment& other) {
    if (this != &other) {
        Robot* newRobots = new Robot[other.robotNum];
        for (int i = 0; i < other.robotNum; ++i) {
            newRobots[i] = other.robots[i];
        }

        delete[] robots;
        robots = newRobots;
        robotNum = other.robotNum;
    }
    return *this;
}

Environment::~Environment() {
    delete[] robots;
    robots = nullptr;
    --envCount;
}

void Environment::draw() const {
    std::cout << "---- Environment ----\n";
    for (int i = 0; i < robotNum; ++i) {
        std::cout << "[" << i << "] ";
        robots[i].draw();
    }
}

bool Environment::moveRobot(int index, Robot::Direction dir, int steps) {
    if (index < 0 || index >= robotNum) return false;
    robots[index].move(dir, steps);
    return true;
}

bool Environment::resetRobot(int index) {
    if (index < 0 || index >= robotNum) return false;
    robots[index].reset();
    return true;
}

void Environment::controlByKeys() {
    std::cout << "\nInput: index key steps\n";
    std::cout << "key: w(up), s(down), a(left), d(right), q(quit)\n";

    while (true) {
        int idx;
        char key;
        int steps = 1;

        std::cout << ">> ";
        std::cin >> idx >> key;
        if (!std::cin) return;
        if (key == 'q' || key == 'Q') return;

        std::cin >> steps;

        bool ok = false;
        if (key == 'w' || key == 'W') ok = moveRobot(idx, Robot::UP, steps);
        else if (key == 's' || key == 'S') ok = moveRobot(idx, Robot::DOWN, steps);
        else if (key == 'a' || key == 'A') ok = moveRobot(idx, Robot::LEFT, steps);
        else if (key == 'd' || key == 'D') ok = moveRobot(idx, Robot::RIGHT, steps);

        if (!ok) std::cout << "Invalid input\n";
        draw();
    }
}

int Environment::getRobotNum() const {
    return robotNum;
}

int Environment::getEnvironmentCount() {
    return envCount;
}