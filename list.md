# class

## CheckPoint
* void add();
* void pasue();
* int getNum();
* bool getState();

## SerpQueue
* void add();
* bool isfull();
* int getNum();

## RestArea
* int getNum();
* void add(int num);

## PassengerGenerator
* void auto_start();
* void auto_stop();
* void addSingle(int num=1);
* void add(int num);
* void setRestArea(RestArea *p);
* void setInterval(time_t ti);//设置间隔
* time_t getInterval();
* void setGauss(int m,int v);//设置均值方差

# struct
* Passenger

# function
* int distribution();
* void readSettingFile();
* void writeLog();
