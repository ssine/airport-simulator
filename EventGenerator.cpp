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
	if (rand() % 100 > 90)
	{
		int id = rand() % MaxCheck;
		if (CheckP[id]->getState() == onDuty)
			CheckP[id]->toPause(rand() % 20);
	}
	if (rand() % 256 == 1 && getTime() > 300)
	{
		programEnd(CheckP,SerpQ);
	}
}

void EventGenerator::set(PassengerGenerator *PG,CheckPoint **CheckP,SerpQueue *SerpQ)
{
	this->PG = PG;
	this->CheckP = CheckP;
	this->SerpQ = SerpQ;
}