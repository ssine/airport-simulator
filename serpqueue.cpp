#include "stdafx.h"
#include "queue.h"
#include "serpqueue.h"
#include "globalvar.h"


extern int MaxRestNum;
extern int MaxCustNum;

int SerpQueue::getLineNum() {
    return lineNum;
}
int SerpQueue::getCustSingleLine() {
    return custSingleLine;
}
bool SerpQueue::isFull() {
    return getNum() >= MaxCustNum;
}



bool RestArea::isFull() {
    return getNum() >= MaxRestNum;
}