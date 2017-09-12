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

void CheckPoint::pause() {
    if(state != offDuty && state != closed) {
        state = onDuty;
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
        popPassenger();
        nextPopTime=getTime()+getFirstPassenger().checkTime;
    }
}