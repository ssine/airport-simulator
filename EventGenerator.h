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
	
	PassengerGenerator *PG;
	CheckPoint **CheckP;
	SerpQueue *SerpQ;
public:
	EventGenerator();
	~EventGenerator();
	void eventStart();
	void EventGenerator::set(PassengerGenerator *PG, CheckPoint **CheckP, SerpQueue *SerpQ);
};

