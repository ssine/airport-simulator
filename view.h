#ifndef VIEW_H
#define VIEW_H

#include <SOIL.h>
#include <GL/glut.h>
#include <cmath>
#include "struct.h"

// 窗口宽高
const int windowWidth = 1366;
const int windowHeight = 768;

// 材质名字的枚举变量，实现动图的时候需要改
enum texName;


// 工具
inline float sym(float a, float b);

// 驱动
void show();

void drawInit();
/* 绘图前初始化函数：
    计算必要的值
    载入材质
    设置键鼠回调
*/
void genRoute();

// 绘图
void drawObject(texName, Point&, float, float);
void drawPassenger(Passenger& p);
void drawSerpQueue();
void flush(int value);


// 从文件读取材质
void loadTexture();
void loadPassengerTex();

// 什么也不做的咸鱼函数
void display();

// 键鼠交互回调函数
void onEscPressed(unsigned char key, int x, int y);



#endif