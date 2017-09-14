#include "stdafx.h"
#include "view.h"
#include "struct.h"
#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <windows.h>
#include "globalvar.h"
#include "button.h"

#include "glyph.h"
#include "passenger.h"
#include "serpqueue.h"
#include "checkpoint.h"

using std::cout;
using std::endl;

clock_t clock();

// 窗口宽高
const int windowWidth = 1024;
const int windowHeight = 576;
int curWindowWidth = 1366;
int curWindowHeight = 768;

// 窗口名称
const char* windowTitle = "测试样例";

extern CheckPoint* CheckP[];

extern texName a;
int texId[300];

std::vector<Point> route;
// 每排&每斜线人数
// passenger纹理总数
int passengerTexNum = 5;


// 控制FPS
int FPS = 60;
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


float varX = -0.5, varY = 0.7;
float nameVarSpace = 0.7;
float nameBtnSpace = 0.53;
float nameBtnSpace2 = 0.3;
float varListHeight = 0.2;

std::vector<Button> btnList;

void drawString(const char* str);
void selectFont(int size, int charset, const char* face);

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
    glutPassiveMotionFunc(mouseMotion);
    glutMouseFunc(mouseClick);

    //初始化
    drawInit();

    //初始绘图函数
    glutDisplayFunc(display);
    flush(0);

    //进入主循环
    glutMainLoop();
}

void drawInit() {
    // 必要的数值计算
    lmd = alp / sqdw;
    //cout << lmd << endl;
    SQDW=lmd*sqdw, SQDH=lmd*sqdh*alph, SQLRW=lmd*sqlrw, SQLRH=lmd*sqlrh*alph;
    SQdX=lmd*dltx, SQdY=lmd*dlty*alph, SQdX_=lmd*dltx_, SQdY_=lmd*dlty_*alph;

    // 读取材质
    loadTexture();

    for(int i = 0; i < MaxCheck; i++) CheckP[i] = new CheckPoint();

    // 生成乘客路径点
    genRoute();

    // 生成按钮
    initButton();

    // 设定空白色
    glClearColor(0.796875, 0.59765625, 1.0, 1.0);

    // 测试回调函数
    glutKeyboardFunc(onEscPressed);
    // 计算Timer时间
    timeInterval = 1000 / FPS;
}


// 每一帧的绘图函数
void flush(int value) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(value == 0) {
        // 变量编辑
        drawVars();
        drawButton();
    } else {
        // 图形

        // 移动队列中所有乘客并绘制
        for(int i = 0; i < SerpQ.getNum(); i++) SerpQ[i].move();
        drawSerpQueue();
        for(int i = 0; i < MaxCheck; i++) {
            for(int j = 0; j < CheckP[i]->getNum(); j++)
                (*(CheckP[i]))[j].move();
        }
        drawCheckPoint();

    }

    glutSwapBuffers();
    //cout << "flushed!" << endl;
    if(aniWindow) glutTimerFunc(timeInterval, flush, 1);
    else glutTimerFunc(timeInterval, flush, 0);
}


void drawCheckPoint() {
    for(int i = 0; i < MaxCheck; i++) {
        CheckP[i]->draw();
    }
}


void drawVars() {
    char s[100];

    glColor3f(1.0f, 1.0f, 1.0f);     //设置字体颜色

    glRasterPos2f(varX, varY);
    sprintf(s, "MinCheck");
    drawString(s);
    glRasterPos2f(varX + nameVarSpace, varY);
    sprintf(s, "%d", MinCheck);
    drawString(s);   //输出的字符串
	
	

    glRasterPos2f(varX, varY-1*varListHeight);
    sprintf(s, "MaxCheck");
    drawString(s);
    glRasterPos2f(varX + nameVarSpace, varY-1*varListHeight);
    sprintf(s, "%d", MaxCheck);
    drawString(s);   //输出的字符串
    
    glRasterPos2f(varX, varY-2*varListHeight);
    sprintf(s, "MaxCustSingleLine");
    drawString(s);
    glRasterPos2f(varX + nameVarSpace,varY-2*varListHeight);
    sprintf(s, "%d", MaxCustSingleLine);
    drawString(s);   //输出的字符串
	
    glRasterPos2f(varX, varY-3*varListHeight);
    sprintf(s, "MaxLines");
    drawString(s);
    glRasterPos2f(varX + nameVarSpace, varY-3*varListHeight);
    sprintf(s, "%d", MaxLines);
    drawString(s);   //输出的字符串

    glRasterPos2f(varX, varY-4*varListHeight);
    sprintf(s, "MaxSeqLen");
    drawString(s);
    glRasterPos2f(varX + nameVarSpace, varY-4*varListHeight);
    sprintf(s, "%d", MaxSeqLen);
    drawString(s);   //输出的字符串
	
    glRasterPos2f(varX, varY-5*varListHeight);
    sprintf(s, "EasySeqLen");
    drawString(s);
    glRasterPos2f(varX + nameVarSpace, varY-5*varListHeight);
    sprintf(s, "%d", EasySeqLen);
    drawString(s);   //输出的字符串
	
    glRasterPos2f(varX, varY-6*varListHeight);
    sprintf(s, "MaxCustCheck");
    drawString(s);
    glRasterPos2f(varX + nameVarSpace, varY-6*varListHeight);
    sprintf(s, "%d", MaxCustCheck);
    drawString(s);   //输出的字符串
	
    glRasterPos2f(varX, varY-7*varListHeight);
    sprintf(s, "MaxSec");
    drawString(s);
    glRasterPos2f(varX + nameVarSpace, varY-7*varListHeight);
    sprintf(s, "%d", MaxSec);
    drawString(s);   //输出的字符串

}

