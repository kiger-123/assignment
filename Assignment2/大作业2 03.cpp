#include <iostream>
#include "Robot.hpp"
#include "Environment.hpp"

int main() {
    std::cout << "=== Robot Test ===\n";
    Robot r1("A", 1, 1);
    r1.draw();
    r1.move(Robot::RIGHT, 3);
    r1.move(Robot::UP, 2);
    r1.draw();
    r1.reset();
    r1.draw();

    const Robot c1("ConstRobot", 5, 5);
    c1.draw();
    std::cout << "c1 x=" << c1.getX() << ", y=" << c1.getY() << "\n";
    std::cout << "Robot count: " << Robot::getRobotCount() << "\n";

    std::cout << "\n=== Environment Test ===\n";
    Environment env(3);
    env.draw();
    env.moveRobot(0, Robot::UP, 1);
    env.moveRobot(1, Robot::LEFT, 2);
    env.resetRobot(1);
    env.draw();
    std::cout << "Environment count: " << Environment::getEnvironmentCount() << "\n";

    // 录视频时可以打开交互控制
    // env.controlByKeys();

    return 0;
}