#include<bits/stdc++.h>
#include<windows.h>
#include "model.h"

using namespace std;

extern int MinCheck;
extern int MaxCheck;
extern int MaxCustSingleLine;
extern int MaxLines;
extern int MaxSeqLen;
extern int EasySeqLen;
extern int MaxCustCheck;
extern int MaxSec;
extern int MaxRestNum;

class Passenger;
class Queue;
class CheckPoint;
class RestArea;
class SerpQueue;
//时间单位
const time_t t_unit=500;

PassengerGenerator PassengerG;
CheckPoint CheckP[MaxCheck];

int main()
{

    for(int i=0;i<MaxCheck;i++)
    {
        if(i<MinCheck)
            CheckP[i].start();
        else
            CheckP[i].shut();
    }
    RestArea RestA;
    SerpQueue SerpQ;
    PassengerG.setRestArea(&RestA);
    while(true)
    {
        int c=rand()%10;
        for(int i=0;i<c;i++)
        PassengerG.addSingle();
        while(!SerpQ.isFull()&&!RestA.isempty())
        {
            SerpQ.addPassenger(RestA.getFirstPassenger());
            RestA.popPassenger();
        }
        int checkId;
        refreshCheckPoint(CheckP);
        while(!SerpQ.isempty()&&(checkId=distribution(CheckP))!=-1)
        {
            CheckP[checkId].addPassenger(SerpQ.getFirstPassenger());
            CheckP[checkId].refreshPopTime();
            SerpQ.popPassenger();
        }
        int nowCheckNum=getCheckNum(CheckP);
        int switchC=whetherSwitchCheckPoint(SerpQ,nowCheckNum);
        makeSwitchCheckPoint(CheckP,switchC);
        Sleep(t_unit);
    }
    return 0;
}