void initButton() {
    for(int i = 0; i < 8; i++) {
        btnList.push_back(Button(varX+nameBtnSpace, varY-i*varListHeight-0.01, arrow_left_normal));
    }
    for(int i = 0; i < 8; i++) {
        btnList.push_back(Button(varX+nameBtnSpace+nameBtnSpace2, varY-i*varListHeight-0.01, arrow_right_normal));
    }
    btnList.push_back(Button(0.5, -0.5, button_normal));
    btnList[0].corspVar = &MinCheck;
    btnList[1].corspVar = &MaxCheck;
    btnList[2].corspVar = &MaxCustSingleLine;
    btnList[3].corspVar = &MaxLines;
    btnList[4].corspVar = &MaxSeqLen;
    btnList[5].corspVar = &EasySeqLen;
    btnList[6].corspVar = &MaxCustCheck;
    btnList[7].corspVar = &MaxSec;
    btnList[8].corspVar = &MinCheck;
    btnList[9].corspVar = &MaxCheck;
    btnList[10].corspVar = &MaxCustSingleLine;
    btnList[11].corspVar = &MaxLines;
    btnList[12].corspVar = &MaxSeqLen;
    btnList[13].corspVar = &EasySeqLen;
    btnList[14].corspVar = &MaxCustCheck;
    btnList[15].corspVar = &MaxSec;

}

void drawButton() {
    for(auto btn : btnList) {
        btn.draw();
    }
}

void mouseMotion(int x, int y) {
    for(int i = 0; i < btnList.size(); i++) {
        btnList[i].mouseMove(x, y);
    }
}


void mouseClick(int btn, int state, int x, int y) {
    for(int i = 0; i < btnList.size(); i++) {
        btnList[i].mouseClick(btn, state, x, y);
    }

}


// 绘制蛇形队列
void drawSerpQueue() {
    drawObject(_serpQueueLeft, Point(SQX+SQdX+2*SQdX_,SQY+SQdY+2*SQdY_), SQLRW, SQLRH);
    int i = 0;
    for(int j = 0; j < MaxCustSingleLine + MaxCustSingleSkew && i < SerpQ.getNum(); j++, i++) {
        
        SerpQ[i].draw();
    }
    //cout << "drawing pass at" << SerpQ[1].pos.x << "." << SerpQ[1].pos.y << endl;
    drawObject(_serpQueueRight, Point(SQX+SQdX+SQdX_,SQY+SQdY+SQdY_), SQLRW, SQLRH);
    for(int j = 0; j < MaxCustSingleLine + MaxCustSingleSkew && i < SerpQ.getNum(); j++, i++)
        SerpQ[i].draw();
    drawObject(_serpQueueLeft, Point(SQX+SQdX,SQY+SQdY), SQLRW, SQLRH);
    for(int j = 0; j < MaxCustSingleLine + MaxCustSingleSkew && i < SerpQ.getNum(); j++, i++)
        SerpQ[i].draw();
    drawObject(_serpQueueDownU, Point(SQX,SQY), SQDW, SQDH);
    for(int j = 0; j < MaxCustSingleLine + MaxCustSingleSkew && i < SerpQ.getNum(); j++, i++)
        SerpQ[i].draw();
    drawObject(_serpQueueDownL, Point(SQX,SQY), SQDW, SQDH);
}


