#pragma once

class CInlineHook_x64
{
public:
	CInlineHook_x64(void);
	~CInlineHook_x64(void);

	unsigned char  m_szOldCode[255];       //存放原来API函数在内存中的前12个字节
	__int32        m_nOldCodeLen;

	//Hook15个字节,不影响寄存器
	bool InlineHook15(__int64 pHookAddr,__int64 pNewAddr,__int32 nCoveredCodeLen = 0);

private:
	//1. 远跳 不影响寄存器 + 15字节方法
	//push 函数低地址(8个字节)
	//mov qword ptr ss:[rsp + 4],函数高地址(8个字节,不过高4个字节一般都是0所以可以不用给)
	//ret
	//硬编码:
	//
	//68 XX XX XX XX						push LowAddress
	//48 C7 44 24 04 XX XX XX XX            mov qword ptr ss:[rsp + 4],HighAddress
	//C3	                                ret
#pragma pack(push)
#pragma pack(1)
	struct _x64LongJMP_15
	{
		unsigned char m_push;
		DWORD         m_dwLowAddress;
		unsigned char m_movrsp4[5];
		DWORD         m_dwHighAddress;
		unsigned char m_ret;
	};
#pragma pack(pop)

	//2.远跳 影响寄存器 + 12字节方法
	//这一种方法则会影响寄存器的值.
	//
	//原理: 利用 rax + jmp的方式进行跳转.
	//	mov rax,Address
	//	Jmp rax
	//	硬编码
	//	48 B8 XX XX XX XX XX XX XX XX FF E0 
#pragma pack(push)
#pragma pack(1)
	struct _x64LongJMP_12
	{
		__int64 m_nCode;
	};
#pragma pack(pop)
	//unsigned char shellcode_12[]= {0x68,0x00,0x00,0x00,0x00,0x48,0xC7,0x44,0x24,0x04,0x00,0x00,0x00,0x00,0xC3};

};