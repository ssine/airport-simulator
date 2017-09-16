#pragma once

#include <ctime>
#include "queue.h"
#include "globalvar.h"
#include "glyph.h"

class CheckPoint : public Queue, public Glyph
{
public:
    CheckPoint();
	void toPause();
    void toPause(time_t pauseTime);  //暂停
    void start();  //开始
    int getState();   //获取安检口状态
    void setState(int s);
    bool isFull();
    void refreshNum();
    void refreshPopTime();
    void shut();
    void draw();
    void addPassenger(Passenger p);
    friend void refreshCheckPoint(CheckPoint* CheckP[]);
private:
    static int num;
    int id;
    int state;  //  关闭 : 0     打开 : 1
    int nextPopTime=0;
    time_t pauseEndTime;
};