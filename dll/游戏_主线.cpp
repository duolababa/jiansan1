#include "游戏_主线.h"
vector<录制坐标_>录制坐标组;
vector<录制坐标_>路径分段坐标组;
录制坐标_ 分段处理坐标;
vector<DWORD>优先打怪ID;
DWORD 任务流程 = 0;

vector<DWORD>暂时不开的传送阵;
bool ID是否已存在(DWORD ID, vector<DWORD>& ID组)
{
	for (size_t j = 0; j < ID组.size(); j++)
	{
		//MyTrace(L"优先打怪判断  %d/%d", ID, ID组[j]);
		if (ID == ID组[j])
		{
			return true;
		}
	}
	return false;
}
void 加入暂时不打ID(CString ID文本)
{
	if (ID文本 == L"")
	{
		暂时不打ID.clear();
	}
	暂时不打ID.push_back(_ttoi(ID文本));
}
void 加入暂时不打ID_数字(DWORD ID)
{
	if (ID == 0)
	{
		暂时不打ID.clear();
	}
	暂时不打ID.push_back(ID);
}
void 加入优先打怪ID(CString ID文本)
{
	CArray<CString, CString>返回文本组;
	优先打怪ID.clear();
	if (ID文本 == L"")
	{
		优先打怪ID.clear();
	}
	else
	{
		if (ID文本.Find(L"|") == -1)
		{
			if (ID是否已存在(_ttoi(ID文本), 优先打怪ID) == false)
			{
				优先打怪ID.push_back(_ttoi(ID文本));
			}
		}
		else
		{
			文本分割(ID文本, '|', &返回文本组);
			if (返回文本组.GetCount() == 0)
			{
				优先打怪ID.clear();
			}
			else
			{

				for (size_t i = 0; i < 返回文本组.GetCount(); i++)
				{
					if (ID是否已存在(_ttoi(返回文本组[i]), 优先打怪ID) == false)
					{
						优先打怪ID.push_back(_ttoi(返回文本组[i]));
					}

				}
			}
		}

	}

}
void 加入暂时不开启传送阵ID(DWORD ID)
{
	if (!ID是否已存在(ID, 暂时不开的传送阵))
	{
		暂时不开的传送阵.push_back(ID);
	}

}
size_t 读条计数 = 0;
bool 游戏::Pass各种窗口()
{

	if (UI功能::getGameCurStageValue() == 0 || UI功能::getGameCurStageValue() == 3)
	{
		//if (UI功能::指定UI是否显示(L"root1.arkui.frameCanvas.narrationAssistanceFrame") == true)
		//{
		//	UI功能::Fun_NarrationAssistance_OnOff(0);
		//	UI功能::Fun_NarrationAssistance_Continue();
		//	return true;
		//}
		CString 弹窗文本 = UI功能::getMsgBoxText();
		MyTrace(L"弹窗 %s", 弹窗文本);
		if (弹窗文本.Find(L"Cannot connect") != -1)
		{
			MyTrace(L"弹窗 %s", 弹窗文本);
			SendMessageToMoConter(122, L"无法连接服务器");
			Sleep(10000);
			return true;
		}
		if (弹窗文本.Find(L"Server authentication") != -1)
		{
			MyTrace(L"弹窗 %s", 弹窗文本);
			SendMessageToMoConter(122, L"10010弹窗");
			Sleep(10000);
			//UI功能::getMsgBoxTextList();
			return true;
		}
		if (弹窗文本.Find(L"We are unable to provide") != -1)
		{
			MyTrace(L"弹窗 %s", 弹窗文本);
			SendMessageToMoConter(122, L"IP归属地有问题");
			Sleep(10000);
			return true;
		}
		if (弹窗文本 != L"")
		{
			MyTrace(L"弹窗 %s", 弹窗文本);
			SendMessageToMoConter(122, L"未知服务器弹窗" + 弹窗文本);
			Sleep(10000);
			//UI功能::getMsgBoxTextList();
			return true;
		}
		return false;
	}

	if (UI功能::退出菜单是否打开())
	{

		UI功能::内存按键(VK_ESCAPE);
		Sleep(3000);
		return true;
	}
	if (环境::是否在动画())
	{
		UI功能::内存按键(VK_ESCAPE);
		Sleep(3000);
		return true;
	}
	if (环境::是否在加载页面2() || 环境::是否在加载页面())
	{
		MyTrace(L"加载页面中");
		读条计数 = 读条计数 + 1;
		SendMessageToMoConter(122, L"读条中:" + 整数到文本(读条计数));
		Sleep(3000);
		return true;
	}
	if (!UI功能::getMsgBoxTextList())
	{
		Sleep(3000);
		return true;
	}
	if (本人::get_ActionTimingTime())
	{
		MyTrace(L"是否读条 %d", 1);
		Sleep(1000);
		return true;
	}
	/*else if (UI功能::是否读条())
	{
		MyTrace(L"是否读条 %d", 1);
		Sleep(1000);
		return true;
	}*/
	if (本人::取角色信息().当前动作 == 10)
	{

		MyTrace(L"当前动作 %d", 本人::取角色信息().当前动作);
		if (地图::取地图ID() != 10201)
		{
			Sleep(1000);
			return true;
		}

	}
	读条计数 = 0;
	/*else if (环境::是否在和NPC对话())
	{
		UI功能::内存按键(DWORD('G'));
		return true;
	}*/
	return false;
}
int 当前任务分段 = 0;
int 当前地图分段 = 0;
void 初始化任务分段()
{
	当前任务分段 = 0;
}
void 初始化地图分段()
{
	当前地图分段 = 0;
}
bool 游戏::主线_序章(QuestInfo_ 主线任务)
{
	ActorInfo_ 角色信息 = 本人::取角色信息();
	DWORD 大陆ID = 地图::取当前大陆ID();
	DWORD 地图ID = 地图::取地图ID();
	if (主线任务.dQuestId == 101901)//命运的岔路口
	{
		//QuestInfo_ 主线子任务 = 任务::取出主线子任务();
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标;
			任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			地图::本地图寻路(任务坐标.x, 任务坐标.y, 任务坐标.z, 0);
			return false;
		}
		if (主线任务.dStep == 2)
		{
			当前任务分段 = 0;
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(大陆ID, 地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 100);
			return false;
			/*if (GetDis(任务坐标.x, 任务坐标.y, 任务坐标.z) <= 70)
			{
				UI功能::内存按键(DWORD('G'));
				Sleep(500);
				return false;
			}
			else
			{
				地图::本地图寻路(任务坐标.x, 任务坐标.y, 任务坐标.z, 0);
				Sleep(500);
				return false;
			}*/
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			objInfo_ 触发选择职业 = 环境::取指定对象信息(0x272F);
			if (GetDis(触发选择职业.坐标.x, 触发选择职业.坐标.y, 触发选择职业.坐标.z) <= 50)
			{
				if (UI功能::经验条界面是否显示() == false)
				{
					MyTrace(L"选择职业");
					新手::CALL_选择职业(0xCD);
					Sleep(5000);

				}
				return false;
			}
			else
			{
				//objInfo_ 触发选择职业2 = 环境::取指定对象信息(0x272F);
				if (触发选择职业.dResShow == 1)
				{
					MyTrace(L"寻路到0x272F");
					地图::本地图寻路(触发选择职业.坐标.x, 触发选择职业.坐标.y, 触发选择职业.坐标.z, 0);
					Sleep(5000);
					return false;
				}
				if (UI功能::经验条界面是否显示() == false)
				{
					MyTrace(L"选择体验");
					新手::CALL_选择体验(0xCD);
					Sleep(5000);
					return false;
				}
				if (UI功能::体验职业中界面是否显示() == true)
				{
					MyTrace(L"退出体验");
					新手::CALL_退出体验();
					Sleep(5000);
					return false;
				}
				/*else
				{

					地图::本地图寻路(任务坐标.x, 任务坐标.y, 任务坐标.z, 0);
					Sleep(500);
					return false;
				}*/
			}

			/*if (当前任务分段 == 0)
			{
				新手::CALL_选择体验(0xCD);
				当前任务分段 = 当前任务分段 + 1;
				Sleep(5000);
			}
			if (当前任务分段 == 1)
			{
				新手::CALL_退出体验();
				当前任务分段 = 当前任务分段 + 1;
				Sleep(5000);
			}
			if (当前任务分段 == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				if (GetDis(任务坐标.x, 任务坐标.y, 任务坐标.z) <= 20)
				{
					当前任务分段 = 当前任务分段 + 1;
				}
				else
				{
					地图::本地图寻路(任务坐标.x, 任务坐标.y, 任务坐标.z, 0);
					Sleep(500);
				}


			}
			if (当前任务分段 == 3)
			{
				新手::CALL_选择职业(0xCD);
				当前任务分段 = 当前任务分段 + 1;
				Sleep(5000);
				当前任务分段 = 0;
			}*/

			return false;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (环境::是否在和NPC对话())
			{
				for (size_t i = 0; i < 5; i++)
				{
					UI功能::内存按键(DWORD('G'));
					Sleep(300);
				}
			}
			else
			{
				if (任务坐标.x == 0)
				{
					return false;
				}
				if (GetDis(任务坐标.x, 任务坐标.y, 任务坐标.z) <= 20)
				{
					UI功能::内存按键(DWORD('G'));
					Sleep(500);
					return false;
				}
				else
				{
					地图::本地图寻路(任务坐标.x, 任务坐标.y, 任务坐标.z, 0);
					Sleep(500);
				}
			}

		}
		return false;
	}
	if (主线任务.dQuestId == 0x19F0A1)
	{
		if (地图ID == 10001)
		{
			UI功能::内存按键(DWORD('G'));
			Sleep(500);
			return false;
		}
		return false;
	}
	if (主线任务.dQuestId == 1700401)//被遗忘的土地
	{
		新手::CALL_跳过序幕();
		Sleep(8000);
		return false;

	}
	return true;
}
void 游戏::主线_莱文哈特罗格尔(QuestInfo_ 主线任务)
{
	ActorInfo_ 角色信息 = 本人::取角色信息();
	DWORD 大陆ID = 地图::取当前大陆ID();
	DWORD 地图ID = 地图::取地图ID();

	if (主线任务.dQuestId == 201001)//被遗忘的土地
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(1, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return;

		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 1500);

			return;
		}
		if (主线任务.dStep == 3)//和阿曼对话
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(1, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);

		}
		return;
	}
	if (主线任务.dQuestId == 201002)//被遗忘的土地
	{
		if (主线任务.dStep == 1)//上马车
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(1, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 200, 100);
			return;
		}
		if (主线任务.dStep == 2)//拯救阿曼
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(1, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 100);
			return;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 1500);
			return;

		}
		if (主线任务.dStep == 4)
		{

			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (功能::优先打怪(1500) == true)
			{
				功能::到指定地点找NPC交任务3(1, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			}
			return;


		}
		return;
	}
	if (主线任务.dQuestId == 201003)//救命恩人
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(1, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return;


		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(1, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);

		}
		return;
	}
	if (主线任务.dQuestId == 202009)//前往大堂外
	{
		if (主线任务.dState == 1)
		{
			if (GetDis(10086, 4090, -37344.5) >= 20)
			{
				地图::本地图寻路(10086, 4090, -37344.5, 0);
				Sleep(500);

			}

		}
		if (主线任务.dState == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, L"", 主线任务.dQuestId, 1, 50);
			Sleep(5000);
		}
		return;
	}
	if (主线任务.dQuestId == 205004)//巴图图的礼物 //202002
	{
		if (主线任务.dStep == 1)
		{
			背包::使用背包指定物品_ByResId(0x1F401);//坐骑
			//背包::使用背包指定物品(L"坐骑");
			Sleep(500);
			return;
		}
		if (主线任务.dStep == 2)
		{
			本人::CALL_使用坐骑(6001);
			Sleep(500);
			return;
		}
		return;
	}
	if (主线任务.dQuestId == 202002)//巴图图的礼物
	{

		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(1, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);

		}
		if (主线任务.dStep == 2)//向装备商人艾尔拉拉
		{

			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(1, 任务坐标.地图ID, 7579, 9463, -18015, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);

		}
		if (主线任务.dStep == 3)//向装备商人艾尔拉拉
		{
			//return;
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);

			功能::到指定地点找NPC交任务3(1, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			/*if (地图::取小地图名() == L"艾尔拉拉的装备商店")
			{
				if (GetDis(7638, 8790, -18015) >= 20)
				{
					地图::本地图寻路(7638, 8790, -18015, 0);
					Sleep(500);
					return;
				}
			}
			if (地图::取小地图名() == L"")
			{
				功能::自动主线和NPC对话(50);

			}*/
		}

		if (主线任务.dStep == 4)//传说与童话 查看大教堂旁的观景台
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
		}
		if (主线任务.dStep == 5)//传说与童话 与冒险家协会会长<FONT COLOR='#CFF960'>鲁汀</FONT>交谈  0/1
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(1, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);

		}
		if (主线任务.dStep == 6)//传说与童话 跟传送点管理员<FONT COLOR='#CFF960'>内尔</FONT>打听石板碎片的消息
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(1, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);

		}
		if (主线任务.dStep == 7)//传说与童话  启动<FONT COLOR='#CFF960'>传送点</FONT>进行调查  0/1
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);

		}
		if (主线任务.dStep == 8)//传说与童话  回到传送点管理员<FONT COLOR='#CFF960'>内尔</FONT>身边  0/1
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(1, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);

		}
		if (主线任务.dStep == 9)//传说与童话  与希利对话
		{

			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(1, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);

		}
		if (主线任务.dStep == 10)//传说与童话  与希利对话
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(1, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);

		}
		if (主线任务.dStep == 11)//传说与童话  按下<img src='emoticon_keyBoard_I' width='0' height=  0/1 登记逃生乐章
		{
			背包::使用背包指定物品_ByResId(0x75303);
			Sleep(500);

		}
		if (主线任务.dStep == 12)//传说与童话   与吟游诗人<FONT COLOR='#CFF960'>希利</FONT>对话  0/1
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(1, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
		}
		return;
	}
	if (主线任务.dQuestId == 203001)//古代的遗产
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 11291, 主线任务.dQuestId, -1, 50);
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 6128, 15018, 7, 500);

		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 2457, 17967, 264, 500);

		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 2606, 22516, 265, 500);
			Sleep(2000);
		}
		if (主线任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 2158, 25754, 265, 500);
		}
		if (主线任务.dStep == 6)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 11292, 主线任务.dQuestId, -1, 50);
		}
		return;
	}
	if (主线任务.dQuestId == 203005)//
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::寻路到副本(1, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z);
			/*if (UI功能::副本界面是否打开() == true)
			{
				if (UI功能::进入副本())
				{
					Sleep(2000);
					UI功能::内存按键(VK_RETURN);
				}

			}
			else
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			}*/


		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 11292, 主线任务.dQuestId, -1, 50);

		}
		return;
	}
	if (主线任务.dQuestId == 203002)//
	{
		if (主线任务.dStep == 1)
		{
			加入优先打怪ID(L"120184");

			功能::移动打怪(5892, 34217, 1005.79, 0, 3000);


		}
		if (主线任务.dStep == 2)
		{
			加入优先打怪ID(L"");
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);

		}
		return;
	}
	if (主线任务.dQuestId == 203003)//向警备队员<FONT COLOR='#CFF960'>米格尔</FONT>询问石板的下落
	{
		if (主线任务.dStep == 1)
		{
			if (主线任务.子任务进度.size() == 2)
			{
				if (主线任务.子任务进度[0].dCur < 主线任务.子任务进度[0].dNeed)
				{
					MyTrace(L"子任务进度 %s %d/%d TargetID:%d", 主线任务.子任务进度[0].任务描述, 主线任务.子任务进度[0].dCur, 主线任务.子任务进度[0].dNeed, 主线任务.子任务进度[0].TargetID);
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 11295, 主线任务.dQuestId, -1, 50);
					return;
				}
				if (主线任务.子任务进度[1].dCur < 主线任务.子任务进度[1].dNeed)
				{
					MyTrace(L"子任务进度 %s %d/%d TargetID:%d", 主线任务.子任务进度[1].任务描述, 主线任务.子任务进度[1].dCur, 主线任务.子任务进度[1].dNeed, 主线任务.子任务进度[1].TargetID);
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 12333, 34652, 292, 200);
					return;
				}
			}
			return;
		}
		if (主线任务.dStep == 2)//回莱
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 7521, 8481, 264, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 11794, 34887, 256, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"120500");
			功能::移动打怪(15334, 33195, 256, 0, 2000);
			return;
		}
		if (主线任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
		}
		if (主线任务.dStep == 6)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, 2, 50, 主线任务.dStep);
		}
		return;
	}
	if (主线任务.dQuestId == 203006)//毒爪偷盗团藏匿之地 内部
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			//功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			功能::寻路到副本(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z);
			return;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
	}
	if (主线任务.dQuestId == 203004)//偷盗团所寻之物
	{
		if (主线任务.dStep == 1)
		{
			//坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(18334.752, 16101.212, 1024.172, 0, 3000);
			return;
		}
		if (主线任务.dStep == 2)
		{
			功能::移动打怪(18505.975, 19338.146, 1268.000, 0, 3000);
			return;
		}
	}
	if (主线任务.dQuestId == 205001)//警报！ //去找<FONT COLOR='#CFF960'>舒迪尔</FONT>
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 2)
		{
			加入优先打怪ID(L"120140");
			功能::移动打怪(17289.721, 38286.797, 256.000, 0, 3000);
			return;
		}
		if (主线任务.dStep == 3)
		{
			if (优先打怪ID.size() != 0)
			{
				优先打怪ID.clear();
			}
			功能::移动打怪(17524.967, 47466.867, 256.000, 0, 100);
			return;
		}
	}
	if (主线任务.dQuestId == 205002)//科尔兹森林的偷盗团 ！ //向休息区管理员<FONT COLOR='#CFF960'>梅德</FONT>打听消息
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 2)
		{
			if (UI功能::副本界面是否打开() == true)
			{
				if (UI功能::进入副本())
				{
					Sleep(2000);
					UI功能::内存按键(VK_RETURN);
				}

			}
			else
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			}
			return;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}

	}
	if (主线任务.dQuestId == 205003)//调查科尔兹森林里<FONT COLOR='#CFF960'>被破坏的遗址</FONT>
	{
		if (主线任务.dStep == 1)
		{
			//加入优先打怪ID(L"20637");
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 300);
			//功能::移动打怪(18559.10, 58385.082, 512.000, 0, 3000);
			return;
		}
		if (主线任务.dStep == 2)
		{
			加入优先打怪ID(L"120450");
			//坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			//功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 300);
			功能::移动打怪(17757.746, 57911.805, 512.000, 0, 3000);
			//功能::移动打怪(18559.10, 58385.082, 512.000, 0, 3000);
			return;
		}
	}
	if (主线任务.dQuestId == 204001)//梅德提供了毒爪偷盗团头目藏身的洞穴位置.那个洞穴位于科尔兹森林附近，但好像还没有被警备队员们发现.<br>为了尽快找到钥之石板，你便匆忙赶往偷盗团藏身的洞穴.
	{
		if (主线任务.dStep == 1)
		{
			加入优先打怪ID(L"");
			if (UI功能::副本界面是否打开() == true)
			{
				if (UI功能::进入副本())
				{
					Sleep(2000);
					UI功能::内存按键(VK_RETURN);
				}

			}
			else
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			}
			return;
		}

	}
	//if (主线任务.dQuestId == 204002)//梅德提供了毒爪偷盗团头目藏身的洞穴位置.那个洞穴位于科尔兹森林附近，但好像还没有被警备队员们发现.<br>为了尽快找到钥之石板，你便匆忙赶往偷盗团藏身的洞穴.
	//{
	//	if (主线任务.dStep == 1)
	//	{
	//		if (本人::取坐标().z > 1530)
	//		{
	//			MyTrace(L"分段1");
	//			功能::到指定地点按G(地图::取当前大陆ID(), 地图::取地图ID(), 15566, 11229, 1535, 50);
	//			return;
	//		}
	//		if (本人::取坐标().z > 1200)
	//		{
	//			MyTrace(L"分段2");
	//			if (功能::移动打怪(16679, 11454, 1279.82, 0, 300))
	//			{
	//				功能::到指定地点按G(地图::取当前大陆ID(), 地图::取地图ID(), 16679, 11454, 1279.82, 50);
	//			}			
	//			return;
	//		}
	//	}
	//	if (主线任务.dStep == 2)
	//	{
	//		if (本人::取坐标().z > 1200)
	//		{
	//			MyTrace(L"分段2");
	//			if (功能::移动打怪(16679, 11454, 1279.82, 0, 300))
	//			{
	//				功能::到指定地点按G(地图::取当前大陆ID(), 地图::取地图ID(), 16679, 11454, 1279.82, 50);
	//			}
	//			return;
	//		}
	//	}
	//	if (主线任务.dStep == 3)
	//	{
	//		坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
	//		功能::移动打怪(18712.5, 14512.8, 1024, 0, 3000);
	//		return;
	//	}
	//	if (主线任务.dStep == 4)
	//	{
	//		if (本人::取坐标().z < 1050)
	//		{
	//			MyTrace(L"分段2");

	//			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
	//			功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 150);
	//			return;

	//		}
	//	}
	//	if (主线任务.dStep == 5)
	//	{
	//		CString temp;
	//		temp.Format(L"%d", 主线任务.TargetId);
	//		加入优先打怪ID(temp);
	//		坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
	//		功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 1400);
	//		return;
	//	}
	//	if (主线任务.dStep == 6)
	//	{
	//		//坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
	//		
	//		功能::移动打怪(21652,17230,1536, 0, 1400);
	//		return;
	//	}
	//	if (主线任务.dStep == 7)
	//	{
	//		if (主线任务.子任务进度.size() == 2)
	//		{
	//			if (主线任务.子任务进度[0].dCur < 主线任务.子任务进度[0].dNeed)
	//			{
	//				MyTrace(L"子任务进度 %s %d/%d TargetID:%d", 主线任务.子任务进度[0].任务描述, 主线任务.子任务进度[0].dCur, 主线任务.子任务进度[0].dNeed, 主线任务.子任务进度[0].TargetID);
	//				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
	//				CString temp;
	//				temp.Format(L"%d", 主线任务.子任务进度[0].TargetID);
	//				加入优先打怪ID(temp);
	//				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 1400);
	//				
	//				return;
	//			}
	//			if (主线任务.子任务进度[1].dCur < 主线任务.子任务进度[1].dNeed)
	//			{
	//				MyTrace(L"子任务进度 %s %d/%d TargetID:%d", 主线任务.子任务进度[1].任务描述, 主线任务.子任务进度[1].dCur, 主线任务.子任务进度[1].dNeed, 主线任务.子任务进度[1].TargetID);
	//				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
	//				CString temp;
	//				temp.Format(L"%d", 主线任务.子任务进度[1].TargetID);
	//				加入优先打怪ID(temp);
	//				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 1400);
	//				return;
	//			}
	//		}
	//	}
	//	if (主线任务.dStep == 8)
	//	{
	//		坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
	//		功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 150);
	//		return;
	//	}
	//	if (主线任务.dStep == 9)
	//	{
	//		坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
	//		CString temp;
	//		temp.Format(L"%d", 主线任务.TargetId);
	//		加入优先打怪ID(temp);
	//		功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 1400);
	//		return;
	//	}
	//}
	if (主线任务.dQuestId == 202008)//梅德提供了毒爪偷盗团头目藏身的洞穴位置.那个洞穴位于科尔兹森林附近，但好像还没有被警备队员们发现.<br>为了尽快找到钥之石板，你便匆忙赶往偷盗团藏身的洞穴.
	{
		if (主线任务.dStep == 1)
		{
			if (地图ID == 10253)
			{
				if (功能::拾取道具(2000) == true)
				{
					MyTrace(L"副本中，演奏乐谱");
					本人::CALL_演奏乐谱(1);
					Sleep(10000);


				}
				return;
			}
			else
			{
				if (UI功能::副本界面是否打开() == true)
				{
					if (UI功能::进入副本())
					{
						Sleep(2000);
						UI功能::内存按键(VK_RETURN);
					}

				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 150);
				}
			}

			return;
		}

	}
	if (主线任务.dQuestId == 202007)//梅德提供了毒爪偷盗团头目藏身的洞穴位置.那个洞穴位于科尔兹森林附近，但好像还没有被警备队员们发现.<br>为了尽快找到钥之石板，你便匆忙赶往偷盗团藏身的洞穴.
	{
		if (主线任务.dStep == 1)
		{
			if (主线任务.子任务进度.size() == 2)
			{
				if (主线任务.子任务进度[0].dCur < 主线任务.子任务进度[0].dNeed)
				{
					MyTrace(L"子任务进度 %s %d/%d TargetID:%d", 主线任务.子任务进度[0].任务描述, 主线任务.子任务进度[0].dCur, 主线任务.子任务进度[0].dNeed, 主线任务.子任务进度[0].TargetID);
					if (功能::优先打怪(100))
					{
						if (功能::优先破坏击打道具(500))
						{
							坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
							if (主线任务.子任务进度[0].dCur == 0)
							{
								功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 5581, 3514, -259, 0x2C4F, 主线任务.dQuestId, -1, 600);
								Sleep(500);
								return;
							}
							if (主线任务.子任务进度[0].dCur == 1)
							{
								功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 5581, 3514, -259, 0x2C62, 主线任务.dQuestId, -1, 600);
								Sleep(500);
								return;
							}

						}
					}
					return;
				}
				if (主线任务.子任务进度[1].dCur < 主线任务.子任务进度[1].dNeed)
				{

					if (功能::优先打怪(100))
					{
						if (功能::优先破坏击打道具(2000))
						{
							坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
							if (主线任务.子任务进度[1].dCur == 0)
							{
								功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 5683, 5838, 5.00822, 0x2C46, 主线任务.dQuestId, -1, 600);
								Sleep(500);
								return;
							}
							if (主线任务.子任务进度[1].dCur == 1)
							{
								功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 5683, 5838, 5.00822, 0x2C60, 主线任务.dQuestId, -1, 600);
								Sleep(500);
								return;
							}
						}
					}



					return;

				}
			}
		}
		if (主线任务.dStep == 2)
		{
			if (主线任务.子任务进度.size() == 4)
			{
				if (主线任务.子任务进度[0].dCur < 主线任务.子任务进度[0].dNeed)
				{
					MyTrace(L"子任务1");
					if (功能::优先打怪(100))
					{
						if (功能::优先破坏击打道具(2000))
						{
							功能::移动打怪(8307, 6649, 261, 100, 3000, 300);
						}
					}
					return;
				}
				if (主线任务.子任务进度[1].dCur < 主线任务.子任务进度[1].dNeed)
				{
					MyTrace(L"子任务2");
					if (功能::优先打怪(100))
					{
						if (功能::优先破坏击打道具(2000))//if (功能::移动打怪(8327, 6423, 256, 200, 500, 600))
						{
							坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
							if (主线任务.子任务进度[1].dCur == 0)
							{
								功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 8327, 6423, 256, 11258, 主线任务.dQuestId, -1, 600);
								Sleep(1000);
								return;
							}
							if (主线任务.子任务进度[1].dCur == 1)
							{
								功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 8327, 6423, 256, 11362, 主线任务.dQuestId, -1, 600);
								Sleep(1000);
								return;
							}
							if (主线任务.子任务进度[1].dCur == 2)
							{
								功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 8327, 6423, 256, 11361, 主线任务.dQuestId, -1, 600);
								Sleep(1000);
								return;
							}
						}
					}
					return;
				}
				if (主线任务.子任务进度[2].dCur < 主线任务.子任务进度[2].dNeed)
				{
					MyTrace(L"子任务3");
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					if (GetDis(9042.29, 8507.98, -15356.8) <= 3000)
					{
						objInfo_ 附近NPC = 环境::取指定任务显示对象信息(11360,0);
						MyTrace(L"附近NPC %d", 附近NPC.dResId);
						if (附近NPC.dResId == 11360)
						{
							功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 附近NPC.坐标.x, 附近NPC.坐标.y, 附近NPC.坐标.z, 11360, 主线任务.dQuestId, -1, 600);
							return;
						}
						附近NPC = 环境::取指定任务显示对象信息(11333,0);
						MyTrace(L"附近NPC2 %d", 附近NPC.dResId);
						if (附近NPC.dResId == 11333)
						{
							功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 附近NPC.坐标.x, 附近NPC.坐标.y, 附近NPC.坐标.z, 11333, 主线任务.dQuestId, -1, 600);
							return;
						}
						附近NPC = 环境::取指定任务显示对象信息(11289,0);
						MyTrace(L"附近NPC3 %d", 附近NPC.dResId);
						if (附近NPC.dResId == 11289)
						{
							功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 附近NPC.坐标.x, 附近NPC.坐标.y, 附近NPC.坐标.z, 11289, 主线任务.dQuestId, -1, 600);
							return;
						}
					}
					else
					{
						if (功能::优先破坏击打道具(3000))//if (功能::移动打怪(8327, 6423, 256, 200, 500, 600))
						{
							功能::到指定地点(任务坐标.大陆ID, 任务坐标.地图ID, 9042.29, 8507.98, -15356.8, 50);
						}
					}


					return;
				}

				if (主线任务.子任务进度[3].dCur < 主线任务.子任务进度[3].dNeed)
				{
					MyTrace(L"子任务4");
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					if (GetDis(7660, 8879, -18011) <= 3000)
					{
						if (功能::优先打怪(1000))
						{
							//坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
							objInfo_ 附近NPC = 环境::取指定任务显示对象信息(11343,0);
							if (附近NPC.dResId == 11343)
							{
								功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 附近NPC.坐标.x, 附近NPC.坐标.y, 附近NPC.坐标.z, 11343, 主线任务.dQuestId, -1, 600);
								return;
							}
							附近NPC = 环境::取指定任务显示对象信息(11334,0);
							if (附近NPC.dResId == 11334)
							{
								功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 附近NPC.坐标.x, 附近NPC.坐标.y, 附近NPC.坐标.z, 11334, 主线任务.dQuestId, -1, 600);
								return;
							}

						}
					}
					else
					{
						MyTrace(L"前置");
						if (功能::优先破坏击打道具(3000))//if (功能::移动打怪(8327, 6423, 256, 200, 500, 600))
						{
							功能::到指定地点(任务坐标.大陆ID, 任务坐标.地图ID, 7660, 8879, -18011, 50);
						}
					}

					return;
				}

				return;


			}
		}
		if (主线任务.dStep == 3)
		{
			if (功能::优先打怪(100))
			{
				if (功能::优先破坏击打道具(2000))//if (功能::移动打怪(8327, 6423, 256, 200, 500, 600))
				{
					功能::移动打怪(9859, 4033, 517.211, 100, 1500, 600);
					Sleep(500);
					MyTrace(L"营救巴图嗯");

				}
			}
			return;
		}
		if (主线任务.dStep == 4)
		{
			if (功能::优先打怪(100))
			{
				if (功能::优先破坏击打道具(2000))//if (功能::移动打怪(8327, 6423, 256, 200, 500, 600))
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 12884, 3942, -15352.5, 11276, 主线任务.dQuestId, -1, 50);
				}
			}
			/*}
			else
			{
				if (!地图::指定地点是否可到达_M(10847, 3961, 766))
				{
					MyTrace(L"巴吞2");
					功能::移动打怪(9966, 3937, 517.211, 0, 1500, 500);
					Sleep(1000);
					return;
				}
				else
				{
					功能::寻路到指定传送门(10847, 3961, 766, 20219, 500);
					return;
				}
			}*/
			return;
		}
		if (主线任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);

			//if (地图::取小地图名() != L"") //6月5日  linjinmao屏蔽
			//{
			//	坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			//	功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);

			//}
			return;
		}
		if (主线任务.dStep == 6)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);

			//if (地图::取小地图名() != L"")  //6月5日  linjinmao屏蔽
			//{
			//	坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			//	功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);

			//}
			return;
		}
	}
	if (主线任务.dQuestId == 202004)//涅利亚的故事
	{
		if (主线任务.dStep == 1)
		{

			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);

			return;
		}
	}
	if (主线任务.dQuestId == 202001)//预言石板
	{
		if (主线任务.dStep == 1)
		{

			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);

		}
		if (主线任务.dStep == 2)
		{
			if (主线任务.dState == 1 || 主线任务.dState == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 11256, 主线任务.dQuestId, -1, 50);
			}

		}
		return;
	}
	if (主线任务.dQuestId == 202003)//预言石板
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 11255, 主线任务.dQuestId, -1, 50);
			return;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
	}
	/*if (!功能::开启传送点())
	{
		return;
	}*/
	//循环跳出 = true;
}
void 游戏::主线_安格莫斯山麓(QuestInfo_ 主线任务)
{

	if (主线任务.dQuestId == 206001)//阴风阵阵的山麓
	{
		if (主线任务.dStep == 1)//与疲惫的<FONT COLOR = '#CFF960'>安格莫斯使者< / FONT>交谈  0 / 1
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 2)//与疲惫的<FONT COLOR = '#CFF960'>安格莫斯使者< / FONT>交谈  0 / 1
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 3)//采集
		{
			if (环境::是否在和NPC对话())
			{
				环境::CALL_退出NPC();
				Sleep(1000);
			}
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (主线任务.子任务进度.size() == 3)
			{

				if (主线任务.子任务进度[0].dCur < 主线任务.子任务进度[0].dNeed)
				{
					功能::到指定地点采集(任务坐标.大陆ID, 任务坐标.地图ID, 6708, -1735, -377, 100, 主线任务.子任务进度[0].TargetID, 200, 200);
					return;
				}
				if (主线任务.子任务进度[1].dCur < 主线任务.子任务进度[1].dNeed)
				{
					功能::到指定地点采集(任务坐标.大陆ID, 任务坐标.地图ID, 7852, 5023, -377, 100, 主线任务.子任务进度[1].TargetID, 200, 200);
					return;
				}
				if (主线任务.子任务进度[2].dCur < 主线任务.子任务进度[2].dNeed)
				{
					功能::到指定地点采集(任务坐标.大陆ID, 任务坐标.地图ID, -391, 5736, -121, 100, 主线任务.子任务进度[2].TargetID, 200, 200);
					return;
				}
			}
			/*坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);*/
			return;
		}

	}
	if (主线任务.dQuestId == 206002)//圣泉
	{
		if (主线任务.dStep == 1)//在圣泉附近寻找<FONT COLOR='#CFF960'>阿曼</FONT>
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			/*vector<objInfo_>vsk;
			环境::遍历全部环境对象(vsk);
			for (size_t i = 0; i < vsk.size(); i++)
			{
				MyTrace(L"名称 %d", vsk[i].dObjId);
			}*/
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 2)//装入<FONT COLOR='#CFF960'>圣泉的泉水</FONT>
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点采集(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 2000, 主线任务.TargetId, 100);
			return;
		}
		if (主线任务.dStep == 3)//装入<FONT COLOR='#CFF960'>圣泉的泉水</FONT>
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (主线任务.子任务进度.size() == 2)
			{

				if (主线任务.子任务进度[0].dCur < 主线任务.子任务进度[0].dNeed)
				{
					MyTrace(L"1");
					功能::到指定地点采集(任务坐标.大陆ID, 任务坐标.地图ID, 3251, 11883, 0, 3000, 主线任务.子任务进度[0].TargetID, 200);
					return;
				}
				if (主线任务.子任务进度[1].dCur < 主线任务.子任务进度[1].dNeed)
				{
					MyTrace(L"2");
					//功能::到指定地点采集(任务坐标.大陆ID, 任务坐标.地图ID, 3251, 11883, 0, 3000, 主线任务.子任务进度[1].TargetID, 300);
					功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 3352.752, 13465.304, 0, 50, 100);
					return;
				}
			}
		}
		if (主线任务.dStep == 4)//回到<FONT COLOR='#CFF960'>阿曼</FONT>身边
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return;
		}
		if (主线任务.dStep == 5)//前往<FONT COLOR='#CFF960'>国境监视哨所</FONT>
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return;
		}

	}
	if (主线任务.dQuestId == 206003)//寻找瘟疫起因
	{
		if (主线任务.dStep == 1)//与<FONT COLOR='#CFF960'>阿曼</FONT>交谈
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return;
		}
		if (主线任务.dStep == 2)//消灭国境监视哨所周边的<FONT COLOR='#CFF960'>感染体</FONT>
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			CString temp;
			temp.Format(L"%d", 主线任务.TargetId);
			加入优先打怪ID(temp);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 3000, 200);
			return;
		}
		if (主线任务.dStep == 3)//与<FONT COLOR='#CFF960'>阿曼</FONT>交谈
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return;
		}
		if (主线任务.dStep == 4)//与<FONT COLOR='#CFF960'>阿曼</FONT>交谈
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return;
		}
	}
	if (主线任务.dQuestId == 206004)//孤立无援的死灵基地
	{
		if (主线任务.dStep == 1)//消灭死灵地图的怪物
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			CString temp;
			temp.Format(L"%d", 主线任务.TargetId);
			加入优先打怪ID(temp);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 3000, 200);
			return;
		}
		if (主线任务.dStep == 2)//消灭死灵地图的怪物
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::寻路到副本(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z);
			return;
		}
	}
	if (主线任务.dQuestId == 206005)//恶意之涛
	{
		if (主线任务.dStep == 1)//消灭死灵地图的怪物
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return;
		}
		if (主线任务.dStep == 2 || 主线任务.dStep == 3)//与国境守备队队长<FONT COLOR='#CFF960'>哈米摩尔</FONT>交谈
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 200, 3000, 200);
			return;
		}
		if (主线任务.dStep == 4)//消灭死灵地图的怪物
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
	}
	if (主线任务.dQuestId == 206006)//迟来的援军  
	{
		if (主线任务.dStep == 1)//消灭死灵地图的怪物
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return;
		}
		if (主线任务.dStep == 2)//消灭死灵地图的怪物
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return;
		}
	}
	if (主线任务.dQuestId == 206007)//牺牲必将铭记于心  
	{
		if (主线任务.dStep == 1)//消灭死灵地图的怪物
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return;
		}
		if (主线任务.dStep == 2)//消灭死灵地图的怪物
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return;
		}
		if (主线任务.dStep == 3)//消灭死灵地图的怪物
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 100);
			return;
		}
		if (主线任务.dStep == 4)//前往<FONT COLOR='#CFF960'>国境地带</FONT>
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::寻路到指定传送门(19029, 13488, 221, 0x5153, 100);
			return;
		}
	}

	//循环跳出 = true;
}
void 游戏::主线_国境地带(QuestInfo_ 主线任务)
{

	if (主线任务.dQuestId == 208001)//袭击商团的是？
	{
		if (主线任务.dStep == 1)//与商人<FONT COLOR='#CFF960'>吉达</FONT>交谈
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return;
		}
		if (主线任务.dStep == 2)//与商人<FONT COLOR='#CFF960'>吉达</FONT>交谈
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return;
		}
		if (主线任务.dStep == 3)//与商人<FONT COLOR='#CFF960'>吉达</FONT>交谈
		{
			if (主线任务.子任务进度.size() == 2)
			{
				if (主线任务.子任务进度[0].dCur < 主线任务.子任务进度[0].dNeed)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					CString temp;
					temp.Format(L"%d", 主线任务.子任务进度[0].TargetID);
					加入优先打怪ID(temp);
					MyTrace(L"优先打怪数量%d", 优先打怪ID.size());
					功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 500, 2000, 200);
					return;
				}
				if (主线任务.子任务进度[1].dCur < 主线任务.子任务进度[1].dNeed)
				{

					ActorInfo_ 局_角色信息 = 本人::取角色信息();
					MyTrace(L"进度2 举起状态 %d ", 局_角色信息.举起状态);
					if (局_角色信息.举起状态 == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
						功能::到指定地点采集(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 1500, 主线任务.子任务进度[1].TargetID, 100, 150);
					}
					else if (局_角色信息.举起状态 == 4)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
						if (功能::到指定地点(任务坐标.大陆ID, 任务坐标.地图ID, 7879, 496, -3.8147e-005, 50))
						{
							objInfo_ temp = 环境::取指定对象信息(0x521F);
							技能::屏蔽鼠标();
							技能::写怪物坐标到鼠标(temp.坐标);
							UI功能::内存按键(DWORD('Q'));
							Sleep(500);
							UI功能::内存按键(DWORD('Q'));
							技能::解除屏蔽鼠标();
						}
					}

					return;
				}
			}

		}
		if (主线任务.dStep == 4)//回到商人<FONT COLOR='#CFF960'>威尼斯</FONT>身边
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return;
		}
		if (主线任务.dStep == 5)//去修道院寻找修道士<FONT COLOR='#CFF960'>奥雷德</FONT>
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return;
		}
	}
	if (主线任务.dQuestId == 208003)//新的瘟疫？
	{
		if (主线任务.dStep == 1)//与修道士<FONT COLOR='#CFF960'>奥雷德</FONT>交谈
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return;
		}
		if (主线任务.dStep == 2)//与修道士<FONT COLOR='#CFF960'>奥雷德</FONT>交谈
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"21004");
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 1000, 100);
			return;

		}
		if (主线任务.dStep == 3)//回到修道士<FONT COLOR='#CFF960'>奥雷德</FONT>身边
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return;
		}
		if (主线任务.dStep == 4)//与<FONT COLOR='#CFF960'>阿曼</FONT>交谈
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return;
		}
	}
	if (主线任务.dQuestId == 208004)//跟修道士<FONT COLOR='#CFF960'>奥雷德</FONT>打听宝玉的下落
	{
		if (主线任务.dStep == 1)//与修道士<FONT COLOR='#CFF960'>奥雷德</FONT>交谈
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return;
		}
		if (主线任务.dStep == 2)//跟修道士<FONT COLOR='#CFF960'>迪连</FONT>打听宝玉的下落
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return;
		}
		if (主线任务.dStep == 3)//消灭国境哨所附近的<FONT COLOR='#CFF960'>消灭巨型尸蛛</FONT>
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			CString temp;
			temp.Format(L"%d", 主线任务.TargetId);
			加入优先打怪ID(temp);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 3000, 200);
			return;
		}
		if (主线任务.dStep == 4)//回到修道士<FONT COLOR='#CFF960'>迪连</FONT>身边
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return;
		}
	}
	if (主线任务.dQuestId == 209001)//蛇中宝石
	{
		if (主线任务.dStep == 1)//到达<FONT color='{0}'>洞穴深处</FONT>
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			//DWORD 角度 = 取相对角度(8249, -858);
			坐标_ 角色坐标 = 本人::取坐标();
			if (角色坐标.y >= -858 || (-858) - 角色坐标.y <= 50)
			{
				MyTrace(L"分段1");
				if (功能::移动打怪(8268, -887, 483, 50, 1000, 100))
				{
					功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 8268, -887, 483, 50);
				}
			}
			return;
		}
		if (主线任务.dStep == 2)//击败占领洞穴的<FONT color='{0}'>瘟疫军团</FONT>
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 1500, 100);
			return;
		}
		if (主线任务.dStep == 3)//破坏成熟的<FONT color='{0}'>掘墓人的蛋袋</FONT>
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			CString temp;
			temp.Format(L"%d", 主线任务.TargetId);
			加入优先打怪ID(temp);
			功能::移动打怪(12915.000, -991.000, 477.000, 50, 3000, 3000);
			return;
		}
		if (主线任务.dStep == 4)//破坏成熟的<FONT color='{0}'>掘墓人的蛋袋</FONT>
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 3000, 100);
			return;
		}
		if (主线任务.dStep == 5)//破坏成熟的<FONT color='{0}'>掘墓人的蛋袋</FONT>
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			CString temp;
			temp.Format(L"%d", 主线任务.TargetId);
			加入优先打怪ID(temp);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 3000, 100);
			return;
		}
		if (主线任务.dStep == 6)//到达洞穴的<FONT color='{0}'>最深处</FONT>
		{
			功能::寻路到指定传送门(12906, 8815, 468, 21132, 200);
			return;
			//功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 3000, 100);
		}
		if (主线任务.dStep == 7)//到达洞穴的<FONT color='{0}'>最深处</FONT>
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			CString temp;
			temp.Format(L"%d", 主线任务.TargetId);
			加入优先打怪ID(temp);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 3000, 100);
			return;
		}
		if (主线任务.dStep == 8)//到达洞穴的<FONT color='{0}'>最深处</FONT>
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 16559, 11826, 119, 150);
			return;
		}
	}
	if (主线任务.dQuestId == 209002)//蛇中宝石
	{
		if (主线任务.dStep == 1)//在阿吉罗斯之尾寻找蛇王宝玉
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::寻路到副本(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z);
			return;
		}

	}
	if (主线任务.dQuestId == 208005)//边境之旅
	{
		if (地图::取地图ID() == 10252)
		{
			本人::CALL_演奏乐谱(1);
			Sleep(10000);
			return;
		}
		if (主线任务.dStep == 1)//在阿吉罗斯之尾寻找蛇王宝玉
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return;
		}
		if (主线任务.dStep == 2)//在阿吉罗斯之尾寻找蛇王宝玉
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return;
		}
		if (主线任务.dStep == 3)//在阿吉罗斯之尾寻找蛇王宝玉
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return;
		}
		if (主线任务.dStep == 4)//在阿吉罗斯之尾寻找蛇王宝玉
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return;
		}
	}
	//循环跳出 = true;
}
void 游戏::主线_萨尔兰德丘陵(QuestInfo_ 主线任务)
{
	if (主线任务.dQuestId == 601001)//寻找流浪民
	{
		if (主线任务.dStep == 1)//与<FONT COLOR='#FF973A'>阿曼</FONT>对话  0/1
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return;
		}
		if (主线任务.dStep == 2)//与<FONT COLOR='#FF973A'>阿曼</FONT>对话  0/1
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return;
		}
	}
	if (主线任务.dQuestId == 601002)//燃烧的营地
	{
		if (主线任务.dStep == 1)//与<FONT COLOR='{0}'>阿曼</FONT>对话
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return;
		}
		if (主线任务.dStep == 2)//与流浪民长老交谈<FONT COLOR='{0}'>托莱伦</FONT>
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return;
		}
		if (主线任务.dStep == 3)//与临时营地北侧的<FONT color='{0}'>鲍乌根</FONT>对话
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return;
		}
		if (主线任务.dStep == 4)//与临时营地北侧的<FONT color='{0}'>鲍乌根</FONT>对话
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return;
		}
		if (主线任务.dStep == 5)//与临时营地北侧的<FONT color='{0}'>鲍乌根</FONT>对话
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			CString temp;
			temp.Format(L"%d", 主线任务.TargetId);
			加入优先打怪ID(temp);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 2000, 100);
			return;
		}
	}
	if (主线任务.dQuestId == 601003)//燃烧的营地
	{
		if (主线任务.dStep == 1)//与<FONT COLOR='{0}'>格斯</FONT>对话
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return;
		}
		if (主线任务.dStep == 2)//在前往盐场的路上击败 <FONT COLOR='{0}'>白沙盗贼团抢劫者</FONT>
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			CString temp;
			temp.Format(L"%d", 主线任务.TargetId);
			加入优先打怪ID(temp);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 2000, 100);
			return;
		}
		if (主线任务.dStep == 3)//与游牧领袖 <FONT COLOR='{0}'>巴尔迪</FONT> 交谈
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return;
		}
	}
	if (主线任务.dQuestId == 601004)// 盐场
	{
		if (主线任务.dStep == 1)//与<FONT COLOR='{0}'>阿曼</FONT>对话
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return;
		}
		if (主线任务.dStep == 2)//与<FONT COLOR='{0}'>阿曼</FONT>对话
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return;
		}
		if (主线任务.dStep == 3)//与<FONT COLOR='{0}'>阿曼</FONT>对话
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return;
		}
	}
	if (主线任务.dQuestId == 601005)// 盐场
	{
		if (主线任务.dStep == 1)//与<FONT COLOR='{0}'>阿曼</FONT>对话
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 2)//与<FONT COLOR='{0}'>阿曼</FONT>对话
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点采集(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 1500, 60181, 100, 150);
			return;
		}
	}
	if (主线任务.dQuestId == 601006)// 盐场
	{
		if (主线任务.dStep == 1)//与<FONT COLOR='{0}'>阿曼</FONT>对话
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 2)//与<FONT COLOR='{0}'>阿曼</FONT>对话
		{
			if (主线任务.子任务进度.size() == 2)
			{
				if (主线任务.子任务进度[0].dCur < 主线任务.子任务进度[0].dNeed)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					CString temp;
					temp.Format(L"%d", 主线任务.子任务进度[0].TargetID);
					加入优先打怪ID(temp);
					MyTrace(L"优先打怪数量%d", 优先打怪ID.size());
					功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 500, 2000, 200);
					return;
				}
				if (主线任务.子任务进度[1].dCur < 主线任务.子任务进度[1].dNeed)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					坐标_ 角色坐标 = 本人::取坐标();
					if (角色坐标.z < 900)
					{
						if (!功能::优先打怪(100))
						{
							return;
						}
						if (本人::是否在走路() == true)
						{
							return;
						}
						if (地图::指定地点是否可到达_M(11116, 2098, 769.167))
						{
							功能::到指定地点按G(17, 任务坐标.地图ID, 11116, 2098, 769.167, 50);
							Sleep(1000);
							return;
						}
						if (地图::指定地点是否可到达_M(10442, 4037, 772.167))
						{
							功能::到指定地点按G(17, 任务坐标.地图ID, 10442, 4037, 772.167, 50);
							Sleep(1000);
							return;
						}
					}
					else
					{
						CString temp;
						temp.Format(L"%d", 主线任务.子任务进度[1].TargetID);
						加入优先打怪ID(temp);
						功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 2000, 100);
					}

					/*坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					CString temp;
					temp.Format(L"%d", 主线任务.TargetId);
					加入优先打怪ID(temp);
					功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 2000, 100);*/
				}
			}
			return;
		}
		if (主线任务.dStep == 3)//与<FONT COLOR='{0}'>阿曼</FONT>对话
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			坐标_ 角色坐标 = 本人::取坐标();
			if (角色坐标.z > 900)
			{
				if (地图::指定地点是否可到达_M(9028, 3885, 1029.17))
				{
					功能::到指定地点按G(17, 任务坐标.地图ID, 9028, 3885, 1029.17, 50);
					Sleep(1000);
					return;
				}
			}
			else
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
				return;
			}

		}
	}
	if (主线任务.dQuestId == 601007)// 另一块石碑
	{
		if (主线任务.dStep == 1)//与<FONT COLOR='{0}'>阿曼</FONT>对话
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return;
		}
		if (主线任务.dStep == 2)//与石碑对话
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点采集(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 1000, 主线任务.TargetId, 100, 150);
			return;

		}
		if (主线任务.dStep == 3)//前往 <FONT COLOR='{0}'>阿雷加蓝盐平原</FONT>
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 100);
			return;
		}
	}
	if (主线任务.dQuestId == 602001)// 阿雷加蓝盐平原  
	{
		if (主线任务.dStep == 1)//与<FONT COLOR='{0}'>阿曼</FONT>对话
		{
			if (主线任务.子任务进度.size() == 3)
			{
				if (主线任务.子任务进度[0].dCur < 主线任务.子任务进度[0].dNeed)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, 11815, 15898, 512, 主线任务.子任务进度[0].TargetID, 主线任务.dQuestId, -1, 50);
					return;
				}
				if (主线任务.子任务进度[1].dCur < 主线任务.子任务进度[1].dNeed)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);

					功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, 10784, 17421, 512, 主线任务.子任务进度[1].TargetID, 主线任务.dQuestId, -1, 50);
					return;
				}
				if (主线任务.子任务进度[2].dCur < 主线任务.子任务进度[2].dNeed)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, 12198, 18747, 510, 主线任务.子任务进度[2].TargetID, 主线任务.dQuestId, -1, 50);
					return;
				}
			}

		}
		if (主线任务.dStep == 2)//与流浪民<FONT COLOR='{0}'>雷比尔</FONT> 交谈
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return;
		}
		if (主线任务.dStep == 3)//与流浪民<FONT COLOR='{0}'>雷比尔</FONT> 交谈
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return;
		}


	}
	if (主线任务.dQuestId == 602002)// 阿雷加蓝盐平原  
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 100);
			return;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			CString temp;
			temp.Format(L"%d", 主线任务.TargetId);
			加入优先打怪ID(temp);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 2000, 100);
			return;
		}
		if (主线任务.dStep == 3)//可能有问题
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return;
		}
	}
	if (主线任务.dQuestId == 602004)// 最后的石碑   
	{
		if (主线任务.dStep == 1)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return;
		}
		if (主线任务.dStep == 2)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return;
		}
		if (主线任务.dStep == 3)//查看石碑
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(17, 任务坐标.地图ID, 27055, 20782, 507, 150);
			return;
		}
	}
	if (主线任务.dQuestId == 602005)// 优先事项
	{
		if (主线任务.dStep == 1)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return;
		}
		if (主线任务.dStep == 2)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return;
		}
		if (主线任务.dStep == 3)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 100);
			return;
		}
		if (主线任务.dStep == 4)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(17, 任务坐标.地图ID, 24311, 33432, 776, 150);
			return;
		}
	}
	if (主线任务.dQuestId == 602401)// 流浪民的会合
	{
		if (主线任务.dStep == 1)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return;
		}
		if (主线任务.dStep == 2)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入暂时不打ID(L"160450");
			加入优先打怪ID(L"160490|160480|160470");
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 2000, 100);
			return;
		}
		if (主线任务.dStep == 3)//
		{
			if (UI功能::怪物击杀求饶界面是否打开() == true)
			{
				UI功能::内存按键(DWORD('G'));
				Sleep(200);
			}
			暂时不打ID.clear();
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"160500");
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 2000, 100);
			return;
		}
		if (主线任务.dStep == 4)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return;
		}
	}
	if (主线任务.dQuestId == 602007)// 流浪民的会合
	{
		if (主线任务.dStep == 1)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return;
		}
		if (主线任务.dStep == 2)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点采集(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 1000, 0xEB35, 100, 250);
			return;
		}
		if (主线任务.dStep == 3)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return;
		}
		if (主线任务.dStep == 4)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return;
		}
		if (主线任务.dStep == 5)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 200);
			return;
		}
	}
	if (主线任务.dQuestId == 602008)// :朝着莫拉伊出发
	{
		if (主线任务.dStep == 1)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return;
		}
		if (主线任务.dStep == 2)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return;
		}
		if (主线任务.dStep == 3)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(17, 任务坐标.地图ID, 18447, 17904, 513, 50);
			return;
		}

	}
	if (主线任务.dQuestId == 602009)// :朝着莫拉伊出发
	{
		if (主线任务.dStep == 1)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::寻路到副本(17, 10611, 17644, 17658, 517);
			return;
		}
	}
	if (主线任务.dQuestId == 602402)// :莫拉伊遗迹 副本
	{
		if (主线任务.dStep == 1)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return;
		}
		if (主线任务.dStep == 2)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (本人::是否在走路())
			{
				return;
			}
			if (地图::指定地点是否可到达_M(-1215.3, 1554.16, -501.651))
			{
				功能::到指定地点按G(17, 任务坐标.地图ID, -1215.3, 1554.16, -501.651, 50);
				return;
			}
			else
			{
				功能::到指定地点按G(17, 任务坐标.地图ID, -984, -911, 3.63446, 50);
				return;
			}
		}
		if (主线任务.dStep == 3)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return;
		}
		if (主线任务.dStep == 4)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"169010");
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 2000, 100);
			return;
		}
		if (主线任务.dStep == 5)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (本人::是否在走路())
			{
				return;
			}
			if (地图::指定地点是否可到达_M(250, 2529, -512))
			{
				功能::到指定地点按G(17, 任务坐标.地图ID, 250, 2529, -512, 50);

			}
			return;
			/*else
			{
				功能::到指定地点按G(17, 任务坐标.地图ID, -984, -911, 3.63446, 50);
				return;
			}*/
		}
		if (主线任务.dStep == 6)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			坐标_ 角色坐标 = 本人::取坐标();
			if (角色坐标.y < 5506)
			{
				if (功能::移动打怪(2506, 5460, -504.134, 50, 1000, 100))
				{
					功能::到指定地点按G(17, 任务坐标.地图ID, 2506, 5460, -504.134, 50);
				}
			}
			else
			{
				if (角色坐标.x < 2900)
				{
					if (功能::移动打怪(2834, 6488, -511, 50, 1000, 100))
					{
						功能::到指定地点按G(17, 任务坐标.地图ID, 2834, 6488, -511, 50);
					}
				}
				else
				{
					功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 1000, 100);
				}

			}


			return;

		}
		if (主线任务.dStep == 7)//
		{
			if (主线任务.子任务进度.size() == 3)
			{
				if (主线任务.子任务进度[0].dCur < 主线任务.子任务进度[0].dNeed)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					if (功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 1500, 100))
					{
						功能::到指定地点按G(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 150);
					}
					return;
				}
				if (主线任务.子任务进度[1].dCur < 主线任务.子任务进度[1].dNeed)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					坐标_ 角色坐标 = 本人::取坐标();
					if (角色坐标.x < 7415)
					{
						if (功能::移动打怪(7385, 4762, -237, 50, 1500, 100))
						{
							功能::到指定地点按G(17, 任务坐标.地图ID, 7385, 4762, -237, 50);
						}
						return;
					}
					else
					{
						if (GetDis(7752, 4829, 0) < 250)
						{
							功能::到指定地点按G(17, 任务坐标.地图ID, 7752, 4829, 0, 50);
							return;
						}
						if (GetDis(7660, 5190, 0) < 250)
						{
							功能::到指定地点按G(17, 任务坐标.地图ID, 7660, 5190, 0, 50);
							return;
						}
						if (角色坐标.z > 200)
						{
							if (功能::移动打怪(8138, 3560, 249, 50, 1500, 100))
							{
								功能::到指定地点按G(17, 任务坐标.地图ID, 8138, 3560, 249, 150);
							}
						}
						return;
					}
					/*坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);

					功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, 10784, 17421, 512, 主线任务.子任务进度[1].TargetID, 主线任务.dQuestId, -1, 50);
					return;*/
				}
				if (主线任务.子任务进度[2].dCur < 主线任务.子任务进度[2].dNeed)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					坐标_ 角色坐标 = 本人::取坐标();
					if (角色坐标.y < 6600 || 角色坐标.z>200)
					{
						if (功能::移动打怪(8458, 6596, 281, 50, 1500, 100))
						{
							功能::到指定地点按G(17, 任务坐标.地图ID, 8458, 6596, 281, 150);
						}
						return;
					}
					else
					{
						if (角色坐标.x > 6900)
						{
							if (功能::移动打怪(6975, 10147, -767, 50, 1500, 100))
							{
								功能::到指定地点按G(17, 任务坐标.地图ID, 6975, 10147, -767, 150);
							}
							return;
						}
						else
						{
							if (功能::移动打怪(6143, 11087, -767, 50, 1500, 100))
							{
								功能::到指定地点按G(17, 任务坐标.地图ID, 6143, 11087, -767, 150);
							}
							return;
						}
					}
					/*坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, 12198, 18747, 510, 主线任务.子任务进度[2].TargetID, 主线任务.dQuestId, -1, 50);
					return;*/
				}
			}

		}
		if (主线任务.dStep == 8)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			坐标_ 角色坐标 = 本人::取坐标();
			if (角色坐标.y > 8700)
			{
				if (功能::移动打怪(6386, 8776, -1277, 50, 1500, 100))
				{
					功能::到指定地点按G(17, 任务坐标.地图ID, 6386, 8776, -1277, 150);
				}
				return;
			}
			else
			{
				if (功能::移动打怪(7141, 7792, -1262, 50, 1500, 100))
				{

				}
			}
			return;
		}
		if (主线任务.dStep == 9)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			坐标_ 角色坐标 = 本人::取坐标();
			if (角色坐标.x < 9050)
			{
				if (功能::移动打怪(9001, 7672, -1256, 50, 1500, 100))
				{
					功能::到指定地点按G(17, 任务坐标.地图ID, 9001, 7672, -1256, 150);
				}
				return;
			}
			else
			{
				if (功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 1500, 100))
				{
					功能::到指定地点按G(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 150);
				}
				return;
			}
		}
		if (主线任务.dStep == 10)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"169061");
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 1500, 100);
			return;
		}
		if (主线任务.dStep == 11)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			坐标_ 角色坐标 = 本人::取坐标();
			if (角色坐标.z < -700)
			{
				功能::到指定地点按G(17, 任务坐标.地图ID, 12508, 10854, -761, 150);
				return;
			}
			else
			{
				if (地图::指定地点是否可到达_M(任务坐标.x, 任务坐标.y, 任务坐标.z))
				{
					功能::到指定地点按G(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 150);
				}
				else
				{
					功能::到指定地点按G(17, 任务坐标.地图ID, 角色坐标.x, 角色坐标.y + 250, 角色坐标.z, 150);
				}


				return;
			}
		}
		if (主线任务.dStep == 12)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			//功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 1500, 100);
			坐标_ 角色坐标 = 本人::取坐标();
			if (角色坐标.z > -250)
			{
				功能::到指定地点按G(17, 任务坐标.地图ID, 12469, 13817, -215, 150);
				return;
			}
			else
			{
				//功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 1500, 100);
				if (角色坐标.x > 8900)
				{
					if (功能::移动打怪(9007, 16597, -1531, 50, 1500, 100))
					{
						功能::到指定地点按G(17, 任务坐标.地图ID, 9007, 16597, -1531, 150);
					}
				}
				else
				{
					功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 1500, 100);
				}
				return;
			}
		}
		if (主线任务.dStep == 13)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"60507");
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 1500, 100);
			return;
		}
		if (主线任务.dStep == 14)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			坐标_ 角色坐标 = 本人::取坐标();

			if (角色坐标.z < -2000)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 1500, 100);
				return;
			}
			else
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				坐标_ 角色坐标 = 本人::取坐标();
				if (角色坐标.z <= -917)
				{
					if (功能::移动打怪(10762, 14561, -1018, 50, 1500, 100))
					{
						功能::到指定地点按G(17, 任务坐标.地图ID, 10762, 14561, -1018, 150);
					}
					return;
				}
				if (角色坐标.z <= -200)
				{
					if (功能::移动打怪(11384, 15101, -496, 50, 1500, 100))
					{
						功能::到指定地点按G(17, 任务坐标.地图ID, 11384, 15101, -496, 150);
					}
					return;
				}
				else
				{
					CString temp;
					temp.Format(L"%d", 主线任务.TargetId);
					加入优先打怪ID(temp);
					功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 1500, 100);
					return;
				}



			}
		}
		if (主线任务.dStep == 15)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			坐标_ 角色坐标 = 本人::取坐标();
			if (角色坐标.y < 17000)
			{
				if (角色坐标.z < 100)
				{
					if (功能::移动打怪(14414, 15024, 5, 50, 1500, 100))
					{
						功能::到指定地点按G(17, 任务坐标.地图ID, 14414, 15024, 5, 150);
					}
				}
				else
				{
					if (功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 3000, 300))
					{
						功能::到指定地点按G(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 150);
					}
				}
			}
			else
			{
				if (角色坐标.x < 17000)
				{
					if (功能::移动打怪(16856, 18937, -5, 50, 1000, 100))
					{
						功能::到指定地点按G(17, 任务坐标.地图ID, 16856, 18937, -5, 300);
					}
				}
				else
				{
					if (角色坐标.y < 19750 && 角色坐标.y>17000)
					{
						if (功能::移动打怪(18139, 19642, 11, 50, 1000, 100))
						{
							功能::到指定地点按G(17, 任务坐标.地图ID, 18139, 19642, 11, 300);
						}
					}
					else
					{
						功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 3000, 300);
					}
				}
			}

			return;
		}
		if (主线任务.dStep == 16)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 3000, 300);
			return;
		}
		if (主线任务.dStep == 17)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			CString temp;
			temp.Format(L"%d", 主线任务.TargetId);
			加入优先打怪ID(temp);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 3000, 300);
			return;
		}
		if (主线任务.dStep == 18)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			ActorInfo_ 角色信息 = 本人::取角色信息();
			if (功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 1000, 3000, 300))
			{
				MyTrace(L"到指定地点采集");
				if (角色信息.举起状态 == 1)
				{
					功能::到指定地点采集任务显示(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 3000, 0xEC6E, 100, 100);
				}
				else
				{
					if (功能::到指定地点(17, 任务坐标.地图ID, 18168, 24322, -117, 50))
					{
						objInfo_ 怪物信息 = 环境::取指定对象信息(0x31196);
						技能::屏蔽鼠标();
						技能::写怪物坐标到鼠标(怪物信息.坐标);
						UI功能::内存按键(DWORD('Q'));
						Sleep(10000);
						技能::解除屏蔽鼠标();
					}

				}

			}
			return;

		}
		if (主线任务.dStep == 19)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点采集任务显示(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 1500, 0xEC73, 100, 100);
			return;
		}
	}
	if (主线任务.dQuestId == 602010)
	{
		if (主线任务.dStep == 1)
		{
			if (地图::取地图ID() == 10691)
			{
				objInfo_ 宝箱 = 环境::取指定任务显示对象信息(0xEC86);
				if (宝箱.dResShow != 0)
				{
					功能::到指定地点采集任务显示(17, 10691, 宝箱.坐标.x, 宝箱.坐标.y, 宝箱.坐标.z, 1500, 0xEC86, 100, 100);
				}
				else
				{
					if (功能::拾取道具(1000))
					{
						本人::CALL_演奏乐谱(1);
						Sleep(10000);
					}

				}
			}
			else
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			}
			return;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return;
		}
	}


}
void 游戏::主线_奥兹霍丘陵(QuestInfo_ 主线任务)
{
	if (主线任务.dQuestId == 603001)
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return;
		}
	}
	if (主线任务.dQuestId == 603002)
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(17, 任务坐标.地图ID, -8390, -6451, -111, 100);

			//功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, -8390, -6451, -111, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(17, 任务坐标.地图ID, 764, 1711, 512, 50);
			return;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return;
		}
	}
	if (主线任务.dQuestId == 603003)
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			CString temp;
			temp.Format(L"%d", 主线任务.TargetId);
			加入优先打怪ID(temp);
			功能::移动打怪(5291, -8673, 704, 50, 3000, 100);
			return;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return;
		}
		if (主线任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return;
		}
	}

}
void 游戏::主线_扎格拉斯山(QuestInfo_ 主线任务)
{
	if (主线任务.dQuestId == 603005)
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return;
		}
	}
	if (主线任务.dQuestId == 802001)
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
	}
	if (主线任务.dQuestId == 802002)//变成废墟的哨所
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return;
		}
	}
	if (主线任务.dQuestId == 802003)//前往扎格拉斯要塞
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::寻路到副本(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z);
			return;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return;
		}

	}
	if (主线任务.dQuestId == 802004)//命运之轮开始转动
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 300, 1500, 150);
			return;
		}
	}
	if (主线任务.dQuestId == 802005)//阿曼的请求
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点采集(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 2000, 0x139BA, 100, 150);
			return;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return;
		}
	}
	if (主线任务.dQuestId == 802007)//阿曼的请求
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点采集(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 2000, 0x139BB, 100, 250);
			return;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return;
		}
		if (主线任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点采集(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 2000, 主线任务.TargetId, 100, 250);
			return;
		}
		if (主线任务.dStep == 6)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return;
		}
	}
	if (主线任务.dQuestId == 802008)//阿曼的请求
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"180320");
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 300, 1500, 150);
			return;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return;
		}
	}
	if (主线任务.dQuestId == 802009)//阿曼的请求
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点采集(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 2000, 0x139BC, 100, 250);
			return;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 6)
		{
			背包::使用背包指定物品_ByResId(0x75304);
			Sleep(500);
			return;
		}
		if (主线任务.dStep == 7)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}

	}
	if (主线任务.dQuestId == 802010)//前往雷科巴
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
	}

}
void 游戏::主线_雷科巴(QuestInfo_ 主线任务)
{
	if (主线任务.dQuestId == 803001)
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::寻路到副本(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z);
			return;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
	}
	if (主线任务.dQuestId == 803002)
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (功能::到指定地点(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50))
			{
				本人::CALL_做社交动作(0xF23E);
				Sleep(5000);
			}
			return;
		}
		if (主线任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 300, 1500, 150);
			return;
		}
		if (主线任务.dStep == 6)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"180393");
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 300, 1500, 150);
			return;
		}
	}
	if (主线任务.dQuestId == 803003)
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 2)
		{
			if (主线任务.子任务进度.size() == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				if (主线任务.子任务进度[0].dCur < 主线任务.子任务进度[0].dNeed)
				{
					CString temp;
					temp.Format(L"%d", 主线任务.子任务进度[0].TargetID);
					加入优先打怪ID(temp);
					功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 300, 1500, 100);
				}
				if (主线任务.子任务进度[1].dCur < 主线任务.子任务进度[1].dNeed)
				{
					CString temp;
					temp.Format(L"%d", 主线任务.子任务进度[1].TargetID);
					加入优先打怪ID(temp);
					功能::移动打怪(10099, -678, 2048, 300, 1500, 100);
				}


			}
			return;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}

	}
	if (主线任务.dQuestId == 803004)
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
	}
	if (主线任务.dQuestId == 803005)//铁王冠
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 2)
		{
			if (主线任务.子任务进度.size() == 3)
			{
				//坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				if (主线任务.子任务进度[0].dCur < 主线任务.子任务进度[0].dNeed)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点找NPC交任务2(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.子任务进度[0].TargetID, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
					return;
				}
				if (主线任务.子任务进度[1].dCur < 主线任务.子任务进度[1].dNeed)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点找NPC交任务2(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.子任务进度[1].TargetID, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
					return;
				}
				if (主线任务.子任务进度[2].dCur < 主线任务.子任务进度[2].dNeed)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点找NPC交任务2(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.子任务进度[2].TargetID, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
					return;
				}
			}

		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
	}
	if (主线任务.dQuestId == 803006)//卢特兰的精神
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 3)
		{
			if (主线任务.子任务进度.size() == 3)
			{
				//坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				if (主线任务.子任务进度[0].dCur < 主线任务.子任务进度[0].dNeed)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点找NPC交任务2(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.子任务进度[0].TargetID, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
					return;
				}
				if (主线任务.子任务进度[1].dCur < 主线任务.子任务进度[1].dNeed)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点找NPC交任务2(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.子任务进度[1].TargetID, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
					return;
				}
				if (主线任务.子任务进度[2].dCur < 主线任务.子任务进度[2].dNeed)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点找NPC交任务2(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.子任务进度[2].TargetID, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
					return;
				}
			}

		}
	}
	if (主线任务.dQuestId == 803007)//雷科巴的王冠
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 4)
		{
			UI功能::内存按键(VK_F5);
			Sleep(5000);
			return;
		}
		if (主线任务.dStep == 5)
		{
			if (主线任务.子任务进度.size() == 2)
			{
				//坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				if (主线任务.子任务进度[0].dCur < 主线任务.子任务进度[0].dNeed)
				{
					加入优先打怪ID(L"180211|180360");
					功能::移动打怪(14978, 8883, 1024, 300, 3000, 100);
					return;
				}
				if (主线任务.子任务进度[1].dCur < 主线任务.子任务进度[1].dNeed)
				{
					加入优先打怪ID(L"180221|180232|20180450");
					功能::移动打怪(21299, 10984, 1532, 300, 3000, 100);
					return;
				}
			}
		}
		if (主线任务.dStep == 6)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 7)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
	}
	if (主线任务.dQuestId == 803008)//前往光辉山脊
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 2)
		{
			if (主线任务.dState == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
				return;
			}
			else
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务2(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0x2F37, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
				return;
			}

		}
	}
	if (主线任务.dQuestId == 804002)//光辉山脊
	{
		if (主线任务.dStep == 1)//操作:CEFQuestOption_End_ClearDungeon
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::寻路到副本(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z);
			return;
		}
	}
	if (主线任务.dQuestId == 804001)//光辉山脊
	{
		if (主线任务.dStep == 1)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return;
		}
		if (主线任务.dStep == 2)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 3000, 2000);
			return;
		}
		if (主线任务.dStep == 3)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"180500|180490");
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 3000, 150);
			return;
		}
		if (主线任务.dStep == 4)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(13965, 19263, 512, 50, 1500, 150);
			return;
		}
		if (主线任务.dStep == 5)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"180540");
			暂时不打ID.clear();
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 3000, 150);
			return;
		}
		if (主线任务.dStep == 6)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 1500, 50);
			return;
		}
		if (主线任务.dStep == 7)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 250);
			return;
		}
		if (主线任务.dStep == 8)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return;
		}
		if (主线任务.dStep == 9)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
	}
	if (主线任务.dQuestId == 804003)//前往梅德里克修道院
	{
		if (主线任务.dStep == 1)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 主线任务.dQuestId, -1, 50, 0);
			return;
		}
		if (主线任务.dStep == 2)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 主线任务.dQuestId, -1, 50, 0);
			return;
		}
	}

}
void 游戏::主线_梅德里克修道院(QuestInfo_ 主线任务)
{
	if (主线任务.dQuestId == 805001)//悬崖尽头的修道院
	{
		if (主线任务.dStep == 1)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 主线任务.dQuestId, -1, 50, 0);
			return;
		}
		if (主线任务.dStep == 2)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 3)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::寻路到副本(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z);
			return;
		}
		if (主线任务.dStep == 4)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
	}
	if (主线任务.dQuestId == 805002)//勇气的含义
	{
		if (主线任务.dStep == 1)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 2)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 3)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 4)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 5)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (功能::到指定地点(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50))
			{
				本人::CALL_演奏乐谱(2);
				Sleep(15000);
			}
			return;
		}
		if (主线任务.dStep == 6)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
	}
	if (主线任务.dQuestId == 805003)//梅德里克的战斗祭司
	{
		if (主线任务.dStep == 1)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 2)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 3)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 4)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"180580|180590");
			暂时不打ID.clear();
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 3000, 150);
			return;
		}
		if (主线任务.dStep == 5)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
	}
	if (主线任务.dQuestId == 805004)//梅德里克的战斗祭司
	{
		if (主线任务.dStep == 1)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 2)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 3)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 4)//
		{
			if (主线任务.子任务进度.size() == 2)
			{
				if (主线任务.子任务进度[0].dCur < 主线任务.子任务进度[0].dNeed)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					加入优先打怪ID(L"180384|180385");
					暂时不打ID.clear();
					功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 3000, 150);
					return;
				}
				if (主线任务.子任务进度[1].dCur < 主线任务.子任务进度[1].dNeed)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					if (主线任务.子任务进度[1].dCur == 0)
					{
						功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 19305, 25405, -1024, 12144, 0, -1, 50, 0);
					}
					if (主线任务.子任务进度[1].dCur == 1)
					{
						功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 19407, 24303, -1025, 12149, 0, -1, 50, 0);
					}
					if (主线任务.子任务进度[1].dCur == 2)
					{
						功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 20680, 22847, -1024, 12157, 0, -1, 50, 0);
					}
					return;
				}

			}

		}
		if (主线任务.dStep == 5)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
	}
	if (主线任务.dQuestId == 805005)//梅德里克的战斗祭司
	{
		if (主线任务.dStep == 1)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 2)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
	}

}
void 游戏::主线_比尔布森林(QuestInfo_ 主线任务)
{
	if (主线任务.dQuestId == 806001)//猎人的礼节
	{
		if (主线任务.dStep == 1)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 2)//
		{

			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"180371|180341|850117");
			暂时不打ID.clear();
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 3000, 150);
			return;
		}
		if (主线任务.dStep == 3)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
	}
	if (主线任务.dQuestId == 806002)//与民兵队接头
	{
		if (主线任务.dStep == 1)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 2)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点采集(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 2000, 0x13AE4, 100, 250);
			return;
		}
		if (主线任务.dStep == 3)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
	}
	if (主线任务.dQuestId == 806003)//与民兵队接头
	{
		if (地图::取地图ID() == 10855)
		{
			本人::CALL_演奏乐谱(1);
			Sleep(10000);
			return;
		}
		if (主线任务.dStep == 1)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 2)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 3)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 4)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 5)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"180650|180660|180670|180672|180662");
			暂时不打ID.clear();
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 3000, 150);
			return;
		}
	}
	if (主线任务.dQuestId == 806004)//与民兵队接头
	{
		if (地图::取地图ID() == 10855)
		{
			本人::CALL_演奏乐谱(1);
			Sleep(10000);
			return;
		}
		if (主线任务.dStep == 1)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 2)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 3)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::寻路到副本(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z);
			return;
		}
	}
	if (主线任务.dQuestId == 806005)//与民兵队接头
	{
		if (主线任务.dStep == 1)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 2)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (功能::到指定地点(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50))
			{
				objInfo_ 木桶 = 环境::取指定对象信息(0x13AEC);

				if (木桶.fDis > 500)
				{
					地图::本地图寻路(木桶.坐标.x, 木桶.坐标.y, 木桶.坐标.z, 0);
				}
				else
				{
					技能::屏蔽鼠标();
					技能::写怪物坐标到鼠标(木桶.坐标);
					UI功能::内存按键(VK_F5);
					Sleep(500);
					UI功能::内存按键(VK_F5);
					技能::解除屏蔽鼠标();
				}



			}
			return;
		}
		if (主线任务.dStep == 3)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"80630");
			暂时不打ID.clear();
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 3000, 150);
			return;
		}
		if (主线任务.dStep == 4)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"180654|180655");
			暂时不打ID.clear();
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 3000, 150);
			return;
		}
		if (主线任务.dStep == 5)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (主线任务.子任务进度.size() == 3)
			{
				if (主线任务.子任务进度[0].dCur < 主线任务.子任务进度[0].dNeed)
				{
					MyTrace(L"进度1");
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点采集(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 2000, 80607, 500, 250);
					return;
				}
				if (主线任务.子任务进度[1].dCur < 主线任务.子任务进度[1].dNeed)
				{
					MyTrace(L"进度2");
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					if (!功能::优先打怪(100))
					{
						return;
					}
					if (本人::是否在走路())
					{
						return;
					}
					if (地图::指定地点是否可到达_M(26362, 19306, 1791))
					{

						功能::到指定地点采集(14, 任务坐标.地图ID, 26362, 19306, 1791, 2000, 80672, 500, 250);
						return;
					}
					else
					{
						加入优先打怪ID(L"81130");
						暂时不打ID.clear();
						功能::移动打怪(25884, 21524, 1791, 50, 3000, 150);
						return;
					}

				}
				if (主线任务.子任务进度[2].dCur < 主线任务.子任务进度[2].dNeed)
				{
					MyTrace(L"进度3");
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点采集(14, 任务坐标.地图ID, 23677, 18731, 1791, 2000, 80673, 500, 250);
					return;
				}
			}
			return;
		}
		if (主线任务.dStep == 6)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"180664");
			暂时不打ID.clear();
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 3000, 150);
			return;
		}
	}
	if (主线任务.dQuestId == 806006)//坚定的信念
	{
		if (地图::取地图ID() == 10855)
		{
			本人::CALL_演奏乐谱(1);
			Sleep(10000);
			return;
		}
		if (主线任务.dStep == 1)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 2)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 3)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 4)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}

	}
	if (主线任务.dQuestId == 806007)//坚定的信念
	{
		if (地图::取地图ID() == 10855)
		{
			本人::CALL_演奏乐谱(1);
			Sleep(10000);
			return;
		}
		if (主线任务.dStep == 1)//
		{
			if (主线任务.子任务进度.size() == 5)
			{
				if (主线任务.子任务进度[0].dCur < 主线任务.子任务进度[0].dNeed)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 17082, 21974, 1536, 12227, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
					return;
				}
				if (主线任务.子任务进度[1].dCur < 主线任务.子任务进度[1].dNeed)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 18068, 22030, 1536, 12228, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
					return;
				}
				if (主线任务.子任务进度[2].dCur < 主线任务.子任务进度[2].dNeed)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 17587, 23178, 1536, 12229, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
					return;
				}
				if (主线任务.子任务进度[3].dCur < 主线任务.子任务进度[3].dNeed)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 17909, 22547, 1536, 12230, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
					return;
				}
				if (主线任务.子任务进度[4].dCur < 主线任务.子任务进度[4].dNeed)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 17348, 22516, 1536, 12231, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
					return;
				}
			}
			return;
		}
		if (主线任务.dStep == 2)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 3)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
	}
	if (主线任务.dQuestId == 822001)//空麻袋山贼团的据点 
	{
		if (主线任务.dStep == 1)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(14, 任务坐标.地图ID, 3375, 1395, 1023, 25);
			return;
		}
		if (主线任务.dStep == 2)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点采集(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 2000, 0x13C70);
			return;
		}
		if (主线任务.dStep == 3)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (功能::到指定地点(14, 任务坐标.地图ID, 3375, 1200, 1023, 50))
			{
				技能::屏蔽鼠标();
				坐标_ 新坐标;
				新坐标.x = 3377;
				新坐标.y = 1558;
				新坐标.z = 1023;
				技能::写怪物坐标到鼠标(新坐标);
				UI功能::内存按键(VK_F5);
				Sleep(500);
				UI功能::内存按键(VK_F5);
				技能::解除屏蔽鼠标();
			}
			return;
		}
		if (主线任务.dStep == 4)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			ActorInfo_ 角色信息 = 本人::取角色信息();
			if (角色信息.坐标.z > 10)
			{
				功能::到指定地点乘坐电梯(14, 任务坐标.地图ID, 3413, 4692, 1025, 25, 0x10903D);
				return;
			}
			else
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return;
			}
		}
		if (主线任务.dStep == 5)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return;
		}
		if (主线任务.dStep == 6)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"181074|181073");
			暂时不打ID.clear();
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 3000, 150);
			return;
		}
		if (主线任务.dStep == 7)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"81009|81006|181074|181073");
			暂时不打ID.clear();
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 3000, 150);
			return;

		}
		if (主线任务.dStep == 8)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"81009|81006|181074|181073");
			暂时不打ID.clear();
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 3000, 150);
			return;
		}
		if (主线任务.dStep == 9)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"81009|81006|181074|181073");
			暂时不打ID.clear();
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 3000, 150);
			return;
		}
		if (主线任务.dStep == 10)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点采集(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 2000, 81126);
			return;
		}
		if (主线任务.dStep == 11)//
		{
			ActorInfo_ 角色信息 = 本人::取角色信息();
			if (角色信息.举起状态 == 4)
			{
				if (功能::到指定地点(14, 10855, 6447, 11065, -514, 25))
				{
					UI功能::内存按键(DWORD('R'));

				}
				return;
			}
			else
			{
				//坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点采集(14, 10855, 6420, 12369, -511, 2000, 0x13CE5);

				return;
			}
		}
		if (主线任务.dStep == 12)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			//加入优先打怪ID(L"81009|81006|181074|181073");
			暂时不打ID.clear();
			功能::到指定地点(14, 10855, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return;
		}
		if (主线任务.dStep == 13)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			//加入优先打怪ID(L"81009|81006|181074|181073");
			暂时不打ID.clear();
			功能::到指定地点按G(14, 10855, 任务坐标.x, 任务坐标.y, 任务坐标.z, 200);
			return;
		}
		if (主线任务.dStep == 14)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"181072|181073");
			暂时不打ID.clear();
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 6000, 150);
			return;
		}
		if (主线任务.dStep == 15)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (本人::是否在走路())
			{
				return;
			}
			//加入优先打怪ID(L"81009|81006|181074|181073");
			if (地图::指定地点是否可到达_M(任务坐标.x, 任务坐标.y, 任务坐标.z))
			{
				暂时不打ID.clear();
				功能::到指定地点按G(14, 10855, 任务坐标.x, 任务坐标.y, 任务坐标.z, 200);
			}
			else
			{
				//坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				加入优先打怪ID(L"81120");
				暂时不打ID.clear();
				功能::移动打怪(9476, 11578, -3328, 50, 1000, 150);
				Sleep(2000);
				return;
			}

			return;
		}
		if (主线任务.dStep == 16)//
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"201090");
			暂时不打ID.clear();
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 6000, 150);
			return;
		}
	}

}
void 游戏::主线_激战平原(QuestInfo_ 主线任务)
{
	if (主线任务.dQuestId == 807001)//突破魔兽军团防线
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"180710|180740");
			//暂时不打ID.clear();
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 3000, 150);
			return;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 4)
		{
			if (主线任务.dState == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::寻路到副本(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z);
				return;
			}
			else
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
				return;
			}


		}
	}
	if (主线任务.dQuestId == 807002)//进攻
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"180830|180840");
			//暂时不打ID.clear();
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 3000, 150);
			return;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return;
		}

	}
	if (主线任务.dQuestId == 807003)//黑血荒野之战
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"180950|180850");
			//暂时不打ID.clear();
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 3000, 150);
			return;
		}
	}
	if (主线任务.dQuestId == 807004)//逆转战局
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return;
		}
	}
	if (主线任务.dQuestId == 807005)//逆转战局
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 2)
		{
			if (主线任务.子任务进度.size() == 2)
			{
				ActorInfo_ 角色信息 = 本人::取角色信息();
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				if (主线任务.子任务进度[0].dCur < 主线任务.子任务进度[0].dNeed)
				{
					if (角色信息.举起状态 == 1)
					{
						功能::到指定地点采集(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 5000, 0x13B46);
					}
					else
					{
						if (功能::到指定地点(14, 任务坐标.地图ID, 11851, 20052, 512, 50))
						{
							UI功能::内存按键(DWORD('R'));
						}
					}
					return;
				}
				if (主线任务.子任务进度[1].dCur < 主线任务.子任务进度[1].dNeed)
				{
					if (角色信息.举起状态 == 1)
					{
						功能::到指定地点采集(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 5000, 0x13B47);
					}
					else
					{
						if (功能::到指定地点(14, 任务坐标.地图ID, 11851, 20052, 512, 50))
						{
							UI功能::内存按键(DWORD('R'));
						}
					}
					return;
				}
			}


			return;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (功能::到指定地点(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 25))
			{
				本人::CALL_做社交动作(0xF23E);
				Sleep(8000);
			}
			return;
		}
		if (主线任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 250);
			return;
		}
		if (主线任务.dStep == 6)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 7)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return;
		}
	}
	if (主线任务.dQuestId == 808001)//逆转战局
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 25);
			return;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(14, 任务坐标.地图ID, -19120, -15712, 782, 100);
			return;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (功能::到指定地点(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 1000))
			{
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 1000, 150);
			}
			//暂时不打ID.clear();

			return;
		}
		if (主线任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			//暂时不打ID.clear();
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 800, 150);
			return;
		}
		if (主线任务.dStep == 6)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (GetDis(-14934, -6861, 938) <= 200)
			{
				功能::到指定地点(14, 任务坐标.地图ID, -15100, -6861, 938, 100);
				return;
			}
			else
			{

				//暂时不打ID.clear();
				if (功能::优先打怪(3000))
				{
					if (功能::到指定地点(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 1000))
					{
						功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 1000, 150);
					}
				}

			}

			return;
		}
		if (主线任务.dStep == 7)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 100);
			return;
		}
		if (主线任务.dStep == 8)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 100);
			return;
		}
		if (主线任务.dStep == 9)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 3000, 150);
			return;
		}
		if (主线任务.dStep == 10)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 100);
			return;
		}
		if (主线任务.dStep == 11)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"181051");
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 3000, 150);
			return;
		}
		if (主线任务.dStep == 12)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 5000, 150);
			return;
		}
		if (主线任务.dStep == 13)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return;
		}
		if (主线任务.dStep == 14)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"180800");
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 5000, 150);
			return;
		}
		if (主线任务.dStep == 15)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return;
		}
	}
	if (主线任务.dQuestId == 808002)//最终激战
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 角色坐标 = 本人::取坐标();
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (角色坐标.x < 14435)
			{
				功能::到指定地点按G(14, 任务坐标.地图ID, 13825, -21, -14591, 50);
			}
			else
			{
				if (UI功能::怪物击杀求饶界面是否打开())
				{
					MyTrace(L"按H服从");
					UI功能::内存按键(DWORD('H'));
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 5000, 150);
					return;
				}
			}

			//功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 5000, 150);
			return;
		}
		if (主线任务.dStep == 3)
		{

			坐标_ 角色坐标 = 本人::取坐标();
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (角色坐标.x < 14435)
			{
				功能::到指定地点按G(14, 任务坐标.地图ID, 13825, -21, -14591, 50);
			}
			else
			{

				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 5000, 150);
				return;

			}

			//功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 5000, 150);
			return;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return;
		}
		if (主线任务.dStep == 5)
		{
			ActorInfo_ 角色信息 = 本人::取角色信息();
			if (角色信息.举起状态 == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点按G(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			}
			else
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点按G(14, 任务坐标.地图ID, 5678, 217, 755, 50);
			}

			return;
		}
	}

}
void 游戏::主线_卢特兰城(QuestInfo_ 主线任务)
{
	if (主线任务.dQuestId == 801001)//突破魔兽军团防线
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(15, 任务坐标.地图ID, 11901, -1873, -14591, 200);
			return;
		}

	}
	if (主线任务.dQuestId == 801002)//重建卢特兰王国
	{
		if (主线任务.dStep == 1)
		{
			if (地图::取小地图名() == L"卢特兰王宫" /*|| 地图::取小地图名()!=L""*/)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(15, 任务坐标.地图ID, 10711, 4, -14592, 25);
				return;
			}
			else
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
				return;
			}

		}
		if (主线任务.dStep == 2)
		{
			if (主线任务.dState == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 25);
				return;
			}
			else
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
				return;
			}

		}

	}
	if (主线任务.dQuestId == 801006)//回归之歌  
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 2)
		{
			if (主线任务.dState == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点按G(15, 任务坐标.地图ID, 4695, 81, 770, 200);
				UI功能::getMsgBoxTextList();
				return;
			}
			else
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0xC75A, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
				return;
			}

		}
	}
	if (主线任务.dQuestId == 801003)//卢特兰城的人    
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
	}
	if (主线任务.dQuestId == 801005)
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
				return;
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 300, 主线任务.dStep);
				return;
			}
			if (主线任务.dStep == 3)
			{
				if (地图::取地图ID() != 10813)
				{
					地图::传送(900203);
					Sleep(10000);
					return;
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点找NPC交任务3(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 300, 主线任务.dStep);
					return;
				}

			}
			if (主线任务.dStep == 4)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点按G(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 200);
				return;
			}
			if (主线任务.dStep == 5)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 300, 主线任务.dStep);
				return;
			}
			if (主线任务.dStep == 6)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点按G(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 200);
				return;
			}
			if (主线任务.dStep == 7)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 300, 主线任务.dStep);
				return;
			}
			if (主线任务.dStep == 8)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 300, 主线任务.dStep);
				return;
			}
		}

	}

}
void 游戏::主线_迪奥利卡平原(QuestInfo_ 主线任务)
{
	if (主线任务.dQuestId == 809001)//两个家族    
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
				return;
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				加入优先打怪ID(L"182010|182020");
				功能::移动打怪(14161, 4524, 1536, 100, 3000, 100);
				//功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
				return;
			}
			if (主线任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
				return;
			}
			if (主线任务.dStep == 4)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
				return;
			}
		}
		else
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0x36BA, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}

	}
	if (主线任务.dQuestId == 809002)//以哥哥之名    
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
				return;
			}
			if (主线任务.dStep == 2)
			{
				if (主线任务.子任务进度.size() == 2)
				{
					if (主线任务.子任务进度[0].dCur == 0)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
						功能::到指定地点采集(15, 任务坐标.地图ID, 12536, 9807, 1534, 1000, 0x140CB, 100, 100);
						return;
					}
					if (主线任务.子任务进度[1].dCur == 0)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
						功能::到指定地点采集(15, 任务坐标.地图ID, 14799, 13941, 1535, 1000, 0x140CC, 100, 200);
						return;
					}
				}
			}

		}
		else
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0x36BB, 主线任务.dQuestId, -1, 150, 主线任务.dStep);
			return;
		}
	}
	if (主线任务.dQuestId == 809003)//以哥哥之名    
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
				return;
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
				return;
			}
			if (主线任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
				return;
			}
			if (主线任务.dStep == 4)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
				return;
			}
			if (主线任务.dStep == 5)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
				return;
			}
		}
		else
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0x3771, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
	}
	if (主线任务.dQuestId == 809004)//以哥哥之名    
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				if (主线任务.子任务进度.size() == 3)
				{
					if (主线任务.子任务进度[0].dCur < 主线任务.子任务进度[0].dNeed)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
						功能::到指定地点采集(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 3000, 82151);
						return;
					}
					if (主线任务.子任务进度[1].dCur < 主线任务.子任务进度[1].dNeed)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
						加入优先打怪ID(L"182280");
						功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 1000);
						return;
					}
					if (主线任务.子任务进度[2].dCur < 主线任务.子任务进度[2].dNeed)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
						加入优先打怪ID(L"182210|182220|182225|102381|182280");
						功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 500, 3000);
						return;
					}
				}
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
				return;

			}
			if (主线任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
				return;

			}

		}
		else
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0x36BA, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
	}
	if (主线任务.dQuestId == 809005)//开始真正和解      
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
				return;
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
				return;
			}
		}
	}
	if (主线任务.dQuestId == 809006)//齐心协力       
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
				return;
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::寻路到副本(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z);
				return;
			}
		}
	}
	if (主线任务.dQuestId == 809007)//罗纳云的形迹       
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				//加入优先打怪ID(L"182280");
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 500, 3000);
				return;
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				//加入优先打怪ID(L"182280");
				功能::到指定地点按G(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 100);
				return;
			}
			if (主线任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				if (主线任务.子任务进度.size() == 4)
				{
					if (主线任务.子任务进度[0].dCur == 0)
					{
						功能::到指定地点按G(15, 任务坐标.地图ID, 7317, 20426, 1024, 150, 500);
						return;
					}
					if (主线任务.子任务进度[1].dCur == 0)
					{
						功能::到指定地点按G(15, 任务坐标.地图ID, 8116, 19391, 1022, 150, 500);
						return;
					}
					if (主线任务.子任务进度[2].dCur == 0)
					{
						功能::到指定地点按G(15, 任务坐标.地图ID, 6670, 21726, 1024, 150, 500);
						return;
					}
					if (主线任务.子任务进度[3].dCur == 0)
					{
						功能::到指定地点按G(15, 任务坐标.地图ID, 6518, 19153, 1024, 150, 500);
						return;
					}
				}
				//加入优先打怪ID(L"182280");

			}
			if (主线任务.dStep == 4)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点按G(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 200);
				return;
			}
		}
	}
	if (主线任务.dQuestId == 809008)//寻找被遗忘的纹章       
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
				return;
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
				return;
			}
		}
		else
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0x36BE, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
	}
	//循环跳出 = true;
}
void 游戏::主线_圆虹之丘(QuestInfo_ 主线任务)
{
	if (主线任务.dQuestId == 810001)
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
				return;
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				加入优先打怪ID(L"182290");
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 500, 3000);
				return;
			}
			if (主线任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点按G(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 250);
				return;
			}
		}
		else
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0x36E6, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
	}
	if (主线任务.dQuestId == 810008)
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
				return;
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				加入优先打怪ID(L"182400");
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 500, 3000);
				return;
			}
			if (主线任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
				return;
			}
		}
	}
	if (主线任务.dQuestId == 810002)
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				if (主线任务.子任务进度.size() == 3)
				{
					if (主线任务.子任务进度[0].dCur < 主线任务.子任务进度[0].dNeed)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
						加入优先打怪ID(L"182460");
						功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 500, 3000);
						return;
					}
					if (主线任务.子任务进度[1].dCur < 主线任务.子任务进度[1].dNeed)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
						加入优先打怪ID(L"182350");
						功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 500, 3000);
						return;
					}
					if (主线任务.子任务进度[2].dCur < 主线任务.子任务进度[2].dNeed)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
						加入优先打怪ID(L"182330|182340");
						功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 500, 3000);
						return;
					}
				}
			}
			if (主线任务.dStep == 2)
			{
				if (主线任务.子任务进度.size() == 2)
				{
					if (主线任务.子任务进度[0].dCur < 主线任务.子任务进度[0].dNeed)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
						加入优先打怪ID(L"182360");
						功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 1000);
						return;
					}
					if (主线任务.子任务进度[1].dCur < 主线任务.子任务进度[1].dNeed)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
						加入优先打怪ID(L"182400|182403");
						功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 500, 2000);
						return;
					}

				}
			}
			if (主线任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
				return;
			}
			if (主线任务.dStep == 4)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
				return;
			}
		}
	}
	if (主线任务.dQuestId == 810003)//耳聋的吟游诗人
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点按G(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 200);
				return;

			}
		}
		else
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0x36E7, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
	}
	if (主线任务.dQuestId == 810004)//看不见的吟游诗人
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
				return;

			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
				return;

			}
			if (主线任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
				return;

			}
		}
		else
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0x36EE, 主线任务.dQuestId, -1, 150, 主线任务.dStep);
			return;
		}
	}
	if (主线任务.dQuestId == 810005)//从黄昏到黎明
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 150, 主线任务.dStep);
				return;

			}

		}
	}
	if (主线任务.dQuestId == 810401)//夜晚的向日葵农场
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 150, 主线任务.dStep);
				return;

			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 500, 1500);
				return;

			}
			if (主线任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 150, 主线任务.dStep);
				return;

			}
		}
	}
	if (主线任务.dQuestId == 810006)//王室的鹰之印章 
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 150, 主线任务.dStep);
				return;

			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 100);
				return;

			}

		}
		else
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0x3707, 主线任务.dQuestId, -1, 150, 主线任务.dStep);
			return;
		}
	}
	if (主线任务.dQuestId == 810007)//王室的鹰之印章 
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 150, 主线任务.dStep);
				return;

			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 150, 主线任务.dStep);
				return;

			}
			if (主线任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 500, 3000);
				return;
			}
			if (主线任务.dStep == 4)
			{
				UI功能::内存按键(VK_F5);
				return;
			}
			if (主线任务.dStep == 5)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 150, 主线任务.dStep);
				return;

			}
		}
		else
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 主线任务.dQuestId, -1, 150, 0);
			return;
		}
	}
	if (主线任务.dQuestId == 811001)//王室的鹰之印章 
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::寻路到副本(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z);
				return;

			}

		}
	}
	if (主线任务.dQuestId == 811101)//前往君王墓地 1 
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 150, 1000);
			return;

		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"180001");
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 500, 1500);
			return;

		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 150, 300);
			return;

		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 150);
			return;

		}
		if (主线任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"180110");
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 500, 1500);
			return;

		}
		if (主线任务.dStep == 6)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 150, 300);
			return;

		}
		if (主线任务.dStep == 7)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 150, 300);
			return;

		}
		if (主线任务.dStep == 8)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(15, 任务坐标.地图ID, 1616, 9100, 2310, 150);
			return;

		}
		if (主线任务.dStep == 9)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 150, 主线任务.dStep);
			return;

		}
		if (主线任务.dStep == 10)
		{
			ActorInfo_ 角色信息 = 本人::取角色信息();
			if (角色信息.举起状态 == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点按G(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 200, 300);//左门
				//功能::到指定地点按G(15, 任务坐标.地图ID, 2715.43 , 10119 ,2048, 200, 300);//右门
				return;
			}
			else
			{
				UI功能::内存按键('R');
				return;
			}


		}
	}
	if (主线任务.dQuestId == 811103)//前往君王墓地 2 
	{

		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"180040");
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 500, 1500);
			return;

		}
		if (主线任务.dStep == 2)
		{
			//坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (主线任务.子任务进度[0].dCur == 0)
			{
				功能::到指定地点按G(15, 10892, 7697.829, 15337.646, 1600, 200, 1000);
				return;
			}
			if (主线任务.子任务进度[0].dCur == 1)
			{
				功能::到指定地点按G(15, 10892, 6010, 15249, 1604, 200, 1000);
				return;

			}
			if (主线任务.子任务进度[0].dCur == 2)
			{
				功能::到指定地点按G(15, 10892, 5985, 13636, 1604, 200, 1000);
				return;

			}
			return;
		}

	}
	if (主线任务.dQuestId == 811105)//前往君王墓地 3
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 200, 300);
			return;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(15, 任务坐标.地图ID, 7366, 18586, 1536, 200, 300);
			return;
		}
	}
	if (主线任务.dQuestId == 811107)//前往君王墓地 4
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"80023");
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 500, 500, true);
			return;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"180041");
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 500, 500, false);
			return;
		}
	}
	if (主线任务.dQuestId == 811109)//前往君王墓地 5
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 200, 100);
			return;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return;
		}
	}
	if (主线任务.dQuestId == 811102)//罗纳云的最终试炼 
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 500);
			return;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			坐标_ 角色坐标 = 本人::取坐标();
			if (角色坐标.z < 8000)
			{
				if (GetDis(11137, 41831, 4094) <= 200)
				{
					功能::到指定地点(15, 任务坐标.地图ID, 角色坐标.x - 200, 角色坐标.y + 200, 4099, 50);
					return;
				}
				objInfo_ 怪物信息 = 环境::取指定对象信息(0x2BF98);
				if (怪物信息.dResId == 0x2BF98 && 怪物信息.dCurHp > 0 && 怪物信息.IsHide == false && 怪物信息.dMaxHp == 10849)
				{
					怪物信息.坐标.x = 9740;
					怪物信息.坐标.y = 42042;
					怪物信息.坐标.z = 4097;
					if (GetDis(9740, 42042, 4097) > 500)
					{
						//10139, 41455, 4097
						地图::本地图寻路(9917, 41728, 4097, 0);
					}
					else
					{
						objInfo_ 开关信息;
						功能::打怪程序2(怪物信息.objBase, 怪物信息.坐标, 开关信息);
					}

					return;
				}
				else
				{
					if (GetDis(6773, 45268, 6149) <= 300)
					{
						功能::到指定地点乘坐电梯(15, 任务坐标.地图ID, 6773, 45268, 6149, 50, 0);
					}
					else
					{
						加入优先打怪ID(L"80101|80102");
						if (功能::优先破坏击打道具(3000))
						{
							功能::移动打怪(6773, 45268, 6149, 50, 10000, 10000, true, 1000);
						}

					}

					return;
				}
			}
			else
			{
				//坐标_ 角色坐标 = 本人::取坐标();
				int 角度 = DWORD(Get_Rel_Angle(9104, 43919, 角色坐标.x, 角色坐标.y) * 0.00549317);
				MyTrace(L"角度 %d", 角度);
				if (角度 > 80 && 角度 < 220)
				{
					MyTrace(L"第一关 角度:%d", 角度);
					objInfo_ 开关信息 = 环境::取指定对象信息(0x138E8);
					if (开关信息.dPortalOpen != 2 && 开关信息.dObjId != 0)
					{
						objInfo_ 怪物信息 = 环境::取指定对象信息(0x2BF99);
						if (怪物信息.dResId == 0x2BF99 && 开关信息.dResShow == 0 && 怪物信息.IsHide == false)
						{
							if (GetDis(8168, 43876, 8709) <= 200)
							{
								MyTrace(L"打怪");
								怪物信息.坐标.x = 8724;
								怪物信息.坐标.y = 44160;
								怪物信息.坐标.z = 8705;

								功能::打怪程序2(怪物信息.objBase, 怪物信息.坐标, 开关信息);
							}
							else
							{
								功能::到指定地点(15, 任务坐标.地图ID, 8168, 43876, 8709, 50);
							}
							return;
						}
						else
						{
							功能::到指定地点按G(15, 任务坐标.地图ID, 7844, 43725, 8721, 200);
							//Sleep(1000);
							//然后移动到7430,43187,8705
						}
						return;
					}
					else
					{
						objInfo_ 电梯信息 = 环境::取指定对象信息(0x109F17);
						地图::本地图寻路(7435, 42295, 8707, 电梯信息.ModId);
						//功能::到指定地点乘坐电梯(15, 任务坐标.地图ID, 7521, 42627, 8705, 50, 0x109F17);
						return;
					}
				}
				if (角度 > 218 && 角度 < 260)
				{
					MyTrace(L"第一个移动浮板");
					if (本人::是否在走路2())
					{
						Sleep(1000);
						return;
					}
					if (地图::指定地点是否可到达_M(8815, 41624, 8708))
					{
						if (GetDis(7435, 42295, 8707) <= 200 && 环境::获取当前电梯ID() != 0)
						{
							功能::到指定地点(15, 任务坐标.地图ID, 8815, 41624, 8708, 10);
							Sleep(1000);
							return;
						}
						else
						{
							objInfo_ 电梯信息 = 环境::取指定对象信息(0x109F17);
							地图::本地图寻路(7435, 42295, 8707, 电梯信息.ModId);
							Sleep(1000);
						}

					}
					else
					{
						/*objInfo_ 传送点信息 = 环境::取指定任务显示对象信息(0x13920);
						if (传送点信息.dResId != 0 && 环境::获取对象释放技能组(环境::取指定对象信息(0x2BF99).objBase) == 0)
						{*/
						if (地图::指定地点是否可到达_M(8509, 41641, 8705) && 环境::获取对象释放技能组(环境::取指定对象信息(0x2BF99).objBase) == 0)
						{
							功能::到指定地点按G(15, 任务坐标.地图ID, 8509, 41641, 8705, 10);
						}
						else
						{
							objInfo_ 电梯信息 = 环境::取指定对象信息(0x109F17);
							地图::本地图寻路(7435, 42295, 8707, 电梯信息.ModId);
							Sleep(1000);
						}
						//}
						//else
						//{
						//	objInfo_ 电梯信息 = 环境::取指定对象信息(0x109F17);
						//	地图::本地图寻路(7435, 42295, 8707, 电梯信息.ModId);
						//	//Sleep(1000);
						//	//功能::到指定地点乘坐电梯(15, 任务坐标.地图ID, 7521, 42627, 8705, 50, 0x109F17);
						//}
						//13920
						//if()

					}
					return;
				}
				if (角度 > 260 && 角度 < 320)
				{
					MyTrace(L"第二关 角度:%d", 角度);
					objInfo_ 开关信息1 = 环境::取指定对象信息(0x138E9);
					if (开关信息1.dPortalOpen != 2 && 开关信息1.dObjId != 0)
					{
						objInfo_ 怪物信息 = 环境::取指定对象信息(0x2BF99);
						if (怪物信息.dResId == 0x2BF99 && 开关信息1.dResShow == 0 && 怪物信息.IsHide == false)
						{
							if (GetDis(10221, 41434, 8705) <= 200)
							{
								MyTrace(L"打怪");
								怪物信息.坐标.x = 10225.1;
								怪物信息.坐标.y = 42049.3;
								怪物信息.坐标.z = 8705;

								功能::打怪程序2(怪物信息.objBase, 怪物信息.坐标, 开关信息1);
							}
							else
							{
								地图::本地图寻路(10221, 41434, 8705, 0);
								//功能::到指定地点(15, 任务坐标.地图ID, 11501, 41431, 8722, 50);
							}
							return;
						}
						else
						{
							功能::到指定地点按G(15, 任务坐标.地图ID, 10700, 41349, 8721, 200);
							//功能::到指定地点采集任务显示(15, 任务坐标.地图ID, 10700, 41349, 8721, 1000, 0x138E9, 100, 200);
						}
						return;
					}
					else
					{
						objInfo_ 电梯信息 = 环境::取指定对象信息(0x109F17);
						地图::本地图寻路(12331.2, 41903.4, 8707.12, 电梯信息.ModId);
						//功能::到指定地点乘坐电梯(15, 任务坐标.地图ID, 11810,41949,8713 ,50, 0x109F17);
					}

					return;

				}
				if (角度 >= 320 && 角度 <= 349)
				{
					MyTrace(L"第二个移动浮板 %d", 角度);
					if (本人::是否在走路())
					{
						Sleep(1000);
						return;
					}
					if (地图::指定地点是否可到达_M(12166, 43396.1, 8705))
					{
						if (GetDis(12331.2, 41903.4, 8707.12) <= 200 && 环境::获取当前电梯ID() != 0)
						{
							功能::到指定地点(15, 任务坐标.地图ID, 12166, 43396.1, 8705, 10);
							Sleep(1000);
						}
						else
						{
							objInfo_ 电梯信息 = 环境::取指定对象信息(0x109F17);
							地图::本地图寻路(12331.2, 41903.4, 8707.12, 电梯信息.ModId);
							//地图::本地图寻路(12331.2, 41903.4, 8707.12, 0x109F17);
							Sleep(1000);
							//功能::到指定地点(15, 任务坐标.地图ID, 12253, 43150, 8705, 10);
						}

					}
					else
					{
						/*objInfo_ 传送点信息 = 环境::取指定任务显示对象信息(0x13920);
						if (传送点信息.dResId != 0)
						{*/
						if (地图::指定地点是否可到达_M(12253, 43150, 8705) && 环境::获取对象释放技能组(环境::取指定对象信息(0x2BF99).objBase) == 0)
						{
							功能::到指定地点按G(15, 任务坐标.地图ID, 12253, 43150, 8705, 10);
						}
						else
						{
							objInfo_ 电梯信息 = 环境::取指定对象信息(0x109F17);
							地图::本地图寻路(12331.2, 41903.4, 8707.12, 电梯信息.ModId);
							//地图::本地图寻路(12331.2, 41903.4, 8707.12, 0x109F17);
							Sleep(1000);
						}
						//}
						//else
						//{
						//	objInfo_ 电梯信息 = 环境::取指定对象信息(0x109F17);
						//	地图::本地图寻路(12331.2, 41903.4, 8707.12, 电梯信息.ModId);
						//	//Sleep(1000);
						//	//功能::到指定地点乘坐电梯(15, 任务坐标.地图ID,11810,41949,8713, 50, 0x109F17);
						//}
						//if (环境::获取当前电梯ID() != 0)
						//{
						//	地图::本地图寻路(11501, 41431, 8722, 0x109F17);
						//	//功能::到指定地点乘坐电梯(15, 任务坐标.地图ID, 12165, 42188, 8711, 50, 0x109F17);
						//}

					}
					return;
				}
				if (角度 >= 350 || 角度 <= 35)
				{
					MyTrace(L"第三阶段 %d", 角度);
					objInfo_ 开关信息1 = 环境::取指定对象信息(0x138EA);
					if (开关信息1.dPortalOpen != 2 && 开关信息1.dObjId != 0)
					{
						objInfo_ 怪物信息 = 环境::取指定对象信息(0x2BF99);
						MyTrace(L"怪物信息 是否死亡%d", 怪物信息.dIsDead);
						if (怪物信息.dResId == 0x2BF99 && 开关信息1.dResShow == 0 && 怪物信息.IsHide == false)
						{
							if (GetDis(11408, 44250, 8705) <= 200)
							{
								MyTrace(L"打怪");
								怪物信息.坐标.x = 11408;
								怪物信息.坐标.y = 44250;
								怪物信息.坐标.z = 8705;
								//objInfo_ 开关信息1;
								//开关信息1.dResId = 1;
								功能::打怪程序2(怪物信息.objBase, 怪物信息.坐标, 开关信息1);
							}
							else
							{
								地图::本地图寻路(11408, 44250, 8705, 0);
								//功能::到指定地点(15, 任务坐标.地图ID, 11501, 41431, 8722, 50);
							}
							return;
						}
						else
						{
							功能::到指定地点按G(15, 任务坐标.地图ID, 11325, 45148, 8721, 200);
						}
					}

					//else
					//{
					//	功能::到指定地点按G(15, 任务坐标.地图ID, 10700, 41349, 8721, 200);
					//	//功能::到指定地点采集任务显示(15, 任务坐标.地图ID, 10700, 41349, 8721, 1000, 0x138E9, 100, 200);
					//}
					return;
				}
				else
				{
					return;
				}
			}

		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			//功能::到指定地点(15, 任务坐标.地图ID, 9991, 51614, 8136, 150);
			功能::到指定地点(15, 任务坐标.地图ID, 9933, 49046, 8723, 150);
			return;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			//功能::到指定地点(15, 任务坐标.地图ID, 9991, 51614, 8136, 150);
			功能::到指定地点(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 150);
			return;
		}
	}
	if (主线任务.dQuestId == 801004)
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				if (地图::取地图ID() == 10893)
				{
					objInfo_ 宝箱 = 环境::取指定对象信息(0x138A0);
					if (宝箱.dResShow == 1)
					{
						功能::到指定地点采集任务显示(15, 10893, 9987, 52008, 8151, 1000, 0x138A0, 100, 200);
					}
					else
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
						功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
					}

					return;
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
				}
				return;
			}
		}
		else
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}

	}
	if (主线任务.dQuestId == 812001)
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点按G(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 200);
				return;
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 200, 主线任务.dStep);
				return;
			}
			if (主线任务.dStep == 3)
			{
				背包::使用背包指定物品_ByResId(0x75306);
				/*坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 200, 主线任务.dStep);*/
				return;
			}
		}
	}
	if (主线任务.dQuestId == 812002)
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				本人::CALL_演奏乐谱(4);
				Sleep(1000);
				return;
			}
		}
	}
	if (主线任务.dQuestId == 812402)
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(22, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 200, 主线任务.dStep);
			return;
		}
	}
	if (主线任务.dQuestId == 812003)
	{
		if (主线任务.dStep == 1)
		{
			if (地图::取地图ID() == 10002)
			{
				功能::到指定地点按G(22, 10002, 12992, 103, 233, 200);
				return;
			}
			else
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 200, 主线任务.dStep);
				return;
			}

		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 200);
			return;

		}
	}
	//循环跳出 = true;
}
void 游戏::主线_梨树栖息地(QuestInfo_ 主线任务)
{
	if (主线任务.dQuestId == 812003)
	{
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 200, 主线任务.dStep);
			return;

		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点采集任务显示(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 2000, 0x1417E, 150);
			return;

		}
		if (主线任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::寻路到副本(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z);
			return;

		}
	}
	if (主线任务.dQuestId == 812401)
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 200, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 主线任务.dQuestId, -1, 200, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 200, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (环境::取指定对象信息(0x3742).IsHide == true)
			{
				if (UI功能::怪物击杀求饶界面是否打开() == false)
				{
					功能::到指定地点按G(15, 任务坐标.地图ID, 13048, -17549, 1824, 200);
				}
				else
				{
					UI功能::内存按键('G');
				}
				return;
			}
			else
			{
				功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 13235, -17375, 1826, 主线任务.TargetId, 主线任务.dQuestId, -1, 200, 主线任务.dStep);
				return;
			}

			return;
		}
	}
	if (主线任务.dQuestId == 812004)
	{

		if (主线任务.dStep == 1)
		{
			if (地图::取地图ID() == 10832)
			{
				功能::到指定地点(15, 10832, 13397, -17952, 1825, 50);
				return;
			}
			else
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 200, 主线任务.dStep);
				return;
			}


		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 200, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 200, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 200, 3000);
			//功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 200, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 150);
			return;
		}
		if (主线任务.dStep == 6)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 200, 主线任务.dStep);
			return;
		}
	}
	if (主线任务.dQuestId == 812005)
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 200, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 200, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 200, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 100);
			return;
		}
		if (主线任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 200, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 6)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 200, 主线任务.dStep);
			return;
		}
	}
	if (主线任务.dQuestId == 812006)
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 200, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 200, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 200);
			return;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"183950");
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 500, 2000, false);
			return;
		}
		if (主线任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 200, 主线任务.dStep);
			return;
		}
	}
	if (主线任务.dQuestId == 812007)
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"183310");
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 700, 200, false);
			return;
		}
		if (主线任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"183220|183230");
			功能::移动打怪(-10886, -12113, 768, 100, 2000, 150, false);
			return;
		}
	}
	if (主线任务.dQuestId == 812008)
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
	}


}
void 游戏::主线_黑玫瑰教堂(QuestInfo_ 主线任务)
{
	if (主线任务.dQuestId == 813001)
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 3)
		{
			ActorInfo_ 角色信息 = 本人::取角色信息();
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (角色信息.举起状态 == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点采集任务显示(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 500, 0x141E3);
			}
			else
			{
				if (功能::到指定地点(15, 任务坐标.地图ID, 6127, 14032, 511, 200))
				{
					UI功能::内存按键('R');
				}
			}

			return;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return;
		}
		if (主线任务.dStep == 6)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入暂时不开启传送阵ID(900442);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
	}
	if (主线任务.dQuestId == 813002)
	{
		if (主线任务.dStep == 1)
		{
			if (暂时不开的传送阵.size() > 0)
			{
				暂时不开的传送阵.clear();
			}
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点采集任务显示(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 2000, 0x141E8);
			return;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
	}
	if (主线任务.dQuestId == 813003)
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 100);
			return;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(15, 任务坐标.地图ID, 21691, 13345, 134, 25);
			return;
		}
		if (主线任务.dStep == 4)
		{
			if (主线任务.子任务进度.size() == 3)
			{
				if (主线任务.子任务进度[0].dCur == 0)
				{
					功能::到指定地点采集任务显示(15, 10819, 22843, 10833, 256, 1000, 82412, 200);
					return;
				}
				if (主线任务.子任务进度[1].dCur == 0)
				{
					功能::到指定地点采集任务显示(15, 10819, 23828, 15601, -159, 500, 82411, 200);
					return;
				}
				if (主线任务.子任务进度[2].dCur == 0)
				{
					功能::到指定地点采集任务显示(15, 10819, 21816, 16073, 113, 500, 82410, 200);
					return;
				}
				//坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);

				return;
			}

		}

	}
	if (主线任务.dQuestId == 813004)
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
	}
	if (主线任务.dQuestId == 813401)
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(15, 任务坐标.地图ID, 27615, 11649, 14, 50);
			return;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (功能::到指定地点(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 100))
			{
				UI功能::内存按键('Q');
			}
			return;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (功能::到指定地点(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 100))
			{
				UI功能::内存按键('W');
			}
			return;
		}
		if (主线任务.dStep == 5)
		{

			UI功能::内存按键('Q');
			Sleep(500);
			return;
		}
		if (主线任务.dStep == 6)
		{

			UI功能::内存按键('W');
			Sleep(500);
			return;
		}
		if (主线任务.dStep == 7)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (本人::取坐标().x <= 27247)
			{
				功能::到指定地点按G(15, 任务坐标.地图ID, 26862, 11648, -125, 200);
				return;
			}
			else
			{

				加入优先打怪ID(L"183520|183530|183540");
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 2000);
				return;
			}

		}
		if (主线任务.dStep == 8)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 100);
			return;
		}
	}
	if (主线任务.dQuestId == 813005)
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::寻路到副本(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z);
			return;
		}
	}
	if (主线任务.dQuestId == 814401)
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"184190");
			功能::移动打怪(-5354, -32735, -6428, 100, 3000);
			return;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"184191|184192");
			功能::移动打怪(-6562, -29397, -6174, 100, 1000);
			return;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 100);
			return;
		}
		if (主线任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 100, 200);
			return;
		}
		if (主线任务.dStep == 6)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"184190");
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 1000);
			return;
		}
		if (主线任务.dStep == 7)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return;
		}
		if (主线任务.dStep == 8)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"184190");
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 1000);
			return;
		}
		if (主线任务.dStep == 9)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"184194|184195");
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 1000);
			return;
		}
		if (主线任务.dStep == 10)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 100);
			return;
		}
		if (主线任务.dStep == 11)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"184170");
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 1000);
			return;
		}
		if (主线任务.dStep == 12)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return;
		}
		if (主线任务.dStep == 13)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"184130");
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 2000);
			return;
		}
		if (主线任务.dStep == 14)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"184121|184150");
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 2000);
			return;
		}
		if (主线任务.dStep == 15)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 2000);
			return;
		}
		if (主线任务.dStep == 16)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"184180");
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 5000, 2000);
			Sleep(1000);
			return;
		}
	}
	if (主线任务.dQuestId == 813006)
	{
		if (主线任务.dStep == 1)
		{
			if (地图::取地图ID() == 10852)
			{
				本人::CALL_演奏乐谱(1);
				Sleep(10000);
				return;
			}
			else
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
				return;
			}

		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 150);
			return;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 150);
			return;
		}
	}
}
void 游戏::主线_拉伊亚阶地(QuestInfo_ 主线任务)
{
	if (主线任务.dQuestId == 815001)
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (功能::到指定地点(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 100))
			{
				本人::CALL_做社交动作(0xF231);//对话
			}

			return;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (功能::到指定地点(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 100))
			{
				本人::CALL_做社交动作(0xF236);//悲伤
			}

			return;
		}
		if (主线任务.dStep == 6)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
	}
	if (主线任务.dQuestId == 815002)
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 4)
		{
			if (主线任务.子任务进度.size() == 3)
			{
				if (主线任务.子任务进度[0].dCur == 0)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, -6766, -8893, 1280, 14250, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
					return;
				}
				if (主线任务.子任务进度[1].dCur == 0)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, -6192, -9162, 1274, 14251, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
					return;
				}
				if (主线任务.子任务进度[2].dCur == 0)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, -6962, -8096, 1280, 14252, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
					return;
				}
				if (主线任务.子任务进度[2].dCur == 1)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, -7136, -8020, 1280, 14253, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
					return;
				}
				if (主线任务.子任务进度[2].dCur == 2)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, -7003, -7960, 1280, 14254, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
					return;
				}
			}

		}
		if (主线任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
	}
	if (主线任务.dQuestId == 815003)
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 150, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 2)
		{
			if (主线任务.子任务进度.size() == 3)
			{
				if (主线任务.子任务进度[0].dCur == 0)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点采集(15, 任务坐标.地图ID, -6088, -12050, 1301, 200, 0x1424B);
					return;
				}
				if (主线任务.子任务进度[1].dCur == 0)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点采集(15, 任务坐标.地图ID, -5658, -13656, 1305, 200, 0x1424D);
					return;
				}
				if (主线任务.子任务进度[2].dCur == 0)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点采集任务显示(15, 任务坐标.地图ID, -4676, -12606, 2311, 1000, 0x1424C);
					return;
				}
			}
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 150, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点对怪物使用F5(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 3000, 183700);
			return;
		}
		if (主线任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 150, 主线任务.dStep);
			return;
		}
	}
	if (主线任务.dQuestId == 815004)
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 150, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 150, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::寻路到副本(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z);
			return;
		}
	}
	if (主线任务.dQuestId == 815401)//宣战
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(15, 任务坐标.地图ID, -11722, -5482, 766, 100);
			return;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 2000);
			return;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点采集任务显示(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 500, 0x14248);
			return;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 150, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 150, 主线任务.dStep);
			return;
		}
	}
	if (主线任务.dQuestId == 815005)
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				if (地图::取地图ID() == 10834)
				{
					功能::到指定地点(15, 10834, -12370, -6245, 789, 50);
					return;
				}
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 150, 主线任务.dStep);
				return;
			}
			if (主线任务.dStep == 2)
			{

				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 150, 主线任务.dStep);
				return;
			}
			if (主线任务.dStep == 3)
			{

				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 150, 主线任务.dStep);
				return;
			}
		}
		else
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0x32CF, 主线任务.dQuestId, -1, 150, 主线任务.dStep);
			return;
		}

	}
	if (主线任务.dQuestId == 815006)
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				UI功能::内存按键(VK_F5);
				Sleep(1000);
				return;
				/*坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 150, 主线任务.dStep);
				return;*/
			}
			if (主线任务.dStep == 2)
			{

				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 150, 主线任务.dStep);
				return;
			}
			if (主线任务.dStep == 3)
			{
				if (主线任务.子任务进度.size() == 3)
				{
					if (主线任务.子任务进度[0].dCur == 0)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
						功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, -17190, -13567, 1015, 14377, 主线任务.dQuestId, -1, 150, 主线任务.dStep);
						return;
					}
					if (主线任务.子任务进度[1].dCur == 0)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
						功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, -19394, -15490, 616, 14378, 主线任务.dQuestId, -1, 150, 主线任务.dStep);
						return;
					}
					if (主线任务.子任务进度[2].dCur == 0)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
						功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, -23095, -12279, 473, 14379, 主线任务.dQuestId, -1, 150, 主线任务.dStep);
						return;
					}
				}

			}
			if (主线任务.dStep == 4)
			{

				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 150, 主线任务.dStep);
				return;
			}
			if (主线任务.dStep == 5)
			{

				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 150, 主线任务.dStep);
				return;
			}
			if (主线任务.dStep == 6)
			{

				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::寻路到副本(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z);
				return;
			}
		}


	}
	if (主线任务.dQuestId == 815402)
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 2000);
				return;
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 150, 主线任务.dStep);
				return;
			}
		}
	}

}
void 游戏::主线_博伦亚领地(QuestInfo_ 主线任务)
{
	if (主线任务.dQuestId == 816001)
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点采集任务显示(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 1000, 0x142AA, 200);
			return;
		}
		if (主线任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点采集任务显示(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 1000, 0x142AB, 200);
			return;
		}

	}
	if (主线任务.dQuestId == 816003)
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 3)
		{
			if (主线任务.子任务进度.size() == 2)
			{
				if (主线任务.子任务进度[0].dCur < 主线任务.子任务进度[0].dNeed)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					加入优先打怪ID(L"183860|183870|183890");
					功能::移动打怪(-21250, -26148, 512, 100, 3000);
					return;
				}
				if (主线任务.子任务进度[1].dCur == 0)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, -22382, -28075, 512, 14291, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
					return;
				}
				if (主线任务.子任务进度[1].dCur == 1)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, -22787, -26626, 512, 14292, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
					return;
				}
			}

		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 150, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点采集任务显示(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 3000, 0x142AF, 100, 150);;
			return;
		}
		if (主线任务.dStep == 6)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 150, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 7)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 150, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 8)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			objInfo_ NPC信息 = 环境::取指定对象信息(主线任务.TargetId);
			if (NPC信息.dResId == 0)
				//if (GetDis(任务坐标.x, 任务坐标.y, 任务坐标.z) > 10000)
			{
				if (地图::传送点是否激活(0xDBD6D))
				{
					地图::传送(0xDBD6D);
					return;
				}
				else
				{
					功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 150, 主线任务.dStep);
					return;
				}

			}
			else
			{
				功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 150, 主线任务.dStep);
				return;
			}

		}
	}
	if (主线任务.dQuestId == 816002)
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			objInfo_ NPC信息 = 环境::取指定对象信息(主线任务.TargetId);
			if (NPC信息.dResId == 0)
			{
				if (地图::传送点是否激活(0xDBD6E))
				{
					地图::传送(0xDBD6E);
					return;
				}
				else
				{
					功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 150, 主线任务.dStep);
					return;
				}

			}
			else
			{
				功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 150, 主线任务.dStep);
				return;
			}
		}
	}
	if (主线任务.dQuestId == 816004)
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"82609");
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 2000, 100, true, 200);
			return;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return;
		}
		if (主线任务.dStep == 3)
		{
			if (主线任务.子任务进度.size() == 2)
			{
				if (主线任务.子任务进度[0].dCur < 主线任务.子任务进度[0].dNeed)
				{
					MyTrace(L"进度1");
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					加入优先打怪ID(L"82608");
					功能::移动打怪(-15113, -14502, 512, 100, 1000, 50, true, 3000);
					return;
				}
				if (主线任务.子任务进度[1].dCur < 主线任务.子任务进度[1].dNeed)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					加入优先打怪ID(L"183830|183820");
					功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 300, 2000, 125, true, 100);
					return;
				}
			}
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, -4854, -7710, 512, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
	}
	if (主线任务.dQuestId == 816009)
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 150);
			return;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点采集任务显示(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 2000, 0x142B8, 100, 200);
			return;
		}
		if (主线任务.dStep == 6)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 7)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"183840");
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 300, 2000, 100, false, 100);
			return;
		}
		if (主线任务.dStep == 8)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
	}
	if (主线任务.dQuestId == 816005)
	{
		if (主线任务.dStep == 1)
		{
			objInfo_ NPC信息 = 环境::取指定对象信息(14279);
			if (NPC信息.dResId != 0)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
				return;
			}
			else
			{
				if (地图::传送点是否激活(900461))
				{
					地图::传送(900461);
					Sleep(10000);
					return;
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
					return;
				}
			}



		}
		if (主线任务.dStep == 2)
		{
			if (地图::取地图ID() != 10816)
			{
				地图::传送(0xDBD3B);
				Sleep(10000);
				return;
			}
			else
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
				return;
			}

		}
		if (主线任务.dStep == 3)
		{
			if (地图::取地图ID() != 10818)
			{
				地图::传送(0xDBD4F);
				Sleep(10000);
				return;
			}
			else
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
				return;
			}

		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 5)
		{
			objInfo_ NPC信息 = 环境::取指定对象信息(14279);
			if (NPC信息.dResId != 0)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
				return;
			}
			else
			{
				if (地图::传送点是否激活(900461))
				{
					地图::传送(900461);
					Sleep(10000);
					return;
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
					return;
				}
			}
		}
	}
	if (主线任务.dQuestId == 816006)
	{
		if (主线任务.dStep == 1)
		{
			objInfo_ NPC信息 = 环境::取指定对象信息(14294);
			if (NPC信息.dResId != 0)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
				return;
			}
			else
			{
				if (地图::传送点是否激活(0xDBD6F))
				{
					地图::传送(0xDBD6F);
					Sleep(10000);
					return;
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
					return;
				}
			}
		}
		if (主线任务.dStep == 2)
		{

			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, -14996, -7295, 768, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;

		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::寻路到副本(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z);
			return;
		}
	}
	if (主线任务.dQuestId == 816401)
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 100);
			return;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 300, 2000, 125, true, 100);
			return;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 300, 2000, 125, true, 100);
			return;
		}
		if (主线任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"188020|188030");
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 300, 2000, 125, true, 100);
			return;
		}
		if (主线任务.dStep == 6)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"188020|188030");
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 300, 2000, 125, true, 100);
			return;
		}
		if (主线任务.dStep == 7)
		{
			ActorInfo_ 角色信息 = 本人::取角色信息();
			if (角色信息.举起状态 == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点按G(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 200);
			}
			else
			{
				objInfo_ 怪物信息 = 环境::取随机怪物信息();
				if (怪物信息.dCurHp > 0)
				{
					技能::屏蔽鼠标();
					技能::写怪物坐标到鼠标(怪物信息.坐标);
					UI功能::内存按键('Q');
					技能::解除屏蔽鼠标();
				}

			}

			return;
		}
		if (主线任务.dStep == 8)
		{
			ActorInfo_ 角色信息 = 本人::取角色信息();
			if (GetDis(-25019, -21591, 1493) <= 1000)
			{
				if (角色信息.举起状态 != 1)
				{
					UI功能::内存按键('R');
					Sleep(2000);
					return;
				}
			}
			if (GetDis(-23599, -20279, 1331) <= 1000)
			{
				if (角色信息.举起状态 == 1)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点按G(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 200);
					return;
				}
				else
				{
					if (主线任务.子任务进度.size() == 2)
					{
						if (主线任务.子任务进度[0].dCur < 主线任务.子任务进度[0].dNeed)
						{
							objInfo_ 怪物信息 = 环境::取指定对象信息(188170);
							if (怪物信息.dCurHp > 0)
							{
								技能::屏蔽鼠标();
								技能::写怪物坐标到鼠标(怪物信息.坐标);
								UI功能::内存按键('Q');
								Sleep(500);
								UI功能::内存按键('W');
								Sleep(500);
								UI功能::内存按键('E');
								技能::解除屏蔽鼠标();
							}
							return;
						}
						if (主线任务.子任务进度[1].dCur < 主线任务.子任务进度[1].dNeed)
						{
							objInfo_ 怪物信息 = 环境::取指定对象信息(0x2DF2E);
							if (怪物信息.dCurHp > 0)
							{
								技能::屏蔽鼠标();
								技能::写怪物坐标到鼠标(怪物信息.坐标);
								UI功能::内存按键('Q');
								技能::解除屏蔽鼠标();
								//Sleep(500);
							/*	UI功能::内存按键('W');
								Sleep(500);
								UI功能::内存按键('E');*/
							}
						}
						return;
					}


				}
			}
			else
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点按G(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 200);
				return;
			}

			return;
		}
		if (主线任务.dStep == 9)
		{
			ActorInfo_ 角色信息 = 本人::取角色信息();
			if (角色信息.举起状态 != 1)
			{
				UI功能::内存按键('R');
				Sleep(2000);
				return;
			}
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(-25215, -17172, 768, 300, 3000, 125, true, 100);
			return;
		}
		if (主线任务.dStep == 10)
		{

			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 300, 3000, 125, true, 100);
			return;
		}
		if (主线任务.dStep == 11)
		{

			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 300, 3000, 125, true, 100);
			return;
		}
		if (主线任务.dStep == 12)
		{

			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 300, 3000, 125, true, 100);
			return;
		}
		if (主线任务.dStep == 13)
		{

			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 300, 6000, 125, true, 100);
			return;
		}
		if (主线任务.dStep == 14)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			ActorInfo_ 角色信息 = 本人::取角色信息();
			if (角色信息.举起状态 == 1)
			{
				功能::到指定地点按G(15, 任务坐标.地图ID, -27197, -13598, 772, 200);
				return;
			}
			else
			{
				功能::到指定地点(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			}
			return;
		}
		if (主线任务.dStep == 15)
		{
			ActorInfo_ 角色信息 = 本人::取角色信息();
			if (本人::是否在走路2())
			{
				Sleep(2000);
				return;
			}
			/*if (角色信息.举起状态 != 1)
			{
				UI功能::内存按键('R');
				Sleep(2000);
				return;
			}*/
			//坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (功能::优先打怪(500))
			{
				功能::移动打怪(-28538, 2073, 1530, 300, 2000, 300, true, 100);
			}



			return;
		}
		if (主线任务.dStep == 16)
		{

			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 300, 3000, 100, true, 100);
			return;
		}
		if (主线任务.dStep == 17)
		{

			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 300, 3000, 125, true, 100);
			return;
		}
	}
	if (主线任务.dQuestId == 816007)
	{

		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 6)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 7)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 8)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
	}
	if (主线任务.dQuestId == 816008)
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (功能::到指定地点(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 100))
			{
				本人::CALL_做社交动作(0xF23D);
				Sleep(10000);
			}
			return;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 6)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 7)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 8)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
	}
	if (主线任务.dQuestId == 816010)
	{
		if (主线任务.dStep == 1)
		{
			if (主线任务.子任务进度.size() == 2)
			{
				if (主线任务.子任务进度[0].dCur == 0)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点采集任务显示(15, 任务坐标.地图ID, -27858, -8902, 509, 1000, 主线任务.子任务进度[0].TargetID);
					return;
				}
				if (主线任务.子任务进度[1].dCur == 0)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点采集任务显示(15, 任务坐标.地图ID, -26367, -4801, 512, 1000, 主线任务.子任务进度[1].TargetID);
					return;
				}
			}

		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 100);
			return;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 100);
			return;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 100);
			return;
		}
		if (主线任务.dStep == 6)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
	}
	if (主线任务.dQuestId == 817001)
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::寻路到副本(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z);
				return;
			}
		}
		else
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 主线任务.dQuestId, -1, 50);
			return;
		}

	}
	if (主线任务.dQuestId == 817401)
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 200, true);
			return;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (功能::到指定地点(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 200, true))
			{
				UI功能::内存按键('Q');
				Sleep(500);
			}
			return;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (功能::到指定地点(15, 任务坐标.地图ID, 3707, 3491, 1148, 200, true))
			{
				UI功能::内存按键('Q');
				Sleep(500);
			}
			return;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (功能::到指定地点(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 200, true))
			{
				UI功能::内存按键('Q');
				Sleep(500);
				UI功能::内存按键('W');
			}
			return;
		}
		if (主线任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (功能::到指定地点(15, 任务坐标.地图ID, 4639, 8717, 1472, 50, true))
			{
				UI功能::内存按键('E');

			}
			return;
		}
		if (主线任务.dStep == 6)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (本人::是否在走路() == false)
			{
				UI功能::内存按键('Q');
				Sleep(5000);
			}
			功能::到指定地点(15, 任务坐标.地图ID, 4307, 9517, 1496, 200, true);
			Sleep(1000);
			return;
		}
		if (主线任务.dStep == 7)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			/*if (本人::是否在走路() == false)
			{
				UI功能::内存按键('Q');
				Sleep(3000);
				UI功能::内存按键('W');
				Sleep(7000);
				UI功能::内存按键('E');
				Sleep(500);
			}*/
			加入优先打怪ID(L"189030");
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 1000, 100);
			//功能::到指定地点(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 200, false);
			//Sleep(1000);
			return;
		}
		if (主线任务.dStep == 8)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
	}

}
void 游戏::主线_鬃波港(QuestInfo_ 主线任务)
{
	if (主线任务.dQuestId == 818001)
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 6)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return;
		}
		if (主线任务.dStep == 7)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 8)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 主线任务.dQuestId, -1, 50);
			return;
		}
		if (主线任务.dStep == 9)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
	}
	if (主线任务.dQuestId == 818002)
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 100);
			return;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
	}
	if (主线任务.dQuestId == 818003)
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 14272, -10234, 518, 主线任务.TargetId, 主线任务.dQuestId, -1, 250, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 6)
		{
			if (主线任务.子任务进度.size() == 3)
			{
				if (主线任务.子任务进度[0].dCur == 0)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点采集任务显示(15, 任务坐标.地图ID, 4876, 7004, 256, 500, 82916);
					return;
				}
				if (主线任务.子任务进度[1].dCur == 0)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点采集任务显示(15, 任务坐标.地图ID, 7226, 8006, 455, 500, 82917);
					return;
				}
				if (主线任务.子任务进度[2].dCur == 0)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点采集任务显示(15, 任务坐标.地图ID, 8501, 8354, 521, 500, 82918);
					return;
				}
			}

		}
		if (主线任务.dStep == 7)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
	}
	if (主线任务.dQuestId == 818401)
	{
		if (主线任务.dStep == 1)
		{
			objInfo_ 任务道具 = 环境::取指定任务显示对象信息(0x143EF);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (任务道具.dResShow == 0)
			{

				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 2000, 125, true, 100);
				return;
			}
			else
			{
				功能::到指定地点采集任务显示(15, 任务坐标.地图ID, 8098, -10693, 518, 500, 0x143EF);
				return;
			}
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点采集任务显示(15, 任务坐标.地图ID, 8098, -10693, 518, 500, 0x143EF);
			return;
		}

	}
	if (主线任务.dQuestId == 818004)
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::寻路到副本(15, 任务坐标.地图ID, 9606, 11536, 252);
			return;
		}
		if (主线任务.dStep == 2)
		{
			if (地图::取地图ID() == 10839)
			{
				功能::到指定地点(15, 10839, 7399, -9957, 515, 50);
				return;
			}
			else
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
				return;
			}
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点使用表情(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 0xF231);
			return;
		}
		if (主线任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点使用表情(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 0xF243);
			return;
		}
		if (主线任务.dStep == 6)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 7666, -19916, 730, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 7)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 8)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(15, 任务坐标.地图ID, 8623, -21084, 729, 50);
			return;
		}
		if (主线任务.dStep == 9)
		{
			UI功能::内存按键(VK_F5);
			return;
		}
		if (主线任务.dStep == 10)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
	}


}
void 游戏::主线_科罗克尼斯渔村(QuestInfo_ 主线任务)
{
	if (主线任务.dQuestId == 819001)
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点采集任务显示(15, 任务坐标.地图ID, 19103, 7359, 128, 1000, 83001, 100, 300);
			return;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 300, 2000);
			return;
		}
		if (主线任务.dStep == 6)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 7)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 8)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 9)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 10)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (主线任务.子任务进度.size() == 2)
			{
				if (主线任务.子任务进度[0].dCur < 主线任务.子任务进度[0].dNeed)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					加入优先打怪ID(L"185050|186140");
					功能::移动打怪(17215, 3756, 512, 100, 3000);
					return;
				}
				if (主线任务.子任务进度[1].dCur < 主线任务.子任务进度[1].dNeed)
				{
					if (主线任务.子任务进度[1].dCur == 0)
					{
						功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 15058, 3659, 512, 15174, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
						return;
					}
					if (主线任务.子任务进度[1].dCur == 1)
					{
						功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 15058, 3659, 512, 15175, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
						return;
					}
					if (主线任务.子任务进度[1].dCur == 2)
					{
						功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 14609, 4557, 512, 15176, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
						return;
					}
					if (主线任务.子任务进度[1].dCur == 3)
					{
						功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 14609, 4557, 512, 15177, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
						return;
					}
				}
			}

			return;
		}
		if (主线任务.dStep == 11)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
	}
	if (主线任务.dQuestId == 819002)
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"83002|83019");
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 3000, 100, true);
			return;
		}
		if (主线任务.dStep == 6)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"83002|83019");
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 3000, 100, true);
			return;
		}
		if (主线任务.dStep == 7)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 8)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点采集任务显示(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 1000, 83020, 150, 250);
			return;
		}
		if (主线任务.dStep == 9)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 10)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 11)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 12)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 13)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 14)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			ActorInfo_ 角色信息 = 本人::取角色信息();
			if (角色信息.举起状态 == 1)
			{
				功能::到指定地点采集任务显示(15, 任务坐标.地图ID, 7544, 10623, 1024, 1000, 83003);
			}
			else
			{
				if (功能::到指定地点(15, 任务坐标.地图ID, 6933, 9820, 1024, 50))
				{
					UI功能::内存按键('R');
				}
			}

			return;
		}

	}
	if (主线任务.dQuestId == 819401)
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 100);
			return;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"184840");
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 3000, 100, true);
			return;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 6)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
	}
	if (主线任务.dQuestId == 819003)
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::寻路到副本(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z);
			return;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
	}
	if (主线任务.dQuestId == 819004)
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"185050|185070");
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 3000, 100, true);
			return;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点采集任务显示(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 1000, 83012, 100, 200);
			return;
		}
		if (主线任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点对怪物使用F5(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 3000, 185030);
			功能::到指定地点对怪物使用F5(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 3000, 185040);
			return;
		}
		if (主线任务.dStep == 6)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 7)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return;
		}
		if (主线任务.dStep == 8)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 9)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 10)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 11)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
	}
	if (主线任务.dQuestId == 819005)
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点采集任务显示(15, 任务坐标.地图ID, 5273, 31499, 512, 1000, 83022, 100, 200);
			return;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (功能::到指定地点(15, 任务坐标.地图ID, 5273, 31499, 512, 50))
			{
				UI功能::内存按键(VK_F5);

			}
			return;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
	}
	if (主线任务.dQuestId == 819006)
	{
		if (主线任务.dStep == 1)
		{
			if (主线任务.子任务进度.size() == 2)
			{
				if (主线任务.子任务进度[0].dCur == 0)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					加入优先打怪ID(L"83128");
					功能::移动打怪(5728, 39463, 800, 100, 3000, 100, true);
					return;
				}
				if (主线任务.子任务进度[1].dCur < 主线任务.子任务进度[1].dNeed)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					加入优先打怪ID(L"185121|185131|185151|185181");
					功能::移动打怪(5728, 39463, 800, 100, 3000, 100, true);
					return;
				}
			}

		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
	}
	if (主线任务.dQuestId == 819007)
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			ActorInfo_ 角色信息 = 本人::取角色信息();
			if (角色信息.举起状态 == 1)
			{
				功能::到指定地点采集任务显示(15, 任务坐标.地图ID, 13897, 40915, 630, 1000, 83129);
			}
			else
			{
				if (功能::到指定地点(15, 任务坐标.地图ID, 14231, 41728, 910, 50))
				{
					UI功能::内存按键('R');
				}
			}
			return;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点采集任务显示(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 1000, 83103);
			return;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return;
		}
	}
	if (主线任务.dQuestId == 819402)
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"185220|185230");
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 3000, 100, true);
			return;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (主线任务.子任务进度.size() == 1)
			{
				if (主线任务.子任务进度[0].dCur == 0)
				{
					加入优先打怪ID(L"82301");
					功能::移动打怪(4019, 49310, 1106, 100, 500, 100, true, 300);
					return;
				}
				if (主线任务.子任务进度[0].dCur == 1)
				{
					加入优先打怪ID(L"82301");
					功能::移动打怪(2620, 48115, 800, 100, 500, 100, true, 300);
					return;
				}
			}

			return;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"185270");
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 3000, 100, true);
			return;
		}
	}
	if (主线任务.dQuestId == 819008)
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::寻路到副本(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z);
			return;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
	}
	if (主线任务.dQuestId == 819009)
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::寻路到副本(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z);
			return;
		}
	}
	if (主线任务.dQuestId == 821401)
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"186020|186030");
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 3000, 100, true);
			return;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 100);
			return;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return;
		}
		if (主线任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"186020|186030");
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 3000, 100, true);
			return;
		}
		if (主线任务.dStep == 6)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (主线任务.子任务进度.size() == 2)
			{
				if (主线任务.子任务进度[0].dCur < 主线任务.子任务进度[0].dNeed)
				{
					加入优先打怪ID(L"186070");
					功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 3000, 100, true);
				}
				if (主线任务.子任务进度[1].dCur < 主线任务.子任务进度[1].dNeed)
				{
					加入优先打怪ID(L"186020|186180");
					功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 3000, 100, true);
				}
			}

			return;
		}
		if (主线任务.dStep == 7)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return;
		}
		if (主线任务.dStep == 8)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"186011|186030");
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 5000, 100, true);
			return;
		}
		if (主线任务.dStep == 9)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return;
		}
		if (主线任务.dStep == 10)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"186030|186070");
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 5000, 100, true);
			return;
		}
		if (主线任务.dStep == 11)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (功能::优先破坏击打道具(6000))
			{
				功能::到指定地点(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			}

			return;
		}
		if (主线任务.dStep == 12)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"83202");
			功能::移动打怪(2885, 20962, -1280, 100, 5000, 500, true, 5000);
			return;
		}
		if (主线任务.dStep == 13)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return;
		}
		if (主线任务.dStep == 14)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 15)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"186100");
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 2000, 100, true);
			return;
		}
		if (主线任务.dStep == 16)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 200, 500);
			return;
		}
		if (主线任务.dStep == 17)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"186071|186061");
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 3000, 100, true);
			return;
		}
		if (主线任务.dStep == 18)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			//功能::到指定地点采集任务显示(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 1000,0x14504,500,100);
			功能::到指定地点按G(15, 任务坐标.地图ID, 20546, 17785, -2903, 150, 500);
			return;
		}
		if (主线任务.dStep == 19)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 200, 500);
			return;
		}
		if (主线任务.dStep == 20)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"186110");
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 3000, 100, true);
			return;
		}
	}
	if (主线任务.dQuestId == 818005)//大海盗留下的地图  
	{
		if (主线任务.dStep == 1)//与<FONT COLOR='{0}'>鬃波港</FONT>的<FONT COLOR='{0}'>黑牙</FONT>对话
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}

	}
	if (主线任务.dQuestId == 818006)//启航!
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 2)
		{
			if (!UI功能::背包界面是否显示())
			{
				UI功能::内存按键('I');
				return;
			}
			背包::使用背包指定物品_ByResId(0xB242A);
			return;
		}
		if (主线任务.dStep == 3)
		{
			if (UI功能::背包界面是否显示())
			{
				UI功能::内存按键('I');
				return;
			}
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return;
		}
		if (主线任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 6)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 7)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
		if (主线任务.dStep == 8)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return;
		}
	}
	//循环跳出 = true;
}
objInfo_ 取出附近未开启的传送点(vector<objInfo_>& 采集组, DWORD 距离)
{
	objInfo_ temp;
	for (size_t i = 0; i < 采集组.size(); i++)
	{
		if (!地图::传送点是否激活(采集组[i].dResId) && 采集组[i].dType == 6 && 采集组[i].fDis <= 距离 && 采集组[i].wName != L"" && ID是否已存在(采集组[i].dResId, 暂时不开的传送阵) == false && 采集组[i].dResId != 0xF3D && 采集组[i].dResId != 0xEC87 && 采集组[i].dResId != 0x6255571 && 采集组[i].dResId != 0x6436971 && 采集组[i].dResId != 0x6436970 && 采集组[i].dResId != 0x606A9E1 && 采集组[i].wName.Find(L"FONT COLO") == -1 && 采集组[i].dPortalOpen != 2 && 采集组[i].dResId != 0x13CF3 && 采集组[i].dResId != 0x1391F && 采集组[i].dResId != 0x113A55 && 采集组[i].IsHide == false && 采集组[i].dResId != 0x113A4D && 采集组[i].dResId != 0x2418 && 采集组[i].dResShow == 1 && 采集组[i].dResId != 0x273D && 采集组[i].dResId != 0x141F7 && 采集组[i].wName != L"Teleport" && 采集组[i].dResId < 0x6000000 && 采集组[i].dResId != 0x244A && 采集组[i].dResId != 0xFD71A && 采集组[i].dResId != 0xFD718 && 采集组[i].dResId != 0x247C)//获得的摩可可种子 606A9E1
		{
			temp = 采集组[i];
			break;
		}
	}
	return temp;
}
bool 功能::开启传送点()
{
	if (地图::取地图ID() == 30703)//航海地图
	{
		return true;
	}
	objInfo_ 附近传送点;
	vector<objInfo_>采集组;
	//MyTrace(L"遍历采集物");
	环境::遍历采集物(采集组);
	MyTrace(L"采集物数量 %d", 采集组.size());
	附近传送点 = 取出附近未开启的传送点(采集组, 3000);
	if (附近传送点.dObjId != 0)
	{
		MyTrace(L"最近尚未开启传送点 %s 距离%0.3f", 附近传送点.wName, 附近传送点.fDis);
		if (附近传送点.fDis > 200)
		{
			if (地图::指定地点是否可到达_M(附近传送点.坐标.x, 附近传送点.坐标.y, 附近传送点.坐标.z))
			{
				地图::本地图寻路(附近传送点.坐标.x, 附近传送点.坐标.y, 附近传送点.坐标.z, 0);
				Sleep(3000);
			}
			else
			{
				加入暂时不开启传送阵ID(附近传送点.dResId);
			}

		}
		else
		{
			UI功能::内存按键('G');
			//功能::到指定地点按G(地图::取当前大陆ID(), 地图::取地图ID(), 附近传送点.坐标.x, 附近传送点.坐标.y, 附近传送点.坐标.z, 50);
		}
		return false;
	}
	return true;

}
bool 游戏::支线_莱温哈特(vector<DWORD>& vsk)
{
	if (任务::任务是否已完成(202002, vsk))//传说与童话 第一张地图最后一个任务
	{
		if (!任务::任务是否已完成(202123, vsk))//大胆的创意
		{
			if (任务::是否已接任务(202123))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(202123);
				if (支线任务.dStep == 1)
				{
					if (GetDis(8581, 6179, 256.54) <= 200)
					{
						本人::CALL_做社交动作(0xF239);
						Sleep(10000);
					}
					else
					{
						地图::本地图寻路(8581, 6179, 256.54, 0);
					}
				}
				if (支线任务.dStep == 2)
				{
					功能::到指定地点找NPC交任务(1, 10201, 8847, 6206, 256.54, L"吟游诗人勒内本", 支线任务.dQuestId, -1, 25);

				}

			}
			else
			{
				功能::到指定地点找NPC接任务(1, 10201, 8847, 6206, 256.54, L"吟游诗人勒内本", 202123, 25);
			}
			return false;
		}
		if (!任务::任务是否已完成(202106, vsk))//警备队员卡迪 送花
		{
			if (任务::是否已接任务(202106))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(202106);
				if (支线任务.dStep == 1)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0x2C07, 支线任务.dQuestId, -1, 25);

				}
				if (支线任务.dStep == 2)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0x2C07, 支线任务.dQuestId, -1, 25);

				}
			}
			else
			{
				功能::到指定地点找NPC接任务2(1, 10201, 10230, 5970, 517.381, 0x2C44, 202106, 25);
			}
			return false;
		}
		if (!任务::任务是否已完成(202109, vsk))//布拉卡 把花插花坛
		{
			if (任务::是否已接任务(202109))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(202109);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 7518, 7254, 260.405, 200);
					}
					/*if (支线任务.dStep == 2)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0x2C07, 支线任务.dQuestId, -1, 25, 支线任务.dStep);

					}*/
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务3(1, 任务坐标.地图ID, 7894, 7548, 259, 0x2C07, 支线任务.dQuestId, -1, 25, 支线任务.dStep);
				}

			}
			else
			{
				功能::到指定地点找NPC接任务2(1, 10201, 7974, 7576, 258.999, 0x2C07, 202109, 25);
			}
			return false;
		}
	}
	return true;
}
bool 游戏::支线_罗格尔(vector<DWORD>& vsk)
{
	if (任务::任务是否已完成(203005, vsk))//传说与童话 第一张地图最后一个任务
	{
		if (!任务::任务是否已完成(0x31968, vsk))
		{
			if (任务::是否已接任务(0x31968))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0x31968);
				if (支线任务.dStep == 1)
				{
					if (支线任务.dState == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						加入优先打怪ID(L"120180");
						功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 2000);
					}
					if (支线任务.dState == 2)
					{
						优先打怪ID.clear();
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						//MyTrace(L"任务目标 大陆ID:%d 地图ID %d 本大陆ID：%d", 任务坐标.大陆ID, 任务坐标.地图ID, 地图::取当前大陆ID());
						功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 11304, 支线任务.dQuestId, -1, 25);
						/*if (任务坐标.地图ID == 0 && 任务坐标.x == 0)
						{
							循环跳出 = true;
						}*/
					}
				}

			}
			else
			{
				功能::到指定地点找NPC接任务2(1, 10211, 8180, 27533, 0, 0x2C1C, 0x31968, 25);
			}
			return false;
		}
	}
	return true;
}
bool 游戏::支线_安格莫斯山麓(vector<DWORD>& vsk)
{
	if (任务::任务是否已完成(206002, vsk) || 任务::取出指定主线任务(206002).dStep >= 2)//传说与童话 第一张地图最后一个任务
	{
		if (!任务::任务是否已完成(0x32517, vsk))//大胆的创意
		{
			if (任务::是否已接任务(0x32517))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0x32517);
				if (支线任务.dState == 1)
				{
					功能::移动打怪(-391, 5736, -121, 100, 1000, 100);
					return false;
				}
				if (支线任务.dState == 2)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					//MyTrace(L"任务目标 大陆ID:%d 地图ID %d 本大陆ID：%d", 任务坐标.大陆ID, 任务坐标.地图ID, 地图::取当前大陆ID());
					功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 11410, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
			else
			{
				功能::到指定地点找NPC接任务2(1, 10220, 8765, 845, -508, 0x2C8A, 0x32517, 50);
				return false;
			}
			return false;
		}
		if (!任务::任务是否已完成(0x32515, vsk))//帮一把手 
		{
			if (任务::是否已接任务(0x32515))//清理病人身边的<FONT COLOR='#CFF960'>大教堂残骸</FONT>
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0x32515);

				if (支线任务.dState == 1)//净化<FONT COLOR='#CFF960'>堆放的尸体</FONT>
				{
					if (支线任务.dStep == 1)
					{
						ActorInfo_ 局_角色信息 = 本人::取角色信息();
						MyTrace(L"举起状态 %d", 局_角色信息.举起状态);
						if (局_角色信息.举起状态 == 1)
						{
							坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
							功能::到指定地点采集(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 1000, 0x5146, 100, 150);

						}
						else
						{
							if (局_角色信息.举起状态 == 4)
							{
								坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
								if (功能::到指定地点(任务坐标.大陆ID, 任务坐标.地图ID, 7724, 350, -507, 100))
								{
									UI功能::内存按键(DWORD('R'));
								}
							}

						}
						return false;
					}
					if (支线任务.dStep == 2)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点采集(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 1000, 支线任务.TargetId, 100, 150);
						return false;
					}

					return false;
				}
				if (支线任务.dState == 2)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					//MyTrace(L"任务目标 大陆ID:%d 地图ID %d 本大陆ID：%d", 任务坐标.大陆ID, 任务坐标.地图ID, 地图::取当前大陆ID());
					功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0x2C8F, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
			else
			{
				功能::到指定地点找NPC接任务2(1, 10220, 8087, 476, -508, 0x2C8F, 0x32515, 50);
				return false;
			}
			return false;
		}

	}
	if (任务::任务是否已完成(206002, vsk) || 任务::取出指定主线任务(206002).dStep >= 5)//圣泉 安格鲁斯山麓
	{
		if (!任务::任务是否已完成(0x32519, vsk))//加强防备 
		{
			if (任务::是否已接任务(0x32519))//从斯凯哈尔那收集 <FONT COLOR='{0}'>粘液</FONT>
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0x32519);
				if (支线任务.dState == 1)//净化<FONT COLOR='#CFF960'>堆放的尸体</FONT>
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					CString temp;
					temp.Format(L"%d", 支线任务.TargetId);
					加入优先打怪ID(L"122030");
					MyTrace(L"优先打怪数量%d", 优先打怪ID.size());
					功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 500, 3000, 200);
					/*功能::到指定地点采集(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 1000, 支线任务.TargetId, 100, 150);*/
					return false;
				}
				if (支线任务.dState == 2)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					//MyTrace(L"任务目标 大陆ID:%d 地图ID %d 本大陆ID：%d", 任务坐标.大陆ID, 任务坐标.地图ID, 地图::取当前大陆ID());
					功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0x2C93, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
			else
			{
				功能::到指定地点找NPC接任务2(1, 10220, 2470, 10765, 0, 0x2C93, 0x32519, 50);
				return false;
			}
			return false;
		}
		if (!任务::任务是否已完成(0x3251A, vsk))//加强防备 
		{
			if (任务::是否已接任务(0x3251A))//从斯凯哈尔那收集 <FONT COLOR='{0}'>粘液</FONT>
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0x3251A);
				if (支线任务.dState == 1)//净化<FONT COLOR='#CFF960'>堆放的尸体</FONT>
				{
					if (支线任务.子任务进度.size() == 2)
					{
						if (支线任务.子任务进度[0].dCur < 支线任务.子任务进度[0].dNeed)
						{
							坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
							CString temp;
							temp.Format(L"%d", 支线任务.子任务进度[0].TargetID);
							加入优先打怪ID(L"122030");
							MyTrace(L"优先打怪数量%d", 优先打怪ID.size());
							功能::移动打怪(2796, 14266, 0, 500, 3000, 200);
							return false;
						}
						if (支线任务.子任务进度[1].dCur < 支线任务.子任务进度[1].dNeed)
						{
							坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
							CString temp;
							temp.Format(L"%d", 支线任务.子任务进度[1].TargetID);
							加入优先打怪ID(L"122010");
							MyTrace(L"优先打怪数量%d", 优先打怪ID.size());
							功能::移动打怪(2796, 14266, 0, 500, 2000, 100);
							return false;
						}
					}


					/*功能::到指定地点采集(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 1000, 支线任务.TargetId, 100, 150);*/
					return false;
				}
				if (支线任务.dState == 2)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					//MyTrace(L"任务目标 大陆ID:%d 地图ID %d 本大陆ID：%d", 任务坐标.大陆ID, 任务坐标.地图ID, 地图::取当前大陆ID());
					功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0x2C94, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
			else
			{
				功能::到指定地点找NPC接任务2(1, 10220, 2607, 10917, -5, 0x2C94, 0x3251A, 50);
				return false;
			}
			return false;
		}
		if (!任务::任务是否已完成(0x3251D, vsk))//加强防备 
		{
			if (任务::是否已接任务(0x3251D))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0x3251D);
				if (支线任务.dState == 1)//净化<FONT COLOR='#CFF960'>堆放的尸体</FONT>
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					CString temp;
					temp.Format(L"%d", 支线任务.TargetId);
					加入优先打怪ID(temp);
					MyTrace(L"优先打怪数量%d", 优先打怪ID.size());
					功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 500, 3000, 200);
					/*功能::到指定地点采集(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 1000, 支线任务.TargetId, 100, 150);*/
					return false;
				}
				if (支线任务.dState == 2)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					//MyTrace(L"任务目标 大陆ID:%d 地图ID %d 本大陆ID：%d", 任务坐标.大陆ID, 任务坐标.地图ID, 地图::取当前大陆ID());
					功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0x2C98, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
			else
			{
				功能::到指定地点找NPC接任务2(1, 10220, 9092, 12982, 85, 0x2C9B, 0x3251D, 50);
				return false;
			}
			return false;
		}


	}
	if (任务::任务是否已完成(206002, vsk))
	{
		if (!任务::任务是否已完成(0x3251E, vsk))//加强防备 
		{
			if (任务::是否已接任务(0x3251E))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0x3251E);
				if (支线任务.dState == 1)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点采集(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 1000, 支线任务.TargetId, 100, 150);
					return false;
				}
				if (支线任务.dState == 2)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					//MyTrace(L"任务目标 大陆ID:%d 地图ID %d 本大陆ID：%d", 任务坐标.大陆ID, 任务坐标.地图ID, 地图::取当前大陆ID());
					功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0x2C99, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
			else
			{
				功能::到指定地点找NPC接任务2(1, 10220, 15802, 14239, 256, 0x2C99, 0x3251E, 50);
				return false;
			}
			return false;
		}
		if (!任务::任务是否已完成(0x3251F, vsk))//加强防备 
		{
			if (任务::是否已接任务(0x3251F))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0x3251F);
				if (支线任务.dState == 1)//净化<FONT COLOR='#CFF960'>堆放的尸体</FONT>
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点采集(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 1000, 支线任务.TargetId, 100, 150);
					return false;
				}
				if (支线任务.dState == 2)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					//MyTrace(L"任务目标 大陆ID:%d 地图ID %d 本大陆ID：%d", 任务坐标.大陆ID, 任务坐标.地图ID, 地图::取当前大陆ID());
					功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0x2C9A, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
			else
			{
				功能::到指定地点找NPC接任务2(1, 10220, 17450, 12427, 256, 0x2C9A, 0x3251F, 50);
				return false;
			}
			return false;
		}
	}
	return true;
}
bool 游戏::支线_国境地带(vector<DWORD>& vsk)
{
	if (任务::任务是否已完成(208001, vsk) || 任务::取出指定主线任务(208001).dStep >= 5)//国境地带 袭击商团的是？
	{
		if (!任务::任务是否已完成(0x32D01, vsk))//当时的回忆  在乱成一堆的宝箱里找到<FONT COLOR='#CFF960'>药箱</FONT>
		{
			if (任务::是否已接任务(0x32D01))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0x32D01);
				if (支线任务.dState == 1)//净化<FONT COLOR='#CFF960'>堆放的尸体</FONT>
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点采集(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 1000, 0x5239, 100, 150);
					return false;
				}
				if (支线任务.dState == 2)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					//MyTrace(L"任务目标 大陆ID:%d 地图ID %d 本大陆ID：%d", 任务坐标.大陆ID, 任务坐标.地图ID, 地图::取当前大陆ID());
					功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0x2DE0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
			else
			{
				功能::到指定地点找NPC接任务2(1, 10222, 8186, 4860, 0, 0x2DE0, 0x32D01, 50);
				return false;
			}
			return false;
		}
	}
	if (任务::任务是否已完成(208003, vsk))//国境地带 袭击商团的是？
	{
		if (!任务::任务是否已完成(0x32CF2, vsk))//当时的回忆  在乱成一堆的宝箱里找到<FONT COLOR='#CFF960'>药箱</FONT>
		{
			if (任务::是否已接任务(0x32CF2))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0x32CF2);
				if (支线任务.dState == 1)//净化<FONT COLOR='#CFF960'>堆放的尸体</FONT>
				{
					if (支线任务.子任务进度.size() == 2)
					{
						if (支线任务.子任务进度[0].dCur < 支线任务.子任务进度[0].dNeed)
						{
							坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
							CString temp;
							temp.Format(L"%d", 支线任务.子任务进度[0].TargetID);
							加入优先打怪ID(temp);
							MyTrace(L"优先打怪数量%d", 优先打怪ID.size());
							功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 500, 3000, 200);
							return false;
						}
						if (支线任务.子任务进度[1].dCur < 支线任务.子任务进度[1].dNeed)
						{
							坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
							CString temp;
							temp.Format(L"%d", 支线任务.子任务进度[1].TargetID);
							加入优先打怪ID(temp);
							MyTrace(L"优先打怪数量%d", 优先打怪ID.size());
							功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 500, 3000, 100);
							return false;
						}
					}
				}
				if (支线任务.dState == 2)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					//MyTrace(L"任务目标 大陆ID:%d 地图ID %d 本大陆ID：%d", 任务坐标.大陆ID, 任务坐标.地图ID, 地图::取当前大陆ID());
					功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0x2CC0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
			else
			{
				功能::到指定地点找NPC接任务2(1, 10222, 6568, 13424, 0, 0x2CC0, 0x32CF2, 50);
				return false;
			}
			return false;
		}

	}
	if (任务::任务是否已完成(208004, vsk) || 任务::取出指定主线任务(208004).dStep >= 2)//国境地带 袭击商团的是？
	{
		//MyTrace(L"208004");
		if (!任务::任务是否已完成(0x32CF1, vsk))//当时的回忆  在乱成一堆的宝箱里找到<FONT COLOR='#CFF960'>药箱</FONT>
		{
			if (!任务::是否已接任务(0x32CF1))
			{
				MyTrace(L"接0x32CF1");
				功能::到指定地点找NPC接任务2(1, 10222, 6568, 13424, 0, 0x2CC0, 0x32CF1, 50);
				return false;
			}
		}
		if (!任务::任务是否已完成(0x32CF9, vsk))//当时的回忆  在乱成一堆的宝箱里找到<FONT COLOR='#CFF960'>药箱</FONT>
		{
			if (任务::是否已接任务(0x32CF9))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0x32CF9);
				if (支线任务.dStep == 1)//支援<FONT COLOR='#CFF960'>国境哨所</FONT>
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点破坏击打道具(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 2000, 0x522B, 100);
					return false;
				}
				if (支线任务.dStep == 2)//支援<FONT COLOR='#CFF960'>国境哨所</FONT>
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					//MyTrace(L"任务目标 大陆ID:%d 地图ID %d 本大陆ID：%d", 任务坐标.大陆ID, 任务坐标.地图ID, 地图::取当前大陆ID());
					功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0x2CC5, 支线任务.dQuestId, -1, 25);
					return false;
				}
				if (支线任务.dStep == 3)//支援<FONT COLOR='#CFF960'>国境哨所</FONT>
				{
					if (支线任务.dState == 1)//支援<FONT COLOR='#CFF960'>国境哨所</FONT>
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点采集(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 3000, 支线任务.TargetId, 100, 150);
						return false;
					}
					if (支线任务.dState == 2)//支援<FONT COLOR='#CFF960'>国境哨所</FONT>
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						//MyTrace(L"任务目标 大陆ID:%d 地图ID %d 本大陆ID：%d", 任务坐标.大陆ID, 任务坐标.地图ID, 地图::取当前大陆ID());
						功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 100);
						return false;
					}
				}


			}
			else
			{
				功能::到指定地点找NPC接任务2(1, 10222, 3722, 12152, 0, 0x2CC6, 0x32CF9, 50);
				return false;
			}
		}
		if (!任务::任务是否已完成(0x32CF1, vsk))//当时的回忆  在乱成一堆的宝箱里找到<FONT COLOR='#CFF960'>药箱</FONT>
		{
			if (任务::是否已接任务(0x32CF1))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0x32CF1);
				if (支线任务.dState == 1)//支援<FONT COLOR='#CFF960'>国境哨所</FONT>
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 200);
					return false;
				}
				if (支线任务.dState == 2)//支援<FONT COLOR='#CFF960'>国境哨所</FONT>
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					//MyTrace(L"任务目标 大陆ID:%d 地图ID %d 本大陆ID：%d", 任务坐标.大陆ID, 任务坐标.地图ID, 地图::取当前大陆ID());
					功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0x2CCB, 支线任务.dQuestId, -1, 25);
					return false;
				}

			}
			else
			{
				功能::到指定地点找NPC接任务2(1, 10222, 6568, 13424, 0, 0x2CC0, 0x32CF1, 50);
				return false;
			}
		}
	}
	return true;
}
bool 游戏::支线_萨尔兰德丘陵(vector<DWORD>& vsk)
{
	if (任务::取出指定主线任务(601001).dStep >= 2)//国境地带 袭击商团的是？
	{
		if (!任务::任务是否已完成(0x92C0D, vsk))//当时的回忆  在乱成一堆的宝箱里找到<FONT COLOR='#CFF960'>药箱</FONT>
		{
			if (!任务::是否已接任务(0x92C0D))
			{
				功能::到指定地点找NPC接任务2(17, 10611, -2928, -13111, 1024, 0x2D51, 0x92C0D, 50);
				return false;
			}
		}
	}
	if (任务::任务是否已完成(601001, vsk))//
	{
		if (!任务::任务是否已完成(0x92C0D, vsk))//传达消息
		{
			if (任务::是否已接任务(0x92C0D))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0x92C0D);
				if (支线任务.dStep == 1)//将情况通知临时营地的车队领队<FONT COLOR='{0}'>乔弗瑞</FONT>那里
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 11603, 支线任务.dQuestId, -1, 25);
				}
				return false;

			}
			else
			{
				功能::到指定地点找NPC接任务2(17, 10611, -2928, -13111, 1024, 0x2D51, 0x92C0D, 50);
				return false;
			}
		}
	}
	if (任务::取出指定主线任务(601002).dStep >= 3)//燃烧的营地
	{
		if (!任务::任务是否已完成(0x92C0F, vsk))//传达消息
		{
			if (任务::是否已接任务(0x92C0F))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0x92C0F);
				if (支线任务.dStep == 1)//将情况通知临时营地的车队领队<FONT COLOR='{0}'>乔弗瑞</FONT>那里
				{
					if (支线任务.dState == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点采集(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 3000, 0xEAD4, 100, 150);
					}
					else
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 11612, 支线任务.dQuestId, -1, 25);
					}

				}
				return false;

			}
			else
			{
				功能::到指定地点找NPC接任务2(17, 10611, 2770, -12372, 1024, 0x2D52, 0x92C0F, 50);
				return false;
			}
		}

	}
	if (任务::任务是否已完成(601002, vsk))//燃烧的营地
	{
		if (!任务::任务是否已完成(0x92C13, vsk))//传达消息
		{
			if (任务::是否已接任务(0x92C13))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0x92C13);
				if (支线任务.dStep == 1)//将情况通知临时营地的车队领队<FONT COLOR='{0}'>乔弗瑞</FONT>那里
				{
					if (支线任务.子任务进度.size() == 2)
					{
						if (支线任务.子任务进度[0].dCur < 支线任务.子任务进度[0].dNeed)
						{
							坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
							功能::到指定地点采集(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 3000, 60119, 100, 150);
							return false;
						}
						if (支线任务.子任务进度[1].dCur < 支线任务.子任务进度[1].dNeed)
						{
							坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
							CString temp;
							temp.Format(L"%d", 支线任务.子任务进度[1].TargetID);
							加入优先打怪ID(temp);
							MyTrace(L"优先打怪数量%d", 优先打怪ID.size());
							功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 300, 1000, 150);
							return false;
						}
					}
					if (支线任务.dState == 2)//将情况通知临时营地的车队领队<FONT COLOR='{0}'>乔弗瑞</FONT>那里
					{

					}
				}

				//return false;

			}
			else
			{
				功能::到指定地点找NPC接任务2(17, 10611, 9378, -11207, 1535, 0x2DEB, 0x92C13, 50);
				return false;
			}
		}
		if (!任务::任务是否已完成(0x92C12, vsk))//传达消息
		{
			if (任务::是否已接任务(0x92C12))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0x92C12);
				if (支线任务.dStep == 1)//将情况通知临时营地的车队领队<FONT COLOR='{0}'>乔弗瑞</FONT>那里
				{
					if (支线任务.dState == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						CString temp;
						temp.Format(L"%d", 支线任务.TargetId);
						加入优先打怪ID(temp);
						MyTrace(L"优先打怪数量%d", 优先打怪ID.size());
						功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 300, 1000, 150);
						return false;
					}
					else
					{

					}

				}


			}
			else
			{
				功能::到指定地点找NPC接任务2(17, 10611, 9255, -11058, 1535, 0x2DD1, 0x92C12, 50);
				return false;
			}
		}
		if (!任务::任务是否已完成(0x92C13, vsk))//传达消息
		{
			QuestInfo_ 支线任务 = 任务::取出指定支线任务(0x92C13);
			if (支线任务.dState == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
				功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0x2D55, 支线任务.dQuestId, -1, 25);
				return false;
			}
		}
		if (!任务::任务是否已完成(0x92C12, vsk))//传达消息
		{
			QuestInfo_ 支线任务 = 任务::取出指定支线任务(0x92C12);
			if (支线任务.dState == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
				功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0x2D77, 支线任务.dQuestId, -1, 25);
				return false;
			}
		}
	}
	if (任务::任务是否已完成(601005, vsk))//燃烧的营地
	{
		if (!任务::任务是否已完成(0x92C17, vsk))//传达消息
		{
			if (任务::是否已接任务(0x92C17))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0x92C17);
				if (支线任务.dState == 1)
				{
					if (支线任务.子任务进度.size() == 2)
					{
						if (支线任务.子任务进度[0].dCur < 支线任务.子任务进度[0].dNeed)
						{
							坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
							功能::到指定地点采集(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 3000, 支线任务.子任务进度[0].TargetID, 200, 150);
							return false;
						}
						if (支线任务.子任务进度[1].dCur < 支线任务.子任务进度[1].dNeed)
						{
							坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
							CString temp;
							temp.Format(L"%d", 支线任务.子任务进度[1].TargetID);
							加入优先打怪ID(L"60152");
							MyTrace(L"优先打怪数量%d", 优先打怪ID.size());
							功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 300, 5000, 100, true, 200);
							return false;

						}
					}
				}
				/*if (支线任务.dState == 2)
				{
					优先打怪ID.clear();
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0x2D5A, 支线任务.dQuestId, -1, 25);
					return false;
				}*/

			}
			else
			{
				功能::到指定地点找NPC接任务2(17, 10611, -5719, 3472, 1024, 0x2D5A, 0x92C17, 50);
				return false;
			}
		}
		if (!任务::任务是否已完成(0x92C18, vsk))//传达消息
		{
			if (任务::是否已接任务(0x92C18))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0x92C18);
				if (支线任务.dState == 1)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					CString temp;
					temp.Format(L"%d", 支线任务.TargetId);
					加入优先打怪ID(temp);
					MyTrace(L"优先打怪数量%d", 优先打怪ID.size());
					功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 300, 2000, 150);
					return false;
				}
			}
			else
			{
				功能::到指定地点找NPC接任务2(17, 10611, -5719, 3472, 1024, 0x2DEC, 0x92C18, 50);
				return false;
			}
		}
		if (!任务::任务是否已完成(0x92C17, vsk))//传达消息
		{
			QuestInfo_ 支线任务 = 任务::取出指定支线任务(0x92C17);
			if (支线任务.dState == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
				功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0x2D5A, 支线任务.dQuestId, -1, 25);
				return false;
			}
		}
		if (!任务::任务是否已完成(0x92C18, vsk))//传达消息
		{
			QuestInfo_ 支线任务 = 任务::取出指定支线任务(0x92C18);
			if (支线任务.dState == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
				功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0x2DEC, 支线任务.dQuestId, -1, 25);
				return false;
			}
		}
		if (!任务::任务是否已完成(0x92C15, vsk))//传达消息
		{
			if (任务::是否已接任务(0x92C15))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0x92C15);
				if (支线任务.dState == 1)
				{
					if (支线任务.子任务进度.size() == 2)
					{
						if (支线任务.子任务进度[0].dCur < 支线任务.子任务进度[0].dNeed)
						{
							坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
							CString temp;
							temp.Format(L"%d", 支线任务.子任务进度[0].TargetID);
							加入优先打怪ID(temp);
							MyTrace(L"优先打怪数量%d", 优先打怪ID.size());
							功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 300, 1500, 150);
							return false;
						}
						if (支线任务.子任务进度[1].dCur < 支线任务.子任务进度[1].dNeed)
						{
							坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
							CString temp;
							temp.Format(L"%d", 支线任务.子任务进度[1].TargetID);
							加入优先打怪ID(temp);
							MyTrace(L"优先打怪数量%d", 优先打怪ID.size());
							功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 300, 1500, 150);
							return false;

						}
					}
					return false;
				}
				if (支线任务.dState == 2)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0x2D57, 支线任务.dQuestId, -1, 25);
					return false;
				}

			}
			else
			{
				功能::到指定地点找NPC接任务2(17, 10611, 1561, 933, 512, 0x2DA7, 0x92C15, 50);
				return false;
			}
		}
	}

	if (任务::任务是否已完成(601006, vsk) || 任务::取出指定主线任务(601006).dStep >= 2)//燃烧的营地
	{
		if (!任务::任务是否已完成(0x92C1A, vsk))//传达消息
		{
			if (任务::是否已接任务(0x92C1A))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0x92C1A);
				if (支线任务.dState == 1)
				{
					if (支线任务.子任务进度[0].dCur < 支线任务.子任务进度[0].dNeed)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						CString temp;
						temp.Format(L"%d", 支线任务.子任务进度[0].TargetID);
						加入优先打怪ID(temp);
						MyTrace(L"优先打怪数量%d", 优先打怪ID.size());
						功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 300, 500, 150);
						return false;
					}
					if (支线任务.子任务进度[1].dCur < 支线任务.子任务进度[1].dNeed)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						CString temp;
						temp.Format(L"%d", 支线任务.子任务进度[1].TargetID);
						加入优先打怪ID(temp);
						MyTrace(L"优先打怪数量%d", 优先打怪ID.size());
						功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 300, 500, 150);
						return false;

					}
				}
				if (任务::任务是否已完成(601006, vsk))
				{
					if (支线任务.dState == 2)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0x2DEE, 支线任务.dQuestId, -1, 25);
						return false;
					}
				}

			}
			else
			{
				功能::到指定地点找NPC接任务2(17, 10611, -376, 7201, 512, 0x2D59, 0x92C1A, 50);
				return false;
			}
		}
	}
	if (任务::任务是否已完成(602001, vsk))//燃烧的营地
	{
		if (!任务::任务是否已完成(0x92FF5, vsk))//传达消息
		{
			if (任务::是否已接任务(0x92FF5))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0x92FF5);
				if (支线任务.dState == 1)
				{
					if (支线任务.子任务进度.size() == 2)
					{
						if (支线任务.子任务进度[0].dCur < 支线任务.子任务进度[0].dNeed)
						{
							坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
							CString temp;
							temp.Format(L"%d", 支线任务.子任务进度[0].TargetID);
							加入优先打怪ID(temp);
							MyTrace(L"优先打怪数量%d", 优先打怪ID.size());
							功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 300, 500, 150);
							return false;

						}
						if (支线任务.子任务进度[1].dCur < 支线任务.子任务进度[1].dNeed)
						{
							坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
							功能::到指定地点采集(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 3000, 60237, 200, 150);
							return false;

						}

					}

				}
				if (支线任务.dState == 2)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
			else
			{
				功能::到指定地点找NPC接任务2(17, 10611, 9063, 25649, 509, 0x2D6C, 0x92FF5, 50);
			}
		}
		if (!任务::任务是否已完成(0x92FF6, vsk))
		{
			if (任务::是否已接任务(0x92FF6))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0x92FF6);//挖掘地面并获得 <FONT COLOR='{0}'>巴拉特的木盒</FONT>
				if (支线任务.dState == 1)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点采集(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 3000, 60239, 200, 150);
					return false;
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
			else
			{
				功能::到指定地点找NPC接任务2(17, 10611, 3976, 29612, 509, 0x2D70, 0x92FF6, 50);
				return false;
			}
		}

	}
	if (任务::任务是否已完成(602002, vsk))//燃烧的营地
	{
		if (!任务::任务是否已完成(0x92FF7, vsk))
		{
			if (任务::是否已接任务(0x92FF7))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0x92FF7);//挖掘地面并获得 <FONT COLOR='{0}'>巴拉特的木盒</FONT>
				if (支线任务.dState == 1)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					CString temp;
					temp.Format(L"%d", 支线任务.TargetId);
					加入优先打怪ID(temp);
					MyTrace(L"优先打怪数量%d", 优先打怪ID.size());
					功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 300, 2000, 150, true, 100);
					return false;
				}

			}
			else
			{
				功能::到指定地点找NPC接任务2(17, 10611, 3976, 29612, 509, 0x2D70, 0x92FF7, 50);
				return false;
			}
		}
		if (!任务::任务是否已完成(0x93004, vsk))
		{
			if (任务::是否已接任务(0x93004))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0x93004);//挖掘地面并获得 <FONT COLOR='{0}'>巴拉特的木盒</FONT>

				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点采集(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 3000, 0xEB79, 200, 150);
						return false;
					}
					if (支线任务.dStep == 2)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						CString temp;
						temp.Format(L"%d", 支线任务.TargetId);
						加入优先打怪ID(temp);
						MyTrace(L"优先打怪数量%d", 优先打怪ID.size());
						功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 300, 300, 150);
						return false;
					}
				}

			}
			else
			{
				功能::到指定地点找NPC接任务2(17, 10611, 3888, 29698, 509, 0x2D71, 0x93004, 50);
				return false;
			}
		}
		if (!任务::任务是否已完成(0x93002, vsk))
		{
			if (任务::是否已接任务(0x93002))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0x93002);//挖掘地面并获得 <FONT COLOR='{0}'>巴拉特的木盒</FONT>

				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
						return false;
					}
					if (支线任务.dStep == 2)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
						return false;
					}

				}
				if (支线任务.dState == 2)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}

			}
			else
			{
				功能::到指定地点找NPC接任务2(17, 10611, 12845, 34321, 509, 0x2D7D, 0x93002, 50);
				return false;
			}
		}
		if (!任务::任务是否已完成(0x92FF7, vsk))
		{
			if (任务::是否已接任务(0x92FF7))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0x92FF7);//挖掘地面并获得 <FONT COLOR='{0}'>巴拉特的木盒</FONT>
				if (支线任务.dState == 2)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}
		if (!任务::任务是否已完成(0x93004, vsk))
		{
			if (任务::是否已接任务(0x93004))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0x93004);//挖掘地面并获得 <FONT COLOR='{0}'>巴拉特的木盒</FONT>
				if (支线任务.dState == 2)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}

	}
	if (任务::任务是否已完成(602004, vsk) || 任务::取出指定主线任务(602004).dStep >= 3)//燃烧的营地
	{
		if (!任务::任务是否已完成(0x92FFD, vsk))//传达消息
		{
			if (!任务::是否已接任务(0x92FFD))
			{
				功能::到指定地点找NPC接任务2(17, 10611, 20925, 29805, 509, 0x2D68, 0x92FFD, 50);
				return false;
			}
		}
		if (!任务::任务是否已完成(0x92FFC, vsk))//传达消息
		{
			if (!任务::是否已接任务(0x92FFC))
			{
				功能::到指定地点找NPC接任务2(17, 10611, 19092, 29761, 509, 0x2D6A, 0x92FFC, 50);
				return false;
			}
		}

		if (!任务::任务是否已完成(0x92FFD, vsk))//传达消息
		{
			if (任务::是否已接任务(0x92FFD))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0x92FFD);//挖掘地面并获得 <FONT COLOR='{0}'>巴拉特的木盒</FONT>
				if (支线任务.dState == 1)
				{
					if (支线任务.子任务进度.size() == 2)
					{
						if (支线任务.子任务进度[0].dCur < 支线任务.子任务进度[0].dNeed)
						{
							坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
							CString temp;
							temp.Format(L"%d", 支线任务.子任务进度[0].TargetID);
							加入优先打怪ID(temp);
							MyTrace(L"优先打怪数量%d", 优先打怪ID.size());
							功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 300, 1500, 150);
							return false;
						}
						if (支线任务.子任务进度[1].dCur < 支线任务.子任务进度[1].dNeed)
						{
							坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
							CString temp;
							temp.Format(L"%d", 支线任务.子任务进度[1].TargetID);
							加入优先打怪ID(temp);
							MyTrace(L"优先打怪数量%d", 优先打怪ID.size());
							功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 300, 1500, 150);
							return false;
						}
					}

				}
			}
		}
		if (!任务::任务是否已完成(0x92FFC, vsk))//传达消息
		{
			if (任务::是否已接任务(0x92FFC))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0x92FFC);//挖掘地面并获得 <FONT COLOR='{0}'>巴拉特的木盒</FONT>
				if (支线任务.dState == 1)
				{
					if (支线任务.子任务进度.size() == 3)
					{
						if (支线任务.子任务进度[0].dCur < 支线任务.子任务进度[0].dNeed)
						{
							坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
							功能::到指定地点采集(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 2000, 支线任务.子任务进度[0].TargetID, 200, 150);
							return false;
						}
						if (支线任务.子任务进度[1].dCur < 支线任务.子任务进度[1].dNeed)
						{
							坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
							功能::到指定地点采集(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 2000, 支线任务.子任务进度[1].TargetID, 200, 150);
							return false;
						}
						if (支线任务.子任务进度[2].dCur < 支线任务.子任务进度[2].dNeed)
						{
							坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
							功能::到指定地点采集(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 2000, 支线任务.子任务进度[2].TargetID, 200, 150);
							return false;
						}
					}
				}
			}
		}
		if (任务::任务是否已完成(602004, vsk))
		{
			if (任务::是否已接任务(0x92FFC))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0x92FFC);//挖掘地面并获得 <FONT COLOR='{0}'>巴拉特的木盒</FONT>
				if (支线任务.dState == 2)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
			if (任务::是否已接任务(0x92FFD))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0x92FFD);//挖掘地面并获得 <FONT COLOR='{0}'>巴拉特的木盒</FONT>
				if (支线任务.dState == 2)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}


	}
	return true;
}
bool 游戏::支线_奥兹霍丘陵(vector<DWORD>& vsk)
{
	if (任务::任务是否已完成(603001, vsk) || 任务::取出指定主线任务(603001).dStep >= 2)// 阿曼与恶魔
	{
		if (!任务::任务是否已完成(0x933DE, vsk))//传达消息
		{
			if (任务::是否已接任务(0x933DE))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0x933DE);//挖掘地面并获得 <FONT COLOR='{0}'>巴拉特的木盒</FONT>
				if (支线任务.dState == 1)
				{
					if (支线任务.子任务进度.size() == 2)
					{
						if (支线任务.子任务进度[0].dCur < 支线任务.子任务进度[0].dNeed)
						{
							坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
							功能::到指定地点采集任务显示(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 5000, 0xEB9A, 200, 150);
							return false;
						}
						if (支线任务.子任务进度[1].dCur < 支线任务.子任务进度[1].dNeed)
						{
							坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
							功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 300, 1500, 150);
							return false;
						}

					}
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
			else
			{
				功能::到指定地点找NPC接任务2(17, 10619, -13440, 13028, 512, 0x2D89, 0x933DE, 50);
				return false;
			}
		}
		if (!任务::任务是否已完成(0x933DF, vsk))//传达消息
		{
			if (任务::是否已接任务(0x933DF))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0x933DF);//挖掘地面并获得 <FONT COLOR='{0}'>巴拉特的木盒</FONT>
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点采集(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 2000, 0xEB98, 200, 150);
						return false;
					}
					if (支线任务.dStep == 2)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 支线任务.TargetId, 支线任务.dQuestId, -1, 25);
						return false;
					}


				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
			else
			{
				功能::到指定地点找NPC接任务2(17, 10619, -7108, 10841, 1023, 0x2D8A, 0x933DF, 50);
				return false;
			}
		}
	}
	if (任务::任务是否已完成(603001, vsk) || 任务::取出指定主线任务(603001).dStep >= 3)// 阿曼与恶魔
	{
		if (!任务::任务是否已完成(0x933E1, vsk))//传达消息
		{
			if (!任务::是否已接任务(0x933E1))
			{
				功能::到指定地点找NPC接任务2(17, 10619, -3057, 2424, 520, 0x2D8B, 0x933E1, 50);
				return false;
			}
		}
		if (!任务::任务是否已完成(0x933E2, vsk))//传达消息
		{
			if (!任务::是否已接任务(0x933E2))
			{
				功能::到指定地点找NPC接任务2(17, 10619, -3041, 2233, 512, 0x2DDB, 0x933E2, 50);
				return false;
			}
		}
		if (!任务::任务是否已完成(0x933E1, vsk))
		{
			if (任务::是否已接任务(0x933E1))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0x933E1);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						CString temp;
						temp.Format(L"%d", 支线任务.TargetId);
						加入优先打怪ID(temp);
						MyTrace(L"优先打怪数量%d", 优先打怪ID.size());
						功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 300, 1500, 150);
						return false;
					}
					if (支线任务.dStep == 2)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
						return false;
					}
				}

			}

		}
		if (!任务::任务是否已完成(0x933E2, vsk))
		{
			if (任务::是否已接任务(0x933E2))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0x933E2);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						CString temp;
						temp.Format(L"%d", 支线任务.TargetId);
						加入优先打怪ID(temp);
						MyTrace(L"优先打怪数量%d", 优先打怪ID.size());
						功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 500, 150);
						return false;
					}


				}

			}

		}


		if (任务::是否已接任务(0x933E2))
		{
			QuestInfo_ 支线任务 = 任务::取出指定支线任务(0x933E2);//挖掘地面并获得 <FONT COLOR='{0}'>巴拉特的木盒</FONT>
			if (支线任务.dState == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
				功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
				return false;
			}
		}

		if (!任务::任务是否已完成(0x933E0, vsk))
		{
			if (任务::是否已接任务(0x933E0))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0x933E0);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);

						功能::到指定地点采集任务显示(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 2500, 0xEB9D, 200, 150);
						return false;
					}
					if (支线任务.dStep == 2)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
						return false;
					}
				}

			}
			else
			{
				功能::到指定地点找NPC接任务2(17, 10619, -5463, -2680, 529, 0x26B5, 0x933E0, 50);
				return false;
			}

		}
		if (任务::任务是否已完成(603002, vsk) || 任务::取出指定主线任务(603002).dStep >= 3)//主线
		{
			if (!任务::任务是否已完成(0x933ED, vsk))
			{
				if (任务::是否已接任务(0x933ED))
				{
					QuestInfo_ 支线任务 = 任务::取出指定支线任务(0x933ED);
					if (支线任务.dState == 1)
					{
						if (支线任务.dStep == 1)
						{
							坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
							功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 300, 1500, 150);
							return false;
						}

					}
					else
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
						return false;

					}

				}
				else
				{
					功能::到指定地点找NPC接任务2(17, 10619, -1739, -3088, 512, 0x2D99, 0x933ED, 50);
					return false;
				}

			}

			if (任务::是否已接任务(0x933E1))//不祥的气息 
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0x933E1);//挖掘地面并获得 <FONT COLOR='{0}'>巴拉特的木盒</FONT>
				if (支线任务.dState == 2)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
			if (任务::是否已接任务(0x933E0))//收集遗物 
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0x933E0);//挖掘地面并获得 <FONT COLOR='{0}'>巴拉特的木盒</FONT>
				if (支线任务.dState == 2)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}

	}
	if (任务::任务是否已完成(603002, vsk))
	{
		if (!任务::任务是否已完成(0x933E4, vsk))
		{
			if (!任务::是否已接任务(0x933E4))
			{
				功能::到指定地点找NPC接任务2(17, 10619, 318, 1916, 511, 0x2DDD, 0x933E4, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0x933E4);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
						return false;
					}

				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;

				}
			}
		}

		if (!任务::任务是否已完成(0x933E6, vsk))
		{
			if (!任务::是否已接任务(0x933E6))
			{
				功能::到指定地点找NPC接任务2(17, 10619, 1243, 1872, 511, 0x2D93, 0x933E6, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0x933E6);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点采集(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 2000, 0xEBCF, 200, 150);
						return false;
					}
					if (支线任务.dStep == 2)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点按G(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 150);
						return false;
					}

				}
				else
				{
					任务::CALL_交任务(支线任务.dQuestId, -1);
					/*坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);*/
					return false;

				}
			}
		}

	}
	if (任务::任务是否已完成(603003, vsk) || 任务::取出指定主线任务(603003).dStep >= 4)
	{
		if (!任务::任务是否已完成(0x933EA, vsk))
		{
			if (!任务::是否已接任务(0x933EA))
			{
				功能::到指定地点找NPC接任务2(17, 10619, 7585, -2888, 511, 0x2DA4, 0x933EA, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0x933EA);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点采集(17, 任务坐标.地图ID, 10647, -3395, 511, 2000, 0xEBDC, 200, 150);
						return false;
					}


				}

			}
		}
		if (!任务::任务是否已完成(0x933EB, vsk))
		{
			if (!任务::是否已接任务(0x933EB))
			{
				功能::到指定地点找NPC接任务2(17, 10619, 6260, -2119, 511, 0x2E01, 0x933EB, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0x933EB);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
						return false;
					}


				}
				else
				{
					//任务::CALL_交任务(支线任务.dQuestId, -1);
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;

				}
			}
		}
		if (任务::是否已接任务(0x933EA))//收集遗物 
		{
			QuestInfo_ 支线任务 = 任务::取出指定支线任务(0x933EA);//挖掘地面并获得 <FONT COLOR='{0}'>巴拉特的木盒</FONT>
			if (支线任务.dState == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
				功能::到指定地点找NPC交任务2(17, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
				return false;
			}
		}
	}

	return true;
}
bool 游戏::支线_扎格拉斯山(vector<DWORD>& vsk)
{
	if (任务::任务是否已完成(0xC3CD1, vsk) || 任务::取出指定主线任务(0xC3CD1).dStep >= 3) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(0xC3D36, vsk))
		{
			if (!任务::是否已接任务(0xC3D36))
			{
				功能::到指定地点找NPC接任务2(14, 10811, 2911, 4348, 512, 0x2F60, 0xC3D36, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC3D36);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 300, 1500, 150);
						return false;
					}


				}
				else
				{
					//任务::CALL_交任务(支线任务.dQuestId, -1);
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;

				}
			}
		}
		if (!任务::任务是否已完成(0xC3D37, vsk))
		{
			MyTrace(L"0xC3D37 未完成");
			if (!任务::是否已接任务(0xC3D37))
			{
				功能::到指定地点找NPC接任务2(14, 10811, 4353, 2670, 1024, 0x2EE2, 0xC3D37, 50);
				return false;
			}
			else
			{
				//MyTrace(L"0xC3D37 已接");
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC3D37);
				if (支线任务.dState == 1)
				{
					//MyTrace(L"0xC3D37 state=1");
					if (支线任务.dStep == 1)
					{
						//MyTrace(L"0xC3D37 dStep=1");
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点采集(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 1500, 0x139B8, 100, 200);
						return false;
					}


				}
				else
				{
					//任务::CALL_交任务(支线任务.dQuestId, -1);
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;

				}
			}
		}
	}
	if (任务::任务是否已完成(802007, vsk) || 任务::取出指定主线任务(802007).dStep >= 2) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(0xC3D3A, vsk))
		{
			if (!任务::是否已接任务(0xC3D3A))
			{
				功能::到指定地点找NPC接任务2(14, 10811, 16084, 13330, 2048, 0x2EE7, 0xC3D3A, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC3D3A);
				if (支线任务.dState == 1)
				{
					//MyTrace(L"0xC3D37 state=1");
					if (支线任务.dStep == 1)
					{
						//MyTrace(L"0xC3D37 dStep=1");
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点按G(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 200);
						return false;
					}
					if (支线任务.dStep == 2)
					{
						UI功能::内存按键(VK_F5);
						Sleep(1000);
						return false;
					}
					if (支线任务.dStep == 3)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务2(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
						return false;
					}
					if (支线任务.dStep == 4)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点采集(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 1500, 0x139B4, 100, 200);
						return false;
					}


				}
				else
				{
					//任务::CALL_交任务(支线任务.dQuestId, -1);
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;

				}
			}
		}
	}
	if (任务::任务是否已完成(802007, vsk) || 任务::取出指定主线任务(802007).dStep >= 3) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(0xC3D3C, vsk))
		{
			if (!任务::是否已接任务(0xC3D3C))
			{
				功能::到指定地点找NPC接任务2(14, 10811, 27085, 18871, 2560, 0x2EEB, 0xC3D3C, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC3D3C);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						加入优先打怪ID(L"180242");
						功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 300, 1500, 150);
						return false;
					}
				}
			}
		}
		if (任务::任务是否已完成(802007, vsk) || 任务::取出指定主线任务(802007).dStep >= 4)
		{
			if (任务::是否已接任务(0xC3D3C))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC3D3C);
				if (支线任务.dState == 2)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}

	}
	if (任务::任务是否已完成(802008, vsk) || 任务::取出指定主线任务(802008).dStep >= 2) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(0xC3D3F, vsk))
		{
			if (!任务::是否已接任务(0xC3D3F))
			{
				功能::到指定地点找NPC接任务2(14, 10811, 16084, 13330, 2048, 0x2EE7, 0xC3D3F, 50);
				return false;
			}
		}
		if (!任务::任务是否已完成(0xC3D3E, vsk))
		{
			if (!任务::是否已接任务(0xC3D3E))
			{
				功能::到指定地点找NPC接任务2(14, 10811, 16666, 11568, 2052, 0x2F62, 0xC3D3E, 50);
				return false;
			}
		}
		if (!任务::任务是否已完成(0xC3D3F, vsk))
		{
			QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC3D3F);
			if (支线任务.dState == 1)
			{
				if (支线任务.dStep == 1)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					加入优先打怪ID(L"180320");
					功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 300, 1500, 150);
					return false;
				}
			}

		}
		if (!任务::任务是否已完成(0xC3D3E, vsk))
		{
			QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC3D3E);
			if (支线任务.dState == 1)
			{
				if (支线任务.dStep == 1)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点按G(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 200);
					return false;
				}
			}
		}
		if (任务::是否已接任务(0xC3D3F))
		{
			QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC3D3F);
			if (支线任务.dState == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
				功能::到指定地点找NPC交任务2(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
				return false;
			}
		}
		if (任务::是否已接任务(0xC3D3E))
		{
			QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC3D3E);
			if (支线任务.dState == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
				功能::到指定地点找NPC交任务2(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
				return false;
			}
		}
	}
	if (任务::任务是否已完成(802008, vsk)) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(0xC3D45, vsk))
		{
			if (!任务::是否已接任务(0xC3D45))
			{
				功能::到指定地点找NPC接任务2(14, 10811, 16310, 7672, 2048, 0x2EE8, 0xC3D45, 50);
				return false;
			}
		}
		if (!任务::任务是否已完成(0xC3D45, vsk))
		{
			QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC3D45);
			if (支线任务.dState == 1)
			{
				if (支线任务.dStep == 1)
				{
					ActorInfo_ 角色信息 = 本人::取角色信息();
					if (角色信息.举起状态 == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点采集(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 1500, 0x139B2, 100, 150);
						return false;
					}
					else
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						if (功能::到指定地点(14, 任务坐标.地图ID, 16644, 8235, 2048, 50))
						{
							UI功能::内存按键(DWORD('R'));
						}
						return false;
					}
				}

			}
			else
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
				功能::到指定地点找NPC交任务2(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
				return false;
			}

		}
	}
	return true;
}
bool 游戏::支线_雷科巴(vector<DWORD>& vsk)
{
	//if (任务::任务是否已完成(0xC3CD1, vsk) || 任务::取出指定主线任务(0xC3CD1).dStep >= 3) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	//{
	//	if (!任务::任务是否已完成(0xC3D36, vsk))
	//	{

	//	}
	//}
	if (任务::任务是否已完成(803003, vsk) || 任务::取出指定主线任务(803003).dStep >= 2) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(0xC4120, vsk))
		{
			if (!任务::是否已接任务(0xC4120))
			{
				功能::到指定地点找NPC接任务2(14, 10812, 11980, 15386, 1024, 0x2EF7, 0xC4120, 50);
				return false;
			}
		}
		if (!任务::任务是否已完成(0xC4122, vsk))
		{
			if (!任务::是否已接任务(0xC4122))
			{
				功能::到指定地点找NPC接任务2(14, 10812, 10341, 13799, 1021, 0x2EFB, 0xC4122, 50);
				return false;
			}
		}
		if (!任务::任务是否已完成(0xC4120, vsk))
		{
			QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC4120);
			if (支线任务.dState == 1)
			{
				if (支线任务.dStep == 1)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点采集(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 1500, 0x13A18, 100, 150);
					return false;
				}
			}
		}
		if (!任务::任务是否已完成(0xC4122, vsk))
		{
			QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC4122);
			if (支线任务.dState == 1)
			{
				if (支线任务.dStep == 1)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					加入优先打怪ID(L"80413");
					功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 300, 1000, 100);
					return false;
				}
			}
		}
		if (任务::任务是否已完成(803003, vsk) || 任务::取出指定主线任务(803003).dStep >= 3)
		{
			if (!任务::任务是否已完成(0xC4120, vsk))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC4120);
				if (支线任务.dState == 2)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
			if (!任务::任务是否已完成(0xC4122, vsk))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC4122);
				if (支线任务.dState == 2)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}
	}
	if (任务::任务是否已完成(803006, vsk)) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(0xC4125, vsk))
		{
			if (!任务::是否已接任务(0xC4125))
			{
				功能::到指定地点找NPC接任务2(14, 10812, 10359, 4436, 1277, 0x2F06, 0xC4125, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC4125);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点按G(14, 任务坐标.地图ID, 10737, 4084, 1393, 50);
					}
					return false;
				}
				if (支线任务.dState == 2)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}
	}
	return true;
}
bool 游戏::支线_梅德里克修道院(vector<DWORD>& vsk)
{
	//if (任务::任务是否已完成(0xC3CD1, vsk) || 任务::取出指定主线任务(0xC3CD1).dStep >= 3) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	//{
	//	if (!任务::任务是否已完成(0xC3D36, vsk))
	//	{

	//	}
	//}
	if (任务::任务是否已完成(805001, vsk) || 任务::取出指定主线任务(805001).dStep >= 2) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(0xC48ED, vsk))
		{
			if (!任务::是否已接任务(0xC48ED))
			{
				功能::到指定地点找NPC接任务2(14, 10813, 2497, -1525, 1957, 0x2FC0, 0xC48ED, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC48ED);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						加入优先打怪ID(L"180570");
						功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 300, 3000, 100);
						return false;
					}
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}
	}
	if (任务::任务是否已完成(805001, vsk) || 任务::取出指定主线任务(805001).dStep >= 3) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(0xC48EE, vsk))
		{
			if (!任务::是否已接任务(0xC48EE))
			{
				功能::到指定地点找NPC接任务2(14, 10813, 10963, 10150, 2896, 0x2F0E, 0xC48EE, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC48EE);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						if (支线任务.子任务进度.size() == 2)
						{
							if (支线任务.子任务进度[0].dCur < 支线任务.子任务进度[0].dNeed)
							{
								坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
								加入优先打怪ID(L"180610");
								功能::移动打怪(6182, 10437, 2387, 300, 3000, 100);
								return false;
							}
							if (支线任务.子任务进度[1].dCur < 支线任务.子任务进度[1].dNeed)
							{
								坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
								加入优先打怪ID(L"180600");
								功能::移动打怪(5577, 13471, 2130, 300, 3000, 100);
								return false;
							}
						}

					}
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}
	}
	if (任务::任务是否已完成(805003, vsk) || 任务::取出指定主线任务(805003).dStep >= 4)
	{
		if (!任务::任务是否已完成(0xC48F3, vsk))
		{
			if (!任务::是否已接任务(0xC48F3))
			{
				功能::到指定地点找NPC接任务2(14, 10813, 10157, 8145, 2896, 0x2F7A, 0xC48F3, 50);
				return false;
			}
		}
	}
	if (任务::任务是否已完成(805003, vsk) || 任务::取出指定主线任务(805003).dStep >= 6)
	{
		if (!任务::任务是否已完成(0xC48F3, vsk))
		{
			if (!任务::是否已接任务(0xC48F3))
			{
				功能::到指定地点找NPC接任务2(14, 10813, 10157, 8145, 2896, 0x2F7A, 0xC48F3, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC48F3);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务2(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
						return false;
					}
				}

			}
		}
		if (!任务::任务是否已完成(0xC48F4, vsk))
		{
			if (!任务::是否已接任务(0xC48F4))
			{
				功能::到指定地点找NPC接任务2(14, 10813, 21560, -283, 2672, 0x2FC1, 0xC48F4, 50);
				return false;
			}
		}
		if (!任务::任务是否已完成(0xC48F1, vsk))
		{
			if (!任务::是否已接任务(0xC48F1))
			{
				功能::到指定地点找NPC接任务2(14, 10813, 21560, -283, 2672, 0x2FC1, 0xC48F1, 50);
				return false;
			}
		}
		if (!任务::任务是否已完成(0xC48F1, vsk))
		{

			QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC48F1);
			if (支线任务.dState == 1)
			{
				if (支线任务.dStep == 1)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点采集(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 3000, 支线任务.TargetId, 200, 100);
					return false;
				}
			}
			else
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
				功能::到指定地点找NPC交任务2(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
				return false;
			}

		}
		if (!任务::任务是否已完成(0xC48F4, vsk))
		{

			QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC48F4);
			if (支线任务.dState == 1)
			{
				if (支线任务.dStep == 1)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
				if (支线任务.dStep == 2)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点采集(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 3000, 0x13A79, 200, 100);
					return false;
				}
			}
			else
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
				功能::到指定地点找NPC交任务2(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
				return false;
			}

		}
		if (!任务::任务是否已完成(0xC48FB, vsk))
		{
			MyTrace(L"执行支线 %x", 0xC48FB);
			if (!任务::是否已接任务(0xC48FB))
			{
				功能::到指定地点找NPC接任务2(14, 10813, 28895, -1797, 2673, 0x2F4F, 0xC48FB, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC48FB);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点按G(14, 任务坐标.地图ID, 24091, 4236, 1629, 200);
						return false;
					}
				}
				/*else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}*/

			}



		}
		if (!任务::任务是否已完成(0xC48F5, vsk))
		{
			MyTrace(L"执行支线 %x", 0xC48F5);
			if (!任务::是否已接任务(0xC48F5))
			{
				功能::到指定地点找NPC接任务2(14, 10813, 26805, 12770, 609, 0x2F7E, 0xC48F5, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC48F5);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						if (功能::到指定地点(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 2000))
						{
							objInfo_ 蝗虫 = 环境::取指定对象信息(0x2C146);
							if (蝗虫.dCurHp > 0)
							{
								if (蝗虫.fDis > 500)
								{
									地图::本地图寻路(蝗虫.坐标.x, 蝗虫.坐标.y, 蝗虫.坐标.z, 0);
								}
								else
								{
									技能::屏蔽鼠标();
									技能::写怪物坐标到鼠标(蝗虫.坐标);
									UI功能::内存按键(VK_F5);
									Sleep(500);
									UI功能::内存按键(VK_F5);
									技能::解除屏蔽鼠标();
								}
							}


						}

						return false;
					}
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}
		if (!任务::任务是否已完成(0xC48FB, vsk))
		{
			if (任务::是否已接任务(0xC48FB))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC48FB);
				if (支线任务.dState == 2)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}
		if (!任务::任务是否已完成(0xC48F3, vsk))
		{
			if (任务::是否已接任务(0xC48F3))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC48F3);
				if (支线任务.dState == 2)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}
	}
	if (任务::任务是否已完成(805004, vsk) || 任务::取出指定主线任务(805004).dStep >= 4)
	{
		if (!任务::任务是否已完成(0xC48FA, vsk))
		{
			MyTrace(L"执行支线 %x", 0xC48FA);
			if (!任务::是否已接任务(0xC48FA))
			{
				功能::到指定地点找NPC接任务2(14, 10813, 21062, 17353, 0, 0x2F14, 0xC48FA, 50);
				return false;
			}

		}
	}
	if (任务::任务是否已完成(805004, vsk) || 任务::取出指定主线任务(805004).dStep >= 5)
	{
		if (!任务::任务是否已完成(0xC48FA, vsk))
		{
			MyTrace(L"执行支线 %x", 0xC48FA);
			if (!任务::是否已接任务(0xC48FA))
			{
				功能::到指定地点找NPC接任务2(14, 10813, 21062, 17353, 0, 0x2F14, 0xC48FA, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC48FA);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点采集任务显示(14, 任务坐标.地图ID, 19280, 25207, -1024, 2000, 0x13A85);
						return false;
					}
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}


			}

		}
	}
	return true;
}
bool 游戏::支线_比尔布森林(vector<DWORD>& vsk)
{
	//if (任务::任务是否已完成(0xC3CD1, vsk) || 任务::取出指定主线任务(0xC3CD1).dStep >= 3) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	//{
	//	if (!任务::任务是否已完成(0xC3D36, vsk))
	//	{

	//	}
	//}
	if (任务::任务是否已完成(806002, vsk) || 任务::取出指定主线任务(806002).dStep >= 2)
	{
		if (!任务::任务是否已完成(0xC4CD8, vsk))
		{
			if (!任务::是否已接任务(0xC4CD8))
			{
				功能::到指定地点找NPC接任务2(14, 10814, 14710, 1101, 1536, 0x2F21, 0xC4CD8, 50);
				return false;
			}
		}
		if (!任务::任务是否已完成(0xC4CD7, vsk))
		{
			if (!任务::是否已接任务(0xC4CD7))
			{
				功能::到指定地点找NPC接任务2(14, 10814, 14510, 772, 1536, 0x2FCA, 0xC4CD7, 50);
				return false;
			}
		}
		if (!任务::任务是否已完成(0xC4CD8, vsk))
		{
			if (任务::是否已接任务(0xC4CD8))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC4CD8);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);

						功能::到指定地点采集(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 2000, 0x13AE5);
						return false;
					}
				}

			}
		}
		if (!任务::任务是否已完成(0xC4CD7, vsk))
		{
			if (任务::是否已接任务(0xC4CD7))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC4CD7);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						加入优先打怪ID(L"180640|180641");
						功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 300, 3000, 100);
						return false;
					}
				}

			}
		}
	}
	if (任务::任务是否已完成(806002, vsk) || 任务::取出指定主线任务(806002).dStep >= 3)
	{
		if (!任务::任务是否已完成(0xC4CD8, vsk))
		{
			if (任务::是否已接任务(0xC4CD8))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC4CD8);
				if (支线任务.dState == 2)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}
		if (!任务::任务是否已完成(0xC4CD7, vsk))
		{
			if (任务::是否已接任务(0xC4CD7))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC4CD7);
				if (支线任务.dState == 2)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}
	}
	if (任务::任务是否已完成(806003, vsk) || 任务::取出指定主线任务(806003).dStep >= 5)
	{
		if (!任务::任务是否已完成(0xC4CD9, vsk))
		{
			if (!任务::是否已接任务(0xC4CD9))
			{
				功能::到指定地点找NPC接任务2(14, 10814, 9268, 12774, 1024, 0x2F2B, 0xC4CD9, 50);
				return false;
			}
		}
		if (!任务::任务是否已完成(0xC4CDA, vsk))
		{
			if (!任务::是否已接任务(0xC4CDA))
			{
				功能::到指定地点找NPC接任务2(14, 10814, 9891, 13653, 1024, 0x2FCB, 0xC4CDA, 50);
				return false;
			}
		}
		if (!任务::任务是否已完成(0xC8B55, vsk))
		{
			if (!任务::是否已接任务(0xC8B55))
			{
				功能::到指定地点找NPC接任务2(14, 10814, 10716, 13402, 1024, 0x2F27, 0xC8B55, 50);
				return false;
			}
		}
		if (!任务::任务是否已完成(0xC4CD9, vsk))
		{
			if (任务::是否已接任务(0xC4CD9))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC4CD9);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点采集(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 2000, 0x13ADD, 200);
						return false;
					}
				}
			}
		}

		if (!任务::任务是否已完成(0xC4CDA, vsk))
		{
			if (任务::是否已接任务(0xC4CDA))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC4CDA);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点采集(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 2000, 0x13AE6, 200);
						return false;
					}
				}
			}
		}
		if (!任务::任务是否已完成(0xC8B55, vsk)) //悲鸣洞穴前置
		{
			if (任务::是否已接任务(0xC8B55))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC8B55);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务2(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
						return false;
					}
				}
				if (支线任务.dState == 2)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}
		if (!任务::任务是否已完成(0xC8B57, vsk))
		{
			if (!任务::是否已接任务(0xC8B57))
			{
				功能::到指定地点找NPC接任务2(14, 10814, 22478, -1569, 2046, 0x3762, 0xC8B57, 50);
				return false;
			}
		}
		if (!任务::任务是否已完成(0xC8B56, vsk))
		{
			if (!任务::是否已接任务(0xC8B56))
			{
				功能::到指定地点找NPC接任务2(14, 10814, 22478, -1569, 2046, 0x3762, 0xC8B56, 50);
				return false;
			}
		}
		if (!任务::任务是否已完成(0xC8B57, vsk)) //悲鸣洞穴前置
		{
			if (任务::是否已接任务(0xC8B57))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC8B57);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						if (地图::取地图ID() != 10855)
						{
							功能::寻路到副本(14, 10814, 22085, -2524, 2045);
							return false;
						}
					}
				}
				else
				{
					if (地图::取地图ID() != 10855)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务2(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
						return false;
					}
				}


			}
		}
		if (!任务::任务是否已完成(0xC8B56, vsk))
		{
			if (任务::是否已接任务(0xC8B56))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC8B56);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						if (地图::取地图ID() != 10855)
						{
							功能::寻路到副本(14, 10814, 22085, -2524, 2045);
							return false;
						}
					}
				}
				else
				{
					if (地图::取地图ID() != 10855)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务2(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
						return false;
					}
				}


			}
		}
	}
	if (任务::任务是否已完成(806004, vsk) || 任务::取出指定主线任务(806004).dStep >= 2)
	{
		if (!任务::任务是否已完成(0xC4CD9, vsk))
		{
			if (任务::是否已接任务(0xC4CD9))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC4CD9);
				if (支线任务.dState == 2)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}
		if (!任务::任务是否已完成(0xC4CDA, vsk))
		{
			if (任务::是否已接任务(0xC4CDA))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC4CDA);
				if (支线任务.dState == 2)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}

	}

	if (任务::任务是否已完成(822001, vsk) || 任务::取出指定主线任务(822001).dStep >= 8)
	{
		if (!任务::任务是否已完成(0xC8B57, vsk)) //悲鸣洞穴前置
		{
			if (任务::是否已接任务(0xC8B57))//消灭奥贝里斯克
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC8B57);
				if (支线任务.dStep == 1)
				{
					if (支线任务.dState == 1)
					{
						if (地图::取地图ID() == 10855)
						{
							objInfo_ 目标 = 环境::取指定对象信息(81006);
							if (目标.dResId == 81006)
							{
								//坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
								加入优先打怪ID(L"81009|81006|181074|181073");
								暂时不打ID.clear();
								功能::移动打怪(目标.坐标.x, 目标.坐标.y, 目标.坐标.z, 50, 3000, 150);
								return false;
							}
						}
					}

				}


			}
		}
		if (!任务::任务是否已完成(0xC8B56, vsk))
		{
			if (任务::是否已接任务(0xC8B56))//解救奴隶
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC8B56);
				if (支线任务.dStep == 1)
				{
					if (支线任务.dState == 1)
					{
						if (地图::取地图ID() == 10855)
						{
							objInfo_ 目标 = 环境::取指定对象信息(81009);
							if (目标.dResId == 81009)
							{
								//坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
								加入优先打怪ID(L"81009|81006|181074|181073");
								暂时不打ID.clear();
								功能::移动打怪(目标.坐标.x, 目标.坐标.y, 目标.坐标.z, 50, 3000, 150);
								return false;
							}
						}
					}
				}

			}
		}

	}
	if (任务::任务是否已完成(806007, vsk) || 任务::取出指定主线任务(806007).dStep >= 3)
	{
		if (!任务::任务是否已完成(0xC4CDD, vsk))
		{
			if (!任务::是否已接任务(0xC4CDD))
			{
				功能::到指定地点找NPC接任务2(14, 10814, 17022, 22144, 1541, 0x2F2E, 0xC4CDD, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC4CDD);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点采集(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 3000, 支线任务.TargetId, 100, 200);
						return false;
					}
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}

	}
	/*if (任务::任务是否已完成(822001, vsk))
	{
		MyTrace(L"822001 已完成");
		if (地图::取地图ID() == 10855)
		{
			本人::CALL_演奏乐谱(1);
			return false;
		}
	}*/

	return true;
}
bool 游戏::支线_激战平原(vector<DWORD>& vsk)
{
	//if (任务::任务是否已完成(0xC3CD1, vsk) || 任务::取出指定主线任务(0xC3CD1).dStep >= 3) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	//{
	//	if (!任务::任务是否已完成(0xC3D36, vsk))
	//	{

	//	}
	//}
	return true;
}
bool 游戏::支线_卢特兰城(vector<DWORD>& vsk)
{
	if (任务::任务是否已完成(801002, vsk) || 任务::取出指定主线任务(801002).dStep >= 2) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(0x41A0CF, vsk))
		{
			QuestInfo_ 支线任务 = 任务::取出指定支线任务(0x41A0CF);
			if (支线任务.dState == 1)
			{
				if (支线任务.dStep == 1)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 支线任务.TargetId, 支线任务.dQuestId, -1, 25, 支线任务.dStep);
					return false;
				}
				if (支线任务.dStep == 2)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 支线任务.TargetId, 支线任务.dQuestId, -1, 25, 支线任务.dStep);
					return false;
				}
			}

		}
		if (!任务::任务是否已完成(0x41A0C8, vsk))
		{
			QuestInfo_ 支线任务 = 任务::取出指定支线任务(0x41A0C8);
			if (支线任务.dState == 1)
			{
				if (支线任务.dStep == 1)
				{
					本人::CALL_演奏乐谱(15);
					Sleep(10000);
					return false;
				}
			}
		}
		if (!任务::任务是否已完成(0x41A0C9, vsk))
		{
			QuestInfo_ 支线任务 = 任务::取出指定支线任务(0x41A0C9);
			if (支线任务.dState == 1)
			{
				if (支线任务.dStep == 1)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务3(0, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 支线任务.TargetId, 支线任务.dQuestId, -1, 25, 支线任务.dStep);
					return false;
				}
				if (支线任务.dStep == 2)
				{
					if (支线任务.子任务进度.size() == 3)
					{
						if (支线任务.子任务进度[0].dCur == 0)
						{
							坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
							功能::到指定地点找NPC交任务3(0, 任务坐标.地图ID, 10529, 4145, 1072.19, 支线任务.子任务进度[0].TargetID, 支线任务.dQuestId, -1, 25, 支线任务.dStep);
							return false;
						}
						if (支线任务.子任务进度[1].dCur == 0)
						{
							坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
							功能::到指定地点找NPC交任务3(0, 任务坐标.地图ID, 10373, 4154, 1072.19, 支线任务.子任务进度[1].TargetID, 支线任务.dQuestId, -1, 25, 支线任务.dStep);
							return false;
						}
						if (支线任务.子任务进度[2].dCur == 0)
						{
							坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
							功能::到指定地点找NPC交任务3(0, 任务坐标.地图ID, 10625, 4009, 1072.19, 支线任务.子任务进度[2].TargetID, 支线任务.dQuestId, -1, 25, 支线任务.dStep);
							return false;
						}
					}
				}
				if (支线任务.dStep == 3)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务3(0, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 支线任务.TargetId, 支线任务.dQuestId, -1, 25, 支线任务.dStep);
					return false;
				}
				if (支线任务.dStep == 4)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点(0, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
					return false;
				}
				if (支线任务.dStep == 5)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务3(0, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 支线任务.TargetId, 支线任务.dQuestId, -1, 25, 支线任务.dStep);
					return false;
				}
			}
			else
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
				功能::到指定地点找NPC交任务3(0, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 支线任务.TargetId, 支线任务.dQuestId, -1, 25, 支线任务.dStep);
				return false;
			}
		}
		if (!任务::任务是否已完成(0x41A0D0, vsk))
		{
			QuestInfo_ 支线任务 = 任务::取出指定支线任务(0x41A0D0);
			if (支线任务.dState == 1)
			{
				if (支线任务.dStep == 1)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务3(0, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 支线任务.TargetId, 支线任务.dQuestId, -1, 25, 支线任务.dStep);
					return false;
				}
				if (支线任务.dStep == 2)
				{
					Sleep(5000);
					return false;
				}
				if (支线任务.dStep == 3)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					if (功能::到指定地点(0, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 100))
					{
						本人::CALL_做社交动作(0xF246);
						Sleep(7000);
					}

					return false;
				}
				if (支线任务.dStep == 4)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务3(0, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 支线任务.TargetId, 支线任务.dQuestId, -1, 25, 支线任务.dStep);
					return false;
				}
				if (支线任务.dStep == 5)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务3(0, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 支线任务.TargetId, 支线任务.dQuestId, -1, 25, 支线任务.dStep);
					return false;
				}
				if (支线任务.dStep == 6)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点(0, 任务坐标.地图ID, 12331, 3568, 1320, 25);
					return false;
				}
				if (支线任务.dStep == 7)
				{
					坐标_ 角色坐标 = 本人::取坐标();
					if (角色坐标.z < 2000)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点(0, 任务坐标.地图ID, 12331, 3568, 1320, 25);
						return false;
					}
					else
					{
						UI功能::内存按键(DWORD('G'));
						return false;
					}

				}
			}
		}
		if (!任务::任务是否已完成(0x41A0CA, vsk))
		{
			QuestInfo_ 支线任务 = 任务::取出指定支线任务(0x41A0CA);
			if (支线任务.dState == 1)
			{
				if (支线任务.dStep == 1)
				{
					坐标_ 角色坐标 = 本人::取坐标();
					if (角色坐标.z > 2000)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点(0, 任务坐标.地图ID, 12703, 3407, 2147, 0);
						return false;
					}
					else
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务3(0, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 支线任务.TargetId, 支线任务.dQuestId, -1, 25, 支线任务.dStep);
						return false;
					}
				}
				if (支线任务.dStep == 2)
				{
					UI功能::内存按键(VK_F5);
					Sleep(3000);
					return false;
				}
				if (支线任务.dStep == 3)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务3(0, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 支线任务.TargetId, 支线任务.dQuestId, -1, 25, 支线任务.dStep);
					return false;
				}
				if (支线任务.dStep == 4)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点(0, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0);
					return false;
				}
				if (支线任务.dStep == 5)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务3(0, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 支线任务.TargetId, 支线任务.dQuestId, -1, 25, 支线任务.dStep);
					return false;
				}
				if (支线任务.dStep == 6) //ctrl+1 领地研究
				{

				}
			}
		}
	}
	if (任务::任务是否已完成(801002, vsk) || 任务::取出指定主线任务(801006).dStep >= 1) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(801105, vsk))
		{
			if (!任务::是否已接任务(801105))
			{
				功能::到指定地点找NPC接任务2(15, 10801, 9539, 5369, 992, 0x32CA, 801105, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(801105);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						if (支线任务.子任务进度.size() == 4)
						{
							if (支线任务.子任务进度[0].dCur == 0)
							{
								坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
								功能::到指定地点采集(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 3000, 支线任务.子任务进度[0].TargetID, 100, 200);
								return false;
							}
							if (支线任务.子任务进度[1].dCur == 0)
							{
								坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
								功能::到指定地点采集(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 3000, 支线任务.子任务进度[1].TargetID, 100, 200);
								return false;
							}
							if (支线任务.子任务进度[2].dCur == 0)
							{
								坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
								功能::到指定地点采集(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 3000, 支线任务.子任务进度[2].TargetID, 100, 200);
								return false;
							}
							if (支线任务.子任务进度[3].dCur == 0)
							{
								坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
								功能::到指定地点采集(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 3000, 支线任务.子任务进度[3].TargetID, 100, 200);
								return false;
							}
						}

					}
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}
		if (!任务::任务是否已完成(801102, vsk))
		{
			if (!任务::是否已接任务(801102))
			{
				功能::到指定地点找NPC接任务2(15, 10801, 7882, 4150, 1027, 0x3342, 801102, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(801102);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						if (功能::到指定地点(0, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 100))
						{
							本人::CALL_做社交动作(0xF23E);
							Sleep(7000);

						}
						return false;
					}
					if (支线任务.dStep == 2)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
						return false;
					}
					if (支线任务.dStep == 3)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
						return false;
					}
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}
		if (!任务::任务是否已完成(801120, vsk))
		{
			if (!任务::是否已接任务(801120))
			{
				功能::到指定地点找NPC接任务2(15, 10801, 4247, 4168, 384, 0x32CE, 801120, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(801120);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
						return false;
					}

				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}
		if (!任务::任务是否已完成(801121, vsk))
		{
			if (!任务::是否已接任务(801121))
			{
				功能::到指定地点找NPC接任务2(15, 10801, 4127, 4740, 454, 0x3319, 801121, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(801121);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
						return false;
					}
					if (支线任务.dStep == 2)
					{
						if (背包::返回指定物品数量(0x77A11) == 0)
						{
							坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
							功能::到指定地点找NPC买物品(15, 任务坐标.地图ID, 5127, 4323, 448, 0x3775, 50, 0x77A11, 1);
							return false;
						}
						else
						{
							坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
							功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 4166, 4845, 448, 0x3323, 支线任务.dQuestId, -1, 25, 支线任务.dStep);
							return false;
						}

					}
					if (支线任务.dStep == 3)
					{
						if (背包::返回指定物品数量(0x77A11) == 0)
						{
							坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
							功能::到指定地点找NPC买物品(15, 任务坐标.地图ID, 5127, 4323, 448, 0x3775, 50, 0x77A11, 1);
							return false;
						}
						else
						{
							背包::使用背包指定物品_ByResId(0x77A11);
							Sleep(1000);
							return false;

						}
					}

				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}
	}

	if (任务::任务是否已完成(801005, vsk) || 任务::取出指定主线任务(801005).dStep >= 6) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(801107, vsk))
		{
			if (!任务::是否已接任务(801107))
			{
				功能::到指定地点找NPC接任务2(15, 10801, 12810, -6197, 1024, 0x32CC, 801107, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(801107);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点按G(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 100);
						return false;
					}
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}
	}
	if (任务::任务是否已完成(801005, vsk) || 任务::取出指定主线任务(801005).dStep >= 8) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(801108, vsk))
		{
			if (!任务::是否已接任务(801108))
			{
				功能::到指定地点找NPC接任务2(15, 10801, 15281, 284, -23551, 0x3301, 801108, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(801108);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
						return false;
					}
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}
	}
	return true;
}
bool 游戏::支线_迪奥利卡平原(vector<DWORD>& vsk)
{
	if (任务::任务是否已完成(809001, vsk) || 任务::取出指定主线任务(809001).dStep >= 1) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(0xC588D, vsk))
		{
			if (!任务::是否已接任务(0xC588D))
			{
				功能::到指定地点找NPC接任务2(15, 10816, 16082, 2212, 1536, 0x36BF, 0xC588D, 50);
				return false;
			}
		}
		if (!任务::任务是否已完成(0xC58A2, vsk))
		{
			if (!任务::是否已接任务(0xC58A2))
			{
				功能::到指定地点找NPC接任务2(15, 10816, 16421, 1705, 1536, 0x3779, 0xC58A2, 50);
				return false;
			}
		}
		if (!任务::任务是否已完成(0xC588D, vsk))
		{
			if (任务::是否已接任务(0xC588D))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC588D);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
						return false;
					}
					if (支线任务.dStep == 2)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
						return false;

					}
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}

			}
		}
		if (!任务::任务是否已完成(0xC58A2, vsk))
		{
			if (任务::是否已接任务(0xC58A2))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC58A2);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						加入优先打怪ID(L"82117");
						功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 3000, 150);
						return false;
					}
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}
	}
	if (任务::任务是否已完成(809001, vsk) || 任务::取出指定主线任务(809002).dStep >= 1) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(0xC5893, vsk))
		{
			if (!任务::是否已接任务(0xC5893))
			{
				功能::到指定地点找NPC接任务2(15, 10816, 17880, 7712, 1541, 0x36BA, 0xC5893, 50);
				return false;
			}
		}
		if (!任务::任务是否已完成(0xC5891, vsk))
		{
			if (!任务::是否已接任务(0xC5891))
			{
				功能::到指定地点找NPC接任务2(15, 10816, 17321, 8071, 1538, 0x36C6, 0xC5891, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC5891);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						ActorInfo_ 角色信息 = 本人::取角色信息();
						if (角色信息.举起状态 == 1)
						{
							功能::到指定地点采集任务显示(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 3000, 0x140C3, 100, 150);
							return false;
						}
						else
						{
							if (功能::到指定地点(15, 任务坐标.地图ID, 12671, 8086, 1317, 50))
							{
								UI功能::内存按键('R');
							}
							return false;
						}

					}

				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}
	}
	if (任务::任务是否已完成(809002, vsk)) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(0xC5893, vsk))
		{
			if (!任务::是否已接任务(0xC5893))
			{
				功能::到指定地点找NPC接任务2(15, 10816, 17880, 7712, 1541, 0x36BA, 0xC5893, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC5893);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
						return false;

					}

				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0x36BC, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}

	}
	if (任务::任务是否已完成(809003, vsk) || 任务::取出指定主线任务(809003).dStep >= 1) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(0xC5894, vsk))
		{
			if (!任务::是否已接任务(0xC5894))
			{
				功能::到指定地点找NPC接任务2(15, 10816, 14275, 16270, 1536, 0x36BC, 0xC5894, 50);
				return false;
			}

		}

	}
	if (任务::任务是否已完成(809003, vsk) || 任务::取出指定主线任务(809003).dStep >= 3) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(0xC5894, vsk))
		{
			if (任务::是否已接任务(0xC5894))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC5894);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
						return false;

					}
					if (支线任务.dStep == 2)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点按G(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 150);
						return false;

					}

				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}
	}
	if (任务::任务是否已完成(809003, vsk) || 任务::取出指定主线任务(809003).dState == 2) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(0xC5896, vsk))
		{
			if (!任务::是否已接任务(0xC5896))
			{
				功能::到指定地点找NPC接任务2(15, 10816, -484, 9818, 1396, 0x36E5, 0xC5896, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC5896);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点采集(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 1500, 0x140DF, 100, 100);
						return false;

					}



				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}
	}
	if (任务::任务是否已完成(809003, vsk)) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(0xC5899, vsk))
		{
			if (!任务::是否已接任务(0xC5899))
			{
				功能::到指定地点找NPC接任务2(15, 10816, -459, 7248, 1536, 0x3771, 0xC5899, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC5899);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						加入优先打怪ID(L"182220");
						功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 500, 3000);
						return false;

					}



				}
				/*else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}*/
			}
		}
	}
	if (任务::任务是否已完成(809004, vsk) || 任务::取出指定主线任务(809004).dStep >= 2) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(0xC5899, vsk))
		{
			if (任务::是否已接任务(0xC5899))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC5899);
				if (支线任务.dState == 2)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}
	}
	if (任务::任务是否已完成(809004, vsk) || 任务::取出指定主线任务(809004).dStep >= 3) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(0xC588E, vsk))
		{
			if (!任务::是否已接任务(0xC588E))
			{
				功能::到指定地点找NPC接任务2(15, 10816, 13358, 2695, 1536, 0x36C0, 0xC588E, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC588E);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
						return false;

					}



				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}
		if (!任务::任务是否已完成(0xC58A6, vsk))
		{
			if (!任务::是否已接任务(0xC58A6))
			{
				功能::到指定地点找NPC接任务2(15, 10816, 17321, 8071, 1538, 0x36C6, 0xC58A6, 50);
				return false;
			}

		}

	}
	if (任务::任务是否已完成(809004, vsk)) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(0xC5895, vsk))
		{
			if (!任务::是否已接任务(0xC5895))
			{
				功能::到指定地点找NPC接任务2(15, 10816, 17880, 7712, 1541, 0x36BA, 0xC5895, 50);
				return false;
			}


		}
		if (!任务::任务是否已完成(0xC58A6, vsk))
		{
			if (任务::是否已接任务(0xC58A6))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC58A6);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						加入优先打怪ID(L"182041");
						if (功能::移动打怪(19886, 7127, 1535, 500, 1000))
						{
							功能::到指定地点打开NPC(15, 10816, 19886, 7127, 1535, 50, 0x3789);
						}
						return false;

					}
					if (支线任务.dStep == 2)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
						return false;

					}
					if (支线任务.dStep == 3)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
						return false;

					}
					if (支线任务.dStep == 4)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
						return false;

					}
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}

		}

	}
	if (任务::任务是否已完成(809005, vsk) || 任务::取出指定主线任务(809005).dStep >= 2) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(0xC5895, vsk))
		{
			if (任务::是否已接任务(0xC5895))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC5895);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点按G(15, 任务坐标.地图ID, 16684, 9541, 1536, 50);
						return false;
					}
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}

	}
	if (任务::任务是否已完成(809008, vsk) || 任务::取出指定主线任务(809008).dStep >= 2) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(0xC3956, vsk))
		{
			if (任务::是否已接任务(0xC3956))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC3956);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
						return false;
					}
					if (支线任务.dStep == 2)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点按G(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 150);
						return false;
					}
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 5869, -4588, -23535, 0x32E3, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
			else
			{
				功能::到指定地点找NPC接任务2(15, 10801, 5869, -4588, -23535, 0x32E3, 0xC3956, 50);
				return false;
			}
		}

	}
	if (任务::任务是否已完成(809008, vsk)) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(0xC58A1, vsk))
		{
			if (!任务::是否已接任务(0xC58A1))
			{
				功能::到指定地点找NPC接任务2(15, 10816, 1599, 12583, 1536, 0x36BE, 0xC58A1, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC58A1);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
						return false;
					}
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}

	}
	return true;
}
bool 游戏::支线_圆虹之丘(vector<DWORD>& vsk)
{
	if (任务::任务是否已完成(810001, vsk) || 任务::取出指定主线任务(810001).dStep >= 3) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(0xC5C75, vsk))
		{
			if (任务::是否已接任务(0xC5C75))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC5C75);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						加入优先打怪ID(L"182300");
						功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 500, 3000);
						return false;
					}

				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
			else
			{
				功能::到指定地点找NPC接任务2(15, 10817, -24863, -14612, 1238, 0x3705, 0xC5C75, 50);
				return false;
			}
		}

	}
	if (任务::任务是否已完成(810001, vsk)) //
	{
		if (!任务::任务是否已完成(0xC5C7C, vsk))//卢特兰的传说
		{
			if (任务::是否已接任务(0xC5C7C))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC5C7C);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点按G(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 150);
						return false;
					}
					if (支线任务.dStep == 2)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点按G(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 150);
						return false;
					}
				}

			}
			else
			{
				功能::到指定地点找NPC接任务2(15, 10817, -24635, -16533, 1024, 0x3702, 0xC5C7C, 50);
				return false;
			}
		}

	}
	if (任务::任务是否已完成(810008, vsk) || 任务::取出指定主线任务(810008).dStep >= 2) //卢特兰的传说
	{
		if (!任务::任务是否已完成(0xC5C7B, vsk))//卢特兰的传说
		{
			if (任务::是否已接任务(0xC5C7B))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC5C7B);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						ActorInfo_ 角色信息 = 本人::取角色信息();
						if (角色信息.举起状态 == 1)
						{
							功能::到指定地点采集(15, 任务坐标.地图ID, -18130, -15833, 768, 1000, 0x1412D);
							return false;
						}
						else
						{
							if (功能::到指定地点(15, 任务坐标.地图ID, -17258, -15221, 768, 50))
							{
								UI功能::内存按键('R');
							}
							return false;
						}

					}
					if (支线任务.dStep == 2)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点采集任务显示(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 1000, 0x1412F);
						return false;
					}
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}

			}
			else
			{
				功能::到指定地点找NPC接任务2(15, 10817, -17300, -15027, 773, 0x3700, 0xC5C7B, 50);
				return false;
			}
		}
		if (!任务::任务是否已完成(0xC5C79, vsk))//卢特兰的传说
		{
			if (!任务::是否已接任务(0xC5C79))
			{
				功能::到指定地点找NPC接任务2(15, 10817, -17300, -15027, 773, 0x3700, 0xC5C79, 50);
				return false;
			}
		}
	}
	if (任务::任务是否已完成(810002, vsk) || 任务::取出指定主线任务(810002).dStep >= 2) //卢特兰的传说
	{
		if (!任务::任务是否已完成(0xC5C79, vsk))//卢特兰的传说
		{
			if (任务::是否已接任务(0xC5C79))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC5C79);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点采集任务显示(15, 任务坐标.地图ID, -16731, -23859, 768, 1000, 0x14128);
						return false;
					}
				}
				else
				{
					QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC5C79);
					if (支线任务.dState == 2)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
						return false;
					}
				}
			}
		}
		if (!任务::任务是否已完成(0xC5C7D, vsk))//该回家了  
		{
			if (任务::是否已接任务(0xC5C7D))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC5C7D);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
						return false;
					}
				}

			}
			else
			{
				功能::到指定地点找NPC接任务2(15, 10817, -15763, -22616, 768, 0x36FF, 0xC5C7D, 50);
				return false;
			}
		}

	}
	if (任务::任务是否已完成(810002, vsk) || 任务::取出指定主线任务(810002).dStep >= 3) //卢特兰的传说
	{

		if (!任务::任务是否已完成(0xC5C7D, vsk))
		{
			if (任务::是否已接任务(0xC5C7D))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC5C7D);
				if (支线任务.dState == 2)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}

			}
		}
		if (!任务::任务是否已完成(0xC5C7C, vsk))
		{
			if (任务::是否已接任务(0xC5C7C))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC5C7C);
				if (支线任务.dState == 2)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0x3704, 支线任务.dQuestId, -1, 25, 支线任务.dStep);
					return false;
				}

			}
		}
	}
	if (任务::任务是否已完成(810004, vsk) || 任务::取出指定主线任务(810004).dStep >= 3)
	{
		if (!任务::任务是否已完成(0xC5C81, vsk))///看不见的吟游诗人
		{
			if (任务::是否已接任务(0xC5C81))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC5C81);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
						return false;

					}
					if (支线任务.dStep == 2)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						if (功能::到指定地点(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50))
						{
							本人::CALL_做社交动作(0xF23F);
							Sleep(10000);
						}

						return false;
					}
					if (支线任务.dStep == 3)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 支线任务.TargetId, 支线任务.dQuestId, -1, 25, 支线任务.dStep);
						return false;

					}
				}
				else
				{

					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;

				}
			}
			else
			{
				功能::到指定地点找NPC接任务2(15, 10817, -6112, -13965, 1152, 0x36F1, 0xC5C81, 50);
				return false;
			}
		}
	}
	if (任务::任务是否已完成(810007, vsk) || 任务::取出指定主线任务(810007).dStep >= 3)
	{
		if (!任务::任务是否已完成(0xC5C82, vsk))///看不见的吟游诗人
		{
			if (任务::是否已接任务(0xC5C82))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC5C82);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点采集任务显示(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 2000, 0x1415F, 150, 100);
						return false;

					}
					if (支线任务.dStep == 2)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点按G(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 150);
						return false;

					}
				}
				else
				{

					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;

				}
			}
			else
			{
				功能::到指定地点找NPC接任务2(15, 10817, -15822, -6972, 768, 0x3703, 0xC5C82, 50);
				return false;
			}
		}
	}
	return true;
}
bool 游戏::支线_梨树栖息地(vector<DWORD>& vsk)
{
	if (任务::任务是否已完成(812004, vsk) || 任务::取出指定主线任务(812004).dStep >= 1) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (地图::取地图ID() == 10832)
		{
			功能::到指定地点(15, 10832, 13397, -17952, 1825, 50);
			return false;
		}
		else
		{

			if (!任务::任务是否已完成(0xC644A, vsk))
			{
				if (!任务::是否已接任务(0xC644A))
				{
					功能::到指定地点找NPC接任务2(15, 10818, -15081, -20421, 1024, 0x3744, 0xC644A, 50);
					return false;
				}
				else
				{
					QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC644A);
					if (支线任务.dState == 1)
					{
						if (支线任务.dStep == 1)
						{
							坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
							功能::到指定地点采集任务显示(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 1000, 0x1418E);
							return false;
						}
					}
					else
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
						return false;
					}
				}
			}
			if (!任务::任务是否已完成(0xC644B, vsk))
			{
				if (!任务::是否已接任务(0xC644B))
				{
					功能::到指定地点找NPC接任务2(15, 10818, -14259, -21769, 1024, 0x3815, 0xC644B, 50);
					return false;
				}
				else
				{
					QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC644B);
					if (支线任务.dState == 1)
					{
						if (支线任务.dStep == 1)
						{
							坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
							功能::到指定地点采集任务显示(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 1000, 0x14195);
							return false;
						}
					}
					else
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
						return false;
					}
				}
			}

		}
	}
	if (任务::任务是否已完成(812004, vsk) || 任务::取出指定主线任务(812004).dStep >= 4) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(0xC644C, vsk))
		{
			if (!任务::是否已接任务(0xC644C))
			{
				功能::到指定地点找NPC接任务2(15, 10818, -10968, -27678, 749, 0x3750, 0xC644C, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC644C);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 200, 1000);
						return false;
					}
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}
	}
	if (任务::任务是否已完成(812005, vsk)) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(0xC644E, vsk))
		{
			if (!任务::是否已接任务(0xC644E))
			{
				功能::到指定地点找NPC接任务2(15, 10818, -21880, -17248, 1020, 0x374B, 0xC644E, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC644E);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						if (支线任务.子任务进度.size() == 2)
						{
							if (支线任务.子任务进度[0].dCur < 支线任务.子任务进度[0].dNeed)//14184
							{
								坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
								加入优先打怪ID(L"183100");
								功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 200, 2000);
								return false;
							}
							if (支线任务.子任务进度[1].dCur < 支线任务.子任务进度[1].dNeed)//14184
							{
								坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
								功能::到指定地点采集任务显示(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 2000, 0x14184, 200);
								return false;
							}
						}

					}
					if (支线任务.dStep == 2)
					{
						if (支线任务.子任务进度.size() == 2)
						{

							if (支线任务.子任务进度[1].dCur < 支线任务.子任务进度[1].dNeed)//14184
							{
								坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
								加入优先打怪ID(L"183130|183140");
								功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 200, 2000);
								return false;
							}
							if (支线任务.子任务进度[0].dCur < 支线任务.子任务进度[0].dNeed)//14184
							{
								坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
								功能::到指定地点采集任务显示(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 2000, 0x14185, 200);
								return false;

							}
						}

					}
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}
	}
	if (任务::任务是否已完成(812006, vsk) || 任务::取出指定主线任务(812006).dStep >= 3) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(0xC644F, vsk))
		{
			if (!任务::是否已接任务(0xC644F))
			{
				功能::到指定地点找NPC接任务2(15, 10818, -23150, -9593, 768, 0x3746, 0xC644F, 50);
				return false;
			}

		}
	}
	if (任务::任务是否已完成(812006, vsk) || 任务::取出指定主线任务(812006).dStep >= 4) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(0xC644F, vsk))
		{
			if (!任务::是否已接任务(0xC644F))
			{
				功能::到指定地点找NPC接任务2(15, 10818, -23150, -9593, 768, 0x3746, 0xC644F, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC644F);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点按G(15, 10818, 任务坐标.x, 任务坐标.y, 任务坐标.z, 200);
						return false;
					}
				}

			}
		}
	}
	if (任务::任务是否已完成(812006, vsk) || 任务::取出指定主线任务(812006).dStep >= 5) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(0xC644F, vsk))
		{
			if (任务::是否已接任务(0xC644F))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC644F);
				if (支线任务.dState == 2)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}

		}
	}
	if (任务::任务是否已完成(812006, vsk)) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(0xC6450, vsk))
		{
			if (!任务::是否已接任务(0xC6450))
			{
				功能::到指定地点找NPC接任务2(15, 10818, -17194, -2472, 1024, 0x3753, 0xC6450, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC6450);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
						return false;
					}

				}
			}
		}
		if (!任务::任务是否已完成(0xC6451, vsk))
		{
			if (!任务::是否已接任务(0xC6451))
			{
				功能::到指定地点找NPC接任务2(15, 10818, -16245, -2592, 1024, 0x378D, 0xC6451, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC6451);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
						return false;
					}
				}
			}
		}
	}
	if (任务::任务是否已完成(812007, vsk) || 任务::取出指定主线任务(812007).dStep >= 2) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(0xC6450, vsk))
		{
			if (任务::是否已接任务(0xC6450))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC6450);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 2)
					{
						if (支线任务.子任务进度[0].dCur == 0)
						{
							坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
							功能::到指定地点按G(15, 任务坐标.地图ID, -13203, -4776, 1023, 50, 200);
							return false;
						}
						if (支线任务.子任务进度[0].dCur == 1)
						{
							坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
							功能::到指定地点按G(15, 任务坐标.地图ID, -14138, -4113, 1026, 50, 200);
							return false;
						}
					}


				}
			}
		}
		if (!任务::任务是否已完成(0xC6451, vsk))
		{
			if (任务::是否已接任务(0xC6451))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC6451);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 2)
					{
						if (支线任务.子任务进度.size() == 4)
						{
							if (支线任务.子任务进度[0].dCur == 0)
							{
								坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
								功能::移动打怪(-7408, -7932, 1024, 100, 500);
								return false;

							}
							if (支线任务.子任务进度[1].dCur == 0)
							{
								坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
								功能::移动打怪(-9959, -9360, 1024, 100, 500);
								return false;
							}
							if (支线任务.子任务进度[2].dCur == 0 || 支线任务.子任务进度[3].dCur == 0)
							{
								坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
								功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 200, 2000);
								return false;
							}
						}

					}
					if (支线任务.dStep == 3)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
						return false;
					}
					if (支线任务.dStep == 4)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
						return false;
					}
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}

		if (!任务::任务是否已完成(0xC6450, vsk))
		{
			if (任务::是否已接任务(0xC6450))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC6450);
				if (支线任务.dState == 2)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}

		}
		if (!任务::任务是否已完成(0xC6452, vsk))
		{
			if (!任务::是否已接任务(0xC6452))
			{
				功能::到指定地点找NPC接任务2(15, 10818, -13574, -8765, 772, 0x374D, 0xC6452, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC6452);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
						return false;
					}
					if (支线任务.dStep == 2)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点采集任务显示(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 1000, 0x14190, 550);
						return false;
					}
					if (支线任务.dStep == 3)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点采集任务显示(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 1000, 0x14191, 550);
						return false;
					}
					if (支线任务.dStep == 4)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点采集任务显示(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 1000, 0x14187, 550);
						return false;
					}
					if (支线任务.dStep == 5)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点按G(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 550);
						return false;
					}
				}
				else
				{
					任务::CALL_交任务(0xC6452, -1);
					return false;
				}
			}
		}
	}
	if (任务::任务是否已完成(812008, vsk) || 任务::取出指定主线任务(812008).dStep >= 3) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(0xC6455, vsk))
		{
			if (!任务::是否已接任务(0xC6455))
			{
				功能::到指定地点找NPC接任务2(15, 10818, -1849, -10412, 1024, 0x375E, 0xC6455, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC6455);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						加入优先打怪ID(L"183080");
						功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 200, 1000);
						return false;
					}
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}
		if (!任务::任务是否已完成(0xC6456, vsk))
		{
			if (!任务::是否已接任务(0xC6456))
			{
				功能::到指定地点找NPC接任务2(15, 10818, -1849, -10412, 1024, 0x375E, 0xC6456, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC6456);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						UI功能::内存按键(VK_F5);
						Sleep(1000);
						return false;
					}
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}
		if (!任务::任务是否已完成(0xC6457, vsk))
		{
			if (!任务::是否已接任务(0xC6457))
			{
				功能::到指定地点找NPC接任务2(15, 10818, -1849, -10412, 1024, 0x375E, 0xC6457, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC6457);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						ActorInfo_ 角色信息 = 本人::取角色信息();
						if (技能::get_SkillShortCurPage() != 7)
						{
							UI功能::内存按键(VK_F5);
						}
						else
						{
							坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
							功能::到指定地点按G(15, 任务坐标.地图ID, -3654, -15440, 1024, 100);
						}



						//Sleep(1000);
						return false;
					}
					if (支线任务.dStep == 2)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点按G_无打怪(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 100);


						//Sleep(1000);
						return false;
					}
					if (支线任务.dStep == 3)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						if (支线任务.子任务进度[0].dCur == 0)
						{
							功能::到指定地点采集任务显示(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 1000, 0x1419C, 0, 100, true);
						}
						if (支线任务.子任务进度[0].dCur == 1)
						{
							功能::到指定地点采集任务显示(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 1000, 0x1419D, 0, 100, true);
						}
						if (支线任务.子任务进度[0].dCur == 2)
						{
							功能::到指定地点采集任务显示(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 1000, 0x1419E, 0, 100, true);
						}

						//Sleep(1000);
						return false;
					}
					if (支线任务.dStep == 4)
					{

						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点按G_无打怪(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 100);


						//Sleep(1000);
						return false;
					}
				}
				else
				{
					if (支线任务.dState == 2)
					{
						if (UI功能::商店是否打开() == true)
						{
							环境::CALL_退出NPC();
							Sleep(1000);
						}
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
						return false;
					}
					if (支线任务.dState == 4)//放弃任务
					{
						/*任务::CALL_交任务();
						return false;*/
					}
				}
			}
		}
		if (!任务::任务是否已完成(0xC6458, vsk))
		{
			if (!任务::是否已接任务(0xC6458))
			{
				功能::到指定地点找NPC接任务2(15, 10818, -1849, -10412, 1024, 0x375E, 0xC6458, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC6458);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						ActorInfo_ 角色信息 = 本人::取角色信息();
						if (角色信息.举起状态 == 1)
						{
							UI功能::内存按键(VK_F5);
						}
						else
						{
							UI功能::内存按键('R');

						}
						return false;

					}
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}
	}

	return true;
}
bool 游戏::支线_黑玫瑰教堂(vector<DWORD>& vsk)
{
	if (任务::任务是否已完成(813001, vsk) || 任务::取出指定主线任务(813001).dStep >= 5) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(0xC682E, vsk))
		{
			if (!任务::是否已接任务(0xC682E))
			{
				功能::到指定地点找NPC接任务2(15, 10819, 7199, 12480, 512, 0x3797, 0xC682E, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC682E);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						ActorInfo_ 角色信息 = 本人::取角色信息();
						if (角色信息.坐标.z <= 550)
						{
							坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);

							功能::到指定地点按G(15, 任务坐标.地图ID, 6914, 12714, 512, 50);
						}
						else
						{
							坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);

							功能::到指定地点按G(15, 任务坐标.地图ID, 7168, 12714, 1025, 25);
						}

						return false;
					}
					if (支线任务.dStep == 2)
					{
						ActorInfo_ 角色信息 = 本人::取角色信息();
						if (角色信息.坐标.z >= 1000)
						{
							坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);

							功能::到指定地点按G(15, 任务坐标.地图ID, 6973, 12736, 1044, 50);
						}
						else
						{
							坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);

							功能::到指定地点按G(15, 任务坐标.地图ID, 6775, 12702, 512, 25);
						}

						return false;
					}

				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}
		if (!任务::任务是否已完成(0xC682D, vsk))
		{
			if (!任务::是否已接任务(0xC682D))
			{
				功能::到指定地点找NPC接任务2(15, 10819, 5816, 13924, 512, 0x3796, 0xC682D, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC682D);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{

						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						加入优先打怪ID(L"82401");
						功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 200, 3000);
						return false;

					}
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}
		if (!任务::任务是否已完成(0xC6830, vsk))
		{
			if (!任务::是否已接任务(0xC6830))
			{
				功能::到指定地点找NPC接任务2(15, 10819, 5816, 13924, 512, 0x3796, 0xC6830, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC6830);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{

						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						加入优先打怪ID(L"82404|183320");
						功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 200, 500);
						return false;

					}
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}
		if (!任务::任务是否已完成(0xC6831, vsk))
		{
			if (!任务::是否已接任务(0xC6831))
			{
				功能::到指定地点找NPC接任务2(15, 10819, 12564, 11363, -1, 0x379A, 0xC6831, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC6831);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{

						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						加入优先打怪ID(L"183340");
						功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 200, 2000);
						return false;

					}
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}
		if (!任务::任务是否已完成(0xC6832, vsk))
		{
			if (!任务::是否已接任务(0xC6832))
			{
				功能::到指定地点找NPC接任务2(15, 10819, 12564, 11363, -1, 0x379A, 0xC6832, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC6832);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
						return false;
					}
					if (支线任务.dStep == 2)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
						return false;
					}
					if (支线任务.dStep == 3)
					{
						UI功能::内存按键(VK_F5);
						/*坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);*/
						return false;
					}
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}
	}
	if (任务::任务是否已完成(813002, vsk) || 任务::取出指定主线任务(813002).dStep >= 2) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(0xC6834, vsk))
		{
			if (!任务::是否已接任务(0xC6834))
			{
				功能::到指定地点找NPC接任务2(15, 10819, 15002, 7880, 0, 0x3791, 0xC6834, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC6834);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						加入优先打怪ID(L"183360");
						功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 300, 2000, 150);
						return false;
					}
				}
			}
		}
	}
	if (任务::任务是否已完成(813002, vsk) || 任务::取出指定主线任务(813002).dStep >= 3) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(0xC6834, vsk))
		{
			if (!任务::是否已接任务(0xC6834))
			{
				功能::到指定地点找NPC接任务2(15, 10819, 15002, 7880, 0, 0x3791, 0xC6834, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC6834);
				if (支线任务.dState == 2)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}
	}
	if (任务::任务是否已完成(813003, vsk) || 任务::取出指定主线任务(813003).dStep >= 3) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(0xC6835, vsk))
		{
			if (!任务::是否已接任务(0xC6835))
			{
				功能::到指定地点找NPC接任务2(15, 10819, 14831, 8868, 0, 0x379C, 0xC6835, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC6835);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25, 1);
						return false;
					}
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}

		if (!任务::任务是否已完成(0xC6836, vsk))
		{
			if (!任务::是否已接任务(0xC6836))
			{
				功能::到指定地点找NPC接任务2(15, 10819, 20309, 11412, 128, 0x3792, 0xC6836, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC6836);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						加入优先打怪ID(L"183370|183380");
						功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 300, 2000, 125);
						return false;
					}
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}
	}
	return true;
}
bool 游戏::支线_拉伊亚阶地(vector<DWORD>& vsk)
{
	if (任务::任务是否已完成(815001, vsk) || 任务::取出指定主线任务(815001).dStep >= 2) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(0xC7004, vsk))
		{
			if (!任务::是否已接任务(0xC7004))
			{
				功能::到指定地点找NPC接任务2(15, 10820, -14265, -22866, 1024, 0x37A4, 0xC7004, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC7004);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
						return false;
					}
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}
		if (!任务::任务是否已完成(0xC7005, vsk))
		{
			if (!任务::是否已接任务(0xC7005))
			{
				功能::到指定地点找NPC接任务2(15, 10820, -12122, -23214, 1773, 0x37B7, 0xC7005, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC7005);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 支线任务.TargetId, 支线任务.dQuestId, -1, 100, 支线任务.dStep);
						return false;
					}
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}
		if (!任务::任务是否已完成(0xC7006, vsk))
		{
			if (!任务::是否已接任务(0xC7006))
			{
				功能::到指定地点找NPC接任务2(15, 10820, -11892, -20632, 1479, 0x37B8, 0xC7006, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC7006);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点采集任务显示(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 1000, 0x14245);
						return false;
					}
					if (支线任务.dStep == 2)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点采集任务显示(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 1000, 0x1424F, 100, 200);
						return false;
					}
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}
		if (!任务::任务是否已完成(0xC7007, vsk))
		{
			if (!任务::是否已接任务(0xC7007))
			{
				功能::到指定地点找NPC接任务2(15, 10820, -11892, -20632, 1479, 0x37B8, 0xC7007, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC7007);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 支线任务.TargetId, 支线任务.dQuestId, -1, 100, 支线任务.dStep);
						return false;
					}

				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}
		if (!任务::任务是否已完成(0xC7008, vsk))
		{
			if (!任务::是否已接任务(0xC7008))
			{
				功能::到指定地点找NPC接任务2(15, 10820, 12122, -23214, 1773, 0x37B7, 0xC7008, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC7008);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点按G(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 100);
						return false;
					}

				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}
		if (!任务::任务是否已完成(0xC7009, vsk))
		{
			if (!任务::是否已接任务(0xC7009))
			{
				功能::到指定地点找NPC接任务2(15, 10820, 12122, -23214, 1773, 0x37B7, 0xC7009, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC7009);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 支线任务.TargetId, 支线任务.dQuestId, -1, 100, 支线任务.dStep);
						return false;
					}
					if (支线任务.dStep == 2)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 支线任务.TargetId, 支线任务.dQuestId, -1, 100, 支线任务.dStep);
						return false;
					}

				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}
	}
	if (任务::任务是否已完成(815003, vsk)) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(0xC6FFF, vsk))
		{
			if (!任务::是否已接任务(0xC6FFF))
			{
				功能::到指定地点找NPC接任务2(15, 10820, -7788, -13783, 1449, 0x37A5, 0xC6FFF, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC6FFF);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点采集任务显示(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 1000, 0x1424E);
						return false;
					}
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}
	}
	if (任务::任务是否已完成(815005, vsk) || 任务::取出指定主线任务(815005).dStep >= 3) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(0xC7001, vsk))
		{
			if (!任务::是否已接任务(0xC7001))
			{
				功能::到指定地点找NPC接任务2(15, 10820, -13995, -16210, 1021, 0x37B0, 0xC7001, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC7001);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
						return false;
					}
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}
	}
	return true;
}
bool 游戏::支线_博伦亚领地(vector<DWORD>& vsk)
{
	if (任务::任务是否已完成(816001, vsk) || 任务::取出指定主线任务(816001).dStep >= 2) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(816101, vsk))
		{
			if (!任务::是否已接任务(816101))
			{
				功能::到指定地点找NPC接任务2(15, 10821, -26472, -17243, 768, 0x37CB, 816101, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(816101);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
						return false;
					}
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}
		if (!任务::任务是否已完成(816102, vsk))
		{
			if (!任务::是否已接任务(816102))
			{
				功能::到指定地点找NPC接任务2(15, 10821, -26762, -16575, 832, 0x37CA, 816102, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(816102);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						if (背包::返回指定物品数量(0x61A83) == 0)
						{
							坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
							功能::到指定地点找NPC买物品(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0x37CA, 50, 0x61A83, 1);
							return false;
						}
						else
						{
							坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
							功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 支线任务.TargetId, 支线任务.dQuestId, -1, 50, 支线任务.dStep);
							return false;
						}
					}
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}
		if (!任务::任务是否已完成(816103, vsk))
		{
			if (!任务::是否已接任务(816103))
			{
				功能::到指定地点找NPC接任务2(15, 10821, -26472, -17257, 770, 0x37CB, 816103, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(816103);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
						return false;
					}
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}
	}
	if (任务::任务是否已完成(816003, vsk) || 任务::取出指定主线任务(816003).dStep >= 3) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(0xC73E9, vsk))
		{
			if (!任务::是否已接任务(0xC73E9))
			{
				功能::到指定地点找NPC接任务2(15, 10821, -21457, -28637, 512, 0x37D1, 0xC73E9, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC73E9);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						加入优先打怪ID(L"183870");
						功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 300, 2000, 125, true, 100);
						return false;
					}
				}
				/*else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}*/
			}
		}
	}
	if (任务::任务是否已完成(816003, vsk) || 任务::取出指定主线任务(816003).dStep >= 4) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(0xC73E9, vsk))
		{
			if (任务::是否已接任务(0xC73E9))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC73E9);
				if (支线任务.dState == 2)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}

		}
	}
	if (任务::任务是否已完成(816003, vsk) || 任务::取出指定主线任务(816003).dStep >= 5) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(0xC73EA, vsk))
		{
			if (!任务::是否已接任务(0xC73EA))
			{
				功能::到指定地点找NPC接任务2(15, 10821, -19346, -28784, 512, 0x37D2, 0xC73EA, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC73EA);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						if (支线任务.子任务进度[0].dCur == 0)
						{
							功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, -17628, -27065, 512, 0x37E8, 支线任务.dQuestId, -1, 500);
							return false;
						}
						if (支线任务.子任务进度[0].dCur == 1)
						{
							功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, -20403, -26422, 512, 0x37E8, 支线任务.dQuestId, -1, 500);
							return false;
						}

					}
				}
				/*else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}*/
			}
		}
	}
	if (任务::任务是否已完成(816003, vsk) || 任务::取出指定主线任务(816003).dStep >= 6) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(0xC73EA, vsk))
		{
			if (任务::是否已接任务(0xC73EA))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC73EA);
				if (支线任务.dState == 2)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}


		}
	}
	if (任务::任务是否已完成(816002, vsk) || 任务::取出指定主线任务(816002).dStep >= 5) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(816104, vsk))
		{
			if (!任务::是否已接任务(816104))
			{
				功能::到指定地点找NPC接任务2(15, 10821, -26574, -15317, 832, 0x37CC, 816104, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(816104);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 150);
						return false;
					}
					if (支线任务.dStep == 2)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 150);
						return false;
					}
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}
	}
	if (任务::任务是否已完成(816004, vsk) || 任务::取出指定主线任务(816004).dStep >= 1) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(816112, vsk))
		{
			if (!任务::是否已接任务(816112))
			{
				功能::到指定地点找NPC接任务2(15, 10821, -13603, -28282, 768, 0x37E3, 816112, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(816112);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 150);
						return false;
					}

				}
				/*else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}*/
			}
		}

	}
	if (任务::任务是否已完成(816002, vsk) || 任务::取出指定主线任务(816002).dStep >= 2) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(816112, vsk))
		{
			if (任务::是否已接任务(816112))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(816112);
				if (支线任务.dState == 2)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}


		}
		/*if (!任务::任务是否已完成(816113, vsk))
		{
			if (!任务::是否已接任务(816113))
			{
				功能::到指定地点找NPC接任务2(15, 10821, -15944, -18458, 513, 0x37DF, 816113, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(816113);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 150);
						return false;
					}

				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}
		if (!任务::任务是否已完成(816114, vsk))
		{
			if (!任务::是否已接任务(816114))
			{
				功能::到指定地点找NPC接任务2(15, 10821, -18156, -19885, -1024, 0x37E0, 816114, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(816114);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点按G(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 150);
						return false;
					}

				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}
		if (!任务::任务是否已完成(816115, vsk))
		{
			if (!任务::是否已接任务(816115))
			{
				功能::到指定地点找NPC接任务2(15, 10821, -15944, -18458, 513, 0x37DF, 816114, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(816115);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						if (支线任务.子任务进度.size() == 2)
						{
							if (支线任务.子任务进度[0].dCur == 0)
							{
								坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
								功能::到指定地点(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
								return false;
							}
							if (支线任务.子任务进度[1].dCur< 支线任务.子任务进度[1].dNeed)
							{
								坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
								功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 300, 2000, 125, true, 100);
								return false;
							}
						}

					}
					if (支线任务.dStep == 2)
					{
						if (支线任务.子任务进度.size() == 2)
						{
							if (支线任务.子任务进度[0].dCur == 0)
							{
								坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
								功能::到指定地点(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
								return false;
							}
							if (支线任务.子任务进度[1].dCur < 支线任务.子任务进度[1].dNeed)
							{
								坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
								加入优先打怪ID(L"82614");
								功能::移动打怪(-14105, -15786, 512, 300, 2000, 125, true, 100);
								return false;
							}
						}
					}
					if (支线任务.dStep == 3)
					{
						if (支线任务.子任务进度.size() == 2)
						{
							if (支线任务.子任务进度[0].dCur == 0)
							{
								坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
								功能::到指定地点(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
								return false;
							}
							if (支线任务.子任务进度[1].dCur < 支线任务.子任务进度[1].dNeed)
							{
								坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
								加入优先打怪ID(L"187080");
								功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 300, 2000, 125, true, 100);
								return false;
							}
						}
					}
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}*/
	}
	if (任务::任务是否已完成(816006, vsk) || 任务::取出指定主线任务(816006).dStep >= 4) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(0xC73EE, vsk))
		{
			if (!任务::是否已接任务(0xC73EE))
			{
				功能::到指定地点找NPC接任务2(15, 10821, -14955, -7272, 768, 0x37D7, 0xC73EE, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC73EE);
				if (支线任务.dState == 1)
				{
					objInfo_ NPC信息 = 环境::取指定对象信息(支线任务.TargetId);
					if (NPC信息.dResId != 0)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 支线任务.TargetId, 支线任务.dQuestId, -1, 50, 支线任务.dStep);
						return false;
					}
					else
					{
						if (地图::传送点是否激活(0xDBD6D))
						{
							地图::传送(0xDBD6D);
							Sleep(10000);
							return false;
						}
						else
						{
							坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
							功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 支线任务.TargetId, 支线任务.dQuestId, -1, 50, 支线任务.dStep);
							return false;
						}
					}
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}

	}
	if (任务::任务是否已完成(817001, vsk))
	{
		if (!任务::任务是否已完成(0xC3965, vsk))//卢特兰的回忆 
		{
			if (!任务::是否已接任务(0xC3965))
			{
				功能::到指定地点找NPC接任务2(15, 10801, 17927, 0, -14236, 0x32C9, 0xC3965, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC3965);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 支线任务.TargetId, 支线任务.dQuestId, -1, 50, 支线任务.dStep);
						return false;
					}
					if (支线任务.dStep == 2)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 支线任务.TargetId, 支线任务.dQuestId, -1, 50, 支线任务.dStep);
						return false;
					}
					if (支线任务.dStep == 3)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点按G(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
						return false;
					}
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}
		if (!任务::任务是否已完成(0xC3966, vsk))//卢特兰的回忆 
		{
			if (!任务::是否已接任务(0xC3966))
			{
				功能::到指定地点找NPC接任务2(15, 10801, 14716, 4133, 1025, 0x3307, 0xC3966, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC3966);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 支线任务.TargetId, 支线任务.dQuestId, -1, 50, 支线任务.dStep);
						return false;
					}
					if (支线任务.dStep == 2)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
						return false;
					}

				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}
		if (!任务::任务是否已完成(0xC3967, vsk))//卢特兰的回忆 
		{
			if (!任务::是否已接任务(0xC3967))
			{
				功能::到指定地点找NPC接任务2(15, 10801, -1343, 563, 261, 0x3375, 0xC3967, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC3967);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 支线任务.TargetId, 支线任务.dQuestId, -1, 50, 支线任务.dStep);
						return false;
					}
					if (支线任务.dStep == 2)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 支线任务.TargetId, 支线任务.dQuestId, -1, 50, 支线任务.dStep);
						return false;
					}
					if (支线任务.dStep == 3)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						if (功能::到指定地点(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50))
						{
							本人::CALL_做社交动作(0xF24A);
							Sleep(1000);
						}
						return false;
					}
					if (支线任务.dStep == 4)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 支线任务.TargetId, 支线任务.dQuestId, -1, 50, 支线任务.dStep);
						return false;
					}
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}
		if (!任务::任务是否已完成(0xC3968, vsk))//卢特兰的回忆 
		{
			if (!任务::是否已接任务(0xC3968))
			{
				功能::到指定地点找NPC接任务2(15, 10801, -810, -5540, -30, 0x335C, 0xC3968, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC3968);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 支线任务.TargetId, 支线任务.dQuestId, -1, 50, 支线任务.dStep);
						return false;
					}
					if (支线任务.dStep == 2)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点采集任务显示(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 1000, 0x140C9, 100, 200);
						return false;
					}
					if (支线任务.dStep == 3)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 支线任务.TargetId, 支线任务.dQuestId, -1, 50, 支线任务.dStep);
						return false;
					}
					if (支线任务.dStep == 4)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 支线任务.TargetId, 支线任务.dQuestId, -1, 50, 支线任务.dStep);
						return false;
					}
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}
		if (!任务::任务是否已完成(0xC3969, vsk))//卢特兰的回忆 
		{
			if (!任务::是否已接任务(0xC3969))
			{
				功能::到指定地点找NPC接任务2(15, 10801, 14636, 8949, 1533, 0x36C4, 0xC3969, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC3969);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 支线任务.TargetId, 支线任务.dQuestId, -1, 50, 支线任务.dStep);
						return false;
					}
					if (支线任务.dStep == 2)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 支线任务.TargetId, 支线任务.dQuestId, -1, 50, 支线任务.dStep);
						return false;
					}
					if (支线任务.dStep == 3)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 50, 支线任务.dStep);
						return false;
					}
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}

		if (!任务::任务是否已完成(0xC6839, vsk))//救我 
		{
			if (!任务::是否已接任务(0xC6839))
			{
				功能::到指定地点找NPC接任务2(15, 10819, 5816, 13924, 512, 0x3796, 0xC6839, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC6839);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点按G(15, 任务坐标.地图ID, 19905, 22649, -0, 50);
						return false;
					}
					if (支线任务.dStep == 2)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点按G(15, 任务坐标.地图ID, 19905, 22649, -0, 50);
						return false;
					}
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}

		if (!任务::任务是否已完成(0xC683A, vsk))//救我 
		{
			if (!任务::是否已接任务(0xC683A))
			{
				功能::到指定地点找NPC接任务2(15, 10819, 20043, 22638, 0, 0x3862, 0xC683A, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC683A);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 支线任务.TargetId, 支线任务.dQuestId, -1, 50, 支线任务.dStep);
						return false;
					}
					if (支线任务.dStep == 2)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 支线任务.TargetId, 支线任务.dQuestId, -1, 50, 支线任务.dStep);
						return false;
					}
					if (支线任务.dStep == 3)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 支线任务.TargetId, 支线任务.dQuestId, -1, 50, 支线任务.dStep);
						return false;
					}
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}
		if (!任务::任务是否已完成(0xC683B, vsk))//救我 
		{
			if (!任务::是否已接任务(0xC683B))
			{
				功能::到指定地点找NPC接任务2(15, 10819, 23225, 21576, 1024, 0x3798, 0xC683B, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC683B);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点采集任务显示(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 500, 0x141FC);
						return false;
					}
					if (支线任务.dStep == 2)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 支线任务.TargetId, 支线任务.dQuestId, -1, 50, 支线任务.dStep);
						return false;
					}
					if (支线任务.dStep == 3)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 支线任务.TargetId, 支线任务.dQuestId, -1, 50, 支线任务.dStep);
						return false;
					}
					if (支线任务.dStep == 4)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						if (功能::到指定地点(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50))
						{
							本人::CALL_做社交动作(0xF23D);
							Sleep(1000);
						}
						return false;
					}
					if (支线任务.dStep == 5)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 支线任务.TargetId, 支线任务.dQuestId, -1, 50, 支线任务.dStep);
						return false;
					}
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}
		if (!任务::任务是否已完成(0xC73EF, vsk))//体力药水 
		{
			if (!任务::是否已接任务(0xC73EF))
			{
				功能::到指定地点找NPC接任务2(15, 10819, 19909, 22645, 0, 0x3863, 0xC73EF, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC73EF);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						objInfo_ NPC信息 = 环境::取指定对象信息(支线任务.TargetId);
						if (NPC信息.dResId != 0)
						{
							坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
							功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 支线任务.TargetId, 支线任务.dQuestId, -1, 50, 支线任务.dStep);
							return false;
						}
						else
						{
							if (地图::传送点是否激活(900461))
							{
								地图::传送(900461);
								Sleep(10000);
								return false;
							}

						}
					}
					if (支线任务.dStep == 2)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 支线任务.TargetId, 支线任务.dQuestId, -1, 50, 支线任务.dStep);
						return false;
					}
					if (支线任务.dStep == 3)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 支线任务.TargetId, 支线任务.dQuestId, -1, 50, 支线任务.dStep);
						return false;
					}
					if (支线任务.dStep == 4)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点按G(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 100);
						return false;
					}
					if (支线任务.dStep == 5)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 支线任务.TargetId, 支线任务.dQuestId, -1, 50, 支线任务.dStep);
						return false;
					}
					if (支线任务.dStep == 6)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 支线任务.TargetId, 支线任务.dQuestId, -1, 50, 支线任务.dStep);
						return false;
					}
					if (支线任务.dStep == 7)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 支线任务.TargetId, 支线任务.dQuestId, -1, 50, 支线任务.dStep);
						return false;
					}
					if (支线任务.dStep == 8)
					{
						UI功能::内存按键(VK_F5);
						Sleep(3000);
						return false;
					}
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}
	}

	return true;
}
bool 游戏::支线_鬃波港(vector<DWORD>& vsk)
{
	if (任务::任务是否已完成(818001, vsk) || 任务::取出指定主线任务(818001).dStep >= 5) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(818102, vsk))
		{
			if (!任务::是否已接任务(818102))
			{
				功能::到指定地点找NPC接任务2(15, 10804, 7801, -20470, 729, 0x3AAA, 818102, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(818102);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
						return false;
					}
					if (支线任务.dStep == 2)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
						return false;
					}
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}
		if (!任务::任务是否已完成(818110, vsk))
		{
			if (!任务::是否已接任务(818110))
			{
				功能::到指定地点找NPC接任务2(15, 10804, 5139, 8698, 256, 0x3ABB, 818110, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(818110);
				if (支线任务.dState == 1)
				{

					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
						return false;
					}
					if (支线任务.dStep == 2)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点按G(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
						return false;
					}
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}
		if (!任务::任务是否已完成(818104, vsk))
		{
			if (!任务::是否已接任务(818104))
			{
				功能::到指定地点找NPC接任务2(15, 10804, 5139, 8698, 256, 0x3ABB, 818104, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(818104);
				if (支线任务.dState == 1)
				{

					if (支线任务.dStep == 1)
					{
						ActorInfo_ 角色信息 = 本人::取角色信息();
						if (角色信息.举起状态 == 1)
						{
							坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
							功能::到指定地点采集任务显示(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 500, 0x143DD);
							return false;
						}
						else
						{
							坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
							if (功能::到指定地点(15, 任务坐标.地图ID, 6020, 9763, 256, 100))
							{
								UI功能::内存按键('R');
							}
							return false;
						}

					}

				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}
		if (!任务::任务是否已完成(818112, vsk))
		{
			if (!任务::是否已接任务(818112))
			{
				功能::到指定地点找NPC接任务2(15, 10804, 6064, 9793, 256, 0x3ABC, 818112, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(818112);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点(15, 任务坐标.地图ID, 6568, 10054, 257, 50);
						return false;

					}
					if (支线任务.dStep == 2)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 支线任务.TargetId, 支线任务.dQuestId, -1, 25, 支线任务.dStep);
						return false;

					}
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}
	}
	if (任务::任务是否已完成(818004, vsk) || 任务::取出指定主线任务(818004).dStep >= 10) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(818106, vsk))
		{
			if (!任务::是否已接任务(818106))
			{
				功能::到指定地点找NPC接任务2(15, 10804, 9555, 10879, 255, 0x3AB8, 818106, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(818106);

				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点采集任务显示(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 1000, 0x143E8, 100, 300);
						return false;
					}
					if (支线任务.dStep == 2)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点采集任务显示(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 1000, 0x143E8, 100, 300);
						return false;
					}
					if (支线任务.dStep == 3)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 支线任务.TargetId, 支线任务.dQuestId, -1, 25, 支线任务.dStep);
						return false;
					}
					if (支线任务.dStep == 4)
					{
						UI功能::内存按键(VK_F5);
						return false;
					}
					if (支线任务.dStep == 5)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点采集任务显示(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 1000, 0x143E9, 100, 100);
						return false;
					}
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}
	}
	return true;
}
bool 游戏::支线_科罗克尼斯渔村(vector<DWORD>& vsk)
{
	if (任务::任务是否已完成(819003, vsk) || 任务::取出指定主线任务(819003).dStep >= 3) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(0xC7FA1, vsk))
		{
			if (!任务::是否已接任务(0xC7FA1))
			{
				功能::到指定地点找NPC接任务2(15, 10823, 9490, 17075, 640, 0x3ADE, 0xC7FA1, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC7FA1);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						加入优先打怪ID(L"83025");
						功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 3000, 100, true);
						return false;
					}

				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}
			}
		}
	}
	if (任务::任务是否已完成(819005, vsk) || 任务::取出指定主线任务(819005).dStep >= 2) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(0xC7FA5, vsk))
		{
			if (!任务::是否已接任务(0xC7FA5))
			{
				功能::到指定地点找NPC接任务2(15, 10823, 7510, 33283, 512, 0x3AE4, 0xC7FA5, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC7FA5);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						加入优先打怪ID(L"185161");
						功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 3000, 100, true);
						return false;
					}

				}

			}
		}
	}
	if (任务::任务是否已完成(819005, vsk) || 任务::取出指定主线任务(819005).dStep >= 4) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(0xC7FA5, vsk))
		{
			if (任务::是否已接任务(0xC7FA5))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC7FA5);
				if (支线任务.dState == 2)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;

				}
			}


		}
	}
	if (任务::任务是否已完成(819006, vsk) || 任务::取出指定主线任务(819006).dStep >= 5) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(0xC7FA6, vsk))
		{
			if (!任务::是否已接任务(0xC7FA6))
			{
				功能::到指定地点找NPC接任务2(15, 10823, 5563, 42169, 1033, 0x3AE7, 0xC7FA6, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC7FA6);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务3(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 支线任务.TargetId, 支线任务.dQuestId, -1, 25, 支线任务.dStep);
						return false;
					}

				}

			}
		}
	}
	if (任务::任务是否已完成(819006, vsk)) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(0xC7FA6, vsk))
		{
			if (任务::是否已接任务(0xC7FA6))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC7FA6);
				if (支线任务.dState == 2)
				{

					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;


				}
			}

		}
	}
	if (任务::任务是否已完成(819007, vsk) || 任务::取出指定主线任务(819007).dStep >= 1) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(0xC7FA7, vsk))
		{
			if (!任务::是否已接任务(0xC7FA7))
			{
				功能::到指定地点找NPC接任务2(15, 10823, 10958, 39630, 510, 0x3AE9, 0xC7FA7, 50);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xC7FA7);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						加入优先打怪ID(L"185120|185130");
						功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 3000, 100, true);
						return false;
					}

				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25);
					return false;
				}

			}
		}
	}
	return true;
}
bool 游戏::支线_世界1(vector<DWORD>& vsk)
{
	if (任务::任务是否已完成(1002002, vsk) || 任务::取出指定主线任务(1002002).dStep >= 2) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		//MyTrace(L"支线 0xF4A76");
		if (!任务::任务是否已完成(0xF4A76, vsk))
		{
			if (!任务::是否已接任务(0xF4A76))
			{
				功能::到指定地点找NPC接任务2(2, 11011, 5188, 4492, 516, 0x5284, 0xF4A76, 250);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xF4A76);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 5188, 4492, 516, 支线任务.TargetId, 支线任务.dQuestId, -1, 25, 支线任务.dStep);
						return false;
					}
					if (支线任务.dStep == 2)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						if (支线任务.子任务进度.size() == 3)
						{
							if (支线任务.子任务进度[0].dCur < 支线任务.子任务进度[0].dNeed)
							{
								功能::到指定地点采集任务显示(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 2000, 0x1ADBA);
								return false;
							}
							if (支线任务.子任务进度[1].dCur < 支线任务.子任务进度[1].dNeed)
							{
								功能::到指定地点采集任务显示(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 2000, 0x1ADBA);
								return false;
							}
							if (支线任务.子任务进度[2].dCur < 支线任务.子任务进度[2].dNeed)
							{
								功能::到指定地点采集任务显示(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 2000, 0x1ADBA);
								return false;
							}
						}
						return false;
					}
					if (支线任务.dStep == 3)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点按G(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 150);
						return false;
					}
					if (支线任务.dStep == 4)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点按G(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 150);
						return false;
					}
					if (支线任务.dStep == 5)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点按G(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 150);
						return false;
					}
				}
				else
				{
					任务::CALL_交任务(支线任务.dQuestId, -1);
					Sleep(500);
					return false;
				}
			}
		}

	}
	if (任务::任务是否已完成(1002006, vsk) || 任务::取出指定主线任务(1002006).dStep >= 1) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(0xF4A7D, vsk))
		{
			if (!任务::是否已接任务(0xF4A7D))
			{
				功能::到指定地点找NPC接任务2(2, 11011, 24251, 21897, 1026, 0x521D, 0xF4A7D, 250);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xF4A7D);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						加入优先打怪ID(L"190133");
						功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 3000, 100, true);
						return false;
					}
				}
				else
				{

				}
			}
		}
	}
	if (任务::任务是否已完成(1002006, vsk) || 任务::取出指定主线任务(1002006).dState == 2) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(0xF4A7D, vsk))
		{
			if (任务::是否已接任务(0xF4A7D))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xF4A7D);
				if (支线任务.dState == 2)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(2, 任务坐标.地图ID, 24891, 13464, 1500, 0x521E, 支线任务.dQuestId, -1, 150);
					return false;
				}
			}
		}
	}
	if (任务::任务是否已完成(1002006, vsk)) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(0xF4A7F, vsk))
		{
			if (!任务::是否已接任务(0xF4A7F))
			{
				功能::到指定地点找NPC接任务2(2, 11011, 26788, 11666, 1500, 0x528C, 0xF4A7F, 250);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xF4A7F);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点采集任务显示(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 2000, 110042);
						return false;
					}
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 150);
					return false;
				}
			}
		}
	}
	if (任务::任务是否已完成(1001004, vsk) || 任务::取出指定主线任务(1001004).dStep >= 1) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(0xF468E, vsk))
		{
			if (!任务::是否已接任务(0xF468E))
			{
				功能::到指定地点找NPC接任务2(2, 11001, 3043, 8303, 521, 0x5220, 0xF468E, 250);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xF468E);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点按G(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 150);
						return false;
					}
					if (支线任务.dStep == 2)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点按G(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 150);
						return false;
					}
					if (支线任务.dStep == 3)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务2(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 150);
						return false;
					}
					if (支线任务.dStep == 4)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						ActorInfo_ 角色信息 = 本人::取角色信息();
						if (角色信息.举起状态 == 1)
						{

							功能::到指定地点采集任务显示(2, 任务坐标.地图ID, 3575, 8110, 514, 1000, 0x1AE1D, 100, 100);

						}
						else
						{
							if (功能::到指定地点(2, 任务坐标.地图ID, 3283, 8073, 525, 50))
							{
								UI功能::内存按键('R');
								Sleep(1000);
							}
						}
						return false;
					}
					if (支线任务.dStep == 5)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						ActorInfo_ 角色信息 = 本人::取角色信息();
						if (角色信息.举起状态 == 1)
						{

							功能::到指定地点采集任务显示(2, 任务坐标.地图ID, 3575, 8110, 514, 1000, 0x1AE1F, 100, 100);

						}
						else
						{
							if (功能::到指定地点(2, 任务坐标.地图ID, 3283, 8073, 525, 50))
							{
								UI功能::内存按键('R');
								Sleep(1000);
							}
						}
						return false;
					}
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 150);
					return false;
				}
			}
		}
	}
	if (任务::任务是否已完成(1001005, vsk) || 任务::取出指定主线任务(1001005).dStep >= 1) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(0xF4691, vsk))
		{
			if (!任务::是否已接任务(0xF4691))
			{
				功能::到指定地点找NPC接任务2(2, 11001, 4526, 3258, -340, 0x527F, 0xF4691, 150);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xF4691);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点采集任务显示(2, 任务坐标.地图ID, 4503, 3138, -338, 2000, 0x1AE2D, 100, 100);
						return false;
					}
					if (支线任务.dStep == 2)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						if (功能::到指定地点(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50))
						{
							UI功能::内存按键(VK_F5);
						}

						return false;
					}
					if (支线任务.dStep == 3)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点按G(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
						return false;
					}
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 150);
					return false;
				}
			}
		}
		if (!任务::任务是否已完成(0xF468F, vsk))
		{
			if (!任务::是否已接任务(0xF468F))
			{
				功能::到指定地点找NPC接任务2(2, 11001, 3432, 5453, -340, 0x52E2, 0xF468F, 150);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xF468F);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点采集任务显示(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 1000, 0x1AE3E, 100, 100);
						return false;
					}
					if (支线任务.dStep == 2)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点采集任务显示(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 1000, 0x1AE21, 100, 250);
						return false;
					}
				}
				else
				{
					任务::CALL_交任务(支线任务.dQuestId, -1);
					return false;
				}
			}
		}
	}
	if (任务::任务是否已完成(1001006, vsk)) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(0xF4E62, vsk))
		{
			if (!任务::是否已接任务(0xF4E62))
			{
				功能::到指定地点找NPC接任务2(2, 11012, 1804, 1861, 0, 0x529A, 0xF4E62, 150);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xF4E62);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点按G(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
						return false;
					}
					if (支线任务.dStep == 2)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点按G(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
						return false;
					}
					if (支线任务.dStep == 3)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点按G(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
						return false;
					}
				}
				else
				{
					任务::CALL_交任务(支线任务.dQuestId, -1);
					return false;
				}
			}
		}
	}
	if (任务::任务是否已完成(1003003, vsk) || 任务::取出指定主线任务(1003003).dStep >= 3) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(0xF4E63, vsk))
		{
			if (!任务::是否已接任务(0xF4E63))
			{
				功能::到指定地点找NPC接任务2(2, 11012, 10861, 12788, 485, 0x529B, 0xF4E63, 150);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xF4E63);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点按G(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 100);
						return false;
					}

				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 150);
					return false;
				}
			}
		}
		if (!任务::任务是否已完成(0xF4E5F, vsk))
		{
			if (!任务::是否已接任务(0xF4E5F))
			{
				功能::到指定地点找NPC接任务2(2, 11012, 10459, 12938, 469, 0x522B, 0xF4E5F, 150);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xF4E5F);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 3000, 100, true);
						return false;
					}

				}
				else
				{
					任务::CALL_交任务(支线任务.dQuestId, -1);
					return false;
				}
			}
		}
		if (!任务::任务是否已完成(0xF4E63, vsk))
		{
			if (任务::是否已接任务(0xF4E63))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xF4E63);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点按G(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 100);
						return false;
					}
					if (支线任务.dStep == 2)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点按G(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 100);
						return false;
					}
					if (支线任务.dStep == 3)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点按G(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 100);
						return false;
					}
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 150);
					return false;
				}
			}

		}
	}
	if (任务::任务是否已完成(1003005, vsk) || 任务::取出指定主线任务(1003005).dStep >= 2) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(0xF4E65, vsk))
		{
			if (!任务::是否已接任务(0xF4E65))
			{
				功能::到指定地点找NPC接任务2(2, 11012, 7592, 22333, 454, 0x529E, 0xF4E65, 150);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xF4E65);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点按G(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 100);
						return false;
					}

				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 150);
					return false;
				}
			}
		}
	}
	if (任务::任务是否已完成(1003005, vsk) || 任务::取出指定主线任务(1003005).dStep >= 3) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(0xF4E61, vsk))
		{
			if (!任务::是否已接任务(0xF4E61))
			{
				功能::到指定地点找NPC接任务2(2, 11012, 12294, 19738, 464, 0x5231, 0xF4E61, 150);
				return false;
			}

		}
		if (!任务::任务是否已完成(0xF4E60, vsk))
		{
			if (!任务::是否已接任务(0xF4E60))
			{
				功能::到指定地点找NPC接任务2(2, 11012, 12294, 19738, 464, 0x5231, 0xF4E60, 150);
				return false;
			}

		}
		if (!任务::任务是否已完成(0xF4E60, vsk))
		{
			if (任务::是否已接任务(0xF4E60))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xF4E60);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						加入优先打怪ID(L"190270");
						功能::移动打怪(16935, 16242, 465, 100, 3000, 100, true);
						return false;
					}

				}
			}


		}
		if (!任务::任务是否已完成(0xF4E61, vsk))
		{
			if (任务::是否已接任务(0xF4E61))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xF4E61);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点采集任务显示(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 1000, 0x1AE88);
						return false;
					}

				}
			}


		}
	}
	if (任务::任务是否已完成(1003005, vsk) || 任务::取出指定主线任务(1003005).dStep >= 5) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(0xF4E61, vsk))
		{
			if (任务::是否已接任务(0xF4E61))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xF4E61);
				if (支线任务.dState == 2)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 150);
					return false;

				}
			}


		}
		if (!任务::任务是否已完成(0xF4E60, vsk))
		{
			if (任务::是否已接任务(0xF4E60))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xF4E60);
				if (支线任务.dState == 2)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 150);
					return false;

				}
			}


		}
	}
	if (任务::任务是否已完成(1004001, vsk) || 任务::取出指定主线任务(1004001).dStep >= 2) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(0xF5245, vsk))
		{
			if (!任务::是否已接任务(0xF5245))
			{
				功能::到指定地点找NPC接任务2(2, 11013, 7480, 4316, -48, 0x52A4, 0xF5245, 150);
				return false;
			}

		}
		/*if (!任务::任务是否已完成(0xF5246, vsk))
		{
			if (!任务::是否已接任务(0xF5246))
			{
				功能::到指定地点找NPC接任务2(2, 11013, 7493, 3206, -0, 0x523F, 0xF5246, 150);
				return false;
			}

		}
		if (!任务::任务是否已完成(0xF5246, vsk))
		{
			if (任务::是否已接任务(0xF5246))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xF5246);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点按G(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 100);
						return false;
					}

				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 150);
					return false;
				}

			}

		}*/
		if (!任务::任务是否已完成(0xF5245, vsk))
		{
			if (任务::是否已接任务(0xF5245))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xF5245);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务2(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 支线任务.TargetId, 支线任务.dQuestId, -1, 150);
						return false;
					}

				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 150);
					return false;
				}

			}

		}
	}
	if (任务::任务是否已完成(1004003, vsk) || 任务::取出指定主线任务(1004003).dStep >= 1) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(0xF5247, vsk))
		{
			if (!任务::是否已接任务(0xF5247))
			{
				功能::到指定地点找NPC接任务2(2, 11013, 14440, 11329, 2562, 0x52B2, 0xF5247, 150);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xF5247);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点按G(2, 任务坐标.地图ID, 14426, 11691, 2560, 100);
						return false;
					}
					if (支线任务.dStep == 2)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 支线任务.TargetId, 支线任务.dQuestId, -1, 25, 支线任务.dStep);
						return false;
					}
					if (支线任务.dStep == 3)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点采集任务显示(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 3000, 110338);
						return false;
					}
				}
				else
				{
					任务::CALL_交任务(支线任务.dQuestId, -1);
					return false;
				}
			}
		}
	}
	if (任务::任务是否已完成(1004006, vsk) || 任务::取出指定主线任务(1004006).dStep >= 1) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(0xF524B, vsk))
		{
			if (!任务::是否已接任务(0xF524B))
			{
				功能::到指定地点找NPC接任务2(2, 11013, 16767, 17516, 2306, 0x52B9, 0xF524B, 150);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xF524B);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{

						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点按G(2, 任务坐标.地图ID, 15625, 17670, 2304, 50);
						return false;
					}
					if (支线任务.dStep == 2)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点按G(2, 任务坐标.地图ID, 15625, 17670, 2304, 50);
						return false;
					}
					if (支线任务.dStep == 3)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点按G(2, 任务坐标.地图ID, 15625, 17670, 2304, 50);
						return false;
					}
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 150);
					return false;
				}
			}
		}
	}


	if (任务::任务是否已完成(1005004, vsk) || 任务::取出指定主线任务(1005004).dStep >= 1) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(0xF562D, vsk))
		{
			if (!任务::是否已接任务(0xF562D))
			{
				功能::到指定地点找NPC接任务2(2, 11014, 542, -3671, -4065, 0x5247, 0xF562D, 150);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xF562D);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{

						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点采集任务显示(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 3000, 0x1AF6B);
						return false;
					}

				}

			}

		}
		if (!任务::任务是否已完成(0xF562E, vsk))
		{
			if (!任务::是否已接任务(0xF562E))
			{
				功能::到指定地点找NPC接任务2(2, 11014, 2644, -2928, -4069, 0x5249, 0xF562E, 150);
				return false;
			}
		}

	}
	if (任务::任务是否已完成(1005004, vsk) || 任务::取出指定主线任务(1005004).dStep >= 5) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(0xF562E, vsk))
		{
			if (任务::是否已接任务(0xF562E))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xF562E);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						if (支线任务.子任务进度.size() == 2)
						{
							if (支线任务.子任务进度[1].dCur < 支线任务.子任务进度[1].dNeed)
							{
								坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
								功能::到指定地点采集(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 1000, 0x524A, 150, 100);
								return false;
							}
							if (支线任务.子任务进度[0].dCur < 支线任务.子任务进度[0].dNeed)
							{
								坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
								加入优先打怪ID(L"190244");
								功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 3000, 100, true);
								return false;
							}

						}

					}

				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 150);
					return false;
				}
			}
		}
		if (!任务::任务是否已完成(0xF562D, vsk))
		{
			if (任务::是否已接任务(0xF562D))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xF562D);
				if (支线任务.dState == 2)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务2(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 150);
					return false;
				}
			}
		}
	}

	return true;
}
bool 游戏::支线_世界2(vector<DWORD>& vsk)
{
	if (任务::任务是否已完成(705001, vsk) || 任务::取出指定主线任务(705001).dStep >= 1) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(0xAC260, vsk))
		{

			if (!任务::是否已接任务(0xAC260))
			{
				功能::到指定地点找NPC接任务2(2, 10701, -15322, 10312, 385, 0x500C, 0xAC260, 150);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xAC260);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						UI功能::内存按键(VK_F5);
						return false;

					}
				}
				else
				{
					任务::CALL_交任务(支线任务.dQuestId, -1);
					return false;
				}

			}


		}
	}
	if (任务::任务是否已完成(705001, vsk) || 任务::取出指定主线任务(705001).dStep >= 2) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(0xAC262, vsk))
		{
			if (!任务::是否已接任务(0xAC262))
			{
				功能::到指定地点找NPC接任务2(2, 10701, -9556, 14614, 384, 0x500E, 0xAC262, 150);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xAC262);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 支线任务.TargetId, 支线任务.dQuestId, -1, 25, 支线任务.dStep);
						return false;

					}
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25, 支线任务.dStep);
					return false;
					/*任务::CALL_交任务(支线任务.dQuestId, -1);
					return false;*/
				}

			}


		}
	}
	if (任务::任务是否已完成(702051, vsk) || 任务::取出指定主线任务(702052).dStep >= 1) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(0xAB6CC, vsk))
		{
			if (!任务::是否已接任务(0xAB6CC))
			{
				功能::到指定地点找NPC接任务2(3, 10721, 3612, 6362, 895, 0x4F5D, 0xAB6CC, 150);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xAB6CC);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点采集任务显示(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 2000, 0x11634);
						return false;

					}
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25, 支线任务.dStep);
					return false;
					/*任务::CALL_交任务(支线任务.dQuestId, -1);
					return false;*/
				}

			}


		}
	}
	if (任务::任务是否已完成(706002, vsk) || 任务::取出指定主线任务(706002).dStep >= 1) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(0xAC63B, vsk))
		{
			if (!任务::是否已接任务(0xAC63B))
			{
				功能::到指定地点找NPC接任务2(3, 10722, 4332, 5690, 1154, 0x4F79, 0xAC63B, 150);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xAC63B);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						if (支线任务.子任务进度[0].dCur < 支线任务.子任务进度[0].dNeed)
						{
							加入优先打怪ID(L"172350|172360");
							功能::移动打怪(6668, 8244, 1533, 100, 1000);
							return false;
						}
						if (支线任务.子任务进度[1].dCur < 支线任务.子任务进度[1].dNeed)
						{
							加入优先打怪ID(L"172360");
							功能::移动打怪(6668, 8244, 1533, 100, 1000);
							return false;
						}

					}
				}
				else
				{
					任务::CALL_交任务(支线任务.dQuestId, -1);
					return false;
					/*任务::CALL_交任务(支线任务.dQuestId, -1);
					return false;*/
				}

			}


		}
	}
	if (任务::任务是否已完成(706003, vsk) || 任务::取出指定主线任务(706003).dStep >= 3) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(0xAC63E, vsk))
		{
			if (!任务::是否已接任务(0xAC63E))
			{
				功能::到指定地点找NPC接任务2(3, 10722, 14032, 7396, 1024, 0x4F7C, 0xAC63E, 150);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xAC63E);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						if (支线任务.子任务进度[0].dCur < 支线任务.子任务进度[0].dNeed)
						{
							功能::到指定地点采集任务显示(3, 任务坐标.地图ID, 17196, 5050, 1146, 2000, 0x116F8);
							return false;
						}
						if (支线任务.子任务进度[1].dCur < 支线任务.子任务进度[1].dNeed)
						{
							加入优先打怪ID(L"172400");
							功能::移动打怪(17196, 5050, 1146, 100, 3000);
							return false;
						}

					}
				}
				else
				{
					任务::CALL_交任务(支线任务.dQuestId, -1);
					return false;
					/*任务::CALL_交任务(支线任务.dQuestId, -1);
					return false;*/
				}

			}


		}
		if (!任务::任务是否已完成(0xAC646, vsk))
		{
			if (!任务::是否已接任务(0xAC646))
			{
				功能::到指定地点找NPC接任务2(3, 10722, 14032, 7396, 1024, 0x4F7C, 0xAC646, 150);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xAC646);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						if (支线任务.子任务进度[0].dCur < 支线任务.子任务进度[0].dNeed)
						{
							功能::到指定地点采集任务显示(3, 任务坐标.地图ID, 12945, 11239, 895, 2000, 71417, 100, 250);
							return false;
						}
						if (支线任务.子任务进度[1].dCur < 支线任务.子任务进度[1].dNeed)
						{
							功能::到指定地点采集任务显示(3, 任务坐标.地图ID, 12945, 11239, 895, 2000, 71418, 250);
							return false;
						}

					}
				}
				//else
				//{
				//	任务::CALL_交任务(支线任务.dQuestId, -1);
				//	return false;
				//	/*任务::CALL_交任务(支线任务.dQuestId, -1);
				//	return false;*/
				//}

			}


		}
	}
	if (任务::任务是否已完成(706003, vsk) || 任务::取出指定主线任务(706003).dStep >= 6) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(0xAC646, vsk))
		{
			if (任务::是否已接任务(0xAC646))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xAC646);
				if (支线任务.dState == 2)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25, 支线任务.dStep);
					return false;
				}
			}
		}
	}
	if (任务::任务是否已完成(707003, vsk) || 任务::取出指定主线任务(707003).dStep >= 2) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(0xACA2E, vsk))
		{
			if (!任务::是否已接任务(0xACA2E))
			{
				功能::到指定地点找NPC接任务2(3, 10723, -16892, 12573, 1698, 0x4F93, 0xACA2E, 150);
				return false;
			}
		}
		if (!任务::任务是否已完成(0xACA2F, vsk))
		{
			if (!任务::是否已接任务(0xACA2F))
			{
				功能::到指定地点找NPC接任务2(3, 10723, -18564, 13739, 1600, 0x4F94, 0xACA2F, 150);
				return false;
			}
		}
		if (!任务::任务是否已完成(0xACA2E, vsk))
		{
			if (任务::是否已接任务(0xACA2E))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xACA2E);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点采集任务显示(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 3000, 0x117CB, 500, 100);
						return false;

					}
				}
			}
		}
		if (!任务::任务是否已完成(0xACA2E, vsk))
		{
			if (任务::是否已接任务(0xACA2E))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xACA2E);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						加入优先打怪ID(L"173280");
						功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 3000);
						return false;

					}
				}
			}
		}
	}
	if (任务::任务是否已完成(707003, vsk) || 任务::取出指定主线任务(707003).dStep >= 3) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(0xACA2F, vsk))
		{
			if (任务::是否已接任务(0xACA2F))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xACA2F);
				if (支线任务.dState == 2)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25, 支线任务.dStep);
					return false;
				}
			}
		}
		if (!任务::任务是否已完成(0xACA2E, vsk))
		{
			if (任务::是否已接任务(0xACA2E))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xACA2E);
				if (支线任务.dState == 2)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25, 支线任务.dStep);
					return false;
				}
			}
		}

	}
	//if (任务::任务是否已完成(705019, vsk)) //	//{
	//	if (!任务::任务是否已完成(0xAC264, vsk))//雨和星星和风   未写完
	//	{
	//		if (!任务::是否已接任务(0xAC264))
	//		{
	//			功能::到指定地点找NPC接任务2(3, 10701, -10335, 10438, -4, 0x506A, 0xAC264, 150);
	//			return false;
	//		}
	//		else
	//		{
	//			QuestInfo_ 支线任务 = 任务::取出指定支线任务(0xAC264);
	//			if (支线任务.dState == 1)
	//			{
	//				if (支线任务.dStep == 1)
	//				{				
	//					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
	//					功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 支线任务.TargetId, 支线任务.dQuestId, -1, 25, 支线任务.dStep);
	//					return false;
	//				}
	//				if (支线任务.dStep == 2)
	//				{
	//					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
	//					功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 支线任务.TargetId, 支线任务.dQuestId, -1, 25, 支线任务.dStep);
	//					return false;
	//				}
	//			}
	//		}
	//	}
	//}
	return true;
}
bool 游戏::支线_世界3(vector<DWORD>& vsk)
{
	if (任务::任务是否已完成(306002, vsk)) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(0x4ABBA, vsk))//雨和星星和风   未写完
		{
			if (!任务::是否已接任务(0x4ABBA))
			{
				功能::到指定地点找NPC接任务2(4, 10421, -15932, 12768, 1247, 0x46C7, 0x4ABBA, 150);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0x4ABBA);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 支线任务.TargetId, 支线任务.dQuestId, -1, 25, 支线任务.dStep);
						return false;
					}

				}
			}
		}
		if (!任务::任务是否已完成(0x4ABBB, vsk))//雨和星星和风   未写完
		{
			if (!任务::是否已接任务(0x4ABBB))
			{
				功能::到指定地点找NPC接任务2(4, 10421, -16144, 12711, 1246, 0x46CC, 0x4ABBB, 150);
				return false;
			}
		}
		if (!任务::任务是否已完成(0x4ABBA, vsk))//雨和星星和风   未写完
		{
			if (任务::是否已接任务(0x4ABBA))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0x4ABBA);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 2)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						加入优先打怪ID(L"141030|141040|141070|141050");
						功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 3000, 150);
						return false;
					}

				}
			}

		}
		if (!任务::任务是否已完成(0x4ABBB, vsk))//雨和星星和风   未写完
		{
			if (任务::是否已接任务(0x4ABBB))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0x4ABBB);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						if (支线任务.子任务进度.size() == 2)
						{
							if (支线任务.子任务进度[1].dCur < 支线任务.子任务进度[1].dNeed)
							{

								加入优先打怪ID(L"141070|141050");
								功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 3000, 150);
								return false;
							}

							if (支线任务.子任务进度[0].dCur == 0)
							{
								功能::到指定地点采集任务显示(4, 任务坐标.地图ID, -10927, 11193, 1335, 3000, 0xA496, 300, 100);
								return false;
								//-10927,11193,1335 iD=0xA496 
							}
						}

					}

				}
			}

		}
		if (!任务::任务是否已完成(0x4ABBA, vsk))//雨和星星和风   未写完
		{
			if (任务::是否已接任务(0x4ABBA))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0x4ABBA);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 3)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 支线任务.TargetId, 支线任务.dQuestId, -1, 25, 支线任务.dStep);
						return false;
					}
					if (支线任务.dStep == 4)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 支线任务.TargetId, 支线任务.dQuestId, -1, 25, 支线任务.dStep);
						return false;
					}
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25, 支线任务.dStep);
					return false;
				}
			}

		}
		if (!任务::任务是否已完成(0x4ABBB, vsk))//
		{
			if (任务::是否已接任务(0x4ABBB))
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0x4ABBB);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 2)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25, 支线任务.dStep);
						return false;
					}
					if (支线任务.dStep == 3)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点按G(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 150);
						return false;
					}
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25, 支线任务.dStep);
					return false;
				}
			}
		}
	}

	return true;
}
bool 游戏::支线_世界4(vector<DWORD>& vsk)
{
	if (任务::任务是否已完成(1101002, vsk)) //地址0x219CA950010 资源地址0x21A05377A80 任务ID C3CD1 类型0 步骤3 状态1 是否已做0 遇袭的要塞  
	{
		if (!任务::任务是否已完成(0x10D8E5, vsk))//雨和星星和风   未写完
		{
			if (!任务::是否已接任务(0x10D8E5))
			{
				功能::到指定地点找NPC接任务2(18, 11101, -955, -39607, 243, 0x59AA, 0x10D8E5, 150);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0x10D8E5);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						MyTrace(L"跟踪1");
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
						return false;
					}

				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25, 支线任务.dStep);
					return false;
				}
			}
		}
		if (!任务::任务是否已完成(0x10D8E6, vsk))//雨和星星和风   未写完
		{
			MyTrace(L"跟踪7");
			if (!任务::是否已接任务(0x10D8E6))
			{
				MyTrace(L"接任务");
				功能::到指定地点找NPC接任务2(18, 11113, 1503, 2867, 4120, 22270, 0x10D8E6, 150);
				return false;
			}
			else
			{
				MyTrace(L"做任务");
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0x10D8E6);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点采集任务显示(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 3000, 111350, 150, 200);
						return false;
					}
					if (支线任务.dStep == 2)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 支线任务.TargetId, 支线任务.dQuestId, -1, 25, 支线任务.dStep);
						return false;

					}
					if (支线任务.dStep == 3)
					{
						if (支线任务.子任务进度[0].dCur < 支线任务.子任务进度[0].dNeed)
						{
							坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
							objInfo_ 对象 = 环境::取指定任务显示对象信息(22594);
							if (对象.dResId != 22594)
							{
								对象 = 环境::取指定任务显示对象信息(22591);
								if (对象.dResId == 22591)
								{
									功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 3551, 9585, 4490, 22591, 支线任务.dQuestId, -1, 25, 支线任务.dStep);
									return false;
								}
								else
								{
									对象 = 环境::取指定任务显示对象信息(22593);
									if (对象.dResId == 22593)
									{
										功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 3642, 8620, 4490, 22593, 支线任务.dQuestId, -1, 25, 支线任务.dStep);
										return false;
									}
									else
									{
										功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 3514, 10215, 4490, 22594, 支线任务.dQuestId, -1, 25, 支线任务.dStep);
										return false;
									}

								}
							}
							else
							{
								功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 3514, 10215, 4490, 22594, 支线任务.dQuestId, -1, 25, 支线任务.dStep);
								return false;
							}

						}
						if (支线任务.子任务进度[1].dCur < 支线任务.子任务进度[1].dNeed)
						{
							坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
							加入优先打怪ID(L"213132|213142|213152");
							功能::移动打怪(5006, 9563, 4490, 100, 3000);
							return false;
						}
					}
					if (支线任务.dStep == 4)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
						return false;
					}
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25, 支线任务.dStep);
					return false;
				}
			}
		}
		if (!任务::任务是否已完成(0x10D8E7, vsk))//过去的青年 
		{
			MyTrace(L"跟踪8");
			if (!任务::是否已接任务(0x10D8E7))
			{
				功能::到指定地点找NPC接任务2(18, 11113, 7375, 8338, 4490, 22278, 0x10D8E7, 150);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0x10D8E7);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点采集任务显示(4, 任务坐标.地图ID, 7321, 8230, 4490, 3000, 111358, 150, 200);
						return false;
					}
					if (支线任务.dStep == 2)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
						return false;

					}
					if (支线任务.dStep == 3)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点采集任务显示(4, 任务坐标.地图ID, 12617, 6300, 3976, 3000, 111361, 300, 200);
						return false;
					}
					if (支线任务.dStep == 4)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
						return false;
					}
					if (支线任务.dStep == 5)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 支线任务.TargetId, 支线任务.dQuestId, -1, 25, 支线任务.dStep);
						return false;
					}
					if (支线任务.dStep == 6)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
						return false;
					}
					if (支线任务.dStep == 7)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
						return false;
					}
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25, 支线任务.dStep);
					return false;
				}
			}
		}
		if (!任务::任务是否已完成(0x10D8E8, vsk))//雨和星星和风   未写完
		{
			MyTrace(L"跟踪9");
			if (!任务::是否已接任务(0x10D8E8))
			{
				功能::到指定地点找NPC接任务2(18, 11113, 19303, 8900, 3466, 22271, 0x10D8E8, 150);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0x10D8E8);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
						return false;
					}
					if (支线任务.dStep == 2)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 支线任务.TargetId, 支线任务.dQuestId, -1, 25, 支线任务.dStep);
						return false;
					}
					if (支线任务.dStep == 3)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 支线任务.TargetId, 支线任务.dQuestId, -1, 25, 支线任务.dStep);
						return false;
					}
					if (支线任务.dStep == 4)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						加入优先打怪ID(L"213200|213210");
						功能::移动打怪(15814, 10311, 3978, 100, 3000);
						return false;
					}
					if (支线任务.dStep == 5)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
						return false;
					}
					if (支线任务.dStep == 6)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 支线任务.TargetId, 支线任务.dQuestId, -1, 25, 支线任务.dStep);
						return false;
					}
					if (支线任务.dStep == 7)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 支线任务.TargetId, 支线任务.dQuestId, -1, 25, 支线任务.dStep);
						return false;
					}
					if (支线任务.dStep == 8)
					{
						if (支线任务.子任务进度[0].dCur < 支线任务.子任务进度[0].dNeed)
						{
							坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
							加入优先打怪ID(L"213200|213210");
							功能::移动打怪(15814, 10311, 3978, 100, 3000);
							return false;
						}
						if (支线任务.子任务进度[1].dCur < 支线任务.子任务进度[1].dNeed)
						{
							坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
							功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 12556, 12007, 3978, 22267, 支线任务.dQuestId, -1, 25, 支线任务.dStep);
							return false;
						}
					}
					if (支线任务.dStep == 9)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 支线任务.TargetId, 支线任务.dQuestId, -1, 25, 支线任务.dStep);
						return false;
					}
				}
				else
				{

					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25, 支线任务.dStep);
					return false;

				}
			}
		}
		if (!任务::任务是否已完成(0x10D8E9, vsk))//雨和星星和风   未写完
		{
			MyTrace(L"跟踪10");
			if (!任务::是否已接任务(0x10D8E9))
			{
				功能::到指定地点找NPC接任务2(18, 11113, 10383, 15434, 3467, 22280, 0x10D8E9, 150);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0x10D8E9);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
						return false;
					}
					if (支线任务.dStep == 2)
					{

						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						加入优先打怪ID(L"213210|213200");
						功能::移动打怪(15306, 14058, 3977, 100, 3000);
						return false;
					}
					if (支线任务.dStep == 3)
					{
						if (支线任务.子任务进度[1].dCur < 支线任务.子任务进度[1].dNeed)
						{
							坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
							加入优先打怪ID(L"111313");
							功能::移动打怪(17074, 15298, 3978, 100, 3000);
							return false;
						}
						if (支线任务.子任务进度[0].dCur < 支线任务.子任务进度[0].dNeed)
						{
							坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
							加入优先打怪ID(L"213250|213200|213210|213020");
							功能::移动打怪(17170, 15503, 3978, 100, 3000);
							return false;
						}

					}
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25, 支线任务.dStep);
					return false;
				}
			}
		}
		if (!任务::任务是否已完成(0x10D8EA, vsk))//堕落骑士团的安息m
		{
			MyTrace(L"跟踪11");
			if (!任务::是否已接任务(0x10D8EA))
			{
				功能::到指定地点找NPC接任务2(18, 11113, 19541, 14149, 3975, 22283, 0x10D8EA, 150);
				return false;
			}
			else
			{
				QuestInfo_ 支线任务 = 任务::取出指定支线任务(0x10D8EA);
				if (支线任务.dState == 1)
				{
					if (支线任务.dStep == 1)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
						return false;
					}
					if (支线任务.dStep == 2)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 支线任务.TargetId, 支线任务.dQuestId, -1, 25, 支线任务.dStep);
						return false;
					}
					if (支线任务.dStep == 3)
					{
						if (支线任务.子任务进度[0].dCur < 支线任务.子任务进度[0].dNeed)
						{
							坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
							加入优先打怪ID(L"111369");
							功能::移动打怪(23897, 8234, 4233, 100, 3000);
							return false;
						}
						if (支线任务.子任务进度[1].dCur < 支线任务.子任务进度[1].dNeed)
						{
							坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
							加入优先打怪ID(L"213030|213040|213060|213050");
							功能::移动打怪(23897, 8234, 4233, 100, 3000);
							return false;
						}


					}
					if (支线任务.dStep == 4)
					{
						if (支线任务.子任务进度[1].dCur < 支线任务.子任务进度[1].dNeed)
						{
							坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
							加入优先打怪ID(L"213270");
							功能::移动打怪(27046, 15017, 4723, 100, 3000);
							return false;
						}
						if (支线任务.子任务进度[0].dCur < 支线任务.子任务进度[0].dNeed)
						{
							坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
							加入优先打怪ID(L"213260");
							功能::移动打怪(24336, 14918, 4747, 100, 3000);
							return false;
						}
						if (支线任务.子任务进度[2].dCur < 支线任务.子任务进度[2].dNeed)
						{
							坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
							加入优先打怪ID(L"213280");
							功能::移动打怪(23508, 16335, 4746, 100, 3000);
							return false;
						}


					}
					if (支线任务.dStep == 5)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 支线任务.TargetId, 支线任务.dQuestId, -1, 25, 支线任务.dStep);
						return false;
					}
					if (支线任务.dStep == 6)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 支线任务.dQuestId, -1, 25, 支线任务.dStep);
						return false;

					}
					if (支线任务.dStep == 7)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 支线任务.TargetId, 支线任务.dQuestId, -1, 25, 支线任务.dStep);
						return false;
					}
					if (支线任务.dStep == 8)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 支线任务.TargetId, 支线任务.dQuestId, -1, 25, 支线任务.dStep);
						return false;
					}
					if (支线任务.dStep == 9)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
						功能::寻路到副本(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z);
						return false;
					}
					if (支线任务.dStep == 10)
					{
						if (地图::取地图ID() == 11118)
						{
							本人::CALL_演奏乐谱(1);
							Sleep(10000);
							return false;
						}
						else
						{
							坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
							功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 支线任务.TargetId, 支线任务.dQuestId, -1, 25, 支线任务.dStep);
							return false;
						}
					}
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(支线任务.dQuestId, 支线任务.objBase, 支线任务.dResAddr);
					功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 22025, 支线任务.dQuestId, -1, 25, 支线任务.dStep);
					return false;
				}
			}
		}
	}

	return true;
}
bool 游戏::执行触发任务()
{
	QuestInfo_ 触发任务 = 任务::取出触发任务();
	if (触发任务.dQuestId != 0)
	{
		MyTrace(L"触发任务 [%s] Questid [%d]", 触发任务.QuestName, 触发任务.dQuestId);
		if (触发任务.dQuestId == 0xC40B9)
		{
			if (触发任务.dState == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(触发任务.dQuestId, 触发任务.objBase, 触发任务.dResAddr);
				加入优先打怪ID(L"180350|180340");
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 300, 1500, 150);
			}
			return false;
		}
		if (触发任务.dQuestId == 0xC42AE)
		{
			if (触发任务.dState == 1)
			{
				if (触发任务.子任务进度.size() == 2)
				{
					if (触发任务.子任务进度[0].dCur < 触发任务.子任务进度[0].dNeed)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(触发任务.dQuestId, 触发任务.objBase, 触发任务.dResAddr);
						加入优先打怪ID(L"180211");
						功能::移动打怪(10434, 8464, 1024, 300, 3000, 150);
					}
					if (触发任务.子任务进度[1].dCur < 触发任务.子任务进度[1].dNeed)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(触发任务.dQuestId, 触发任务.objBase, 触发任务.dResAddr);
						加入优先打怪ID(L"180360");
						功能::移动打怪(10434, 8464, 1024, 300, 3000, 150);
					}

				}

			}
			return false;
		}
		if (触发任务.dQuestId == 0xC42AF)
		{
			if (触发任务.dState == 1)
			{
				if (触发任务.子任务进度.size() == 2)
				{
					if (触发任务.子任务进度[0].dCur < 触发任务.子任务进度[0].dNeed)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(触发任务.dQuestId, 触发任务.objBase, 触发任务.dResAddr);
						加入优先打怪ID(L"180430|180431");
						功能::移动打怪(19854, 16477, 1531, 300, 3000, 150);
					}
					if (触发任务.子任务进度[1].dCur < 触发任务.子任务进度[1].dNeed)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(触发任务.dQuestId, 触发任务.objBase, 触发任务.dResAddr);
						加入优先打怪ID(L"180450|180451");
						功能::移动打怪(19854, 16477, 1531, 300, 3000, 150);
					}

				}
			}
			return false;
		}
		if (触发任务.dQuestId == 0xC5E05)
		{
			if (触发任务.dState == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(触发任务.dQuestId, 触发任务.objBase, 触发任务.dResAddr);
				加入优先打怪ID(L"182355");
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 300, 1500, 150);
				return false;
			}

		}
		if (触发任务.dQuestId == 0xC5E08)
		{
			if (触发任务.dState == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(触发任务.dQuestId, 触发任务.objBase, 触发任务.dResAddr);
				CString temp;
				temp.Format(L"%d", 触发任务.TargetId);
				加入优先打怪ID(temp);
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 300, 1500, 150);
				return false;
			}

		}
		if (触发任务.dQuestId == 810502)
		{
			if (触发任务.dState == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(触发任务.dQuestId, 触发任务.objBase, 触发任务.dResAddr);
				CString temp;
				temp.Format(L"%d", 触发任务.TargetId);
				加入优先打怪ID(temp);
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 300, 2000, 150);
				return false;
			}

		}
		if (触发任务.dQuestId == 812501)
		{
			if (触发任务.dState == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(触发任务.dQuestId, 触发任务.objBase, 触发任务.dResAddr);
				功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 触发任务.TargetId, 触发任务.dQuestId, -1, 25);
				return false;
			}
		}

		if (触发任务.dQuestId == 812502)
		{
			if (触发任务.dState == 1)
			{
				if (触发任务.dStep == 1)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(触发任务.dQuestId, 触发任务.objBase, 触发任务.dResAddr);
					加入优先打怪ID(L"183270|183280");
					功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 300, 2000, 150);
					return false;
				}
				if (触发任务.dStep == 2)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(触发任务.dQuestId, 触发任务.objBase, 触发任务.dResAddr);
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 触发任务.dQuestId, -1, 25);
					return false;
				}
			}
			else
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(触发任务.dQuestId, 触发任务.objBase, 触发任务.dResAddr);
				功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 触发任务.dQuestId, -1, 25);
				return false;
			}

		}
		if (触发任务.dQuestId == 815501)
		{
			if (触发任务.dState == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(触发任务.dQuestId, 触发任务.objBase, 触发任务.dResAddr);
				加入优先打怪ID(L"187070");
				功能::移动打怪(-11625, -15415, 1274, 100, 2000, 150);
				return false;
			}
		}
		if (触发任务.dQuestId == 815502)
		{
			if (触发任务.dState == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(触发任务.dQuestId, 触发任务.objBase, 触发任务.dResAddr);
				加入优先打怪ID(L"183670|183680");
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 2000, 150);
				return false;
			}
		}
		if (触发任务.dQuestId == 816501)
		{
			if (触发任务.dState == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(触发任务.dQuestId, 触发任务.objBase, 触发任务.dResAddr);
				加入优先打怪ID(L"183781|183821|183761|183831");
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 2000, 150);
				return false;
			}
		}
		if (触发任务.dQuestId == 816502)
		{
			if (触发任务.dState == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(触发任务.dQuestId, 触发任务.objBase, 触发任务.dResAddr);
				加入优先打怪ID(L"183820|183830");
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 2000, 150);
				return false;
			}
		}
		if (触发任务.dQuestId == 819509)
		{
			if (触发任务.dState == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(触发任务.dQuestId, 触发任务.objBase, 触发任务.dResAddr);
				加入优先打怪ID(L"184610");
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 2000, 150);
				return false;
			}
		}
		if (触发任务.dQuestId == 819501)
		{
			if (触发任务.dState == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(触发任务.dQuestId, 触发任务.objBase, 触发任务.dResAddr);
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 2000, 150);
				return false;
			}
		}
		if (触发任务.dQuestId == 819503)
		{
			if (触发任务.dState == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(触发任务.dQuestId, 触发任务.objBase, 触发任务.dResAddr);
				加入优先打怪ID(L"185090");
				功能::移动打怪(11562, 24795, 512, 100, 2000, 150);
				return false;
			}
		}
		if (触发任务.dQuestId == 819502)
		{
			if (触发任务.dState == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(触发任务.dQuestId, 触发任务.objBase, 触发任务.dResAddr);
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 2000, 150, true, 1000);
				return false;
			}
		}
		if (触发任务.dQuestId == 819507)
		{
			if (触发任务.dState == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(触发任务.dQuestId, 触发任务.objBase, 触发任务.dResAddr);
				if (触发任务.子任务进度[0].dCur == 0)
				{
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 11761, 53048, 512, 0x3B23, 触发任务.dQuestId, -1, 200);
					return false;
				}
				if (触发任务.子任务进度[0].dCur == 1)
				{
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 11423, 53056, 512, 0x3B26, 触发任务.dQuestId, -1, 200);
					return false;
				}
				if (触发任务.子任务进度[0].dCur == 2)
				{
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 11400, 52360, 512, 0x3B23, 触发任务.dQuestId, -1, 200);
					return false;
				}
				if (触发任务.子任务进度[0].dCur == 3)
				{
					功能::到指定地点找NPC交任务2(15, 任务坐标.地图ID, 11944, 52271, 512, 0x3B24, 触发任务.dQuestId, -1, 200);
					return false;
				}

			}
		}
		if (触发任务.dQuestId == 1002501)
		{
			if (触发任务.dState == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(触发任务.dQuestId, 触发任务.objBase, 触发任务.dResAddr);
				加入优先打怪ID(L"190180|190190");
				功能::移动打怪(21165, 24618, 586, 100, 2000, 150);
				return false;
			}
		}
		if (触发任务.dQuestId == 1003501)
		{
			if (触发任务.dState == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(触发任务.dQuestId, 触发任务.objBase, 触发任务.dResAddr);
				加入优先打怪ID(L"190700|190710");
				功能::移动打怪(9561, 19167, 459, 100, 2000, 150);
				return false;
			}
		}
		if (触发任务.QuestName == L"没有栅栏的监狱")
		{
			if (触发任务.dState == 1)
			{
				if (触发任务.dStep == 1)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(触发任务.dQuestId, 触发任务.objBase, 触发任务.dResAddr);
					功能::到指定地点按G(2, 任务坐标.地图ID, 12632, 11986, 2018, 100);
					return false;

				}
				if (触发任务.dStep == 2)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(触发任务.dQuestId, 触发任务.objBase, 触发任务.dResAddr);
					功能::到指定地点按G(2, 任务坐标.地图ID, 14150, 11220, 2560, 100);
					return false;

				}
			}
			return false;
		}
		if (触发任务.dQuestId == 1004502)
		{
			if (触发任务.dState == 1)
			{
				if (触发任务.dStep == 1)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(触发任务.dQuestId, 触发任务.objBase, 触发任务.dResAddr);
					功能::到指定地点按G(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 100);
					return false;

				}

			}
			return false;
		}
		if (触发任务.dQuestId == 1005501)
		{
			if (触发任务.dState == 1)
			{
				if (触发任务.dStep == 1)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(触发任务.dQuestId, 触发任务.objBase, 触发任务.dResAddr);
					if (触发任务.子任务进度[0].dCur == 0)
					{
						功能::到指定地点按G(2, 任务坐标.地图ID, 4053, 2927, -3556, 100);
						return false;
					}
					if (触发任务.子任务进度[0].dCur == 1)
					{
						功能::到指定地点按G(2, 任务坐标.地图ID, 3791, 3649, -3556, 100);
						return false;
					}
					if (触发任务.子任务进度[0].dCur == 2)
					{
						功能::到指定地点按G(2, 任务坐标.地图ID, 3218, 3947, -3556, 100);
						return false;
					}
				}

			}
		}
		if (触发任务.dQuestId == 706501)
		{
			if (触发任务.dState == 1)
			{
				if (触发任务.dStep == 1)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(触发任务.dQuestId, 触发任务.objBase, 触发任务.dResAddr);
					加入优先打怪ID(L"71425");
					功能::移动打怪(3531, 8637, 1149, 100, 1000, 150);
					return false;
				}

			}
			return false;
		}
		if (触发任务.dQuestId == 707501)
		{
			if (触发任务.dState == 1)
			{
				if (触发任务.dStep == 1)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(触发任务.dQuestId, 触发任务.objBase, 触发任务.dResAddr);
					加入优先打怪ID(L"173210|173220");
					功能::移动打怪(-10616, 4953, 1600, 100, 3000, 150);
					return false;
				}

			}
			return false;
		}
		if (触发任务.dQuestId == 306501)
		{
			if (触发任务.dState == 1)
			{
				if (触发任务.dStep == 1)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(触发任务.dQuestId, 触发任务.objBase, 触发任务.dResAddr);
					加入优先打怪ID(L"141070|141050");
					功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 3000, 150);
					return false;
				}

			}
			return false;
		}
	}

	return true;
}
bool 游戏::执行副本任务()
{
	QuestInfo_ 主线任务 = 任务::取出副本任务();
	MyTrace(L"任务ID %d<%I64X> 副本任务: %s 阶段%d 状态%d 当前地图 %d 子任务数量 %d 操作 %s", 主线任务.dQuestId, 主线任务.dQuestId, 主线任务.QuestName, 主线任务.dStep, 主线任务.dState, 地图::取地图ID(), 主线任务.子任务进度.size(), 主线任务.QuestOption);
	if (主线任务.dQuestId == 204002)//梅德提供了毒爪偷盗团头目藏身的洞穴位置.那个洞穴位于科尔兹森林附近，但好像还没有被警备队员们发现.<br>为了尽快找到钥之石板，你便匆忙赶往偷盗团藏身的洞穴.
	{
		if (主线任务.dStep == 1)
		{
			if (本人::取坐标().z > 1530)
			{
				MyTrace(L"分段1");
				功能::到指定地点按G(地图::取当前大陆ID(), 地图::取地图ID(), 15566, 11229, 1535, 50);
				return false;
			}
			if (本人::取坐标().z > 1200)
			{
				MyTrace(L"分段2");
				if (功能::移动打怪(16679, 11454, 1279.82, 0, 300))
				{
					功能::到指定地点按G(地图::取当前大陆ID(), 地图::取地图ID(), 16679, 11454, 1279.82, 50);
				}
				return false;
			}
		}
		if (主线任务.dStep == 2)
		{
			if (本人::取坐标().z > 1200)
			{
				MyTrace(L"分段2");
				if (功能::优先打怪(2000))
				{
					功能::到指定地点按G(地图::取当前大陆ID(), 地图::取地图ID(), 16679, 11454, 1280, 100);
				}
				return false;
			}
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"20718");
			功能::移动打怪(18712.5, 14512.8, 1024, 100, 3000, 100, true, 1000);
			return false;
		}
		if (主线任务.dStep == 4)
		{
			if (本人::取坐标().z < 1050)
			{
				MyTrace(L"分段2");

				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 150);
				return false;

			}
		}
		if (主线任务.dStep == 5)
		{
			CString temp;
			temp.Format(L"%d", 主线任务.TargetId);
			加入优先打怪ID(temp);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 1400);
			return false;
		}
		if (主线任务.dStep == 6)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (功能::优先破坏击打道具(3000))
			{
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 1400);
			}

			return false;
		}
		if (主线任务.dStep == 7)
		{
			if (主线任务.子任务进度.size() == 2)
			{
				if (主线任务.子任务进度[0].dCur < 主线任务.子任务进度[0].dNeed)
				{
					MyTrace(L"子任务进度 %s %d/%d TargetID:%d", 主线任务.子任务进度[0].任务描述, 主线任务.子任务进度[0].dCur, 主线任务.子任务进度[0].dNeed, 主线任务.子任务进度[0].TargetID);
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					CString temp;
					temp.Format(L"%d", 主线任务.子任务进度[0].TargetID);
					加入优先打怪ID(temp);
					功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 1400);

					return false;
				}
				if (主线任务.子任务进度[1].dCur < 主线任务.子任务进度[1].dNeed)
				{
					MyTrace(L"子任务进度 %s %d/%d TargetID:%d", 主线任务.子任务进度[1].任务描述, 主线任务.子任务进度[1].dCur, 主线任务.子任务进度[1].dNeed, 主线任务.子任务进度[1].TargetID);
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					CString temp;
					temp.Format(L"%d", 主线任务.子任务进度[1].TargetID);
					加入优先打怪ID(temp);
					功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 1400);
					return false;
				}
			}
		}
		if (主线任务.dStep == 8)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 150);
			return false;
		}
		if (主线任务.dStep == 9)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			CString temp;
			temp.Format(L"%d", 主线任务.TargetId);
			加入优先打怪ID(temp);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 1400);
			return false;
		}
	}
	if (主线任务.dQuestId == 0x10DA11)
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return false;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 200);
			return false;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 3000);
			return false;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (功能::优先破坏击打道具(2000))
			{
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 3000);
			}
			return false;
		}
		if (主线任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"213120");
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 3000);
			return false;
		}
		return false;
	}
	if (主线任务.dQuestId == 1108401)//被死亡侵蚀的空间
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (功能::优先破坏击打道具(2000))
			{
				功能::到指定地点(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			}
			return false;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"111717");
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 5000, true, 3000);
			return false;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (功能::优先破坏击打道具(5000))
			{
				功能::到指定地点(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			}
			return false;
		}
		if (主线任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);

			功能::到指定地点(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);

			return false;
		}
		if (主线任务.dStep == 6)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"");
			if (功能::优先破坏击打道具(5000))
			{
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 5000);
			}
			return false;
		}
		if (主线任务.dStep == 7)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"216013");
			if (功能::优先破坏击打道具(5000))
			{
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 5000);
			}
			return false;
		}
		if (主线任务.dStep == 8)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return false;
		}
		if (主线任务.dStep == 9)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"216013");
			if (功能::优先破坏击打道具(1000))
			{
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 2000);
			}
			return false;
		}
		if (主线任务.dStep == 10)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (功能::优先破坏击打道具(5000))
			{
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 2000);
			}
			return false;
		}
		if (主线任务.dStep == 11)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);

			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 2000);

			return false;
		}
		if (主线任务.dStep == 12)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点采集任务显示(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 3000, 0x1B458);
			return false;
		}
		if (主线任务.dStep == 13)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return false;
		}
		if (主线任务.dStep == 14)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (钓鱼::getquickSlotFrameType() == 6)
			{

				if (功能::到指定地点(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 100, true))
				{
					UI功能::内存按键('R');
				}
			}
			else
			{
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 3000);
			}

			return false;
		}
		if (主线任务.dStep == 15)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (钓鱼::getquickSlotFrameType() == 6)
			{

				if (功能::到指定地点(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 100, true))
				{
					UI功能::内存按键('R');
				}
			}
			else
			{
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 3000);
			}

			return false;
		}
	}
	if (主线任务.dQuestId == 1108402)
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 3000);
			return false;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 3000);
			return false;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return false;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return false;
		}
		if (主线任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 2000);
			return false;
		}
		if (主线任务.dStep == 6)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"216090|216060");
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 3000);
			return false;
		}
		if (主线任务.dStep == 7)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"216150");
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 3000);
			return false;
		}
		if (主线任务.dStep == 8)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"216030");
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 3000);
			return false;
		}
	}
	if (主线任务.dQuestId == 405401)//影子市场 1D<62F99>
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 2)
		{
			if (主线任务.子任务进度[0].dCur == 0)
			{
				MyTrace(L"子任务进度 %s %d/%d TargetID:%d", 主线任务.子任务进度[0].任务描述, 主线任务.子任务进度[0].dCur, 主线任务.子任务进度[0].dNeed, 主线任务.子任务进度[0].TargetID);
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.子任务进度[1].dCur == 0)
			{
				MyTrace(L"子任务进度 %s %d/%d TargetID:%d", 主线任务.子任务进度[1].任务描述, 主线任务.子任务进度[1].dCur, 主线任务.子任务进度[1].dNeed, 主线任务.子任务进度[1].TargetID);
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.子任务进度[2].dCur == 0)
			{
				MyTrace(L"子任务进度 %s %d/%d TargetID:%d", 主线任务.子任务进度[1].任务描述, 主线任务.子任务进度[1].dCur, 主线任务.子任务进度[1].dNeed, 主线任务.子任务进度[1].TargetID);
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return false;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(14, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return false;
		}
		if (主线任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return false;
		}
		if (主线任务.dStep == 6)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			//加入优先打怪ID(L"216150");
			//功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 3000);
			功能::优先打怪(500);
			return false;
		}
		if (主线任务.dStep == 7)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, -9028, 23595, 293.626, 50);
			return false;
		}
		if (主线任务.dStep == 8)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return false;
		}
		if (主线任务.dStep == 9)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return false;
		}
		if (主线任务.dStep == 10)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return false;
		}
		if (主线任务.dStep == 11)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(-6081.000, 21685.000, 489.626, 100, 3000);
			return false;
		}
		if (主线任务.dStep == 12)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(-6081.000, 21685.000, 489.626, 100, 3000);
			return false;
		}
		if (主线任务.dStep == 13)
		{
			if (主线任务.子任务进度[0].dCur == 0)
			{
				MyTrace(L"子任务进度 %s %d/%d TargetID:%d", 主线任务.子任务进度[0].任务描述, 主线任务.子任务进度[0].dCur, 主线任务.子任务进度[0].dNeed, 主线任务.子任务进度[0].TargetID);
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.子任务进度[1].dCur == 0)
			{
				MyTrace(L"子任务进度 %s %d/%d TargetID:%d", 主线任务.子任务进度[1].任务描述, 主线任务.子任务进度[1].dCur, 主线任务.子任务进度[1].dNeed, 主线任务.子任务进度[1].TargetID);
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.子任务进度[2].dCur == 0)
			{
				MyTrace(L"子任务进度 %s %d/%d TargetID:%d", 主线任务.子任务进度[1].任务描述, 主线任务.子任务进度[1].dCur, 主线任务.子任务进度[1].dNeed, 主线任务.子任务进度[1].TargetID);
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
		}
		if (主线任务.dStep == 14)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return false;
		}
		if (主线任务.dStep == 15)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 3000);//如果不对 就换这个坐标  -9742.903,22319.068,236.890
			return false;
		}
		if (主线任务.dStep == 16)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, -10308, 23325, -79, 50);
			return false;
		}
		if (主线任务.dStep == 17)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 3000);
			return false;
		}
		if (主线任务.dStep == 18)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			//功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 3000);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 3000);
			return false;
		}
		if (主线任务.dStep == 19)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return false;
		}
		if (主线任务.dStep == 20)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (主线任务.子任务进度[0].dCur < 主线任务.子任务进度[0].dNeed)
			{
				//加入优先打怪ID(L"71616");
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 3000);
				return false;
			}
			return false;
		}
		if (主线任务.dStep == 21)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			//功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 3000);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 3000);
			return false;
		}
		if (主线任务.dStep == 22)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return false;
		}
	}
	if (主线任务.dQuestId == 406401)// :宿敌 1D<63381>
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return false;
		}

	}
	if (主线任务.dQuestId == 407401)// :红幕之内  整体流程弄完之后在回头写
	{
		if (主线任务.dStep == 1)
		{
			ActorInfo_ 角色信息 = 本人::取角色信息();
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点采集(6, 10331, 3563.000, 8321.000, 4333.954, 5000, 0x7BEB); //类型6
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G_无打怪(6, 10331, 任务坐标.x, 任务坐标.y, 任务坐标.z, 100);
			任务流程 = 0;
			return false;
		}
		if (主线任务.dStep == 3)
		{
			MyTrace(L"Step3 任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (任务流程 == 0)
			{
				if (功能::到指定地点(任务坐标.大陆ID, 任务坐标.地图ID, 5648, 6842, 4331.8, 50, true))
				{
					任务流程 = 1;
					MyTrace(L"Step3        任务流程 %d", 任务流程);
					Sleep(7000);
				}
				//功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			}
			if (任务流程 == 1)
			{
				if (功能::到指定地点(任务坐标.大陆ID, 任务坐标.地图ID, 7178, 6847, 4338.56, 300, true))
				{
					任务流程 = 2;
					MyTrace(L"Step3        任务流程 %d", 任务流程);
					Sleep(9000);
				}
			}
			return false;
		}
		if (主线任务.dStep == 4)
		{
			MyTrace(L"Step4 任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (任务流程 == 2)
			{
				if (功能::到指定地点(任务坐标.大陆ID, 任务坐标.地图ID, 6417, 6919, 4343.23, 50, true))
				{
					任务流程 = 3;
					MyTrace(L"Step4        任务流程 %d", 任务流程);
					Sleep(500);
				}
				//功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			}
			if (任务流程 == 3)
			{
				if (功能::到指定地点(任务坐标.大陆ID, 任务坐标.地图ID, 6517, 7499, 4338.56, 50, true))
				{
					任务流程 = 4;
					MyTrace(L"Step4        任务流程 %d", 任务流程);
					Sleep(200);
				}
			}
			if (任务流程 == 4)
			{
				if (功能::到指定地点(任务坐标.大陆ID, 任务坐标.地图ID, 6785, 7841, 4338.56, 50, true))
				{
					任务流程 = 0;
					MyTrace(L"Step4        任务流程 %d", 任务流程);
					Sleep(2000);
				}
			}
			return false;
		}
		if (主线任务.dStep == 5)
		{
			任务流程 = 0;
			MyTrace(L"Step5 任务流程 %d", 任务流程);
			if (主线任务.子任务进度[0].dCur == 0)
			{
				MyTrace(L"子任务%d进度 %s %d/%d TargetID:%d", 0, 主线任务.子任务进度[0].任务描述, 主线任务.子任务进度[0].dCur, 主线任务.子任务进度[0].dNeed, 主线任务.子任务进度[0].TargetID);
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 主线任务.dQuestId, -1, 50);
				return false;
			}
			if (主线任务.子任务进度[1].dCur == 0)
			{
				MyTrace(L"子任务%d进度 %s %d/%d TargetID:%d", 1, 主线任务.子任务进度[1].任务描述, 主线任务.子任务进度[1].dCur, 主线任务.子任务进度[1].dNeed, 主线任务.子任务进度[1].TargetID);
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 主线任务.dQuestId, -1, 50);
				return false;
			}
		}
		if (主线任务.dStep == 6)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G_无打怪(6, 10331, 任务坐标.x, 任务坐标.y, 任务坐标.z, 100);
			return false;
		}
		if (主线任务.dStep == 7)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G_无打怪(6, 10331, 任务坐标.x, 任务坐标.y, 任务坐标.z, 100);
			return false;
		}
		if (主线任务.dStep == 8)
		{
			MyTrace(L"Step8 任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (任务流程 == 0)
			{
				MyTrace(L"Step8        任务流程 %d", 任务流程);
				if (功能::到指定地点(任务坐标.大陆ID, 任务坐标.地图ID, 6750, 7640, 4338.56, 50, true))
				{
					任务流程 = 1;
				}
			}
			if (任务流程 == 1)
			{
				MyTrace(L"Step8        任务流程 %d", 任务流程);
				if (功能::范围内是否警备兵(6518, 7049, 4338.56, 100, 131222))//远来是！
				{
					任务流程 = 2;
					Sleep(6000);//200
				}
			}
			if (任务流程 == 2)
			{
				MyTrace(L"Step8        任务流程 %d", 任务流程);
				if (功能::到指定地点(任务坐标.大陆ID, 任务坐标.地图ID, 6528, 7412, 4338.56, 50, true))
				{
					任务流程 = 3;
					Sleep(500);
				}
			}
			if (任务流程 == 3)
			{
				MyTrace(L"Step8        任务流程 %d", 任务流程);
				if (功能::到指定地点(任务坐标.大陆ID, 任务坐标.地图ID, 6429, 6885, 4343.23, 50, true))
				{
					任务流程 = 4;
					Sleep(200);
				}
			}
			if (任务流程 == 4)
			{
				MyTrace(L"Step8        任务流程 %d", 任务流程);
				if (功能::到指定地点(任务坐标.大陆ID, 任务坐标.地图ID, 7296, 6705, 4388.62, 50, true))
				{
					任务流程 = 5;
					Sleep(500);
				}
			}
			if (任务流程 == 5)
			{
				MyTrace(L"Step8        任务流程 %d", 任务流程);
				if (功能::到指定地点(任务坐标.大陆ID, 任务坐标.地图ID, 7728, 6711, 4466.11, 50, true))
				{
					任务流程 = 6;
					Sleep(200);
				}
			}
			if (任务流程 == 6)
			{
				MyTrace(L"Step8        任务流程 %d", 任务流程);
				if (功能::到指定地点(任务坐标.大陆ID, 任务坐标.地图ID, 7683, 6044, 4697, 50, true))
				{
					任务流程 = 7;
				}
			}
			if (任务流程 == 7)
			{
				MyTrace(L"Step8        任务流程 %d", 任务流程);
				//功能::范围内是否警备兵(7749.000, 5544.000, 4733.580, 300, 131224)返回false，  就走到这个坐标 角色坐标 8115.000,5473.000,4744.053 
				//功能::范围内是否警备兵(8087.000, 5138.000, 4744.829, 300, 131224)返回false，  就走到任务坐标 
				bool 判断1 = !功能::范围内是否警备兵(7755, 5480, 4744.05, 400, 131224);
				bool 判断2 = !功能::范围内是否警备兵(7727, 5461, 4744.05, 400, 131224);
				MyTrace(L"Step8    警卫判断结果   判断1 %d  判断2 %d", 判断1, 判断2);
				if (判断1 || 判断2)
				{
					任务流程 = 8;
				}
			}
			if (任务流程 == 8)
			{
				MyTrace(L"Step8        任务流程 %d", 任务流程);
				if (功能::到指定地点(任务坐标.大陆ID, 任务坐标.地图ID, 7545, 5027, 4742.73, 50, true))
				{
					任务流程 = 9;
					Sleep(200);
				}
			}
			if (任务流程 == 9)
			{
				MyTrace(L"Step8        任务流程 %d", 任务流程);
				bool 判断1 = !功能::范围内是否警备兵(8193, 4528, 4741, 300, 131224);
				bool 判断2 = !功能::范围内是否警备兵(7723, 5718, 4697, 100, 131224);
				bool 判断3 = !功能::范围内是否警备兵(8021, 4724, 4741, 300, 131224);
				bool 判断4 = !功能::范围内是否警备兵(8398, 5240, 4743.52, 300, 131224);
				bool 判断5 = !功能::范围内是否警备兵(8281.99, 4409.66, 4741, 300, 131224);
				MyTrace(L"Step8    警卫判断结果   判断1 %d  判断2 %d  判断3 %d  判断4 %d  判断5 %d", 判断1, 判断2, 判断3, 判断4, 判断5);
				if (判断1 && 判断2 && 判断3 && 判断4 && 判断5)
				{
					任务流程 = 10;
				}
			}
			if (任务流程 == 10)
			{
				MyTrace(L"Step8        任务流程 %d", 任务流程);
				if (功能::到指定地点(任务坐标.大陆ID, 任务坐标.地图ID, 8400, 4790, 4743.52, 50, true))
				{
					任务流程 = 11;
					Sleep(1000);
				}
			}
			if (任务流程 == 11)
			{
				MyTrace(L"Step8        任务流程 %d", 任务流程);
				if (功能::到指定地点(任务坐标.大陆ID, 任务坐标.地图ID, 7995.35, 4592.81, 4741, 50, true))
				{
					任务流程 = 12;
					Sleep(1000);
				}
			}
			if (任务流程 == 12)
			{
				MyTrace(L"Step8        任务流程 %d", 任务流程);
				功能::到指定地点(任务坐标.大陆ID, 任务坐标.地图ID, 7346, 5244, 4745, 50, true);
			}
			return false;
		}
		if (主线任务.dStep == 9)
		{
			任务流程 = 0;
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 7346, 5244, 4745, 0, 主线任务.dQuestId, -1, 50);
			return false;
		}
		if (主线任务.dStep == 10)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (任务流程 == 0)
			{
				MyTrace(L"Step10        任务流程 %d", 任务流程);
				bool 判断1 = !功能::范围内是否警备兵(7975, 5130, 4744.83, 300, 131224);
				bool 判断2 = !功能::范围内是否警备兵(7803, 5476, 4744.05, 300, 131224);
				MyTrace(L"Step10    警卫判断结果   判断1 %d  判断2 %d ", 判断1, 判断2);
				if (判断1 && 判断2)
				{
					if (功能::到指定地点(任务坐标.大陆ID, 任务坐标.地图ID, 7983, 5497, 4744.05, 50, true))
					{
						任务流程 = 1;
						Sleep(1000);
					}
				}
			}
			if (任务流程 == 1)
			{
				MyTrace(L"Step10        任务流程 %d", 任务流程);
				bool 判断1 = 功能::范围内是否警备兵(7719.92, 5713.94, 4697, 200, 131224);
				bool 判断2 = 功能::范围内是否警备兵(7864.4, 4727.05, 4741, 200, 131224);
				bool 判断3 = 功能::范围内是否警备兵(8862.5, 4598.91, 4744.93, 200, 131224);
				MyTrace(L"Step10    警卫判断结果   判断1 %d  判断2 %d  判断3 %d  ", 判断1, 判断2, 判断3);
				if (判断1 && 判断2 && 判断3)
				{
					任务流程 = 2;
				}
			}

			if (任务流程 == 2)
			{
				MyTrace(L"Step10        任务流程 %d", 任务流程);
				if (功能::到指定地点(任务坐标.大陆ID, 任务坐标.地图ID, 8905, 5141, 4750.82, 50, true))
				{
					任务流程 = 3;
					Sleep(1000);
				}
			}
			if (任务流程 == 3)
			{
				MyTrace(L"Step10        任务流程 %d", 任务流程);
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 100);
			}
			return false;
		}
		if (主线任务.dStep == 11)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (任务流程 == 3)
			{
				MyTrace(L"Step11        任务流程 %d", 任务流程);
				bool 判断1 = !功能::范围内是否警备兵(8717, 4481, 4744.95, 200, 131224);
				MyTrace(L"Step12    警卫判断结果   判断1 %d  ", 判断1);
				if (判断1)
				{
					任务流程 = 4;
				}
			}
			if (任务流程 == 4)
			{
				MyTrace(L"Step11        任务流程 %d", 任务流程);
				if (功能::到指定地点(任务坐标.大陆ID, 任务坐标.地图ID, 8716, 4575, 4744.95, 50, true))
				{
					任务流程 = 5;
					Sleep(500);
				}
			}
			if (任务流程 == 5)
			{
				MyTrace(L"Step11        任务流程 %d", 任务流程);
				if (功能::到指定地点(任务坐标.大陆ID, 任务坐标.地图ID, 8866, 4357, 4744.95, 50, true))
				{
					任务流程 = 6;
					Sleep(500);
				}
			}
			if (任务流程 == 6)
			{
				MyTrace(L"Step11        任务流程 %d", 任务流程);
				if (功能::到指定地点(任务坐标.大陆ID, 任务坐标.地图ID, 9354, 4233, 4682.6, 50, true))
				{
					任务流程 = 7;
					Sleep(500);
				}
			}
			if (任务流程 == 7)
			{
				MyTrace(L"Step11        任务流程 %d", 任务流程);
				功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 9354, 4233, 4682.6, 100);
				任务流程 = 0;
			}
			return false;
		}
		if (主线任务.dStep == 12)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (任务流程 == 0)
			{
				MyTrace(L"Step12        任务流程 %d", 任务流程);
				bool 判断1 = 功能::范围内是否警备兵(8191.94, 4970.83, 4745.49, 200, 131224);
				bool 判断2 = 功能::范围内是否警备兵(8635.85, 5583.67, 4745.52, 100, 131224);
				bool 判断3 = 功能::范围内是否警备兵(8473, 4514.11, 4740.89, 100, 131224);
				MyTrace(L"Step12    警卫判断结果   判断1 %d  判断2 %d  判断3 %d  ", 判断1, 判断2, 判断3);
				if (判断1 && 判断2 && 判断3)
				{
					任务流程 = 1;
				}
			}
			if (任务流程 == 1)
			{
				MyTrace(L"Step12        任务流程 %d", 任务流程);
				if (功能::到指定地点(任务坐标.大陆ID, 任务坐标.地图ID, 8789, 4497, 4744.95, 50, true))
				{
					任务流程 = 2;
					Sleep(11000);
				}
			}
			if (任务流程 == 2)
			{
				MyTrace(L"Step12        任务流程 %d", 任务流程);
				if (功能::到指定地点(任务坐标.大陆ID, 任务坐标.地图ID, 8470, 6036, 4744.55, 50, true))
				{
					任务流程 = 3;
				}
			}
			if (任务流程 == 3)
			{
				MyTrace(L"Step12        任务流程 %d", 任务流程);
				功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 8470, 6036, 4744.55, 100);
				任务流程 = 4;
			}
			if (任务流程 == 4)
			{
				MyTrace(L"Step12        任务流程 %d", 任务流程);
				bool 判断1 = 功能::范围内是否警备兵(7894, 4854, 4744.829, 300, 131224);//  8713.11, 4381.14, 4744.86
				bool 判断2 = 功能::范围内是否警备兵(8126, 5021, 4744.829, 200, 131224);//   8134.02, 4983.01, 4744.83
				bool 判断3 = 功能::范围内是否警备兵(8589, 4350, 4744.952, 200, 131224);//   7887.23, 4877.73, 4744.65
				MyTrace(L"Step12    警卫判断结果   判断1 %d  判断2 %d  判断3 %d  ", 判断1, 判断2, 判断3);
				if (判断1 && 判断2 && 判断3)
				{
					任务流程 = 5;
				}
			}
			if (任务流程 == 5)
			{
				MyTrace(L"Step11        任务流程 %d", 任务流程);
				if (功能::到指定地点(任务坐标.大陆ID, 任务坐标.地图ID, 8516.000, 5006.000, 4750.822, 50, true))//7983, 5497, 4744.05
				{
					任务流程 = 6;
					Sleep(1000);
				}
			}
			if (任务流程 == 6)
			{
				MyTrace(L"Step11        任务流程 %d", 任务流程);
				bool 判断1 = 功能::范围内是否警备兵(7712, 5851, 4697, 100, 131224);
				MyTrace(L"Step12    警卫判断结果   判断1 %d  ", 判断1);
				if (判断1)
				{
					任务流程 = 7;
				}
			}
			if (任务流程 == 7)
			{
				MyTrace(L"Step11        任务流程 %d", 任务流程);
				if (功能::到指定地点(任务坐标.大陆ID, 任务坐标.地图ID, 7336, 5273, 4745, 50, true))
				{
					任务流程 = 8;
					Sleep(1000);
				}
			}
			if (任务流程 == 8)
			{
				MyTrace(L"Step11        任务流程 %d", 任务流程);
				坐标_ 任务坐标2 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务2(任务坐标2.大陆ID, 任务坐标2.地图ID, 任务坐标2.x, 任务坐标2.y, 任务坐标2.z, 0, 主线任务.dQuestId, -1, 50);
				任务流程 = 9;
			}

		}
		if (主线任务.dStep == 13)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (任务流程 == 4)
			{
				MyTrace(L"Step11        任务流程 %d", 任务流程);
				bool 判断1 = 功能::范围内是否警备兵(8713.11, 4381.14, 4744.86, 200, 131224);
				bool 判断2 = 功能::范围内是否警备兵(8134.02, 4983.01, 4744.83, 100, 131224);
				bool 判断3 = 功能::范围内是否警备兵(7887.23, 4877.73, 4744.65, 100, 131224);
				MyTrace(L"Step12    警卫判断结果   判断1 %d  判断2 %d  判断3 %d  ", 判断1, 判断2, 判断3);
				if (判断1 && 判断2 && 判断3)
				{
					任务流程 = 5;
				}
			}
			if (任务流程 == 5)
			{
				MyTrace(L"Step11        任务流程 %d", 任务流程);
				if (功能::到指定地点(任务坐标.大陆ID, 任务坐标.地图ID, 7737, 6436, 4549.89, 50, true))
				{
					任务流程 = 6;
					Sleep(1000);
				}
			}
			if (任务流程 == 6)
			{
				MyTrace(L"Step11        任务流程 %d", 任务流程);
				if (功能::到指定地点(任务坐标.大陆ID, 任务坐标.地图ID, 9015, 7965, 4082, 50, true))
				{
					任务流程 = 0;
					Sleep(1000);
				}
			}
		}
	}
	if (主线任务.dQuestId == 408401)// 莱卡瑟斯监视塔
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return false;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return false;
		}
		if (主线任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return false;
		}
		if (主线任务.dStep == 6)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return false;
		}
		if (主线任务.dStep == 7)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return false;
		}
		if (主线任务.dStep == 8)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 7279, 10751, 3456, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return false;
		}
		if (主线任务.dStep == 9)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 1000, 500);
			return false;
		}
		if (主线任务.dStep == 10)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return false;
		}

	}
	if (主线任务.dQuestId == 408402)// 莱卡瑟斯监视塔
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 1000, 500);
			return false;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 1000, 500);
			return false;
		}
		if (主线任务.dStep == 3)
		{
			MyTrace(L"Step3 任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (任务流程 == 0)
			{
				//功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, -6198.000, 2455.000, 289.000, 100);

				if (功能::到指定地点(任务坐标.大陆ID, 任务坐标.地图ID, -6135.000, 2385.000, 289.000, 50, true))
				{
					UI功能::内存按键(DWORD('G'));
					Sleep(500);
					UI功能::内存按键(DWORD('G'));
					Sleep(500);
					任务流程 = 1;
					MyTrace(L"Step3        任务流程 %d", 任务流程);
					Sleep(5000);
				}
			}
			if (任务流程 == 1)
			{
				if (功能::移动打怪(-4214, 3048, 289, 50, 1000, 500))
				{
					任务流程 = 2;
					MyTrace(L"Step3        任务流程 %d", 任务流程);
				}
			}
			if (任务流程 == 2)
			{
				if (功能::移动打怪(-2216.05, 1417.62, 415.535, 50, 1000, 500))
				{
					任务流程 = 3;
					MyTrace(L"Step3        任务流程 %d", 任务流程);
				}
			}
			if (任务流程 == 3)
			{
				if (功能::移动打怪(-812, -215, 289, 50, 1000, 500))
				{
					任务流程 = 3;
					MyTrace(L"Step3        任务流程 %d", 任务流程);
				}
			}
			return false;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 3000, 500);
			任务流程 = 0;
			return false;
		}
		if (主线任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(-208.000, -3302.000, 433.000, 50, 1000, 500);
			return false;
		}
		if (主线任务.dStep == 6)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 1000, 500);
			return false;
		}
		if (主线任务.dStep == 7)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 1000, 500);
			return false;
		}
		if (主线任务.dStep == 8)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return false;
		}
		if (主线任务.dStep == 9)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 1000, 500);
			return false;
		}
		if (主线任务.dStep == 10)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(2531.000, -3284.000, -327.000, 50, 1000, 500);
			return false;
		}
		if (主线任务.dStep == 11)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 1000, 500);
			return false;
		}
		if (主线任务.dStep == 12)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (任务流程 == 0)
			{
				if (功能::到指定地点(任务坐标.大陆ID, 任务坐标.地图ID, 2898, -3703, -327, 50, true))
				{
					UI功能::内存按键(DWORD('G'));
					Sleep(500);
					UI功能::内存按键(DWORD('G'));
					Sleep(500);
					任务流程 = 1;
					MyTrace(L"Step3        任务流程 %d", 任务流程);
					Sleep(5000);
				}
			}
			if (任务流程 == 1)
			{
				功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			}

			return false;
		}
		if (主线任务.dStep == 13)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (任务流程 == 2)
			{
				if (功能::到指定地点(任务坐标.大陆ID, 任务坐标.地图ID, 2168.000, -237.000, -207.000, 50, true))
				{
					任务流程 = 3;
					MyTrace(L"Step3        任务流程 %d", 任务流程);
				}
			}
			if (任务流程 == 3)
			{
				if (功能::到指定地点(任务坐标.大陆ID, 任务坐标.地图ID, -943.000, -73.000, 289.000, 50, true))
				{
					任务流程 = 4;
					MyTrace(L"Step3        任务流程 %d", 任务流程);
				}
			}
			if (任务流程 == 4)
			{
				if (功能::到指定地点(任务坐标.大陆ID, 任务坐标.地图ID, -309.000, 1476.000, 432.000, 50, true))
				{
					UI功能::内存按键(DWORD('G'));
					Sleep(500);
					UI功能::内存按键(DWORD('G'));
					Sleep(500);
					任务流程 = 5;
					MyTrace(L"Step3        任务流程 %d", 任务流程);
					Sleep(5000);
				}
			}//
			if (任务流程 == 5)
			{
				if (功能::移动打怪(-247.661, 2047.047, 433.000, 50, 3300, 500))
				{
					任务流程 = 6;
					MyTrace(L"Step3        任务流程 %d", 任务流程);
				}
			}//-309.000,1476.000,432.000
			if (任务流程 == 6)
			{
				if (功能::到指定地点(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50, true))
				{
					任务流程 = 7;
					MyTrace(L"Step3        任务流程 %d", 任务流程);
				}
			}//-309.000,1476.000,432.000
			return false;
		}
		if (主线任务.dStep == 14)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 5000, 500);
			任务流程 = 0;
			return false;
		}
		if (主线任务.dStep == 15)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (任务流程 == 0)
			{
				if (功能::到指定地点(任务坐标.大陆ID, 任务坐标.地图ID, -42.000, 5490.000, 561.000, 50, true))
				{
					UI功能::内存按键(DWORD('G'));
					Sleep(500);
					UI功能::内存按键(DWORD('G'));
					Sleep(500);
					任务流程 = 1;
					MyTrace(L"Step3        任务流程 %d", 任务流程);
					Sleep(5000);
				}
			}//
			if (任务流程 == 1)
			{
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 1000, 500);
			}

			return false;
		}
		if (主线任务.dStep == 16)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 1000, 500);
			return false;
		}
		if (主线任务.dStep == 17)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 1000, 500);
			return false;
		}
		if (主线任务.dStep == 18)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return false;
		}

	}
	if (主线任务.dQuestId == 407403)// :407403<6376B> QuestName:罪和罚 阶段
	{
		if (主线任务.dStep == 1)
		{
			MyTrace(L"Step1        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(16108.6, 8007.48, 4685.07, 50, 1000, 500);
			return false;
		}
		if (主线任务.dStep == 2)
		{
			MyTrace(L"Step1        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 1000, 500);
			return false;
		}
		if (主线任务.dStep == 3)
		{
			MyTrace(L"Step1        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return false;
		}
		if (主线任务.dStep == 4)
		{
			MyTrace(L"Step1        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return false;
		}


	}
	if (主线任务.dQuestId == 409401)// :409401<63F39> QuestName:瑟克塞德圣殿 
	{
		if (主线任务.dStep == 1)
		{
			MyTrace(L"Step1        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 2)
		{
			MyTrace(L"Step2        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (地图::指定地点是否可到达_M(2328.000, 4864.000, -957.000))
			{
				if (地图::指定地点是否可到达_M(5281.210, 3931.457, -505.698))// 5931.131,4060.946,-509.850
				{
					//功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);			

					if (地图::指定地点是否可到达_M(5931.131, 4060.946, -509.850))
					{
						功能::移动打怪(5177.000, 4122.000, -505.698, 50, 8000, 500);
					}
					else
					{
						功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 5384.5, 4131.43, -512, 50);
					}

				}
				else
				{
					功能::移动打怪(3394.000, 5315.000, -765.000, 50, 8000, 500);
					//功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 3394.000, 5315.000, -765.000, 50);
				}
			}
			else
			{
				if (功能::到指定地点(任务坐标.大陆ID, 任务坐标.地图ID, 2176, 4391, -949.698, 50))
				{
					清理击打道具(2176, 4391, -949.698, 500, 500);
				}
			}
			return false;
		}
		if (主线任务.dStep == 3)
		{
			任务流程 = 0;
			MyTrace(L"Step1        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(7967.853, 4131.286, -504.696, 50, 3000, 500);
			return false;
		}
		if (主线任务.dStep == 4)
		{
			MyTrace(L"Step1        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return false;
		}
		if (主线任务.dStep == 5)
		{
			MyTrace(L"Step1        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(9877, 4858, 3, 50, 3000, 500);
			return false;
		}
		if (主线任务.dStep == 6)
		{
			MyTrace(L"Step1        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 7)
		{
			//MyTrace(L"Step7        任务流程 %d", 任务流程);
			//坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			//if (任务流程 == 0)
			//{
			//	if (清理击打道具(12389, 3090, 3, 500, 500))
			//	{
			//		任务流程 = 1;
			//	}
			//}
			//if (任务流程 == 1)
			//{
			//	功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			//}
			//return false;

			MyTrace(L"Step7        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (地图::指定地点是否可到达_M(任务坐标.x, 任务坐标.y, 任务坐标.z))
			{
				功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			}
			else
			{
				清理击打道具(12389, 3090, 3, 500, 500);
			}
			return false;
		}
		if (主线任务.dStep == 8)
		{
			任务流程 = 0;
			MyTrace(L"Step8        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 3000, 500);
			return false;
		}
		if (主线任务.dStep == 9)
		{
			MyTrace(L"Step1        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 3000, 500);
			return false;
		}
		if (主线任务.dStep == 10)
		{
			MyTrace(L"Step1        任务流程 %d", 任务流程);
			加入优先打怪ID(L"131583|131587");
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(15110, 16241, -15, 50, 3000, 500);
			return false;
		}
		if (主线任务.dStep == 11)
		{
			MyTrace(L"Step1        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (!地图::指定地点是否可到达_M(15324.000, 17882.000, 25.000))
			{
				功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 15320, 17664, 27.2485, 50);
			}
			else if (!地图::指定地点是否可到达_M(18233.000, 20498.000, 453.000))
			{
				功能::移动打怪(18233.000, 20498.000, 453.000, 50, 3000, 500);
			}
			else
			{
				功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			}

			return false;
		}
		if (主线任务.dStep == 12)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (地图::指定地点是否可到达_M(任务坐标.x, 任务坐标.y, 任务坐标.z))
			{
				功能::到指定地点(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			}
			else
			{
				清理击打道具(18063, 20158, 453, 500, 500);
			}
		}
		if (主线任务.dStep == 13)
		{
			MyTrace(L"Step1        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(任务坐标.大陆ID, 任务坐标.地图ID, 20246.6, 22264.4, 892.865, 50);
			return false;
		}
		if (主线任务.dStep == 14)
		{
			MyTrace(L"Step14       任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (地图::指定地点是否可到达_M(任务坐标.x, 任务坐标.y, 任务坐标.z))
			{

				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 8000, 500);
			}
			else
			{
				功能::移动打怪(26602.000, 24599.000, 901.183, 50, 8000, 500);
			}
			return false;
		}
		if (主线任务.dStep == 15)
		{
			MyTrace(L"Step1        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 26528.3, 26882.9, 1259.06, 50);
			return false;
		}
		if (主线任务.dStep == 16)
		{
			MyTrace(L"Step1        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return false;
		}
		if (主线任务.dStep == 17)
		{
			MyTrace(L"Step1        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return false;
		}


	}
	if (主线任务.dQuestId == 410401)//  410401<64321> 副本任务: 虚像之塔
	{
		if (主线任务.dStep == 1)
		{
			MyTrace(L"Step1        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 2)
		{
			任务流程 = 0;
			MyTrace(L"Step1        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 3000, 500);
			return false;
		}
		if (主线任务.dStep == 3)
		{
			MyTrace(L"Step1        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return false;
		}

	}
	if (主线任务.dQuestId == 410402)// D 410402<64322> 副本任务: 镜之迷宫
	{
		if (主线任务.dStep == 1)
		{
			MyTrace(L"Step1        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 3000, 500);
			return false;
		}
		if (主线任务.dStep == 2)
		{
			MyTrace(L"Step2        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (地图::指定地点是否可到达_M(-6385, -4461, 258.105))
			{
				MyTrace(L"Step2        任务地点可达");
				功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			}
			else
			{
				MyTrace(L"Step2        任务地点不可达，前往清理障碍");
				if (功能::到指定地点(任务坐标.大陆ID, 任务坐标.地图ID, -6411, -9735, 522.105, 50))
				{
					MyTrace(L"Step2        任务地点不可达，清理障碍");
					清理击打道具(-6428.07, -9696.1, 522.105, 500, 500);
				}
			}
			return false;
		}
		if (主线任务.dStep == 3)
		{
			任务流程 = 0;
			MyTrace(L"Step1        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return false;
		}
		if (主线任务.dStep == 4)
		{
			MyTrace(L"Step4        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (地图::指定地点是否可到达_M(-987, -8094, 268.076))
			{
				功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, -987, -8094, 268.076, 50);
			}
			else
			{

				if (地图::指定地点是否可到达_M(-2481.000, -10296.000, 522.105))
				{
					if (功能::到指定地点(任务坐标.大陆ID, 任务坐标.地图ID, -2481.000, -10296.000, 522.105, 50))
					{
						清理击打道具(-2481.000, -10296.000, 522.105, 500, 500);
					}
				}
				else
				{
					if (功能::到指定地点(任务坐标.大陆ID, 任务坐标.地图ID, -6152, -6362, 526.558, 50))
					{
						清理击打道具(-6152, -6362, 526.558, 500, 500);
					}

				}

			}
			return false;
		}
		if (主线任务.dStep == 5)
		{
			MyTrace(L"Step1        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 3000, 500);
			return false;
		}
		if (主线任务.dStep == 6)
		{
			MyTrace(L"Step1        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, -556, -7717, 268.076, 50);
			return false;
		}
		if (主线任务.dStep == 7)
		{
			MyTrace(L"Step7        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);

			return false;
		}
		if (主线任务.dStep == 8)
		{
			MyTrace(L"Step8        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (地图::指定地点是否可到达_M(任务坐标.x, 任务坐标.y, 任务坐标.z))
			{
				功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			}
			else
			{

				if (地图::指定地点是否可到达_M(-32.000, -652.000, 556.324))
				{
					if (功能::移动打怪(-32.000, -652.000, 556.324, 50, 3000, 500))// -1584.908,-774.630,550.955
					{
						清理击打道具(79, -717, 556.324, 500, 500);
					}
				}
				else
				{
					if (功能::到指定地点(任务坐标.大陆ID, 任务坐标.地图ID, 1923.000, -804.000, 553.331, 50))
					{
						清理击打道具(1840, -837, 552.595, 500, 500);
					}

				}

			}
			return false;
		}
		if (主线任务.dStep == 9)// -1510.000,-785.000,550.955??
		{
			MyTrace(L"Step9        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (地图::指定地点是否可到达_M(任务坐标.x, 任务坐标.y, 任务坐标.z))
			{
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 3000, 500);
			}
			else
			{
				if (功能::到指定地点(任务坐标.大陆ID, 任务坐标.地图ID, -1495.000, -862.000, 550.955, 50))
				{
					清理击打道具(-1495.000, -862.000, 550.955, 500, 500);
				}

			}
			return false;
		}
		if (主线任务.dStep == 10)
		{
			MyTrace(L"Step10        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (功能::移动打怪(-2420.000, 1473.000, 548.076, 50, 3000, 500))// -1584.908,-774.630,550.955
			{
				功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, -2420.000, 1473.000, 548.076, 50);
			}
			return false;
		}
		if (主线任务.dStep == 11)
		{
			MyTrace(L"Step11       任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return false;
		}
		if (主线任务.dStep == 12)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return false;
		}
		if (主线任务.dStep == 13)
		{
			MyTrace(L"Step1        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 3000, 500);
			return false;
		}
		if (主线任务.dStep == 14)
		{
			MyTrace(L"Step14       任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (地图::指定地点是否可到达_M(2934.000, 6223.000, 717.779))
			{
				功能::移动打怪(2934.000, 6223.000, 717.779, 50, 3000, 500);
			}
			else
			{
				if (功能::到指定地点(任务坐标.大陆ID, 任务坐标.地图ID, 671, 5209, 188.601, 50))
				{
					清理击打道具(987, 5236, 188.601, 500, 500);
				}

			}
			return false;
		}
		if (主线任务.dStep == 15)//youwnti
		{
			MyTrace(L"Step1        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			地图::本地图寻路(5845.38, 6264.95, 1464.37, 0);
			//功能::到指定地点(任务坐标.大陆ID, 任务坐标.地图ID, 5845.38, 6264.95, 1464.37, 50);
			return false;
		}
		if (主线任务.dStep == 16)
		{
			MyTrace(L"Step1        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 3000, 500);
			return false;
		}
		if (主线任务.dStep == 17)
		{
			MyTrace(L"Step17        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return false;
		}
		if (主线任务.dStep == 18)
		{
			MyTrace(L"Step18        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 19)
		{
			MyTrace(L"Step19        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return false;
		}
	}
	if (主线任务.dQuestId == 406402)// :406402<63382> QuestName:以自由的名义！  给缘分套装
	{
		if (主线任务.dStep == 1)
		{
			MyTrace(L"Step1        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 2)
		{
			MyTrace(L"Step1        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 3)
		{
			MyTrace(L"Step1        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return false;
		}
		if (主线任务.dStep == 4)
		{
			MyTrace(L"Step1        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 5)
		{
			MyTrace(L"Step1        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return false;
		}
		if (主线任务.dStep == 6)
		{
			MyTrace(L"Step1        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return false;
		}
		if (主线任务.dStep == 7)
		{
			MyTrace(L"Step7        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (UI功能::经验条界面是否显示() == false)
			{
				UI功能::内存按键(DWORD('G'));
				Sleep(500);
			}
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return false;
		}
	}
	if (主线任务.dQuestId == 4500402)//  4500402<44ABB2> 副本任务: 酷寒中的光明
	{
		if (主线任务.dStep == 1)
		{
			MyTrace(L"Step1        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return false;
		}
		if (主线任务.dStep == 2)
		{
			任务流程 = 0;
			MyTrace(L"Step1        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return false;
		}
	}

	return true;
}
bool 游戏::执行支线任务()
{
	MyTrace(L"执行支线任务");
	//return true;
	vector<DWORD>vsk;
	任务::get_FinishQuestList(vsk);
	//MyTrace(L"判断莱文哈特支线");
	if (!游戏::支线_莱温哈特(vsk))
	{
		return false;
	}
	//MyTrace(L"判断罗格尔支线");
	if (!游戏::支线_罗格尔(vsk))
	{
		return false;
	}
	//MyTrace(L"判断安格莫斯山麓支线");
	if (!游戏::支线_安格莫斯山麓(vsk))
	{
		return false;
	}
	//MyTrace(L"判断国境地带支线");
	if (!游戏::支线_国境地带(vsk))
	{
		return false;
	}
	//MyTrace(L"支线_萨尔兰德丘陵");
	if (!游戏::支线_萨尔兰德丘陵(vsk))
	{
		return false;
	}
	//MyTrace(L"支线_奥兹霍丘陵");
	if (!游戏::支线_奥兹霍丘陵(vsk))
	{
		return false;
	}
	//MyTrace(L"支线_扎格拉斯山");
	if (!游戏::支线_扎格拉斯山(vsk))
	{
		return false;
	}
	//MyTrace(L"支线_雷科巴");
	if (!游戏::支线_雷科巴(vsk))
	{
		return false;
	}
	//MyTrace(L"支线_梅德里克修道院");
	if (!游戏::支线_梅德里克修道院(vsk))
	{
		return false;
	}
	//MyTrace(L"支线_比尔布森林");
	if (!游戏::支线_比尔布森林(vsk))
	{
		return false;
	}
	//MyTrace(L"支线_激战平原");
	if (!游戏::支线_激战平原(vsk))
	{
		return false;
	}
	//MyTrace(L"支线_卢特兰城");
	if (!游戏::支线_卢特兰城(vsk))
	{
		return false;
	}
	//MyTrace(L"支线_迪奥利卡平原");
	if (!游戏::支线_迪奥利卡平原(vsk))
	{
		return false;
	}
	//MyTrace(L"支线_圆虹之丘");
	if (!游戏::支线_圆虹之丘(vsk))
	{
		return false;
	}
	//MyTrace(L"支线_梨树栖息地");
	if (!游戏::支线_梨树栖息地(vsk))
	{
		return false;
	}
	//MyTrace(L"支线_黑玫瑰教堂");
	if (!游戏::支线_黑玫瑰教堂(vsk))
	{
		return false;
	}
	//MyTrace(L"支线_拉伊亚阶地");
	if (!游戏::支线_拉伊亚阶地(vsk))
	{
		return false;
	}
	//MyTrace(L"支线_博伦亚领地");
	if (!游戏::支线_博伦亚领地(vsk))
	{
		return false;
	}
	//MyTrace(L"支线_鬃波港");
	if (!游戏::支线_鬃波港(vsk))
	{
		return false;
	}
	//MyTrace(L"支线_科罗克尼斯渔村");
	if (!游戏::支线_科罗克尼斯渔村(vsk))
	{
		return false;
	}
	//MyTrace(L"支线_世界1");
	if (!游戏::支线_世界1(vsk))
	{
		return false;
	}
	//MyTrace(L"支线_世界2");
	if (!游戏::支线_世界2(vsk))
	{
		return false;
	}
	//MyTrace(L"支线_世界3");
	if (!游戏::支线_世界3(vsk))
	{
		return false;
	}
	//MyTrace(L"支线_世界4");
	if (!游戏::支线_世界4(vsk))
	{
		return false;
	}
	MyTrace(L"判断完毕");
	return true;
	//205004
}
bool 游戏::世界1(QuestInfo_ 必做引导任务)
{

	if (必做引导任务.dQuestId == 4002001)//我先讲讲航海的基本常识吧.  
	{
		if (必做引导任务.dStep == 1 || 必做引导任务.dStep == 2)
		{
			if (地图::取地图ID() != 30703)
			{
				if (!UI功能::是否在航海准备界面())
				{
					功能::到指定地点(15, 10804, 3298, 13919, -144, 50);
				}

			}
			else
			{
				if (!航海::指定船员是否上船(0xB242A))
				{
					if (!UI功能::是否在航海准备界面())
					{
						if (功能::到指定地点(15, 30703, -31678, 32086, 1, 50))
						{
							UI功能::内存按键('Z');
							Sleep(2000);
						}
					}
					else
					{
						if (!航海::指定船员是否上船(0xB242A))
						{
							航海::VoyageShipAddCrew(0xB242A);
							return true;
						}

					}
				}
				else
				{
					if (UI功能::是否在航海准备界面())
					{
						UI功能::航海出港();
						MyTrace(L"航海出港");
					}
				}
			}
		}
		if (必做引导任务.dStep == 3)
		{
			功能::到指定地点(18, 30703, -29155, 35264, 1, 50);
			//Sleep(2000);
		}
		if (必做引导任务.dStep == 4)
		{
			功能::到指定地点(18, 30703, -28496, 38351, 1, 50);
			//Sleep(2000);
		}
		if (必做引导任务.dStep == 5)
		{
			功能::到指定地点采集任务显示(18, 30703, -28496, 38351, 1, 1000, 1038100, 1, 200);
			//Sleep(2000);
		}
		if (必做引导任务.dStep == 6)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			功能::到指定地点(18, 30703, 任务坐标.x, 任务坐标.y, 1, 50);
			//Sleep(2000);
		}
		if (必做引导任务.dStep == 7)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 必做引导任务.TargetId, 必做引导任务.dQuestId, -1, 50, 必做引导任务.dStep);
			//Sleep(2000);
		}
		if (必做引导任务.dStep == 9)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			功能::到指定地点入港(18, 30703, -17144, 45477, 1, 50);
			//Sleep(2000);
		}
		if (必做引导任务.dStep == 10)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 必做引导任务.TargetId, 必做引导任务.dQuestId, -1, 50, 必做引导任务.dStep);
			//Sleep(2000);
		}
		return false;
	}
	if (必做引导任务.dQuestId == 1002002)//我先讲讲航海的基本常识吧.  
	{
		if (必做引导任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 必做引导任务.TargetId, 必做引导任务.dQuestId, -1, 100, 必做引导任务.dStep);
			//Sleep(2000);
			return false;
		}
		if (必做引导任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 必做引导任务.TargetId, 必做引导任务.dQuestId, -1, 150, 必做引导任务.dStep);
			//Sleep(2000);
			return false;
		}
		if (必做引导任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 必做引导任务.TargetId, 必做引导任务.dQuestId, -1, 100, 必做引导任务.dStep);
			//Sleep(2000);
			return false;
		}
		if (必做引导任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 必做引导任务.TargetId, 必做引导任务.dQuestId, -1, 200, 必做引导任务.dStep);
			//Sleep(2000);
			return false;
		}
		if (必做引导任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			功能::到指定地点采集任务显示_多目标(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 3000, 110002, 110013, 100, 150);
			//Sleep(2000);
			return false;
		}
		if (必做引导任务.dStep == 6)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 必做引导任务.TargetId, 必做引导任务.dQuestId, -1, 200, 必做引导任务.dStep);
			//Sleep(2000);
			return false;
		}
		if (必做引导任务.dStep == 7)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			功能::到指定地点采集任务显示(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 3000, 110031, 100, 150);
			//Sleep(2000);
			return false;
		}
	}
	if (必做引导任务.dQuestId == 1002401)//我先讲讲航海的基本常识吧.  
	{
		if (必做引导任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			if (功能::到指定地点(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50))
			{
				UI功能::内存按键(VK_F5);
			}
			return false;
		}
		if (必做引导任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			加入优先打怪ID(L"110005");
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 3000, 100, true);
			return false;
		}
		if (必做引导任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			if (功能::优先破坏击打道具(6000))
			{
				功能::到指定地点(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			}
			return false;
		}
		if (必做引导任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			加入优先打怪ID(L"190150");
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 3000, 100, false);
			return false;
		}
		if (必做引导任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			功能::到指定地点按G(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 200);
			return false;
		}
		if (必做引导任务.dStep == 6)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			功能::到指定地点按G(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 200);
			return false;
		}
		if (必做引导任务.dStep == 7)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			功能::到指定地点按G(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 200);
			return false;
		}
	}
	if (必做引导任务.dQuestId == 1002003)//我先讲讲航海的基本常识吧.  
	{
		if (必做引导任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			功能::寻路到副本(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z);
			return false;
		}
	}
	if (必做引导任务.dQuestId == 1002004)//我先讲讲航海的基本常识吧.  
	{
		if (必做引导任务.dState == 1)
		{
			if (必做引导任务.dStep == 1)
			{
				if (地图::取地图ID() == 11017)
				{
					本人::CALL_演奏乐谱(1);
					Sleep(10000);
					return false;
				}
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点按G(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 200);
				return false;
			}
			if (必做引导任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 必做引导任务.TargetId, 必做引导任务.dQuestId, -1, 200, 必做引导任务.dStep);
				//Sleep(2000);
				return false;
			}
			if (必做引导任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				if (功能::到指定地点(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50))
				{
					UI功能::内存按键(VK_F5);
				}
				return false;
			}
			if (必做引导任务.dStep == 4)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 必做引导任务.TargetId, 必做引导任务.dQuestId, -1, 200, 必做引导任务.dStep);
				//Sleep(2000);
				return false;
			}
			if (必做引导任务.dStep == 5)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点采集任务显示(2, 任务坐标.地图ID, 7040, 19633, 1200, 2000, 110006, 100, 300);
				//Sleep(2000);
				return false;
			}
			if (必做引导任务.dStep == 6)
			{
				if (功能::优先打怪(200))
				{
					UI功能::内存按键(VK_F5);
					return false;
				}

			}
			if (必做引导任务.dStep == 7)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点采集任务显示(2, 任务坐标.地图ID, 15260, 22890, 1024, 2000, 110014, 200, 150);
				//Sleep(2000);
				return false;
			}
		}
		else
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 必做引导任务.dQuestId, -1, 200, 必做引导任务.dStep);
			//Sleep(2000);
			return false;
		}
	}
	if (必做引导任务.dQuestId == 1002005)//我先讲讲航海的基本常识吧.  
	{
		if (必做引导任务.dState == 1)
		{
			if (必做引导任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点采集任务显示(2, 任务坐标.地图ID, 20612, 23931, 512, 2000, 110007, 100, 100);
				//Sleep(2000);
				return false;
			}
		}
		else
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 必做引导任务.dQuestId, -1, 200, 必做引导任务.dStep);
			//Sleep(2000);
			return false;
		}
	}
	if (必做引导任务.dQuestId == 1002006)//我先讲讲航海的基本常识吧.  
	{
		if (必做引导任务.dState == 1)
		{
			if (必做引导任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点采集任务显示(2, 任务坐标.地图ID, 25829, 17505, 1024, 2000, 110008, 100, 300);
				//Sleep(2000);
				return false;
			}
			if (必做引导任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点采集任务显示(2, 任务坐标.地图ID, 25829, 17505, 1024, 2000, 110009, 100, 300);
				//Sleep(2000);
				return false;
			}
			if (必做引导任务.dStep == 3)
			{
				UI功能::内存按键(VK_F5);
				return false;
			}
		}
		else
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 必做引导任务.dQuestId, -1, 200, 必做引导任务.dStep);
			//Sleep(2000);
			return false;
		}
	}
	if (必做引导任务.dQuestId == 1002007)//我先讲讲航海的基本常识吧.  
	{
		if (必做引导任务.dState == 1)
		{
			if (必做引导任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点按G(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 200);
				return false;
			}
			if (必做引导任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				if (功能::到指定地点(2, 任务坐标.地图ID, 28691, 10022, 1500, 50))
				{
					UI功能::内存按键(VK_F5);
				}
				return false;
			}
		}
	}
	if (必做引导任务.dQuestId == 1001401)//我先讲讲航海的基本常识吧.  
	{
		if (必做引导任务.dState == 1)
		{
			if (必做引导任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 1000, 100, false);
				return false;
			}
			if (必做引导任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 必做引导任务.TargetId, 必做引导任务.dQuestId, -1, 100, 必做引导任务.dStep);
				//Sleep(2000);
				return false;
			}
		}
	}
	if (必做引导任务.dQuestId == 1001002)//我先讲讲航海的基本常识吧.  
	{
		if (必做引导任务.dState == 1)
		{
			if (必做引导任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::寻路到副本(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z);
				return false;
			}
		}
	}
	if (必做引导任务.dQuestId == 1001402)//我先讲讲航海的基本常识吧.  
	{
		if (必做引导任务.dState == 1)
		{
			if (必做引导任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}
			if (必做引导任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 必做引导任务.TargetId, 必做引导任务.dQuestId, -1, 100, 必做引导任务.dStep);
				return false;
			}
			if (必做引导任务.dStep == 3)
			{
				功能::到指定地点使用表情(2, 11016, 8818, 5705, -5106, 50, 0xF237);

				return false;
			}
		}
	}
	if (必做引导任务.dQuestId == 1001003)//我先讲讲航海的基本常识吧.  
	{
		if (必做引导任务.dState == 1)
		{
			if (必做引导任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				ActorInfo_ 角色信息 = 本人::取角色信息();
				if (角色信息.举起状态 == 1)
				{

					功能::到指定地点采集任务显示(2, 任务坐标.地图ID, 5138, 7260, 299, 3000, 110102, 100, 100);

				}
				else
				{
					if (功能::到指定地点(2, 任务坐标.地图ID, 2808, 7881, 514, 50))
					{
						UI功能::内存按键('R');
						Sleep(1000);
					}
				}
				return false;
			}
		}
		else
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 必做引导任务.dQuestId, -1, 100, 必做引导任务.dStep);
			return false;
		}
	}
	if (必做引导任务.dQuestId == 1001004)//我先讲讲航海的基本常识吧.  
	{
		if (必做引导任务.dState == 1)
		{
			if (必做引导任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点采集任务显示(2, 任务坐标.地图ID, 2894, 8448, 514, 1000, 110104, 100, 100);
				return false;
			}
			if (必做引导任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点采集任务显示(2, 任务坐标.地图ID, 3279, 2706, -328, 1000, 110106, 100, 300);
				return false;
			}
		}
		else
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 必做引导任务.dQuestId, -1, 100, 必做引导任务.dStep);
			return false;
		}
	}
	if (必做引导任务.dQuestId == 1001005)//净化地图 
	{
		if (必做引导任务.dState == 1)
		{
			if (必做引导任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 必做引导任务.dQuestId, -1, 100, 必做引导任务.dStep);
				return false;

			}
			if (必做引导任务.dStep == 2)
			{
				UI功能::内存按键(VK_F5);
				Sleep(1000);
			}
			if (必做引导任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;

			}
		}
		else
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 必做引导任务.dQuestId, -1, 100, 必做引导任务.dStep);
			return false;
		}
	}
	if (必做引导任务.dQuestId == 1001006)//净化地图 
	{
		if (必做引导任务.dState == 1)
		{
			if (必做引导任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;

			}
		}
		else
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 必做引导任务.TargetId, 必做引导任务.dQuestId, -1, 100, 必做引导任务.dStep);
			return false;
		}
	}
	if (必做引导任务.dQuestId == 1003001)//净化地图 
	{
		if (必做引导任务.dState == 1)
		{
			if (必做引导任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点采集任务显示(2, 任务坐标.地图ID, 3263, 9444, 0, 1000, 110264, 100, 100);
				return false;

			}
			if (必做引导任务.dStep == 2)
			{
				if (必做引导任务.子任务进度.size() == 1)
				{
					if (必做引导任务.子任务进度[0].dCur == 0)
					{
						ActorInfo_ 角色信息 = 本人::取角色信息();
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
						if (角色信息.举起状态 == 1)
						{
							功能::到指定地点采集任务显示(2, 任务坐标.地图ID, 3272, 9526, 0, 1000, 0x1AE79, 100, 100);
							return false;
						}
						else
						{
							if (功能::到指定地点(2, 任务坐标.地图ID, 4740, 10390, 11, 100))
							{
								objInfo_ 目标信息 = 环境::取指定任务显示对象信息(0x1AEB7);
								if (目标信息.dResId != 0)
								{
									技能::屏蔽鼠标();
									技能::写怪物坐标到鼠标(目标信息.坐标);
									UI功能::内存按键('Q');
									技能::解除屏蔽鼠标();
								}
							}
							return false;
						}
					}
					if (必做引导任务.子任务进度[0].dCur == 1)
					{
						ActorInfo_ 角色信息 = 本人::取角色信息();
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
						if (角色信息.举起状态 == 1)
						{
							功能::到指定地点采集任务显示(2, 任务坐标.地图ID, 3272, 9526, 0, 1000, 0x1AE79, 100, 100);
							return false;
						}
						else
						{
							if (功能::到指定地点(2, 任务坐标.地图ID, 3969, 10807, -0, 100))
							{
								objInfo_ 目标信息 = 环境::取指定任务显示对象信息(0x1AEB7);
								if (目标信息.dResId != 0)
								{
									技能::屏蔽鼠标();
									技能::写怪物坐标到鼠标(目标信息.坐标);
									UI功能::内存按键('Q');
									技能::解除屏蔽鼠标();
								}
							}
							return false;
						}
					}
				}
			}
			if (必做引导任务.dStep == 3)
			{
				if (必做引导任务.子任务进度.size() == 1)
				{
					if (必做引导任务.子任务进度[0].dCur == 0)
					{
						ActorInfo_ 角色信息 = 本人::取角色信息();
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
						if (角色信息.举起状态 == 1)
						{
							功能::到指定地点采集任务显示(2, 任务坐标.地图ID, 3837, 9519, 0, 1000, 0x1AEB6, 100, 100);
							return false;
						}
						else
						{
							if (功能::到指定地点(2, 任务坐标.地图ID, 4647, 10376, 0, 100))
							{
								UI功能::内存按键('R');
							}
							return false;
						}
					}

				}
			}
			if (必做引导任务.dStep == 4)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 必做引导任务.TargetId, 必做引导任务.dQuestId, -1, 100, 必做引导任务.dStep);
				return false;
			}
		}
	}
	if (必做引导任务.dQuestId == 1003002)//瓢虫快来 
	{
		if (必做引导任务.dState == 1)
		{
			if (必做引导任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 必做引导任务.TargetId, 必做引导任务.dQuestId, -1, 100, 必做引导任务.dStep);
				return false;

			}
			if (必做引导任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 必做引导任务.TargetId, 必做引导任务.dQuestId, -1, 100, 必做引导任务.dStep);
				return false;

			}
			if (必做引导任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				if (功能::到指定地点(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 100))
				{
					UI功能::内存按键('Q');
				}
				return false;

			}
			if (必做引导任务.dStep == 4)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 100);

				return false;

			}
			if (必做引导任务.dStep == 5)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点按G(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 100);

				return false;

			}
			if (必做引导任务.dStep == 6)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点按G(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 100);

				return false;

			}
			if (必做引导任务.dStep == 7)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点按G(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 100);
				return false;
			}
			if (必做引导任务.dStep == 8)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点按G_无打怪(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 100);
				return false;
			}
			if (必做引导任务.dStep == 9)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 必做引导任务.TargetId, 必做引导任务.dQuestId, -1, 100, 必做引导任务.dStep);
				return false;

			}
		}
		else
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 必做引导任务.dQuestId, Random(0, 2), 100, 必做引导任务.dStep);
			return false;

		}
	}
	if (必做引导任务.dQuestId == 1003003)//刺心的针 
	{
		if (必做引导任务.dState == 1)
		{
			if (必做引导任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点采集任务显示(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 3000, 110205);
				return false;
			}
			if (必做引导任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点采集任务显示(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 3000, 110206);
				return false;
			}
			if (必做引导任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				加入优先打怪ID(L"190220|190230");
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 3000, 100, true);
				return false;
			}
		}
		else
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 必做引导任务.dQuestId, Random(0, 2), 100, 必做引导任务.dStep);
			return false;
		}
	}
	if (必做引导任务.dQuestId == 1003004)//刺心的针 
	{
		if (必做引导任务.dState == 1)
		{
			if (必做引导任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::寻路到副本(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z);
				return false;
			}

		}
	}
	if (必做引导任务.dQuestId == 1003401)//刺心的针 
	{
		if (必做引导任务.dState == 1)
		{
			if (必做引导任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点按G(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 200);
				return false;
			}
			if (必做引导任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 3000, 100, true);
				return false;
			}
			if (必做引导任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 必做引导任务.TargetId, 必做引导任务.dQuestId, -1, 100, 必做引导任务.dStep);
				return false;

			}
			if (必做引导任务.dStep == 4)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点按G(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 200);
				return false;
			}
		}
	}
	if (必做引导任务.dQuestId == 1003005)//刺心的针 
	{
		if (必做引导任务.dState == 1)
		{
			if (必做引导任务.dStep == 1)
			{
				if (地图::取地图ID() == 11018)
				{
					功能::到指定地点(2, 11018, 6641, 22423, 459, 50);
					return false;
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
					if (功能::到指定地点(2, 任务坐标.地图ID, 6785, 22396, 454, 50))
					{
						UI功能::内存按键(VK_F5);
					}
					return false;
				}

			}
			if (必做引导任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 必做引导任务.TargetId, 必做引导任务.dQuestId, -1, 100, 必做引导任务.dStep);
				return false;
			}
			if (必做引导任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				ActorInfo_ 角色信息 = 本人::取角色信息();
				if (角色信息.举起状态 == 1)
				{
					功能::到指定地点采集任务显示(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 3000, 110236, 300, 100);
					return false;
				}
				else
				{
					if (功能::到指定地点(2, 任务坐标.地图ID, 16213, 19341, 462, 50))
					{
						UI功能::内存按键('R');
					}
					return false;
				}

			}
			if (必做引导任务.dStep == 4)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);

				功能::到指定地点采集任务显示(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 3000, 110237);
				return false;

			}
			if (必做引导任务.dStep == 5)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;

			}

		}
		else
		{

			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 必做引导任务.dQuestId, -1, 100, 必做引导任务.dStep);
			return false;
		}
	}
	if (必做引导任务.dQuestId == 1003006)//:潜入海盗巢穴 
	{
		if (必做引导任务.dState == 1)
		{
			if (必做引导任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::寻路到副本(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z);
				return false;
			}
		}
	}
	if (必做引导任务.dQuestId == 1006401)//前往海盗巢穴 副本 
	{
		if (必做引导任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			功能::优先破坏击打道具(1000);
			return false;
		}
		if (必做引导任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			if (!功能::优先打怪(1000))
			{
				return false;
			}
			if (本人::是否在走路())
			{
				return false;
			}
			if (地图::指定地点是否可到达_M(任务坐标.x, 任务坐标.y, 任务坐标.z))
			{
				ActorInfo_ 角色信息 = 本人::取角色信息();
				if (角色信息.举起状态 == 1)
				{
					功能::到指定地点按G(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 500);

				}
				else
				{
					if (功能::到指定地点(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50))
					{
						UI功能::内存按键('R');
					}
				}
			}
			else
			{
				功能::到指定地点按G(2, 任务坐标.地图ID, 11548, 5832, 144, 50, 500);
			}

			return false;
		}
		if (必做引导任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			功能::到指定地点(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return false;
		}
		if (必做引导任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			加入优先打怪ID(L"190261");
			功能::移动打怪(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 2000);
			return false;
		}
		if (必做引导任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			if (功能::优先破坏击打道具(1000))
			{
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 2000);
			}
			return false;
		}
		if (必做引导任务.dStep == 6)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			加入优先打怪ID(L"190261");
			功能::移动打怪(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 2000);
			return false;
		}
		if (必做引导任务.dStep == 7)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			if (功能::优先破坏击打道具(6000))
			{
				功能::到指定地点按G(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 500);
			}
			return false;
		}
		if (必做引导任务.dStep == 8)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			加入优先打怪ID(L"190264");
			功能::移动打怪(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 2000);
			return false;
		}
		if (必做引导任务.dStep == 9)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			ActorInfo_ 角色信息 = 本人::取角色信息();
			if (!背包::指定位置生活工具是否已装备(1))
			{
				if (背包::返回指定物品数量(0x67EEA4) == 0)
				{
					if (功能::到指定地点(2, 任务坐标.地图ID, 14342, 24353, 0, 500))
					{
						功能::优先破坏击打道具(2000);
					}

					return false;
				}
				else
				{
					背包::装备背包指定物品_ByResId(0x67EEA4);
				}
			}
			else
			{
				功能::到指定地点按G(2, 任务坐标.地图ID, 14973, 24902, 0, 50);

			}
			return false;
		}
		if (必做引导任务.dStep == 10)
		{
			if (钓鱼::getquickSlotFrameType() != 1)
			{
				UI功能::内存按键('B');
				return false;
			}
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			if (功能::优先破坏击打道具(500))
			{
				if (功能::优先打怪(1000))
				{
					功能::到指定地点(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				}
			}

			return false;
		}
		if (必做引导任务.dStep == 11)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			加入优先打怪ID(L"190261");
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 200, 2000);
			return false;
		}
		if (必做引导任务.dStep == 12)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			if (功能::优先破坏击打道具(2000))
			{
				功能::到指定地点按G(2, 任务坐标.地图ID, 21174, 24066, 58, 50, 500);
			}
			return false;
		}
		if (必做引导任务.dStep == 13)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);

			功能::到指定地点按G(2, 任务坐标.地图ID, 21174, 24066, 58, 50, 500);

			return false;
		}
		if (必做引导任务.dStep == 14)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			ActorInfo_ 角色信息 = 本人::取角色信息();
			if (角色信息.坐标.z > 0)
			{
				功能::移动打怪(21174, 24066, 58, 200, 2000);
			}
			else
			{
				功能::移动打怪(22429, 26106, -680, 200, 2000);
			}


			return false;
		}
	}
	if (必做引导任务.dQuestId == 1006001)//前往海盗巢穴 副本 
	{
		if (必做引导任务.dStep == 1)
		{
			if (地图::取地图ID() == 11051)
			{
				本人::CALL_演奏乐谱(1);
				Sleep(10000);
				return false;
			}
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			功能::到指定地点(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return false;
		}
		if (必做引导任务.dStep == 2)
		{
			UI功能::内存按键(VK_F5);
			return false;
		}
		if (必做引导任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 必做引导任务.TargetId, 必做引导任务.dQuestId, -1, 100, 必做引导任务.dStep);
			return false;
		}
		if (必做引导任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 必做引导任务.TargetId, 必做引导任务.dQuestId, -1, 100, 必做引导任务.dStep);
			return false;
		}
		if (必做引导任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 必做引导任务.TargetId, 必做引导任务.dQuestId, -1, 100, 必做引导任务.dStep);
			return false;
		}
		if (必做引导任务.dStep == 6)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 必做引导任务.TargetId, 必做引导任务.dQuestId, -1, 100, 必做引导任务.dStep);
			return false;
		}
		if (必做引导任务.dStep == 7)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 必做引导任务.TargetId, 必做引导任务.dQuestId, -1, 100, 必做引导任务.dStep);
			return false;
		}
		if (必做引导任务.dStep == 8)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 必做引导任务.TargetId, 必做引导任务.dQuestId, -1, 100, 必做引导任务.dStep);
			return false;
		}
	}
	if (必做引导任务.dQuestId == 1004001)//前往海盗巢穴 副本 
	{
		if (必做引导任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 必做引导任务.dQuestId, -1, 100, 必做引导任务.dStep);
			return false;
		}
		if (必做引导任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 必做引导任务.TargetId, 必做引导任务.dQuestId, -1, 100, 必做引导任务.dStep);
			return false;
		}
	}
	if (必做引导任务.dQuestId == 1004002)//前往海盗巢穴 副本 
	{
		if (必做引导任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			加入优先打怪ID(L"190146|190243|190340");
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 200, 2000);
			return false;
		}
		if (必做引导任务.dStep == 2)
		{
			if (必做引导任务.子任务进度.size() == 2)
			{
				if (必做引导任务.子任务进度[0].dCur < 必做引导任务.子任务进度[0].dNeed)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
					加入优先打怪ID(L"190531|190147|190245|850045");
					功能::移动打怪(11548, 14041, 2046, 200, 2000);
					return false;
				}
				if (必做引导任务.子任务进度[1].dCur < 必做引导任务.子任务进度[1].dNeed)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
					功能::到指定地点采集任务显示(2, 任务坐标.地图ID, 11548, 14041, 2046, 3000, 110336, 100, 100);
					return false;
				}
			}

		}
	}
	if (必做引导任务.dQuestId == 1004002)//前往海盗巢穴 副本 
	{
		if (必做引导任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			加入优先打怪ID(L"190146|190243|190340");
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 200, 2000);
			return false;
		}

	}
	if (必做引导任务.dQuestId == 1004003)//前往海盗巢穴 副本 
	{
		if (必做引导任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			功能::寻路到副本(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z);
			return false;
		}
	}
	if (必做引导任务.dQuestId == 1004401)//前往海盗巢穴 副本 
	{
		if (必做引导任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			if (功能::优先破坏击打道具(1000))
			{
				加入优先打怪ID(L"110302|190350|190262");
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 200, 2000);
				return false;
			}


		}
		if (必做引导任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			if (必做引导任务.子任务进度.size() == 2)
			{
				if (功能::优先破坏击打道具(1000))
				{

					if (必做引导任务.子任务进度[0].dCur < 必做引导任务.子任务进度[0].dNeed)
					{
						if (必做引导任务.子任务进度[0].dCur == 0)
						{
							功能::到指定地点按G(2, 任务坐标.地图ID, 19424, 13032, 3584, 50, 300);
							return false;
						}
						if (必做引导任务.子任务进度[0].dCur == 1)
						{
							功能::到指定地点按G(2, 任务坐标.地图ID, 20790, 13520, 3584, 50, 300);
							return false;
						}
						if (必做引导任务.子任务进度[0].dCur == 2)
						{
							功能::到指定地点按G(2, 任务坐标.地图ID, 18606, 15103, 3584, 50, 300);
							return false;
						}
					}
					if (必做引导任务.子任务进度[1].dCur < 必做引导任务.子任务进度[1].dNeed)
					{
						加入优先打怪ID(L"190350|190262");
						功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 200, 2000);
						return false;
					}
				}
			}

			return false;
		}
		if (必做引导任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			加入优先打怪ID(L"190660");
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 200, 2000);
			return false;


		}
		if (必做引导任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			功能::到指定地点按G(2, 任务坐标.地图ID, 20506, 14906, 3584, 50);
			return false;
		}
		if (必做引导任务.dStep == 5)
		{
			UI功能::内存按键(VK_F5);
			return false;
		}
		if (必做引导任务.dStep == 6)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 必做引导任务.dQuestId, -1, 100, 必做引导任务.dStep);
			return false;
		}
	}
	if (必做引导任务.dQuestId == 1004006)//前往海盗巢穴 副本 
	{
		if (必做引导任务.dStep == 1)
		{
			if (地图::取地图ID() == 11019)
			{
				本人::CALL_演奏乐谱(1);
				Sleep(10000);
				return false;
			}
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 必做引导任务.dQuestId, -1, 100, 必做引导任务.dStep);
			return false;
		}
		if (必做引导任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 必做引导任务.dQuestId, -1, 100, 必做引导任务.dStep);
			return false;
		}
		if (必做引导任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 必做引导任务.dQuestId, -1, 100, 必做引导任务.dStep);
			return false;
		}
		if (必做引导任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			功能::到指定地点采集任务显示(2, 任务坐标.地图ID, 15352, 18444, 2304, 1000, 110322);
			return false;
		}
		if (必做引导任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 必做引导任务.TargetId, 必做引导任务.dQuestId, -1, 100, 必做引导任务.dStep);
			return false;
		}
		if (必做引导任务.dStep == 6)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 必做引导任务.TargetId, 必做引导任务.dQuestId, -1, 100, 必做引导任务.dStep);
			return false;
		}
		if (必做引导任务.dStep == 7)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 必做引导任务.TargetId, 必做引导任务.dQuestId, -1, 100, 必做引导任务.dStep);
			return false;
		}
		if (必做引导任务.dStep == 8)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 必做引导任务.TargetId, 必做引导任务.dQuestId, -1, 100, 必做引导任务.dStep);
			return false;
		}
	}
	if (必做引导任务.dQuestId == 1004004)//前往海盗巢穴 副本 
	{
		if (必做引导任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			功能::寻路到副本(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z);
			return false;
		}
	}
	if (必做引导任务.dQuestId == 1004402)//另一个守护者 
	{
		if (必做引导任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 必做引导任务.TargetId, 必做引导任务.dQuestId, -1, 100, 必做引导任务.dStep);
			return false;
		}
		if (必做引导任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			功能::到指定地点按G(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 150);
			return false;
		}
		if (必做引导任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 200, 2000);
			return false;
		}
		if (必做引导任务.dStep == 4)
		{
			UI功能::内存按键(VK_F5);
			return false;
		}
		if (必做引导任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 必做引导任务.TargetId, 必做引导任务.dQuestId, -1, 100, 必做引导任务.dStep);
			return false;
		}
	}
	if (必做引导任务.dQuestId == 1004005)//另一个守护者 
	{
		if (必做引导任务.dState == 1)
		{
			if (必做引导任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 必做引导任务.TargetId, 必做引导任务.dQuestId, -1, 100, 必做引导任务.dStep);
				return false;
			}
			if (必做引导任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				加入优先打怪ID(L"190258|190354");
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 200, 2000);
				return false;
			}
			if (必做引导任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点按G(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}

		}
		else
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 必做引导任务.dQuestId, -1, 100, 必做引导任务.dStep);
			return false;
		}

	}
	if (必做引导任务.dQuestId == 1005004)//另一个守护者 
	{
		if (必做引导任务.dState == 1)
		{
			if (必做引导任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 必做引导任务.TargetId, 必做引导任务.dQuestId, -1, 100, 必做引导任务.dStep);
				return false;
			}
			if (必做引导任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 必做引导任务.TargetId, 必做引导任务.dQuestId, -1, 100, 必做引导任务.dStep);
				return false;
			}
			if (必做引导任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 必做引导任务.TargetId, 必做引导任务.dQuestId, -1, 100, 必做引导任务.dStep);
				return false;
			}
			if (必做引导任务.dStep == 4)
			{
				UI功能::内存按键(VK_F5);
				return false;
			}
			if (必做引导任务.dStep == 5)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}
		}
		else
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 必做引导任务.dQuestId, -1, 100, 必做引导任务.dStep);
			return false;
		}
	}
	if (必做引导任务.dQuestId == 1005001)//可以得到的情报   
	{
		if (必做引导任务.dState == 1)
		{
			if (必做引导任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::寻路到副本(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z);
				return false;
			}
		}
	}
	if (必做引导任务.dQuestId == 1005401)//最后的问候   
	{
		if (必做引导任务.dState == 1)
		{
			if (必做引导任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}
			if (必做引导任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点按G(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 150);
				return false;
			}
			if (必做引导任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 2000);
				return false;
			}
			if (必做引导任务.dStep == 4)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}
			if (必做引导任务.dStep == 5)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 必做引导任务.TargetId, 必做引导任务.dQuestId, -1, 100, 必做引导任务.dStep);
				return false;
			}
			if (必做引导任务.dStep == 6)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 必做引导任务.TargetId, 必做引导任务.dQuestId, -1, 100, 必做引导任务.dStep);
				return false;
			}
			if (必做引导任务.dStep == 7)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 必做引导任务.TargetId, 必做引导任务.dQuestId, -1, 100, 必做引导任务.dStep);
				return false;
			}
			if (必做引导任务.dStep == 8)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 必做引导任务.TargetId, 必做引导任务.dQuestId, -1, 100, 必做引导任务.dStep);
				return false;
			}
			if (必做引导任务.dStep == 9)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 必做引导任务.TargetId, 必做引导任务.dQuestId, -1, 100, 必做引导任务.dStep);
				return false;
			}
			if (必做引导任务.dStep == 10)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 必做引导任务.TargetId, 必做引导任务.dQuestId, -1, 100, 必做引导任务.dStep);
				return false;
			}
			if (必做引导任务.dStep == 11)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 必做引导任务.TargetId, 必做引导任务.dQuestId, -1, 100, 必做引导任务.dStep);
				return false;
			}
			if (必做引导任务.dStep == 12)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 必做引导任务.TargetId, 必做引导任务.dQuestId, -1, 100, 必做引导任务.dStep);
				return false;
			}
			if (必做引导任务.dStep == 13)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}
			if (必做引导任务.dStep == 14)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 必做引导任务.TargetId, 必做引导任务.dQuestId, -1, 100, 必做引导任务.dStep);
				return false;
			}
			if (必做引导任务.dStep == 15)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 必做引导任务.TargetId, 必做引导任务.dQuestId, -1, 100, 必做引导任务.dStep);
				return false;
			}
			if (必做引导任务.dStep == 16)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 2000);
				return false;
			}
			if (必做引导任务.dStep == 17)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}
			if (必做引导任务.dStep == 18)
			{
				if (UI功能::怪物击杀求饶界面是否打开())
				{
					UI功能::内存按键('H');
					return false;
				}
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 2000);
				return false;
			}
			if (必做引导任务.dStep == 19)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				if (必做引导任务.子任务进度[0].dCur == 0)
				{
					功能::到指定地点按G(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 150);
					return false;
				}
				if (必做引导任务.子任务进度[0].dCur == 1)
				{
					功能::到指定地点按G(2, 任务坐标.地图ID, 1753, 6950, -3044, 150);
					return false;
				}
				if (必做引导任务.子任务进度[0].dCur == 2)
				{
					功能::到指定地点按G(2, 任务坐标.地图ID, 1510, 6929, -3044, 150);
					return false;
				}
			}
			if (必做引导任务.dStep == 20)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 必做引导任务.TargetId, 必做引导任务.dQuestId, -1, 100, 必做引导任务.dStep);
				return false;
			}
		}
	}
	if (必做引导任务.dQuestId == 1005002)//最后的问候   
	{
		if (必做引导任务.dState == 1)
		{
			if (必做引导任务.dStep == 1)
			{
				if (地图::取地图ID() == 11021)
				{
					功能::到指定地点(2, 11021, 1154, 6327, -3043, 50);
					return false;
				}

				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 必做引导任务.TargetId, 必做引导任务.dQuestId, -1, 100, 必做引导任务.dStep);
				return false;
			}
			if (必做引导任务.dStep == 2)
			{

				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 必做引导任务.TargetId, 必做引导任务.dQuestId, -1, 100, 必做引导任务.dStep);
				return false;
			}
			if (必做引导任务.dStep == 3)
			{

				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}
			if (必做引导任务.dStep == 4)
			{

				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 必做引导任务.TargetId, 必做引导任务.dQuestId, -1, 100, 必做引导任务.dStep);
				return false;
			}
		}
		else
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 必做引导任务.dQuestId, -1, 100, 必做引导任务.dStep);
			return false;
		}
	}
	if (必做引导任务.dQuestId == 1005003)//最后的问候   
	{
		if (必做引导任务.dState == 1)
		{
			if (必做引导任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点采集任务显示(2, 任务坐标.地图ID, 6083, 12883, -2524, 1000, 110403, 100, 200);
				return false;
			}
			if (必做引导任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点采集任务显示(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 1000, 110430, 100, 200);
				return false;
			}
		}
		else
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 必做引导任务.dQuestId, -1, 100, 必做引导任务.dStep);
			return false;
		}
	}
	if (必做引导任务.dQuestId == 1005005)//最后的问候   
	{
		if (必做引导任务.dState == 1)
		{
			if (必做引导任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				坐标_ 角色坐标 = 本人::取坐标();
				if (角色坐标.z > -1735)
				{
					功能::到指定地点采集任务显示(2, 任务坐标.地图ID, 9374, 14355, -1735, 100, 110431, 100, 150);
					return false;
				}
				else
				{
					功能::到指定地点采集任务显示(2, 任务坐标.地图ID, 9374, 14355, -1735, 1000, 110431, 100, 150);
					return false;
				}

			}
			if (必做引导任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点采集任务显示(2, 任务坐标.地图ID, 23777, 13411, 657, 200, 110405, 100, 200);
				return false;
			}
			if (必做引导任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点采集任务显示(2, 任务坐标.地图ID, 23777, 13411, 657, 1000, 110444, 100, 200);
				return false;
			}
			if (必做引导任务.dStep == 4)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点采集任务显示(2, 任务坐标.地图ID, 23777, 13411, 657, 1000, 110445, 100, 200);
				return false;
			}
			if (必做引导任务.dStep == 5)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点采集任务显示(2, 任务坐标.地图ID, 23777, 13411, 657, 1000, 110446, 100, 200);
				return false;
			}
		}
		else
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
			功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 必做引导任务.dQuestId, -1, 100, 必做引导任务.dStep);
			return false;
		}
	}
	if (必做引导任务.dQuestId == 1005006)//最后的问候   
	{
		if (必做引导任务.dState == 1)
		{
			if (必做引导任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 必做引导任务.TargetId, 必做引导任务.dQuestId, -1, 100, 必做引导任务.dStep);
				return false;
			}
			if (必做引导任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 必做引导任务.TargetId, 必做引导任务.dQuestId, -1, 100, 必做引导任务.dStep);
				return false;
			}
			if (必做引导任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				UI功能::内存按键(VK_F5);
				return false;
			}
			if (必做引导任务.dStep == 4)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点按G(2, 任务坐标.地图ID, 15830, 23245, 523, 150);
				return false;
			}
		}
	}
	if (必做引导任务.dQuestId == 1005007)//最后的问候   
	{
		if (必做引导任务.dState == 1)
		{
			if (必做引导任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::寻路到副本(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z);
				return false;
			}
		}
	}
	if (必做引导任务.dQuestId == 1007401)//最后的问候   
	{
		if (必做引导任务.dState == 1)
		{
			if (必做引导任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				加入优先打怪ID(L"190460");
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 2000);
				return false;
			}
			if (必做引导任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 100);
				return false;
			}
			if (必做引导任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点按G(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 150);
				return false;

			}
			if (必做引导任务.dStep == 4)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 100);
				return false;
			}
			if (必做引导任务.dStep == 5)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 必做引导任务.TargetId, 必做引导任务.dQuestId, -1, 100, 必做引导任务.dStep);
				return false;

			}
			if (必做引导任务.dStep == 6)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点按G(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 150);
				return false;

			}
			if (必做引导任务.dStep == 7)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				加入优先打怪ID(L"190378|190382");
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 5000);
				return false;
			}
			if (必做引导任务.dStep == 8)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 100);
				return false;
			}
			if (必做引导任务.dStep == 9)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				加入优先打怪ID(L"190534|190382");
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 5000);
				return false;
			}
			if (必做引导任务.dStep == 10)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 100);
				return false;
			}
			if (必做引导任务.dStep == 11)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				加入优先打怪ID(L"190534|190378");
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 5000);
				return false;
			}
			if (必做引导任务.dStep == 12)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点(2, 任务坐标.地图ID, 4348, 440, -2185, 100);
				return false;
			}
			if (必做引导任务.dStep == 13)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 5000);
				return false;
			}
			if (必做引导任务.dStep == 14)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点按G(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 150);
				return false;

			}
			if (必做引导任务.dStep == 15)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;

			}
			if (必做引导任务.dStep == 16)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 5000);
				return false;
			}
			if (必做引导任务.dStep == 17)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;

			}
			if (必做引导任务.dStep == 18)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 3000);
				return false;
			}
			if (必做引导任务.dStep == 19)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;

			}
			if (必做引导任务.dStep == 20)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 必做引导任务.TargetId, 必做引导任务.dQuestId, -1, 100, 必做引导任务.dStep);
				return false;

			}
			if (必做引导任务.dStep == 21)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				if (功能::到指定地点(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50))
				{
					本人::CALL_演奏乐谱(5);//000001ED650B2E00 名字：心潮如歌
				}
				return false;
			}
			if (必做引导任务.dStep == 22)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}
			if (必做引导任务.dStep == 23)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}
			if (必做引导任务.dStep == 24)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}
			if (必做引导任务.dStep == 25)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				if (功能::到指定地点(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50))
				{
					本人::CALL_演奏乐谱(5);//000001ED650B2E00 名字：心潮如歌
				}
				return false;
			}
			if (必做引导任务.dStep == 26)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}
			if (必做引导任务.dStep == 27)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 3000);
				return false;
			}
			if (必做引导任务.dStep == 28)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}
			if (必做引导任务.dStep == 29)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 3000);
				return false;
			}
			if (必做引导任务.dStep == 30)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				if (功能::到指定地点(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50))
				{
					本人::CALL_演奏乐谱(5);//000001ED650B2E00 名字：心潮如歌
				}
				return false;
			}
			if (必做引导任务.dStep == 31)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}
			if (必做引导任务.dStep == 32)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 必做引导任务.TargetId, 必做引导任务.dQuestId, -1, 100, 必做引导任务.dStep);
				return false;

			}
			if (必做引导任务.dStep == 33)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 必做引导任务.TargetId, 必做引导任务.dQuestId, -1, 100, 必做引导任务.dStep);
				return false;

			}
			if (必做引导任务.dStep == 34)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 必做引导任务.TargetId, 必做引导任务.dQuestId, -1, 100, 必做引导任务.dStep);
				return false;

			}
			if (必做引导任务.dStep == 35)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}
			if (必做引导任务.dStep == 36)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}
			if (必做引导任务.dStep == 37)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 3000);
				return false;
			}
			if (必做引导任务.dStep == 38)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点按G(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 150);
				return false;

			}
		}
	}
	if (必做引导任务.dQuestId == 1005008)//小镇的骄傲   
	{
		if (必做引导任务.dState == 1)
		{
			if (必做引导任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}
			if (必做引导任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 必做引导任务.TargetId, 必做引导任务.dQuestId, -1, 100, 必做引导任务.dStep);
				return false;
			}
			if (必做引导任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 必做引导任务.TargetId, 必做引导任务.dQuestId, -1, 100, 必做引导任务.dStep);
				return false;
			}
			if (必做引导任务.dStep == 4)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 必做引导任务.TargetId, 必做引导任务.dQuestId, -1, 100, 必做引导任务.dStep);
				return false;
			}
			if (必做引导任务.dStep == 5)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 必做引导任务.TargetId, 必做引导任务.dQuestId, -1, 100, 必做引导任务.dStep);
				return false;
			}
		}
	}
	if (必做引导任务.dQuestId == 1005009)//重逢，然后再一次   
	{
		if (必做引导任务.dState == 1)
		{
			if (必做引导任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 必做引导任务.TargetId, 必做引导任务.dQuestId, -1, 100, 必做引导任务.dStep);
				return false;
			}
			if (必做引导任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 必做引导任务.TargetId, 必做引导任务.dQuestId, -1, 100, 必做引导任务.dStep);
				return false;
			}
			if (必做引导任务.dStep == 3)
			{

				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点找NPC交任务3(2, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 必做引导任务.TargetId, 必做引导任务.dQuestId, -1, 100, 必做引导任务.dStep);
				return false;
			}
		}
	}
	if (必做引导任务.dQuestId == 4500401)//重逢，然后再一次   
	{
		if (必做引导任务.dState == 1)
		{
			if (必做引导任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(必做引导任务.dQuestId, 必做引导任务.objBase, 必做引导任务.dResAddr);
				功能::到指定地点找NPC交任务3(22, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 必做引导任务.TargetId, 必做引导任务.dQuestId, -1, 100, 必做引导任务.dStep);
				return false;
			}
		}
	}
	if (必做引导任务.dQuestId == 4002002)//重逢，然后再一次   
	{
		if (必做引导任务.dState == 1)
		{
			if (必做引导任务.dStep == 1)
			{
				if (UI功能::背包界面是否显示())
				{
					背包::使用背包指定物品_ByResId(0xB2429);
				}
				else
				{
					UI功能::内存按键('I');
				}

				return false;
			}
			if (必做引导任务.dStep == 2)
			{
				if (UI功能::背包界面是否显示())
				{
					UI功能::内存按键('I');
					return false;
				}
				if (!UI功能::是否在航海准备界面())
				{
					MyTrace(L"准备出航");
					UI功能::准备出航();
					return false;
				}
			}
			if (必做引导任务.dStep == 3)
			{
				/*if (UI功能::是否在航海准备界面())
				{
					if (!航海::指定船员是否上船(0xB2429))
					{
						航海::VoyageShipAddCrew(0xB2429);
						return false;
					}
					UI功能::航海出港();
					return false;
				}*/
				功能::到指定地点入港(2, 30703, 1684.702, 58610.578, 1, 50);
				return false;
			}
		}
	}

	return true;
}
bool 游戏::世界2(QuestInfo_ 主线任务)
{
	if (主线任务.dQuestId == 705001)//我先讲讲航海的基本常识吧.  
	{
		if (主线任务.dStep == 1)
		{
			if (主线任务.子任务进度.size() == 4)
			{
				if (主线任务.子任务进度[1].dCur == 0)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, -14726, 10256, 384, 20378, 主线任务.dQuestId, -1, 150, 主线任务.dStep);
					return false;
				}
				if (主线任务.子任务进度[2].dCur == 0)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, -14539, 9964, 384, 20379, 主线任务.dQuestId, -1, 150, 主线任务.dStep);
					return false;
				}
				if (主线任务.子任务进度[0].dCur == 0)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, -10766, 14199, 385, 20377, 主线任务.dQuestId, -1, 150, 主线任务.dStep);
					return false;
				}
				if (主线任务.子任务进度[3].dCur == 0)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, -10099, 14570, 384, 20380, 主线任务.dQuestId, -1, 150, 主线任务.dStep);
					return false;
				}
			}

		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点采集任务显示(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 2000, 71048);
			return false;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
	}
	if (主线任务.dQuestId == 705020)//参加比武大会.  
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, -10168, -11378, 381, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 6)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 7)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
	}
	if (主线任务.dQuestId == 705002)//参加比武大会.  
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (任务坐标.x == 0)
			{
				功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, -12914, 10186, 394, 0x4FB0, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			}
			else
			{
				功能::寻路到副本(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z);
			}

			return false;

		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
	}
	if (主线任务.dQuestId == 705401)//参加比武大会.  
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(-10250, 10170, -4, 100, 3000);
			return false;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(-10250, 10170, -4, 100, 3000);
			return false;
		}
	}
	if (主线任务.dQuestId == 705004)//饺子来了!.  
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			ActorInfo_ 角色信息 = 本人::取角色信息();
			if (角色信息.举起状态 == 1)
			{
				功能::到指定地点采集任务显示(3, 任务坐标.地图ID, -9900, -7511, 260, 300, 71007, 100, 150);
			}
			else
			{
				if (功能::到指定地点(3, 任务坐标.地图ID, -10505, -6635, 260, 100))
				{
					UI功能::内存按键('R');
				}
			}

			return false;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
	}
	if (主线任务.dQuestId == 705005)//饺子来了!.  
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, -10071, -7888, 260, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (主线任务.子任务进度.size() == 3)
			{
				if (主线任务.子任务进度[2].dCur == 0)
				{
					功能::到指定地点采集任务显示(3, 任务坐标.地图ID, -5699, 6700, 256, 1000, 71018, 100, 150);
					return false;
				}
				if (主线任务.子任务进度[1].dCur == 0)
				{
					功能::到指定地点采集任务显示(3, 任务坐标.地图ID, -10523, 5227, 384, 1000, 71046, 100, 300);
					return false;
				}
				if (主线任务.子任务进度[0].dCur == 0)
				{
					功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, -10166, -11344, 377, 20388, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
					return false;
				}
			}


		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
	}
	if (主线任务.dQuestId == 705006)//饺子来了!.  
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, -10071, -7888, 260, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点使用指定按键(3, 任务坐标.地图ID, -9857, -7887, 260, 50, VK_F5);
			return false;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点使用指定按键(3, 任务坐标.地图ID, -9857, -7887, 260, 50, VK_F5);
			return false;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点使用指定按键(3, 任务坐标.地图ID, -9857, -7887, 260, 50, VK_F5);
			return false;
		}
		if (主线任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点采集任务显示(3, 任务坐标.地图ID, -9234, -8021, 260, 1000, 71010, 100, 150);
			return false;
		}
		if (主线任务.dStep == 6)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点采集任务显示(3, 任务坐标.地图ID, -9854, -8086, 264, 200, 71011, 100, 150);
			return false;
		}
		if (主线任务.dStep == 7)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
	}
	if (主线任务.dQuestId == 705007)//饺子来了!.  
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (任务坐标.x == 0)
			{
				功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, -12914, 10186, 394, 0x4FB0, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			}
			else
			{
				功能::寻路到副本(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z);
			}
			return false;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
	}
	if (主线任务.dQuestId == 705403)//饺子来了!.  
	{
		if (主线任务.dStep == 1 || 主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(-10480, 10175, -4, 100, 3000);
			return false;
		}
	}
	if (主线任务.dQuestId == 702051)//饺子来了!.  
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点使用指定按键(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50, VK_F5);
			return false;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);

			if (主线任务.子任务进度[0].dCur == 0)
			{
				功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 3526, 5219, 895, 20316, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.子任务进度[0].dCur == 1)
			{
				功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 4386, 5393, 895, 20314, 主线任务.dQuestId, -1, 150, 主线任务.dStep);
				return false;
			}
			if (主线任务.子任务进度[0].dCur == 2)
			{
				功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 4386, 5393, 895, 20315, 主线任务.dQuestId, -1, 150, 主线任务.dStep);
				return false;
			}


		}
		if (主线任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
	}
	if (主线任务.dQuestId == 702052)//饺子来了!.  
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点采集任务显示_多目标(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 2000, 71215, 71216);
			return false;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return false;
		}
		if (主线任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
	}
	if (主线任务.dQuestId == 702053)//满月升起的古宅!.  
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点采集任务显示(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 2000, 71219);
			return false;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::寻路到副本(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z);
			return false;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
	}
	if (主线任务.dQuestId == 710401)//满月升起的古宅!.  
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 2000);
			return false;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::优先破坏击打道具(5000);
			//功能::到指定地点按G(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return false;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 2000);
			return false;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::优先破坏击打道具(5000);
			//功能::到指定地点按G(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return false;
		}
		if (主线任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 2000);
			return false;
		}
		if (主线任务.dStep == 6)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::优先破坏击打道具(5000);
			//功能::到指定地点按G(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return false;
		}
		if (主线任务.dStep == 7)
		{
			if (主线任务.子任务进度.size() == 3)
			{
				if (主线任务.子任务进度[0].dCur == 0)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					加入优先打怪ID(L"172250");
					功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 2000);
					return false;
				}
				if (主线任务.子任务进度[1].dCur == 0)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					加入优先打怪ID(L"172260");
					功能::移动打怪(8124, 7029, -512, 100, 2000);
					return false;
				}
				if (主线任务.子任务进度[2].dCur == 0)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					加入优先打怪ID(L"172270");
					功能::移动打怪(10094, 4764, -379, 100, 5000, 100, true, 300);
					return false;
				}
			}
		}
		if (主线任务.dStep == 8)
		{
			if (主线任务.子任务进度.size() == 2)
			{
				if (主线任务.子任务进度[0].dCur == 0)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					if (功能::优先破坏击打道具(6000))
					{
						加入优先打怪ID(L"172290");
						功能::移动打怪(13798, 1423, -566, 100, 2000);
						return false;
					}

				}
				if (主线任务.子任务进度[1].dCur == 0)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					加入优先打怪ID(L"172292");
					功能::移动打怪(10641, 2729, -509, 100, 2000);
					return false;
				}

			}
		}
		if (主线任务.dStep == 9)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (功能::优先打怪(500))
			{
				if (功能::优先破坏击打道具(500))
				{
					功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 2000);
				}
				else
				{
					//如果优先破坏击打道具 没有找到目标，在这里走到目标位置  ,也不行，  会一直往回走。 还要在想办法。 如果在那个坐标范围内 就往另外一个地方走 走出这个坐标范围
				}
			}

			return false;
		}
		if (主线任务.dStep == 10)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);

			功能::移动打怪(9334, -3102, -446, 100, 2000, 500);

			return false;
		}
	}
	if (主线任务.dQuestId == 705009)//满月升起的古宅!.  
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (任务坐标.x == 0)
			{
				功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, -12914, 10186, 394, 0x4FB0, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			}
			else
			{
				功能::寻路到副本(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z);
			}
			return false;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
	}
	if (主线任务.dQuestId == 705405)//满月升起的古宅!.  
	{

		if (主线任务.dStep == 1 || 主线任务.dStep == 2)
		{
			加入优先打怪ID(L"171080");
			功能::移动打怪(-10480, 10175, -4, 100, 3000);
			return false;
		}

	}
	if (主线任务.dQuestId == 705022)//特殊的机械臂  
	{

		if (主线任务.dStep == 1)
		{
			if (主线任务.子任务进度.size() == 2)
			{
				if (主线任务.子任务进度[1].dCur == 0)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, -5992, 9030, 384, 20379, 主线任务.dQuestId, -1, 150, 主线任务.dStep);
					return false;
				}
				if (主线任务.子任务进度[0].dCur == 0)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, -5992, 9030, 384, 20377, 主线任务.dQuestId, -1, 150, 主线任务.dStep);
					return false;
				}

			}

		}

	}
	if (主线任务.dQuestId == 705010)//满月升起的古宅!.  
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (任务坐标.x == 0)
			{
				功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, -12914, 10186, 394, 0x4FB0, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			}
			else
			{
				功能::寻路到副本(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z);
			}
			return false;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
	}
	if (主线任务.dQuestId == 705406)//满月升起的古宅!.  
	{

		if (主线任务.dStep == 1 || 主线任务.dStep == 2)
		{
			加入优先打怪ID(L"171080");
			功能::移动打怪(-10480, 10175, -4, 100, 3000);
			return false;
		}

	}
	if (主线任务.dQuestId == 705023)//特殊的机械臂  
	{
		if (主线任务.dStep == 1)
		{
			if (主线任务.子任务进度.size() == 2)
			{
				if (主线任务.子任务进度[0].dCur == 0)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, -9098, 11549, 384, 20619, 主线任务.dQuestId, -1, 150, 主线任务.dStep);
					return false;
				}
				if (主线任务.子任务进度[1].dCur == 0)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, -9098, 11549, 384, 20620, 主线任务.dQuestId, -1, 150, 主线任务.dStep);
					return false;
				}

			}

		}

	}
	if (主线任务.dQuestId == 705011)//第五场比武   
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (任务坐标.x == 0)
			{
				功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, -12914, 10186, 394, 0x4FB0, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			}
			else
			{
				功能::寻路到副本(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z);
			}
			return false;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
	}
	if (主线任务.dQuestId == 705407)//满月升起的古宅!.  
	{

		if (主线任务.dStep == 1 || 主线任务.dStep == 2)
		{
			加入优先打怪ID(L"171080");
			功能::移动打怪(-10480, 10175, -4, 100, 3000);
			return false;
		}

	}
	if (主线任务.dQuestId == 706002)//第五场比武   
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"172320|172340");
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 2000);
			return false;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
	}
	if (主线任务.dQuestId == 706003)//第五场比武   
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, -4690, 11378, 1758, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点采集任务显示(3, 任务坐标.地图ID, 12747, 12511, 1322, 2000, 71413);
			return false;
		}
		if (主线任务.dStep == 5)
		{
			UI功能::内存按键(VK_F5);
			return false;
		}
		if (主线任务.dStep == 6)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"71426");
			功能::移动打怪(20534, 12045, 1536, 100, 1000, 100, true, 500);
			return false;
		}
		if (主线任务.dStep == 7)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
	}
	if (主线任务.dQuestId == 706004)//妻子的信    
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
	}
	if (主线任务.dQuestId == 706005)//结界里的恶魔    
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::寻路到副本(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z);
			return false;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
	}
	if (主线任务.dQuestId == 711401)//结界里的恶魔    
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (功能::优先打怪(500))
			{
				if (功能::优先破坏击打道具(1500))
				{
					功能::到指定地点(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				}
			}


			return false;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"173070");
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 2000);
			return false;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"173070");
			if (功能::优先破坏击打道具(2000))
			{
				功能::移动打怪(21695, 9778, -320, 50, 2000);
			}
			return false;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return false;
		}
		if (主线任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return false;
		}
		if (主线任务.dStep == 6)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 2000);
			return false;
		}
		if (主线任务.dStep == 7)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (功能::优先打怪(500))
			{
				objInfo_ 传送对象 = 环境::取指定对象信息(0x1157B);
				if (传送对象.dResShow == 0)
				{
					if (功能::到指定地点(3, 任务坐标.地图ID, 22483, 12301, 593, 50))
					{
						技能::屏蔽鼠标();
						技能::写怪物坐标到鼠标(本人::取坐标());
						UI功能::内存按键('Q');
						Sleep(500);
						UI功能::内存按键('A');
						技能::解除屏蔽鼠标();
					}
				}
				else
				{
					功能::到指定地点(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				}

			}
			return false;
		}
		if (主线任务.dStep == 8)
		{
			/*坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			objInfo_ 宝箱 = 环境::取指定对象信息(0x11754);
			if (宝箱.dResShow == 1)
			{
				功能::到指定地点采集任务显示(3, 任务坐标.地图ID, 23286, 13674, 708, 1000, 0x11754, 100, 200);
				return false;
			}
			else
			{*/
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(21382, 14274, 853, 50, 2000);
			return false;
			//}		
		}
		if (主线任务.dStep == 9)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (功能::优先破坏击打道具(1000))
			{
				功能::到指定地点(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			}
			return false;
		}
		if (主线任务.dStep == 10)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 2000);
			return false;
		}
		if (主线任务.dStep == 11)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return false;
		}
		if (主线任务.dStep == 12)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(16481, 18651, 723, 50, 6000);
			return false;
		}
		if (主线任务.dStep == 13)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return false;
		}
		if (主线任务.dStep == 14)
		{
			if (功能::优先打怪(3000))
			{
				if (功能::优先破坏击打道具(1000))
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				}
			}
			return false;
		}
		if (主线任务.dStep == 15)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			加入优先打怪ID(L"71520");
			if (功能::优先破坏击打道具(3000))
			{
				功能::移动打怪(14864, 14317, 76, 50, 6000);
			}
			return false;
		}
		if (主线任务.dStep == 16)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			objInfo_ 传送对象 = 环境::取指定对象信息(0x1157A);
			if (传送对象.dResShow == 0)
			{
				if (功能::到指定地点(3, 任务坐标.地图ID, 12732, 14199, 65, 50))
				{
					技能::屏蔽鼠标();
					技能::写怪物坐标到鼠标(本人::取坐标());
					UI功能::内存按键('Q');
					Sleep(500);
					UI功能::内存按键('A');
					技能::解除屏蔽鼠标();
				}
			}
			else
			{
				功能::到指定地点(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			}
			return false;
		}
		if (主线任务.dStep == 17)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			objInfo_ 传送对象 = 环境::取指定对象信息(0x1157B);
			if (传送对象.dResShow == 0)
			{
				if (功能::到指定地点(3, 任务坐标.地图ID, 11329, 17384, -256, 50))
				{
					if (功能::优先打怪(1500))
					{
						技能::屏蔽鼠标();
						技能::写怪物坐标到鼠标(本人::取坐标());
						UI功能::内存按键('Q');
						Sleep(500);
						UI功能::内存按键('A');
						技能::解除屏蔽鼠标();
					}

				}
			}
			else
			{
				功能::到指定地点(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			}
			return false;
		}
		if (主线任务.dStep == 18)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(8309, 16975, 363, 50, 5000);
			return false;

		}
		if (主线任务.dStep == 19)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return false;

		}
		if (主线任务.dStep == 20)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 3000, 1500);
			return false;

		}
		if (主线任务.dStep == 21)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return false;
		}
		if (主线任务.dStep == 22)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 3000, 1500);
			return false;
		}
	}
	if (主线任务.dQuestId == 705013)//第六场比武    
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (任务坐标.x == 0)
			{
				功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, -12914, 10186, 394, 0x4FB0, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			}
			else
			{
				功能::寻路到副本(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z);
			}
			return false;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
	}
	if (主线任务.dQuestId == 705409)//第六场比武    
	{

		if (主线任务.dStep == 1 || 主线任务.dStep == 2)
		{
			功能::移动打怪(-10480, 10175, -4, 100, 3000);
			return false;
		}

	}
	if (主线任务.dQuestId == 705021)//第六场比武    
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 2)
		{
			UI功能::内存按键(VK_F5);
			return false;
		}
		if (主线任务.dStep == 3)
		{
			UI功能::内存按键(VK_F5);
			return false;
		}
		if (主线任务.dStep == 4)
		{
			UI功能::内存按键(VK_F5);
			return false;
		}
		if (主线任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 6)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 7)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 8)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
	}
	if (主线任务.dQuestId == 707001)//第六场比武    
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 2)
		{
			if (主线任务.子任务进度.size() == 3)
			{
				if (主线任务.子任务进度[0].dCur < 主线任务.子任务进度[0].dNeed)
				{
					加入优先打怪ID(L"71616");
					功能::移动打怪(-10569, 4818, 1600, 100, 3000);
					return false;
				}
				if (主线任务.子任务进度[2].dCur < 主线任务.子任务进度[2].dNeed)
				{
					功能::到指定地点采集任务显示(3, 10723, -7644, 8896, 2153, 3000, 71619);
					return false;
				}
				if (主线任务.子任务进度[1].dCur < 主线任务.子任务进度[1].dNeed)
				{
					加入优先打怪ID(L"71615");
					功能::移动打怪(-10013, 9661, 1700, 100, 3000);
					return false;
				}
			}
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
	}
	if (主线任务.dQuestId == 707002)//第六场比武    
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
	}
	if (主线任务.dQuestId == 707003)//第六场比武    
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 2)
		{
			加入优先打怪ID(L"173290|173300|173310");
			功能::移动打怪(-17243, 15931, 1700, 100, 3000);
			return false;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
	}
	if (主线任务.dQuestId == 707004)//打落怪鸟的力量    
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
	}
	if (主线任务.dQuestId == 707005)//破灭的征兆      
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (主线任务.子任务进度.size() == 3)
			{
				if (主线任务.子任务进度[2].dCur == 0)
				{
					功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, -19269, 16894, 1600, 20501, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
					return false;
				}
				if (主线任务.子任务进度[0].dCur == 0)
				{
					功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, -19573, 16646, 1600, 20507, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
					return false;
				}
				if (主线任务.子任务进度[1].dCur == 0)
				{
					功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, -19439, 17110, 1600, 20500, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
					return false;
				}

			}
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
	}
	if (主线任务.dQuestId == 705015)//第七场比武    
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (任务坐标.x == 0)
			{
				功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, -12914, 10186, 394, 0x4FB0, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			}
			else
			{
				功能::寻路到副本(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z);
			}
			return false;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
	}
	if (主线任务.dQuestId == 705412)//第七场比武    
	{

		if (主线任务.dStep == 1 || 主线任务.dStep == 2)
		{
			功能::移动打怪(-10480, 10175, -4, 100, 3000);
			return false;
		}

	}
	if (主线任务.dQuestId == 705024)//第七场比武    
	{
		if (主线任务.dStep == 1)
		{
			if (主线任务.子任务进度[0].dCur == 0)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, -9586, 14672, 384, 20494, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.子任务进度[1].dCur == 0)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, -9586, 14672, 384, 20495, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
		}

	}
	if (主线任务.dQuestId == 705016)//第八场比武      
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (任务坐标.x == 0)
			{
				功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, -12914, 10186, 394, 0x4FB0, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			}
			else
			{
				功能::寻路到副本(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z);
			}
			return false;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 6)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
	}
	if (主线任务.dQuestId == 705413)//第八场比武 
	{

		if (主线任务.dStep == 1 || 主线任务.dStep == 2)
		{
			功能::移动打怪(-10480, 10175, -4, 100, 3000);
			return false;
		}

	}
	if (主线任务.dQuestId == 708003)//进入雾气之中      
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (主线任务.子任务进度.size() == 3)
			{

				if (主线任务.子任务进度[0].dCur == 0)
				{
					功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 3309, 15861, 2560, 20412, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
					return false;
				}
				if (主线任务.子任务进度[1].dCur == 0)
				{
					功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 5573, 10596, 2048, 20411, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
					return false;
				}
				if (主线任务.子任务进度[2].dCur == 0)
				{
					功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 5879, 6231, 2304, 20410, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
					return false;
				}
			}
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
	}
	if (主线任务.dQuestId == 708004)//狂人的引导      
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点使用表情(3, 任务坐标.地图ID, 11826, 9170, 2175, 100, 62027);
			return false;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 4)
		{
			加入优先打怪ID(L"174580|174520|174590");
			功能::移动打怪(13858, 13222, 1536, 100, 3000);
			return false;
		}
		if (主线任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
	}
	if (主线任务.dQuestId == 708005)//幻术之源        
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (主线任务.子任务进度.size() == 4)
			{

				if (主线任务.子任务进度[2].dCur == 0)
				{
					功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 20545, 18293, 1024, 20504, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
					return false;
				}
				if (主线任务.子任务进度[1].dCur == 0)
				{
					功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 20916, 16095, 1280, 20503, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
					return false;
				}
				if (主线任务.子任务进度[3].dCur == 0)
				{
					功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 21811, 16983, 1280, 20505, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
					return false;
				}
				if (主线任务.子任务进度[0].dCur == 0)
				{
					功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 22793, 18639, 1280, 20502, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
					return false;
				}
			}
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return false;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::寻路到副本(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z);
			return false;
		}
		if (主线任务.dStep == 5)
		{
			if (地图::取地图ID() == 10764)
			{
				本人::CALL_演奏乐谱(1);
				Sleep(10000);
				return false;
			}
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 6)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
	}
	if (主线任务.dQuestId == 717401)// 守魂的怪物          
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return false;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 100);
			return false;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return false;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 150);
			return false;
		}
		if (主线任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(3, 任务坐标.地图ID, -3179, 5432, 1024, 150);
			return false;
		}
		if (主线任务.dStep == 6)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(-3179, 5432, 1024, 100, 1000);
			return false;
		}
		if (主线任务.dStep == 7)
		{
			if (主线任务.子任务进度.size() == 2)
			{
				if (主线任务.子任务进度[0].dCur == 0)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点按G(3, 任务坐标.地图ID, -1987, 4004, 1024, 150, 200);
					return false;
				}
				if (主线任务.子任务进度[1].dCur == 0)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点按G(3, 任务坐标.地图ID, -5117, 4567, 1025, 150, 200);
					return false;
				}
			}
		}
		if (主线任务.dStep == 8)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(3, 任务坐标.地图ID, -2988, 3778, 1024, 200);
			return false;
		}
		if (主线任务.dStep == 9)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(-3320, 3947, 1024, 100, 3000);
			return false;
		}
	}
	if (主线任务.dQuestId == 708008)//幻术之源        
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 2)
		{
			if (主线任务.子任务进度.size() == 2)
			{
				if (主线任务.子任务进度[0].dCur < 主线任务.子任务进度[0].dNeed)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点采集任务显示(3, 任务坐标.地图ID, 11077, 14545, 1280, 3000, 71911);
					return false;
				}
				if (主线任务.子任务进度[1].dCur < 主线任务.子任务进度[1].dNeed)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					加入优先打怪ID(L"174520|174500|174580|850057|174530");
					功能::移动打怪(11077, 14545, 1280, 150, 2000);
					return false;
				}
			}

		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
	}
	if (主线任务.dQuestId == 705018)//第九场比武      
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (任务坐标.x == 0)
			{
				功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, -12914, 10186, 394, 0x4FB0, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			}
			else
			{
				功能::寻路到副本(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z);
			}
			return false;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}


	}
	if (主线任务.dQuestId == 705415)//第九场比武 
	{

		if (主线任务.dStep == 1 || 主线任务.dStep == 2)
		{
			加入优先打怪ID(L"171230");
			功能::移动打怪(-10480, 10175, -4, 100, 3000);
			return false;
		}

	}
	if (主线任务.dQuestId == 708007)//在地狱的门槛      
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::寻路到副本(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z);
			return false;
		}
		if (主线任务.dStep == 3)
		{
			if (地图::取地图ID() == 10765)
			{
				本人::CALL_演奏乐谱(1);
				Sleep(10000);
				return false;
			}
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
	}
	if (主线任务.dQuestId == 713401)//在地狱的门槛      
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return false;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(1631, 3649, 2815, 100, 2000);
			return false;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(4113, 3407, 2813, 100, 2000);
			return false;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 2000);
			return false;
		}
		if (主线任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return false;
		}
		if (主线任务.dStep == 6)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 2000);
			return false;
		}
		if (主线任务.dStep == 7)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (功能::优先打怪(5000))
			{
				功能::到指定地点(3, 任务坐标.地图ID, 11004, 6609, 2304, 50);

			}

			return false;
		}
		if (主线任务.dStep == 8)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 2000);
			return false;
		}
		if (主线任务.dStep == 9)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return false;
		}
		if (主线任务.dStep == 10)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 2000);
			return false;
		}
		if (主线任务.dStep == 11)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return false;
		}
		if (主线任务.dStep == 12)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 2000);
			return false;
		}
		if (主线任务.dStep == 13)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (功能::优先打怪(5000))
			{
				功能::到指定地点(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			}
			return false;
		}
		if (主线任务.dStep == 14)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (功能::优先破坏击打道具(1000))
			{
				if (功能::优先打怪(1000))
				{
					功能::到指定地点(3, 任务坐标.地图ID, 12523, 7740, -7, 150);
				}
			}
			return false;
		}
		if (主线任务.dStep == 15)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (功能::优先打怪(5000))
			{
				功能::到指定地点(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			}
			return false;
		}
		if (主线任务.dStep == 16)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 2000);
			return false;
		}
		if (主线任务.dStep == 17)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (功能::优先打怪(5000))
			{
				功能::到指定地点(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			}
			return false;
		}
		if (主线任务.dStep == 18)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (功能::优先打怪(5000))
			{
				功能::到指定地点(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			}
			return false;
		}
		if (主线任务.dStep == 19)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 2000);
			return false;
		}
	}
	if (主线任务.dQuestId == 705019)//在地狱的门槛      
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
		}
		else
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0x4F71, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}

	}
	if (主线任务.dQuestId == 705025)//在地狱的门槛      
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点使用指定按键(3, 任务坐标.地图ID, -4510, 15707, 519, 50, VK_F5);
				return false;
			}
			if (主线任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点使用指定按键(3, 任务坐标.地图ID, -4510, 15707, 519, 50, VK_F5);
				return false;
			}
		}
		else
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(3, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0x4F9F, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
	}
	if (主线任务.dQuestId == 4002003)//在地狱的门槛      
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(3, 30703, 1805, 58552, 1, 50);
				return false;
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(3, 30703, 26659, 53067, 1, 50);
				return false;
			}
			if (主线任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点入港(3, 30703, 任务坐标.x, 任务坐标.y, 1, 50);
				return false;
			}
		}
	}
	return true;
}
bool 游戏::世界3(QuestInfo_ 主线任务)
{
	if (主线任务.dQuestId == 306001)//我先讲讲航海的基本常识吧.  
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				if (主线任务.子任务进度.size() == 4)
				{
					if (主线任务.子任务进度[0].dCur == 0)
					{
						功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, -19321, 3274, 470, 18006, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
						return false;
					}
					if (主线任务.子任务进度[3].dCur == 0)
					{
						功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, -21044, 4764, 673, 18022, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
						return false;
					}
					if (主线任务.子任务进度[2].dCur == 0)
					{
						功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, -22338, 8406, 681, 18005, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
						return false;
					}
					if (主线任务.子任务进度[1].dCur == 0)
					{
						功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, -24293, 8510, 681, 18004, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
						return false;
					}
				}

			}
		}
		else
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, -23216, 5626, 547, 18002, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}

	}
	if (主线任务.dQuestId == 306002)//我先讲讲航海的基本常识吧.  
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, -23290, 5645, 547, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, -15801, 12924, 1246, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, -15801, 12924, 1246, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 4)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点采集任务显示(4, 任务坐标.地图ID, -15444, 10956, 2260, 2000, 42132);
				return false;
			}
			if (主线任务.dStep == 5)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, -15801, 12924, 1246, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 6)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, -15801, 12924, 1246, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 7)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
		}
		else
		{

			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, -15801, 12924, 1246, 18013, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;

		}
	}
	if (主线任务.dQuestId == 306003)//我先讲讲航海的基本常识吧.  
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 2)
			{
				UI功能::内存按键(VK_F5);
				return false;
			}
			if (主线任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::寻路到副本(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z);
				return false;
			}
			if (主线任务.dStep == 4)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
		}
	}
	if (主线任务.dQuestId == 306401)//我先讲讲航海的基本常识吧.  
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 2000);
				return false;
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点按G(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 100);
				return false;
			}
			if (主线任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 2000);
				return false;
			}
			if (主线任务.dStep == 4)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点按G(4, 任务坐标.地图ID, -3452, 12584, 2997, 100);
				return false;
			}
			if (主线任务.dStep == 5)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}
			if (主线任务.dStep == 6)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点使用指定按键(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50, VK_F5);
				return false;
			}
			if (主线任务.dStep == 7)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点按G(4, 任务坐标.地图ID, -2853, 11583, 3085, 25);
				return false;
			}
			if (主线任务.dStep == 8)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点按G(4, 任务坐标.地图ID, -2592, 11346, 3112, 50);
				return false;
			}
			if (主线任务.dStep == 9)
			{
				if (UI功能::怪物击杀求饶界面是否打开())
				{
					UI功能::内存按键('G');
					return false;
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
					return false;
				}

			}

		}
	}
	if (主线任务.dQuestId == 306004)//我先讲讲航海的基本常识吧.  
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, -21021, 4761, 673, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, -19870, 5394, 767, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, -19870, 5394, 767, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 4)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, -19624, 5114, 769, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 5)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, -19624, 5114, 769, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
		}
	}
	if (主线任务.dQuestId == 305001)//我先讲讲航海的基本常识吧.  
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}
			if (主线任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}
			if (主线任务.dStep == 4)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 5)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				if (主线任务.子任务进度.size() == 2)
				{
					if (主线任务.子任务进度[1].dCur == 0)
					{
						功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 6707, 11832, 512, 18026, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
						return false;
					}
					if (主线任务.子任务进度[0].dCur == 0)
					{
						功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 9246, 12145, 820, 18025, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
						return false;
					}
				}

			}
			if (主线任务.dStep == 6)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 7)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点采集任务显示(4, 任务坐标.地图ID, 11814, 9180, 774, 1000, 41031);
				return false;
			}
		}
	}
	if (主线任务.dQuestId == 305002)//我先讲讲航海的基本常识吧.  
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				环境::加入优先采集ID(L"41041|41032|41021|41061");
				功能::到指定地点采集任务显示(4, 任务坐标.地图ID, 7278, 7383, 653, 1000, 0xA051);
				return false;
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}
			if (主线任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
		}
		else
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
	}
	if (主线任务.dQuestId == 305003)//我先讲讲航海的基本常识吧.  
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}
			if (主线任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 4)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点采集任务显示(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 3000, 41044);
				return false;
			}
			if (主线任务.dStep == 5)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 6)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
		}
		else
		{

			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;

		}
	}
	if (主线任务.dQuestId == 305004)//我先讲讲航海的基本常识吧.  
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 10396, 48671, -12, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 18720, 16221, 1028, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 2481, 72117, -446, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 4)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点采集任务显示(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 1000, 41083, 100, 200);
				return false;
			}
			if (主线任务.dStep == 5)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 6)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}
			if (主线任务.dStep == 7)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 8)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 9)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点使用指定按键(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50, VK_F5);
				return false;
			}
			if (主线任务.dStep == 10)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 11)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
		}
		else
		{

			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;

		}
	}
	if (主线任务.dQuestId == 307001)//我先讲讲航海的基本常识吧.  
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 2)
			{
				背包::使用背包指定物品_ByResId(205008);
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				加入优先打怪ID(L"141360");
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 3000);
				return false;
			}
			if (主线任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 15402, 7334, 2244, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 4)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点采集任务显示(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 5000, 42221, 100, 200);
				return false;
			}
			if (主线任务.dStep == 5)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点采集任务显示(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 5000, 42222, 100, 200);
				return false;
			}
		}
		else
		{

			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
	}
	if (主线任务.dQuestId == 307002)//我先讲讲航海的基本常识吧.  
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 15392, 7166, 2245, 0x46FD, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				ActorInfo_ 角色信息 = 本人::取角色信息();
				if (角色信息.举起状态 == 1)
				{
					功能::到指定地点采集任务显示(4, 任务坐标.地图ID, 11259, 18719, 1918, 6000, 42248, 100, 200);
					return false;
				}
				else
				{
					功能::到指定地点使用指定按键(4, 任务坐标.地图ID, 13829, 18567, 1931, 50, 'R');
					return false;
				}

			}
			if (主线任务.dStep == 4)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点采集任务显示(4, 任务坐标.地图ID, 13829, 18567, 1931, 6000, 42250, 100, 200);
				return false;
			}
			if (主线任务.dStep == 5)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				环境::加入优先采集ID(L"42247|42246|42244|42245|42241");
				功能::到指定地点采集任务显示(4, 任务坐标.地图ID, 13276, 18997, 1923, 6000, 42247, 100, 200);
				return false;
			}
			if (主线任务.dStep == 6)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
		}
		else
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
	}
	if (主线任务.dQuestId == 307003)//我先讲讲航海的基本常识吧.  
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 15392, 7166, 2245, 0x467C, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::寻路到副本(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z);
				return false;
			}
			if (主线任务.dStep == 4)
			{
				if (地图::取地图ID() == 10432)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点按G(4, 10432, 27580, 7833, 1541, 50);
					return false;
				}
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
		}
		else
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
	}
	if (主线任务.dQuestId == 307401)//我先讲讲航海的基本常识吧.  
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				if (主线任务.子任务进度.size() == 2)
				{
					if (主线任务.子任务进度[0].dCur < 主线任务.子任务进度[0].dNeed)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
						加入优先打怪ID(L"42285");
						功能::移动打怪(24687, 4361, 1553, 100, 5000, 1000);
						return false;
					}
					if (主线任务.子任务进度[1].dCur < 主线任务.子任务进度[1].dNeed)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
						加入优先打怪ID(L"141340|141350");
						功能::移动打怪(24359, 6796, 1545, 100, 6000, 1000);
						return false;
					}
				}
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点按G(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 150);
				return false;
			}
			if (主线任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 150);
				return false;
			}
			if (主线任务.dStep == 4)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::移动打怪(27362, 7804, 1545, 150, 6000);
				return false;
			}
		}
	}
	if (主线任务.dQuestId == 307004)//我先讲讲航海的基本常识吧.  
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}
			if (主线任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 4)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点采集任务显示(4, 任务坐标.地图ID, 24378, 16264, 1543, 3000, 42262, 200, 200);
				return false;
			}
			if (主线任务.dStep == 5)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点采集任务显示(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 3000, 42264, 300, 200);
				return false;
			}
			if (主线任务.dStep == 6)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 7)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 8)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
		}
		else
		{

			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;

		}
	}
	if (主线任务.dQuestId == 308001)//我先讲讲航海的基本常识吧.  
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 10423, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 10423, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}

		}
		else
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
	}
	if (主线任务.dQuestId == 308401)//我先讲讲航海的基本常识吧.  
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::移动打怪(-22603, 10070, 3072, 150, 6000);
				return false;
			}
			if (主线任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
		}

	}
	if (主线任务.dQuestId == 308002)//我先讲讲航海的基本常识吧.  
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::移动打怪(-2365, 26801, 1515, 150, 6000);
				return false;
			}
			if (主线任务.dStep == 4)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
		}
	}
	if (主线任务.dQuestId == 308003)//我先讲讲航海的基本常识吧.  
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 100);
				return false;
			}
			if (主线任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				加入优先打怪ID(L"141820|141810|141950");
				功能::移动打怪(-23092, 26410, 1536, 150, 3000);
				return false;
			}
			if (主线任务.dStep == 4)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 100);
				return false;
			}
			if (主线任务.dStep == 5)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 6)
			{

				if (GetDis(-16230, 14198, 3340) < 5000)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
					return false;
				}
				else
				{
					if (地图::传送点是否激活(0xDBF43))
					{
						地图::传送(0xDBF43);
						return false;
					}
					else
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
						功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
						return false;
					}
				}

			}
		}
	}
	if (主线任务.dQuestId == 308004)//营救 
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}
		}
	}
	if (主线任务.dQuestId == 308005)//营救 
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::寻路到副本(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z);
				return false;
			}
			if (主线任务.dStep == 2)
			{
				if (地图::取地图ID() != 10423)
				{
					if (地图::传送点是否激活(0xDBF43))
					{
						地图::传送(0xDBF43);
					}
					else
					{
						本人::CALL_演奏乐谱(1);
						Sleep(10000);
					}
					return false;
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
					return false;
				}

			}
			if (主线任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 200, 主线任务.dStep);
				return false;
			}

		}
		else
		{
			if (地图::取地图ID() != 10401)
			{
				if (地图::传送点是否激活(900901))
				{
					地图::传送(900901);
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 主线任务.dQuestId, -1, 200, 主线任务.dStep);

				}
				return false;
			}
			else
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 主线任务.dQuestId, -1, 200, 主线任务.dStep);
				return false;
			}

		}
	}
	if (主线任务.dQuestId == 308402)//被堵住的入口 
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}
			if (主线任务.dStep == 4)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::移动打怪(-31103, -14248, 6611, 150, 5000);
				return false;
			}
			if (主线任务.dStep == 5)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点按G(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 150);
				return false;
			}
			if (主线任务.dStep == 6)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}
			if (主线任务.dStep == 7)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}

		}
	}
	if (主线任务.dQuestId == 308403)//突破机械室1区域 
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				if (功能::优先破坏击打道具(500))
				{
					功能::到指定地点(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);

				}
				return false;
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 150, 3000);
				return false;
			}
			if (主线任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点按G(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 150);
				return false;
			}
			if (主线任务.dStep == 4)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}
			if (主线任务.dStep == 5)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 150, 3000);
				return false;
			}
			if (主线任务.dStep == 6)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点按G(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 150);
				return false;
			}
		}
	}
	if (主线任务.dQuestId == 308404)//突破机械室1区域 
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				if (功能::优先破坏击打道具(500))
				{
					功能::到指定地点(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
					return false;
				}
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点按G(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 150);
				return false;
			}
			if (主线任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 150);
				return false;
			}
			if (主线任务.dStep == 4)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 150);
				return false;
			}
		}
	}
	if (主线任务.dQuestId == 308405)//机器人工厂
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				if (功能::优先破坏击打道具(500))
				{
					功能::到指定地点(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
					return false;
				}
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点按G(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 150);
				return false;
			}
			if (主线任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				if (功能::优先破坏击打道具(3000))
				{
					功能::到指定地点按G(4, 任务坐标.地图ID, 11623, -15869, 3359, 150);

				}
				return false;
			}
			if (主线任务.dStep == 4)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点按G(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 150);
				return false;
			}
			if (主线任务.dStep == 5)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				if (功能::优先破坏击打道具(3000))
				{
					功能::到指定地点按G(4, 任务坐标.地图ID, 17435, -8104, 3893, 150);

				}
				return false;
			}
			if (主线任务.dStep == 6)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 150);
				return false;
			}
			if (主线任务.dStep == 7)
			{
				if (本人::是否在骑马() == false)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点按G(4, 任务坐标.地图ID, 21665, -282, 2610, 50);
				}
				else
				{
					if (功能::优先破坏击打道具(3000))
					{
						if (功能::优先打怪(3000))
						{
							坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
							功能::到指定地点(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 150);
						}

					}
				}

				return false;
			}
			if (主线任务.dStep == 8)
			{
				if (功能::优先破坏击打道具(3000))
				{

				}
				return false;
			}
			if (主线任务.dStep == 9)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 150);
				return false;
			}
		}
	}
	if (主线任务.dQuestId == 308406)//执着的追击者
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				if (功能::优先破坏击打道具(1500))
				{
					功能::到指定地点(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);

				}
				return false;
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}
			if (主线任务.dStep == 3)
			{
				功能::移动打怪(41155, 4767, 1979, 100, 5000);
				return false;
			}
			if (主线任务.dStep == 4)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}
			if (主线任务.dStep == 5)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(4, 任务坐标.地图ID, 44326, 3204, 1204, 50);
				return false;
			}

		}
	}
	if (主线任务.dQuestId == 308407)//执着的追击者
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				if (功能::优先打怪(5000))
				{

				}
				return false;
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}
			if (主线任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				if (功能::优先打怪(5000))
				{

				}
				return false;
			}
			if (主线任务.dStep == 4)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				if (功能::优先破坏击打道具(5000))
				{
					功能::到指定地点(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				}
				return false;
			}
			if (主线任务.dStep == 5)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}

		}
	}
	if (主线任务.dQuestId == 308408)//守住心脏
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				if (功能::优先打怪(5000))
				{
					功能::移动打怪(4, 任务坐标.地图ID, 32059, -16509, 4669, 50);
				}
				return false;
			}
			if (主线任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 4)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点按G(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 150);
				return false;
			}
		}
	}
	if (主线任务.dQuestId == 305005)//营救 
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 3)
			{
				if (主线任务.子任务进度.size() == 4)
				{
					if (主线任务.子任务进度[0].dCur == 0)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
						功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 10546, 46424, -6, 18035, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
						return false;
					}
					if (主线任务.子任务进度[1].dCur == 0)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
						功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 10913, 46428, -6, 18036, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
						return false;
					}
					if (主线任务.子任务进度[2].dCur == 0)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
						功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 10868, 47004, -6, 18037, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
						return false;
					}
					if (主线任务.子任务进度[3].dCur == 0)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
						功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 10556, 47010, -6, 18038, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
						return false;
					}
				}

			}
			if (主线任务.dStep == 4)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
		}
		else
		{

			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;

		}
	}
	if (主线任务.dQuestId == 309001)//卡因的去向  
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				加入优先打怪ID(L"142130|142150");
				功能::移动打怪(20842, 8106, -629, 100, 1500);
				return false;
			}
			if (主线任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				加入优先打怪ID(L"142130|142150");
				功能::到指定地点采集任务显示(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 1000, 42411, 100, 250);
				return false;
			}
		}
		else
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
	}
	if (主线任务.dQuestId == 309002)// 废弃场的血斗    
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 3)
			{
				if (环境::取指定任务显示对象信息(0xA5A7).dResShow == 1)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::寻路到副本(4, 任务坐标.地图ID, 15360, 7235, -280);
					return false;
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
					return false;
				}

			}
		}
		else
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
	}
	if (主线任务.dQuestId == 309401)// 废弃场的血斗    
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				加入优先打怪ID(L"142290");
				功能::移动打怪(20683, 7768, -640, 100, 3000, 1000);
				return false;
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}
			if (主线任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				加入优先打怪ID(L"142290");
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 3000, 1000);
				return false;
			}
			if (主线任务.dStep == 4)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				加入优先打怪ID(L"142290");
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 3000, 1000);
				return false;
			}
			if (主线任务.dStep == 5)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				加入优先打怪ID(L"142290");
				功能::移动打怪(18702, 8499, -9, 100, 6000, 1000);
				return false;
			}
			if (主线任务.dStep == 6)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点按G(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 150);
				return false;
			}
			if (主线任务.dStep == 7)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}
			if (主线任务.dStep == 8)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 5000, 1000);
				return false;
			}
		}
	}
	if (主线任务.dQuestId == 309003)// 机械兵团歼灭战      
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点按G(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 150);
				return false;
			}
		}
		else
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
	}
	if (主线任务.dQuestId == 3010001)// 机械兵团歼灭战      
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 150);
				return false;
			}
			if (主线任务.dStep == 2)
			{
				if (主线任务.子任务进度[0].dCur == 0)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 14256, 10402, 0, 18070, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
					return false;
				}
				if (主线任务.子任务进度[1].dCur == 0)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 11420, 11883, 0, 18071, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
					return false;
				}
				if (主线任务.子任务进度[2].dCur == 0)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 11066, 8785, 0, 18072, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
					return false;
				}
			}
			if (主线任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点采集任务显示(4, 任务坐标.地图ID, 13572, 9121, 169, 1000, 42517, 100, 200);
				return false;
			}
			if (主线任务.dStep == 4)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点采集任务显示(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 2000, 42519, 100, 200);
				return false;
			}
			if (主线任务.dStep == 5)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点采集任务显示(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 2000, 42518, 100, 200);
				return false;
			}
			if (主线任务.dStep == 6)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点采集任务显示(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 2000, 42520, 100, 200);
				return false;
			}
			if (主线任务.dStep == 7)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				加入优先打怪ID(L"142440|142500");
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 5000, 150);
				return false;
			}
			if (主线任务.dStep == 8)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 9)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 10)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 11)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
		}
		else
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
	}
	if (主线任务.dQuestId == 3010002)// 消灭监视者们        
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 10581, 41420, 135, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 2)
			{
				if (主线任务.子任务进度[0].dCur < 主线任务.子任务进度[0].dNeed)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点采集任务显示(4, 任务坐标.地图ID, 8054, 6698, 0, 3000, 42515, 300, 200);
					return false;
				}
				if (主线任务.子任务进度[1].dCur < 主线任务.子任务进度[1].dNeed)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					加入优先打怪ID(L"142500");
					功能::移动打怪(8054, 6698, 0, 100, 5000, 150);
					return false;
				}
			}
		}
		else
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
	}
	if (主线任务.dQuestId == 3010003)// 消灭监视者们        
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::寻路到副本(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z);
				return false;
			}

		}
		else
		{
			if (地图::取地图ID() == 10462)
			{
				本人::CALL_演奏乐谱(1);
				Sleep(10000);
				return false;
			}
			else
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
		}
	}
	if (主线任务.dQuestId == 3013401)// 追踪艾斯与杰伊        
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点按G(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 150);
				return false;
			}
			if (主线任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}
			if (主线任务.dStep == 4)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				加入优先打怪ID(L"143130");
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 5000, 150);
				return false;
			}
			if (主线任务.dStep == 5)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				加入优先打怪ID(L"143110|143120|143130");
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 5000, 150);
				return false;
			}
			if (主线任务.dStep == 6)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}
			if (主线任务.dStep == 7)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点按G(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 150);
				return false;
			}
			if (主线任务.dStep == 8)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				加入优先打怪ID(L"143200");
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 5000, 150);
				return false;
			}
			if (主线任务.dStep == 9)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点按G(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 250);
				return false;
			}
			if (主线任务.dStep == 10)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}
			if (主线任务.dStep == 11)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}

		}
	}
	if (主线任务.dQuestId == 3013402)// 关闭的大门        
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				加入优先打怪ID(L"143180|143190");
				//功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 10000, 10000);//8971.000  8318.000  -318.343
				功能::移动打怪(8971, 8318, -318, 100, 10000, 10000);
				return false;
			}
			if (主线任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}
			if (主线任务.dStep == 4)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点按G(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 250, 700);
				return false;
			}
			if (主线任务.dStep == 5)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				加入优先打怪ID(L"143210");
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 5000, 2000);
				return false;
			}
			if (主线任务.dStep == 6)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点按G(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 250);
				return false;
			}
			if (主线任务.dStep == 7)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点按G(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 250);
				return false;
			}
			if (主线任务.dStep == 8)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}
			if (主线任务.dStep == 9)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 5000, 2000);
				return false;
			}
		}
	}
	if (主线任务.dQuestId == 3013403)// 关闭的大门        
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 5000, 2000);
				return false;
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点按G(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 250);
				return false;
			}
		}
	}
	if (主线任务.dQuestId == 305006)// 消灭监视者们        
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				if (地图::取地图ID() != 10401)
				{
					if (地图::传送点是否激活(0xDBF25))
					{
						地图::传送(0xDBF25);
						return false;
					}
					else
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
						功能::到指定地点(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
						return false;
					}
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
					return false;
				}

			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}

		}
		else
		{

			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;

		}
	}
	if (主线任务.dQuestId == 3011001)// 消灭监视者们        
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				加入优先打怪ID(L"142790");
				功能::移动打怪(787, 8068, 512, 100, 3000);
				return false;
			}
			if (主线任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点采集任务显示(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 3000, 42620, 100, 200);
				return false;
			}
			if (主线任务.dStep == 4)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 5)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 6)
			{
				if (主线任务.子任务进度.size() == 4)
				{
					if (主线任务.子任务进度[0].dCur < 主线任务.子任务进度[0].dNeed)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
						加入优先打怪ID(L"142661");
						功能::移动打怪(13243, 3667, 1024, 100, 3000);
						return false;
					}
					if (主线任务.子任务进度[1].dCur < 主线任务.子任务进度[1].dNeed)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
						加入优先打怪ID(L"142662");
						功能::移动打怪(13899, 7925, 1024, 100, 3000);
						return false;
					}
					if (主线任务.子任务进度[2].dCur < 主线任务.子任务进度[2].dNeed)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
						加入优先打怪ID(L"142663");
						功能::移动打怪(16595, 11398, 1024, 100, 3000);
						return false;
					}
					if (主线任务.子任务进度[3].dCur < 主线任务.子任务进度[3].dNeed)
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
						加入优先打怪ID(L"142664");
						功能::移动打怪(15406, 14050, 1024, 100, 3000);
						return false;
					}
				}

			}
			if (主线任务.dStep == 7)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 8)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点采集任务显示(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 3000, 42641, 100, 200);
				return false;
			}
		}
		else
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 18094, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
	}
	if (主线任务.dQuestId == 3011002)// 消灭监视者们        
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::寻路到副本(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z);
				return false;
			}
		}
		else
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
	}
	if (主线任务.dQuestId == 3011401)// 消灭监视者们        
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				if (功能::优先打怪(5000))
				{
					功能::到指定地点按G(4, 任务坐标.地图ID, 22704, 14465, 1413, 50);
				}

				return false;
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				ActorInfo_ 角色信息 = 本人::取角色信息();
				if (角色信息.坐标.z < 1680)
				{
					if (功能::到指定地点(4, 任务坐标.地图ID, 21853, 15379, 1689, 50))
					{
						功能::优先破坏击打道具(200);

					}
				}
				else
				{
					if (功能::优先破坏击打道具(200))
					{
						if (功能::优先打怪(5000))
						{
							功能::到指定地点按G(4, 任务坐标.地图ID, 20928, 18860, 1691, 50);
						}
					}
				}



				return false;
			}
			if (主线任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				if (功能::优先破坏击打道具(2000))
				{
					功能::到指定地点按G(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				}
				return false;
			}
			if (主线任务.dStep == 4)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				加入优先打怪ID(L"142664");
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 3000);
				return false;
			}
			if (主线任务.dStep == 5)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
		}
	}
	if (主线任务.dQuestId == 3011003)// 消灭监视者们        
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::寻路到副本(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z);
				return false;
			}
			if (主线任务.dStep == 2)
			{
				if (地图::取地图ID() != 10401)
				{
					if (地图::传送点是否激活(0xDBF25))
					{
						地图::传送(0xDBF25);
						return false;
					}
					else
					{
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
						功能::到指定地点(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
						return false;
					}
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
					return false;
				}
			}
		}
		else
		{
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
		}
	}
	if (主线任务.dQuestId == 3014401)// 艾尔盖茨        
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::移动打怪(7612, 8589, 517, 100, 5000, 1500);
				return false;
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}
			if (主线任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				if (功能::优先破坏击打道具(2000))
				{
					功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 5000, 1500);

				}
				return false;
			}
			if (主线任务.dStep == 4)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点按G(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 150);
				return false;
			}

		}
	}
	if (主线任务.dQuestId == 3014402)// 守护者们        
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 5000, 1500);
				return false;
			}
			if (主线任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点按G(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 150);
				return false;
			}
			if (主线任务.dStep == 4)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}
		}
	}
	if (主线任务.dQuestId == 3014403)// 守护者们        
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(4, 任务坐标.地图ID, 4210, 14815, 4467, 50);
				return false;
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 5000, 1500);
				return false;
			}
			if (主线任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点按G(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 150);
				return false;
			}

		}
	}
	if (主线任务.dQuestId == 3014404)// 守护者们        
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 5000, 1500);
				return false;
			}

			/*if (主线任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点按G(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 150);
				return false;
			}
			if (主线任务.dStep == 4)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}*/
		}
	}
	if (主线任务.dQuestId == 3014405)// 守护者们        最后的场所??
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				加入优先打怪ID(L"143440");
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 5000, 1500);//7624,9760,519,7640,10536,3079,2,1,0,2,6  分段坐标分区从4改成2
				return false;
			}
		}
	}
	if (主线任务.dQuestId == 305007)// 守护者们        
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
		}
		else
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
	}
	if (主线任务.dQuestId == 305008)// 守护者们        
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 22035, 69433, 134, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点采集任务显示(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 2000, 41016, 100, 200);
				return false;
			}
			if (主线任务.dStep == 4)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 5)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 6)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 7)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
		}
	}
	if (主线任务.dQuestId == 4500403)// 红色沙漠之眼        
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
		}
	}
	return true;
}
bool 游戏::世界4(QuestInfo_ 主线任务)
{
	if (主线任务.dQuestId == 4002004)// 哈伯克的神奇冒险          
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 2)
			{
				if (!UI功能::背包界面是否显示())
				{
					UI功能::内存按键('I');
					return false;
				}
				背包::使用背包指定物品_ByResId(730152);
				return false;
			}
			if (主线任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}
			if (主线任务.dStep == 4)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点入港(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}
			if (主线任务.dStep == 5)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点按G(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 250);
				return false;
			}
			if (主线任务.dStep == 6)
			{
				if (地图::取地图ID() == 30724)
				{
					本人::CALL_演奏乐谱(1);
					Sleep(10000);
					return false;
				}
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}
			if (主线任务.dStep == 7)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(18, 任务坐标.地图ID, 20346, 36623, 1, 50);
				return false;
			}
			if (主线任务.dStep == 8)
			{
				if (UI功能::是否在航海准备界面())
				{
					UI功能::内存按键('Z');
					Sleep(3000);
					return false;
				}
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点采集任务显示(18, 任务坐标.地图ID, 19774, 37031, 1, 5000, 1046605);
				return false;
			}
			if (主线任务.dStep == 9)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点按G(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}
		}
	}
	if (主线任务.dQuestId == 4002401)// 哈伯克的神奇冒险          
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点按G(4, 任务坐标.地图ID, -14, -1092, 475, 150, 500);
				return false;
			}
		}
	}

	if (主线任务.dQuestId == 4002005)// 哈伯克的神奇冒险          
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点采集任务显示(18, 任务坐标.地图ID, 9668, 7465, 7, 2000, 1038120, 100, 200);
				return false;
			}
			if (主线任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 4)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}
			if (主线任务.dStep == 5)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点入港(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}
		}
	}
	if (主线任务.dQuestId == 1102001)// 哈伯克的神奇冒险          
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 4)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 5)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::寻路到副本(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z);
				return false;
			}
			if (主线任务.dStep == 6)
			{
				if (地图::取地图ID() == 11116)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点(18, 11116, 15253, 22084, 1565, 50);
					return false;
				}

			}

		}
	}
	if (主线任务.dQuestId == 1102401)// 哈伯克的神奇冒险          
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}
			if (主线任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}
			if (主线任务.dStep == 4)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 5)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点按G(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 150);
				return false;
			}
			if (主线任务.dStep == 6)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 100);
				return false;
			}
			if (主线任务.dStep == 7)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 8)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 9)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 3000);
				return false;
			}
			if (主线任务.dStep == 10)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点按G(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 150);
				return false;
			}
			if (主线任务.dStep == 11)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 100);
				return false;
			}
			if (主线任务.dStep == 12)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::移动打怪(5946, 17909, 1568, 100, 5000);
				return false;
			}
			if (主线任务.dStep == 13)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				if (功能::优先破坏击打道具(3000))
				{
					加入优先打怪ID(L"210020");
					功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 5000);

				}
				return false;
			}
			if (主线任务.dStep == 14)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				if (功能::优先破坏击打道具(3000))
				{
					加入优先打怪ID(L"210050");
					功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 5000);

				}
				return false;
			}
			if (主线任务.dStep == 15)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				加入优先打怪ID(L"111106|111127|111128|111129");
				if (功能::优先打怪(250))
				{
					if (功能::优先破坏击打道具(3000))
					{
						if (主线任务.子任务进度[0].dCur == 0)
						{
							功能::到指定地点(18, 任务坐标.地图ID, 5714, 22622, 1568, 150);
							return false;
						}
						if (主线任务.子任务进度[1].dCur == 0)
						{
							功能::到指定地点(18, 任务坐标.地图ID, 6988, 24119, 1564, 150);
							return false;
						}
						if (主线任务.子任务进度[2].dCur == 0)
						{
							功能::到指定地点(18, 任务坐标.地图ID, 8541, 24711, 1564, 150);
							return false;
						}
						if (主线任务.子任务进度[3].dCur == 0)
						{
							功能::到指定地点(18, 任务坐标.地图ID, 9745, 24372, 1568, 150);
						}
					}
				}
				return false;
			}
			if (主线任务.dStep == 16)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				if (功能::优先破坏击打道具(5000))
				{
					功能::到指定地点(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 100);
				}
				return false;
			}
			if (主线任务.dStep == 17)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 3000);
				return false;
			}
			if (主线任务.dStep == 18)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 19)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 20)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
		}
	}
	if (主线任务.dQuestId == 1102002)// 哈伯克的神奇冒险          
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}
		}
	}
	if (主线任务.dQuestId == 1109001)// 哈伯克的神奇冒险          
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
		}
		else
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
	}
	if (主线任务.dQuestId == 1109003)// 哈伯克的神奇冒险          
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 3)
			{
				if (主线任务.子任务进度[2].dCur == 0)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 5929, -29430, 4077, 25174, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
					return false;
				}
				if (主线任务.子任务进度[1].dCur == 0)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 5900, -29720, 4077, 25173, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
					return false;
				}
				if (主线任务.子任务进度[0].dCur == 0)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 5776, -29985, 4077, 25172, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
					return false;
				}
			}
			if (主线任务.dStep == 4)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
		}
		else
		{

			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;

		}
	}
	if (主线任务.dQuestId == 1109004)// 艾达琳的请求         
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 4)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}
			if (主线任务.dStep == 5)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
		}
	}
	if (主线任务.dQuestId == 1109005)// 艾达琳的请求         
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点使用指定按键(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50, VK_F5);
				return false;
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 4)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(18, 任务坐标.地图ID, 22072, 10133, 5134, 50);
				return false;
			}
			if (主线任务.dStep == 5)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(18, 任务坐标.地图ID, 22082, 8161, 4358, 50);
				return false;
			}
		}
	}
	if (主线任务.dQuestId == 1109006)// 艾达琳的请求         
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 4)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}
		}
	}
	if (主线任务.dQuestId == 1101001)// 艾达琳的请求         
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}
			if (主线任务.dStep == 4)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 5)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 6)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 7)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 8)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点使用指定按键(18, 任务坐标.地图ID, -1545, -39018, 243, 50, VK_F5);
				return false;
			}
			if (主线任务.dStep == 9)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 10)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
		}
	}
	if (主线任务.dQuestId == 1101002)// 艾达琳的请求         
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 4)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 5)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
		}
	}
	if (主线任务.dQuestId == 1101003)// 追踪的资格           地图:11113
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 4)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
		}
	}
	if (主线任务.dQuestId == 1106001)// 追踪的资格           
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
		}
		else
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
	}
	if (主线任务.dQuestId == 1106002)// 追踪死灵术           
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}
			if (主线任务.dStep == 4)
			{
				if (主线任务.子任务进度[1].dCur < 主线任务.子任务进度[1].dNeed)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					加入优先打怪ID(L"214120");
					功能::移动打怪(7643, 20354, 1258, 100, 1000);
					return false;
				}
				if (主线任务.子任务进度[0].dCur < 主线任务.子任务进度[0].dNeed)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					加入优先打怪ID(L"214100");
					功能::移动打怪(6144, 20573, 1258, 100, 1000);
					return false;
				}
				if (主线任务.子任务进度[2].dCur < 主线任务.子任务进度[2].dNeed)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					加入优先打怪ID(L"214130");
					功能::移动打怪(7696, 22147, 1259, 100, 1000);
					return false;
				}
			}
			if (主线任务.dStep == 5)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
		}
	}
	if (主线任务.dQuestId == 1106003)// 追踪死灵术           
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点采集任务显示(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 3000, 111508);
				return false;
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点使用指定按键(18, 任务坐标.地图ID, 6877, 19085, 1026, 50, VK_F5);
				return false;
			}
			if (主线任务.dStep == 3)
			{
				if (主线任务.子任务进度[0].dCur < 主线任务.子任务进度[0].dNeed)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					加入优先打怪ID(L"111507");
					功能::移动打怪(6828, 16547, 782, 100, 5000);
					return false;
				}
				if (主线任务.子任务进度[1].dCur < 主线任务.子任务进度[1].dNeed)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					加入优先打怪ID(L"214020|214030|214010|214011");
					功能::移动打怪(6828, 16547, 782, 100, 5000);
					return false;
				}
			}
			if (主线任务.dStep == 4)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}
		}
		else
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
	}
	if (主线任务.dQuestId == 1106004)// 西格蒙德的行踪           
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}
			if (主线任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 4)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 5)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
		}
	}
	if (主线任务.dQuestId == 1106005)// 在古代遗迹里            
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
		}
	}
	if (主线任务.dQuestId == 1106006)// 泰仑要塞战斗              
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				加入优先打怪ID(L"214020|214090|214012|214013|214030");
				功能::移动打怪(25128, 10071, 547, 100, 5000);
				return false;
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}
			if (主线任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 4)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 5)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}
			if (主线任务.dStep == 6)
			{
				if (主线任务.子任务进度[0].dCur < 主线任务.子任务进度[0].dNeed)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					加入优先打怪ID(L"111544");
					功能::移动打怪(27640, 9819, 1021, 100, 1000);
					return false;
				}
				if (主线任务.子任务进度[1].dCur < 主线任务.子任务进度[1].dNeed)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					加入优先打怪ID(L"214020|214030|214012|214013|850093");
					功能::移动打怪(27640, 9819, 1021, 100, 3000);
					return false;
				}
			}
			if (主线任务.dStep == 7)
			{
				if (主线任务.子任务进度[2].dCur < 主线任务.子任务进度[2].dNeed)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点采集任务显示(18, 任务坐标.地图ID, 29421, 9341, 512, 3000, 111553);
					return false;
				}
				if (主线任务.子任务进度[1].dCur < 主线任务.子任务进度[1].dNeed)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点采集任务显示(18, 任务坐标.地图ID, 30035, 9052, 512, 3000, 111552);
					return false;
				}
				if (主线任务.子任务进度[0].dCur < 主线任务.子任务进度[0].dNeed)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点采集任务显示(18, 任务坐标.地图ID, 30787, 8807, 512, 3000, 111545);
					return false;
				}
			}
			if (主线任务.dStep == 8)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}
			if (主线任务.dStep == 9)
			{
				if (本人::取角色信息().举起状态 == 1)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点采集任务显示(18, 任务坐标.地图ID, 29936, 10033, 1369, 3000, 111526);
					return false;
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点使用指定按键(18, 任务坐标.地图ID, 31742, 10048, 1383, 50, 'R');
					return false;
				}

			}
		}
	}
	if (主线任务.dQuestId == 1106007)// 升起希望之光           
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}
			if (主线任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
		}
	}
	if (主线任务.dQuestId == 1106008)// 前往古代遗迹艾伯利亚            
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				加入优先打怪ID(L"214050");
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 3000);
				return false;
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				加入优先打怪ID(L"214060");
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 3000);
				return false;
			}
			if (主线任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				加入优先打怪ID(L"214040");
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 3000);
				return false;
			}
			if (主线任务.dStep == 4)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点采集任务显示(18, 任务坐标.地图ID, 21963, 25305, 512, 3000, 111549);
				return false;
			}
			if (主线任务.dStep == 5)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				加入优先打怪ID(L"214070");
				功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 3000);
				return false;
			}
			if (主线任务.dStep == 6)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 7)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::寻路到副本(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z);
				return false;
			}
		}
	}
	if (主线任务.dQuestId == 1101004)// 新的冒险              
	{
		if (主线任务.dState == 1)
		{
			if (地图::取地图ID() == 11152)
			{
				本人::CALL_演奏乐谱(1);
				Sleep(10000);
				return false;
			}
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 4)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
		}
	}
	if (主线任务.dQuestId == 1109002)// 艾达琳的礼物              
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dState == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}
			if (主线任务.dState == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}
		}
		else
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}

	}
	if (主线任务.dQuestId == 1109007)// 跨越冰封之海             
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				MyTrace(L"任务跨越冰封之海dStep2 地点  %0.3f %0.3f %0.3f ", 任务坐标.x, 任务坐标.y, 任务坐标.z);
				功能::到指定地点(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}
		}
		else
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			MyTrace(L"任务跨越冰封之海dState=2 地点  %0.3f %0.3f %0.3f ", 任务坐标.x, 任务坐标.y, 任务坐标.z);
			功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
			return false;
		}
	}
	//循环跳出 = true;
	return true;
}
bool 游戏::世界5(QuestInfo_ 主线任务)//冰岛任务
{
	if (主线任务.dQuestId == 1102003)// 巴克斯图姆, 出发!    
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点入港(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}
			if (主线任务.dStep == 3)
			{
				if (主线任务.子任务进度.size() == 2)
				{
					if (主线任务.子任务进度[0].dCur == 0)
					{
						MyTrace(L"子任务进度 %s %d/%d TargetID:%d", 主线任务.子任务进度[0].任务描述, 主线任务.子任务进度[0].dCur, 主线任务.子任务进度[0].dNeed, 主线任务.子任务进度[0].TargetID);
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
						功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 11295, 主线任务.dQuestId, -1, 50);
						return false;
					}
					if (主线任务.子任务进度[1].dCur == 0)
					{
						MyTrace(L"子任务进度 %s %d/%d TargetID:%d", 主线任务.子任务进度[1].任务描述, 主线任务.子任务进度[1].dCur, 主线任务.子任务进度[1].dNeed, 主线任务.子任务进度[1].TargetID);
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
						功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 11295, 主线任务.dQuestId, -1, 50);
						return false;
					}
				}
				return false;
			}
		}
	}
	if (主线任务.dQuestId == 405001)//冰封之海
	{
		if (主线任务.dState == 1)
		{
			if (主线任务.dStep == 1)
			{
				if (主线任务.子任务进度.size() == 2)
				{
					if (主线任务.子任务进度[0].dCur == 0)
					{
						MyTrace(L"子任务进度 %s %d/%d TargetID:%d", 主线任务.子任务进度[0].任务描述, 主线任务.子任务进度[0].dCur, 主线任务.子任务进度[0].dNeed, 主线任务.子任务进度[0].TargetID);
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
						功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
						return false;
					}
					if (主线任务.子任务进度[1].dCur == 0)
					{
						MyTrace(L"子任务进度 %s %d/%d TargetID:%d", 主线任务.子任务进度[1].任务描述, 主线任务.子任务进度[1].dCur, 主线任务.子任务进度[1].dNeed, 主线任务.子任务进度[1].TargetID);
						坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
						功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
						return false;
					}
				}
			}
			if (主线任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
				return false;
			}
			if (主线任务.dStep == 4)
			{
				ActorInfo_ 角色信息 = 本人::取角色信息();
				if (角色信息.举起状态 == 1)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点采集(6, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 1500, 0x79E2, 100, 150);
					return false;
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					if (功能::到指定地点(6, 任务坐标.地图ID, -8957, 8609, 497, 50))
					{
						UI功能::内存按键(DWORD('R'));
					}
					return false;
				}
			}
			if (主线任务.dStep == 5)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
				return false;
			}
			if (主线任务.dStep == 6)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
			if (主线任务.dStep == 7)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(4, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 主线任务.dQuestId, -1, 100, 主线任务.dStep);
				return false;
			}
		}
	}
	if (主线任务.dQuestId == 405002)//沉睡在冰冻大地的东西
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 3000);
			return false;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return false;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::寻路到副本(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z);
			return false;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return false;
		}
		if (主线任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return false;
		}
	}
	if (主线任务.dQuestId == 405003)//:黎明的开始
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return false;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return false;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 3000);
			return false;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return false;
		}
		if (主线任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return false;
		}
	}
	if (主线任务.dQuestId == 406001)//拯救行动
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);//
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return false;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return false;
		}
		if (主线任务.dStep == 3)
		{
			if (主线任务.子任务进度.size() == 2)
			{
				if (主线任务.子任务进度[0].dCur == 0)
				{
					MyTrace(L"子任务进度 %s %d/%d TargetID:%d", 主线任务.子任务进度[0].任务描述, 主线任务.子任务进度[0].dCur, 主线任务.子任务进度[0].dNeed, 主线任务.子任务进度[0].TargetID);
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					//功能::到指定地点按G_无打怪(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50); 
					功能::到指定地点找NPC交任务2(6, 10301, 9116, 6240, 1029, 0, 主线任务.dQuestId, -1, 50);
					return false;
				}
				if (主线任务.子任务进度[1].dCur == 0)
				{
					MyTrace(L"子任务进度 %s %d/%d TargetID:%d", 主线任务.子任务进度[1].任务描述, 主线任务.子任务进度[1].dCur, 主线任务.子任务进度[1].dNeed, 主线任务.子任务进度[1].TargetID);
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					//功能::到指定地点按G_无打怪(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50); 
					功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 主线任务.dQuestId, -1, 50);
					return false;
				}
			}
			////功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 11295, 主线任务.dQuestId, -1, 50);
			//return false;
			return false;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return false;
		}
		if (主线任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return false;
		}
	}
	if (主线任务.dQuestId == 406002)//拯救行动
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return false;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return false;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return false;
		}
	}
	if (主线任务.dQuestId == 406003)//向着红幕
	{
		if (主线任务.dStep == 1)
		{
			if (主线任务.子任务进度.size() == 3)
			{
				if (主线任务.子任务进度[0].dCur == 0)
				{
					MyTrace(L"子任务进度 %s %d/%d TargetID:%d", 主线任务.子任务进度[0].任务描述, 主线任务.子任务进度[0].dCur, 主线任务.子任务进度[0].dNeed, 主线任务.子任务进度[0].TargetID);
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 主线任务.dQuestId, -1, 50);
					return false;
				}
				if (主线任务.子任务进度[1].dCur == 0)
				{
					MyTrace(L"子任务进度 %s %d/%d TargetID:%d", 主线任务.子任务进度[1].任务描述, 主线任务.子任务进度[1].dCur, 主线任务.子任务进度[1].dNeed, 主线任务.子任务进度[1].TargetID);
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 主线任务.dQuestId, -1, 50);
					return false;
				}
				if (主线任务.子任务进度[2].dCur == 0)
				{
					MyTrace(L"子任务进度 %s %d/%d TargetID:%d", 主线任务.子任务进度[2].任务描述, 主线任务.子任务进度[2].dCur, 主线任务.子任务进度[2].dNeed, 主线任务.子任务进度[2].TargetID);
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 主线任务.dQuestId, -1, 50);
					return false;
				}
			}
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return false;
		}
	}
	if (主线任务.dQuestId == 407001)//穿过风刃
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return false;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return false;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return false;
		}
	}
	if (主线任务.dQuestId == 407002)//温柔而和平
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return false;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return false;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(17828.000, 9583.000, 3792.894, 100, 1000); return false;

		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return false;
		}
		if (主线任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(17828.000, 9583.000, 3792.894, 100, 800);
			return false;
		}
		if (主线任务.dStep == 6)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return false;
		}
		if (主线任务.dStep == 7)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return false;
		}
		if (主线任务.dStep == 8)
		{
			ActorInfo_ 角色信息 = 本人::取角色信息();
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (角色信息.举起状态 == 1)
			{
				功能::到指定地点采集(6, 10322, 任务坐标.x, 任务坐标.y, 任务坐标.z, 5000, 0x7A47);
			}
			else
			{
				if (功能::到指定地点(6, 10322, 17351.961, 4585.227, 3931.417, 50))
				{
					UI功能::内存按键(DWORD('R'));
				}
			}
		}
		if (主线任务.dStep == 9)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return false;
		}
		if (主线任务.dStep == 10)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return false;
		}
	}
	if (主线任务.dQuestId == 407003)//麻雀磨坊
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return false;
		}
		if (主线任务.dStep == 2)
		{
			ActorInfo_ 角色信息 = 本人::取角色信息();
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (角色信息.举起状态 == 1)
			{
				功能::到指定地点采集(6, 10322, 任务坐标.x, 任务坐标.y, 任务坐标.z, 5000, 0x7A49);
			}
			else
			{
				if (功能::到指定地点(6, 10322, 17351.961, 4585.227, 3931.417, 50))
				{
					UI功能::内存按键(DWORD('R'));
				}
			}
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return false;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return false;
		}
		if (主线任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return false;
		}
	}
	if (主线任务.dQuestId == 407004)//穿过风刃
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::寻路到副本(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z);
			return false;
		}
	}
	if (主线任务.dQuestId == 407005)//
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return false;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return false;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return false;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return false;
		}
		if (主线任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::寻路到副本(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z);
			return false;
		}
	}
	if (主线任务.dQuestId == 407006)//追踪痕迹
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			//功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 12861.000, 6731.000, 3727.616, 500);
			return false;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 100);
			return false;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 3000);
			return false;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 500);
			return false;
		}
		if (主线任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 500);
			return false;
		}
		if (主线任务.dStep == 6)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 500);
			return false;
		}
		if (主线任务.dStep == 7)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 500);
			return false;
		}
		if (主线任务.dStep == 8)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return false;
		}

	}
	if (主线任务.dQuestId == 407007)//再次燃烧的火种
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 9413.000, 6477.000, 3409.870, 100);
			return false;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 100);
			return false;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return false;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 100);
			return false;
		}
		if (主线任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return false;
		}
	}
	if (主线任务.dQuestId == 407008)//巴耶丹的结局
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return false;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::寻路到副本(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z);
			return false;
		}
	}
	if (主线任务.dQuestId == 408001)//老人与湖
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 100);
			return false;
		}
		if (主线任务.dStep == 2)
		{
			MyTrace(L"Step2 任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			if (任务流程 == 0)
			{
				//功能::移动打怪(6782, 11424, 3127.131, 100, 500)
				if (功能::到指定地点(6, 10322, 6782, 11424, 3127.131, 100))
				{
					任务流程 = 1;
				}
			}
			if (任务流程 == 1)
			{
				功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
				return false;
			}

		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return false;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点使用表情(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 0xF234);//谢罪
			return false;
		}
		if (主线任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return false;
		}
		if (主线任务.dStep == 6)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return false;
		}
	}
	if (主线任务.dQuestId == 408002)//师傅和弟子
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50);
			return false;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 16262, 3139, 512, 100);
			return false;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 15548, 5004, 512, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 15548, 5004, 512, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return false;
		}
	}
	if (主线任务.dQuestId == 408003)//寻找巴耶丹
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, -1, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::寻路到副本(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z);
			return false;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, -1, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 100);
			return false;
		}
		if (主线任务.dStep == 5)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, -1, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 6)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 100);
			return false;
		}
		if (主线任务.dStep == 7)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, -1, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 8)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 7814, 11866, 3461.01, 100);
			return false;
		}
	}
	if (主线任务.dQuestId == 408004)
	{
		if (主线任务.dStep == 1)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, -1, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 2)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 100);
			return false;
		}
		if (主线任务.dStep == 3)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::寻路到副本(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z);
			任务流程 = 0;
			return false;
		}
		if (主线任务.dStep == 4)
		{
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, -1, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			任务流程 = 0;
			return false;
		}

	}
	if (主线任务.dQuestId == 406004)// ::406004<631F4> QuestName:在欢呼声中
	{
		if (主线任务.dStep == 1)
		{
			MyTrace(L"Step1        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 2)
		{
			MyTrace(L"Step2       任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 3)
		{
			MyTrace(L"Step3        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			//功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			if (功能::到指定地点(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50))
			{
				UI功能::内存按键(VK_F5);
			}
			return false;
		}
		if (主线任务.dStep == 4)
		{
			MyTrace(L"Step4        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点使用表情(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50, 功能::返回表情编号(L"疑问"));//疑问
			//功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 5)
		{
			MyTrace(L"Step5        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 6)
		{
			MyTrace(L"Step6        任务流程 %d", 任务流程);
			if (主线任务.子任务进度.size() == 3)
			{
				if (主线任务.子任务进度[0].dCur < 主线任务.子任务进度[0].dNeed)
				{
					MyTrace(L"子任务进度0 %s %d/%d TargetID:%d", 主线任务.子任务进度[0].任务描述, 主线任务.子任务进度[0].dCur, 主线任务.子任务进度[0].dNeed, 主线任务.子任务进度[0].TargetID);
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.子任务进度[0].TargetID, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
					return false;
				}
				if (主线任务.子任务进度[1].dCur < 主线任务.子任务进度[1].dNeed)
				{
					MyTrace(L"子任务进度1 %s %d/%d TargetID:%d", 主线任务.子任务进度[1].任务描述, 主线任务.子任务进度[1].dCur, 主线任务.子任务进度[1].dNeed, 主线任务.子任务进度[1].TargetID);
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.子任务进度[1].TargetID, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
					return false;
				}
				if (主线任务.子任务进度[2].dCur < 主线任务.子任务进度[2].dNeed)
				{
					MyTrace(L"子任务进度2 %s %d/%d TargetID:%d", 主线任务.子任务进度[2].任务描述, 主线任务.子任务进度[2].dCur, 主线任务.子任务进度[2].dNeed, 主线任务.子任务进度[2].TargetID);
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.子任务进度[2].TargetID, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
					return false;//ceshi 
				}
			}
			return false;
		}
	}
	if (主线任务.dQuestId == 406006)// :406006<631F6> QuestName:被揭开的黑幕
	{
		if (主线任务.dStep == 1)
		{
			MyTrace(L"Step1        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 2)
		{
			MyTrace(L"Step2       任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 3)
		{
			MyTrace(L"Step3        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 4)
		{
			MyTrace(L"Step4        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return false;
		}

	}
	if (主线任务.dQuestId == 409001)//:409001<63DA9> QuestName:圣所的狼群
	{
		if (主线任务.dStep == 1)
		{
			MyTrace(L"Step1        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 2)
		{
			MyTrace(L"Step2       任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return false;
		}
		if (主线任务.dStep == 3)
		{
			MyTrace(L"Step3        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 4)
		{
			MyTrace(L"Step4        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 5)
		{
			MyTrace(L"Step1        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 6)
		{
			MyTrace(L"Step2       任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 7)
		{
			MyTrace(L"Step3        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 3000);
			return false;
		}
		if (主线任务.dStep == 8)
		{
			MyTrace(L"Step4        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return false;
		}

	}
	if (主线任务.dQuestId == 409002)//::409002<63DAA> QuestName:圣所的恶魔
	{
		if (主线任务.dStep == 1)
		{
			MyTrace(L"Step1        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 2)
		{
			MyTrace(L"Step2       任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 11583, 33527, 4814.38, 50);
			return false;
		}
		if (主线任务.dStep == 3)
		{
			MyTrace(L"Step3        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 4)
		{
			MyTrace(L"Step4        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			//功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			if (功能::到指定地点(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50))
			{
				UI功能::内存按键(VK_F5);//此处是需要按f5之后，用手榴弹打怪， 
			}
			return false;
		}
		if (主线任务.dStep == 5)
		{
			MyTrace(L"Step1        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 6)
		{
			MyTrace(L"Step2       任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 24467, 25405, 4750, 50);
			return false;
		}
		if (主线任务.dStep == 7)
		{
			MyTrace(L"Step3        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);

			return false;
		}
		if (主线任务.dStep == 8)
		{
			MyTrace(L"Step4        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 26153, 28853, 4750, 50);
			return false;
		}
		if (主线任务.dStep == 9)
		{
			MyTrace(L"Step3        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 22668, 32063, 4958.79, 50);
			return false;
		}
		if (主线任务.dStep == 10)
		{
			MyTrace(L"Step4        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 11)
		{
			MyTrace(L"Step3        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::寻路到副本(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z);
			return false;
		}
		if (主线任务.dStep == 12)
		{
			MyTrace(L"Step4        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 13)
		{
			MyTrace(L"Step4        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return false;
		}
	}
	if (主线任务.dQuestId == 409003)//::409003<63DAB> QuestName:悬崖的尽头 
	{
		if (主线任务.dStep == 1)
		{
			MyTrace(L"Step1        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 24906, 31071, 4733.15, 50);
			return false;
		}
		if (主线任务.dStep == 2)
		{
			MyTrace(L"Step2       任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 3)
		{
			if (主线任务.dState == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
				return false;
			}
			else
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, -1, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
				return false;
			}
		}

	}
	if (主线任务.dQuestId == 410001)//410001<64191> QuestName:留下的脚印
	{
		if (主线任务.dStep == 1)
		{
			MyTrace(L"Step1        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 2)
		{
			MyTrace(L"Step2       任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::移动打怪(任务坐标.x, 任务坐标.y, 任务坐标.z, 100, 3000);
			return false;
		}
		if (主线任务.dStep == 3)
		{
			MyTrace(L"Step3        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 4)
		{
			MyTrace(L"Step4        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return false;
		}
		if (主线任务.dStep == 5)
		{
			MyTrace(L"Step5       任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 6)
		{
			MyTrace(L"Step6       任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 20991.000, 17548.000, 513.789, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return false;
		}

	}
	if (主线任务.dQuestId == 410002)//:410002<64192> QuestName:冻住的脚印 
	{
		if (主线任务.dStep == 1)
		{
			MyTrace(L"Step1        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 2)
		{
			MyTrace(L"Step2       任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return false;
		}
		if (主线任务.dStep == 3)
		{
			MyTrace(L"Step3        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 4)
		{
			MyTrace(L"Step4        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 5)
		{
			MyTrace(L"Step5       任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return false;
		}
	}
	if (主线任务.dQuestId == 410003)//:410003<64193> QuestName:雪雾迷蒙 
	{
		if (主线任务.dStep == 1)
		{
			MyTrace(L"Step1        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 2)
		{
			MyTrace(L"Step2       任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::寻路到副本(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z);
			return false;
		}
		if (主线任务.dStep == 3)
		{
			MyTrace(L"Step3        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 4)
		{
			MyTrace(L"Step4        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 5)
		{
			MyTrace(L"Step5       任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点使用表情(任务坐标.大陆ID, 任务坐标.地图ID, 23330, 21243, -503.354, 50, 功能::返回表情编号(L"悲伤"));//疑问
			return false;
		}
		if (主线任务.dStep == 6)
		{
			MyTrace(L"Step2       任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 7)
		{
			MyTrace(L"Step3        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return false;
		}
		if (主线任务.dStep == 8)
		{
			MyTrace(L"Step4        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
			return false;
		}
		if (主线任务.dStep == 9)
		{
			MyTrace(L"Step5       任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return false;
		}
	}
	if (主线任务.dQuestId == 410004)//410004<64194> QuestName:瘟疫军团团长阿肯 
	{
		if (主线任务.dStep == 1)
		{
			MyTrace(L"Step1        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 2)
		{
			MyTrace(L"Step2       任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 3)
		{
			MyTrace(L"Step3        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::寻路到副本(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z);
			return false;
		}

	}
	if (主线任务.dQuestId == 406005)//:406005<631F5> QuestName:黎明 
	{
		if (主线任务.dStep == 1)
		{
			MyTrace(L"Step1        任务流程 %d", 任务流程);
			if (主线任务.子任务进度.size() == 2)
			{
				if (主线任务.子任务进度[0].dCur < 主线任务.子任务进度[0].dNeed)
				{
					MyTrace(L"子任务进度 %s %d/%d TargetID:%d", 主线任务.子任务进度[0].任务描述, 主线任务.子任务进度[0].dCur, 主线任务.子任务进度[0].dNeed, 主线任务.子任务进度[0].TargetID);
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, -1, 主线任务.dQuestId, -1, 50);
					return false;
				}
				if (主线任务.子任务进度[1].dCur < 主线任务.子任务进度[1].dNeed)
				{
					MyTrace(L"子任务进度 %s %d/%d TargetID:%d", 主线任务.子任务进度[1].任务描述, 主线任务.子任务进度[1].dCur, 主线任务.子任务进度[1].dNeed, 主线任务.子任务进度[1].TargetID);
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
					功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, -1, 主线任务.dQuestId, -1, 50);
					return false;
				}
			}
		}
		if (主线任务.dStep == 2)
		{
			MyTrace(L"Step2       任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 3)
		{
			MyTrace(L"Step3        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::寻路到副本(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z);
			return false;
		}

	}
	if (主线任务.dQuestId == 406007)//406007<631F7> QuestName:亚尔比斯
	{
		if (主线任务.dStep == 1)
		{
			MyTrace(L"Step1        任务流程 %d", 任务流程);
			坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
			功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
			return false;
		}
		if (主线任务.dStep == 2)
		{
			MyTrace(L"Step2       任务流程 %d", 任务流程);
			if (主线任务.dState == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 50);
				return false;
			}
			if (主线任务.dState == 2)
			{
				MyTrace(L"Step2       dState %d", 主线任务.dState);
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
				QuestInfo_ 寻找方舟任务 = 任务::取出寻找方舟任务();
				if (寻找方舟任务.CurNum == 4)
				{
					功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);

				}
				else
				{
					功能::到指定地点找NPC交任务3(22, 10002, 11113.000, 137.000, 25.711, 主线任务.TargetId, 主线任务.dQuestId, -1, 50, 主线任务.dStep);
				}
				return false;
			}
		}
	}
	return true;
}
bool 游戏::执行世界任务()
{
	QuestInfo_ 必做引导任务 = 任务::取出世界任务();
	MyTrace(L"Type:%d QuestID:%d QuestName:%s 阶段:%d  状态:%d 当前地图ID:%d 子任务数量:%d 主线任务目标:%d 操作:%s", 必做引导任务.dType, 必做引导任务.dQuestId, 必做引导任务.QuestName, 必做引导任务.dStep, 必做引导任务.dState, 地图::取地图ID(), 必做引导任务.子任务进度.size(), 必做引导任务.TargetId, 必做引导任务.QuestOption);
	if (!游戏::世界1(必做引导任务))
	{
		return false;
	}
	return true;
}
bool 游戏::执行指引任务()
{
	vector<QuestInfo_>vsk;
	QuestInfo_ 可接指引 = 任务::取出可接指引任务();
	if (可接指引.dQuestId == 0x451FD9)//何为宠物
	{
		if (任务::是否已接任务(0x451FD9))
		{
			MyTrace(L"是否已接指引 %x", 0x451FD9);
			QuestInfo_ 指引任务 = 任务::取出指定支线任务(0x451FD9);
			//MyTrace(L"指引任务 %s %X 当前step %d state %d  %s", 可接指引.QuestName, 可接指引.dQuestId, 可接指引.dStep, 可接指引.dState, 可接指引.QuestOption);
			if (指引任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(指引任务.dQuestId, 指引任务.objBase, 指引任务.dResAddr);
				//MyTrace(L"任务目标 大陆ID:%d 地图ID %d 本大陆ID：%d", 任务坐标.大陆ID, 任务坐标.地图ID, 地图::取当前大陆ID());
				功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 指引任务.TargetId, 指引任务.dQuestId, -1, 50);
				return false;
			}
			if (指引任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(指引任务.dQuestId, 指引任务.objBase, 指引任务.dResAddr);
				功能::到指定地点采集(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 3000, 指引任务.TargetId, 100, 150);
				return false;
			}
			if (指引任务.dStep == 3)
			{
				if (功能::拾取道具(3000))
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(指引任务.dQuestId, 指引任务.objBase, 指引任务.dResAddr);
					//MyTrace(L"任务目标 大陆ID:%d 地图ID %d 本大陆ID：%d", 任务坐标.大陆ID, 任务坐标.地图ID, 地图::取当前大陆ID());
					功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 指引任务.TargetId, 指引任务.dQuestId, -1, 50, 1);
				}
				return false;
			}
			if (指引任务.dStep == 4)
			{

				坐标_ 任务坐标 = 任务::CALL_取任务坐标(指引任务.dQuestId, 指引任务.objBase, 指引任务.dResAddr);
				//MyTrace(L"任务目标 大陆ID:%d 地图ID %d 本大陆ID：%d", 任务坐标.大陆ID, 任务坐标.地图ID, 地图::取当前大陆ID());
				功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 指引任务.TargetId, 指引任务.dQuestId, -1, 50, 1);

				return false;
			}
			if (指引任务.dStep == 5)
			{

				坐标_ 任务坐标 = 任务::CALL_取任务坐标(指引任务.dQuestId, 指引任务.objBase, 指引任务.dResAddr);
				//MyTrace(L"任务目标 大陆ID:%d 地图ID %d 本大陆ID：%d", 任务坐标.大陆ID, 任务坐标.地图ID, 地图::取当前大陆ID());
				功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 指引任务.TargetId, 指引任务.dQuestId, -1, 50, 0);

				return false;
			}
		}
		else
		{
			任务::CALL_接任务(0x451FD9);
			return false;
		}
		return false;
	}
	if (可接指引.dQuestId == 0x451FDA)//[指引] 最好在一起
	{

		if (任务::是否已接任务(0x451FDA))
		{
			//MyTrace(L"是否已接指引 %x", 0x451FD9);
			QuestInfo_ 指引任务 = 任务::取出指定支线任务(0x451FDA);
			//MyTrace(L"指引任务 %s %X 当前step %d state %d  %s", 可接指引.QuestName, 可接指引.dQuestId, 可接指引.dStep, 可接指引.dState, 可接指引.QuestOption);
			if (指引任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(指引任务.dQuestId, 指引任务.objBase, 指引任务.dResAddr);
				//MyTrace(L"任务目标 大陆ID:%d 地图ID %d 本大陆ID：%d", 任务坐标.大陆ID, 任务坐标.地图ID, 地图::取当前大陆ID());
				功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 指引任务.TargetId, 指引任务.dQuestId, -1, 50, 0);
			}
			if (指引任务.dStep == 2)
			{
				if (本人::召唤宠物())
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(指引任务.dQuestId, 指引任务.objBase, 指引任务.dResAddr);
					//MyTrace(L"任务目标 大陆ID:%d 地图ID %d 本大陆ID：%d", 任务坐标.大陆ID, 任务坐标.地图ID, 地图::取当前大陆ID());
					功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 指引任务.TargetId, 指引任务.dQuestId, -1, 50, 0);
				}

			}
			if (指引任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(指引任务.dQuestId, 指引任务.objBase, 指引任务.dResAddr);
				//MyTrace(L"任务目标 大陆ID:%d 地图ID %d 本大陆ID：%d", 任务坐标.大陆ID, 任务坐标.地图ID, 地图::取当前大陆ID());
				功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 指引任务.TargetId, 指引任务.dQuestId, -1, 50, 0);
			}
			if (指引任务.dStep == 4)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(指引任务.dQuestId, 指引任务.objBase, 指引任务.dResAddr);
				功能::到指定地点采集(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 3000, 指引任务.TargetId, 100, 150);
			}
			if (指引任务.dStep == 5)
			{
				if (指引任务.dState == 1)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(指引任务.dQuestId, 指引任务.objBase, 指引任务.dResAddr);
					//MyTrace(L"任务目标 大陆ID:%d 地图ID %d 本大陆ID：%d", 任务坐标.大陆ID, 任务坐标.地图ID, 地图::取当前大陆ID());
					功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 指引任务.TargetId, 指引任务.dQuestId, -1, 50, 0);
				}
				else
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(指引任务.dQuestId, 指引任务.objBase, 指引任务.dResAddr);
					//MyTrace(L"任务目标 大陆ID:%d 地图ID %d 本大陆ID：%d", 任务坐标.大陆ID, 任务坐标.地图ID, 地图::取当前大陆ID());
					功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0x13899, 指引任务.dQuestId, -1, 50, 0);
				}
			}
		}
		else
		{
			任务::CALL_接任务(0x451FDA);
		}
		return false;
	}
	if (地图::取地图ID() == 10801)
	{
		if (任务::bCheckGuildQuestState(0x41A0D2))
		{
			任务::CALL_接任务(0x41A0D2);
			return false;
		}
	}
	if (可接指引.dQuestId == 0x10EC6F)//[指引] 加工能力石 
	{
		if (任务::是否已接任务(0x10EC6F))
		{
			QuestInfo_ 指引任务 = 任务::取出指定支线任务(0x10EC6F);
			if (指引任务.dState == 1)
			{
				if (指引任务.dStep == 1)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(指引任务.dQuestId, 指引任务.objBase, 指引任务.dResAddr);
					功能::到指定地点找NPC交任务2(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 指引任务.dQuestId, -1, 50, 0);
					return false;

				}
			}
			else
			{
				if (地图::取地图ID() == 10801)
				{
					功能::到指定地点找NPC交任务3(2, 10801, -238, 6893, 453, 13007, 0x10EC6F, -1, 50, 指引任务.dStep);
					return false;
				}
				if (地图::取地图ID() == 10401)
				{
					功能::到指定地点找NPC交任务3(2, 10401, 8885, 17055, 768, 18502, 0x10EC6F, -1, 50, 指引任务.dStep);
					return false;
				}
				if (地图::取地图ID() == 11102)
				{
					功能::到指定地点找NPC交任务3(18, 11102, 7762, 7314, 4337, 0x623C, 0x10EC6F, -1, 50, 指引任务.dStep);
					return false;
				}
			}
			return false;
		}
		else
		{
			if (地图::取地图ID() == 11102)
			{
				任务::CALL_接任务(0x10EC6F);
				return false;
			}
		}

	}
	if (可接指引.dQuestId == 0x451FD0)//[指引] 尝试刻印 
	{
		if (任务::是否已接任务(0x451FD0))
		{
			QuestInfo_ 指引任务 = 任务::取出指定支线任务(0x451FD0);
			if (指引任务.dState == 1)
			{
				if (指引任务.dStep == 1)
				{

					坐标_ 任务坐标 = 任务::CALL_取任务坐标(指引任务.dQuestId, 指引任务.objBase, 指引任务.dResAddr);
					功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 0, 指引任务.dQuestId, -1, 50, 指引任务.dStep);
					return false;

				}
			}
			else
			{
				if (地图::取地图ID() == 10801)
				{
					功能::到指定地点找NPC交任务2(2, 10801, 2910, 5775, 448, 82000, 0x451FD0, -1, 50, 2);
					return false;
				}
				if (地图::取地图ID() == 10401)
				{
					功能::到指定地点找NPC交任务2(2, 10401, 8371, 16770, 777, 18517, 0x451FD0, -1, 50, 2);
					return false;
				}
				if (地图::取地图ID() == 11102)
				{
					功能::到指定地点找NPC交任务2(18, 11102, 6922, 8805, 4225, 25011, 0x451FD0, -1, 50, 2);
					return false;
				}


			}
			return false;
		}
		else
		{
			if (地图::取地图ID() == 11102)
			{
				任务::CALL_接任务(0x451FD0);
				return false;
			}
		}

	}
	if (可接指引.dQuestId == 0x10EC6E)//[指引] 天灾守护者讨伐资格证明  
	{
		if (任务::是否已接任务(0x10EC6E))
		{
			//MyTrace(L"是否已接指引 %x", 0x451FD9);
			QuestInfo_ 指引任务 = 任务::取出指定支线任务(0x10EC6E);
			//MyTrace(L"指引任务 %s %X 当前step %d state %d  %s", 指引任务.QuestName, 指引任务.dQuestId, 指引任务.dStep, 指引任务.dState, 可接指引.QuestOption);
			if (指引任务.dStep == 1)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(指引任务.dQuestId, 指引任务.objBase, 指引任务.dResAddr);
				功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 指引任务.TargetId, 指引任务.dQuestId, -1, 100, 指引任务.dStep);
				return false;
			}
			if (指引任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(指引任务.dQuestId, 指引任务.objBase, 指引任务.dResAddr);
				功能::到指定地点使用指定按键(18, 任务坐标.地图ID, 20348, 13852, 4913, 50, VK_F5);
				return false;
			}
			if (指引任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(指引任务.dQuestId, 指引任务.objBase, 指引任务.dResAddr);
				功能::到指定地点找NPC交任务3(18, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 指引任务.TargetId, 指引任务.dQuestId, -1, 100, 指引任务.dStep);
				return false;
			}
		}
		else
		{
			任务::CALL_接任务(0x10EC6E);
		}
		return false;
	}
	if (可接指引.dQuestId == 0x44AED1)//[觉醒]渴望力量  暂时屏蔽这个
	{
		if (任务::是否已接任务(0x44AED1))
		{
			QuestInfo_ 前置任务 = 任务::取出指定世界任务(0x631F7);//判断世界5组后一个任务是否完成
			if (前置任务.IsFinish == 1)
			{
				QuestInfo_ 指引任务 = 任务::取出指定支线任务(0x44AED1);
				MyTrace(L"指引任务 %s %X 当前step %d state %d  %s", 可接指引.QuestName, 可接指引.dQuestId, 可接指引.dStep, 可接指引.dState, 可接指引.QuestOption);
				if (指引任务.dStep == 1)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(指引任务.dQuestId, 指引任务.objBase, 指引任务.dResAddr);
					功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 指引任务.TargetId, 指引任务.dQuestId, -1, 50, 指引任务.dStep);
					return false;
				}
				if (指引任务.dStep == 2)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(指引任务.dQuestId, 指引任务.objBase, 指引任务.dResAddr);
					功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 指引任务.TargetId, 指引任务.dQuestId, -1, 50, 指引任务.dStep);
					return false;
				}
				if (指引任务.dStep == 3)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(指引任务.dQuestId, 指引任务.objBase, 指引任务.dResAddr);
					功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 指引任务.TargetId, 指引任务.dQuestId, -1, 50, 指引任务.dStep);
					return false;
				}
				if (指引任务.dStep == 4)
				{
					坐标_ 任务坐标 = 任务::CALL_取任务坐标(指引任务.dQuestId, 指引任务.objBase, 指引任务.dResAddr);
					功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 指引任务.TargetId, 指引任务.dQuestId, -1, 50, 指引任务.dStep);
					return false;
				}
			}
		}
		return false;
	}
	if (可接指引.dQuestId == 0x452019)// [指引]指引：罗亨达尔  4530201
	{
		if (任务::是否已接任务(0x452019))
		{
			QuestInfo_ 指引任务 = 任务::取出指定支线任务(0x452019);
			//MyTrace(L"指引任务 %s %X 当前step %d state %d  %s", 指引任务.QuestName, 指引任务.dQuestId, 指引任务.dStep, 指引任务.dState, 指引任务.QuestOption);
			if (指引任务.dStep == 2)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(指引任务.dQuestId, 指引任务.objBase, 指引任务.dResAddr);
				DWORD 地图ID = 地图::取地图ID();
				DWORD 大陆ID = 地图::取当前大陆ID();
				if (地图ID == 10301)//需要重新判断  用地图ID判断。完成最后的地图id
				{//dobj 0x1D00D380010,resaddr 0x1CFAF3007C0,类型 1 任务名称 [指引]新航程 当前阶段：1 任务ID：4001130<3D0D6A> 任务目标iD:25322 目标数量:1,当前数量:0 需求数量:1
					功能::到指定地点入港(3, 30703, 12583.000, 16724.000, 1, 50);
				}
				else
				{//任务名称 
					if (任务::是否已接任务(0x3D0D6A))//[指引]新航程
					{
						QuestInfo_ 指引任务1 = 任务::取出指定支线任务(0x3D0D6A);
						if (指引任务1.dStep == 1)
						{
							坐标_ 任务坐标1 = 任务::CALL_取任务坐标(指引任务1.dQuestId, 指引任务1.objBase, 指引任务1.dResAddr);
							功能::到指定地点找NPC交任务3(任务坐标1.大陆ID, 任务坐标1.地图ID, 任务坐标1.x, 任务坐标1.y, 任务坐标1.z, 0, 指引任务1.dQuestId, -1, 50, 指引任务1.dStep);
							return false;
						}
						if (指引任务1.dStep == 2)
						{
							坐标_ 任务坐标1 = 任务::CALL_取任务坐标(指引任务1.dQuestId, 指引任务1.objBase, 指引任务1.dResAddr);
							功能::到指定地点入港(任务坐标1.大陆ID, 任务坐标1.地图ID, 任务坐标1.x, 任务坐标1.y, 1, 50);
							return false;
						}
						if (指引任务1.dStep == 3)
						{
							坐标_ 任务坐标1 = 任务::CALL_取任务坐标(指引任务1.dQuestId, 指引任务1.objBase, 指引任务1.dResAddr);
							功能::到指定地点找NPC交任务3(任务坐标1.大陆ID, 任务坐标1.地图ID, 任务坐标1.x, 任务坐标1.y, 任务坐标1.z, 0, 指引任务1.dQuestId, -1, 50, 指引任务1.dStep);
							return false;
						}
						if (指引任务1.dStep == 4)
						{
							坐标_ 任务坐标1 = 任务::CALL_取任务坐标(指引任务1.dQuestId, 指引任务1.objBase, 指引任务1.dResAddr);
							功能::到指定地点找NPC交任务3(任务坐标1.大陆ID, 任务坐标1.地图ID, 任务坐标1.x, 任务坐标1.y, 任务坐标1.z, 0, 指引任务1.dQuestId, -1, 50, 指引任务1.dStep);
							return false;
						}
						if (指引任务1.dStep == 5)
						{
							if (指引任务1.dState == 1)
							{
								坐标_ 任务坐标1 = 任务::CALL_取任务坐标(指引任务1.dQuestId, 指引任务1.objBase, 指引任务1.dResAddr);
								功能::到指定地点找NPC交任务3(任务坐标1.大陆ID, 任务坐标1.地图ID, 任务坐标1.x, 任务坐标1.y, 任务坐标1.z, 0, 指引任务1.dQuestId, -1, 50, 指引任务1.dStep);
								return false;
							}
							if (指引任务1.dState == 2)
							{
								坐标_ 任务坐标1 = 任务::CALL_取任务坐标(指引任务1.dQuestId, 指引任务1.objBase, 指引任务1.dResAddr);
								if (地图ID == 50048)
								{
									功能::到指定地点入港(3, 30703, 12583.000, 16724.000, 1, 50);
								}
								else
								{
									功能::到指定地点找NPC交任务3(任务坐标1.大陆ID, 任务坐标1.地图ID, 任务坐标1.x, 任务坐标1.y, 任务坐标1.z, 0, 指引任务1.dQuestId, -1, 50, 指引任务1.dStep);

								}
								return false;
							}
						}
						if (指引任务1.dStep == 6)
						{
							坐标_ 任务坐标1 = 任务::CALL_取任务坐标(指引任务1.dQuestId, 指引任务1.objBase, 指引任务1.dResAddr);
							功能::到指定地点找NPC交任务3(任务坐标1.大陆ID, 任务坐标1.地图ID, 任务坐标1.x, 任务坐标1.y, 任务坐标1.z, 0, 指引任务1.dQuestId, -1, 50, 指引任务1.dStep);
							return false;
						}

					}
					else if (任务::是否已接任务(0x3D0D6B))//[指引]普卢吉恩结界 当前阶段：2 任务ID：4001131
					{
						QuestInfo_ 指引任务1 = 任务::取出指定支线任务(0x3D0D6B);
						if (指引任务1.dStep == 1)
						{
							坐标_ 任务坐标1 = 任务::CALL_取任务坐标(指引任务1.dQuestId, 指引任务1.objBase, 指引任务1.dResAddr);
							功能::到指定地点找NPC交任务3(任务坐标1.大陆ID, 任务坐标1.地图ID, 任务坐标1.x, 任务坐标1.y, 任务坐标1.z, 0, 指引任务1.dQuestId, -1, 50, 指引任务1.dStep);
							return false;
						}
						if (指引任务1.dStep == 2)
						{
							坐标_ 任务坐标1 = 任务::CALL_取任务坐标(指引任务1.dQuestId, 指引任务1.objBase, 指引任务1.dResAddr);
							功能::到指定地点入港(任务坐标1.大陆ID, 任务坐标1.地图ID, 任务坐标1.x, 任务坐标1.y, 1, 50);
							return false;
						}
						if (指引任务1.dStep == 3)
						{
							坐标_ 任务坐标1 = 任务::CALL_取任务坐标(指引任务1.dQuestId, 指引任务1.objBase, 指引任务1.dResAddr);
							功能::到指定地点找NPC交任务3(任务坐标1.大陆ID, 任务坐标1.地图ID, 任务坐标1.x, 任务坐标1.y, 任务坐标1.z, 0, 指引任务1.dQuestId, -1, 50, 指引任务1.dStep);
							return false;
						}
						if (指引任务1.dStep == 4)
						{
							坐标_ 任务坐标1 = 任务::CALL_取任务坐标(指引任务1.dQuestId, 指引任务1.objBase, 指引任务1.dResAddr);
							功能::到指定地点找NPC交任务3(任务坐标1.大陆ID, 任务坐标1.地图ID, 任务坐标1.x, 任务坐标1.y, 任务坐标1.z, 0, 指引任务1.dQuestId, -1, 50, 指引任务1.dStep);
							return false;
						}
						if (指引任务1.dStep == 5)
						{
							if (指引任务1.dState == 1)
							{
								坐标_ 任务坐标1 = 任务::CALL_取任务坐标(指引任务1.dQuestId, 指引任务1.objBase, 指引任务1.dResAddr);
								功能::到指定地点找NPC交任务3(任务坐标1.大陆ID, 任务坐标1.地图ID, 任务坐标1.x, 任务坐标1.y, 任务坐标1.z, 0, 指引任务1.dQuestId, -1, 50, 指引任务1.dStep);
								return false;
							}
							if (指引任务1.dState == 2)
							{
								坐标_ 任务坐标1 = 任务::CALL_取任务坐标(指引任务1.dQuestId, 指引任务1.objBase, 指引任务1.dResAddr);
								if (地图ID == 50048)
								{
									功能::到指定地点入港(3, 30703, 12583.000, 16724.000, 1, 50);
								}
								else
								{
									功能::到指定地点找NPC交任务3(任务坐标1.大陆ID, 任务坐标1.地图ID, 任务坐标1.x, 任务坐标1.y, 任务坐标1.z, 0, 指引任务1.dQuestId, -1, 50, 指引任务1.dStep);

								}
								return false;
							}
						}
						if (指引任务1.dStep == 6)
						{
							坐标_ 任务坐标1 = 任务::CALL_取任务坐标(指引任务1.dQuestId, 指引任务1.objBase, 指引任务1.dResAddr);
							功能::到指定地点找NPC交任务3(任务坐标1.大陆ID, 任务坐标1.地图ID, 任务坐标1.x, 任务坐标1.y, 任务坐标1.z, 0, 指引任务1.dQuestId, -1, 50, 指引任务1.dStep);
							return false;
						}
					}
					else//没交任务交完任务后会自动接到指引任务
					{
						vector<DWORD>vsk;
						任务::get_FinishQuestList(vsk);
						if (任务::任务是否已完成(0x3D0D6A, vsk) && 任务::任务是否已完成(0x3D0D6B, vsk))
						{

						}
						else
						{
							功能::到指定地点找NPC交任务3(11, 11102, 5290.259, -28528.775, 4149.653, -1, 指引任务.dQuestId, -1, 50, 指引任务.dStep);
						}
					}
				}
				return false;
			}
			if (指引任务.dStep == 3)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(指引任务.dQuestId, 指引任务.objBase, 指引任务.dResAddr);
				功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 指引任务.TargetId, 指引任务.dQuestId, -1, 50, 指引任务.dStep);
				return false;

			}
			if (指引任务.dStep == 4)
			{
				坐标_ 任务坐标 = 任务::CALL_取任务坐标(指引任务.dQuestId, 指引任务.objBase, 指引任务.dResAddr);
				功能::到指定地点找NPC交任务3(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 指引任务.TargetId, 指引任务.dQuestId, -1, 50, 指引任务.dStep);
				return false;

			}
			return false;
		}
	}
	return true;
}
bool 游戏::执行紫色任务()
{
	MyTrace(L"执行紫色任务");
	vector<DWORD>vsk;
	任务::get_FinishQuestList(vsk);
	if (任务::任务是否已完成(0x10EC6F, vsk))
	{
		MyTrace(L"执行紫色任务1");
		if (!任务::任务是否已完成(0x10EC74, vsk))
		{
			if (!任务::是否已接任务(0x10EC74))
			{
				if (地图::取地图ID() == 10801)
				{
					功能::到指定地点找NPC接任务2(2, 10801, -238, 6893, 453, 13007, 0x10EC74, 150);
					return false;
				}
				if (地图::取地图ID() == 10401)
				{
					功能::到指定地点找NPC接任务2(2, 10401, 8885, 17055, 768, 18502, 0x10EC74, 150);
					return false;
				}
				if (地图::取地图ID() == 11102)
				{
					功能::到指定地点找NPC接任务2(18, 11102, 7739, 7336, 4337, 25148, 0x10EC74, 150);
					return false;
				}
			}
			else
			{
				//return true;
				if (地图::取地图ID() == 10801)
				{
					功能::诞生石任务(10801, -238, 6893, 453, 13007, 150);
					return true;
				}
				if (地图::取地图ID() == 10401)
				{
					功能::诞生石任务(10401, 8885, 17055, 768, 18502, 150);
					return true;
				}
				if (地图::取地图ID() == 11102)
				{
					功能::诞生石任务(11102, 7739, 7336, 4337, 25148, 150);
					return true;
				}

			}
			return false;
		}
		else
		{

		}
	}
	return true;
}
void 功能::寻路到指定传送门(float x, float y, float z, DWORD 传送门ID, int 攻击范围)
{
	if (x == 0)
	{
		return;
	}
	if (GetDis(x, y, z) <= 200)
	{
		设置分段坐标已到达();
		路径分段坐标组.clear();

		objInfo_ 传送门 = 环境::取指定对象信息(传送门ID);
		if (传送门.dResId == 传送门ID)
		{
			MyTrace(L"传送门 %d %0.3f %0.3f %0.3f", 传送门.dResId, 传送门.坐标.x, 传送门.坐标.y, 传送门.坐标.z);
			功能::移动打怪(传送门.坐标.x, 传送门.坐标.y, 传送门.坐标.z, 0, 攻击范围);
		}
		Sleep(500);
	}
	else
	{
		功能::移动打怪(x, y, z, 0, 攻击范围);
		//地图::本地图寻路(x, y, z, 0);
		Sleep(500);
	}
}
void 功能::寻路到副本(DWORD 大陆ID, DWORD 地图ID, float x, float y, float z)
{
	/*if (x == 0)
	{
		return;
	}*/
	if (UI功能::副本界面是否打开() == true)
	{
		if (UI功能::进入副本())
		{
			MyTrace(L"点击进入副本");
			Sleep(2000);
			UI功能::getMsgBoxTextList();
			//UI功能::内存按键(VK_RETURN);
		}

	}
	else
	{
		//坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);
		功能::到指定地点按G(大陆ID, 地图ID, x, y, z, 50);
	}
}
void 功能::到指定地点按G(DWORD 大陆ID, DWORD 地图ID, float x, float y, float z, int 对话范围, int 打怪范围)
{

	//if (大陆ID == 地图::取当前大陆ID())
	//{
	if (地图::取地图ID() == 地图ID)
	{
		if (x == 0)
		{
			return;
		}
		if (GetDis(x, y, z) <= 对话范围)
		{
			if (优先打怪(打怪范围) == true)
			{
				设置分段坐标已到达();
				路径分段坐标组.clear();
				UI功能::内存按键(DWORD('G'));
				Sleep(500);
			}
		}
		else
		{
			功能::移动打怪(x, y, z, 0, 200, 打怪范围);
			//地图::本地图寻路(x, y, z, 0);
			Sleep(500);
		}
	}
	else
	{
		功能::跨地图ID处理(地图ID);
		MyTrace(L"不在同一地图,需要前往 当前地图:%d 目标地图%d", 地图::取地图ID(), 地图ID);
	}
	/*}
	else
	{
		MyTrace(L"不在同一大陆,需要前往 当前大陆:%d 目标大陆%d", 地图::取当前大陆ID(), 大陆ID);
	}*/
}
void 功能::到指定地点按G_无打怪(DWORD 大陆ID, DWORD 地图ID, float x, float y, float z, int 对话范围)
{

	if (大陆ID == 地图::取当前大陆ID())
	{
		if (地图::取地图ID() == 地图ID)
		{
			if (x == 0)
			{
				return;
			}
			//if (GetDis(x, y, z) <= 对话范围)
			//{	
			//	UI功能::内存按键(DWORD('G'));
			//	Sleep(500);				
			//}
			//else
			//{
			//	//功能::移动打怪(x, y, z, 0, 100, 打怪范围);
			//	地图::本地图寻路(x, y, z, 0);
			//	Sleep(500);
			//}
			if (GetDis(x, y, z) <= 对话范围)
			{
				UI功能::内存按键(DWORD('G'));
				Sleep(500);
			}
			else
			{
				if (本人::是否在走路2())
				{
					Sleep(100);
					return;
				}
				if (地图::指定地点是否可到达_M(x, y, z))
				{
					MyTrace(L"到指定地点按G_无打怪 目标可达");
					if (分段处理坐标.x1 != 0 && 分段处理坐标.操作 == 2)
					{
						前往分段处理坐标(x, y, z);
					}
					else
					{
						设置分段坐标已到达();
						路径分段坐标组.clear();
						地图::本地图寻路(x, y, z, 0);
						Sleep(100);
					}

				}
				else
				{
					MyTrace(L"前往分段处理");
					前往分段处理坐标(x, y, z);
				}
			}
		}
		else
		{
			功能::跨地图ID处理(地图ID);
			MyTrace(L"不在同一地图,需要前往 当前地图:%d 目标地图%d", 地图::取地图ID(), 地图ID);
		}
	}
	else
	{
		MyTrace(L"不在同一大陆,需要前往 当前大陆:%d 目标大陆%d", 地图::取当前大陆ID(), 大陆ID);
	}
}
void 功能::到指定地点乘坐电梯(DWORD 大陆ID, DWORD 地图ID, float x, float y, float z, int 对话范围, DWORD 电梯ResId)
{

	if (大陆ID == 地图::取当前大陆ID())
	{
		if (地图::取地图ID() == 地图ID)
		{
			if (x == 0)
			{
				return;
			}
			if (GetDis(x, y, z) <= 对话范围)
			{

				if (电梯ResId != 0)
				{
					objInfo_ 电梯信息 = 环境::取指定对象信息(电梯ResId);
					if (电梯信息.dType == 15)
					{
						MyTrace(L"乘坐 %s->%d ->modID %x", 电梯信息.wName, 电梯信息.dResId, 电梯信息.ModId);
						if (地图::本地图寻路(电梯信息.坐标.x, 电梯信息.坐标.y, 电梯信息.坐标.z, 电梯信息.ModId))
						{
							Sleep(2000);
							设置分段坐标已到达();
							路径分段坐标组.clear();
						}
					}
					else
					{
						MyTrace(L"目标不是电梯");
					}
				}
				else
				{
					vector<objInfo_>数组;
					环境::遍历电梯(数组);
					if (数组.size() > 0)
					{
						objInfo_ 电梯信息 = 数组[0];
						MyTrace(L"乘坐 %s->%d ->modID %x", 电梯信息.wName, 电梯信息.dResId, 电梯信息.ModId);
						if (地图::本地图寻路(电梯信息.坐标.x, 电梯信息.坐标.y, 电梯信息.坐标.z, 电梯信息.ModId))
						{
							Sleep(2000);
							设置分段坐标已到达();
							路径分段坐标组.clear();
						}

					}
				}

				Sleep(500);
			}
			else
			{
				功能::移动打怪(x, y, z, 0, 100);
				//地图::本地图寻路(x, y, z, 0);
				Sleep(1500);
			}
		}
		else
		{
			功能::跨地图ID处理(地图ID);
			MyTrace(L"不在同一地图,需要前往 当前地图:%d 目标地图%d", 地图::取地图ID(), 地图ID);
		}
	}
	else
	{
		MyTrace(L"不在同一大陆,需要前往 当前大陆:%d 目标大陆%d", 地图::取当前大陆ID(), 大陆ID);
	}
}
void 功能::到指定地点破坏击打道具(DWORD 大陆ID, DWORD 地图ID, float x, float y, float z, int 采集范围, int 采集目标ID, int 打怪范围)
{

	if (大陆ID == 地图::取当前大陆ID())
	{
		if (地图::取地图ID() == 地图ID)
		{
			if (x == 0)
			{
				return;
			}
			if (GetDis(x, y, z) <= 采集范围)
			{

				设置分段坐标已到达();
				路径分段坐标组.clear();

				if (优先打怪(打怪范围) == true)
				{
					objInfo_ 采集目标 = 环境::取指定对象信息(采集目标ID);
					if (采集目标.dResId != 0)
					{
						if (采集目标.fDis >= 500)
						{
						功能:移动打怪(采集目标.坐标.x, 采集目标.坐标.y, 采集目标.坐标.z, 打怪范围, 100);

						}
						else
						{
							破坏击打道具程序(采集目标.objBase, 采集目标.dResId);
							//UI功能::内存按键(DWORD('G'));

						}
					}
				}


				Sleep(500);
			}
			else
			{
				功能::移动打怪(x, y, z, 打怪范围, 100);
				//地图::本地图寻路(x, y, z, 0);
				Sleep(500);
			}
		}
		else
		{
			功能::跨地图ID处理(地图ID);
			MyTrace(L"不在同一地图,需要前往 当前地图:%d 目标地图%d", 地图::取地图ID(), 地图ID);
		}
	}
	else
	{
		MyTrace(L"不在同一大陆,需要前往 当前大陆:%d 目标大陆%d", 地图::取当前大陆ID(), 大陆ID);
	}
}
void 功能::到指定地点采集(DWORD 大陆ID, DWORD 地图ID, float x, float y, float z, int 采集范围, int 采集目标ID, int 打怪范围, int 按G范围)
{

	if (大陆ID == 地图::取当前大陆ID())
	{
		if (地图::取地图ID() == 地图ID)
		{
			if (x == 0)
			{
				return;
			}
			if (GetDis(x, y, z) <= 采集范围)
			{

				设置分段坐标已到达();
				路径分段坐标组.clear();

				if (优先打怪(打怪范围) == true)
				{
					objInfo_ 采集目标 = 环境::取指定采集对象信息(采集目标ID);
					if (采集目标.dResId != 0)
					{
						if (采集目标.fDis >= 按G范围)
						{
							if (地图::指定地点是否可到达_M(采集目标.坐标.x, 采集目标.坐标.y, 采集目标.坐标.z))
							{
								功能::移动打怪(采集目标.坐标.x, 采集目标.坐标.y, 采集目标.坐标.z, 50, 打怪范围, 100);
							}
							else
							{
								if (!本人::是否在走路())
								{
									srand((unsigned)time(NULL));
									int 随机值 = Random(1, 4);
									if (随机值 == 1)
									{
										地图::本地图寻路(采集目标.坐标.x - 100, 采集目标.坐标.y, 采集目标.坐标.z, 0);
										Sleep(1000);
									}
									if (随机值 == 2)
									{
										地图::本地图寻路(采集目标.坐标.x + 100, 采集目标.坐标.y, 采集目标.坐标.z, 0);
										Sleep(1000);
									}
									if (随机值 == 3)
									{
										地图::本地图寻路(采集目标.坐标.x, 采集目标.坐标.y + 100, 采集目标.坐标.z, 0);
										Sleep(1000);
									}
									if (随机值 == 4)
									{
										地图::本地图寻路(采集目标.坐标.x, 采集目标.坐标.y - 100, 采集目标.坐标.z, 0);
										Sleep(1000);
									}
								}

							}


						}
						else
						{
							UI功能::内存按键(DWORD('G'));
							Sleep(1000);

						}
					}
				}


				Sleep(500);
			}
			else
			{
				功能::移动打怪(x, y, z, 50, 打怪范围, 100);
				//地图::本地图寻路(x, y, z, 0);
				Sleep(500);
			}
		}
		else
		{
			功能::跨地图ID处理(地图ID);
			MyTrace(L"不在同一地图,需要前往 当前地图:%d 目标地图%d", 地图::取地图ID(), 地图ID);
		}
	}
	else
	{
		MyTrace(L"不在同一大陆,需要前往 当前大陆:%d 目标大陆%d", 地图::取当前大陆ID(), 大陆ID);
	}
}
void 功能::到指定地点采集任务显示(DWORD 大陆ID, DWORD 地图ID, float x, float y, float z, int 采集范围, int 采集目标ID, int 打怪范围, int 按G范围, bool 不打怪)
{

	//if (大陆ID == 地图::取当前大陆ID())
	//{
	if (地图::取地图ID() == 地图ID)
	{
		if (x == 0)
		{
			return;
		}
		if (不打怪 == false)
		{
			if (优先打怪(打怪范围) == false)
			{
				return;
			}
		}

		if (GetDis(x, y, z) >= 采集范围)
		{
			if (不打怪 == false)
			{
				功能::移动打怪(x, y, z, 50, 打怪范围, 100);
			}
			else
			{
				地图::本地图寻路(x, y, z, 0);

			}
			return;
		}
		if (本人::是否在走路())
		{
			Sleep(500);
			return;
		}
		bool 是否可达 = false;
		objInfo_ 采集目标 = 环境::取指定范围任务显示对象信息(x, y, z, 采集范围, 采集目标ID);
		MyTrace(L"采集目标 0x%I64x %s %d %0.3f,%0.3f %0.3f|距离:%0.3f 采集范围 %d", 采集目标.objBase, 采集目标.wName, 采集目标.dResShow, 采集目标.坐标.x, 采集目标.坐标.y, 采集目标.坐标.z, 采集目标.fDis, 采集范围);
		if (采集目标.dResId != 0)
		{
			if (采集目标.fDis >= 按G范围)
			{
				for (size_t i = 0; i < 8; i++)
				{
					if (地图::指定地点是否可到达_M(采集目标.坐标.x, 采集目标.坐标.y, 采集目标.坐标.z))
					{
						地图::本地图寻路(采集目标.坐标.x, 采集目标.坐标.y, 采集目标.坐标.z, 0);
						是否可达 = true;
						Sleep(1000);
						break;
					}
					if (地图::指定地点是否可到达_M(采集目标.坐标.x - (i + 1) * 50, 采集目标.坐标.y, 采集目标.坐标.z))
					{
						地图::本地图寻路(采集目标.坐标.x - (i + 1) * 50, 采集目标.坐标.y, 采集目标.坐标.z, 0);
						是否可达 = true;
						Sleep(1000);
						break;
					}
					if (地图::指定地点是否可到达_M(采集目标.坐标.x + (i + 1) * 50, 采集目标.坐标.y, 采集目标.坐标.z))
					{
						地图::本地图寻路(采集目标.坐标.x + (i + 1) * 50, 采集目标.坐标.y, 采集目标.坐标.z, 0);
						是否可达 = true;
						Sleep(1000);
						break;
					}
					if (地图::指定地点是否可到达_M(采集目标.坐标.x, 采集目标.坐标.y - (i + 1) * 50, 采集目标.坐标.z))
					{
						地图::本地图寻路(采集目标.坐标.x, 采集目标.坐标.y - (i + 1) * 50, 采集目标.坐标.z, 0);
						是否可达 = true;
						Sleep(1000);
						break;
					}
					if (地图::指定地点是否可到达_M(采集目标.坐标.x, 采集目标.坐标.y + (i + 1) * 50, 采集目标.坐标.z))
					{
						地图::本地图寻路(采集目标.坐标.x, 采集目标.坐标.y + (i + 1) * 50, 采集目标.坐标.z, 0);
						是否可达 = true;
						Sleep(1000);
						break;
					}
					Sleep(300);
				}
				if (是否可达 == false)
				{

				}
			}
			else
			{
				UI功能::内存按键(DWORD('G'));

			}
		}
		else
		{
			if (GetDis(x, y, z) <= 100)
			{
				MyTrace(L"附近无采集物");
				设置分段坐标已到达();
				路径分段坐标组.clear();
				Sleep(500);
			}
			else
			{
				MyTrace(L"移动到指定位置");
				if (不打怪 == false)
				{
					功能::移动打怪(x, y, z, 50, 打怪范围, 100);
				}
				else
				{
					地图::本地图寻路(x, y, z, 0);

				}
				//地图::本地图寻路(x, y, z, 0);
				Sleep(500);
			}
		}

	}
	else
	{
		功能::跨地图ID处理(地图ID);
		MyTrace(L"不在同一地图,需要前往 当前地图:%d 目标地图%d", 地图::取地图ID(), 地图ID);
	}
	//}
	//else
	//{
	//	MyTrace(L"不在同一大陆,需要前往 当前大陆:%d 目标大陆%d", 地图::取当前大陆ID(), 大陆ID);
	//}
}
void 功能::到指定地点采集任务显示_多目标(DWORD 大陆ID, DWORD 地图ID, float x, float y, float z, int 采集范围, int 采集目标ID, int 采集目标ID2, int 打怪范围, int 按G范围, bool 不打怪)
{

	//if (大陆ID == 地图::取当前大陆ID())
	//{
	if (地图::取地图ID() == 地图ID)
	{
		if (x == 0)
		{
			return;
		}
		if (GetDis(x, y, z) <= 采集范围)
		{

			设置分段坐标已到达();
			路径分段坐标组.clear();

			if (不打怪 == false)
			{
				if (优先打怪(打怪范围) == true)
				{
					objInfo_ 采集目标 = 环境::取指定任务显示对象信息(采集目标ID);
					MyTrace(L"采集目标 0x%I64x %s %d %0.3f,%0.3f %0.3f %d", 采集目标.objBase, 采集目标.wName, 采集目标.dResShow, 采集目标.坐标.x, 采集目标.坐标.y, 采集目标.坐标.z, 采集目标.fDis);
					if (采集目标.dResId != 0)
					{
						if (采集目标.fDis >= 按G范围)
						{

							功能::移动打怪(采集目标.坐标.x, 采集目标.坐标.y, 采集目标.坐标.z, 50, 打怪范围, 100);
							return;


						}
						else
						{
							UI功能::内存按键(DWORD('G'));
							return;
						}
					}
					objInfo_ 采集目标2 = 环境::取指定任务显示对象信息(采集目标ID2);
					MyTrace(L"采集目标2 0x%I64x %s %d %0.3f,%0.3f %0.3f %d", 采集目标2.objBase, 采集目标2.wName, 采集目标2.dResShow, 采集目标2.坐标.x, 采集目标2.坐标.y, 采集目标2.坐标.z, 采集目标2.fDis);
					if (采集目标2.dResId != 0)
					{
						if (采集目标2.fDis >= 按G范围)
						{

							功能::移动打怪(采集目标2.坐标.x, 采集目标2.坐标.y, 采集目标2.坐标.z, 50, 打怪范围, 100);
							return;
						}
						else
						{
							UI功能::内存按键(DWORD('G'));
							return;
						}
					}
				}
			}
			else
			{
				objInfo_ 采集目标 = 环境::取指定任务显示对象信息(采集目标ID);
				MyTrace(L"采集目标 0x%I64x %s %d %0.3f,%0.3f %0.3f %d", 采集目标.objBase, 采集目标.wName, 采集目标.dResShow, 采集目标.坐标.x, 采集目标.坐标.y, 采集目标.坐标.z, 采集目标.fDis);
				if (采集目标.dResId != 0)
				{
					if (采集目标.fDis >= 按G范围)
					{

						地图::本地图寻路(采集目标.坐标.x, 采集目标.坐标.y, 采集目标.坐标.z, 0);
						return;
					}
					else
					{
						UI功能::内存按键(DWORD('G'));
						return;
					}
				}
				objInfo_ 采集目标2 = 环境::取指定任务显示对象信息(采集目标ID2);
				MyTrace(L"采集目标2 0x%I64x %s %d %0.3f,%0.3f %0.3f %d", 采集目标2.objBase, 采集目标2.wName, 采集目标2.dResShow, 采集目标2.坐标.x, 采集目标2.坐标.y, 采集目标2.坐标.z, 采集目标2.fDis);
				if (采集目标2.dResId != 0)
				{
					if (采集目标2.fDis >= 按G范围)
					{

						地图::本地图寻路(采集目标2.坐标.x, 采集目标2.坐标.y, 采集目标2.坐标.z, 0);
						return;
					}
					else
					{
						UI功能::内存按键(DWORD('G'));
						return;
					}
				}
			}

			Sleep(500);
		}
		else
		{
			MyTrace(L"移动到指定位置");
			if (不打怪 == false)
			{
				功能::移动打怪(x, y, z, 50, 打怪范围, 100);
			}
			else
			{
				地图::本地图寻路(x, y, z, 0);

			}
			//地图::本地图寻路(x, y, z, 0);
			Sleep(500);
		}
	}
	else
	{
		功能::跨地图ID处理(地图ID);
		MyTrace(L"不在同一地图,需要前往 当前地图:%d 目标地图%d", 地图::取地图ID(), 地图ID);
	}
	//}
	//else
	//{
	//	MyTrace(L"不在同一大陆,需要前往 当前大陆:%d 目标大陆%d", 地图::取当前大陆ID(), 大陆ID);
	//}
}
int 返回第几大陆(DWORD 大陆ID)
{
	if (大陆ID == 1)
	{
		return 1;
	}
	if (大陆ID == 17)
	{
		return 1;
	}
	if (大陆ID == 14)
	{
		return 1;
	}
	if (大陆ID == 15)
	{
		return 1;
	}
	if (大陆ID == 22)
	{
		return 1;
	}
	if (大陆ID == 3)
	{
		return 2;
	}
	if (大陆ID == 4)
	{
		return 2;
	}
	return -1;
}
bool 是否处于同一大陆(DWORD 目标大陆ID, DWORD 当前大陆ID)
{
	int 第几大陆1 = 返回第几大陆(目标大陆ID);
	int 第几大陆2 = 返回第几大陆(当前大陆ID);
	if (第几大陆1 == 第几大陆2)
	{
		return true;
	}
	return true;
}
void 功能::到指定地点打开NPC(DWORD 大陆ID, DWORD 地图ID, float x, float y, float z, int 对话范围, DWORD NpcResId)
{

	//if (是否处于同一大陆(大陆ID,地图::取当前大陆ID()))
	//{
	MyTrace(L"当前地图 %d   任务地图 %d", 地图::取地图ID(), 地图ID);
	if (地图::取地图ID() == 地图ID)
	{
		if (x == 0)
		{
			return;
		}
		if (GetDis(x, y, z) <= 对话范围)
		{
			MyTrace(L"NPC对话范围内");
			if (!优先打怪(150))
			{
				return;
			}
			设置分段坐标已到达();
			路径分段坐标组.clear();
			if (NpcResId != 0 && NpcResId != -1)
			{
				MyTrace(L"任务处理 打开NPC %d", NpcResId);
				环境::CALL_点击指定NPC_ByResId(NpcResId);
			}
			else
			{
				MyTrace(L"任务处理 按G");
				UI功能::内存按键(DWORD('G'));
			}

			//UI功能::内存按键(DWORD('G'));
			Sleep(500);
		}
		else
		{
			MyTrace(L"移动打怪");
			移动打怪(x, y, z, 0, 100, 100);
			//地图::本地图寻路(x, y, z, 0);
			Sleep(500);
		}
	}
	else
	{
		功能::跨地图ID处理(地图ID);
		MyTrace(L"不在同一地图,需要前往");
	}
	//}
	/*else
	{
		MyTrace(L"不在同一大陆,需要前往 %d/%d", 大陆ID, 地图::取当前大陆ID());
	}*/
}
bool 功能::到指定地点(DWORD 大陆ID, DWORD 地图ID, float x, float y, float z, int 到达范围, bool 不打怪)
{

	/*if (大陆ID == 地图::取当前大陆ID())
	{*/
	if (地图::取地图ID() == 地图ID)
	{

		if (x == 0)
		{
			return false;
		}

		if (GetDis(x, y, z) <= 到达范围)
		{

			设置分段坐标已到达();
			路径分段坐标组.clear();

			return true;
			//UI功能::内存按键(DWORD('G'));
			Sleep(500);
		}
		else
		{
			if (地图ID == 30703)
			{
				if (UI功能::是否在航海准备界面())
				{
					if (航海::自动选择最优战船())
					{
						本人::CALL_修理船只(航海::getCurVoyageShipResId());
						Sleep(1000);
						UI功能::航海出港();
						Sleep(1000);
					}
					return false;
				}
			}
			if (不打怪 == false)
			{
				移动打怪(x, y, z, 0, 100, 100);
			}
			else
			{
				地图::本地图寻路(x, y, z, 0);
			}
			Sleep(100);
		}
	}
	else
	{
		功能::跨地图ID处理(地图ID);
		MyTrace(L"不在同一地图,需要前往");
	}
	/*}
	else
	{
		MyTrace(L"不在同一大陆,需要前往 %d/%d", 大陆ID, 地图::取当前大陆ID());
	}*/
	return false;
}
bool 功能::到指定地点入港(DWORD 大陆ID, DWORD 地图ID, float x, float y, float z, int 到达范围)
{

	/*if (大陆ID == 地图::取当前大陆ID())
	{*/
	if (地图::取地图ID() == 地图ID)
	{

		if (x == 0)
		{
			return false;
		}

		if (GetDis(x, y, z) <= 到达范围)
		{
			if (!UI功能::是否在航海准备界面())
			{
				UI功能::内存按键('Z');
				Sleep(3000);
				return false;
			}
			else
			{
				UI功能::航海入港();
				设置分段坐标已到达();
				路径分段坐标组.clear();

				return true;
				//UI功能::内存按键(DWORD('G'));
				Sleep(500);
			}

		}
		else
		{
			if (地图ID == 30703)
			{
				if (UI功能::是否在航海准备界面())
				{
					if (航海::自动选择最优战船())
					{
						MyTrace(L"修理船只");
						本人::CALL_修理船只(航海::getCurVoyageShipResId());
						Sleep(1000);
						MyTrace(L"出港");
						UI功能::航海出港();
						Sleep(1000);
					}
					return false;
				}
			}
			地图::本地图寻路(x, y, z, 0);
			//
			Sleep(500);
		}
	}
	else
	{
		功能::跨地图ID处理(地图ID);
		MyTrace(L"到指定地点入港 不在同一地图,需要前往 目的地图 %d", 地图ID);
	}
	/*}
	else
	{
		MyTrace(L"不在同一大陆,需要前往 %d/%d", 大陆ID, 地图::取当前大陆ID());
	}*/
	return false;
}
节点处理_ 获取节点信息(DWORD 当前地图ID)
{
	节点处理_ 返回信息;
	if (当前地图ID == 10201)
	{
		返回信息.地图ID = 10201;
		分段处理信息_ 下一张地图传送门;
		下一张地图传送门.属于分段 = 1;
		下一张地图传送门.坐标.x = 5452;
		下一张地图传送门.坐标.y = 10335;
		下一张地图传送门.坐标.z = 2;
		返回信息.前往下一张地图传送门 = 下一张地图传送门;
		小地图信息_ temp;
		temp.属于分段 = 1;
		temp.标记 = 1;//大教堂
		temp.进入坐标.x = 10894;
		temp.进入坐标.y = 3956;
		temp.进入坐标.z = 788;
		temp.返回坐标.x = 10947;
		temp.返回坐标.y = 3954;
		temp.返回坐标.z = -15356;
		返回信息.小地图组.Add(temp);
		temp.属于分段 = 2;
		temp.标记 = 2;//酒馆
		temp.进入坐标.x = 9052;
		temp.进入坐标.y = 8354;
		temp.进入坐标.z = 256;
		temp.返回坐标.x = 9044;
		temp.返回坐标.y = 8225;
		temp.返回坐标.z = -15360;
		返回信息.小地图组.Add(temp);
		temp.属于分段 = 3;
		temp.标记 = 3;//装备商人店
		temp.进入坐标.x = 8141;
		temp.进入坐标.y = 8556;
		temp.进入坐标.z = 282;
		temp.返回坐标.x = 7626;
		temp.返回坐标.y = 8701;
		temp.返回坐标.z = -18015;
		返回信息.小地图组.Add(temp);
		记录传送点信息_ temp2;
		temp2.属于分段 = 1;
		temp2.ResId = 0xDBBA1;
		temp2.名称 = L"莱温哈特";
		temp2.坐标.x = 7811;
		temp2.坐标.y = 4064;
		temp2.坐标.z = 272;
		返回信息.传送点组.Add(temp2);
	}
	if (当前地图ID == 10213)
	{
		返回信息.地图ID = 10213;
		分段处理信息_ 下一张地图传送门;
		下一张地图传送门.属于分段 = 1;
		下一张地图传送门.坐标.x = 6331;
		下一张地图传送门.坐标.y = 32853;
		下一张地图传送门.坐标.z = 1007;
		下一张地图传送门.处理方式 = 2;
		返回信息.前往下一张地图传送门 = 下一张地图传送门;
		返回信息.前往上一张地图传送门 = 下一张地图传送门;
	}
	if (当前地图ID == 10211)
	{
		返回信息.地图ID = 10211;
		分段处理信息_ 上一张地图传送门;
		上一张地图传送门.属于分段 = 1;
		上一张地图传送门.坐标.x = 1752;
		上一张地图传送门.坐标.y = 12414;
		上一张地图传送门.坐标.z = 0;
		上一张地图传送门.处理方式 = 0;
		返回信息.前往上一张地图传送门 = 上一张地图传送门;
		分段处理信息_ 下一张地图传送门;
		下一张地图传送门.属于分段 = 1;
		下一张地图传送门.坐标.x = 28336;
		下一张地图传送门.坐标.y = 55535;
		下一张地图传送门.坐标.z = 256;
		下一张地图传送门.处理方式 = 0;
		返回信息.前往下一张地图传送门 = 下一张地图传送门;
	}
	if (当前地图ID == 10211)
	{
		返回信息.地图ID = 10211;
		分段处理信息_ 上一张地图传送门;
		上一张地图传送门.属于分段 = 1;
		上一张地图传送门.坐标.x = 1752;
		上一张地图传送门.坐标.y = 12414;
		上一张地图传送门.坐标.z = 0;
		上一张地图传送门.处理方式 = 0;
		返回信息.前往上一张地图传送门 = 上一张地图传送门;
		分段处理信息_ 下一张地图传送门;
		下一张地图传送门.属于分段 = 1;
		下一张地图传送门.坐标.x = 28336;
		下一张地图传送门.坐标.y = 55535;
		下一张地图传送门.坐标.z = 256;
		下一张地图传送门.处理方式 = 0;
		返回信息.前往下一张地图传送门 = 下一张地图传送门;
	}
	if (当前地图ID == 10220)
	{
		返回信息.地图ID = 10220;
		分段处理信息_ 上一张地图传送门;
		上一张地图传送门.属于分段 = 1;
		上一张地图传送门.坐标.x = 333;
		上一张地图传送门.坐标.y = -1098;
		上一张地图传送门.坐标.z = -512;
		上一张地图传送门.处理方式 = 0;
		返回信息.前往上一张地图传送门 = 上一张地图传送门;
		分段处理信息_ 下一张地图传送门;
		下一张地图传送门.属于分段 = 1;
		下一张地图传送门.坐标.x = 19029;
		下一张地图传送门.坐标.y = 13488, 221;
		下一张地图传送门.坐标.z = 221;
		下一张地图传送门.处理方式 = 0;
		返回信息.前往下一张地图传送门 = 下一张地图传送门;
	}
	if (当前地图ID == 10222)
	{
		返回信息.地图ID = 10222;
		分段处理信息_ 上一张地图传送门;
		上一张地图传送门.属于分段 = 1;
		上一张地图传送门.坐标.x = -635;
		上一张地图传送门.坐标.y = -2020;
		上一张地图传送门.坐标.z = -2;
		上一张地图传送门.处理方式 = 0;
		返回信息.前往上一张地图传送门 = 上一张地图传送门;
		分段处理信息_ 下一张地图传送门;
		下一张地图传送门.属于分段 = 1;
		下一张地图传送门.坐标.x = 23934;
		下一张地图传送门.坐标.y = 24512;
		下一张地图传送门.坐标.z = 529;
		下一张地图传送门.处理方式 = 0;
		返回信息.前往下一张地图传送门 = 下一张地图传送门;
	}
	if (当前地图ID == 10611)
	{
		返回信息.地图ID = 10611;
		分段处理信息_ 上一张地图传送门;
		上一张地图传送门.属于分段 = 1;
		上一张地图传送门.坐标.x = -7474;
		上一张地图传送门.坐标.y = -12808;
		上一张地图传送门.坐标.z = 1024;
		上一张地图传送门.处理方式 = 0;
		返回信息.前往上一张地图传送门 = 上一张地图传送门;
		分段处理信息_ 下一张地图传送门;
		下一张地图传送门.属于分段 = 1;
		下一张地图传送门.坐标.x = 30117;
		下一张地图传送门.坐标.y = 22401;
		下一张地图传送门.坐标.z = 509;
		下一张地图传送门.处理方式 = 0;
		返回信息.前往下一张地图传送门 = 下一张地图传送门;

	}
	if (当前地图ID == 10619)
	{
		//-15806/8152/512
		//下一个地图传送门  13190/11711/1026 
		返回信息.地图ID = 10619;
		分段处理信息_ 上一张地图传送门;
		上一张地图传送门.属于分段 = 1;
		上一张地图传送门.坐标.x = -15806;
		上一张地图传送门.坐标.y = 8152;
		上一张地图传送门.坐标.z = 512;
		上一张地图传送门.处理方式 = 0;
		返回信息.前往上一张地图传送门 = 上一张地图传送门;
		分段处理信息_ 下一张地图传送门;
		下一张地图传送门.属于分段 = 1;
		下一张地图传送门.坐标.x = 13190;
		下一张地图传送门.坐标.y = 11711;
		下一张地图传送门.坐标.z = 1026;
		下一张地图传送门.处理方式 = 0;
		返回信息.前往下一张地图传送门 = 下一张地图传送门;
	}
	if (当前地图ID == 10811)
	{
		//-336/857/503
		//下一个地图传送门  22942/-3752/1023
		返回信息.地图ID = 10811;
		分段处理信息_ 上一张地图传送门;
		上一张地图传送门.属于分段 = 1;
		上一张地图传送门.坐标.x = -336;
		上一张地图传送门.坐标.y = 857;
		上一张地图传送门.坐标.z = 503;
		上一张地图传送门.处理方式 = 0;
		返回信息.前往上一张地图传送门 = 上一张地图传送门;
		分段处理信息_ 下一张地图传送门;
		下一张地图传送门.属于分段 = 1;
		下一张地图传送门.坐标.x = 22942;
		下一张地图传送门.坐标.y = -3752;
		下一张地图传送门.坐标.z = 1023;
		下一张地图传送门.处理方式 = 0;
		返回信息.前往下一张地图传送门 = 下一张地图传送门;
	}
	if (当前地图ID == 10812)
	{
		//-336/857/503
		//下一个地图传送门  22942/-3752/1023
		返回信息.地图ID = 10812;
		分段处理信息_ 上一张地图传送门;
		上一张地图传送门.属于分段 = 1;
		上一张地图传送门.坐标.x = 2708;
		上一张地图传送门.坐标.y = 23224;
		上一张地图传送门.坐标.z = 2048;
		上一张地图传送门.处理方式 = 0;
		返回信息.前往上一张地图传送门 = 上一张地图传送门;
		分段处理信息_ 下一张地图传送门;
		下一张地图传送门.属于分段 = 1;
		下一张地图传送门.坐标.x = 25715;
		下一张地图传送门.坐标.y = 23825;
		下一张地图传送门.坐标.z = 2097;
		下一张地图传送门.处理方式 = 0;
		返回信息.前往下一张地图传送门 = 下一张地图传送门;
	}
	if (当前地图ID == 10813)
	{
		//-336/857/503
		//下一个地图传送门  22942/-3752/1023
		返回信息.地图ID = 10813;
		分段处理信息_ 上一张地图传送门;
		上一张地图传送门.属于分段 = 1;
		上一张地图传送门.坐标.x = 856;
		上一张地图传送门.坐标.y = -1689;
		上一张地图传送门.坐标.z = 1958;
		上一张地图传送门.处理方式 = 0;
		返回信息.前往上一张地图传送门 = 上一张地图传送门;
		分段处理信息_ 下一张地图传送门;
		下一张地图传送门.属于分段 = 1;
		下一张地图传送门.坐标.x = 26537;
		下一张地图传送门.坐标.y = 23742;
		下一张地图传送门.坐标.z = -1022;
		下一张地图传送门.处理方式 = 0;
		返回信息.前往下一张地图传送门 = 下一张地图传送门;
	}
	if (当前地图ID == 10814)
	{
		//-336/857/503
		//下一个地图传送门  22942/-3752/1023
		返回信息.地图ID = 10814;
		分段处理信息_ 上一张地图传送门;
		上一张地图传送门.属于分段 = 1;
		上一张地图传送门.坐标.x = 1596;
		上一张地图传送门.坐标.y = -2975;
		上一张地图传送门.坐标.z = 2045;
		上一张地图传送门.处理方式 = 0;
		返回信息.前往上一张地图传送门 = 上一张地图传送门;
		分段处理信息_ 下一张地图传送门;
		下一张地图传送门.属于分段 = 1;
		下一张地图传送门.坐标.x = 2221;
		下一张地图传送门.坐标.y = 19572;
		下一张地图传送门.坐标.z = 1226;
		下一张地图传送门.处理方式 = 0;
		返回信息.前往下一张地图传送门 = 下一张地图传送门;
	}
	if (当前地图ID == 10815)
	{
		//-336/857/503
		//下一个地图传送门  22942/-3752/1023
		返回信息.地图ID = 10815;
		分段处理信息_ 上一张地图传送门;
		上一张地图传送门.属于分段 = 1;
		上一张地图传送门.坐标.x = 25760;
		上一张地图传送门.坐标.y = -1461;
		上一张地图传送门.坐标.z = 2566;
		上一张地图传送门.处理方式 = 0;
		返回信息.前往上一张地图传送门 = 上一张地图传送门;
		分段处理信息_ 下一张地图传送门;
		下一张地图传送门.属于分段 = 1;
		下一张地图传送门.坐标.x = 12405;
		下一张地图传送门.坐标.y = 23555;
		下一张地图传送门.坐标.z = 518;
		下一张地图传送门.处理方式 = 0;
		返回信息.前往下一张地图传送门 = 下一张地图传送门;
	}
	if (当前地图ID == 10801)
	{
		//-336/857/503
		//下一个地图传送门  22942/-3752/1023
		返回信息.地图ID = 10801;
		分段处理信息_ 上一张地图传送门;
		上一张地图传送门.属于分段 = 1;
		上一张地图传送门.坐标.x = -8186;
		上一张地图传送门.坐标.y = -1900;
		上一张地图传送门.坐标.z = 0;
		上一张地图传送门.处理方式 = 0;
		返回信息.前往上一张地图传送门 = 上一张地图传送门;
		分段处理信息_ 下一张地图传送门;
		下一张地图传送门.属于分段 = 1;
		下一张地图传送门.坐标.x = -8203;
		下一张地图传送门.坐标.y = 1920;
		下一张地图传送门.坐标.z = 0;
		下一张地图传送门.处理方式 = 0;
		返回信息.前往下一张地图传送门 = 下一张地图传送门;
	}
	if (当前地图ID == 10816)
	{
		//-336/857/503
		//下一个地图传送门  22942/-3752/1023
		返回信息.地图ID = 10816;
		分段处理信息_ 上一张地图传送门;
		上一张地图传送门.属于分段 = 1;
		上一张地图传送门.坐标.x = 15908;
		上一张地图传送门.坐标.y = -3171;
		上一张地图传送门.坐标.z = 1541;
		上一张地图传送门.处理方式 = 0;
		返回信息.前往上一张地图传送门 = 上一张地图传送门;
		分段处理信息_ 下一张地图传送门;
		下一张地图传送门.属于分段 = 1;
		下一张地图传送门.坐标.x = 1424;
		下一张地图传送门.坐标.y = 19915;
		下一张地图传送门.坐标.z = 1536;
		下一张地图传送门.处理方式 = 0;
		返回信息.前往下一张地图传送门 = 下一张地图传送门;
	}
	if (当前地图ID == 10817)
	{
		//-336/857/503
		//下一个地图传送门  22942/-3752/1023
		返回信息.地图ID = 10817;
		分段处理信息_ 上一张地图传送门;
		上一张地图传送门.属于分段 = 1;
		上一张地图传送门.坐标.x = -25604;
		上一张地图传送门.坐标.y = -24166;
		上一张地图传送门.坐标.z = 768;
		上一张地图传送门.处理方式 = 0;
		返回信息.前往上一张地图传送门 = 上一张地图传送门;
		分段处理信息_ 下一张地图传送门;
		下一张地图传送门.属于分段 = 1;
		下一张地图传送门.坐标.x = -20128;
		下一张地图传送门.坐标.y = -6348;
		下一张地图传送门.坐标.z = 769;
		下一张地图传送门.处理方式 = 0;
		返回信息.前往下一张地图传送门 = 下一张地图传送门;
	}
	if (当前地图ID == 10818)
	{
		//-336/857/503
		//下一个地图传送门  22942/-3752/1023
		返回信息.地图ID = 10818;
		分段处理信息_ 上一张地图传送门;
		上一张地图传送门.属于分段 = 1;
		上一张地图传送门.坐标.x = -28731;
		上一张地图传送门.坐标.y = -26512;
		上一张地图传送门.坐标.z = 768;
		上一张地图传送门.处理方式 = 0;
		返回信息.前往上一张地图传送门 = 上一张地图传送门;
		分段处理信息_ 下一张地图传送门;
		下一张地图传送门.属于分段 = 1;
		下一张地图传送门.坐标.x = -3056;
		下一张地图传送门.坐标.y = -6129;
		下一张地图传送门.坐标.z = 1024;
		下一张地图传送门.处理方式 = 0;
		返回信息.前往下一张地图传送门 = 下一张地图传送门;
	}
	if (当前地图ID == 10819)
	{
		//-336/857/503
		//下一个地图传送门  22942/-3752/1023
		返回信息.地图ID = 10819;
		分段处理信息_ 上一张地图传送门;
		上一张地图传送门.属于分段 = 1;
		上一张地图传送门.坐标.x = 6272;
		上一张地图传送门.坐标.y = 4124;
		上一张地图传送门.坐标.z = 0;
		上一张地图传送门.处理方式 = 0;
		返回信息.前往上一张地图传送门 = 上一张地图传送门;
		分段处理信息_ 下一张地图传送门;
		下一张地图传送门.属于分段 = 1;
		下一张地图传送门.坐标.x = 5393;
		下一张地图传送门.坐标.y = 26399;
		下一张地图传送门.坐标.z = -255;
		下一张地图传送门.处理方式 = 0;
		返回信息.前往下一张地图传送门 = 下一张地图传送门;
	}
	if (当前地图ID == 10835)
	{
		//-336/857/503
		//下一个地图传送门  22942/-3752/1023
		返回信息.地图ID = 10835;
		分段处理信息_ 上一张地图传送门;
		//-20837,-8097,513 
		上一张地图传送门.属于分段 = 1;
		上一张地图传送门.坐标.x = -20837;
		上一张地图传送门.坐标.y = -8097;
		上一张地图传送门.坐标.z = 513;
		上一张地图传送门.处理方式 = 0;
		返回信息.前往上一张地图传送门 = 上一张地图传送门;

	}
	if (当前地图ID == 10820)
	{
		//-336/857/503
		//下一个地图传送门  22942/-3752/1023
		返回信息.地图ID = 10820;
		分段处理信息_ 上一张地图传送门;
		上一张地图传送门.属于分段 = 1;
		上一张地图传送门.坐标.x = -13182;
		上一张地图传送门.坐标.y = -29793;
		上一张地图传送门.坐标.z = 1024;
		上一张地图传送门.处理方式 = 0;
		返回信息.前往上一张地图传送门 = 上一张地图传送门;
		分段处理信息_ 下一张地图传送门;
		下一张地图传送门.属于分段 = 1;
		下一张地图传送门.坐标.x = -22041;
		下一张地图传送门.坐标.y = -4601;
		下一张地图传送门.坐标.z = 617;
		下一张地图传送门.处理方式 = 0;
		返回信息.前往下一张地图传送门 = 下一张地图传送门;
	}
	if (当前地图ID == 10821)
	{
		//-336/857/503
		//下一个地图传送门  22942/-3752/1023
		返回信息.地图ID = 10821;
		分段处理信息_ 上一张地图传送门;
		上一张地图传送门.属于分段 = 1;
		上一张地图传送门.坐标.x = -26194;
		上一张地图传送门.坐标.y = -28779;
		上一张地图传送门.坐标.z = 512;
		上一张地图传送门.处理方式 = 0;
		返回信息.前往上一张地图传送门 = 上一张地图传送门;
		分段处理信息_ 下一张地图传送门;
		下一张地图传送门.属于分段 = 1;
		下一张地图传送门.坐标.x = -21610;
		下一张地图传送门.坐标.y = -1626;
		下一张地图传送门.坐标.z = 512;
		下一张地图传送门.处理方式 = 0;
		返回信息.前往下一张地图传送门 = 下一张地图传送门;
	}
	if (当前地图ID == 10804)
	{
		//-336/857/503
		//下一个地图传送门  22942/-3752/1023
		返回信息.地图ID = 10804;
		分段处理信息_ 上一张地图传送门;
		上一张地图传送门.属于分段 = 1;
		上一张地图传送门.坐标.x = 9361;
		上一张地图传送门.坐标.y = 3329;
		上一张地图传送门.坐标.z = 761;
		上一张地图传送门.处理方式 = 0;
		返回信息.前往上一张地图传送门 = 上一张地图传送门;
		分段处理信息_ 下一张地图传送门;
		下一张地图传送门.属于分段 = 1;
		下一张地图传送门.坐标.x = 5485;
		下一张地图传送门.坐标.y = 3407;
		下一张地图传送门.坐标.z = 246;
		下一张地图传送门.处理方式 = 0;
		返回信息.前往下一张地图传送门 = 下一张地图传送门;
	}
	if (当前地图ID == 11015)
	{
		//-336/857/503
		//下一个地图传送门  22942/-3752/1023
		返回信息.地图ID = 11015;
		分段处理信息_ 上一张地图传送门;
		上一张地图传送门.属于分段 = 1;
		上一张地图传送门.坐标.x = 6427;
		上一张地图传送门.坐标.y = 1097;
		上一张地图传送门.坐标.z = 267;
		上一张地图传送门.处理方式 = 0;
		返回信息.前往上一张地图传送门 = 上一张地图传送门;
		分段处理信息_ 下一张地图传送门;
		下一张地图传送门.属于分段 = 1;
		下一张地图传送门.坐标.x = 6427;
		下一张地图传送门.坐标.y = 1097;
		下一张地图传送门.坐标.z = 267;
		下一张地图传送门.处理方式 = 0;
		返回信息.前往下一张地图传送门 = 下一张地图传送门;
	}
	if (当前地图ID == 11016)
	{
		//-336/857/503
		//下一个地图传送门  22942/-3752/1023
		返回信息.地图ID = 11016;
		分段处理信息_ 上一张地图传送门;
		上一张地图传送门.属于分段 = 1;
		上一张地图传送门.坐标.x = 8203;
		上一张地图传送门.坐标.y = 5716;
		上一张地图传送门.坐标.z = -5100;
		上一张地图传送门.处理方式 = 0;
		返回信息.前往上一张地图传送门 = 上一张地图传送门;
		分段处理信息_ 下一张地图传送门;
		下一张地图传送门.属于分段 = 1;
		下一张地图传送门.坐标.x = 8203;
		下一张地图传送门.坐标.y = 5716;
		下一张地图传送门.坐标.z = -5100;
		下一张地图传送门.处理方式 = 0;
		返回信息.前往下一张地图传送门 = 下一张地图传送门;
	}
	if (当前地图ID == 11001)
	{
		//-336/857/503
		//下一个地图传送门  22942/-3752/1023
		返回信息.地图ID = 11001;
		分段处理信息_ 上一张地图传送门;
		上一张地图传送门.属于分段 = 1;
		上一张地图传送门.坐标.x = 4347;
		上一张地图传送门.坐标.y = 336;
		上一张地图传送门.坐标.z = 256;
		上一张地图传送门.处理方式 = 0;
		返回信息.前往上一张地图传送门 = 上一张地图传送门;
		分段处理信息_ 下一张地图传送门;
		下一张地图传送门.属于分段 = 1;
		下一张地图传送门.坐标.x = 1071;
		下一张地图传送门.坐标.y = 7836;
		下一张地图传送门.坐标.z = 670;
		下一张地图传送门.处理方式 = 0;
		返回信息.前往下一张地图传送门 = 下一张地图传送门;
	}
	if (当前地图ID == 11018)
	{
		//-336/857/503
		//下一个地图传送门  22942/-3752/1023
		返回信息.地图ID = 11018;
		分段处理信息_ 上一张地图传送门;
		上一张地图传送门.属于分段 = 1;
		上一张地图传送门.坐标.x = 6641;
		上一张地图传送门.坐标.y = 22423;
		上一张地图传送门.坐标.z = 459;
		上一张地图传送门.处理方式 = 0;
		返回信息.前往上一张地图传送门 = 上一张地图传送门;
		分段处理信息_ 下一张地图传送门;
		下一张地图传送门.属于分段 = 1;
		下一张地图传送门.坐标.x = 6641;
		下一张地图传送门.坐标.y = 22423;
		下一张地图传送门.坐标.z = 459;
		下一张地图传送门.处理方式 = 0;
		返回信息.前往下一张地图传送门 = 下一张地图传送门;
	}
	if (当前地图ID == 11012)
	{
		//-336/857/503
		//下一个地图传送门  22942/-3752/1023
		返回信息.地图ID = 11012;
		分段处理信息_ 上一张地图传送门;
		上一张地图传送门.属于分段 = 1;
		上一张地图传送门.坐标.x = 6641;
		上一张地图传送门.坐标.y = 22423;
		上一张地图传送门.坐标.z = 459;
		上一张地图传送门.处理方式 = 0;
		返回信息.前往上一张地图传送门 = 上一张地图传送门;
		分段处理信息_ 下一张地图传送门;
		下一张地图传送门.属于分段 = 1;
		下一张地图传送门.坐标.x = 25994;
		下一张地图传送门.坐标.y = 3991;
		下一张地图传送门.坐标.z = 960;
		下一张地图传送门.处理方式 = 0;
		返回信息.前往下一张地图传送门 = 下一张地图传送门;
	}
	if (当前地图ID == 11013)
	{
		//-336/857/503
		//下一个地图传送门  22942/-3752/1023
		返回信息.地图ID = 11013;
		分段处理信息_ 上一张地图传送门;
		上一张地图传送门.属于分段 = 1;
		上一张地图传送门.坐标.x = 2550;
		上一张地图传送门.坐标.y = 4326;
		上一张地图传送门.坐标.z = -258;
		上一张地图传送门.处理方式 = 0;
		返回信息.前往上一张地图传送门 = 上一张地图传送门;
		分段处理信息_ 下一张地图传送门;
		下一张地图传送门.属于分段 = 1;
		下一张地图传送门.坐标.x = 29185;
		下一张地图传送门.坐标.y = 29514;
		下一张地图传送门.坐标.z = 3586;
		下一张地图传送门.处理方式 = 0;
		返回信息.前往下一张地图传送门 = 下一张地图传送门;
	}
	if (当前地图ID == 11020)
	{
		//-336/857/503
		//下一个地图传送门  22942/-3752/1023
		返回信息.地图ID = 11012;
		分段处理信息_ 上一张地图传送门;
		上一张地图传送门.属于分段 = 1;
		上一张地图传送门.坐标.x = 26174;
		上一张地图传送门.坐标.y = 19374;
		上一张地图传送门.坐标.z = 3085;
		上一张地图传送门.处理方式 = 0;
		返回信息.前往上一张地图传送门 = 上一张地图传送门;
		分段处理信息_ 下一张地图传送门;
		下一张地图传送门.属于分段 = 1;
		下一张地图传送门.坐标.x = 26174;
		下一张地图传送门.坐标.y = 19374;
		下一张地图传送门.坐标.z = 3085;
		下一张地图传送门.处理方式 = 0;
		返回信息.前往下一张地图传送门 = 下一张地图传送门;
	}
	if (当前地图ID == 10701)
	{
		//-336/857/503
		//下一个地图传送门  22942/-3752/1023
		返回信息.地图ID = 10701;
		分段处理信息_ 上一张地图传送门;
		上一张地图传送门.属于分段 = 1;
		上一张地图传送门.坐标.x = 26174;
		上一张地图传送门.坐标.y = 19374;
		上一张地图传送门.坐标.z = 3085;
		上一张地图传送门.处理方式 = 0;
		返回信息.前往上一张地图传送门 = 上一张地图传送门;
		分段处理信息_ 下一张地图传送门;
		下一张地图传送门.属于分段 = 1;
		下一张地图传送门.坐标.x = -11288;
		下一张地图传送门.坐标.y = 19012;
		下一张地图传送门.坐标.z = 516;
		下一张地图传送门.处理方式 = 0;
		返回信息.前往下一张地图传送门 = 下一张地图传送门;
	}
	if (当前地图ID == 10721)
	{
		//-336/857/503
		//下一个地图传送门  22942/-3752/1023
		返回信息.地图ID = 10721;
		分段处理信息_ 上一张地图传送门;
		上一张地图传送门.属于分段 = 1;
		上一张地图传送门.坐标.x = 1888;
		上一张地图传送门.坐标.y = -3376;
		上一张地图传送门.坐标.z = 1025;
		上一张地图传送门.处理方式 = 0;
		返回信息.前往上一张地图传送门 = 上一张地图传送门;
		分段处理信息_ 下一张地图传送门;
		下一张地图传送门.属于分段 = 1;
		下一张地图传送门.坐标.x = -11288;
		下一张地图传送门.坐标.y = 19012;
		下一张地图传送门.坐标.z = 516;
		下一张地图传送门.处理方式 = 0;
		返回信息.前往下一张地图传送门 = 下一张地图传送门;
	}
	if (当前地图ID == 10722)
	{
		//-336/857/503
		//下一个地图传送门  22942/-3752/1023
		返回信息.地图ID = 10722;
		分段处理信息_ 上一张地图传送门;
		上一张地图传送门.属于分段 = 1;
		上一张地图传送门.坐标.x = 1888;
		上一张地图传送门.坐标.y = -3376;
		上一张地图传送门.坐标.z = 1025;
		上一张地图传送门.处理方式 = 0;
		返回信息.前往上一张地图传送门 = 上一张地图传送门;
		分段处理信息_ 下一张地图传送门;
		下一张地图传送门.属于分段 = 1;
		下一张地图传送门.坐标.x = 14103;
		下一张地图传送门.坐标.y = 22763;
		下一张地图传送门.坐标.z = 1702;
		下一张地图传送门.处理方式 = 0;
		返回信息.前往下一张地图传送门 = 下一张地图传送门;
	}
	if (当前地图ID == 10723)
	{
		//-336/857/503
		//下一个地图传送门  22942/-3752/1023
		返回信息.地图ID = 10723;
		分段处理信息_ 上一张地图传送门;
		上一张地图传送门.属于分段 = 1;
		上一张地图传送门.坐标.x = 1888;
		上一张地图传送门.坐标.y = -3376;
		上一张地图传送门.坐标.z = 1025;
		上一张地图传送门.处理方式 = 0;
		返回信息.前往上一张地图传送门 = 上一张地图传送门;
		分段处理信息_ 下一张地图传送门;
		下一张地图传送门.属于分段 = 1;
		下一张地图传送门.坐标.x = -4877;
		下一张地图传送门.坐标.y = 14996;
		下一张地图传送门.坐标.z = 3519;
		下一张地图传送门.处理方式 = 0;
		返回信息.前往下一张地图传送门 = 下一张地图传送门;
	}
	if (当前地图ID == 10401)
	{
		//-336/857/503
		//下一个地图传送门  22942/-3752/1023
		返回信息.地图ID = 10401;
		分段处理信息_ 上一张地图传送门;
		上一张地图传送门.属于分段 = 1;
		上一张地图传送门.坐标.x = 1888;
		上一张地图传送门.坐标.y = -3376;
		上一张地图传送门.坐标.z = 1025;
		上一张地图传送门.处理方式 = 0;
		返回信息.前往上一张地图传送门 = 上一张地图传送门;
		分段处理信息_ 下一张地图传送门;
		下一张地图传送门.属于分段 = 1;
		下一张地图传送门.坐标.x = 23793;
		下一张地图传送门.坐标.y = 13895;
		下一张地图传送门.坐标.z = 1548;
		下一张地图传送门.处理方式 = 0;
		返回信息.前往下一张地图传送门 = 下一张地图传送门;
	}
	if (当前地图ID == 10422)
	{
		//-336/857/503
		//下一个地图传送门  22942/-3752/1023
		返回信息.地图ID = 10422;
		分段处理信息_ 上一张地图传送门;
		上一张地图传送门.属于分段 = 1;
		上一张地图传送门.坐标.x = 1501;
		上一张地图传送门.坐标.y = 9164;
		上一张地图传送门.坐标.z = 2305;
		上一张地图传送门.处理方式 = 0;
		返回信息.前往上一张地图传送门 = 上一张地图传送门;
		分段处理信息_ 下一张地图传送门;
		下一张地图传送门.属于分段 = 1;
		下一张地图传送门.坐标.x = 29331;
		下一张地图传送门.坐标.y = 13777;
		下一张地图传送门.坐标.z = 1536;
		下一张地图传送门.处理方式 = 0;
		返回信息.前往下一张地图传送门 = 下一张地图传送门;
	}
	if (当前地图ID == 10423)
	{
		//-336/857/503
		//下一个地图传送门  22942/-3752/1023
		返回信息.地图ID = 10423;
		分段处理信息_ 上一张地图传送门;
		上一张地图传送门.属于分段 = 1;
		上一张地图传送门.坐标.x = -30677;
		上一张地图传送门.坐标.y = 14904;
		上一张地图传送门.坐标.z = 2562;
		上一张地图传送门.处理方式 = 0;
	}
	if (当前地图ID == 10424)
	{
		//-336/857/503
		//下一个地图传送门  22942/-3752/1023
		返回信息.地图ID = 10424;
		分段处理信息_ 上一张地图传送门;
		上一张地图传送门.属于分段 = 1;
		上一张地图传送门.坐标.x = -30677;
		上一张地图传送门.坐标.y = 14904;
		上一张地图传送门.坐标.z = 2562;
		上一张地图传送门.处理方式 = 0;
		分段处理信息_ 下一张地图传送门;
		下一张地图传送门.属于分段 = 1;
		下一张地图传送门.坐标.x = 12593;
		下一张地图传送门.坐标.y = 24826;
		下一张地图传送门.坐标.z = 0;
		下一张地图传送门.处理方式 = 0;
		返回信息.前往下一张地图传送门 = 下一张地图传送门;
	}
	//if (当前地图ID == 11111)
	//{
	//	//-336/857/503
	//	//下一个地图传送门  22942/-3752/1023
	//	返回信息.地图ID = 10424;
	//	分段处理信息_ 上一张地图传送门;
	//	上一张地图传送门.属于分段 = 1;
	//	上一张地图传送门.坐标.x = -30677;
	//	上一张地图传送门.坐标.y = 14904;
	//	上一张地图传送门.坐标.z = 2562;
	//	上一张地图传送门.处理方式 = 0;
	//	分段处理信息_ 下一张地图传送门;
	//	下一张地图传送门.属于分段 = 1;
	//	下一张地图传送门.坐标.x = 12593;
	//	下一张地图传送门.坐标.y = 24826;
	//	下一张地图传送门.坐标.z = 0;
	//	下一张地图传送门.处理方式 = 0;
	//	返回信息.前往下一张地图传送门 = 下一张地图传送门;
	//	//28368,9961,3075
	//}
	/*333 / -1098 / -512*/
	//19029,13488,221, 0x5153
	return 返回信息;
}

DWORD 判断角色当前分段(节点处理_ 参_节点信息)
{
	for (size_t i = 0; i < 参_节点信息.前往下一个分段组.GetCount(); i++)
	{
		分段处理信息_ 分段 = 参_节点信息.前往下一个分段组[i];
		if (地图::指定地点是否可到达_M(分段.坐标.x, 分段.坐标.y, 分段.坐标.z))
		{
			return 分段.属于分段;
		}
	}
	for (size_t i = 0; i < 参_节点信息.返回上一个分段组.GetCount(); i++)
	{
		分段处理信息_ 分段 = 参_节点信息.返回上一个分段组[i];
		if (地图::指定地点是否可到达_M(分段.坐标.x, 分段.坐标.y, 分段.坐标.z))
		{
			return 分段.属于分段;
		}
	}
	if (参_节点信息.前往上一张地图传送门.坐标.x != 0)
	{
		if (地图::指定地点是否可到达_M(参_节点信息.前往上一张地图传送门.坐标.x, 参_节点信息.前往上一张地图传送门.坐标.y, 参_节点信息.前往上一张地图传送门.坐标.z))
		{
			return 参_节点信息.前往上一张地图传送门.属于分段;
		}
	}
	if (参_节点信息.前往下一张地图传送门.坐标.x != 0)
	{
		if (地图::指定地点是否可到达_M(参_节点信息.前往下一张地图传送门.坐标.x, 参_节点信息.前往下一张地图传送门.坐标.y, 参_节点信息.前往下一张地图传送门.坐标.z))
		{
			return 参_节点信息.前往下一张地图传送门.属于分段;
		}
	}
	return 0;
}
分段处理信息_ 取出角色当前分段处理点(DWORD 角色分段, CArray<分段处理信息_, 分段处理信息_>& 分段组)
{
	分段处理信息_ temp;
	for (size_t i = 0; i < 分段组.GetCount(); i++)
	{
		分段处理信息_ 分段 = 分段组[i];
		if (角色分段 = 分段.属于分段)
		{
			return 分段;
		}
	}
	return temp;
}


int 功能::前往指定分段(节点处理_ 节点信息, DWORD 目标分段, 坐标_ 目标坐标, DWORD 操作 = 0)
{

	DWORD 角色分段 = 判断角色当前分段(节点信息);
	if (角色分段 == 0)
	{
		//坐标_ 角色坐标 = 本人::取坐标();
		return -1;
		//MyTrace(L"无法判断角色当前分段 当前角色信息:大陆ID: %d 地图ID %d 大地图名称:【%s】 小地图名称:【%s】 坐标:%0.3f,%0.3f,%0.3f", 地图::取当前大陆ID(), 地图::取地图ID(), 地图::取大地图名(), 地图::取小地图名(), 角色坐标.x, 角色坐标.y, 角色坐标.z);
	}
	if (角色分段 == 目标分段)
	{
		if (地图::指定地点是否可到达_M(目标坐标.x, 目标坐标.y, 目标坐标.z))
		{
			if (操作 == 2)
			{
				到指定地点按G(地图::取当前大陆ID(), 地图::取地图ID(), 目标坐标.x, 目标坐标.y, 目标坐标.z, 50);
			}
			else
			{
				功能::移动打怪(目标坐标.x, 目标坐标.y, 目标坐标.z, 0, 50);
			}

			return 1;
		}
		else
		{
			return -2;

		}
	}
	else
	{
		if (角色分段 < 目标分段)
		{
			MyTrace(L"分段 %d/%d 前往下一个分段", 角色分段, 目标分段);
			分段处理信息_ 目标分段 = 取出角色当前分段处理点(角色分段, 节点信息.前往下一个分段组);
			if (目标分段.属于分段 != 0)
			{
				if (目标分段.处理方式 == 2)//G
				{
					功能::到指定地点按G(地图::取当前大陆ID(), 地图::取地图ID(), 目标分段.坐标.x, 目标分段.坐标.y, 目标分段.坐标.z, 20);
					return 1;
				}
				if (目标分段.处理方式 == 3)//电梯
				{
					return 1;
					//功能::到指定地点按G(地图::取当前大陆ID(), 地图::取地图ID(), 目标分段.坐标.x, 目标分段.坐标.y, 目标分段.坐标.z, 20);
				}
			}
			else
			{
				return -3;

			}


		}
		else if (角色分段 > 目标分段)
		{
			MyTrace(L"分段 %d/%d 返回上一个分段", 角色分段, 目标分段);
			分段处理信息_ 目标分段 = 取出角色当前分段处理点(角色分段, 节点信息.返回上一个分段组);
			if (目标分段.属于分段 != 0)
			{
				if (目标分段.处理方式 == 2)//G
				{
					功能::到指定地点按G(地图::取当前大陆ID(), 地图::取地图ID(), 目标分段.坐标.x, 目标分段.坐标.y, 目标分段.坐标.z, 20);
					return 1;
				}
				if (目标分段.处理方式 == 3)//电梯
				{
					return 1;
					//功能::到指定地点按G(地图::取当前大陆ID(), 地图::取地图ID(), 目标分段.坐标.x, 目标分段.坐标.y, 目标分段.坐标.z, 20);
				}
			}
			else
			{
				return -4;
				//MyTrace(L"地图ID:%d 角色分段:%d 未取出前往下一个分段的信息", 地图::取地图ID(), 角色分段);
			}

		}

	}

	return 0;
}
void 前往下一个传送门(DWORD 目标地图ID)
{
	节点处理_ 节点信息;
	DWORD 当前地图ID = 地图::取地图ID();
	if (目标地图ID == 10801)
	{
		if (当前地图ID == 10815)
		{
			功能::到指定地点按G(14, 10815, 12405, 23555, 518, 50);
			return;
		}
	}
	if (目标地图ID == 10722)
	{
		if (当前地图ID == 10701)
		{
			功能::到指定地点按G(3, 10701, -6875, 1231, 553, 50);
			return;
		}
	}
	if (目标地图ID == 10424)
	{
		功能::到指定地点按G(4, 10401, 5254, 13877, 1548, 50);
		return;
	}
	if (目标地图ID == 10426)
	{
		功能::到指定地点按G(4, 10401, 13889, 24114, 1552, 50);
		return;
	}
	if (目标地图ID == 11102)
	{
		功能::到指定地点按G(18, 11111, 28368, 9961, 3075, 50);
		return;
	}
	if (目标地图ID == 11101)
	{
		功能::到指定地点按G(18, 11111, 28546, 22816, 2206, 50);
		return;
	}
	if (目标地图ID == 11113)
	{
		功能::到指定地点按G(18, 11101, 12196, 10094, 1613, 50);
		return;
	}
	if (目标地图ID == 11115)
	{
		功能::到指定地点按G(18, 11101, 10472, -2080, 799, 50);
		return;
	}
	节点信息 = 获取节点信息(当前地图ID);
	if (节点信息.地图ID == 0)
	{

		MyTrace(L"跨地图ID处理:获取地图ID [%d] 节点信息失败", 当前地图ID);
		return;
	}
	if (目标地图ID == 10804)
	{
		if (节点信息.前往下一张地图传送门.坐标.x != 0)
		{
			坐标_ 角色坐标 = 本人::取坐标();
			功能::寻路到指定传送门(节点信息.前往下一张地图传送门.坐标.x, 节点信息.前往下一张地图传送门.坐标.y, 节点信息.前往下一张地图传送门.坐标.z, 20251, 100);
			MyTrace(L"前往下一张地图传送点 %0.3f %0.3f %0.3f ", 节点信息.前往下一张地图传送门.坐标.x, 节点信息.前往下一张地图传送门.坐标.y, 节点信息.前往下一张地图传送门.坐标.z);

		}
		else
		{
			MyTrace(L"%d 获取 节点:前往下一张地图传送门 失败", 目标地图ID);
		}
	}

	if (当前地图ID < 目标地图ID)
	{

		if (节点信息.前往下一张地图传送门.坐标.x != 0)
		{
			坐标_ 角色坐标 = 本人::取坐标();
			功能::寻路到指定传送门(节点信息.前往下一张地图传送门.坐标.x, 节点信息.前往下一张地图传送门.坐标.y, 节点信息.前往下一张地图传送门.坐标.z, 20251, 100);
			MyTrace(L"前往下一张地图传送点 %0.3f %0.3f %0.3f ", 节点信息.前往下一张地图传送门.坐标.x, 节点信息.前往下一张地图传送门.坐标.y, 节点信息.前往下一张地图传送门.坐标.z);

		}
		else
		{
			MyTrace(L"%d 获取 节点:前往下一张地图传送门 失败", 目标地图ID);
		}
	}
	else
	{
		坐标_ 角色坐标 = 本人::取坐标();
		功能::寻路到指定传送门(节点信息.前往下一张地图传送门.坐标.x, 节点信息.前往下一张地图传送门.坐标.y, 节点信息.前往下一张地图传送门.坐标.z, 20251, 100);

		Sleep(500);
	}
}
void 功能::跨地图ID处理(DWORD 目标地图ID)
{
	vector<传送点信息_>vsk;
	节点处理_ 节点信息;
	DWORD 当前地图ID = 地图::取地图ID();
	if (当前地图ID == 10002)
	{
		功能::到指定地点按G(22, 10002, 13011, 130, 233, 50);
		return;
	}
	if (目标地图ID == 30703)
	{
		if (当前地图ID != 30703)
		{
			if (当前地图ID == 50032 || 当前地图ID == 50048)
			{
				本人::CALL_演奏乐谱(1);
				Sleep(10000);
				return;
			}
			if (!UI功能::是否在航海准备界面())
			{
				UI功能::准备出航();
				return;
			}
		}
		else
		{
			if (UI功能::是否在航海准备界面())
			{
				if (航海::自动选择最优战船())
				{
					本人::CALL_修理船只(航海::getCurVoyageShipResId());
					Sleep(1000);
					UI功能::航海出港();
				}
				return;
			}

		}
		return;
	}
	//if (目标地图ID == 10121 || 目标地图ID == 11102)//到贝隆
	//{
	//	if (当前地图ID != 30703)
	//	{
	//		if (当前地图ID == 50032 || 当前地图ID == 50048)//在各个岛屿 只能通过逃生乐曲出岛
	//		{
	//			本人::CALL_演奏乐谱(1);
	//			Sleep(10000);
	//			return;
	//		}
	//		if (!UI功能::是否在航海准备界面())
	//		{
	//			UI功能::准备出航();
	//			return;
	//		}
	//	}
	//	else
	//	{
	//		if (UI功能::是否在航海准备界面())
	//		{
	//			if (航海::自动选择最优战船())
	//			{
	//				本人::CALL_修理船只(航海::getCurVoyageShipResId());
	//				Sleep(1000);
	//				UI功能::航海出港();
	//			}
	//			return;
	//		}

	//	}
	//	return;
	//}

	地图::取目标地图传送点(目标地图ID, vsk);
	if (vsk.size() > 0)
	{
		if (vsk[0].Mapid != 目标地图ID)
		{
			if (vsk[0].Mapid != 地图::取地图ID())
			{
				if (功能::优先打怪(150))
				{
					MyTrace(L"跨地图传送传送至 Map %d  %s %d ", vsk[0].Mapid, vsk[0].cTeleportName, vsk[0].dTeleportId);
					地图::传送(vsk[0].dTeleportId);
					Sleep(10000);
				}

			}
			else
			{
				MyTrace(L"寻路前往下一个地图  Map %d  %s %d ", vsk[0].Mapid, vsk[0].cTeleportName, vsk[0].dTeleportId);
				前往下一个传送门(目标地图ID);
			}

		}
		else
		{
			if (功能::优先打怪(150))
			{
				MyTrace(L"传送至 Map %d  %s %d ", vsk[0].Mapid, vsk[0].cTeleportName, vsk[0].dTeleportId);
				地图::传送(vsk[vsk.size() - 1].dTeleportId);
				Sleep(10000);
			}
		}

	}
	else
	{
		/*if (本人::是否在走路())
		{
			MyTrace(L"目标地图ID：跨地图ID处理 角色在寻路中 无法判断分段:", 目标地图ID);
			Sleep(2000);
			return;
		}*/
		if (目标地图ID == 10722)
		{
			if (当前地图ID == 10701)
			{
				功能::到指定地点按G(3, 10701, -6875, 1231, 553, 50);
				return;
			}
		}
		if (目标地图ID == 10301)
		{
			if (当前地图ID == 10321)
			{
				功能::到指定地点按G(6, 10321, -28634, 27983, 10, 50);
				return;
			}
		}
		if (目标地图ID == 10322)
		{
			if (当前地图ID == 10301)
			{
				功能::到指定地点按G(6, 10301, 735.000, 5255.000, 775.000, 50);
				return;
			}
		}
		if (目标地图ID == 10323)
		{
			if (当前地图ID == 10322)
			{
				功能::到指定地点按G(6, 10322, 27787, 16580, 3114, 50);
				return;
			}
		}
		if (目标地图ID == 10324)
		{
			if (当前地图ID == 10322)
			{
				功能::到指定地点按G(6, 10322, 5813.000, 7425.000, 3190.000, 50);
				return;
			}
		}
		if (目标地图ID == 10325)
		{
			if (当前地图ID == 10323)
			{
				功能::到指定地点按G(6, 10323, 5043.21, 29317.2, 3787, 50);
				return;
			}
		}
		if (目标地图ID == 10424)
		{
			功能::到指定地点按G(4, 10401, 5254, 13877, 1548, 50);
			return;
		}
		节点信息 = 获取节点信息(当前地图ID);
		if (节点信息.地图ID == 0)
		{

			MyTrace(L"跨地图ID处理:获取地图ID [%d] 节点信息失败", 当前地图ID);
			return;
		}

		if (当前地图ID < 目标地图ID)
		{

			if (节点信息.前往下一张地图传送门.坐标.x != 0)
			{
				坐标_ 角色坐标 = 本人::取坐标();
				寻路到指定传送门(节点信息.前往下一张地图传送门.坐标.x, 节点信息.前往下一张地图传送门.坐标.y, 节点信息.前往下一张地图传送门.坐标.z, 20251, 100);
				MyTrace(L"前往下一张地图传送点 %0.3f %0.3f %0.3f ", 节点信息.前往下一张地图传送门.坐标.x, 节点信息.前往下一张地图传送门.坐标.y, 节点信息.前往下一张地图传送门.坐标.z);
				/*	int 返回值 = 前往指定分段(节点信息, 节点信息.前往下一张地图传送门.属于分段, 节点信息.前往下一张地图传送门.坐标, 节点信息.前往下一张地图传送门.处理方式);
					if (返回值 == 1)
					{
						MyTrace(L"前往指定分段[%d]下一个传送门信息:大陆ID: %d 地图ID %d 大地图名称:【%s】 小地图名称:【%s】 起始坐标:%0.3f,%0.3f,%0.3f =>>目标坐标:%0.3f,%0.3f,%0.3f", 节点信息.前往下一张地图传送门.属于分段, 地图::取当前大陆ID(), 地图::取地图ID(), 地图::取大地图名(), 地图::取小地图名(),
							角色坐标.x, 角色坐标.y, 角色坐标.z, 节点信息.前往下一张地图传送门.坐标.x, 节点信息.前往下一张地图传送门.坐标.y, 节点信息.前往下一张地图传送门.坐标.z);
					}
					else if (返回值 == -1)
					{
						MyTrace(L"前往下一张地图传送门：无法判断角色当前分段 当前角色信息:大陆ID: %d 地图ID %d 大地图名称:【%s】 小地图名称:【%s】 坐标:%0.3f,%0.3f,%0.3f", 地图::取当前大陆ID(), 地图::取地图ID(), 地图::取大地图名(), 地图::取小地图名(), 角色坐标.x, 角色坐标.y, 角色坐标.z);
					}
					else if (返回值 == -2)
					{
						MyTrace(L"前往下一张地图传送门：角色与传送门处于同一个分段,判断是否可到达失败 当前角色信息:大陆ID: %d 地图ID %d 大地图名称:【%s】 小地图名称:【%s】 坐标:%0.3f,%0.3f,%0.3f", 地图::取当前大陆ID(), 地图::取地图ID(), 地图::取大地图名(), 地图::取小地图名(), 角色坐标.x, 角色坐标.y, 角色坐标.z);
					}
					else if (返回值 == -3)
					{
						MyTrace(L"前往下一张地图传送门: 地图ID:%d 角色分段:%d 未取出前往下一个分段的信息", 地图::取地图ID(), 判断角色当前分段(节点信息));

					}
					else if (返回值 == -4)
					{
						MyTrace(L"前往下一张地图传送门：地图ID:%d 角色分段:%d 未取出前往上一个分段的信息", 地图::取地图ID(), 判断角色当前分段(节点信息));
					}
					else if (返回值 == 0)
					{
						MyTrace(L"前往下一张地图传送门：地图ID:%d 角色分段:%d 错误未知", 地图::取地图ID(), 判断角色当前分段(节点信息));
					}
					Sleep(500);*/
			}
			else
			{
				MyTrace(L"%d 获取 节点:前往下一张地图传送门 失败", 目标地图ID);
			}
		}
		else
		{
			坐标_ 角色坐标 = 本人::取坐标();
			寻路到指定传送门(节点信息.前往上一张地图传送门.坐标.x, 节点信息.前往上一张地图传送门.坐标.y, 节点信息.前往上一张地图传送门.坐标.z, 20251, 100);
			MyTrace(L"前往上一张地图传送点 %0.3f %0.3f %0.3f ", 节点信息.前往上一张地图传送门.坐标.x, 节点信息.前往上一张地图传送门.坐标.y, 节点信息.前往上一张地图传送门.坐标.z);
			/*int 返回值 = 前往指定分段(节点信息, 节点信息.前往上一张地图传送门.属于分段, 节点信息.前往上一张地图传送门.坐标, 节点信息.前往上一张地图传送门.处理方式);
			if (返回值 == 1)
			{
				MyTrace(L"前往指定分段[%d]上一个传送门信息:大陆ID: %d 地图ID %d 大地图名称:【%s】 小地图名称:【%s】 起始坐标:%0.3f,%0.3f,%0.3f =>>目标坐标:%0.3f,%0.3f,%0.3f", 节点信息.前往下一张地图传送门.属于分段, 地图::取当前大陆ID(), 地图::取地图ID(), 地图::取大地图名(), 地图::取小地图名(),
					角色坐标.x, 角色坐标.y, 角色坐标.z, 节点信息.前往上一张地图传送门.坐标.x, 节点信息.前往上一张地图传送门.坐标.y, 节点信息.前往上一张地图传送门.坐标.z);
			}
			else if (返回值 == -1)
			{
				MyTrace(L"返回上一张地图传送门：无法判断角色当前分段 当前角色信息:大陆ID: %d 地图ID %d 大地图名称:【%s】 小地图名称:【%s】 坐标:%0.3f,%0.3f,%0.3f", 地图::取当前大陆ID(), 地图::取地图ID(), 地图::取大地图名(), 地图::取小地图名(), 角色坐标.x, 角色坐标.y, 角色坐标.z);
			}
			else if (返回值 == -2)
			{
				MyTrace(L"前往下一张地图传送门：角色与传送门处于同一个分段,判断是否可到达失败 当前角色信息:大陆ID: %d 地图ID %d 大地图名称:【%s】 小地图名称:【%s】 坐标:%0.3f,%0.3f,%0.3f", 地图::取当前大陆ID(), 地图::取地图ID(), 地图::取大地图名(), 地图::取小地图名(), 角色坐标.x, 角色坐标.y, 角色坐标.z);
			}
			else if (返回值 == -3)
			{
				MyTrace(L"返回上一张地图传送门: 地图ID:%d 角色分段:%d 未取出前往下一个分段的信息", 地图::取地图ID(), 判断角色当前分段(节点信息));

			}
			else if (返回值 == -4)
			{
				MyTrace(L"返回上一张地图传送门: 地图ID:%d 角色分段:%d 未取出前往上一个分段的信息", 地图::取地图ID(), 判断角色当前分段(节点信息));
			}
			else if (返回值 == 0)
			{
				MyTrace(L"前往下一张地图传送门：地图ID:%d 角色分段:%d 错误未知", 地图::取地图ID(), 判断角色当前分段(节点信息));
			}*/
			Sleep(500);
		}
	}

	//if (目标地图ID == 10211)//罗格尔
	//{
	//	if()
	//}
}
//交任务2 对话后有分支选项
void 功能::到指定地点找NPC交任务2(DWORD 大陆ID, DWORD 地图ID, float x, float y, float z, DWORD NPCResId, DWORD 任务ID, DWORD 奖励, int 对话范围, int 对话分支)
{
	if (UI功能::是否在交接任务界面())
	{
		if (奖励 != -1)
		{
			任务::CALL_交任务(任务ID, -1);
			Sleep(500);
			环境::CALL_退出NPC();
		}
		else
		{
			UI功能::内存按键(DWORD('G'));
			Sleep(500);
		}


	}
	else
	{
		if (环境::是否在和NPC对话())
		{

			for (size_t i = 0; i < 10; i++)
			{
				UI功能::内存按键(DWORD('G'));
				Sleep(100);
			}
			if (UI功能::是否在交接任务界面())
			{
				return;
			}
			if (环境::是否在和NPC对话())
			{
				vector<CString>对话组;
				UI功能::getNpcTalkSelectList(对话组);
				MyTrace(L"对话选项数量 %d", 对话组.size());
				if (对话组.size() > 1)
				{
					环境::CALL_NPC对话分支(对话分支);
				}
				else
				{
					if (对话组.size() == 1)
					{
						环境::CALL_NPC对话分支(0);
					}

				}

			}

		}
		else
		{
			功能::到指定地点打开NPC(大陆ID, 地图ID, x, y, z, 对话范围, NPCResId);
			//功能::到指定地点按G(大陆ID, 地图ID, x, y, z, 对话范围);
		}
	}
}
//交任务3直接交任务
void 功能::到指定地点找NPC交任务3(DWORD 大陆ID, DWORD 地图ID, float x, float y, float z, DWORD NPCResId, DWORD 任务ID, DWORD 奖励, int 对话范围, int 任务阶段)
{
	if (UI功能::是否在交接任务界面())
	{
		MyTrace(L"交接页面");
		if (奖励 != -1)
		{
			任务::CALL_交任务(任务ID, 奖励);
			Sleep(500);
			环境::CALL_退出NPC();
		}
		else
		{
			UI功能::内存按键(DWORD('G'));
			Sleep(500);
		}


	}
	else
	{
		DWORD 返回值 = 环境::是否在和NPC对话();
		MyTrace(L"%s  是否在对话 %d ,", UTF82WCS(__FUNCDNAME__), 返回值);
		if (环境::是否在和NPC对话())
		{
			//MyTrace(L"移动打怪");
			//移动打怪(x, y, z, 0, 100, 100);
			if (任务阶段 != 0)
			{
				if (NPCResId)
				{
					MyTrace(L"%d / %d", NPCResId, 环境::读取当前对话NPC());
					/*if (NPCResId != 环境::读取当前对话NPC())
					{
						环境::CALL_退出NPC();
						return;
					}*/
					MyTrace(L"开始阶段对话");
					int sendarg = 任务::getNpcTaklEndSendArg(NPCResId, 任务ID, 任务阶段);
					if (sendarg)
					{
						MyTrace(L"阶段完成%d", sendarg);

						任务::Fun_阶段任务完成CALL(sendarg);
						Sleep(1000);
						环境::CALL_退出NPC();
						return;
					}
				}
			}


			for (size_t i = 0; i < 5; i++)
			{
				UI功能::内存按键(DWORD('G'));
				Sleep(100);
			}
			if (UI功能::是否在交接任务界面())
			{
				return;
			}
			if (环境::是否在和NPC对话())
			{
				vector<CString>对话组;
				UI功能::getNpcTalkSelectList(对话组);
				MyTrace(L"存在对话数量 %d", 对话组.size());
				if (对话组.size() > 1)
				{
					MyTrace(L"选择对话 %s", 对话组[1]);
					环境::CALL_NPC对话分支(1);
				}
				else
				{
					if (对话组.size() == 1)
					{
						MyTrace(L"选择对话 %s", 对话组[0]);
						环境::CALL_NPC对话分支(0);
					}

				}

			}

		}
		else
		{
			功能::到指定地点打开NPC(大陆ID, 地图ID, x, y, z, 对话范围, NPCResId);
			//功能::到指定地点按G(大陆ID, 地图ID, x, y, z, 对话范围);
		}
	}
}


void 功能::诞生石任务(DWORD 地图ID, float x, float y, float z, DWORD NPCResId, int 对话范围)//
{
	if (环境::是否在和NPC对话())
	{
		if (UI功能::指定UI是否显示(L"root1.arkui.windowCanvas.marbleWnd"))
		{
			诞生石::诞生石强化();
		}
		else
		{
			MyTrace(L"加工界面未打开");
			Sleep(5000);
		}

	}
	else
	{
		功能::到指定地点打开NPC(0, 地图ID, x, y, z, 对话范围, NPCResId);
		//功能::到指定地点按G(大陆ID, 地图ID, x, y, z, 对话范围);
	}
}
void 功能::到指定地点找NPC修理装备(DWORD 大陆ID, DWORD 地图ID, float x, float y, float z, DWORD 对话范围, DWORD NPCResId)//支线用
{
	if (环境::是否在和NPC对话())
	{
		背包::维修装备(1);
		Sleep(1000);
		环境::CALL_退出NPC();
	}
	else
	{
		功能::到指定地点打开NPC(大陆ID, 地图ID, x, y, z, 对话范围, NPCResId);
		//功能::到指定地点按G(大陆ID, 地图ID, x, y, z, 对话范围);
	}

}
void 功能::到指定地点找NPC交任务(DWORD 大陆ID, DWORD 地图ID, float x, float y, float z, CString NpcName, DWORD 任务ID, DWORD 奖励, int 对话范围, int 地图分段)
{
	if (UI功能::是否在交接任务界面())
	{
		任务::CALL_交任务(任务ID, 奖励);
		Sleep(500);
		环境::CALL_退出NPC();
	}
	else
	{
		if (环境::是否在和NPC对话())
		{
			UI功能::内存按键(DWORD('G'));
		}
		else
		{

			功能::到指定地点按G(大陆ID, 地图ID, x, y, z, 对话范围);
		}
	}
}
void 功能::到指定地点找NPC接任务(DWORD 大陆ID, DWORD 地图ID, float x, float y, float z, CString NpcName, DWORD 任务ID, int 对话范围, int 地图分段)//支线用
{
	if (环境::是否在和NPC对话())
	{
		if (任务ID != 0)
		{
			任务::CALL_接任务(任务ID);
			Sleep(500);
			环境::CALL_退出NPC();
		}
		else
		{
			for (size_t i = 0; i < 10; i++)
			{
				UI功能::内存按键(DWORD('G'));
				Sleep(200);
			}
		}
	}
	else
	{
		//功能::到指定地点打开NPC(大陆ID, 地图ID, x, y, z, 对话范围, NPCResId);
		功能::到指定地点按G(大陆ID, 地图ID, x, y, z, 对话范围);
	}

}
void 功能::到指定地点找NPC接任务2(DWORD 大陆ID, DWORD 地图ID, float x, float y, float z, DWORD NPCResId, DWORD 任务ID, int 对话范围, int 地图分段)//支线用
{
	if (环境::是否在和NPC对话())
	{
		if (任务ID != 0)
		{
			MyTrace(L"接任务");
			任务::CALL_接任务(任务ID);
			Sleep(500);
			环境::CALL_退出NPC();
		}
		else
		{
			MyTrace(L"GGGGGGG");
			for (size_t i = 0; i < 10; i++)
			{
				UI功能::内存按键(DWORD('G'));
				Sleep(200);
			}
		}
	}
	else
	{
		MyTrace(L"到指定地点打开NPC");
		功能::到指定地点打开NPC(大陆ID, 地图ID, x, y, z, 对话范围, NPCResId);
		//功能::到指定地点按G(大陆ID, 地图ID, x, y, z, 对话范围);
	}

}
void 功能::到指定地点找NPC买物品(DWORD 大陆ID, DWORD 地图ID, float x, float y, float z, DWORD NPCResId, int 对话范围, DWORD itemResID, DWORD 数量)
{

	if (环境::是否在和NPC对话())
	{
		vector<Inventoryinfo_>vsk;
		NPC商店::get_ShopItemList(vsk);
		for (size_t i = 0; i < vsk.size(); i++)
		{
			//MyTrace(L"Item Name %s Item ResId", vsk[i].ItemName, vsk[i].ItemResId);
			if (itemResID == vsk[i].ItemResId)
			{
				NPC商店::Fun_ShopBuyAddItem(vsk[i].dindex, 数量);
				Sleep(1000);
				NPC商店::Fub_ShopBuyItemClick();
				break;
			}
		}
		环境::CALL_退出NPC();
	}
	else
	{
		功能::到指定地点打开NPC(大陆ID, 地图ID, x, y, z, 对话范围, NPCResId);
		Sleep(2000);
		//功能::到指定地点按G(大陆ID, 地图ID, x, y, z, 对话范围);
	}

}
void 功能::到指定地点对怪物使用F5(DWORD 大陆ID, DWORD 地图ID, float x, float y, float z, int 范围, DWORD 怪物ID)
{

	if (功能::到指定地点(大陆ID, 地图ID, x, y, z, 范围))
	{
		objInfo_ 蝗虫 = 环境::取指定对象信息(怪物ID);
		if (蝗虫.dCurHp > 0)
		{
			if (蝗虫.fDis > 500)
			{
				地图::本地图寻路(蝗虫.坐标.x, 蝗虫.坐标.y, 蝗虫.坐标.z, 0);
			}
			else
			{
				技能::屏蔽鼠标();
				技能::写怪物坐标到鼠标(蝗虫.坐标);
				UI功能::内存按键(VK_F5);
				Sleep(500);
				UI功能::内存按键(VK_F5);
				技能::解除屏蔽鼠标();
			}
		}


	}

}
void 功能::到指定地点使用指定按键(DWORD 大陆ID, DWORD 地图ID, float x, float y, float z, int 范围, DWORD 按键)
{

	if (功能::到指定地点(大陆ID, 地图ID, x, y, z, 范围))
	{


		UI功能::内存按键(按键);
		Sleep(500);

	}

}
void 功能::到指定地点使用表情(DWORD 大陆ID, DWORD 地图ID, float x, float y, float z, int 范围, DWORD 表情ID)
{

	if (功能::到指定地点(大陆ID, 地图ID, x, y, z, 范围))
	{
		本人::CALL_做社交动作(表情ID);
		Sleep(2000);
	}

}
void 功能::自动主线和NPC对话(int 对话范围, int 地图分段)
{
	if (对话范围 == 0)
	{
		对话范围 = 50;
	}
	QuestInfo_ 主线任务 = 任务::取出主线任务();
	坐标_ 任务坐标 = 任务::CALL_取任务坐标(主线任务.dQuestId, 主线任务.objBase, 主线任务.dResAddr);

	if (环境::是否在和NPC对话())
	{
		for (size_t i = 0; i < 10; i++)
		{
			UI功能::内存按键(DWORD('G'));
			Sleep(200);
		}
		//环境::CALL_退出NPC();
		return;
	}
	else
	{
		功能::到指定地点按G(任务坐标.大陆ID, 任务坐标.地图ID, 任务坐标.x, 任务坐标.y, 任务坐标.z, 对话范围);

	}
}
bool 功能::范围内是否警备兵(float x, float y, float z, int 范围, DWORD 怪物ID)
{
	坐标_ 本人坐标 = 本人::取坐标();
	vector<objInfo_>环境对象数组;
	环境::遍历全部环境对象(环境对象数组);
	for (size_t i = 0; i < 环境对象数组.size(); i++)
	{
		if (环境对象数组[i].dResId == 怪物ID)
		{
			int 距离 = 距离计算3(x, y, z, 环境对象数组[i].坐标.x, 环境对象数组[i].坐标.y, 环境对象数组[i].坐标.z);
			MyTrace(L"警备兵距离 %d ", 距离);
			if (距离 < 范围)
			{
				MyTrace(L"距离 %d 全对象 0x%I64X Type: %d, 名称:%s modid:%d resid:%d 是否隐藏:%d 是否敌人:%d HP:%d/%d 击打道具是否死亡 %d dResShow %d dResDead %d 坐标 %0.3f,%0.3f,%0.3f",
					距离计算(本人坐标.x, 本人坐标.y, 本人坐标.z, 环境对象数组[i].坐标.x, 环境对象数组[i].坐标.y, 环境对象数组[i].坐标.z), 环境对象数组[i].objBase, 环境对象数组[i].dType, 环境对象数组[i].wName, 环境对象数组[i].ModId, 环境对象数组[i].dResId, 环境对象数组[i].IsHide, 环境对象数组[i].IsEnemy, 环境对象数组[i].dCurHp, 环境对象数组[i].dMaxHp, 环境::击打道具是否死亡(环境对象数组[i].objBase), 环境对象数组[i].dResShow, 环境对象数组[i].dIsDead, 环境对象数组[i].坐标.x, 环境对象数组[i].坐标.y, 环境对象数组[i].坐标.z);
				return true;
			}
			//if (距离计算3(本人坐标.x, 本人坐标.y, 本人坐标.z, 环境对象数组[i].坐标.x, 环境对象数组[i].坐标.y, 环境对象数组[i].坐标.z) < 范围)
			//{
			//	return true;
			//}
		}
	}
	return false;
}

int 功能::返回表情编号(CString 表情)
{
	if (表情.Find(L"对话") != -1)
	{
		return 0xF231;
	}
	if (表情.Find(L"誓言") != -1)
	{
		return 0xF265;
	}
	if (表情.Find(L"敬意") != -1)
	{
		return 0xF238;
	}
	if (表情.Find(L"礼貌") != -1)
	{
		return 0xF23A;
	}
	if (表情.Find(L"投降") != -1)
	{
		return 0xF23F;
	}
	if (表情.Find(L"干杯") != -1)
	{
		return 0xF250;
	}
	if (表情.Find(L"祈祷") != -1)
	{
		return 0xF252;
	}
	if (表情.Find(L"质问") != -1)
	{
		return 0xF25B;
	}
	if (表情.Find(L"问候") != -1)
	{
		return 0xF232;
	}
	if (表情.Find(L"谢罪") != -1)
	{
		return 0xF234;
	}
	if (表情.Find(L"悲伤") != -1)
	{
		return 0xF236;
	}
	if (表情.Find(L"肯定") != -1)
	{
		return 0xF237;
	}
	if (表情.Find(L"舞蹈") != -1)
	{
		return 0xF239;
	}
	if (表情.Find(L"疑问") != -1)
	{
		return 0xF23B;
	}
	if (表情.Find(L"否定") != -1)
	{
		return 0xF23D;
	}
	if (表情.Find(L"鼓励") != -1)
	{
		return 0xF23E;
	}
	if (表情.Find(L"笑声") != -1)
	{
		return 0xF242;
	}
	if (表情.Find(L"愤怒") != -1)
	{
		return 0xF243;
	}
	if (表情.Find(L"掌声") != -1)
	{
		return 0xF246;
	}
	if (表情.Find(L"失望") != -1)
	{
		return 0xF248;
	}
	if (表情.Find(L"欢呼") != -1)
	{
		return 0xF24A;
	}
	if (表情.Find(L"惊讶") != -1)
	{
		return 0xF24B;
	}
	if (表情.Find(L"坐下") != -1)
	{
		return 0xF256;
	}
	if (表情.Find(L"啦嘞唻") != -1)
	{
		return 0xF25E;
	}
	if (表情.Find(L"吻") != -1)
	{
		return 0xF251;
	}
	return 0;
}
objInfo_ 取范围内怪物(vector<objInfo_>& 怪物数组, int 范围)
{
	objInfo_ temp;
	if (范围 == 0)
	{
		范围 = 1500;
	}
	if (怪物数组.size() > 0)
	{
		if (优先打怪ID.size() != 0)
		{
			for (size_t i = 0; i < 怪物数组.size(); i++)
			{
				if (ID是否已存在(怪物数组[i].dResId, 优先打怪ID) && 怪物数组[i].fDis <= 范围)
				{
					return 怪物数组[0];
				}
			}
		}

		if (怪物数组[0].fDis <= 范围)
		{
			return 怪物数组[0];
		}


	}
	return temp;
}
objInfo_ 取指定坐标范围内怪物(vector<objInfo_>& 怪物数组, float x, float y, float z, int 范围, int 距离自身范围)
{
	objInfo_ temp;
	if (范围 == 0)
	{
		范围 = 1500;
	}
	if (怪物数组.size() > 0)
	{
		MyTrace(L"优先怪物数量 %d", 优先打怪ID.size());
		if (优先打怪ID.size() != 0)
		{
			for (size_t i = 0; i < 怪物数组.size(); i++)
			{
				//MyTrace(L"信息::遍历 优先  怪物 %s   坐标 %0.3f, %0.3f, %0.3f", 怪物数组[i].wName, 怪物数组[i].坐标.x, 怪物数组[i].坐标.y, 怪物数组[i].坐标.z);
				if (ID是否已存在(怪物数组[i].dResId, 优先打怪ID))
				{
					if (怪物数组[i].fDis <= 距离自身范围)
					{
						if (地图::指定地点是否可到达_M(怪物数组[i].坐标.x, 怪物数组[i].坐标.y, 怪物数组[i].坐标.z))
						{
							MyTrace(L"怪物%s可达   坐标 %d,%d,%d", 怪物数组[i].wName, 怪物数组[i].坐标.x, 怪物数组[i].坐标.y, 怪物数组[i].坐标.z);
							return 怪物数组[i];
						}
					}
				}
			}
		}
		if (怪物数组[0].fDis <= 距离自身范围)
		{

			if (地图::指定地点是否可到达_M(怪物数组[0].坐标.x, 怪物数组[0].坐标.y, 怪物数组[0].坐标.z))
			{
				MyTrace(L"怪物%s可达   坐标 %d,%d,%d", 怪物数组[0].wName, 怪物数组[0].坐标.x, 怪物数组[0].坐标.y, 怪物数组[0].坐标.z);
				return 怪物数组[0];
			}
		}
		if (!本人::是否在走路2())
		{
			if (优先打怪ID.size() != 0)
			{
				for (size_t i = 0; i < 怪物数组.size(); i++)
				{
					//MyTrace(L"信息::遍历 优先怪物1 %s   坐标 坐标 %0.3f, %0.3f, %0.3f", 怪物数组[i].wName, 怪物数组[i].坐标.x, 怪物数组[i].坐标.y, 怪物数组[i].坐标.z);
					if (ID是否已存在(怪物数组[i].dResId, 优先打怪ID) && 距离计算(x, y, z, 怪物数组[i].坐标.x, 怪物数组[i].坐标.y, 怪物数组[i].坐标.z) <= 范围)
					{
						if (地图::指定地点是否可到达_M(怪物数组[i].坐标.x, 怪物数组[i].坐标.y, 怪物数组[i].坐标.z))
						{
							MyTrace(L"怪物%s可达   坐标 %d,%d,%d", 怪物数组[i].wName, 怪物数组[i].坐标.x, 怪物数组[i].坐标.y, 怪物数组[i].坐标.z);
							return 怪物数组[i];
						}
						else
						{
							MyTrace(L"******怪物%s不可达   坐标 %d,%d,%d", 怪物数组[i].wName, 怪物数组[i].坐标.x, 怪物数组[i].坐标.y, 怪物数组[i].坐标.z);
						}
					}
				}
			}
			for (size_t i = 0; i < 怪物数组.size(); i++)
			{
				if (距离计算(x, y, z, 怪物数组[i].坐标.x, 怪物数组[i].坐标.y, 怪物数组[i].坐标.z) <= 范围)
				{
					MyTrace(L"信息::遍历 怪物2 %s   坐标  %0.3f, %0.3f, %0.3f  距离 %d", 怪物数组[i].wName, 怪物数组[i].坐标.x, 怪物数组[i].坐标.y, 怪物数组[i].坐标.z, GetDis(怪物数组[i].坐标.x, 怪物数组[i].坐标.y, 怪物数组[i].坐标.z));

					if (地图::指定地点是否可到达_M(怪物数组[i].坐标.x, 怪物数组[i].坐标.y, 怪物数组[i].坐标.z))
					{
						return 怪物数组[i];
					}
				}
			}
		}
	}
	return temp;
}
objInfo_ 取指定坐标范围内NPC怪物(vector<objInfo_>& 怪物数组, float x, float y, float z, int 范围, int 距离自身范围)
{
	objInfo_ temp;
	if (范围 == 0)
	{
		范围 = 1500;
	}
	if (怪物数组.size() > 0)
	{
		for (size_t i = 0; i < 怪物数组.size(); i++)
		{
			if (怪物数组[i].IsEnemy == 1)
			{
				return 怪物数组[i];
			}
		}
	}
	return temp;
}
objInfo_ 取范围内击打道具(vector<objInfo_>& 怪物数组, float x, float y, float z, int 范围, int 自身范围)
{
	objInfo_ temp;
	if (范围 == 0)
	{
		范围 = 1500;
	}
	if (怪物数组.size() > 0)
	{

		/*if (优先打怪ID.size() != 0)
		{
			for (size_t i = 0; i < 怪物数组.size(); i++)
			{
				if (ID是否已存在(怪物数组[i].dResId, 优先打怪ID) && 怪物数组[i].fDis <= 范围)
				{
					return 怪物数组[0];
				}
			}
		}
		else
		{*/
		if (怪物数组[0].fDis <= 自身范围)
		{
			return 怪物数组[0];
		}
		if (!本人::是否在走路2())
		{
			if (优先打怪ID.size() != 0)
			{
				for (size_t i = 0; i < 怪物数组.size(); i++)
				{
					if (怪物数组[i].fDis > 3000)
					{
						continue;
					}
					if (ID是否已存在(怪物数组[i].dResId, 优先打怪ID) && 怪物数组[i].fDis <= 自身范围)
					{
						//if (地图::指定地点是否可到达_M(怪物数组[i].坐标.x, 怪物数组[i].坐标.y, 怪物数组[i].坐标.z))
						{
							return 怪物数组[i];
						}



					}
				}
			}
			for (size_t i = 0; i < 怪物数组.size(); i++)
			{
				if (怪物数组[i].fDis > 3000)
				{
					continue;
				}
				if (距离计算(x, y, z, 怪物数组[i].坐标.x, 怪物数组[i].坐标.y, 怪物数组[i].坐标.z) <= 范围)
				{
					if (地图::指定地点是否可到达_M(怪物数组[i].坐标.x, 怪物数组[i].坐标.y, 怪物数组[i].坐标.z))
					{
						return 怪物数组[i];
					}


				}
			}
		}

		//}

	}
	return temp;
}
objInfo_ 取范围内拾取物品(vector<objInfo_>& 怪物数组, int 范围)
{
	objInfo_ temp;
	if (范围 == 0)
	{
		范围 = 1500;
	}
	if (怪物数组.size() > 0)
	{
		/*if (优先打怪ID.size() != 0)
		{
			for (size_t i = 0; i < 怪物数组.size(); i++)
			{
				if (ID是否已存在(怪物数组[i].dResId, 优先打怪ID) && 怪物数组[i].fDis <= 范围)
				{
					return 怪物数组[0];
				}
			}
		}
		else
		{*/
		for (size_t i = 0; i < 怪物数组.size(); i++)
		{
			if (怪物数组[i].fDis <= 范围)
			{
				if (地图::指定地点是否可到达_M(怪物数组[i].坐标.x, 怪物数组[i].坐标.y, 怪物数组[i].坐标.z))
				{
					return 怪物数组[i];
				}


			}
		}
		/*if (怪物数组[0].fDis <= 范围)
		{
			if (地图::指定地点是否可到达_M(怪物数组[i].坐标.x, 怪物数组[i].坐标.y, 怪物数组[i].坐标.z))
			{
			return 怪物数组[0];

		}*/
		//}

	}
	return temp;
}
void 功能::打怪程序(INT64 怪物obj)
{
	clock_t 打怪时间 = 取启动时间();
	while (取启动时间() - 打怪时间 <= 1 * 60 * 1000)
	{
		objInfo_ 怪物信息 = 环境::getActorInfo(怪物obj);
		if (怪物信息.dType == 3 && 怪物信息.IsEnemy == 1)
		{
			if (怪物信息.dIsDead == 0)
			{
				MyTrace(L"CanAttack %d 攻击怪物 %s %d/%d %0.3f, %0.3f, %0.3f 距离%0.3f", 怪物信息.dCanAttack, 怪物信息.wName, 怪物信息.dCurHp, 怪物信息.dMaxHp, 怪物信息.坐标.x, 怪物信息.坐标.y, 怪物信息.坐标.z, 怪物信息.fDis);
				技能::技能释放2(怪物信息.坐标);
			}
			else
			{
				MyTrace(L"%s 怪物已死亡 %0.3f, %0.3f, %0.3f", 怪物信息.wName, 怪物信息.坐标.x, 怪物信息.坐标.y, 怪物信息.坐标.z);
				break;
			}
		}
		if (怪物信息.dResId == 0x22F74 || 怪物信息.dResId == 0x22F7E)
		{
			if (怪物信息.dCurHp <= 180)
			{
				MyTrace(L"%s 怪物已死亡 %0.3f, %0.3f, %0.3f", 怪物信息.wName, 怪物信息.坐标.x, 怪物信息.坐标.y, 怪物信息.坐标.z);
				break;
			}
		}
		if (怪物信息.dResId == 0x2A106)
		{
			if (怪物信息.dObjId != 0)
			{
				MyTrace(L"CanAttack %d 攻击怪物 %s %d/%d %0.3f, %0.3f, %0.3f 距离%0.3f", 怪物信息.dCanAttack, 怪物信息.wName, 怪物信息.dCurHp, 怪物信息.dMaxHp, 怪物信息.坐标.x, 怪物信息.坐标.y, 怪物信息.坐标.z, 怪物信息.fDis);
				技能::技能释放2(怪物信息.坐标);
			}
			else
			{
				MyTrace(L"%s 怪物已死亡 %0.3f, %0.3f, %0.3f", 怪物信息.wName, 怪物信息.坐标.x, 怪物信息.坐标.y, 怪物信息.坐标.z);
				break;
			}

		}
		else
		{
			if (怪物信息.fDis >= 500)
			{
				MyTrace(L"%s 怪物超出攻击距离跳出 %0.3f, %0.3f, %0.3f", 怪物信息.wName, 怪物信息.坐标.x, 怪物信息.坐标.y, 怪物信息.坐标.z);
				break;
			}
			if (怪物信息.dCurHp <= 0)
			{
				MyTrace(L"%s 怪物已死亡 %0.3f, %0.3f, %0.3f", 怪物信息.wName, 怪物信息.坐标.x, 怪物信息.坐标.y, 怪物信息.坐标.z);
				break;
			}
			else
			{
				MyTrace(L"CanAttack %d 攻击怪物 %s %d/%d %0.3f, %0.3f, %0.3f 距离%0.3f", 怪物信息.dCanAttack, 怪物信息.wName, 怪物信息.dCurHp, 怪物信息.dMaxHp, 怪物信息.坐标.x, 怪物信息.坐标.y, 怪物信息.坐标.z, 怪物信息.fDis);
				技能::技能释放2(怪物信息.坐标);
			}
		}

		Sleep(300);
	}
}
void 功能::打怪程序2(INT64 怪物obj, 坐标_ 固定坐标, objInfo_ 参_开关信息)
{
	clock_t 打怪时间 = 取启动时间();
	while (取启动时间() - 打怪时间 <= 1 * 60 * 1000)
	{
		objInfo_ 怪物信息 = 环境::getActorInfo(怪物obj);
		objInfo_ 开关信息;
		if (参_开关信息.dResId != 0 && 参_开关信息.dResId != 1)
		{
			开关信息 = 环境::getActorInfo(参_开关信息.objBase);
		}

		怪物信息.坐标 = 固定坐标;
		/*if (怪物信息.fDis >= 500)
		{
			MyTrace(L"%s 怪物超出攻击距离跳出 %0.3f, %0.3f, %0.3f", 怪物信息.wName, 怪物信息.坐标.x, 怪物信息.坐标.y, 怪物信息.坐标.z);
			break;
		}*/
		if (参_开关信息.dResId == 0)
		{
			if (怪物信息.dCurHp <= 0)
			{
				MyTrace(L"%s 怪物已死亡 %0.3f, %0.3f, %0.3f", 怪物信息.wName, 怪物信息.坐标.x, 怪物信息.坐标.y, 怪物信息.坐标.z);
				break;
			}
		}
		if (参_开关信息.dResId != 0)
		{
			if (参_开关信息.dResId != 1)
			{
				if (开关信息.dResShow == 1)
				{
					MyTrace(L"%s 怪物已死亡 %0.3f, %0.3f, %0.3f", 怪物信息.wName, 怪物信息.坐标.x, 怪物信息.坐标.y, 怪物信息.坐标.z);
					break;
				}
			}
			else
			{
				if (怪物信息.dIsDead == 1)
				{
					MyTrace(L"%s 怪物已死亡 %0.3f, %0.3f, %0.3f", 怪物信息.wName, 怪物信息.坐标.x, 怪物信息.坐标.y, 怪物信息.坐标.z);
					break;
				}
			}

		}
		if (本人::取角色信息().当前动作 == 12)
		{
			UI功能::内存按键(VK_SPACE);
		}
		MyTrace(L"CanAttack %d 攻击怪物 %s %d/%d %0.3f, %0.3f, %0.3f 距离%0.3f", 怪物信息.dCanAttack, 怪物信息.wName, 怪物信息.dCurHp, 怪物信息.dMaxHp, 怪物信息.坐标.x, 怪物信息.坐标.y, 怪物信息.坐标.z, 怪物信息.fDis);
		技能::技能释放2(怪物信息.坐标);
		Sleep(100);
	}
}
void 功能::破坏击打道具程序(INT64 怪物obj, DWORD dResId)
{
	clock_t 打怪时间 = 取启动时间();
	while (取启动时间() - 打怪时间 <= 0.5 * 60 * 1000)
	{
		objInfo_ 击打道具信息 = 环境::getActorInfo(怪物obj);
		MyTrace(L"击打道具信息 0x%I64X,%d ", 击打道具信息.objBase, 击打道具信息.dResId);
		if (击打道具信息.dResId == dResId)
		{
			if (击打道具信息.dType == 7)
			{
				//if (环境::判断击打道具(怪物obj))
				//{
				if (环境::击打道具是否死亡(击打道具信息.objBase) || 击打道具信息.dResShow == 0 || 击打道具信息.dIsDead == 0) //|| 击打道具信息.dPortalOpen == 2 83BF??????????0F85????????0FB687????????3C??0F84????????3C??0F84????????33F63C??75??0FB687????????2C??A8??
				{
					MyTrace(L"0x%I64x 击打道具已死亡 %0.3f, %0.3f, %0.3f", 击打道具信息.objBase, 击打道具信息.坐标.x, 击打道具信息.坐标.y, 击打道具信息.坐标.z);
					break;
				}
				else
				{
					MyTrace(L"攻击击打道具 %s %d/%d %0.3f, %0.3f, %0.3f", 击打道具信息.wName, 击打道具信息.dCurHp, 击打道具信息.dMaxHp, 击打道具信息.坐标.x, 击打道具信息.坐标.y, 击打道具信息.坐标.z);
					技能::技能释放2(击打道具信息.坐标);
				}
				//}
				//else
				//{
					//break;
				//}
			}
			if (击打道具信息.dType == 11)
			{
				if (击打道具信息.dIsDead == 1 || 击打道具信息.dResId == 0) //|| 击打道具信息.dPortalOpen == 2 83BF??????????0F85????????0FB687????????3C??0F84????????3C??0F84????????33F63C??75??0FB687????????2C??A8??
				{
					MyTrace(L"0x%I64x 击打道具已死亡 %0.3f, %0.3f, %0.3f", 击打道具信息.objBase, 击打道具信息.坐标.x, 击打道具信息.坐标.y, 击打道具信息.坐标.z);
					break;
				}
				else
				{
					MyTrace(L"攻击击打道具 %s %d/%d %0.3f, %0.3f, %0.3f", 击打道具信息.wName, 击打道具信息.dCurHp, 击打道具信息.dMaxHp, 击打道具信息.坐标.x, 击打道具信息.坐标.y, 击打道具信息.坐标.z);
					技能::技能释放2(击打道具信息.坐标);
				}
			}
		}
		else
		{
			break;
		}

		Sleep(300);
	}
}
bool 清理怪物(float x, float y, float z, int 打怪范围, int 距离自身范围 = 100)
{
	objInfo_ 最近怪物;
	vector<objInfo_>怪物数组;
	环境::遍历怪物(怪物数组);
	MyTrace(L"怪物数量 %d", 怪物数组.size());
	最近怪物 = 取指定坐标范围内怪物(怪物数组, x, y, z, 打怪范围, 距离自身范围);
	MyTrace(L"最近怪物名字 %s", 最近怪物.wName);
	if (最近怪物.dObjId != 0)
	{
		//MyTrace(L"最近怪物 %s 距离%0.3f", 最近怪物.wName, 最近怪物.fDis);
		if (最近怪物.fDis > 700)
		{
			地图::本地图寻路(最近怪物.坐标.x, 最近怪物.坐标.y, 最近怪物.坐标.z, 0);
			Sleep(500);
		}
		else
		{
			地图::本地图寻路(最近怪物.坐标.x, 最近怪物.坐标.y, 最近怪物.坐标.z, 0);
			功能::打怪程序(最近怪物.objBase);
			if (暂时不打ID.size() != 0)
			{
				暂时不打ID.clear();
			}

		}
		//MyTrace(L"返回假");
		return false;
	}
	//MyTrace(L"返回真");
	return true;
}
bool 清理NPC转怪物(float x, float y, float z, int 打怪范围, int 距离自身范围 = 100)
{
	objInfo_ 最近NPC怪物;
	vector<objInfo_>NPC怪物数组;
	环境::遍历NPC(NPC怪物数组);
	MyTrace(L"NPC怪物数量 %d", NPC怪物数组.size());
	//最近怪物 = 取范围内怪物(怪物数组, 打怪范围);
	//return false;

	最近NPC怪物 = 取指定坐标范围内NPC怪物(NPC怪物数组, x, y, z, 打怪范围, 距离自身范围);
	MyTrace(L"最近怪物名字 %s", 最近NPC怪物.wName);
	if (最近NPC怪物.dObjId != 0)
	{
		MyTrace(L"最近NPC怪物 %s 距离%0.3f", 最近NPC怪物.wName, 最近NPC怪物.fDis);
		if (最近NPC怪物.fDis > 700)
		{
			地图::本地图寻路(最近NPC怪物.坐标.x, 最近NPC怪物.坐标.y, 最近NPC怪物.坐标.z, 0);
			Sleep(500);
		}
		else
		{
			地图::本地图寻路(最近NPC怪物.坐标.x, 最近NPC怪物.坐标.y, 最近NPC怪物.坐标.z, 0);
			功能::打怪程序(最近NPC怪物.objBase);
			if (暂时不打ID.size() != 0)
			{
				暂时不打ID.clear();
			}

		}
		MyTrace(L"返回假");
		return false;
	}
	MyTrace(L"返回真");
	return true;
}
bool 是否为优先打怪ID(DWORD resid)
{
	for (size_t i = 0; i < 优先打怪ID.size(); i++)
	{
		if (优先打怪ID[i] == resid)
		{
			return true;
		}
	}
	return false;
}
bool 清理击打道具(float x, float y, float z, int 距离自身范围, int 打怪范围)
{
	objInfo_ 最近击打道具;
	vector<objInfo_>击打道具数组;
	环境::遍历击打道具(击打道具数组);
	MyTrace(L"击打道具数组 %d 优先打怪%d  距离自身范围 %d   打怪范围 %d", 击打道具数组.size(), 优先打怪ID.size(), 距离自身范围, 打怪范围);
	最近击打道具 = 取范围内击打道具(击打道具数组, x, y, z, 打怪范围, 距离自身范围);
	MyTrace(L"最近击打道具 %d 距离 %0.3f ->%0.3f %0.3f %0.3f", 最近击打道具.dResId, 最近击打道具.fDis, 最近击打道具.坐标.x, 最近击打道具.坐标.y, 最近击打道具.坐标.z);
	if (最近击打道具.dObjId != 0)
	{
		if (最近击打道具.fDis > 500)
		{
			if (!本人::是否在走路())
			{
				if (地图::指定地点是否可到达_M(最近击打道具.坐标.x, 最近击打道具.坐标.y, 最近击打道具.坐标.z))
				{
					MyTrace(L"可达");
					地图::本地图寻路(最近击打道具.坐标.x, 最近击打道具.坐标.y, 最近击打道具.坐标.z, 0);
					Sleep(1000);

				}
				else
				{
					MyTrace(L"判断附近可走");
					bool 是否可达 = false;
					for (size_t i = 0; i < 8; i++)
					{
						if (地图::指定地点是否可到达_M(最近击打道具.坐标.x - (i + 1) * 50, 最近击打道具.坐标.y, 最近击打道具.坐标.z))
						{
							地图::本地图寻路(最近击打道具.坐标.x - (i + 1) * 50, 最近击打道具.坐标.y, 最近击打道具.坐标.z, 0);
							是否可达 = true;
							Sleep(1000);
							break;
						}
						if (地图::指定地点是否可到达_M(最近击打道具.坐标.x + (i + 1) * 50, 最近击打道具.坐标.y, 最近击打道具.坐标.z))
						{
							地图::本地图寻路(最近击打道具.坐标.x + (i + 1) * 50, 最近击打道具.坐标.y, 最近击打道具.坐标.z, 0);
							是否可达 = true;
							Sleep(1000);
							break;
						}
						if (地图::指定地点是否可到达_M(最近击打道具.坐标.x, 最近击打道具.坐标.y - (i + 1) * 50, 最近击打道具.坐标.z))
						{
							地图::本地图寻路(最近击打道具.坐标.x, 最近击打道具.坐标.y - (i + 1) * 50, 最近击打道具.坐标.z, 0);
							是否可达 = true;
							Sleep(1000);
							break;
						}
						if (地图::指定地点是否可到达_M(最近击打道具.坐标.x, 最近击打道具.坐标.y + (i + 1) * 50, 最近击打道具.坐标.z))
						{
							地图::本地图寻路(最近击打道具.坐标.x, 最近击打道具.坐标.y + (i + 1) * 50, 最近击打道具.坐标.z, 0);
							是否可达 = true;
							Sleep(1000);
							break;
						}
						Sleep(100);
					}
					//if (是否可达 == false)//6月5日 linjinmao 屏蔽
					//{
					//	MyTrace(L"寻路无法到达 判断是否加入暂时不打");
					//	if (是否为优先打怪ID(最近击打道具.dResId) == false)
					//	{
					//		MyTrace(L"加入暂时不打 %d", 最近击打道具.dResId);
					//		加入暂时不打ID_数字(最近击打道具.dResId);
					//	}

					//}
					/*srand((unsigned)time(NULL));
					int 随机值 = Random(1, 4);
					if (随机值 == 1)
					{
						地图::本地图寻路(最近击打道具.坐标.x - 100, 最近击打道具.坐标.y, 最近击打道具.坐标.z, 0);
						Sleep(1000);
					}
					if (随机值 == 2)
					{
						地图::本地图寻路(最近击打道具.坐标.x +100, 最近击打道具.坐标.y, 最近击打道具.坐标.z, 0);
						Sleep(1000);
					}
					if (随机值 == 3)
					{
						地图::本地图寻路(最近击打道具.坐标.x, 最近击打道具.坐标.y + 100, 最近击打道具.坐标.z, 0);
						Sleep(1000);
					}
					if (随机值 == 4)
					{
						地图::本地图寻路(最近击打道具.坐标.x, 最近击打道具.坐标.y - 100, 最近击打道具.坐标.z, 0);
						Sleep(1000);
					}*/
				}
			}


		}
		else
		{
			地图::本地图寻路(最近击打道具.坐标.x, 最近击打道具.坐标.y, 最近击打道具.坐标.z, 0);
			功能::破坏击打道具程序(最近击打道具.objBase, 最近击打道具.dResId);
			if (暂时不打ID.size() != 0)
			{
				暂时不打ID.clear();
			}
		}
		return false;
	}
	return true;
}

bool 功能::拾取道具(int 打怪范围)
{
	objInfo_ 最近拾取道具;
	vector<objInfo_>拾取道具组;
	环境::遍历地面物品(拾取道具组);
	MyTrace(L"拾取道具数量 %d", 拾取道具组.size());
	最近拾取道具 = 取范围内拾取物品(拾取道具组, 打怪范围);
	MyTrace(L"最近拾取道具 %s %d", 最近拾取道具.wName, 最近拾取道具.fDis);
	if (最近拾取道具.dObjId != 0)
	{
		if (最近拾取道具.fDis > 500)
		{
			地图::本地图寻路(最近拾取道具.坐标.x, 最近拾取道具.坐标.y, 最近拾取道具.坐标.z, 0);
		}
		else
		{
			MyTrace(L"拾取道具 %s %d 距离%0.3f", 最近拾取道具.wName, 最近拾取道具.dResId, 最近拾取道具.fDis);
			环境::拾物(最近拾取道具.objBase);
			//功能::打怪程序(最近拾取道具.objBase);
		}
		return false;
	}
	return true;
}
bool 功能::优先打怪(int 打怪范围)
{
	坐标_ 本人 = 本人::取坐标();
	if (清理怪物(本人.x, 本人.y, 本人.z, 打怪范围) == true && 清理NPC转怪物(本人.x, 本人.y, 本人.z, 打怪范围) == true)
	{
		return true;
	}
	return false;
}
bool 功能::优先破坏击打道具(int 打怪范围)
{
	坐标_ 本人 = 本人::取坐标();
	if (清理击打道具(本人.x, 本人.y, 本人.z, 打怪范围, 打怪范围) == true)
	{
		//暂时不打ID.clear();
		return true;
	}
	return false;
}
void 取出指定路径组(DWORD 路径序号, vector<录制坐标_>& 源录制坐标组, vector<录制坐标_>& 返回录制坐标组)
{
	for (size_t i = 0; i < 源录制坐标组.size(); i++)
	{
		if (源录制坐标组[i].线路 == 路径序号)
		{
			返回录制坐标组.push_back(源录制坐标组[i]);
		}
	}
}
bool 地图ID与录制坐标组ID是否相同(DWORD 地图ID)
{
	if (录制坐标组.size() == 0)
	{
		return false;
	}
	if (地图ID == 录制坐标组[0].地图ID)
	{
		return true;
	}
	return false;
}

录制坐标_ 取出最近录制坐标(float x, float y, float z, vector<录制坐标_>& 参录制坐标组)
{
	int 最近距离 = 0;
	录制坐标_ 找到目的相近坐标;
	for (size_t i = 0; i < 参录制坐标组.size(); i++)
	{
		int 最终dis;
		int dis = 距离计算(x, y, z, 参录制坐标组[i].x1, 参录制坐标组[i].y1, 参录制坐标组[i].z1);
		//MyTrace(L"1 %0.3f %0.3f %0.3f ,dis:%d", 参录制坐标组[i].x1, 参录制坐标组[i].y1, 参录制坐标组[i].z1, dis);
		int dis2 = 距离计算(x, y, z, 参录制坐标组[i].x2, 参录制坐标组[i].y2, 参录制坐标组[i].z2);
		//MyTrace(L"2 %0.3f %0.3f %0.3f ,dis:%d", 参录制坐标组[i].x2, 参录制坐标组[i].y2, 参录制坐标组[i].z2, dis2);
		if (dis < dis2)
		{
			最终dis = dis;
		}
		if (dis > dis2)
		{
			最终dis = dis2;
		}
		if (dis == dis2)
		{
			最终dis = dis;
		}
		if (最近距离 == 0)
		{
			最近距离 = 最终dis;
			找到目的相近坐标 = 参录制坐标组[i];
		}
		else
		{
			if (最近距离 > 最终dis)
			{
				最近距离 = 最终dis;
				找到目的相近坐标 = 参录制坐标组[i];
			}
		}
	}
	return 找到目的相近坐标;
}
录制坐标_ 取出最近可达录制坐标(float x, float y, float z, vector<录制坐标_>& 参录制坐标组)
{
	int 最近距离 = 0;
	录制坐标_ 找到目的相近坐标;
	for (size_t i = 0; i < 参录制坐标组.size(); i++)
	{
		int 最终dis = 0;
		int dis = 0, dis2 = 0;
		if (地图::指定地点是否可到达_M(参录制坐标组[i].x1, 参录制坐标组[i].y1, 参录制坐标组[i].z1))
		{
			dis = 距离计算(x, y, z, 参录制坐标组[i].x1, 参录制坐标组[i].y1, 参录制坐标组[i].z1);
		}
		else
		{
			dis = 9999999;
		}

		//MyTrace(L"1 %0.3f %0.3f %0.3f ,dis:%d", 参录制坐标组[i].x1, 参录制坐标组[i].y1, 参录制坐标组[i].z1, dis);
		if (地图::指定地点是否可到达_M(参录制坐标组[i].x2, 参录制坐标组[i].y2, 参录制坐标组[i].z2))
		{
			dis2 = 距离计算(x, y, z, 参录制坐标组[i].x2, 参录制坐标组[i].y2, 参录制坐标组[i].z2);
		}
		else
		{
			dis2 = 9999999;
		}
		//MyTrace(L"2 %0.3f %0.3f %0.3f ,dis:%d", 参录制坐标组[i].x2, 参录制坐标组[i].y2, 参录制坐标组[i].z2, dis2);
		if (dis < dis2)
		{
			最终dis = dis;
		}
		if (dis > dis2)
		{
			最终dis = dis2;
		}
		if (dis == dis2)
		{
			最终dis = dis;
		}
		if (最近距离 == 0)
		{
			最近距离 = 最终dis;
			找到目的相近坐标 = 参录制坐标组[i];
		}
		else
		{
			if (最近距离 > 最终dis)
			{
				最近距离 = 最终dis;
				找到目的相近坐标 = 参录制坐标组[i];
			}
		}
	}
	return 找到目的相近坐标;
}
int 分区方向 = 1;
bool 功能::获取寻路分段坐标组(DWORD 地图ID, float x, float y, float z, vector<录制坐标_>& 返回路径分段坐标组)
{

	vector<录制坐标_>分段录制坐标组;
	int 最近距离 = 0;
	录制坐标_ 找到目的相近坐标;
	录制坐标_ 找到与角色相近坐标;
	录制坐标_ 空;
	坐标_ 角色坐标 = 本人::取坐标();
	if (地图ID与录制坐标组ID是否相同(地图ID) == false)
	{
		配置::取录制坐标(地图ID, 录制坐标组);
	}
	找到目的相近坐标 = 取出最近录制坐标(x, y, z, 录制坐标组);
	if (找到目的相近坐标.x1 == 0)
	{
		MyTrace(L"未找到寻路最近分段坐标");
		return false;
	}
	MyTrace(L"目的地图ID:%d 目的坐标 %0.3f %0.3f %0.3f 找到相近目的坐标 优先到达目的坐标 %0.3f %0.3f %0.3f", 地图ID, x, y, z, 找到目的相近坐标.x1, 找到目的相近坐标.y1, 找到目的相近坐标.z1);
	//地图::本地图寻路(角色坐标.x+50, 角色坐标.y+50, 角色坐标.z, 0);
	Sleep(100);
	if (地图::指定地点是否可到达_M(找到目的相近坐标.x1, 找到目的相近坐标.y1, 找到目的相近坐标.z1))
	{
		MyTrace(L"目标地点可到达");
		分区方向 = 1;
		返回路径分段坐标组.push_back(找到目的相近坐标);
		return true;
	}
	else
	{
		if (地图::指定地点是否可到达_M(找到目的相近坐标.x2, 找到目的相近坐标.y2, 找到目的相近坐标.z2))
		{
			MyTrace(L"目标地点可到达");
			分区方向 = 2;
			返回路径分段坐标组.push_back(找到目的相近坐标);
			return true;
		}
		取出指定路径组(找到目的相近坐标.线路, 录制坐标组, 分段录制坐标组);
		MyTrace(L"地图ID:%d 返回分段[%d]分段录制坐标组数量 %d", 地图ID, 找到目的相近坐标.线路, 分段录制坐标组.size());
		坐标_ 角色坐标 = 本人::取坐标();
		找到与角色相近坐标 = 取出最近可达录制坐标(角色坐标.x, 角色坐标.y, 角色坐标.z, 分段录制坐标组);
		MyTrace(L"目的地图ID:%d 目的坐标 %0.3f %0.3f %0.3f  距离角色最近坐标 %0.3f %0.3f %0.3f", 地图ID, x, y, z, 找到与角色相近坐标.x1, 找到与角色相近坐标.y1, 找到与角色相近坐标.z1);
		if (找到与角色相近坐标.x1 == 0)
		{
			MyTrace(L"未找到与角色相近坐标");
			return false;
		}
		if (找到目的相近坐标.线路分段 == 找到与角色相近坐标.线路分段)
		{
			if (地图::指定地点是否可到达_M(找到与角色相近坐标.x1, 找到与角色相近坐标.y1, 找到与角色相近坐标.z1))
			{
				分区方向 = 1;
				返回路径分段坐标组.push_back(找到目的相近坐标);
				return true;
			}
			else if (地图::指定地点是否可到达_M(找到与角色相近坐标.x2, 找到与角色相近坐标.y2, 找到与角色相近坐标.z2))
			{
				分区方向 = 2;
				返回路径分段坐标组.push_back(找到目的相近坐标);
				return true;
			}
			else
			{
				坐标_ 角色坐标 = 本人::取坐标();
				MyTrace(L"获取线路分段相同,但是无法到达,取角色最近可达坐标   目的坐标 %0.3f %0.3f %0.3f  角色坐标 %0.3f %0.3f %0.3f ", x, y, z, 角色坐标.x, 角色坐标.y, 角色坐标.z);
				/*找到与角色相近坐标 = 取出最近可达录制坐标(角色坐标.x, 角色坐标.y, 角色坐标.z, 录制坐标组);
				if (地图::指定地点是否可到达_M(找到与角色相近坐标.x1, 找到与角色相近坐标.y1, 找到与角色相近坐标.z1))
				{
					分区方向 = 1;
					返回路径分段坐标组.push_back(找到目的相近坐标);
					return true;
				}
				else if (地图::指定地点是否可到达_M(找到与角色相近坐标.x2, 找到与角色相近坐标.y2, 找到与角色相近坐标.z2))
				{
					分区方向 = 2;
					返回路径分段坐标组.push_back(找到目的相近坐标);
					return true;
				}*/
				//返回路径分段坐标组.push_back(找到与角色相近坐标);
				return false;
			}

		}
		分区方向 = 1;
		if (找到目的相近坐标.线路分段 > 找到与角色相近坐标.线路分段)
		{
			for (size_t i = 0; i < 分段录制坐标组.size(); i++)
			{
				if (分段录制坐标组[i].线路分段 > 找到目的相近坐标.线路分段 || 分段录制坐标组[i].线路分段 < 找到与角色相近坐标.线路分段)
				{

					continue;
				}
				if (分段录制坐标组[i].操作 == 2 || 分段录制坐标组[i].操作 == 4)
				{
					分段录制坐标组[i].dis = GetDis(分段录制坐标组[i].x2, 分段录制坐标组[i].y2, 分段录制坐标组[i].z2);
				}
				else
				{
					分段录制坐标组[i].dis = GetDis(分段录制坐标组[i].x1, 分段录制坐标组[i].y1, 分段录制坐标组[i].z1);
				}

				返回路径分段坐标组.push_back(分段录制坐标组[i]);
			}
		}
		if (找到目的相近坐标.线路分段 < 找到与角色相近坐标.线路分段)
		{
			for (size_t i = 0; i < 分段录制坐标组.size(); i++)
			{
				if (分段录制坐标组[i].线路分段 < 找到目的相近坐标.线路分段 || 分段录制坐标组[i].线路分段 > 找到与角色相近坐标.线路分段)
				{
					continue;
				}
				if (分段录制坐标组[i].操作 == 2 || 分段录制坐标组[i].操作 == 4)
				{
					分段录制坐标组[i].dis = GetDis(分段录制坐标组[i].x1, 分段录制坐标组[i].y1, 分段录制坐标组[i].z1);
				}
				else
				{
					分段录制坐标组[i].dis = GetDis(分段录制坐标组[i].x2, 分段录制坐标组[i].y2, 分段录制坐标组[i].z2);
				}
				返回路径分段坐标组.push_back(分段录制坐标组[i]);
			}
		}
		MyTrace(L"地图ID:%d 返回分段[%d]筛选分段录制坐标组数量 %d", 地图ID, 找到目的相近坐标.线路, 返回路径分段坐标组.size());
	}
	return true;
}
void 设置分段坐标已到达()
{
	录制坐标_ 空;
	/*for (size_t i = 0; i < 路径分段坐标组.size(); i++)
	{
		if (分段处理坐标.线路 == 路径分段坐标组[i].线路 && 分段处理坐标.线路分段 == 路径分段坐标组[i].线路分段)
		{
			路径分段坐标组[i].已分配 = true;
		}
	}*/
	int 计次 = 0;
	for (size_t i = 0; i < 路径分段坐标组.size(); i++)
	{

		if (路径分段坐标组[i].已分配 == true)
		{
			计次 = 计次 + 1;
		}

	}
	if (计次 >= 路径分段坐标组.size())
	{
		路径分段坐标组.clear();
	}
	分段处理坐标 = 空;
}
bool 录制坐标排序(const 录制坐标_& o1, const 录制坐标_& o2)
{
	return o1.dis > o2.dis;
}

//局_录制坐标.操作 = _ttoi(坐标文本组[6]);
//局_录制坐标.线路 = _ttoi(坐标文本组[7]);
//局_录制坐标.线路分段 = _ttoi(坐标文本组[8]);
//分段处理操作  0 走到分段目标停止    2  走到分段目标按G    3传送门    4坐电梯
void 前往分段处理坐标(float x, float y, float z)//分段处理操作  0 走到分段目标停止    2  走到分段目标按G    3传送门    4坐电梯
{
	DWORD 地图ID = 地图::取地图ID();

	if (分段处理坐标.x1 != 0 && 分段处理坐标.操作 != -1)
	{

		//分区方向  1 2 使用第一套坐标 还是第二套坐标
		MyTrace(L"分段处理坐标 坐标  %0.3f|%0.3f|%0.3f    操作%d 分段 %d", 分段处理坐标.x1, 分段处理坐标.y1, 分段处理坐标.z1, 分段处理坐标.操作, 分区方向);
		if (分段处理坐标.操作 == 4)
		{

			if (分区方向 == 1)
			{
				if (环境::获取当前电梯ID() != 0)
				{
					MyTrace(L"已乘坐电梯");
					if (地图::指定地点是否可到达_M(分段处理坐标.x2, 分段处理坐标.y2, 分段处理坐标.z2))
					{
						地图::本地图寻路(分段处理坐标.x2, 分段处理坐标.y2, 分段处理坐标.z2, 0);
						Sleep(1000);
						设置分段坐标已到达();
						路径分段坐标组.clear();
					}

					return;
				}
				if (GetDis(分段处理坐标.x1, 分段处理坐标.y1, 分段处理坐标.z1) <= 50)
				{

					MyTrace(L"乘坐电梯1");
					vector<objInfo_>数组;
					环境::遍历电梯(数组);
					if (数组.size() > 0)
					{

						objInfo_ 电梯信息 = 数组[0];
						MyTrace(L"乘坐 %s->%d ->modID %x", 电梯信息.wName, 电梯信息.dResId, 电梯信息.ModId);
						if (地图::本地图寻路(电梯信息.坐标.x, 电梯信息.坐标.y, 电梯信息.坐标.z, 电梯信息.ModId))
						{
							if (电梯信息.dResId == 1069101)
							{
								int 计次 = 0;
								while (环境::获取当前电梯ID() != 0 && 计次 <= 60)
								{
									MyTrace(L"已乘坐木筏");
									if (地图::指定地点是否可到达_M(分段处理坐标.x2, 分段处理坐标.y2, 分段处理坐标.z2))
									{
										地图::本地图寻路(分段处理坐标.x2, 分段处理坐标.y2, 分段处理坐标.z2, 0);
										Sleep(1000);
										设置分段坐标已到达();
										路径分段坐标组.clear();
										break;
									}
									计次 = 计次 + 1;
									Sleep(1000);
								}
							}
							else
							{
								Sleep(2000);
								if (环境::获取当前电梯ID() != 0)
								{
									MyTrace(L"已乘坐电梯");
									Sleep(2000);
									/*设置分段坐标已到达();

									路径分段坐标组.clear();*/
								}
							}

						}

					}
					/*if (!地图::指定地点是否可到达_M(分段处理坐标.x1, 分段处理坐标.y1, 分段处理坐标.z1))
					{
						设置分段坐标已到达();
					}*/
					return;
				}
				else
				{
					if (地图::指定地点是否可到达_M(分段处理坐标.x1, 分段处理坐标.y1, 分段处理坐标.z1))
					{
						地图::本地图寻路(分段处理坐标.x1, 分段处理坐标.y1, 分段处理坐标.z1, 0);
					}
					else
					{
						设置分段坐标已到达();
						路径分段坐标组.clear();
					}
					return;
				}

			}
			else
			{
				if (环境::获取当前电梯ID() != 0)
				{
					MyTrace(L"已乘坐电梯");
					if (地图::指定地点是否可到达_M(分段处理坐标.x1, 分段处理坐标.y1, 分段处理坐标.z1))
					{
						地图::本地图寻路(分段处理坐标.x1, 分段处理坐标.y1, 分段处理坐标.z1, 0);
						Sleep(1000);
						设置分段坐标已到达();

						路径分段坐标组.clear();
					}
					return;
				}
				if (GetDis(分段处理坐标.x2, 分段处理坐标.y2, 分段处理坐标.z2) <= 50)
				{
					MyTrace(L"乘坐电梯2");
					vector<objInfo_>数组;
					环境::遍历电梯(数组);
					if (数组.size() > 0)
					{
						objInfo_ 电梯信息 = 数组[0];
						MyTrace(L"乘坐 %s->%d ->modID %x", 电梯信息.wName, 电梯信息.dResId, 电梯信息.ModId);
						if (地图::本地图寻路(电梯信息.坐标.x, 电梯信息.坐标.y, 电梯信息.坐标.z, 电梯信息.ModId))
						{
							Sleep(2000);
							if (环境::获取当前电梯ID() != 0)
							{
								MyTrace(L"已乘坐电梯");
								/*设置分段坐标已到达();

								路径分段坐标组.clear();*/
							}
						}

					}
					/*if (!地图::指定地点是否可到达_M(分段处理坐标.x2, 分段处理坐标.y2, 分段处理坐标.z2))
					{
						设置分段坐标已到达();
					}*/
					return;
				}
				else
				{
					if (地图::指定地点是否可到达_M(分段处理坐标.x2, 分段处理坐标.y2, 分段处理坐标.z2))
					{
						地图::本地图寻路(分段处理坐标.x2, 分段处理坐标.y2, 分段处理坐标.z2, 0);
					}
					else
					{
						设置分段坐标已到达();
						路径分段坐标组.clear();
					}
					return;
				}
			}

		}
		if (分段处理坐标.操作 == 2)
		{
			if (分区方向 == 1)
			{
				MyTrace(L"分段处理坐标 操作 2 方向1");
				if (!地图::指定地点是否可到达_M(分段处理坐标.x1, 分段处理坐标.y1, 分段处理坐标.z1))
				{
					设置分段坐标已到达();
					路径分段坐标组.clear();
				}
				if (GetDis(分段处理坐标.x1, 分段处理坐标.y1, 分段处理坐标.z1) <= 50)
				{
					UI功能::内存按键('G');
					Sleep(2000);
					坐标_ 角色坐标 = 本人::取坐标();
					if (角色坐标.x != 分段处理坐标.x1 || 角色坐标.y != 分段处理坐标.y1 || 角色坐标.z != 分段处理坐标.z1)
					{
						MyTrace(L"设置已到达");
						设置分段坐标已到达();
					}
					/*if (!地图::指定地点是否可到达_M(分段处理坐标.x1, 分段处理坐标.y1, 分段处理坐标.z1))
					{*/

					//路径分段坐标组.clear();
				//}
					return;
				}
				else
				{
					地图::本地图寻路(分段处理坐标.x1, 分段处理坐标.y1, 分段处理坐标.z1, 0);
				}
			}
			else
			{
				MyTrace(L"分段处理坐标 操作 2 方向2 %0.3f %0.3f %0.3f", 分段处理坐标.x2, 分段处理坐标.y2, 分段处理坐标.z2);
				if (!地图::指定地点是否可到达_M(分段处理坐标.x2, 分段处理坐标.y2, 分段处理坐标.z2))
				{
					设置分段坐标已到达();
					路径分段坐标组.clear();
				}
				MyTrace(L"分段处理坐标 判断 2 方向2");
				if (GetDis(分段处理坐标.x2, 分段处理坐标.y2, 分段处理坐标.z2) <= 50)
				{

					UI功能::内存按键('G');
					Sleep(2000);

					坐标_ 角色坐标 = 本人::取坐标();
					if (角色坐标.x != 分段处理坐标.x2 || 角色坐标.y != 分段处理坐标.y2 || 角色坐标.z != 分段处理坐标.z2)
					{
						MyTrace(L"设置已到达");
						设置分段坐标已到达();
					}
					/*if (!地图::指定地点是否可到达_M(分段处理坐标.x2, 分段处理坐标.y2, 分段处理坐标.z2))
					{*/
					设置分段坐标已到达();
					//路径分段坐标组.clear();
				//}
					return;
				}
				else
				{
					地图::本地图寻路(分段处理坐标.x2, 分段处理坐标.y2, 分段处理坐标.z2, 0);
				}
			}

		}
		if (分段处理坐标.操作 == 0)
		{
			if (分区方向 == 1)
			{
				MyTrace(L"分段处理坐标 操作 0");
				if (GetDis(分段处理坐标.x1, 分段处理坐标.y1, 分段处理坐标.z1) <= 50)
				{
					设置分段坐标已到达();
					//路径分段坐标组.clear();
					return;
				}
				else
				{
					if (地图::指定地点是否可到达_M(分段处理坐标.x1, 分段处理坐标.y1, 分段处理坐标.z1))
					{
						地图::本地图寻路(分段处理坐标.x1, 分段处理坐标.y1, 分段处理坐标.z1, 0);
					}
					else
					{
						设置分段坐标已到达();
						路径分段坐标组.clear();
						return;
					}
				}
			}
			else
			{
				MyTrace(L"分段处理坐标 操作 0");
				if (GetDis(分段处理坐标.x2, 分段处理坐标.y2, 分段处理坐标.z2) <= 50)
				{

					设置分段坐标已到达();
					//路径分段坐标组.clear();
					return;
				}
				else
				{
					if (地图::指定地点是否可到达_M(分段处理坐标.x2, 分段处理坐标.y2, 分段处理坐标.z2))
					{
						地图::本地图寻路(分段处理坐标.x2, 分段处理坐标.y2, 分段处理坐标.z2, 0);
					}
					else
					{
						MyTrace(L"设置已到达");
						设置分段坐标已到达();
						路径分段坐标组.clear();
						return;
					}

				}
			}

		}
		if (分段处理坐标.操作 == 3)
		{
			if (分区方向 == 1)
			{
				MyTrace(L"分段处理坐标 操作 3");
				if (GetDis(分段处理坐标.x1, 分段处理坐标.y1, 分段处理坐标.z1) <= 50)
				{
					MyTrace(L"寻找传送门");
					vector<objInfo_>数组;
					环境::遍历传送门(数组);
					if (数组.size() > 0)
					{
						objInfo_ 传送门信息 = 数组[0];
						MyTrace(L"进入传送门 %x ->fDis %0.3f", 传送门信息.dResId, 传送门信息.fDis);

						if (GetDis(7645, 8792, -18011) < 500)
						{
							if (传送门信息.dResId == 0x4F1B)
							{
								传送门信息.坐标.x = 7645;
								传送门信息.坐标.y = 8792;
								传送门信息.坐标.z = -18011;
							}
						}
						if (GetDis(9083, 8228, -15359) < 500)
						{
							if (传送门信息.dResId == 0x4F1B)
							{
								传送门信息.坐标.x = 9083;
								传送门信息.坐标.y = 8228;
								传送门信息.坐标.z = -15359;
							}
						}
						if (GetDis(5383, -6350, -5104) > 1000)//魔可可酒吧
						{
							if (传送门信息.dResId == 0x1ae33 && 地图::取小地图名() != L"")
							{
								传送门信息.坐标.x = 8366;
								传送门信息.坐标.y = 5666;
							}
						}
						if (!地图::指定地点是否可到达_M(传送门信息.坐标.x, 传送门信息.坐标.y, 传送门信息.坐标.z))
						{
							for (size_t i = 1; i <= 5; i++)
							{
								if (地图::指定地点是否可到达_M(传送门信息.坐标.x + (i * 50), 传送门信息.坐标.y, 传送门信息.坐标.z))
								{
									传送门信息.坐标.x = 传送门信息.坐标.x + (i * 50);
									break;
								}
								if (地图::指定地点是否可到达_M(传送门信息.坐标.x - (i * 50), 传送门信息.坐标.y, 传送门信息.坐标.z))
								{
									传送门信息.坐标.x = 传送门信息.坐标.x - (i * 50);
									break;
								}
								if (地图::指定地点是否可到达_M(传送门信息.坐标.x, 传送门信息.坐标.y + (i * 50), 传送门信息.坐标.z))
								{
									传送门信息.坐标.y = 传送门信息.坐标.y + (i * 50);
									break;
								}
								if (地图::指定地点是否可到达_M(传送门信息.坐标.x, 传送门信息.坐标.y - (i * 50), 传送门信息.坐标.z))
								{
									传送门信息.坐标.y = 传送门信息.坐标.y - (i * 50);
									break;
								}
							}
						}

						if (地图::本地图寻路(传送门信息.坐标.x, 传送门信息.坐标.y, 传送门信息.坐标.z, 0))
						{
							Sleep(1000);

							MyTrace(L"已进入传送门 %0.3f %0.3f %0.3f ", 传送门信息.坐标.x, 传送门信息.坐标.y, 传送门信息.坐标.z);
							设置分段坐标已到达();
							路径分段坐标组.clear();
							return;
							//路径分段坐标组.clear();

						}

					}
					else
					{
						MyTrace(L"未找到传送门");
						//设置分段坐标已到达();
						//路径分段坐标组.clear();
					}

					return;

				}
				else
				{
					if (地图::指定地点是否可到达_M(分段处理坐标.x1, 分段处理坐标.y1, 分段处理坐标.z1))
					{
						地图::本地图寻路(分段处理坐标.x1, 分段处理坐标.y1, 分段处理坐标.z1, 0);
					}
					else
					{
						设置分段坐标已到达();
						路径分段坐标组.clear();
						return;
					}
				}
			}
			else
			{
				MyTrace(L"分段处理坐标 操作 3");
				if (GetDis(分段处理坐标.x2, 分段处理坐标.y2, 分段处理坐标.z2) <= 50)
				{
					MyTrace(L"寻找传送门");
					vector<objInfo_>数组;
					环境::遍历传送门(数组);
					if (数组.size() > 0)
					{
						objInfo_ 传送门信息 = 数组[0];
						MyTrace(L"进入传送门 %x ->fDis %d", 传送门信息.dResId, 传送门信息.fDis);
						if (GetDis(7645, 8792, -18011) < 200)
						{
							if (传送门信息.dResId == 0x4F1B)
							{
								传送门信息.坐标.x = 7645;
								传送门信息.坐标.y = 8792;
								传送门信息.坐标.z = -18011;
							}
						}
						if (GetDis(9083, 8228, -15359) < 500)
						{
							if (传送门信息.dResId == 0x4F1B)
							{
								传送门信息.坐标.x = 9083;
								传送门信息.坐标.y = 8228;
								传送门信息.坐标.z = -15359;
							}
						}
						if (地图::本地图寻路(传送门信息.坐标.x, 传送门信息.坐标.y, 传送门信息.坐标.z, 0))
						{
							Sleep(1000);

							MyTrace(L"已进入传送门 %0.3f %0.3f %0.3f ", 传送门信息.坐标.x, 传送门信息.坐标.y, 传送门信息.坐标.z);
							设置分段坐标已到达();
							路径分段坐标组.clear();
							return;
							//路径分段坐标组.clear();

						}

					}
					MyTrace(L"未找到传送门传送门");
					//设置分段坐标已到达();
					//路径分段坐标组.clear();
					return;
				}
				else
				{
					if (地图::指定地点是否可到达_M(分段处理坐标.x2, 分段处理坐标.y2, 分段处理坐标.z2))
					{
						地图::本地图寻路(分段处理坐标.x2, 分段处理坐标.y2, 分段处理坐标.z2, 0);
					}
					else
					{
						MyTrace(L"设置已到达");
						设置分段坐标已到达();
						路径分段坐标组.clear();
						return;
					}

				}
			}

		}
	}
	else
	{
		if (路径分段坐标组.size() == 0)
		{
			功能::获取寻路分段坐标组(地图ID, x, y, z, 路径分段坐标组);
			return;
		}
		if (路径分段坐标组.size() == 1)
		{
			分段处理坐标 = 路径分段坐标组[0];
			路径分段坐标组[0].已分配 = true;
			MyTrace(L"获取到分段处理坐标 %0.3f %0.3f %0.3f", 分段处理坐标.x1, 分段处理坐标.y1, 分段处理坐标.z1);
			return;
		}
		else
		{
			::sort(路径分段坐标组.begin(), 路径分段坐标组.end(), 录制坐标排序);
			MyTrace(L"路径分段数量 %d", 路径分段坐标组.size());
			for (size_t i = 0; i < 路径分段坐标组.size(); i++)
			{
				MyTrace(L"路径分段坐标组 %0.3f %0.3f %0.3f 距离 %d", 路径分段坐标组[i].x1, 路径分段坐标组[i].y1, 路径分段坐标组[i].z1, 路径分段坐标组[i].dis);
			}
			for (size_t i = 0; i < 路径分段坐标组.size(); i++)
			{
				MyTrace(L"路径分段坐标组 %0.3f %0.3f %0.3f", 路径分段坐标组[i].x1, 路径分段坐标组[i].y1, 路径分段坐标组[i].z1);
				if (地图::指定地点是否可到达_M(路径分段坐标组[i].x1, 路径分段坐标组[i].y1, 路径分段坐标组[i].z1) && 路径分段坐标组[i].已分配 == false)
				{
					分区方向 = 1;
					分段处理坐标 = 路径分段坐标组[i];
					路径分段坐标组[i].已分配 = true;
					break;
				}
				MyTrace(L"路径分段坐标组 %0.3f %0.3f %0.3f", 路径分段坐标组[i].x2, 路径分段坐标组[i].y2, 路径分段坐标组[i].z2);
				if (地图::指定地点是否可到达_M(路径分段坐标组[i].x2, 路径分段坐标组[i].y2, 路径分段坐标组[i].z2) && 路径分段坐标组[i].已分配 == false)
				{
					分区方向 = 2;
					分段处理坐标 = 路径分段坐标组[i];
					路径分段坐标组[i].已分配 = true;
					break;
				}
			}
			/*if (分段处理坐标.x1 == 0)
			{
				for (size_t i = 0; i < 路径分段坐标组.size(); i++)
				{
					MyTrace(L"路径分段坐标组2 %0.3f %0.3f %0.3f", 路径分段坐标组[i].x1, 路径分段坐标组[i].y1, 路径分段坐标组[i].z1);
					if (地图::指定地点是否可到达_M(路径分段坐标组[i].x2, 路径分段坐标组[i].y2, 路径分段坐标组[i].z2) && 路径分段坐标组[i].已分配 == false)
					{
						分区方向 = 2;
						分段处理坐标 = 路径分段坐标组[i];
						路径分段坐标组[i].已分配 = true;
						break;
					}
				}
			}*/
			//分段处理坐标 = 路径分段坐标组[0];
			MyTrace(L"获取到分段处理坐标 %0.3f %0.3f %0.3f 分区方向 %d", 分段处理坐标.x1, 分段处理坐标.y1, 分段处理坐标.z1, 分区方向);
			if (分段处理坐标.x1 == 0)
			{
				for (size_t i = 0; i < 录制坐标组.size(); i++)
				{
					MyTrace(L"录制坐标组 %0.3f %0.3f %0.3f", 录制坐标组[i].x1, 录制坐标组[i].y1, 录制坐标组[i].z1);
					if (地图::指定地点是否可到达_M(录制坐标组[i].x1, 录制坐标组[i].y1, 录制坐标组[i].z1) && 录制坐标组[i].已分配 == false)
					{
						分区方向 = 1;
						分段处理坐标 = 录制坐标组[i];
						//路径分段坐标组[i].已分配 = true;
						break;
					}
					MyTrace(L"路径分段坐标组 %0.3f %0.3f %0.3f", 录制坐标组[i].x2, 录制坐标组[i].y2, 录制坐标组[i].z2);
					if (地图::指定地点是否可到达_M(录制坐标组[i].x2, 录制坐标组[i].y2, 录制坐标组[i].z2) && 录制坐标组[i].已分配 == false)
					{
						分区方向 = 2;
						分段处理坐标 = 录制坐标组[i];
						//路径分段坐标组[i].已分配 = true;
						break;
					}
				}
				/*设置分段坐标已到达();
				路径分段坐标组.clear();*/
			}
		}

	}

}

bool 功能::移动打怪(float x, float y, float z, int 到达范围, int 打怪范围, int 距离自身范围, bool 优先清理击打道具, int 击打道具距离自身距离)
{
	if (环境::是否在和NPC对话())
	{
		环境::CALL_退出NPC();
	}
	if (击打道具距离自身距离 == 0)
	{
		击打道具距离自身距离 = 距离自身范围;
	}

	if (优先清理击打道具 == true)
	{
		//MyTrace(L"清理怪物");
		if (清理怪物(x, y, z, 0, 50) == false)
		{
			return false;
		}
		if (清理击打道具(x, y, z, 击打道具距离自身距离, 打怪范围) == false)
		{
			return false;
		}
	}
	//MyTrace(L"清理怪物2");
	if (清理怪物(x, y, z, 打怪范围, 距离自身范围) == false)
	{
		return false;
	}
	//MyTrace(L"清理击打道具");
	if (清理击打道具(x, y, z, 击打道具距离自身距离, 打怪范围) == false)
	{
		return false;
	}
	//MyTrace(L"拾取道具");
	if (拾取道具(1000) == false)
	{
		return false;
	}
	if (GetDis(x, y, z) <= 到达范围)
	{
		MyTrace(L"已到达指定地点 %0.3f %0.3f %0.3f", x, y, z);
		return true;
	}
	else
	{
		if (本人::是否在走路2())
		{
			Sleep(700);
			return false;
		}
		if (地图::指定地点是否可到达_M(x, y, z))
		{
			MyTrace(L"移动打怪 目标可达");
			if (分段处理坐标.x1 != 0 && 分段处理坐标.操作 == 2)
			{
				前往分段处理坐标(x, y, z);
			}
			else
			{
				设置分段坐标已到达();
				路径分段坐标组.clear();
				地图::本地图寻路(x, y, z, 0);
				Sleep(1000);
			}

		}
		else
		{
			MyTrace(L"前往分段处理");
			前往分段处理坐标(x, y, z);

		}

	}
	//MyTrace(L"移动打怪 结束");
	return false;
}

bool 功能::自动购买装备药水()
{
	int 地图ID = 地图::取地图ID();
	if (地图ID == 10811)
	{
		Equipinfo_ temp = 背包::get_EquipInfobyIndex(0);
		if (temp.颜色 != 3 && temp.物品等级 < 140)
		{

		}
		temp = 背包::get_EquipInfobyIndex(1);
		if (temp.颜色 != 3 && temp.物品等级 < 130)
		{

		}
	}
	return true;
}

bool 功能::签到领取邮件奖励()
{
	if (签到邮件::get_AttendanceList())
	{
		return false;
	}

	/*vector<MailInfo_>vsk;
	签到邮件::get_ExpressMailList(vsk);
	if (vsk.size() > 0)
	{*/
	for (size_t i = 0; i < 2; i++)
	{
		签到邮件::邮件领取();
		//Sleep(2000);
	}
	//return false;
//}
/*int 索引 = 签到邮件::getCurHotTimeEventIndex();
if (索引 != -1)
{
	签到邮件::Fun_hottimeEventRewardTake(索引);
	return false;
}*/
	return true;
}