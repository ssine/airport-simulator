#include "stdafx.h"
#include <vector>
#include "globalvar.h"
#include "queue.h"
#include "checkpoint.h"
#include "function.h"
#include "view.h"

#include <iostream>
using namespace std;

int CheckPoint::num = 0;
float CPInterval = 0.22;
float CPBaseX = -0.8, CPBaseY = -0.05;

void CheckPoint::start() {
    if(state != offDuty) {
        state = onDuty;
    }
}

void CheckPoint::toPause()
{
	if (state != offDuty && state != closed)
		state = pause;
}

void CheckPoint::toPause(int pauseTime)
{
	if (state != offDuty && state != closed)
	{
		state = offDuty;
		nextPopTime += pauseTime;
		pauseEndTime = getTime() + pauseTime;
	}
}

bool CheckPoint::isFull() {
    return getNum() >= MaxCustCheck;
}

int CheckPoint::getState() {
    return state;
}

void CheckPoint::refreshNum() {
    if(!isempty()&&getTime()>nextPopTime) {
        popPassenger();
        for(int i = front; i != rear; i = (i+1)%500)
            q[i].routeId--;
    }
}

void CheckPoint::refreshPopTime() {
    if(getTime()>nextPopTime)
    {
        //popPassenger();
		if(!isempty())
        nextPopTime=getTime()+getFirstPassenger().checkTime*10;
    }
}

void CheckPoint::shut()
{
    state=closed;
}


void CheckPoint::addPassenger(Passenger p) {
    p.routeId = MaxCustNum+1+id*(MaxCustCheck+1) + getNum();
    if(p.routeId > MaxCustNum+(id+1)*(MaxCustCheck+1)) {
        p.routeId = MaxCustNum+(id+1)*(MaxCustCheck+1);
    }
    Queue::addPassenger(p);
}

CheckPoint::CheckPoint() {
    id = num++;
    width = 0.175; height = 0.5;
    texId = ::texId[_checkPoint];
    pos.x = CPBaseX + id*CPInterval;
    pos.y = CPBaseY;
}

void CheckPoint::draw() {
    this->Glyph::draw();
    if(state == closed) {
        //cout << "close pic drawn" << endl;
        drawObject(block, Point(pos.x+0.05, pos.y+height), 0.07, 0.12);
    }
    for(int i = 0; i < this->getNum(); i++) {
        if(i == 0) (*this)[i].draw(true);
        else (*this)[i].draw(false);
    }
}