#pragma once
//#include "windows.h"
#include <atlstr.h>
#include <vector>
using namespace std;
//���к���ʧ��һ������-100;
HANDLE �򿪽���(int ����ID);

//���ڴ溯��
bool ���ڴ�(HANDLE ���̾��, LPVOID Ҫ��ȡ���ڴ��ַ,LPVOID ������ݵ��ڴ��ַ,SIZE_T Ҫ��ȡ�ĳ���);
int ���ڴ�������(HANDLE ���̾��, LPVOID Ҫ��ȡ���ڴ��ַ);
int ���ڴ�������2(HANDLE ���̾��, LPVOID Ҫ��ȡ���ڴ��ַ);

short ���ڴ��������(HANDLE ���̾��, LPVOID Ҫ��ȡ���ڴ��ַ);
short ���ڴ��������2(HANDLE ���̾��, LPVOID Ҫ��ȡ���ڴ��ַ);

long long ���ڴ泤������(HANDLE ���̾��, LPVOID Ҫ��ȡ���ڴ��ַ);
long long ���ڴ泤������2(HANDLE ���̾��, LPVOID Ҫ��ȡ���ڴ��ַ);

float ���ڴ�С����(HANDLE ���̾��, LPVOID Ҫ��ȡ���ڴ��ַ);
float ���ڴ�С����2(HANDLE ���̾��, LPVOID Ҫ��ȡ���ڴ��ַ);

double ���ڴ�˫����С����(HANDLE ���̾��, LPVOID Ҫ��ȡ���ڴ��ַ);
double ���ڴ�˫����С����2(HANDLE ���̾��, LPVOID Ҫ��ȡ���ڴ��ַ);

char ���ڴ��ֽ���(HANDLE ���̾��, LPVOID Ҫ��ȡ���ڴ��ַ);
char ���ڴ��ֽ���2(HANDLE ���̾��, LPVOID Ҫ��ȡ���ڴ��ַ);

int ���ڴ��ֽڼ�(HANDLE ���̾��, LPVOID Ҫ��ȡ���ڴ��ַ, int Ҫ��ȡ�ĳ���, LPVOID outbuff);
int ���ڴ��ֽڼ�2(HANDLE ���̾��, LPVOID Ҫ��ȡ���ڴ��ַ, int Ҫ��ȡ�ĳ���, LPVOID outbuff);

int ���ڴ��ı���(HANDLE ���̾��, LPVOID Ҫ��ȡ���ڴ��ַ, int Ҫ��ȡ���ı�����, TCHAR*(*outbuff)); //����0ΪASCII(����ҳ)����UTF-8(��ͨ�ı�)  ����1ΪUnicode
int ���ڴ��ı���2(HANDLE ���̾��, LPVOID Ҫ��ȡ���ڴ��ַ, int Ҫ��ȡ���ı�����, TCHAR*(*outbuff));

//д�ڴ溯��
bool д�ڴ�(HANDLE ���̾��, LPVOID Ҫд����ڴ��ַ, LPVOID Ҫд����������ڵ�ַ,SIZE_T Ҫд��ĳ���);
bool д�ڴ�������(HANDLE ���̾��, LPVOID Ҫд����ڴ��ַ, int wirtebuff);
bool д�ڴ�������2(HANDLE ���̾��, LPVOID Ҫд����ڴ��ַ, int wirtebuff);

bool д�ڴ��������(HANDLE ���̾��, LPVOID Ҫд����ڴ��ַ, short wirtebuff);
bool д�ڴ��������2(HANDLE ���̾��, LPVOID Ҫд����ڴ��ַ, short wirtebuff);

bool д�ڴ泤������(HANDLE ���̾��, LPVOID Ҫд����ڴ��ַ, long long wirtebuff);
bool д�ڴ泤������2(HANDLE ���̾��, LPVOID Ҫд����ڴ��ַ, long long wirtebuff);

bool д�ڴ�С����(HANDLE ���̾��, LPVOID Ҫд����ڴ��ַ, float wirtebuff);
bool д�ڴ�С����2(HANDLE ���̾��, LPVOID Ҫд����ڴ��ַ, float wirtebuff);

bool д�ڴ�˫����С����(HANDLE ���̾��, LPVOID Ҫд����ڴ��ַ, double wirtebuff);
bool д�ڴ�˫����С����2(HANDLE ���̾��, LPVOID Ҫд����ڴ��ַ, double wirtebuff);

bool д�ڴ��ֽڼ�(HANDLE ���̾��, LPVOID Ҫд����ڴ��ַ, LPVOID Ҫд����������ڵ�ַ, SIZE_T Ҫд��ĳ���);
bool д�ڴ��ֽڼ�2(HANDLE ���̾��, LPVOID Ҫд����ڴ��ַ, LPVOID Ҫд����������ڵ�ַ, SIZE_T Ҫд��ĳ���);

bool д�ڴ��ֽ���(HANDLE ���̾��, LPVOID Ҫд����ڴ��ַ, char wirtebuff);
bool д�ڴ��ֽ���2(HANDLE ���̾��, LPVOID Ҫд����ڴ��ַ, char wirtebuff);

TCHAR* ���ڴ��ı���3(HANDLE ���̾��, LPVOID Ҫ��ȡ���ڴ��ַ, int Ҫ��ȡ���ı�����);
CString ȡ����Ŀ¼();
HANDLE ���ļ�(LPCWSTR �ļ�ȫ·��);
int д�ļ�(HANDLE �ļ����, LPCVOID Ҫд����������ڵ�ַ, DWORD Ҫд����ֽ���);
int ���ļ�(HANDLE �ļ����, LPVOID Ҫ�������������ڵ�ַ, DWORD Ҫ�������ֽ���);

void ��ʼ����ָ�(void);
void ��������ָ�(void);
void ����༭��(HWND �������, int �༭��ؼ�ID);
LPVOID �����ڴ�2(HANDLE ���̾��, int Ҫ������ڴ��С);
bool �ͷ��ڴ�2(HANDLE ���̾��, LPVOID �ͷŵĵ�ַ, int �ڴ��С);
unsigned short ���ڴ��޷��Ŷ�������(HANDLE ���̾��, LPVOID Ҫ��ȡ���ڴ��ַ);
unsigned short ���ڴ��޷��Ŷ�������2(HANDLE ���̾��, LPVOID Ҫ��ȡ���ڴ��ַ);

bool д�ڴ��޷��Ŷ�������(HANDLE ���̾��, LPVOID Ҫд����ڴ��ַ, unsigned short wirtebuff);
bool д�ڴ��޷��Ŷ�������2(HANDLE ���̾��, LPVOID Ҫд����ڴ��ַ, unsigned short wirtebuff);

string Read(LPCWSTR filePath);
//void �����߳��˳�(int en);