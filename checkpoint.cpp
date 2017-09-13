#include "stdafx.h"
#include <vector>
#include "globalvar.h"
#include "queue.h"
#include "checkpoint.h"
#include "function.h"

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
    if(!isempty()&&getTime()>nextPopTime)
        popPassenger();
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
