#include "stdafx.h"

#include <iostream>
#include <string>
#include "queue.h"
#include "struct.h"
#include "globalvar.h"

Passenger Queue::operator[](int n) {
    return q[n];
}

void Queue::addPassenger(Passenger pass) {
    q.push_back(pass);
    std::cout<<"***"<<q.size()<<std::endl;
}

void Queue::addPassenger(int id, int arriveTime, int checkTime, std::string name) {
    Passenger pass{id, arriveTime, checkTime, name};
    q.push_back(pass);
}

void Queue::popPassenger() {
    q.erase(q.begin());
}

Passenger Queue::getFirstPassenger() {
    return q[0];
}

int Queue::getNum() {
    return q.size();
}

bool Queue::isempty()
{
    return getNum() == 0;
}