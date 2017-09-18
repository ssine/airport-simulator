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
const int windowWidth = 1366;
const int windowHeight = 768;
int curWindowWidth = 1366;
int curWindowHeight = 768;

// 窗口名称
const char* windowTitle = "杀虫灭菌安检口";

extern CheckPoint* CheckP[];
extern RestArea RestA;
extern SerpQueue muslimQ;

extern texName a;
int texId[300];

std::vector<Point> route;
// 每排&每斜线人数
// passenger纹理总数
int passengerTexNum = 10;


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


float varX = -0.5, varY = 0.75;
float nameVarSpace = 0.7;
float nameBtnSpace = 0.53;
float nameBtnSpace2 = 0.3;
float varListHeight = 0.2;

extern float CPInterval;
extern float CPBaseX, CPBaseY;
extern float CPWidth, CPHeight;

std::vector<Button> btnList;
std::vector<Button> aniBtnList;

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

void delayedVarInit(int var) {
    if(aniWindow) {
        for(int i = 0; i < MaxCheck; i++) CheckP[i] = new CheckPoint();
        // 生成乘客路径点
        genRoute();
        for(int i = 0; i < MaxCheck; i++) {
            aniBtnList.push_back(Button(playAndPause_normal, CPBaseX+0.06+i*CPInterval, CPBaseY+0.7, 0.06, 0.10667));
            aniBtnList[i].corspCP = i;
        }
        aniBtnList.push_back(Button(gooff_normal, 0.7, -1.0, 0.3, 0.25));
        aniBtnList.push_back(Button(plus_normal, -0.9, -0.6, 0.1, 0.18));
        initFinished = true;
    } else {
        glutTimerFunc(1, delayedVarInit, 0);
    }
}

void drawInit() {
    // 必要的数值计算
    lmd = alp / sqdw;
    SQDW=lmd*sqdw, SQDH=lmd*sqdh*alph, SQLRW=lmd*sqlrw, SQLRH=lmd*sqlrh*alph;
    SQdX=lmd*dltx, SQdY=lmd*dlty*alph, SQdX_=lmd*dltx_, SQdY_=lmd*dlty_*alph;

    // 读取材质
    loadTexture();

    glutTimerFunc(1, delayedVarInit, 0);

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
        drawObject(initbg, Point(-1.0, -1.0), 2.0, 2.0);
        drawVars();
        drawButton();
    } else {
        // 图形
        drawObject(anibg, Point(-1.0, -1.0), 2.0, 2.0);
        
        //drawObject(playAndPause_normal, Point(-1.0, -1.0), 2.0, 2.0);
        // 移动队列中所有乘客并绘制
        for(int i = 0; i < SerpQ.getNum(); i++) SerpQ[i].move();
        for(int i = 0; i < MaxCheck; i++) {
            for(int j = 0; j < CheckP[i]->getNum(); j++)
            (*(CheckP[i]))[j].move();
        }
        for(int i = 0; i < muslimQ.getNum(); i++) {
            muslimQ[i].move();
        }
        if(muslimQ.getNum() > 0 && muslimQ[0].pos.x > 0.75) muslimQ.popPassenger();
        drawObject(cp_muslim, Point(CPBaseX + 10*CPInterval, CPBaseY), CPWidth+0.05, CPHeight+0.26);
        drawCheckPoint();
        drawSerpQueue();

        drawButton();
        drawRestAreaNum();

        if(isoffDuty) {
            glRasterPos2f(0.75, 0.75);
            drawString("Off Duty!");
        }

    }

    glutSwapBuffers();
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

    glRasterPos2f(varX, varY-8*varListHeight);
    sprintf(s, "distributionMethod");
    drawString(s);
    glRasterPos2f(varX + nameVarSpace, varY-8*varListHeight);
    sprintf(s, "%d", distributionMethod);
    drawString(s);   //输出的字符串

}

void drawRestAreaNum() {
    glColor3f(0.0f, 0.0f, 0.0f);
    char s[100];
    glRasterPos2f(-0.95, -0.2);
    sprintf(s, "%d", RestA.getNum());
    drawString(s);   //输出的字符串
    glColor3f(1.0f, 1.0f, 1.0f);
}

