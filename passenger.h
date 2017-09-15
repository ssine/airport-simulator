#pragma once
#include <queue>
#include "struct.h"
#include "glyph.h"

class Passenger : public Glyph {
public:
    int id;
    int arriveTime, checkTime;
    int routeId; // 要去哪个路径点
	bool isMuslim;
    static int count;
    Passenger(int arriveTime, int checkTime);
    Passenger();
    void draw();
    void move();
    void nextPoint();
};

