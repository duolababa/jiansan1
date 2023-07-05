#pragma once
//#include "windows.h"
#include <atlstr.h>
#include <vector>
using namespace std;
//下列函数失败一定返回-100;
HANDLE 打开进程(int 进程ID);

//读内存函数
bool 读内存(HANDLE 进程句柄, LPVOID 要读取的内存地址,LPVOID 存放数据的内存地址,SIZE_T 要读取的长度);
int 读内存整数型(HANDLE 进程句柄, LPVOID 要读取的内存地址);
int 读内存整数型2(HANDLE 进程句柄, LPVOID 要读取的内存地址);

short 读内存短整数型(HANDLE 进程句柄, LPVOID 要读取的内存地址);
short 读内存短整数型2(HANDLE 进程句柄, LPVOID 要读取的内存地址);

long long 读内存长整数型(HANDLE 进程句柄, LPVOID 要读取的内存地址);
long long 读内存长整数型2(HANDLE 进程句柄, LPVOID 要读取的内存地址);

float 读内存小数型(HANDLE 进程句柄, LPVOID 要读取的内存地址);
float 读内存小数型2(HANDLE 进程句柄, LPVOID 要读取的内存地址);

double 读内存双精度小数型(HANDLE 进程句柄, LPVOID 要读取的内存地址);
double 读内存双精度小数型2(HANDLE 进程句柄, LPVOID 要读取的内存地址);

char 读内存字节型(HANDLE 进程句柄, LPVOID 要读取的内存地址);
char 读内存字节型2(HANDLE 进程句柄, LPVOID 要读取的内存地址);

int 读内存字节集(HANDLE 进程句柄, LPVOID 要读取的内存地址, int 要读取的长度, LPVOID outbuff);
int 读内存字节集2(HANDLE 进程句柄, LPVOID 要读取的内存地址, int 要读取的长度, LPVOID outbuff);

int 读内存文本型(HANDLE 进程句柄, LPVOID 要读取的内存地址, int 要读取的文本类型, TCHAR*(*outbuff)); //类型0为ASCII(代码页)或者UTF-8(普通文本)  类型1为Unicode
int 读内存文本型2(HANDLE 进程句柄, LPVOID 要读取的内存地址, int 要读取的文本类型, TCHAR*(*outbuff));

//写内存函数
bool 写内存(HANDLE 进程句柄, LPVOID 要写入的内存地址, LPVOID 要写入的数据所在地址,SIZE_T 要写入的长度);
bool 写内存整数型(HANDLE 进程句柄, LPVOID 要写入的内存地址, int wirtebuff);
bool 写内存整数型2(HANDLE 进程句柄, LPVOID 要写入的内存地址, int wirtebuff);

bool 写内存短整数型(HANDLE 进程句柄, LPVOID 要写入的内存地址, short wirtebuff);
bool 写内存短整数型2(HANDLE 进程句柄, LPVOID 要写入的内存地址, short wirtebuff);

bool 写内存长整数型(HANDLE 进程句柄, LPVOID 要写入的内存地址, long long wirtebuff);
bool 写内存长整数型2(HANDLE 进程句柄, LPVOID 要写入的内存地址, long long wirtebuff);

bool 写内存小数型(HANDLE 进程句柄, LPVOID 要写入的内存地址, float wirtebuff);
bool 写内存小数型2(HANDLE 进程句柄, LPVOID 要写入的内存地址, float wirtebuff);

bool 写内存双精度小数型(HANDLE 进程句柄, LPVOID 要写入的内存地址, double wirtebuff);
bool 写内存双精度小数型2(HANDLE 进程句柄, LPVOID 要写入的内存地址, double wirtebuff);

bool 写内存字节集(HANDLE 进程句柄, LPVOID 要写入的内存地址, LPVOID 要写入的数据所在地址, SIZE_T 要写入的长度);
bool 写内存字节集2(HANDLE 进程句柄, LPVOID 要写入的内存地址, LPVOID 要写入的数据所在地址, SIZE_T 要写入的长度);

bool 写内存字节型(HANDLE 进程句柄, LPVOID 要写入的内存地址, char wirtebuff);
bool 写内存字节型2(HANDLE 进程句柄, LPVOID 要写入的内存地址, char wirtebuff);

TCHAR* 读内存文本型3(HANDLE 进程句柄, LPVOID 要读取的内存地址, int 要读取的文本类型);
CString 取运行目录();
HANDLE 打开文件(LPCWSTR 文件全路径);
int 写文件(HANDLE 文件句柄, LPCVOID 要写入的数据所在地址, DWORD 要写入的字节数);
int 读文件(HANDLE 文件句柄, LPVOID 要读出的数据所在地址, DWORD 要读出的字节数);

void 开始保存恢复(void);
void 结束保存恢复(void);
void 保存编辑框(HWND 父窗句柄, int 编辑框控件ID);
LPVOID 申请内存2(HANDLE 进程句柄, int 要申请的内存大小);
bool 释放内存2(HANDLE 进程句柄, LPVOID 释放的地址, int 内存大小);
unsigned short 读内存无符号短整数型(HANDLE 进程句柄, LPVOID 要读取的内存地址);
unsigned short 读内存无符号短整数型2(HANDLE 进程句柄, LPVOID 要读取的内存地址);

bool 写内存无符号短整数型(HANDLE 进程句柄, LPVOID 要写入的内存地址, unsigned short wirtebuff);
bool 写内存无符号短整数型2(HANDLE 进程句柄, LPVOID 要写入的内存地址, unsigned short wirtebuff);

string Read(LPCWSTR filePath);
//void 设置线程退出(int en);