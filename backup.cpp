#include<bits/stdc++.h>
#include<windows.h>
using namespace std;

int MinCheck=4;
int MaxCheck=8;
int MaxCustSingleLine=30;
int MaxLines=8;
int MaxSeqLen=10;
int EasySeqLen=2;
int MaxCustCheck=6;
int MaxSec=5;
int MaxRestNum=1000;

class Passenger;
class Queue;
class CheckPoint;
class RestArea;
class SerpQueue;
//时间单位
const time_t t_unit=500;

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

//最大安检口数  一条蛇形队列长度   蛇形队列行数
//系统检查“排队缓冲区”乘客数量除以开放的安检口数量
//大于最大允许等待长度MaxSeqLen时增开一个安检口
//小于短期等待长度EasySeqLen时关闭一个安检口
struct Passenger {
    int id;
    int arriveTime, checkTime;
    string name;
};

enum stateOfCheckPoint {onDuty,offDuty,pause,closed};

class Queue {
public:
    void addPassenger(int id, int arriveTime, int checkTime, string name);  //添加乘客
    void addPassenger(Passenger p);
    void popPassenger();  //乘客出队
    Passenger getFirstPassenger(); //即将出队的乘客
    int getNum(); //队列人数
    bool isempty();
    Passenger operator[](int n);
private:
    vector<Passenger> q; //乘客队列;
};
inline Passenger Queue::operator[](int n) {
        return q[n];
}

inline void Queue::addPassenger(Passenger pass) {
    q.push_back(pass);
    cout<<"***"<<q.size()<<endl;
}

inline void Queue::addPassenger(int id, int arriveTime, int checkTime, string name) {
    Passenger pass{id, arriveTime, checkTime, name};
    q.push_back(pass);
}

inline void Queue::popPassenger() {
    q.erase(q.begin());
}

inline Passenger Queue::getFirstPassenger() {
    return q[0];
}

inline int Queue::getNum() {
    return q.size();
}

inline bool Queue::isempty()
{
    return getNum()==0;
}

class CheckPoint : public Queue {
public:
    void pause();  //暂停
    void start();  //开始
    stateOfCheckPoint getState();   //获取安检口状态
    bool isFull();
    void refreshNum();
    void refreshPopTime();

private:
    stateOfCheckPoint state=onDuty;  //  关闭 : 0     打开 : 1
    int nextPopTime=0;
};

inline void CheckPoint::start() {
    if(state != offDuty) {
        state = onDuty;
    }
}

inline void CheckPoint::pause() {
    if(state != offDuty && state != closed) {
        state = onDuty;
    }
}

inline bool CheckPoint::isFull() {
    return getNum() >= MaxCustCheck;
}
inline stateOfCheckPoint CheckPoint::getState() {
    return state;
}

inline void CheckPoint::refreshNum() {
    if(!isempty()&&getTime()>nextPopTime)
        popPassenger();
}

inline void CheckPoint::refreshPopTime() {
    if(getTime()>nextPopTime)
    {
        popPassenger();
        nextPopTime=getTime()+getFirstPassenger().checkTime;
    }
}
/*
inline void CheckPoint::refreshState()
{
    if(getState()==onDuty)
    {
        if(getNum()>=MaxCustSingleLine)
    }
}*/

class SerpQueue : public Queue {
public:
    SerpQueue():custSingleLine{0}, lineNum{2} {}
    int getCustSingleLine();
    int getLineNum();
    bool isFull();
private:
    int custSingleLine, lineNum;
};
inline int SerpQueue::getLineNum() {
    return lineNum;
}
inline int SerpQueue::getCustSingleLine() {
    return custSingleLine;
}
inline bool SerpQueue::isFull() {
    return getNum() == MaxCustSingleLine * MaxLines;
}

class RestArea : public Queue {
public: bool isFull();
};

inline bool RestArea::isFull() {
    return getNum() == MaxRestNum;
}


