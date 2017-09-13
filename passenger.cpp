#include "stdafx.h"
#include "passenger.h"
#include <cstdlib>
#include "view.h"
#include <iostream>
using namespace std;

float width = 0.08, height = 0.25;
// 动画步长
float step = 0.005;
// 距离终点多远时停止
float stopEps = 0.01;

inline float sym(float a, float b) {
    if(std::abs(a - b) < stopEps) return 0.0f;
    else if(a - b > 0) return -1.0f;
    else return 1.0f;
}

int Passenger::count = 0;

Passenger::Passenger(int arriveTime, int checkTime) {
    id = count++;
    this->arriveTime = arriveTime;
    this->checkTime = checkTime;

    texId = getPassengerTexId();
    this->width = ::width;
    this->height = ::height;
    pos.x = pos.y = -1.0;
    routeId = curFreeRtp;
}

void Passenger::move() {
    //cout << routeId << endl;
    pos = route[routeId];
    cout <<routeId << "moved to " << pos.x << "." << pos.y << "this:" << this <<  endl;
    /*
    pos.x += sym(pos.x, route[routeId].x) * step;
    pos.y += sym(pos.y, route[routeId].y) * step;
    */
}

void Passenger::nextPoint() {
    if(routeId > 0) routeId--;
}
