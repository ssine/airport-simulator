#include "stdafx.h"

#include <iostream>
#include <string>
#include <random>
#include <ctime>
#include <algorithm>
#include "queue.h"
#include "struct.h"
#include "passenger.h"
#include "globalvar.h"

using namespace std;

int maxVecNum = 500;

Queue::Queue() {
    front = rear = num = 0;
    for(int i = 0; i < maxVecNum; i++)
        q.push_back(Passenger());
}

Passenger& Queue::operator[](int n) {
    int index = (front + n) % maxVecNum;
    return q[index];
}

void Queue::addPassenger(Passenger pass) {
    q[rear] = pass;
    rear = (rear + 1) % maxVecNum;
    num++;
}

void Queue::addPassenger(int arriveTime, int checkTime) {
	if (isoffDuty)
		return;
    Passenger pass(arriveTime, checkTime);
	srand((unsigned)time(NULL));
	if(rand()%100<6)
		pass.isMuslim = true;
	else
		pass.isMuslim = false;
    q[rear] = pass;
    rear = (rear + 1) % maxVecNum;
    num++;
}

void Queue::popPassenger() {
    front = (front + 1) % maxVecNum;
    num--;
}

Passenger& Queue::getFirstPassenger() {
    return q[front];
}

Passenger& Queue::getLastPassenger() {
    return q[(rear+499)%maxVecNum];
}

int Queue::getNum() {
    return num;
}

bool Queue::isempty()
{
    return num == 0;
}