#ifndef _MAP_
#define _MAP_
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <string>
using namespace std;

struct point {
	int x;
	int y;
};

class map{
private:
	int V;       //x方向有几个格子
	int H;       //y方向有几个格子
	int STEP;
	int STEPBACK;
	int BACKTOTAL;
	bool ISREWRITE;
	char* COPYPATH;
	bool COPYSET;
	vector<point> MAP_BACK;
	vector<point> POINTER;
	int** MAP;
	bool ISWIN();
	//void COPY();
public:
	void COPY(char* p);
	map(int m,int n);
	map(int size);
	map();
	bool LOAD(char* map);
	bool SAVE(char* path,int mode);
	bool NEXT(int mt,int nt,char*p);    //mt从0开始
	bool PRESTEP();
	bool RELOAD();
	void SETCOPY(bool set,bool isrewrite);
	int** THISMAP();
	int THISSTEP();
	int* THISSIZE();
	//一下是复盘所需函数
	bool LOADRESHOW(char* path);
	bool HASRESHOWNEXT();
	point* RESHOWNEXT();
};

#endif