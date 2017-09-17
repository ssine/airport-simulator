#pragma once
#include <ctime>
#include "serpqueue.h"

extern int MinCheck;
extern int MaxCheck;
extern int MaxCustSingleLine;
extern int MaxCustSingleSkew;
extern int MaxLines;
extern int MaxSeqLen;
extern int EasySeqLen;
extern int MaxCustCheck;
extern int MaxSec;
extern int MaxRestNum;
extern time_t t_unit;
extern int distributionMethod;
extern int MaxCustNum;
extern bool isoffDuty;
extern int curFreeRtp;
// 打开动画
extern bool aniWindow;
extern bool initFinished;

extern SerpQueue SerpQ;

// 材质名字的枚举变量，实现动图的时候需要改
typedef enum textureName
{
    _passenger, _checkPoint, _serpQueueLeft, _serpQueueRight,
    _serpQueueDownL, _serpQueueDownU, _restArea,
    arrow_left_normal, arrow_left_hover, arrow_left_pressed,
    arrow_right_normal, arrow_right_hover, arrow_right_pressed,
    button_normal, button_hover, button_pressed,
    initbg, anibg, CPblock, CPpause,
    playAndPause_normal, playAndPause_hover, playAndPause_pressed,
    gooff_normal, gooff_hover, gooff_pressed,
    muslim, cp_muslim, plus_normal, plus_hover, plus_pressed
}texName;

typedef enum checkPointState
{
    onDuty, offDuty, pause, closed
} CPState;