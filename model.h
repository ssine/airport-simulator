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
//random event
struct Entry
{
    int no;
    int sec;
    char type;
    int mans;
    int check;
};

time_t getTime()
{
    return clock()/t_unit;
}
//乘客发生器，在休息区添加数字
class PassengerGenerator
{
private:
    int m_AutoSwitch;
    RestArea *RestPoint=NULL;
    time_t interval=1000;
public:
    //高斯分布自动生成,参数为均值，方差
    void gauss(int mean=5,int variance=2)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::normal_distribution<double> normal(mean,variance);
        while(m_AutoSwitch)
        {
            Sleep(interval);
            RestPoint->add(normal(gen));
        }
    }
    //设置与休息区的链接，传入指针
    void setRestArea(RestArea *p)
    {
        this->RestPoint=p;
    }
    void auto_start()
    {
        m_AutoSwitch=1;
        gauss();
    }
    void auto_stop()
    {
        m_AutoSwitch=0;
    }
    void addSingle()
    {
        RestPoint->add(1);
    }
    void add(int num)
    {
        RestPoint->add(num);
    }
    //设置发生间隔
    void setInterval(time_t ti)
    {
        interval=ti;
    }
    time_t getInterval()
    {
        return interval;
    }
};

#endif

