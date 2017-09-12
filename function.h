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

int distribution(CheckPoint CheckP[]);

void refreshCheckPoint(CheckPoint CheckP[]);

//开放或关闭窗口 1开-1关0不动
int switchCheck(SerpQueue &SerpQ,const int nowCheckNum);
