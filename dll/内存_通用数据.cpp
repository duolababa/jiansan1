#include "内存_通用数据.h"
DWORD getResIndexByName(CString cName)
{
	INT64 dListAddr = R_QW(游戏模块 + gb_ResBase);
	DWORD dStartOffest = go_Res_dtotal + 4;//0x94; D8 0225
	DWORD dArraySize = 0x14;
	long dtotal = R_DW(dListAddr + dStartOffest + 0x10 + 0x18);
	INT64 dKeyAddr = R_QW(dListAddr + dStartOffest + 0x20);
	if (!dKeyAddr)
	{
		dKeyAddr = dListAddr + dStartOffest + 0x10;
	}
	INT64 objStartAddr = R_QW(dListAddr + dStartOffest);
	for (DWORD i = 0; i < dtotal; i++)
	{
		long dKeyValue = R_DW(dKeyAddr + (i / 0x20) * 4);
		DWORD dNum = i % 0x20;
		DWORD dCheck = (dKeyValue >> dNum) & 1;
		if (dCheck)
		{
			DWORD dId = R_DW(objStartAddr + i * dArraySize);
			if (dId && dId != 0xFFFFFFFF)
			{
				INT64 dObj = R_QW(objStartAddr + i * dArraySize + 4);
				if (dObj)
				{
					INT64 dClassAddr = R_QW(dObj);
					INT64 dStrFunAddr = R_QW(dClassAddr + 0x10);
					INT64 dStrAddr = R_DW(dStrFunAddr + 1 + 2) + dStrFunAddr + 5 + 2;
					CString cStr = R_CString(dStrAddr);
					if (cStr.Compare(cName) == 0)
					{
						return dId;
					}
				}
			}
		}
	}
	return 0;
}
INT64 getResAddrById(DWORD dResTypeIndex)
{
	//INT64 gb_ResBase = 0x141e243f0;
	INT64 addr_1 = R_QW(游戏模块 + gb_ResBase);
	INT64 dResAddr = 0;//技能快捷键UI是索引0 骑马的是索引4
	long dtotal = R_DW(addr_1 + go_Res_dtotal);
	INT64 objStartAddr = R_QW(addr_1 + go_Res_dtotal - 0x44);//对象数组地址
	INT64 indexStartAddr = R_QW(addr_1 + go_Res_dtotal - 0x44 + 0x3C);//索引数组地址
	for (long i = 0; i < dtotal; i++)
	{
		if (dResAddr)
		{
			break;
		}
		long dIndex = R_DW(indexStartAddr + i * 4);
		if (dIndex != 0xFFFFFFFF)
		{
			long dOffest = dIndex * 5 * 4;
			INT64 dObjAddr = R_QW(objStartAddr + dOffest + 4);
			if (dResTypeIndex == R_DW(objStartAddr + dOffest))//读4四字节
			{
				dResAddr = dObjAddr;
				break;
			}
			DWORD dNextIndex = 0;
			while (1)
			{
				dNextIndex = R_DW(objStartAddr + dOffest + 0xC);
				if (dNextIndex == 0xFFFFFFFF)//为-1跳出循环
				{
					break;
				}
				else
				{
					dOffest = dNextIndex * 5 * 4;
					dObjAddr = R_QW(objStartAddr + dOffest + 4);
					if (dResTypeIndex == R_DW(objStartAddr + dOffest))
					{
						dResAddr = dObjAddr;
						break;
					}
				}
			}
		}
	}
	return dResAddr;
}
INT64 getResAddrByTypeId(DWORD dResTypeIndex, DWORD dResId, DWORD dStartOffest, DWORD dNextOffest, DWORD dArraySize)
{
	////MyTrace(L"dResTypeIndex %d", dResTypeIndex);
	INT64 dResAddr = getResAddrById(dResTypeIndex);
	////MyTrace(L"地址0x%I64X \r\n", dResAddr);
	long dtotal = R_DW(dResAddr + dStartOffest + 0x44);
	DWORD dHash = dResId & (dtotal - 1);
	INT64 objStartAddr = R_QW(dResAddr + dStartOffest);//对象数组地址
	INT64 indexStartAddr = R_QW(dResAddr + dStartOffest + 0x3C);//索引数组地址
	INT64 dIndex = R_DW(indexStartAddr + dHash * 4);
	DWORD dOffest = dIndex * dArraySize;
	INT64 dObjAddr = R_QW(objStartAddr + dOffest + 4);
	if (dResId == R_DW(objStartAddr + dOffest))
	{
		return R_QW(dObjAddr + 4);
	}
	else
	{
		DWORD dNextIndex = 0;
		while (1)
		{
			dNextIndex = R_DW(objStartAddr + dOffest + dNextOffest);
			if (dNextIndex == 0xFFFFFFFF)//为-1跳出循环
			{
				break;
			}
			else
			{
				dOffest = dNextIndex * dArraySize;
				dObjAddr = R_QW(objStartAddr + dOffest + 4);
				if (dResId == R_DW(objStartAddr + dOffest))
				{
					// //MyTrace(L"地址0x%I64X \r\n",dObjAddr); 
					return R_QW(dObjAddr + 4);
				}
			}
		}
	}
	return 0;
}
INT64 getNpcResAddrById(DWORD dResId)
{
	return getResAddrByTypeId(getResIndexByName(L"Npc"), dResId, 0x68, 0x4C, 0x54);
}
INT64 getItemResAddrById(DWORD dResId)
{
	return getResAddrByTypeId(getResIndexByName(L"Item"), dResId, 0x68, 0x4C, 0x54);
}
INT64 getSquareResAddrById(DWORD dResId)
{
	return getResAddrByTypeId(getResIndexByName(L"Prop"), dResId, 0x68, 0x4C, 0x54);
}
INT64 getMapResAddrById(DWORD dResId)
{
	return getResAddrByTypeId(getResIndexByName(L"ZoneBase"), dResId, 0x68, 0x4C, 0x54);
}
INT64 getVehicleResAddrById(DWORD dResId)
{
	return getResAddrByTypeId(getResIndexByName(L"Vehicle"), dResId, 0x68, 0x4C, 0x54);
}
INT64 getShipResAddrById(DWORD dResId)//船资源
{
	return getResAddrByTypeId(getResIndexByName(L"VoyageShip"), dResId, 0x68, 0x4C, 0x54);
}
INT64 getCrewResAddrById(DWORD dResId)//船员资源
{
	return getResAddrByTypeId(getResIndexByName(L"VoyageCrew"), dResId, 0x68, 0x4C, 0x54);
}
BYTE getItemBoxType(int dItemResId)
{
	INT64 dAddr = getResAddrByTypeId(getResIndexByName(L"RandomBoxBase"), dItemResId, 0x68, 0x4C, 0x54);
	if (dAddr)
	{
		return R_BYTE(dAddr + 0x10);
	}
	return 0;
}
bool HEX2STR(char* psrc, int srclen, char* pdst, int dstlen, bool bspace = false)
{
	int bytesize = 2 + (int)bspace;

	if (dstlen < srclen * bytesize)
		return false;

	for (int i = 0; i < srclen; i++)
		sprintf(pdst + i * bytesize, "%02X", (BYTE)psrc[i]);

	if (bspace)
	{
		for (int i = 0; i < srclen - 1; i++)
			pdst[i * bytesize + 2] = 0x20;
	}

	return true;
}
//char* UnicodeToAnsi(const wchar_t* szStr)
//{
//	int nLen = WideCharToMultiByte(CP_ACP, 0, szStr, -1, NULL, 0, NULL, NULL);
//	if (nLen == 0)
//	{
//		return NULL;
//	}
//	char* pResult = new char[nLen];
//	WideCharToMultiByte(CP_ACP, 0, szStr, -1, pResult, nLen, NULL, NULL);
//	return pResult;
//	return pResult;
//}
CString GetName(INT64 dNameAddr)
{
	CString Name = L"空";
	if (!dNameAddr) return Name;
	char* sName = NULL;
	sName = new char[400 * 2];
	读内存字节集(HANDLE(-1), LPVOID(dNameAddr), 400, sName);
	char* dName;
	HEX2STR(sName, strlen(sName), dName, strlen(sName) * 2);
	DbgPrintf_Mine("%s", dName);
	return L" ";
	//string SSname = sName;
	Name = CString(sName);
	//memcpy((void*)Name.GetBuffer(), (void*)(dNameAddr), 400);
	//Name = dm.ReadDataAddr( dNameAddr, 400);
	BYTE m_code[1000] = { 0 };
	Name.Remove(' ');
	DWORD count = 0;
	for (int i = 0; i < Name.GetLength(); i = i + 2)
	{
		m_code[count] = (BYTE)::wcstol(Name.Mid(i, 2), NULL, 16);
		if (count)
		{
			if ((count & 1) && m_code[count] == 0 && m_code[count - 1] == 0)
			{
				break;
			}
		}
		count++;
	}
	WORD dUCode = 0;
	for (int k = 0; k < count / 2; k++)
	{
		dUCode = *(WORD*)(m_code + k * 2);
		////MyTrace(L"%X",dUCode);
		if (dUCode > 0xAC00 && dUCode < 0xE000)
		{
			continue;//韩文部分 不做处理
		}
		if (dUCode >= 0xE000 && dUCode < 0xFF00)
		{
			dUCode = dUCode - 0x8000;
			*(WORD*)(m_code + k * 2) = dUCode;
		}
		if (dUCode >= 0xE00 && dUCode < 0x4E00)
		{
			if (dUCode >= 0x2000 && dUCode <= 0x3100)
			{
				continue;//跳过中文符号

			}

			dUCode = dUCode + 0x4000;
			*(WORD*)(m_code + k * 2) = dUCode;
		}
	}

	Name.Format(L"%s", (wchar_t*)m_code);
	return Name;
}

