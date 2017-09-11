#ifndef VIEW_H
#define VIEW_H

#include <SOIL.h>
#include <GL/glut.h>
#include <cmath>

// 窗口宽高
const int windowWidth = 720;
const int windowHeight = 480;

// 材质名字的枚举变量，实现动图的时候需要改
enum texName;

// 点，重载了默认、复制构造，norm返回两点间欧氏距离
struct Point {
    float x, y;
    Point();
    Point(float a, float b);
    Point(const Point& p);
    Point& operator = (const Point& p);
    inline static float Point::norm(const Point& a, const Point& b) {
        return std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2));
    }
};

// 测试用类
class Passenger {
public:
    Point pos;
    Point endPoint;
    bool needMove;
    Passenger(float x=0, float y=0) {pos.x = x; pos.y = y; needMove = true;}
};

// 驱动函数
void show(int argc, char *argv[]);

void drawInit();
/* 绘图前初始化函数：
    设置背景
    载入材质
*/
// 从文件读取材质
void loadTexture();

// 什么也不做的咸鱼函数
void display();

// 键鼠交互回调函数
void onEscPressed(unsigned char key, int x, int y);


// 工具函数：
void drawObject(texName, Point&, float, float);
void flush(int value);


#endif