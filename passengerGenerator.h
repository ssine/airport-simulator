#pragma once
#include <random>
#include <ctime>
#include <Windows.h>
#include "queue.h"
#include "globalvar.h"
#include "stdafx.h"
#include "function.h"

class PassengerGenerator
{
private:
	int m_AutoSwitch;
	class RestArea *RestPoint = NULL;
	int m_maxid = 0;
	time_t interval = 1000;
	void addPassenger(int num);
	//高斯分布自动生成,参数为均值，方差
	
public:
	void gauss();
	//设置与休息区的链接，传入指针
	void setRestArea(RestArea *p);
	void auto_start();
	void auto_stop();
	void addSingle();
	void add(int num);
	//设置发生间隔
	void setInterval(time_t ti);
	time_t getInterval();
	
};