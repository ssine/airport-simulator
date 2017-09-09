#ifndef MODEL_H

#define MODEL_H

#include<ctime>

//时间单位
const time_t t_unit=500;

struct passenger
{
    int id;
    int arrTime, checkTime;
    passenger();
};

time_t getTime()
{
    return clock()/t_unit;
}

#endif

