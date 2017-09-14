#pragma once

#include <string>
#include <ctime>
#include "struct.h"
#include "checkpoint.h"
#include "serpqueue.h"


time_t getTime();

void readSettingFile();

void writeSettingFile();

void rondomWriteInputFile();

void readInputFile(Entry *en);

void clearLogFile();

void writeLogFile(std::string s);

int distribution(CheckPoint* CheckP[]);

void refreshCheckPoint(CheckPoint* CheckP[]);

int whetherSwitchCheckPoint(SerpQueue &SerpQ, const int nowCheckNum);

int getCheckNum(CheckPoint* CheckP[]);

void makeSwitchCheckPoint(CheckPoint* CheckP[], int op);//开关安检口

void programEnd();//下班