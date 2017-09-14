#include "stdafx.h"

#include <iostream>
#include <string>
#include <random>
#include <ctime>
#include "queue.h"
#include "struct.h"
#include "passenger.h"
#include "globalvar.h"

Passenger& Queue::operator[](int n) {
    return q[n];
}

void Queue::addPassenger(Passenger pass) {
    q.push_back(pass);
    //std::cout<<"***"<<q.size()<<std::endl;
}

void Queue::addPassenger(int arriveTime, int checkTime) {
    Passenger pass(arriveTime, checkTime);
	srand((unsigned)time(NULL));
	if(rand()%100<6)
		pass.isMuslim = true;
	else
		pass.isMuslim = false;
    q.push_back(pass);
}

void Queue::popPassenger() {
    if(!q.empty()) {
        q.erase(q.begin());
    }
}

Passenger& Queue::getFirstPassenger() {
    return q[0];
}

Passenger& Queue::getLastPassenger() {
    return q[q.size()-1];
}

int Queue::getNum() {
    return q.size();
}

bool Queue::isempty()
{
    return getNum() == 0;
}