class PassengerGenerator
{
private:
    int m_AutoSwitch;
    class RestArea *RestPoint=NULL;
    int m_maxid=0;
    time_t interval=1000;
    void addPassenger(int num)
    {
       srand((unsigned)time(NULL));
        int id,arrTime,checkTime;
        for(int i=0;i<num;i++)
        {
            id=m_maxid++;
            arrTime=rand()%300;
            checkTime=rand()%MaxSec;
            RestPoint->addPassenger(id,arrTime,checkTime,"laowang");
        }
    }
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
            addPassenger(normal(gen));
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
        addPassenger(1);
    }
    void add(int num)
    {
        addPassenger(num);
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



void readSettingFile()
{
    std::ifstream fin("para.dat",std::ios::binary);
    int *a=new int[10];
    fin.read((char *)a,sizeof(a));
    MinCheck=a[0];
    MaxCheck=a[1];
    MaxCustSingleLine=a[2];
    MaxLines=a[3];
    MaxSeqLen=a[4];
    EasySeqLen=a[5];
    MaxCustCheck=a[6];
    MaxSec=a[7];
    fin.close();
    delete a;
}

void writeSettingFile()
{
    std::ofstream fout("para.dat",std::ios::binary);
    int *a=new int[10];
    a[0]=MinCheck;
    a[1]=MaxCheck;
    a[2]=MaxCustSingleLine;
    a[3]=MaxLines;
    a[4]=MaxSeqLen;
    a[5]=EasySeqLen;
    a[6]=MaxCustCheck;
    a[7]=MaxSec;
    fout.write((char *)a,sizeof(a));
    fout.close();
    delete a;
}

void rondomWriteInputFile()
{
    std::ofstream fin("input.dat",std::ios::binary);
    Entry *en=new Entry[100];
    srand((unsigned)time(NULL));
    for(int i=0; i<100; i++)
    {
        en[i].no=i;
        en[i].sec=rand()%300;
        int temp=rand()%3;
        if(temp==0)
            en[i].type='C';
        else if(temp==1)
            en[i].type='X';
        else
            en[i].type='Q';
        en[i].mans=rand()%10;
        en[i].check=rand()%MaxCheck;
    }
    fin.write((char*)en,sizeof(en));
    fin.close();
    delete en;
}

void readInputFile(Entry *en)
{
    std::ifstream fin("input.dat",std::ios::binary);
    fin.read((char*)en,sizeof(en));
    fin.close();
}

void clearLogFile()
{
    std::fstream fout("Log.txt");
    fout<<"Log"<<std::endl;
}

void writeLogFile(string s)
{
    std::fstream fout("Log.txt",std::ios::app);
    fout<<s;
}

int distribution(CheckPoint CheckP[])
{
    for(int i=0;i<MaxCheck;i++)
    {
        if(CheckP[i].getState()==onDuty&&!CheckP[i].isFull())
        {
            return i;
        }
    }
    return -1;
}

void refreshCheckPoint(CheckPoint CheckP[])
{
    for(int i=0;i<MaxCheck;i++)
        if(CheckP[i].getState()==onDuty)
            {
                CheckP[i].refreshNum();

            }
}
//开放或关闭窗口 1开-1关0不动
int switchCheck(SerpQueue &SerpQ,const int nowCheckNum)
{
    int num=SerpQ.getNum()/nowCheckNum;
    if(num>MaxCheck)
        return 1;
    if(num<EasySeqLen)
        return -1;
    return 0;
}

int main()
{
    PassengerGenerator PassengerG;
    CheckPoint CheckP[8];
    RestArea RestA;
    SerpQueue SerpQ;
    PassengerG.setRestArea(&RestA);
    while(1)
    {
        PassengerG.addSingle();
        while(!SerpQ.isFull()&&!RestA.isempty())
        {
            SerpQ.addPassenger(RestA.getFirstPassenger());
            cout<<"RestA "<<RestA.getFirstPassenger().id<<" to "<<"SerpQ"<<endl;
            RestA.popPassenger();
        }
        int checkId;
        refreshCheckPoint(CheckP);
        while(!SerpQ.isempty()&&(checkId=distribution(CheckP))!=-1)
        {
            CheckP[checkId].addPassenger(SerpQ.getFirstPassenger());
            CheckP[checkId].refreshPopTime();
            cout<<"check1 "<<CheckP[0].getNum()<<endl;
            cout<<"SerpQ "<<SerpQ.getFirstPassenger().id<<" to "<<"CheckP "<<checkId<<endl;
            SerpQ.popPassenger();
        }


        Sleep(t_unit);
    }
    return 0;
}
