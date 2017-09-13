#include "stdafx.h"
#include "view.h"
#include "struct.h"
#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <string>

#include "glyph.cpp"
#include "passenger.h"

using std::cout;
using std::endl;

// 窗口宽高
const int windowWidth = 1366;
const int windowHeight = 768;
int curWindowWidth = 1366;
int curWindowHeight = 768;

// 窗口名称
const char* windowTitle = "测试样例";

// Texutre材质管理
enum texName { _passenger, _checkPoint, _serpQueueLeft, _serpQueueRight, _serpQueueDownL, _serpQueueDownU, _restArea };
int texId[100];

std::vector<Point> route;
int passengerPerLine = 20, passengerPerSkew = 2; // 每排&每斜线人数
// passenger纹理总数
int passengerTexNum = 5;


// 控制FPS
int FPS = 30;
int timeInterval;


// 绘图各项参数
float alp = 1.5, alph = 1.2; // 蛇形队列 单位宽度 & 高度修正量
float lmd;

// 蛇形队列的各项数值……请无视
float SQX = -1.0, SQY = -1.0;
int sqdw = 1289, sqdh = 256, sqlrw = 1243, sqlrh = 165;
int dltx = 135, dltx_ = 87, dlty = 167, dlty_ = 76;
float SQDW, SQDH, SQLRW, SQLRH;
float SQdX, SQdY, SQdX_, SQdY_;



void show() {
	int initint = 1;
	char* s = "main";
	char* initchar[] = {s};
    //glut设定
    glutInitWindowPosition(50, 10);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInit(&initint, initchar);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutCreateWindow(windowTitle);
    glutReshapeFunc(changeSize);
    
    //初始化
    drawInit();
    
    //初始绘图函数
    glutDisplayFunc(display);
    flush(1);
    
    //进入主循环
    glutMainLoop();
}

void drawInit() {
    // 必要的数值计算
    lmd = alp / sqdw;
    cout << lmd << endl;
    SQDW=lmd*sqdw, SQDH=lmd*sqdh*alph, SQLRW=lmd*sqlrw, SQLRH=lmd*sqlrh*alph;
    SQdX=lmd*dltx, SQdY=lmd*dlty*alph, SQdX_=lmd*dltx_, SQdY_=lmd*dlty_*alph;

    // 读取材质
    loadTexture();

    // 生成乘客路径点
    genRoute();


    srand(20);

    // 设定空白色
    glClearColor(0.796875, 0.59765625, 1.0, 1.0);

    // 测试回调函数
    glutKeyboardFunc(onEscPressed);
    // 计算Timer时间
    timeInterval = 1000 / FPS;
}