DWORD getEncryValue(INT64 dAttrAddr, DWORD dIndex)
{
	dAttrAddr = dAttrAddr + 0x34;//dump 00000000DA4A4700+30 + 24c+1
	BYTE dKeyIndex = R_BYTE(dAttrAddr + 0x510 + dIndex);
	if (R_DW(dAttrAddr + 0x5A8) == 1)
	{
		dKeyIndex = 0;
	}
	DWORD dEncryValue = R_DW(dAttrAddr + 0x50 + dIndex * 8);
	DWORD dKeyValue = R_DW(dAttrAddr + dKeyIndex * 8);
	DWORD dCurValue = dEncryValue ^ dKeyValue;
	////MyTrace(L"dKeyIndex %d  dEncryValue %d dKeyValue %d \r\n", dKeyIndex, dEncryValue, dKeyValue);
	return dCurValue;
}

INT64 getAttrAddr(DWORD dId)//内存_环境_取属性对象
{
	INT64 count = 0;
	////MyTrace(L"getAttrAddr ID %d", dId);
	//INT64 gb_AttrList = 0x141e46ca0;//0x141687b40;
	INT64 addr_1 = R_QW(游戏模块 + gb_AttrList);
	DWORD dtotal = R_DW(addr_1 + 0xE0);
	INT64 objStartAddr = R_QW(addr_1 + 0x9C);//对象数组地址
	INT64 indexStartAddr = R_QW(addr_1 + 0xD8);//索引数组地址
	for (long i = 0; i < dtotal; i++)
	{
		long dIndex = R_DW(indexStartAddr + i * 4);
		if (dIndex != 0xFFFFFFFF)
		{
			long dOffest = dIndex * 3 * 8;
			INT64 dObjAddr = R_QW(objStartAddr + dOffest + 8);
			if (R_DW(objStartAddr + dOffest) == dId)
			{
				return dObjAddr;
			}
			DWORD dNextIndex = 0;
			while (1)
			{
				if (count >= 30000)
				{
					break;
				}
				dNextIndex = R_DW(objStartAddr + dOffest + 0x10);
				if (dNextIndex == 0xFFFFFFFF)//为-1跳出循环
				{
					break;
				}
				else
				{
					dOffest = dNextIndex * 3 * 8;
					dObjAddr = R_QW(objStartAddr + dOffest + 8);
					if (R_DW(objStartAddr + dOffest) == dId)
					{
						return dObjAddr;
					}
				}
				count = count + 1;
			}
		}
	}
	return 0;
}

