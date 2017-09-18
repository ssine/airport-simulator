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
float CPInterval = 0.15;
float CPBaseX = -0.70, CPBaseY = -0.15;
float CPWidth = 0.135, CPHeight = 0.35;

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

void CheckPoint::toPause(time_t pauseTime)
{
	if (state != offDuty && state != closed)
	{
		state = pause;
		nextPopTime += pauseTime;
		pauseEndTime = getTime() + pauseTime*2;
	}
}

bool CheckPoint::isFull() {
    return getNum() >= MaxCustCheck;
}

int CheckPoint::getState() {
    return state;
}

void CheckPoint::refreshNum() {
	if (state == pause&&getTime() > pauseEndTime)
	{
		state = onDuty;
	} else if(state == onDuty || state == closed) {
        if(!isempty()&&getTime()>nextPopTime) {
            popPassenger();
            for(int i = front; i != rear; i = (i+1)%500)
            q[i].routeId--;
        }
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
    width = CPWidth; height = CPHeight;
    texId = ::texId[_checkPoint];
    pos.x = CPBaseX + id*CPInterval;
    pos.y = CPBaseY;
}

void CheckPoint::draw() {
    this->Glyph::draw();
    switch(state) {
        case closed:
            drawObject(CPblock, Point(pos.x+0.05, pos.y+height), 0.07, 0.12);
            break;
        case pause:
            drawObject(CPpause, Point(pos.x+0.05, pos.y+height), 0.07, 0.12);
            break;
    }
    for(int i = 0; i < this->getNum(); i++) {
        if(i == 0) (*this)[i].draw(true);
        else (*this)[i].draw(false);
    }
}