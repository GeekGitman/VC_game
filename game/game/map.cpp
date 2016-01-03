#include "StdAfx.h"
#include "map.h"

using namespace std;

void map::COPY(char*p){
	string copypath(p);
	CFileFind finder;
	if(finder.FindFile(CString("./reshow/")+CString(p)+CString(".re")) && ISREWRITE==false )  //文件存在且不复写
		return;
	point buf;
	ofstream outf("./reshow/"+copypath+".re");
	outf<<V<<" "<<H<<endl;
	ifstream in("./start/start.buf");
	string x;
	for(int i=0;i<H*V;i++){
		in>>x;
		outf<<x<<" ";
	}
	outf<<endl;
	in.close();
	for(int i=0;i<(int)MAP_BACK.size();i++){
		buf=MAP_BACK.at(i);
		outf<<buf.x<<" "<<buf.y<<endl;
	}
	outf.close();
}

map::map(){
	STEP=0;
	MAP_BACK.clear();
	POINTER.clear();
	STEPBACK=0;
	BACKTOTAL=0;
	COPYSET=false;
	MAP=NULL;
	H=0;V=0;
	ISREWRITE=false;
}

map::map(int m,int n){
	MAP=NULL;
	H=m;V=n;
	MAP=new int*[m];
	for(int i=0;i<m;i++){
		MAP[i]=new int[n];
		for(int j=0;j<n;j++){
			MAP[i][j]=0;
		}
	}
	srand((unsigned int)time(NULL));
	for(int i=0;i<15;i++){
		int mm=rand()%H;
		int nn=rand()%V;
		NEXT(mm,nn,"");
	}
	ofstream out("./start/start.buf");
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			out<<MAP[i][j]<<" ";
		}
	}
	out.close();
	STEP=0;
	STEPBACK=0;
	BACKTOTAL=0;
	COPYSET=false;
	MAP_BACK.clear();
	POINTER.clear();
	ISREWRITE=false;
}

map::map(int size){
	MAP=NULL;
	H=size;V=size;
	MAP=new int*[size];
	for(int i=0;i<size;i++){
		MAP[i]=new int[size];
	}
	if(size==3){
		MAP[0][0]=0;MAP[0][1]=1;MAP[0][2]=1;
		MAP[1][0]=1;MAP[1][1]=1;MAP[1][2]=0;
		MAP[2][0]=0;MAP[2][1]=1;MAP[2][2]=0;
	}
	else if(size==4){
		MAP[0][0]=1;MAP[0][1]=1;MAP[0][2]=0;MAP[0][3]=0;
		MAP[1][0]=1;MAP[1][1]=1;MAP[1][2]=0;MAP[0][1]=1;
		MAP[2][0]=1;MAP[2][1]=1;MAP[2][2]=0;MAP[2][3]=0;
		MAP[3][0]=0;MAP[3][1]=1;MAP[3][2]=1;MAP[3][3]=0;
	}
	else{
		MAP[0][0]=1;MAP[0][1]=1;MAP[0][2]=0;MAP[0][3]=1;MAP[0][4]=1;
		MAP[1][0]=1;MAP[1][1]=0;MAP[1][2]=1;MAP[0][1]=0;MAP[0][2]=1;
		MAP[2][0]=0;MAP[2][1]=1;MAP[2][2]=1;MAP[2][3]=1;MAP[2][4]=0;
		MAP[3][0]=1;MAP[3][1]=0;MAP[3][2]=1;MAP[3][3]=0;MAP[3][4]=1;
		MAP[4][0]=1;MAP[4][1]=1;MAP[4][2]=0;MAP[4][3]=1;MAP[4][4]=1;
	}
	STEP=0;
	STEPBACK=0;
	BACKTOTAL=0;
	COPYSET=false;
	MAP_BACK.clear();
	POINTER.clear();
	ISREWRITE=false;
	ofstream out("./start/start.buf");
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			out<<MAP[i][j]<<" ";
		}
	}
	out.close();
}

bool map::ISWIN(){
	int sum=0;
	for(int i=0;i<H;i++){
		for(int j=0;j<V;j++){
			sum+=MAP[i][j];
		}
	}
	if(sum==0) return true;
	else return false;
}

bool map::LOAD(char* map){
	ifstream in;
	in.open(map);
	if(!in) return false;
	in>>H>>V;
	MAP=NULL;
	MAP=new int*[H];
	for(int i=0;i<H;i++){
		MAP[i]=new int[V];
		for(int j=0;j<V;j++){
			in>>MAP[i][j];
		}
	}
	STEP=0;
	STEPBACK=0;
	BACKTOTAL=0;
	COPYSET=false;
	MAP_BACK.clear();
	POINTER.clear();
	ISREWRITE=false;
	in.close();
	ofstream out("./start/start.buf");
	for(int i=0;i<H;i++){
		for(int j=0;j<V;j++){
			out<<MAP[i][j]<<" ";
		}
	}
	out.close();
	return true;
}

