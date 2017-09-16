#ifndef SerpQueue_H
#define SerpQueue_H

#include "queue.h"

class SerpQueue : public Queue {
public:
    SerpQueue():custSingleLine{0}, lineNum{2} {}
    int getCustSingleLine();
    int getLineNum();
    bool isFull();
	bool isclosed();
	void shut();
private:
    int custSingleLine, lineNum;
	bool closed=false;
};

#endif 