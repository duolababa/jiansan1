#include "pch.h"
#include "InlineHook_x64.h"
//Inline Hook

CInlineHook_x64::CInlineHook_x64(void)
{
	ZeroMemory(m_szOldCode,255);
	m_nOldCodeLen = 0;
}

CInlineHook_x64::~CInlineHook_x64(void)
{

}

//pHookAddr = Hook地址
//pNewAddr  = 跳转地址
//nCoveredCodeLen = 被覆盖的指令长度(Hook最少15个字节,如果超过了,则需要按照被覆盖的指令长度进行COPY)
bool CInlineHook_x64::InlineHook15( __int64 pHookAddr,__int64 pNewAddr,__int32 nCoveredCodeLen)
{
	TCHAR msg[MAX_PATH] = {0};
	__int32 nHookLen = sizeof(_x64LongJMP_15);
	DWORD OldProtect;
	_x64LongJMP_15* pLongJMP = NULL;
	//定义shellcode
	unsigned char shellcode_15[]= {0x68,0x00,0x00,0x00,0x00,0x48,0xC7,0x44,0x24,0x04,0x00,0x00,0x00,0x00,0xC3};


	//_stprintf(msg,_T("[x64InlineHook15]:pHookAddr=%p pNewAddr=%p"), pHookAddr, pNewAddr);
	//OutputDebugString(msg);

	nCoveredCodeLen = nCoveredCodeLen<nHookLen?nHookLen:nCoveredCodeLen;
	m_nOldCodeLen = nCoveredCodeLen;

	//_stprintf(msg,_T("[x64InlineHook15]:pHookAddr=%p nHookLen=%d"), pHookAddr, nHookLen);
	//OutputDebugString(msg);

	// 修改页面保护
	if (::VirtualProtectEx(GetCurrentProcess(),(LPVOID)pHookAddr, nHookLen, PAGE_EXECUTE_READWRITE, &OldProtect)==0)
	{
		//_stprintf(msg,_T("[x64InlineHook15]:VirtualProtect Error=%08X(%d)"),GetLastError(),GetLastError());
		//OutputDebugString(msg);

		return false;
	}
	// 得到原始指令
	memcpy(m_szOldCode,(LPVOID)pHookAddr, nCoveredCodeLen);

	// 构造代码
	pLongJMP = (_x64LongJMP_15*)shellcode_15;
	pLongJMP->m_dwLowAddress = (DWORD)(pNewAddr&0xFFFFFFFF);
	pLongJMP->m_dwHighAddress = (DWORD)((pNewAddr>>32)&0xFFFFFFFF);
	
	// 填充Shellcode
	memcpy((LPVOID)pHookAddr,pLongJMP,nHookLen);

	return true;
}