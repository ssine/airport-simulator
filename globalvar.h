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
extern int onDuty;
extern int offDuty;
extern int pause;
extern int closed;

extern int curFreeRtp;
// 打开动画
extern bool aniWindow;

extern SerpQueue SerpQ;

// 材质名字的枚举变量，实现动图的时候需要改
typedef enum textureName
{
    _passenger, _checkPoint, _serpQueueLeft, _serpQueueRight,
    _serpQueueDownL, _serpQueueDownU, _restArea,
    arrow_left_normal, arrow_left_pressed, arrow_right_normal, arrow_right_pressed,
    button_normal, button_hover, button_pressed
}texName;
