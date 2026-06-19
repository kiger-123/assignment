#ifndef ROBOT_HPP
#define ROBOT_HPP

#include <string>

class Robot {
public:
    enum Direction { UP, DOWN, LEFT, RIGHT };

private:
    int x;
    int y;
    int initX;
    int initY;
    std::string name;
    static int robotCount;

public:
    Robot(std::string n = "Robot", int startX = 0, int startY = 0);
    Robot(const Robot& other);
    Robot& operator=(const Robot& other);
    ~Robot();

    void setPosition(int newX, int newY);
    void reset();
    void move(Direction dir, int steps = 1);

    void draw() const;
    int getX() const;
    int getY() const;
    std::string getName() const;

    static int getRobotCount();
};

#endif