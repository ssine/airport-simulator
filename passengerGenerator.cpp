
#include <random>
#include <ctime>
#include <Windows.h>
#include "queue.h"
#include "globalvar.h"
#include "stdafx.h"
#include "passengerGenerator.h"

void PassengerGenerator::addPassenger(int num)
{
	srand((unsigned)time(NULL));
	int arrTime, checkTime;
	for (int i = 0; i<num; i++)
	{
		arrTime = getTime()+rand() % 20;
		checkTime = rand() % MaxSec;
		//if(RestPoint->getNum()>=499)
		//	continue;
		RestPoint->addPassenger(arrTime, checkTime);
	}
}
std::random_device rd;
std::mt19937 gen(rd());
std::normal_distribution<double> normal(3, 2);
void PassengerGenerator::gauss()
{
	if(getTime()%4==0)
		addPassenger(normal(gen));
}

void PassengerGenerator::setRestArea(RestArea *p)
{
	this->RestPoint = p;
}
void PassengerGenerator::auto_start()
{
	m_AutoSwitch = 1;
	gauss();
}
void PassengerGenerator::auto_stop()
{
	m_AutoSwitch = 0;
}
void PassengerGenerator::addSingle()
{
	addPassenger(1);
}
void PassengerGenerator::add(int num)
{
	addPassenger(num);
}
//ÉèÖÃ·¢Éú¼ä¸ô
void PassengerGenerator::setInterval(time_t ti)
{
	interval = ti;
}
time_t PassengerGenerator::getInterval()
{
	return interval;
}