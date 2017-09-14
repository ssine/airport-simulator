#include "stdafx.h"
#include <ctime>
#include <iostream>
#include <string>
#include <fstream>
#include "checkpoint.h"
#include "serpqueue.h"
#include "struct.h"
#include "globalvar.h"
#include <Windows.h>
extern time_t t_unit;

time_t getTime()
{
    return clock()/t_unit;
}

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

void writeLogFile(std::string s)
{
    std::fstream fout("Log.txt",std::ios::app);
    fout<<s;
}

int distribution(CheckPoint* CheckP[])
{
    for(int i=0;i<MaxCheck;i++)
    {
        if(CheckP[i]->getState()==onDuty&&!CheckP[i]->isFull())
        {
            return i;
        }
    }
    return -1;
}

void refreshCheckPoint(CheckPoint* CheckP[])
{
    for(int i=0;i<MaxCheck;i++)
        if(CheckP[i]->getState()==onDuty)
            {
                CheckP[i]->refreshNum();
            }
		else if(CheckP[i]->getState()==pause)
		{
			CheckP[i]->nextPopTime += t_unit;
		}
}

//开放或关闭窗口 1开-1关0不动
int whetherSwitchCheckPoint(SerpQueue &SerpQ, const int nowCheckNum)
{
	int num = SerpQ.getNum() / nowCheckNum;
	if (num>MaxCheck)
		return 1;
	if (num<EasySeqLen)
		return -1;
	return 0;
}

int getCheckNum(CheckPoint* CheckP[])
{
	int num = 0;
	for (int i = 0; i<MaxCheck; i++)
	{
		if (CheckP[i]->getState() == onDuty)
			num++;
	}
	return num;
}

void makeSwitchCheckPoint(CheckPoint* CheckP[], int op)
{
	if (op == 1)
	{
		for (int i = MinCheck - 1; i<MaxCheck; i++)
		{
			if (CheckP[i]->getState() == closed)
			{
				CheckP[i]->start();
				//cout << i << "is start" << endl;
				return;
			}
		}
	}
	if (op == -1)
	{
		for (int i = MaxCheck - 1; i >= MinCheck; i--)
		{
			if (CheckP[i]->getState() == onDuty)
			{
				CheckP[i]->shut();
				//cout << i << "is shut" << endl;
				return;
			}
		}
	}
	return;
}

void programEnd(CheckPoint* CheckP[])
{
	for (int i = 0; i<MaxCheck; i++)
	{
		CheckP[i]->shut();
	}
	int sum = 0;
	while (true)
	{
		for (int i = 0; i<MaxCheck; i++)
		{
			sum += CheckP[i]->getNum();
		}
		if (!sum)
			exit(0);
		Sleep(t_unit);
	}
}