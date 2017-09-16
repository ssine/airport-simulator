#ifndef VIEW_H
#define VIEW_H

#include <SOIL.h>
#include <GL/glut.h>
#include <cmath>
#include <vector>
#include "struct.h"
#include "passenger.h"
#include "globalvar.h"

// 窗口宽高
extern const int windowWidth;
extern const int windowHeight;
extern int curWindowWidth;
extern int curWindowHeight;
extern bool aniWindow;


extern int texId[];

// 乘客路径点
extern std::vector<Point> route;

// 工具
inline float sym(float a, float b);
int getPassengerTexId();

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
void drawString(const char* str);
void drawVars();
void drawButton();
void initButton();
void drawObject(texName, Point&, float, float);
void drawSerpQueue();
void drawCheckPoint();
void drawRestAreaNum();
void flush(int value);

// 从文件读取材质
void loadTexture();
void loadPassengerTex();

// 什么也不做的咸鱼函数
void display();
void changeSize(int w, int h);

// 键鼠交互回调函数
void onEscPressed(unsigned char key, int x, int y);
void mouseMotion(int x, int y);
void mouseClick(int btn, int state, int x, int y);


#endif