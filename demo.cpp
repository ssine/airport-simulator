// demo.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "view.h"

#include <ctime>
#include <thread>
#include <windows.h>
#include "checkpoint.h"
#include "queue.h"
#include "serpqueue.h"
#include "function.h"
#include "globalvar.h"
#include "passengerGenerator.h"
#include "EventGenerator.h"

using namespace std;


EventGenerator EventG;
PassengerGenerator PassengerG;
CheckPoint* CheckP[20];
RestArea RestA;
SerpQueue muslimQ;
char storeNum[25];


void run();

int main(int argc, char *argv[])
{
	thread t1(show);
	t1.detach();
	readSettingFile();
	while (!initFinished);
	run();
	return 0;
}

void run() {
	clearLogFile();
	EventG.set(&PassengerG, CheckP, &SerpQ);
	for (int i = 0; i < MaxCheck; i++)
	{
		if (i < MinCheck)
		{
			CheckP[i]->start();
			writeLogFile(to_string(i) + string("checkpoint is opened"));
		}
		else
		{
			CheckP[i]->shut();
			//writeLogFile(to_string(i) + string("号安检口关闭"));
			writeLogFile(to_string(i) + string("checkpoint is closed"));
		}
	}

	PassengerG.setRestArea(&RestA);
	while (true)
	{
		EventG.eventStart();
		PassengerG.gauss();
		//休息区to蛇形队列
		while(!RestA.isempty() && RestA.getFirstPassenger().isMuslim) {
			Passenger curp = Passenger(RestA.getFirstPassenger().arriveTime, RestA.getFirstPassenger().checkTime, true, RestA.getFirstPassenger().isMuslim);
			muslimQ.addPassenger(curp);
			RestA.popPassenger();
			//cout << "ms added \n";
		}
		while (!SerpQ.isFull() && !SerpQ.isclosed() && !RestA.isempty())
		{
			Passenger curp = Passenger(RestA.getFirstPassenger().arriveTime, RestA.getFirstPassenger().checkTime, true, RestA.getFirstPassenger().isMuslim);
			curp.routeId = curFreeRtp;
			SerpQ.addPassenger(curp);
			//cout << "passenger added!" << endl;
			writeLogFile(to_string(RestA.getFirstPassenger().id) + string(" passenger enters the queuing buffer"));
			if (curFreeRtp < MaxCustNum - 1) {
				curFreeRtp++;
			}
			RestA.popPassenger();
		}
		int checkId;
		//更新安检口状态，如暂停结束操作，关闭结束操作
		refreshCheckPoint(CheckP);
		//蛇形队列to“checkId”号安检口
		while (!SerpQ.isempty() && (checkId = distribution(CheckP)) != -1)
		{
			CheckP[checkId]->addPassenger(SerpQ.getFirstPassenger());
			writeLogFile(to_string(SerpQ.getFirstPassenger().id) + string(" passengers to enter ") + to_string(checkId) + string(" checkpoint"));
			//安检完就打死
			CheckP[checkId]->refreshPopTime();
			SerpQ.popPassenger();
			for (int i = 0; i < SerpQ.getNum(); i++) SerpQ[i].nextPoint();
			if (curFreeRtp > 0) {
				curFreeRtp--;
			}
		}
		int nowCheckNum = getCheckNum(CheckP);
		int switchC = whetherSwitchCheckPoint(SerpQ, nowCheckNum);
		makeSwitchCheckPoint(CheckP, switchC);
		Sleep(t_unit);
	}
}