void initButton() {
    for(int i = 0; i < 9; i++) {
        btnList.push_back(Button(arrow_left_normal, varX+nameBtnSpace, varY-i*varListHeight-0.01, 0.06, 0.10667));
    }
    for(int i = 0; i < 9; i++) {
        btnList.push_back(Button(arrow_right_normal, varX+nameBtnSpace+nameBtnSpace2, varY-i*varListHeight-0.01, 0.06, 0.10667));
    }
    btnList.push_back(Button(button_normal, 0.55, -0.83, 0.3, 0.23));
    btnList[0].corspVar = &MinCheck;
    btnList[1].corspVar = &MaxCheck;
    btnList[2].corspVar = &MaxCustSingleLine;
    btnList[3].corspVar = &MaxLines;
    btnList[4].corspVar = &MaxSeqLen;
    btnList[5].corspVar = &EasySeqLen;
    btnList[6].corspVar = &MaxCustCheck;
    btnList[7].corspVar = &MaxSec;
    btnList[8].corspVar = &distributionMethod;
    btnList[9].corspVar = &MinCheck;
    btnList[10].corspVar = &MaxCheck;
    btnList[11].corspVar = &MaxCustSingleLine;
    btnList[12].corspVar = &MaxLines;
    btnList[13].corspVar = &MaxSeqLen;
    btnList[14].corspVar = &EasySeqLen;
    btnList[15].corspVar = &MaxCustCheck;
    btnList[16].corspVar = &MaxSec;
    btnList[17].corspVar = &distributionMethod;


}

void drawButton() {
    if(aniWindow) {
        for(auto btn : aniBtnList) {
            btn.draw();
        }
    } else {
        for(auto btn : btnList) btn.draw();
    }
}

void mouseMotion(int x, int y) {
    if(aniWindow) {
        for(int i = 0; i < aniBtnList.size(); i++) aniBtnList[i].mouseMove(x, y);
    } else {
        for(int i = 0; i < btnList.size(); i++) btnList[i].mouseMove(x, y);
    }
}


void mouseClick(int mbtn, int state, int x, int y) {
    if(aniWindow) {
        for(int i = 0; i < aniBtnList.size(); i++) aniBtnList[i].mouseClick(mbtn, state, x, y);
    } else {
        for(int i = 0; i < btnList.size(); i++) btnList[i].mouseClick(mbtn, state, x, y);
    }

}


// 绘制蛇形队列
void drawSerpQueue() {
    drawObject(_serpQueueLeft, Point(SQX+SQdX+2*SQdX_,SQY+SQdY+2*SQdY_), SQLRW, SQLRH);
    int i = 0;
    for(int j = 0; j < MaxCustSingleLine + MaxCustSingleSkew && i < SerpQ.getNum(); j++, i++) {
        SerpQ[i].draw();
    }
    if(i < SerpQ.getNum())
        drawObject(_serpQueueRight, Point(SQX+SQdX+SQdX_,SQY+SQdY+SQdY_), SQLRW, SQLRH);
    for(int j = 0; j < MaxCustSingleLine + MaxCustSingleSkew && i < SerpQ.getNum(); j++, i++)
        SerpQ[i].draw();
    if(i < SerpQ.getNum())
        drawObject(_serpQueueLeft, Point(SQX+SQdX,SQY+SQdY), SQLRW, SQLRH);
    for(int j = 0; j < MaxCustSingleLine + MaxCustSingleSkew && i < SerpQ.getNum(); j++, i++)
        SerpQ[i].draw();
    if(i < SerpQ.getNum()) {
        drawObject(_serpQueueDownU, Point(SQX,SQY), SQDW, SQDH);
        for(int j = 0; j < MaxCustSingleLine + MaxCustSingleSkew && i < SerpQ.getNum(); j++, i++)
            SerpQ[i].draw();
        drawObject(_serpQueueDownL, Point(SQX,SQY), SQDW, SQDH);
    }
    for(int i = 0; i < muslimQ.getNum(); i++)
        muslimQ[i].draw();
}


Point genSkew(Point base) {
    Point step = Point(90/(MaxCustSingleSkew+1)*lmd, 93/(MaxCustSingleSkew+1)*lmd*alph);
    for(int i = 1; i <= MaxCustSingleSkew; i++) route.push_back(base + step*i);
    return Point(base + step*(MaxCustSingleSkew+1));
}

void genCPRoute(float x, float y) {
    for(int i = 0; i < MaxCustCheck+1; i++) {
        route.push_back(Point(x-i*0.02, y-i*0.03));
    }
}

