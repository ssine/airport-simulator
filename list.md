# enum
* stateOfCheckPoint(onDuty,offDuty,pause,closed)上班，下班，暂停，关闭

# class

## Queue
* void addPassenger(int id, int arriveTime, int checkTime, string name);  
* void addPassenger(Passenger p);
* void popPassenger();  //乘客出队
* Passenger getFirstPassenger(); //即将出队的乘客
* int getNum(); //队列人数
* bool isempty();
* Passenger operator[](int n);

## CheckPoint : Queue
* pause(int pauseTime);
* start();
* shut();
* stateOfCheckPoint getState();   //获取安检口状态
* void setState(stateOfCheckPoint s);
* bool isFull();
* void refreshNum();//刷新：安检完出队
* void refreshPopTime();//刷新：检查队首出队时间

## serpQueue
* int getCustSingleLine();
* int getLineNum();
* bool isFull();

## restArea
* bool isFull();

## PassengerGenerator
* setRestArea(RestArea *p);
* void auto_start();
* void auto_stop();
* void addSingle(int num=1);
* void add(int num);
* void fileRead();
* void setInterval(time_t ti);
* time_t getInterval();

# struct
struct Entry
{
    int no;
    int sec;
    char type;
    int mans;
    int check;
};

struct Passenger
{
    int id;
    int arriveTime, checkTime;
    string name;
};

# function
* int distribution(CheckPoint CheckP[]);
* void readSettingFile();
* void writeSettingFile()
* void writeLog();
* void rondomWriteInputFile();
* void readInputFile(Entry *en);
* void clearLogFile();
* void writeLogFile(string s);
* void refreshCheckPoint(CheckPoint CheckP[]);
* int whetherSwitchCheckPoint(SerpQueue &SerpQ,const int nowCheckNum)//开放或关闭窗口 1开-1关0不动
* int getCheckNum(CheckPoint CheckP[]);
* void makeSwitchCheckPoint(CheckPoint CheckP[],int op)//开关安检口
* void programEnd(CheckPoint CheckP[])//下班
