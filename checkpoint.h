#pragma once

#include "queue.h"
#include "globalvar.h"

class CheckPoint : public Queue
{
public:
	void toPause();
    void toPause(int pauseTime);  //暂停
    void start();  //开始
    int getState();   //获取安检口状态
    void setState(int s);
    bool isFull();
    void refreshNum();
    void refreshPopTime();
    void shut();
    friend void refreshCheckPoint(CheckPoint CheckP[]);
private:
    int state;  //  关闭 : 0     打开 : 1
    int nextPopTime=0;
    int pauseEndTime;
};