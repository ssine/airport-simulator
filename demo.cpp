// demo.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
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
CheckPoint CheckP[10];


void run();

int main(int argc, char *argv[])
{
	thread t1(show);
	t1.detach();
	cout << "you see me?";
	//readSettingFile();
	while(!aniWindow) ;
	run();
	return 0;
}

void run() {
	for (int i = 0; i<MaxCheck; i++)
	{
		if (i<MinCheck)
			CheckP[i].start();
		else
			CheckP[i].shut();
	}
	RestArea RestA;
	
	PassengerG.setRestArea(&RestA);
	while (true)
	{
		int c = rand() % 30;
		for (int i = 0; i<c; i++)
			PassengerG.addSingle();
			//休息区to蛇形队列
		//cerr << RestA.isempty()<<endl;
		while (!SerpQ.isFull() && !RestA.isempty())
		{
			//cerr <<"2"<< RestA.isempty() << endl;
			SerpQ.addPassenger(RestA.getFirstPassenger());
			if(curFreeRtp < 40) curFreeRtp++;
			RestA.popPassenger();
		}
		int checkId;
		//更新安检口状态，如暂停结束操作，关闭结束操作
		refreshCheckPoint(CheckP);
		//蛇形队列to“checkId”号安检口
		while (!SerpQ.isempty() && (checkId = distribution(CheckP)) != -1)
		{
			CheckP[checkId].addPassenger(SerpQ.getFirstPassenger());
			//安检完就打死
			cout << "***" << CheckP[0].getNum() << endl;
			CheckP[checkId].refreshPopTime();
			SerpQ.popPassenger();
			for(int i = 0; i < SerpQ.getNum(); i++) SerpQ[i].nextPoint();
			if(curFreeRtp > 0) curFreeRtp--;
			//cout << SerpQ.getNum() << endl;
		}
		int nowCheckNum = getCheckNum(CheckP);
		int switchC = whetherSwitchCheckPoint(SerpQ, nowCheckNum);
		makeSwitchCheckPoint(CheckP, switchC);
		Sleep(t_unit);
	}
}
