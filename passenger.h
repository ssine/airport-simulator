#pragma once
#include "struct.h"
#include "glyph.h"

class Passenger : public Glyph {
public:
    int id;
    int arriveTime, checkTime;
    int routeId; // 要去哪个路径点
    static int count;
    Passenger(int arriveTime, int checkTime);
    void move();
    void nextPoint();
};