void genRoute() {
    Point base(SQX + 88*lmd, SQY + 75*lmd);
    float step = 1050*1.0/(MaxCustSingleLine+1)*lmd;
    for(int i = 0; i < MaxCustSingleLine; i++) route.push_back(Point(base.x+step/2+i*step, base.y));
    base = genSkew(Point(base.x+(MaxCustSingleLine-1)*step+step/2, base.y));
    step = -step;
    for(int i = 0; i < MaxCustSingleLine; i++) route.push_back(Point(base.x+step/2+i*step, base.y));
    base = genSkew(Point(base.x+(MaxCustSingleLine-1)*step-step, base.y));
    step = -step;
    for(int i = 0; i < MaxCustSingleLine; i++) route.push_back(Point(base.x/*+step/2*/+i*step, base.y));
    base = genSkew(Point(base.x+(MaxCustSingleLine-1)*step-step, base.y));
    step = -step;
    base.x += 0.01;
    for(int i = 0; i < MaxCustSingleLine; i++) route.push_back(Point(base.x+step/2+i*step, base.y));


    std::reverse(route.begin(),route.end());
    MaxCustNum = route.size();

    for(int i = 0; i < MaxCheck; i++) {
        genCPRoute(CPBaseX + i*CPInterval + 0.05, CPBaseY + 0.03);
    }

}



void drawObject(texName name, Point& pos, float width=0.0, float height=0.0) {
/* 已封装好，传入名字画出对应对象，参数1名字 2位置 34宽高(无则使用预设) */

    glEnable(GL_TEXTURE_2D);//图像有效化
    glBindTexture( GL_TEXTURE_2D, texId[name] );
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
    int id = (clock() % passengerTexNum)+1;
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
    texId[arrow_left_hover] = SOIL_load_OGL_texture(
        ".\\source\\left_hover.png",
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
    texId[arrow_right_hover] = SOIL_load_OGL_texture(
        ".\\source\\right_hover.png",
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
        ".\\source\\button_normal.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB
    );
    
    texId[button_hover] = SOIL_load_OGL_texture(
        ".\\source\\button_hover.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB
    );
    
    texId[button_pressed] = SOIL_load_OGL_texture(
        ".\\source\\button_pressed.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB
    );

    texId[initbg] = SOIL_load_OGL_texture(
        ".\\source\\initbg.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB
    );

    texId[anibg] = SOIL_load_OGL_texture(
        ".\\source\\anibg.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB
    );
    
    texId[CPblock] = SOIL_load_OGL_texture(
        ".\\source\\CPblock.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB
    );

    texId[CPpause] = SOIL_load_OGL_texture(
        ".\\source\\CPpause.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB
    );

    texId[playAndPause_normal] = SOIL_load_OGL_texture(
        ".\\source\\playAndPause_normal.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB
    );

    texId[playAndPause_hover] = SOIL_load_OGL_texture(
        ".\\source\\playAndPause_hover.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB
    );

    texId[playAndPause_pressed] = SOIL_load_OGL_texture(
        ".\\source\\playAndPause_pressed.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB
    );

    texId[gooff_normal] = SOIL_load_OGL_texture(
        ".\\source\\gooff_normal.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB
    );

    texId[gooff_hover] = SOIL_load_OGL_texture(
        ".\\source\\gooff_hover.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB
    );

    texId[gooff_pressed] = SOIL_load_OGL_texture(
        ".\\source\\gooff_pressed.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB
    );

    texId[muslim] = SOIL_load_OGL_texture(
        ".\\source\\muslim.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB
    );

    texId[cp_muslim] = SOIL_load_OGL_texture(
        ".\\source\\cp_muslim.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB
    );

    texId[plus_normal] = SOIL_load_OGL_texture(
        ".\\source\\plus_normal.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB
    );

    texId[plus_hover] = SOIL_load_OGL_texture(
        ".\\source\\plus_hover.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB
    );

    texId[plus_pressed] = SOIL_load_OGL_texture(
        ".\\source\\plus_pressed.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB
    );
    

}

void loadPassengerTex() {
    char s[200];
    for(int i = 1; i <= passengerTexNum; i++) {
        sprintf(s, ".\\source\\p%d.png", i);
        int st = SOIL_load_OGL_texture(
            s,
            SOIL_LOAD_AUTO,
            i,
            SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB
        );
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
bool Point::operator == (const Point& p) {return x == p.x && y == p.y; }