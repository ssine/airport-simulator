#include "stdafx.h"
#include "globalvar.h"

int MinCheck = 4;
int MaxCheck = 8;
int MaxCustSingleLine = 20;
int MaxCustSingleSkew = 2;
int MaxLines = 8;
int MaxSeqLen = 10;
int EasySeqLen = 2;
int MaxCustCheck = 1;
int MaxSec = 5;
int MaxRestNum = 1000;
int onDuty = 0;
int offDuty = 1;
int pause = 2;
int closed = 3;
time_t t_unit = 500;

int curFreeRtp = 0;
// 打开动画
bool aniWindow = false;

SerpQueue SerpQ;

//enum int {onDuty,offDuty,pause,closed};
