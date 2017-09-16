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
    Passenger(int arriveTime, int checkTime, bool giveid = false, bool isMuslim = false);
    Passenger();
    void draw(bool showNum = false);
    void move();
    void nextPoint();
};