int 距离计算2(坐标_ 源坐标, 坐标_ 目的坐标)
{
	float x = 源坐标.x - 目的坐标.x;
	float y = 源坐标.y - 目的坐标.y;
	float z = 源坐标.z - 目的坐标.z;
	return int(sqrtf(x * x + y * y + z * z));
}
int 距离计算(int x1, int y1, int z1, int x2, int y2, int z2)
{
	float x = x1 - x2;
	float y = y1 - y2;
	float z = z1 - z2;
	return int(sqrtf(float(x * x + y * y + z * z)));
}
float 距离计算3(float x1, float y1, float z1, float x2, float y2, float z2)
{
	float x = x1 - x2;
	float y = y1 - y2;
	float z = z1 - z2;
	return sqrtf(float(x * x + y * y + z * z));
}
float  GetDis(float X1, float Y1, float Z1)
{

	坐标_ 本人坐标 = 本人::取坐标();

	float x = 本人坐标.x - X1;
	float y = 本人坐标.y - Y1;
	float z = 本人坐标.z - Z1;
	return sqrtf(float(x * x + y * y + z * z));
}

float  GetDis1(float X1, float Y1, float Z1)
{

	坐标_ 本人坐标 = 本人::取坐标();

	float x = 本人坐标.x - X1;
	float y = 本人坐标.y - Y1;
	float z = 本人坐标.z - Z1;
	return sqrtf(float(x * x + y * y + z * z))/100;
}



