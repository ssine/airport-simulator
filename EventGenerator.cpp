#include <windows.h>
#include "stdafx.h"
#include "EventGenerator.h"
#include "globalvar.h"

EventGenerator::EventGenerator()
{
	eventStart();
}


EventGenerator::~EventGenerator()
{
}

void EventGenerator::eventStart()
{
	srand((unsigned)time(NULL));
	if (rand() % 100 < 90)
	{
		PG->addSingle();
	}
	else
	{
		int id = rand() % MaxCheck;
		if (CheckP[id]->getState() == onDuty)
			CheckP[id]->toPause(rand() % 20);
	}
	if (rand() % 100 == 100 && getTime() > 100)
	{
		programEnd(CheckP,SerpQ);
	}
}

void EventGenerator::setPassengerGenerator(PassengerGenerator *PG)
{
	this->PG = PG;
}

void EventGenerator::setCheckPointArray(CheckPoint **CheckP)
{
	this->CheckP = CheckP;
}

void EventGenerator::setSerpQueue(SerpQueue *SerpQ)
{
	this->SerpQ = SerpQ;
}