Point genSkew(Point base) {
    Point step = Point(90/(MaxCustSingleSkew+1)*lmd, 93/(MaxCustSingleSkew+1)*lmd*alph);
    for(int i = 1; i <= MaxCustSingleSkew; i++) route.push_back(base + step*i);
    return Point(base + step*(MaxCustSingleSkew+1));
}

void genCPRoute(float x, float y) {
    for(int i = 0; i < MaxCustCheck; i++) {
        route.push_back(Point(x-i*0.05, y-i*0.075));
    }
}

void genRoute() {
    Point base(SQX + 88*lmd, SQY + 66*lmd);
    float step = 1144*1.0/(MaxCustSingleLine+1)*lmd;
    //cout << lmd;
    for(int i = 0; i < MaxCustSingleLine; i++) route.push_back(Point(base.x+step/2+i*step, base.y));
    base = genSkew(Point(base.x+(MaxCustSingleLine-1)*step+step/2, base.y));
    step = -step;
    for(int i = 0; i < MaxCustSingleLine; i++) route.push_back(Point(base.x+step/2+i*step, base.y));
    base = genSkew(Point(base.x+(MaxCustSingleLine-1)*step+step/2, base.y));
    step = -step;
    for(int i = 0; i < MaxCustSingleLine; i++) route.push_back(Point(base.x+step/2+i*step, base.y));
    base = genSkew(Point(base.x+(MaxCustSingleLine-1)*step+step/2, base.y));
    step = -step;
    for(int i = 0; i < MaxCustSingleLine; i++) route.push_back(Point(base.x+step/2+i*step, base.y));


    std::reverse(route.begin(),route.end());
    // cout << route.size();
    // for(int i = 0; i < route.size(); i++) 
    //     cout << route[i].x << endl;
    MaxCustNum = route.size();

    for(int i = 0; i < MaxCheck; i++) {
        genCPRoute(-0.7 + i*0.22, -0.05);
    }

    cout << "MaxCustNum=" << MaxCustNum << "  all pt=" << route.size() << endl;

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
    srand(clock());
    //int id = int(rand()*1.0*passengerTexNum/RAND_MAX+1);
    int id = (clock() % passengerTexNum)+1;
    //cout << "id:" << id << "  time:" << clock() <<  endl;
    return id;
}

// 读取材质，要用GIF的话需要重写
void loadTexture() {
    loadPassengerTex();
    texId[_checkPoint] = SOIL_load_OGL_texture(
        ".\\source\\checkpoint.png",
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
    texId[arrow_left_normal] = SOIL_load_OGL_texture(
        ".\\source\\left_normal.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB
    );
    
    texId[arrow_left_pressed] = SOIL_load_OGL_texture(
        ".\\source\\left_pressed.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB
    );
    
    texId[arrow_right_normal] = SOIL_load_OGL_texture(
        ".\\source\\right_normal.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB
    );
    
    texId[arrow_right_pressed] = SOIL_load_OGL_texture(
        ".\\source\\right_pressed.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB
    );
    
    texId[button_normal] = SOIL_load_OGL_texture(
        ".\\source\\normal.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB
    );
    
    texId[button_hover] = SOIL_load_OGL_texture(
        ".\\source\\hover.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB
    );
    
    texId[button_pressed] = SOIL_load_OGL_texture(
        ".\\source\\pressed.png",
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

void selectFont(int size, int charset, const char* face) {
    HFONT hFont = CreateFontA(size, 0, 0, 0, FW_MEDIUM, 0, 0, 0,
        charset, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, face);
    HFONT hOldFont = (HFONT)SelectObject(wglGetCurrentDC(), hFont);
    DeleteObject(hOldFont);
}

void drawString(const char* str) //屏幕显示字体
{
    selectFont(48, ANSI_CHARSET, "Comic Sans MS");
    static int isFirstCall = 1;
    static GLuint lists;

    if (isFirstCall) {
        isFirstCall = 0;
        // 申请MAX_CHAR个连续的显示列表编号
        lists = glGenLists(128);
        // 把每个字符的绘制命令都装到对应的显示列表中
        wglUseFontBitmaps(wglGetCurrentDC(), 0, 128, lists);
    }
    // 调用每个字符对应的显示列表，绘制每个字符
    for (; *str != '\0'; ++str) {
        glCallList(lists + *str);
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
