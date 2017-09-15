#pragma once

#include <random>
#include <windows.h>
#include "passengerGenerator.h"
#include "function.h"
#include "queue.h"

using namespace std;

class EventGenerator
{
private:
	void eventStart();
	PassengerGenerator *PG;
	CheckPoint **CheckP;
	SerpQueue *SerpQ;
public:
	EventGenerator();
	~EventGenerator();
	void setPassengerGenerator(PassengerGenerator *PG); 
	void setCheckPointArray(CheckPoint **CheckP);
	void setSerpQueue(SerpQueue *SerpQ);
};

