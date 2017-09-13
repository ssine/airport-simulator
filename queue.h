#pragma once

#include <string>
#include <vector>
#include "struct.h"
#include "passenger.h"

class Queue {
public:
    void addPassenger(int arriveTime, int checkTime);  //添加乘客
    void addPassenger(Passenger p);
    void popPassenger();  //乘客出队
    Passenger& getFirstPassenger(); //即将出队的乘客
    int getNum(); //队列人数
    bool isempty();
    Passenger& operator[](int n);
private:
    std::vector<Passenger> q; //乘客队列;
};

class RestArea : public Queue {
public:
    bool isFull();
};
