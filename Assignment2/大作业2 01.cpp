#include "Robot.hpp"
#include <iostream>

int Robot::robotCount = 0;

Robot::Robot(std::string n, int startX, int startY)
    : x(startX), y(startY), initX(startX), initY(startY), name(n) {
    ++robotCount;
}

Robot::Robot(const Robot& other)
    : x(other.x), y(other.y), initX(other.initX), initY(other.initY), name(other.name) {
    ++robotCount;
}

Robot& Robot::operator=(const Robot& other) {
    if (this != &other) {
        x = other.x;
        y = other.y;
        initX = other.initX;
        initY = other.initY;
        name = other.name;
    }
    return *this;
}

Robot::~Robot() {
    --robotCount;
}

void Robot::setPosition(int newX, int newY) {
    this->x = newX;
    this->y = newY;
}

void Robot::reset() {
    x = initX;
    y = initY;
}

void Robot::move(Direction dir, int steps) {
    if (steps < 0) steps = -steps;

    switch (dir) {
    case UP:    y += steps; break;
    case DOWN:  y -= steps; break;
    case LEFT:  x -= steps; break;
    case RIGHT: x += steps; break;
    }
}

void Robot::draw() const {
    std::cout << name << " at (" << x << ", " << y << ")\n";
}

int Robot::getX() const { return x; }
int Robot::getY() const { return y; }
std::string Robot::getName() const { return name; }
int Robot::getRobotCount() { return robotCount; }