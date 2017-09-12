#pragma once

#include "queue.h"
#include "globalvar.h"

class CheckPoint : public Queue {
public:
    void pause();  //暂停
    void start();  //开始
    int getState();   //获取安检口状态
    bool isFull();
    void refreshNum();
    void refreshPopTime();

private:
    int state=onDuty;  //  关闭 : 0     打开 : 1
    int nextPopTime=0;
};
