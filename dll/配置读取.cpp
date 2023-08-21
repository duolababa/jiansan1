#include "配置读取.h"
CString 读取录制坐标文本(CString 地图ID)
{
	CString 配置节点, 配置项名称, path;
	CString 解密后文本;
	if (辅助位置 == L"")
	{
		配置::获取辅助位置();
	}
	if (辅助位置 != L"")
	{
		path = 辅助位置 + L"\\Map\\" + 地图ID + L".txt";
	}
	else
	{
		path = L"D:\\LostArkLUA\\Map\\" + 地图ID + L".txt";
	}

	OutputDebugStringW(path);

	HANDLE 文件句柄;
	char 文本[2048] = "";
	文件句柄 = 打开文件(path);
	if (文件句柄 == INVALID_HANDLE_VALUE)
	{
		return L"文件句柄打开失败";
	}
	int filesucc = 读文件(文件句柄, 文本, 2048);

	if (filesucc == 0)
	{
		return L"读取文件失败";
	}
	int fileSize = GetFileSize(文件句柄, NULL);

	CloseHandle(文件句柄);
	解密后文本 = 文本;
	return 解密后文本;
}
void 文本分割(CString strSource, char ch, CArray<CString, CString>* 返回文本组)
{
	返回文本组->RemoveAll();
	CString strTmp;
	//CArray<CString, CString> vecString;
	int iPos = 0;
	while (AfxExtractSubString(strTmp, strSource, iPos, ch))
	{
		iPos++;
		返回文本组->Add(strTmp);
	}

}
void 处理坐标文本(CString 坐标文本, vector<录制坐标_>& 参_录制坐标组, int 地图标识)
{
	int 文本位置 = -1;
	参_录制坐标组.clear();
	录制坐标_ 局_录制坐标;
	CArray<CString, CString>分配坐标文本组;
	CArray<CString, CString>坐标文本组;
	CArray<CString, CString>坐标操作组;
	CString 标识文本;
	坐标文本.Replace(L"\r\n", L"}");
	坐标文本.Replace(L"//", L"");
	文本分割(坐标文本, '}', &分配坐标文本组);
	for (size_t i = 0; i < 分配坐标文本组.GetCount(); i++)
	{
		文本分割(分配坐标文本组[i], ',', &坐标文本组);
		if (坐标文本组.GetCount() == 11)
		{
			局_录制坐标.x1 = _ttof(坐标文本组[0]);
			局_录制坐标.y1 = _ttof(坐标文本组[1]);
			局_录制坐标.z1 = _ttof(坐标文本组[2]);
			局_录制坐标.x2 = _ttof(坐标文本组[3]);
			局_录制坐标.y2 = _ttof(坐标文本组[4]);
			局_录制坐标.z2 = _ttof(坐标文本组[5]);
			局_录制坐标.操作 = _ttoi(坐标文本组[6]);
			局_录制坐标.线路 = _ttoi(坐标文本组[7]);
			局_录制坐标.线路分段 = _ttoi(坐标文本组[8]);
			局_录制坐标.未知1 = _ttoi(坐标文本组[9]);
			局_录制坐标.未知2 = _ttoi(坐标文本组[10]);
			局_录制坐标.地图ID = 地图标识;
			//局_录制坐标.地图标识 = false;
			参_录制坐标组.push_back(局_录制坐标);
		}
	}
}
void 配置::取录制坐标(int 地图标识, vector<录制坐标_>& 录制坐标组)
{
	if (地图标识 == 0)
	{
		return;
	}
	CString 地图str;
	地图str.Format(L"%d", 地图标识);
	CString 坐标文本 = 读取录制坐标文本(地图str);
	处理坐标文本(坐标文本, 录制坐标组, 地图标识);
	//MyTrace(L"%d 取出录制坐标组:%d 个", 地图标识, 录制坐标组.size());
}
CString 获取LAconfig辅助目录()
{
	CString 返回文本 = L"";

	CString path = L"C:\\LAconfig.ini";
	GetPrivateProfileString(L"全局配置", L"辅助目录", L"", 返回文本.GetBuffer(4096), 4096, path);
	返回文本.ReleaseBuffer();
	return 返回文本;
}
void 配置::获取辅助位置()
{
	辅助位置 = 获取LAconfig辅助目录();
	//辅助位置 = 取模块路径("debugreport.dll");
	if (辅助位置 != L"")
	{
		OutputDebugStringW(L"辅助位置:" + 辅助位置);
	}
	else
	{
		OutputDebugStringW(L"辅助位置错误:" + 辅助位置);
	}

}
CString 配置::获取指定设置文本(CString 配置文件名称, CString 配置节点, CString 配置项名称)
{
	CString 返回文本 = L"", path;
	if (辅助位置 == L"")
	{
		获取辅助位置();
	}
	path = 辅助位置 + L"\\" + 配置文件名称;
	GetPrivateProfileString(配置节点, 配置项名称, L"", 返回文本.GetBuffer(4096), 4096, path);
	返回文本.ReleaseBuffer();
	return 返回文本;
}

//void 配置::读取脚本配置()
//{
//	脚本任务 = 获取指定设置文本(L"脚本配置.ini", L"LostArk" + 整数到文本(GameIndex), L"脚本任务");
//	角色序号 = 获取指定设置文本(L"脚本配置.ini", L"LostArk" + 整数到文本(GameIndex), L"角色");
//	配置
//  = 获取指定设置文本(L"脚本配置.ini", L"LostArk" + 整数到文本(GameIndex), L"服务器");
//	//MyTrace(L"序号 %d 脚本任务 %s 角色序号 %s 服务器: %s", GameIndex, 脚本任务, 角色序号, 配置服务器);
//}