bool map::NEXT(int mt,int nt,char* p){     //这里的mt和nt都是从0开始的
	MAP[mt][nt] = MAP[mt][nt]==0 ? 1:0 ;
	if(mt>0)
		MAP[mt-1][nt] = MAP[mt-1][nt]==0 ? 1:0 ;
	if(mt<H-1)
		MAP[mt+1][nt] = MAP[mt+1][nt]==0 ? 1:0 ;
	if(nt>0)
		MAP[mt][nt-1] = MAP[mt][nt-1]==0 ? 1:0 ;
	if(nt<V-1)
		MAP[mt][nt+1] = MAP[mt][nt+1]==0 ? 1:0 ;
	STEP++;
	point t;t.x=mt;t.y=nt;
	MAP_BACK.push_back(t);
	POINTER.push_back(t);
	STEPBACK=0;
	bool win=ISWIN();
	if(win){
		if(COPYSET==true)
		    COPY(p);
		return true;
	}
	else return false;
}

bool map::PRESTEP(){
	if(STEP<=0 || STEPBACK>=2) return false;
	STEP--;
	point t=POINTER.at(STEP);
	int mt=t.x; int nt=t.y;
	MAP[mt][nt] = MAP[mt][nt]==0 ? 1:0 ;
	if(mt>0)
		MAP[mt-1][nt] = MAP[mt-1][nt]==0 ? 1:0 ;
	if(mt<H-1)
		MAP[mt+1][nt] = MAP[mt+1][nt]==0 ? 1:0 ;
	if(nt>0)
		MAP[mt][nt-1] = MAP[mt][nt-1]==0 ? 1:0 ;
	if(nt<V-1)
		MAP[mt][nt+1] = MAP[mt][nt+1]==0 ? 1:0 ;
	POINTER.pop_back();
	point s; s.x=mt; s.y=nt;
	MAP_BACK.push_back(s);
	STEPBACK++;
	BACKTOTAL++;
	return true;
}

bool map::RELOAD(){
	if(MAP==NULL) return false;
	ifstream in("./start/start.buf");
	for(int i=0;i<H;i++){
		for(int j=0;j<V;j++){
			in>>MAP[i][j];
		}
	}
	STEP=0;
	STEPBACK=0;
	BACKTOTAL=0;
	MAP_BACK.clear();
	POINTER.clear();
	in.close();
	return true;
}

bool map::SAVE(char* path,int mode){
	CString p(path); CString p1("./maps/"); CString p2(".gmap");
	p=p1+p+p2;;
	CFileFind finder;
	if(finder.FindFile(p) && mode==0 )  //文件存在且不复写
		return false;
	ofstream out(p);
	if(!p) return false;
	out<<H<<" "<<V<<endl;
	for(int i=0;i<H;i++){
		for(int j=0;j<V;j++){
			out<<MAP[i][j]<<" ";
		}
		out<<endl;
	}
	out.close();
	return true;
}

void map::SETCOPY(bool set,bool isrewrite){
	if(set==true){
		COPYSET=true;
		ISREWRITE=isrewrite;
	}
	else
		COPYSET=false;
}

int** map::THISMAP(){
	return MAP;
}

int map::THISSTEP(){
	return STEP;
}

int* map::THISSIZE(){
	int size[2];
	size[0]=H;
	size[1]=V;
	return size;
}

bool map::LOADRESHOW(char* path){
	string p(path);
	ifstream in;
	in.open(p);
	if(!in) return false;
	in>>H>>V;
	MAP=NULL;
	MAP=new int*[H];
	for(int i=0;i<H;i++){
		MAP[i]=new int[V];
		for(int j=0;j<V;j++){
			in>>MAP[i][j];
		}
	}
	STEP=0;
	STEPBACK=0;
	BACKTOTAL=0;
	COPYSET=false;
	MAP_BACK.clear();
	POINTER.clear();
	ISREWRITE=false;
	while(!in.eof()){
		point t;
		in>>t.y>>t.x;
		MAP_BACK.push_back(t);
		POINTER.push_back(t);
	}
	in.close();
	return true;
}

bool map::HASRESHOWNEXT(){
	if(MAP_BACK.size()>0 && POINTER.size()>0 && (!ISWIN()))
		return true;
	else return false;
}

point* map::RESHOWNEXT(){
	if(!HASRESHOWNEXT()) return NULL;
	int i=POINTER.size()-MAP_BACK.size();
	point r=POINTER.at(i);
	MAP_BACK.pop_back();
	//
	int mt=r.y;int nt=r.x;
	MAP[mt][nt] = MAP[mt][nt]==0 ? 1:0 ;
	if(mt>0)
		MAP[mt-1][nt] = MAP[mt-1][nt]==0 ? 1:0 ;
	if(mt<H-1)
		MAP[mt+1][nt] = MAP[mt+1][nt]==0 ? 1:0 ;
	if(nt>0)
		MAP[mt][nt-1] = MAP[mt][nt-1]==0 ? 1:0 ;
	if(nt<V-1)
		MAP[mt][nt+1] = MAP[mt][nt+1]==0 ? 1:0 ;
	STEP++;
	//
	return &r;
}