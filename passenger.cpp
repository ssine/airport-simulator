#include "stdafx.h"
#include "passenger.h"
#include <cstdlib>
#include <cstdio>
#include "view.h"
#include <iostream>
using namespace std;

float width = 0.08, height = 0.25;
// 动画步长
float step = 0.02;
// 距离终点多远时停止
float stopEps = 0.05;

extern float CPInterval;
extern float CPBaseX, CPBaseY;
extern float CPWidth, CPHeight;

inline float sym(float a, float b) {
    if(std::abs(a - b) < stopEps) return 0.0f;
    else if(a - b > 0) return -1.0f;
    else return 1.0f;
}

int Passenger::count = 0;

Passenger::Passenger(int arriveTime, int checkTime, bool giveid, bool isMuslim) {
    if(giveid) id = count++;
    this->arriveTime = arriveTime;
    this->checkTime = checkTime;
    this->isMuslim = isMuslim;

    texId = getPassengerTexId();
    this->width = ::width;
    this->height = ::height;
    pos.x = pos.y = -1.0;
    //routeId = curFreeRtp;
}

Passenger::Passenger() {

}

void Passenger::move() {
    if(isMuslim) {
        pos.x += sym(pos.x, CPBaseX + 10*CPInterval) * step;
        pos.y += sym(pos.y, CPBaseY) * step;
    } else {
        pos.x += sym(pos.x, route[routeId].x) * step;
        pos.y += sym(pos.y, route[routeId].y) * step;
    }
    
}

void Passenger::nextPoint() {
    if(routeId > 0) routeId--;
}

void Passenger::draw(bool showNum) {
    if(isMuslim) {
        drawObject(muslim, pos, 0.2, 0.4);
    } else {
        Glyph::draw();
    }

    if(showNum) {
        char s[100];
        glColor3f(1.0f, 1.0f, 1.0f);     //设置字体颜色
        glRasterPos2f(pos.x, pos.y + height);
        sprintf(s, "%d", id);
        drawString(s);
    }
}