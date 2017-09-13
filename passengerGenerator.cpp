#include "passengerGenerator.h"

void PassengerGenerator::addPassenger(int num)
{
	srand((unsigned)time(NULL));
	int id, arrTime, checkTime;
	for (int i = 0; i<num; i++)
	{
		id = m_maxid++;
		arrTime = rand() % 300;
		checkTime = rand() % MaxSec * 5;
		RestPoint->addPassenger(id, arrTime, checkTime, "laowang");
	}
}

void PassengerGenerator::gauss(int mean = 5, int variance = 2)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::normal_distribution<double> normal(mean, variance);
	while (m_AutoSwitch)
	{
		Sleep(interval);
		addPassenger(normal(gen));
	}
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
//设置发生间隔
void PassengerGenerator::setInterval(time_t ti)
{
	interval = ti;
}
time_t PassengerGenerator::getInterval()
{
	return interval;
}