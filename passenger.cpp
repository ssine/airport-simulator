#include "stdafx.h"
#include "passenger.h"
#include <cstdlib>
#include "view.h"

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
    pos.x = pos.y = 0.0;
    routeId = 0;
}

void Passenger::move() {
    pos.x += sym(pos.x, route[routeId].x) * step;
    pos.y += sym(pos.y, route[routeId].y) * step;
}

