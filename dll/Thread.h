#pragma once

typedef struct _THREAD_TIMER_EMU_CTX_
{
	HANDLE hTimer;
	HANDLE hTimerQueue;
	LPVOID Context;
	LPTHREAD_START_ROUTINE Routine;
}TTEMU, * PTTEMU;

class CXThread
{
public:
	enum { Terminate, Running, Suspend };
	CXThread();
	~CXThread();
	BOOL Start(DWORD DueTime = 0, PVOID Context = NULL);
	void Stop() { m_nState = Terminate; }
	int GetState() { return m_nState; }
	void SetState(int state) { m_nState = state; }
	virtual BOOL Run() = 0;
	static VOID CALLBACK ThreadProc(PVOID lpParam, BOOLEAN TimerOrWaitFired);

public:
	PTTEMU m_pCtx;
	int m_nState;

};


//CXThread CMyThread2;