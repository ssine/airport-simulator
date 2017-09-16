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


using namespace std;



PassengerGenerator PassengerG;
CheckPoint* CheckP[20];
char storeNum[25];

void run();

int main(int argc, char *argv[])
{
	thread t1(show);
	t1.detach();
	//readSettingFile();
	while (!aniWindow);
	run();
	return 0;
}

void run() {
	clearLogFile();
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
	RestArea RestA;

	PassengerG.setRestArea(&RestA);
	while (true)
	{
		int c = rand() % 3;
		for (int i = 0; i < c; i++)
			PassengerG.addSingle();

		//休息区to蛇形队列
		while (!SerpQ.isFull() && !RestA.isempty())
		{
			Passenger curp = Passenger(RestA.getFirstPassenger().arriveTime, RestA.getFirstPassenger().checkTime, true);
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
