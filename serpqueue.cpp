#include "stdafx.h"
#include "queue.h"
#include "serpqueue.h"
#include "globalvar.h"


extern int MaxRestNum;
extern int MaxCustSingleLine;
extern int MaxLines;

int SerpQueue::getLineNum() {
    return lineNum;
}
int SerpQueue::getCustSingleLine() {
    return custSingleLine;
}
bool SerpQueue::isFull() {
    return getNum() >= MaxCustSingleLine * MaxLines;
}



bool RestArea::isFull() {
    return getNum() >= MaxRestNum;
}