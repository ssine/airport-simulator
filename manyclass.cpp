#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <queue> 
#include <list>
#include <cstring>
using namespace std;
int maxCheckPoint, maxCustSingleLine, maxLineNum, easySeqLine, maxSeqLine, maxRestNum;
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
    void popPassenger();  //乘客出队
    Passenger getFirstPassenger(); //即将出队的乘客
    int getNum(); //队列人数
    Passenger operator[](int n);
private:
    vector<Passenger> q; //乘客队列;
};
inline Passenger Queue::operator[](int n) {
        return q[n];
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

class CheckPoint : public Queue {
public:
    void pause();  //暂停
    void start();  //开始
    stateOfCheckPoint getState();   //获取安检口状态
    bool isFull();
private:
    stateOfCheckPoint state;  //  关闭 : 0     打开 : 1 
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
    return getNum() == maxCheckPoint;
}
inline stateOfCheckPoint CheckPoint::getState() {
    return state;
}
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
    return getNum() == maxCustSingleLine * maxLineNum;
}

class RestAera : public Queue {
public: bool isFull();
};

inline bool RestAera::isFull() {
    return getNum() == maxRestNum;
}
CheckPoint cp;
SerpQueue sq;
int main()
{
    cin>>maxCheckPoint>>maxCustSingleLine>>maxLineNum>>easySeqLine>>maxSeqLine;
    sq.addPassenger(1,10,10,"bob");
    sq.addPassenger(2,10,10,"alice");
    sq.popPassenger();
    Passenger p = sq.getFirstPassenger();
    cout<<p.id<<" "<<p.name<<" "<<p.arriveTime<<" "<<p.checkTime<<endl;
    cout<<sq.getNum()<<" "<<sq.getCustSingleLine()<<" "<<sq.getLineNum()<<endl;
    return 0;
}