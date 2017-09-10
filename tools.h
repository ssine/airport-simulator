#ifndef TOOLS_H
#define TOOLS_H

#include<fstream>
int MinCheck;
int MaxCheck;
int MaxCustSingleLine;
int MaxLines;
int MaxSeqLen;
int EasySeqLen;
int MaxCustCheck;
int MaxSec;

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

void romdomWriteInputFile()
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

#endif