typedef unsigned __int64 uint64_t;
uint64_t MurmurHash64A(const void* key, int len, unsigned int seed)
{
	const uint64_t m = 0xc6a4a7935bd1e995;
	const int r = 47;

	uint64_t h = seed ^ (len * m);

	const uint64_t* data = (const uint64_t*)key;
	const uint64_t* end = data + (len / 8);

	while (data != end)
	{
		uint64_t k = *data++;
		//   //MyTrace(L"0%I64X \r\n",k);
		k *= m;
		k ^= k >> r;
		k *= m;

		h ^= k;
		h *= m;
		//	//MyTrace(L"0%I64X \r\n",h);
	}
	//  //MyTrace(L"0%I64X \r\n",h);
	const unsigned char* data2 = (const unsigned char*)data;

	switch (len & 7)
	{
	case 7: h ^= uint64_t(data2[6]) << 48;
	case 6: h ^= uint64_t(data2[5]) << 40;
	case 5: h ^= uint64_t(data2[4]) << 32;
	case 4: h ^= uint64_t(data2[3]) << 24;
	case 3: h ^= uint64_t(data2[2]) << 16;
	case 2: h ^= uint64_t(data2[1]) << 8;
		////MyTrace(L"0%I64X \r\n",data2[0]);
	case 1: h ^= uint64_t(data2[0]);
		////MyTrace(L"0%I64X \r\n",h);
		h *= m;
		////MyTrace(L"0%I64X \r\n",h);
	};

	h ^= h >> r;
	h *= m;
	h ^= h >> r;

	return h;
}
INT64  getStringAddrNew(DWORD dStrIndex, INT64 dStrAddr, DWORD dStrLen)
{
	//gb_Str = dm.GetModuleBaseAddr(L"LOSTARK.exe") + 0x4557008;//0x42C1320;
	CString cTargetStr = R_CString(dStrAddr);
	UINT64 dHashValue = MurmurHash64A(cTargetStr.MakeLower(), dStrLen * 2, 0xC70F6907);
	////MyTrace(L"dHashValue %I64X \r\n",dHashValue);
	UINT64 dIndex = (UINT64)((INT)dHashValue + ((INT)(dHashValue >> 32)) * 0x17);
	////MyTrace(L"dIndex %I64X \r\n",dIndex);
	INT64 addr_1 = 游戏模块 + gb_Str + 0xD8;
	DWORD dTotal = R_DW(addr_1 + 0x8C);
	if (dTotal != 0)
	{
		INT64 dStartAddr = 0;
		if (R_QW(addr_1 + 0x84))
		{
			dStartAddr = R_QW(addr_1 + 0x84);
		}
		else
		{
			dStartAddr = addr_1 + 0x80;
		}
		DWORD dTempOffest = ((dTotal - 1) & dIndex) * 4;
		////MyTrace(L"dTempOffest %X \r\n",dTempOffest);
		INT dEnIndex = R_DW(dStartAddr + dTempOffest);
		if (dEnIndex != -1)
		{
			INT64 dEnStartAddr = R_QW(addr_1 + 0x48);
			INT64 dEnAddr = 0;
			while (1)
			{
				if (R_QW(dEnStartAddr + dEnIndex * 0x20) == dHashValue)
				{
					dEnAddr = dEnStartAddr + dEnIndex * 0x20 + 8;
					break;
				}
				dEnIndex = R_DW(dEnStartAddr + dEnIndex * 0x20 + 0x18);
				if (dEnIndex == -1)
				{
					return 0;
				}
			}
			if (dEnAddr != 0)
			{
				DWORD dEnIndexTotal = R_DW(dEnAddr + 8);
				INT64 dEnIndexStartAddr = R_QW(dEnAddr);
				DWORD dCnIndex = 0;
				for (int i = 0; i < dEnIndexTotal; i++)
				{
					INT64 dEnStingAddr = R_QW(dEnIndexStartAddr + i * 0x14);
					CString cTempstr = R_CString(dEnStingAddr);
					if (_wcsicmp(cTempstr, cTargetStr) == 0)
					{
						dCnIndex = R_DW(dEnIndexStartAddr + i * 0x14 + 0x10);
						break;
					}
				}
				if (dCnIndex != 0)
				{
					INT64 dCnStartAddr = R_QW(addr_1);
					INT64 dCnAddr = R_QW(dCnStartAddr + dCnIndex * 0x64);
					return dCnAddr;
				}
			}
		}
	}
	return 0;

}
INT64 getStringAddr(DWORD dStrIndex, INT64 dStrAddr, DWORD dStrLen)
{

	return getStringAddrNew(dStrIndex, dStrAddr, dStrLen);
}

DWORD 取相对角度(float fx, float fy)
{
	坐标_ 角色坐标 = 本人::取坐标();
	return DWORD(Get_Rel_Angle(角色坐标.x, 角色坐标.y, fx, fy) * 0.00549317);
}

string test()
{
	//string str = CString(L"%d", 321).GetBuffer();
	CStringA str;
	str.Format("%d", 123);
	const char* zz = str;
	CString strw = str;
	return str;
}