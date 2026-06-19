#include <iostream>                 // 引入输入输出库
#include <conio.h>                   // 引入 _getch()（控制台按键读取）
#include <new>                       // 引入 placement new / operator new
#include <cstdlib>                   // 引入 system() / 可能用到的cstdlib

using namespace std;               // 使用 std 命名空间，避免 std:: 前缀

class Point {                      // 定义 Point 类（点）
public:                            // 公有访问权限
    int x;                          // x 坐标
    int y;                          // y 坐标

    Point() : x(0), y(0) {}        // 默认构造函数：x,y 初始化为 0
    Point(int x_, int y_) : x(x_), y(y_) {} // 参数构造函数：初始化坐标
    Point(const Point& other) : x(other.x), y(other.y) {} // 拷贝构造函数
    ~Point() {}                     // 析构函数（本题不需要释放资源，但按要求补上）
};

class Robot {                      // 定义 Robot 类（机器人）
private:                           // 私有访问权限
    Point pos;                      // 当前坐标
    Point start;                   // 初始坐标（用于 reset）

    static const int W = 20;       // 画布宽度（列数）
    static const int H = 10;       // 画布高度（行数）

public:                            // 公有访问权限
    Robot(const Point& p) : pos(p), start(p) {} // 构造函数：创建时位置为 p
    Robot(const Robot& other) : pos(other.pos), start(other.start) {} // 拷贝构造函数
    ~Robot() {}                     // 析构函数（按要求补上）

    void draw() const {            // 绘制机器人到控制台
        system("cls");            // 清屏（Dev-C++ 常用写法）
        for (int i = 0; i < H; i++) {          // 遍历每一行
            for (int j = 0; j < W; j++) {      // 遍历每一列
                if (i == pos.y && j == pos.x) cout << 'R'; // 在机器人位置输出 R
                else cout << '.';              // 其他位置输出 .
            }
            cout << '\n';                      // 每行结束换行
        }
        cout << "Position: (" << pos.x << ", " << pos.y << ")\n"; // 输出当前坐标
        cout << "Use Arrow Keys, R: reset, Q: quit\n";             // 输出操作提示
    }

    void move(int dx, int dy) {   // 移动函数：dx/dy 分别表示横纵移动量
        int nx = pos.x + dx;       // 计算新 x
        int ny = pos.y + dy;       // 计算新 y

        if (nx < 0) nx = 0;        // 防止越界（左边）
        if (nx > W - 1) nx = W - 1; // 防止越界（右边）
        if (ny < 0) ny = 0;        // 防止越界（上边）
        if (ny > H - 1) ny = H - 1; // 防止越界（下边）

        pos.x = nx;                // 更新 x
        pos.y = ny;                // 更新 y
    }

    Robot& operator()() {          // (5) 重载 operator()：重置机器人位置
        pos = start;              // 将当前位置恢复到初始位置
        return *this;            // 返回自身引用，支持链式调用（可选）
    }

    friend ostream& operator<<(ostream& os, const Robot& r) { // (4) 重载 operator<<：输出 Robot 位置
        os << "Robot position: (" << r.pos.x << ", " << r.pos.y << ")"; // 输出格式
        return os;                // 返回输出流引用
    }
};

int main() {                        // 主函数入口
    Point p(5, 3);                 // 创建一个初始点 p(5,3)

    void* mem = ::operator new(sizeof(Robot)); // (2) 用 operator new 分配一块原始内存（不构造对象）
    Robot* r = new (mem) Robot(p);            // placement new 在这块内存上构造 Robot 对象

    cout << *r << "\n";            // 测试 operator<< 是否可用
    cout << "Press any key to start...\n"; // 提示开始
    _getch();                      // 等待任意键

    while (true) {                // 无限循环：不断绘制并响应按键
        r->draw();                // 绘制当前机器人
        int ch = _getch();        // 读取一个键

        if (ch == 'q' || ch == 'Q') break;   // 按 q/Q 退出循环

        if (ch == 'r' || ch == 'R') {        // 按 r/R 执行 reset
            (*r)();                            // 调用 operator() 重置位置
            continue;                           // 继续下一轮循环
        }

        if (ch == 0 || ch == 224) {           // 方向键通常会先读到 0 或 224
            int code = _getch();               // 读取真正方向键代码
            if (code == 72) r->move(0, -1);        // 72 表示上
            else if (code == 80) r->move(0, 1);    // 80 表示下
            else if (code == 75) r->move(-1, 0);   // 75 表示左
            else if (code == 77) r->move(1, 0);    // 77 表示右
        }
    }

    r->~Robot();                    // 显式调用析构函数（因为你用了 placement new）
    ::operator delete(mem);        // 释放由 operator new 分配的内存
    return 0;                       // 正常结束
}


