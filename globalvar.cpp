#include "stdafx.h"
#include "globalvar.h"
#include "checkpoint.h"
//最小安检口
int MinCheck = 4;
//最大安检口数
int MaxCheck = 8;
//蛇形队列最大一行的人数
int MaxCustSingleLine = 20;
//两行蛇形队列间人数
int MaxCustSingleSkew = 2;
//最大行数
int MaxLines = 4;
//可打开窗口时
int MaxSeqLen = 10;
//可关闭窗口时
int EasySeqLen = 2;
//安检口最大人数
int MaxCustCheck = 5;
//最大安检时间
int MaxSec = 5;
//最大休息区人数
int MaxRestNum = 1000;
//方案编号
int distributionMethod = 0;
//时间单位
time_t t_unit = 200;
//蛇形队列人数
int MaxCustNum;
//当前可用路径点
int curFreeRtp = 0;
//是否触发了下班函数
bool isoffDuty = false;
// 打开动画
bool aniWindow = false;
//是否初始化完成
bool initFinished = false;
//蛇形队列
SerpQueue SerpQ;


//enum int {onDuty,offDuty,pause,closed};
