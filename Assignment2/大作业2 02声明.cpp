#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include "Robot.hpp"

class Environment {
private:
    Robot* robots;
    int robotNum;
    static int envCount;

public:
    Environment(int count = 2);
    Environment(const Environment& other);
    Environment& operator=(const Environment& other);
    ~Environment();

    void draw() const;
    bool moveRobot(int index, Robot::Direction dir, int steps);
    bool resetRobot(int index);
    void controlByKeys();

    int getRobotNum() const;
    static int getEnvironmentCount();
};

#endif