#include "pch.h"
#include "Thread.h"

CXThread::CXThread()
	: m_pCtx(0), m_nState(Terminate)
{

}

CXThread::~CXThread()
{

}

VOID CALLBACK CXThread::ThreadProc(PVOID lpParam, BOOLEAN TimerOrWaitFired)
{
	CXThread* pThread = reinterpret_cast<CXThread*>(lpParam);
	PTTEMU pCtx = pThread->m_pCtx;
	if (pCtx)
	{
		pThread->m_nState = Running;
		pThread->Run();
		CloseHandle(pCtx->hTimer);
		DeleteTimerQueue(pCtx->hTimerQueue);
		delete pCtx;
		pThread->m_nState = Terminate;
	}
}

BOOL CXThread::Start(DWORD DueTime, PVOID Context)
{
	HANDLE hTimerQueue = NULL;
	hTimerQueue = CreateTimerQueue();
	if (NULL == hTimerQueue)
	{
		return FALSE;
	}
	m_pCtx = new TTEMU;
	m_pCtx->hTimer = NULL;	//¾ä±ú
	m_pCtx->hTimerQueue = hTimerQueue;
	//m_pCtx->Routine = Routine;
	m_pCtx->Context = Context;
	m_nState = Suspend;
	if (!CreateTimerQueueTimer(&m_pCtx->hTimer, hTimerQueue,
		(WAITORTIMERCALLBACK)ThreadProc, this, DueTime, 0, WT_EXECUTEONLYONCE))
	{
		DeleteTimerQueue(hTimerQueue);
		delete m_pCtx;
		m_nState = Terminate;
		return FALSE;
	}

	return TRUE;
}


//BOOL CXThread::Run()
//{
//	
//
//}
