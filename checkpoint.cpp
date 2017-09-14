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
        for(int i = 0; i < q.size(); i++)
            q[i].routeId--;
    }
}

void CheckPoint::refreshPopTime() {
    if(getTime()>nextPopTime)
    {
        //popPassenger();
		if(!isempty())
        nextPopTime=getTime()+getFirstPassenger().checkTime;
    }
}

void CheckPoint::shut()
{
    state=closed;
}


void CheckPoint::addPassenger(Passenger p) {
    p.routeId = MaxCustNum+id*MaxCustCheck-1;
    //cout << "routeId changed to " << p.routeId << endl;
    q.push_back(p);
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
    for(int i = 0; i < this->getNum(); i++)
        (*this)[i].draw();
    //cout << this->getNum() << "passengers drawn " << endl;
}