// 每一帧的绘图函数
void flush(int value) {
    glutTimerFunc(timeInterval, flush, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    drawSerpQueue();

    Passenger p(10, 10);
    p.move();
    //cout << "moved " << p.pos.x << " " << p.pos.y << endl;
    p.draw();
    //cout << "drawn " << p.width << " " << p.height << endl;

    // 移动队列中所有乘客并绘制

    glutSwapBuffers();
}


// 绘制蛇形队列
void drawSerpQueue() {
    drawObject(_serpQueueLeft, Point(SQX+SQdX+2*SQdX_,SQY+SQdY+2*SQdY_), SQLRW, SQLRH);
    int i = route.size()-1;
    for(int j = 0; j < passengerPerLine + passengerPerSkew; j++, i--) 
        drawObject(_checkPoint, route[i], 0.07, 0.25);
    drawObject(_serpQueueRight, Point(SQX+SQdX+SQdX_,SQY+SQdY+SQdY_), SQLRW, SQLRH);
    for(int j = 0; j < passengerPerLine + passengerPerSkew; j++, i--) 
        drawObject(_checkPoint, route[i], 0.07, 0.25);
    drawObject(_serpQueueLeft, Point(SQX+SQdX,SQY+SQdY), SQLRW, SQLRH);
    for(int j = 0; j < passengerPerLine + passengerPerSkew && i >= 0; j++, i--) 
        drawObject(_checkPoint, route[i], 0.07, 0.25);
    drawObject(_serpQueueDownU, Point(SQX,SQY), SQDW, SQDH);
    while(i >= 0) {
        drawObject(_checkPoint, route[i], 0.07, 0.25);
        i--;
    }
    drawObject(_serpQueueDownL, Point(SQX,SQY), SQDW, SQDH);
}


Point genSkew(Point base) {
    Point step = Point(90/(passengerPerSkew+1)*lmd, 93/(passengerPerSkew+1)*lmd*alph);
    for(int i = 1; i <= passengerPerSkew; i++) route.push_back(base + step*i);
    return Point(base + step*(passengerPerSkew+1));
}

void genRoute() {
    Point base(SQX + 88*lmd, SQY + 66*lmd);
    float step = 1144*1.0/(passengerPerLine+1)*lmd;
    cout << lmd;
    for(int i = 0; i < passengerPerLine; i++) route.push_back(Point(base.x+step/2+i*step, base.y));
    base = genSkew(Point(base.x+(passengerPerLine-1)*step+step/2, base.y));
    step = -step;
    for(int i = 0; i < passengerPerLine; i++) route.push_back(Point(base.x+step/2+i*step, base.y));
    base = genSkew(Point(base.x+(passengerPerLine-1)*step+step/2, base.y));
    step = -step;
    for(int i = 0; i < passengerPerLine; i++) route.push_back(Point(base.x+step/2+i*step, base.y));
    base = genSkew(Point(base.x+(passengerPerLine-1)*step+step/2, base.y));
    step = -step;
    for(int i = 0; i < passengerPerLine; i++) route.push_back(Point(base.x+step/2+i*step, base.y));
}



void drawObject(texName name, Point& pos, float width=0.0, float height=0.0) {
/* 已封装好，传入名字画出对应对象，参数1名字 2位置 34宽高(无则使用预设) */

    glEnable(GL_TEXTURE_2D);//图像有效化
    glBindTexture( GL_TEXTURE_2D, texId[name] );
    //cout << name << ' ' << pos.x << ' ' << pos.y << ' ' << width << ' ' << height << endl;
    glEnable(GL_ALPHA_TEST);//试描画开始
    glAlphaFunc(GL_GREATER, 0.5);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f); glVertex2f(pos.x, pos.y);//左下
	glTexCoord2f(0.0f, 1.0f); glVertex2f(pos.x, pos.y + height);//左上
	glTexCoord2f(1.0f, 1.0f); glVertex2f(pos.x + width, pos.y + height);//右上
	glTexCoord2f(1.0f, 0.0f); glVertex2f(pos.x + width, pos.y);//右下
	glEnd();
	glDisable(GL_ALPHA_TEST);//试描画结束
    glDisable(GL_TEXTURE_2D);//图像无效
}

// 键鼠操作回调函数
void onEscPressed(unsigned char key, int x, int y) {
    if(key == 27) glutHideWindow();
}


// 辅助绘图



int getPassengerTexId() {
    return int(rand()*1.0*passengerTexNum/RAND_MAX+1);
}

// 读取材质，要用GIF的话需要重写
void loadTexture() {
    loadPassengerTex();
    texId[_checkPoint] = SOIL_load_OGL_texture(
        ".\\source\\checkPoint.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB
    );
    texId[_serpQueueLeft] = SOIL_load_OGL_texture(
        ".\\source\\line_left.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB
    );
    texId[_serpQueueRight] = SOIL_load_OGL_texture(
        ".\\source\\line_right.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB
    );
    texId[_serpQueueDownL] = SOIL_load_OGL_texture(
        ".\\source\\line_downl.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB 
    );
    texId[_serpQueueDownU] = SOIL_load_OGL_texture(
        ".\\source\\line_downu.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB 
    );
    texId[_restArea] = SOIL_load_OGL_texture(
        ".\\source\\restArea.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB
    );
}

void loadPassengerTex() {
    char s[200];
    for(int i = 1; i <= passengerTexNum; i++) {
        sprintf(s, ".\\source\\p%d.png", i);
        //cout << s << endl;
        int st = SOIL_load_OGL_texture(
            s,
            SOIL_LOAD_AUTO,
            i,
            SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB
        );
        //cout << st << endl;
    }
}

void display() { } // 在窗口改变大小时调用，不灵活，先不用了
void changeSize(int w, int h) {curWindowWidth = w; curWindowHeight = h;}

// 点结构体的实现
Point::Point() { x = 0.0f; y = 0.0f; }
Point::Point(float a, float b) : x(a), y(b) { }
Point::Point(const Point& p) { x = p.x; y = p.y; }
Point& Point::operator = (const Point& p) { x = p.x; y = p.y; return *this; }
Point Point::operator + (const Point& p) { return Point(x + p.x, y + p.y); }
Point Point::operator * (const float m) { return Point(x*m, y*m); }
