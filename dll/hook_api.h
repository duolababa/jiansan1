#pragma once

class hook_api
{
public:
	static void hookNtCursorPos(BOOL isHook);
};

//LONG WINAPI ExceptionFilter(PEXCEPTION_POINTERS ExceptionInfo);
//void SetSehHook();
DWORD NTAPI ExceptionHandler(PEXCEPTION_POINTERS pExceptionInfo);
DWORD WINAPI SetHardwareBreakPointWIN10Version(DWORD TreadId);
DWORD WINAPI SetHardwareBreakPointoffWIN10Version(DWORD TreadId);