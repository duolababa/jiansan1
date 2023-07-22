

// dllmain.cpp : 定义 DLL 应用程序的入口点。
// 本页面代码为固定写法，不需要改动。
#include "pch.h"
#include "luaFunc.h"
#include "ImGuiWin.h"
HWND                    g_hWnd = NULL;
HMODULE                 hOPMOUDULE;
WndProc_t               oWndProc;
tD3D11Present           oPresent;
ResizeBuffers           oResizeBuffers;
ID3D11Device* pDevice;
ID3D11DeviceContext* pContext;
IDXGISwapChain* pSwapChain;
ID3D11RenderTargetView* pRenderTargetView;
HHOOK                   g_HookRet;

bool mainBeginSate = TRUE;
bool bMouseCheck = FALSE;
//bool tab_bar_flags = TRUE;

#ifdef _WIN64
#define SELF_PTR LONG_PTR
#define WNDPROC_INDEX GWLP_WNDPROC
#else
#define SELF_PTR int
#define WNDPROC_INDEX GWL_WNDPROC
#endif

IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);


LRESULT CALLBACK hkWndProc_(int nCode, WPARAM wParam, LPARAM lparam)
{
    CWPSTRUCT* lpArg = (CWPSTRUCT*)lparam;//结构  hwnd message wParam lParam
    //DebugPrintf("我进来了\n");    
    if (nCode == HC_ACTION)//自己进程的消息
    {
        if (lpArg->hwnd == g_hWnd && lpArg->message == 注册消息值)//我们自己的消息  
        {
            switch (lpArg->wParam)
            {
                CallParam2* CanUseCALLParam2;
                CallParam4* CanUseCALLParam4;
                CallParam6* CanUseCALLParam6;
                CallParam8* CanUseCALLParam8;
                坐标_* 目标坐标;
            case Msgid::CallCanUse:// 4个参数的call调用
                //DebugPrintf("ID_通用CALL4当前线程%X", GetCurrentThreadId());				
                CanUseCALLParam4 = (CallParam4*)lpArg->lParam;
                CanUseCALLParam4->RetVal = CALL4(
                    CanUseCALLParam4->RCX,
                    CanUseCALLParam4->RDX,
                    CanUseCALLParam4->R8,
                    CanUseCALLParam4->R9,
                    CanUseCALLParam4->CALLAddr
                );
                return 1;
                break;
            case Msgid::CallCanUse1:// 6个参数的call调用               			
                CanUseCALLParam6 = (CallParam6*)lpArg->lParam;
                CanUseCALLParam6->RetVal = CALL6(
                    CanUseCALLParam6->RCX,
                    CanUseCALLParam6->RDX,
                    CanUseCALLParam6->R8,
                    CanUseCALLParam6->R9,
                    CanUseCALLParam6->第5参数,
                    CanUseCALLParam6->第6参数,
                    CanUseCALLParam6->CALLAddr
                );
                return 1;
                break;
            case Msgid::CallCanUse2:// 2个参数的call调用
                CanUseCALLParam2 = (CallParam2*)lpArg->lParam;
                CanUseCALLParam2->RetVal = CALL2(
                    CanUseCALLParam2->RCX,
                    CanUseCALLParam2->RDX,
                    CanUseCALLParam2->CALLAddr
                );
                return 1;
                break;
            case Msgid::CallCanUse3:// 6个参数的call调用               			
                CanUseCALLParam8 = (CallParam8*)lpArg->lParam;
                CanUseCALLParam8->RetVal = CALL8(
                    CanUseCALLParam8->RCX,
                    CanUseCALLParam8->RDX,
                    CanUseCALLParam8->R8,
                    CanUseCALLParam8->R9,
                    CanUseCALLParam8->第5参数,
                    CanUseCALLParam8->第6参数,
                    CanUseCALLParam8->第7参数,
                    CanUseCALLParam8->第8参数,
                    CanUseCALLParam8->CALLAddr
                );
                return 1;
                break;
            case Msgid::CallLua://lua脚本调用
               // RegLuaScript();
                return 1;
                break;

            case Msgid::Mouse:
                /*
                SendMessage(WM_CLOSE);    //关闭程序
                SendMessage(WM_SYSCOMMAND,SC_MINIMIZE,MAKELPARAM(point.x, point.y));   //最小化
                SendMessage(WM_SYSCOMMAND,SC_RESTORE,MAKELPARAM(point.x, point.y));   //恢复
                SendMessage(WM_SYSCOMMAND,SC_MAXIMIZE,MAKELPARAM(point.x, point.y));   //最大化
                */
                ::SendMessageA(g_hWnd, SC_MINIMIZE, MAKELPARAM(0, 0), 0);

                return 1;
                break;
            case Msgid::CALLCanArrive://lua脚本调用

                目标坐标 = (坐标_*)lpArg->lParam;
                //目标坐标->是否可达 = 地图::指定地点是否可到达(目标坐标->x, 目标坐标->y, 目标坐标->z);
                //int 返回值 = 目标坐标->是否可达;
                //目标坐标->是否可达 = 1000;
                //MyTrace(L"返回值 %d", 目标坐标->是否可达);
                return 1;
                // RegLuaScript();
                      //return 1;
                break;
            case Msgid::CALLExpeditionInRecv://远征队领取

                CanUseCALLParam2 = (CallParam2*)lpArg->lParam;
                成就领取::Fun_ExpeditionInRecv(CanUseCALLParam2->RDX);
                //int 返回值 = 目标坐标->是否可达;
                //目标坐标->是否可达 = 1000;
                //MyTrace(L"返回值 %d", 目标坐标->是否可达);
                return 1;
                // RegLuaScript();
                      //return 1;
                break;

            }

        }

    }

    return CallNextHookEx(g_HookRet, nCode, wParam, lparam);
}

HRESULT __stdcall hkResizeBuffers(IDXGISwapChain* This, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags)
{
    //解决窗口缩放的时候 游戏窗口崩溃的问题
    if (pRenderTargetView) {
        pContext->OMSetRenderTargets(0, 0, 0);
        pRenderTargetView->Release();
    }

    HRESULT hr = oResizeBuffers(This, BufferCount, Width, Height, NewFormat, SwapChainFlags);

    ID3D11Texture2D* pBuffer;
    This->GetBuffer(0, __uuidof(ID3D11Texture2D),
        (void**)&pBuffer);
    // Perform error handling here!

    pDevice->CreateRenderTargetView(pBuffer, NULL, &pRenderTargetView);
    // Perform error handling here!
    pBuffer->Release();

    pContext->OMSetRenderTargets(1, &pRenderTargetView, NULL);

    // Set up the viewport.
    D3D11_VIEWPORT vp;
    vp.Width = Width;
    vp.Height = Height;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    pContext->RSSetViewports(1, &vp);
    return hr;
}

HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyscInterval, UINT Flags)
{
    Helpers::UnHookFunction((PVOID*)(&oPresent), hkPresent);
    static bool isFirst = TRUE;
    if (isFirst)
    {
        isFirst = !isFirst;
        //得到游戏窗体
        if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)(&pDevice))))
            pDevice->GetImmediateContext(&pContext);

        ID3D11Texture2D* renderTargetTexture = nullptr;
        //获取缓冲区地址
        if (SUCCEEDED(pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (PVOID*)(&renderTargetTexture))))
        {
            //创建目标视图
            pDevice->CreateRenderTargetView(renderTargetTexture, NULL, &pRenderTargetView);

            //释放缓冲区
            renderTargetTexture->Release();
        }



        ImGui_ImplWin32_Init(g_hWnd);
        ImGui_ImplDX11_Init(pDevice, pContext);
        ImGui_ImplDX11_CreateDeviceObjects();


        DWORD ndThreadId = GetWindowThreadProcessId(g_hWnd, NULL);
        //WH_CALLWNDPROC
        if (ndThreadId != 0)  g_HookRet = SetWindowsHookEx(WH_CALLWNDPROC, hkWndProc_, NULL, ndThreadId);
        oWndProc = (WNDPROC)SetWindowLongPtr(g_hWnd, WNDPROC_INDEX, (LONG_PTR)hkWndProc);

    }

    ImGui_ImplDX11_NewFrame(); //创建dx11着色器 已经以及字体
    ImGui_ImplWin32_NewFrame();//获取当前系统鼠标 键盘 游戏手柄的信息
    ImGui::NewFrame();

    显示游戏IMGUI窗口(&mainBeginSate);

    ImGui::EndFrame();
    ImGui::SetWindowPos(u8"TestImGui", { 700.f,100.f });
    ImGui::Render();
    pContext->OMSetRenderTargets(1, &pRenderTargetView, NULL);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    HRESULT tmpAdrs = oPresent(pSwapChain, SyscInterval, Flags);
    Helpers::HookFunction((PVOID*)(&oPresent), hkPresent);
    return tmpAdrs;
}

// 程序入口后的线程开始处
BOOL WaitGameCreate(int inMaxTime)
{

    DWORD dwWndOfPid;
    DWORD dwMyid = GetCurrentProcessId();

    for (int i = 0; i < inMaxTime; i++)
    {
        Sleep(1000);

        HWND hGameWnd = FindWindowEx(NULL, NULL, _T("EFLaunchUnrealUWindowsClient"), NULL);
        if (hGameWnd == NULL) continue;
        for (;;)
        {

            GetWindowThreadProcessId(hGameWnd, &dwWndOfPid);

            //找到
            if (dwMyid == dwWndOfPid)
            {
                g_hWnd = hGameWnd;
                return TRUE;
            }

            hGameWnd = FindWindowEx(NULL, hGameWnd, _T("EFLaunchUnrealUWindowsClient"), NULL);
            if (hGameWnd == NULL) break;
        }

    }

    return FALSE;
}
void init_d3d11(void* data)
{
    MyTrace(L"init_d3d11");
    // 设置游戏的类名或者窗口标题，如果此函数被检测，可以更换其他方式获得窗口句柄。
    do
    {
        WaitGameCreate(1);
        //g_hWnd = Helpers::GetCurrentWindowHandle();//获取注入后的程序窗口句柄
        //g_hWnd = FindWindowA("EFLaunchUnrealUWindowsClient",NULL);
    } while (!g_hWnd);
    MyTrace(L"g_hWnd %X", g_hWnd);
    //交接链
    DXGI_SWAP_CHAIN_DESC scd;
    ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));
    scd.BufferCount = 1;
    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;//设置颜色格式为RGBA
    scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;//缩放比
    scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;//扫描线
    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;//渲染目标输出
    scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;//允许模式切换
    scd.OutputWindow = g_hWnd;//在目标窗口内部绘制另外一个窗口，本处确认目标窗口句柄
    scd.SampleDesc.Count = 1;//1重采样
    scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;//常用参数
    scd.Windowed = ((GetWindowLongPtr(g_hWnd, GWL_STYLE) & WS_POPUP) != 0) ? FALSE : TRUE; //是否全屏，随目标窗口变化而定
    scd.BufferDesc.Width = 1920;
    scd.BufferDesc.Height = 1080;
    scd.BufferDesc.RefreshRate.Numerator = 144; //刷新率
    scd.BufferDesc.RefreshRate.Denominator = 1; //分母
    scd.SampleDesc.Quality = 0;   //采样等级

    D3D_FEATURE_LEVEL featrueLevel = D3D_FEATURE_LEVEL_11_0;

    D3D11CreateDeviceAndSwapChain(
        NULL, D3D_DRIVER_TYPE_HARDWARE, NULL,
        NULL, &featrueLevel, 1, D3D11_SDK_VERSION,
        &scd, &pSwapChain, &pDevice, NULL, &pContext
    );
    SELF_PTR* pSwapChainVT = NULL;

    pSwapChainVT = (SELF_PTR*)*(SELF_PTR*)pSwapChain;
    oPresent = (tD3D11Present)(pSwapChainVT[8]);
    oResizeBuffers = (ResizeBuffers)(pSwapChainVT[13]);

    IMGUI_CHECKVERSION();

    ImGui::CreateContext();
    ImGuiIO& Io = ImGui::GetIO();

    //ImGui::StyleColorsDark();
    ImGui::StyleColorsClassic();
    //ImGui::StyleColorsLight();
    //LoadMyStype();

    //设置不生成imgui窗口位置存贮
    Io.WantSaveIniSettings = false;
    Io.IniFilename = NULL;

    ImFontConfig f_cfg;
    f_cfg.FontDataOwnedByAtlas = false;

    //字体加载
    //const ImFont* font = Io.Fonts->AddFontFromMemoryTTF((void*)baidu_font_data, baidu_font_size, 16.0f, &f_cfg, Io.Fonts->GetGlyphRangesChineseFull());
    const ImFont* font = Io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\simhei.ttf", 18.0f, NULL, Io.Fonts->GetGlyphRangesChineseFull());

    Helpers::HookFunction((PVOID*)(&oPresent), hkPresent);
    Helpers::HookFunction((PVOID*)(&oResizeBuffers), hkResizeBuffers);
}

void unLoad()
{
    //卸载主线程HOOK
    UnhookWindowsHookEx(g_HookRet);

    //卸载D3D11指针HOOK
    Helpers::UnHookFunction((PVOID*)(&oPresent), hkPresent);
    Helpers::UnHookFunction((PVOID*)(&oResizeBuffers), hkResizeBuffers);
}
unsigned int WINAPI 载入窗口函数2(void* parm)
{
    MyTrace(L"载入窗口函数2");
    while (true)
    {
        MyTrace(L"载入窗口函数1");
        Sleep(1000);
    }
    return 0;
}
// 程序入口
HWND  GetCurrentHwnd();

WNDPROC oldGameWndProc = NULL;

//LRESULT CALLBACK 协议解析_1088(HWND hWnd, UINT wMsg, WPARAM wParam, LPARAM lParam);

//LRESULT CALLBACK GameMainWndProc(HWND hWnd, UINT wMsg, WPARAM wParam, LPARAM lParam)
//{
//    char buf[512];
//    DWORD tid = GetCurrentThreadId();
//    sprintf_s(buf, "RicardoExe GameMainWndProc(%p,%X,%zx,%zx) tid=<%d,%x>\n", hWnd, wMsg, wParam, lParam, tid, tid);
//    OutputDebugStringA(buf);
//    if (wMsg == WM_USER + 10088)
//    { //自己的指令 暂时执行不到
//        {
//            DWORD	游戏PID = GetGameProcesssID();
//            DWORD	当前PID = GetCurrentProcessId();
//
//
//            DWORD 当前线程ID = GetCurrentThreadId();
//            DWORD 当前游戏主线程 = GetGameThreadId();
//            if (当前线程ID == 当前游戏主线程)
//            {
//                return 协议解析_1088(hWnd, wMsg, wParam, lParam);
//            }
//
//        }
//        return 1;
//    }
//    return CallWindowProc(oldGameWndProc, hWnd, wMsg, wParam, lParam);
//};


BOOL 挂接主线程()
{
    DWORD ndThreadId = GetWindowThreadProcessId(g_hWnd, NULL);
    //WH_CALLWNDPROC
    if (ndThreadId != 0)
    {
        g_HookRet = SetWindowsHookEx(WH_CALLWNDPROC, hkWndProc_, NULL, ndThreadId);
    }
    else
    {
        MyTrace(L"挂接失败 未获取到ndThreadId");
    }
    oWndProc = (WNDPROC)SetWindowLongPtr(g_hWnd, WNDPROC_INDEX, (LONG_PTR)hkWndProc);




    return false;
}

BOOL 卸载主线程()
{
    HWND h = GetCurrentHwnd();
    if (h /*&& oldGameWndProc*/)
    {
        UnhookWindowsHookEx(g_HookRet);
        (WNDPROC)SetWindowLongPtrA(g_hWnd, GWLP_WNDPROC, (LONG_PTR)oWndProc);// GWL_WNDPROC, 0);
        oWndProc = NULL;

        return true;
    }
    return false;
}
DWORD __stdcall WorkThread(LPVOID lpram)
{

    TCHAR 当前进程名[MAX_PATH];
    GetCurrentProcessName(当前进程名);
    DWORD 游戏PID = GetGameProcesssID();
    DWORD 当前PID = GetCurrentProcessId();
    if (_tcsicmp(当前进程名, _T("LOSTARK.exe")) == 0) //要注入那个条件的进程 忽略大写比较
    {
        int inum = 0;
        {
            DWORD 当前线程ID = GetCurrentThreadId();
            DWORD 当前游戏主线程 = GetGameThreadId();
            挂接主线程();
        }
        return 0;
    }

    return 0;
}

class 吃药Thread : public CXThread
{
public:
    virtual BOOL Run()
    {
        //SetHardwareBreakPointoffWIN10Version(MainThreadid);

        while (循环跳出 == false)
        {
            ActorInfo_ 角色信息 = 本人::取角色信息();
            if (角色信息.当前血 <= 0)
            {
                Sleep(2000);
                continue;
            }
            double 血量百分比 = ((double)角色信息.当前血 / (double)角色信息.最大血) * 100;
            if (血量百分比 <= 75)
            {
                if (背包::返回指定物品数量(0x2E63E) > 0)
                {
                    背包::使用背包指定物品_ByResId(0x2E63E);
                    Sleep(1000);
                    continue;
                }
                if (背包::返回指定物品数量(0x2E63D) > 0)
                {
                    背包::使用背包指定物品_ByResId(0x2E63D);
                    Sleep(1000);
                    continue;
                }
                if (背包::返回指定物品数量(0x2E63C) > 0)
                {
                    背包::使用背包指定物品_ByResId(0x2E63C);
                    Sleep(1000);
                    continue;
                }
                if (背包::返回指定物品数量(0x2E63B) > 0)
                {
                    背包::使用背包指定物品_ByResId(0x2E63B);
                    Sleep(1000);
                    continue;
                }
                if (背包::返回指定物品数量(0x2E63A) > 0)
                {
                    背包::使用背包指定物品_ByResId(0x2E63A);
                    Sleep(1000);
                    continue;
                }

            }
            Sleep(1000);
        }
        return TRUE;
    }
};
吃药Thread 吃药线程;
DWORD MainThreadid = 0;
class CMyThread2 : public CXThread
{
public:
    virtual BOOL Run()
    {
        //SetHardwareBreakPointoffWIN10Version(MainThreadid);
        if (0)
        {
            SetHardwareBreakPointWIN10Version(MainThreadid);
        }
        //签到邮件::邮件领取();
       //SetHardwareBreakPointWIN10Version(MainThreadid);
        //SetSehHook();
        //init_d3d11(NULL);
        clock_t 测试时间 = 取启动时间();
        clock_t 判断技能加点时间 = 0;
        clock_t 判断推荐装备时间 = 0;
        clock_t 判断背包物品处理时间 = 0;
        clock_t 判断成就签到奖励处理时间 = 0;
        clock_t 判断邮件领取 = 0;
        bool 判断签到邮件领取 = false;
     /*   CString temp;
        temp.Format(L"%d", GetCurrentProcessId());
        SendMessageToMoConter(121, temp);*/
        MyTrace(L"开始");
        lua_State* L = initLua();
        MyTrace(L"开始1");
        RegLuaScript(L);
        MyTrace(L"进入循环");
        while (循环跳出 == false)
        {
            MyTrace(L"----------------------------程序头部----------------------------");
            // int 判断界面 = UI功能::getGameCurStageValue();
            if (游戏::Pass各种窗口() == true)
            {
                Sleep(500);
                continue;
            }
            DWORD 界面状态 = UI功能::getGameCurStageValue();
            MyTrace(L"界面状态:%d 是否加载中 %d", 界面状态, 环境::是否在加载页面2());
            if (界面状态 == 3)
            {
                MyTrace(L"服务器界面");
                if (登陆::是否出现确认协议())
                {
                    MyTrace(L"确认协议");
                    登陆::CALL_确认协议();
                    Sleep(500);
                    continue;
                }

                if (登陆::是否在服务器界面() == false)
                {
                    SendMessageToMoConter(122, L"无服务器列表");
                    Sleep(1000);
                    MyTrace(L"未读取到服务器列表");
                    continue;
                }
                else
                {
                    if (登陆::CALL_选择服务器(配置服务器))
                    {
                        MyTrace(L"进入 %s", 配置服务器);
                    }
                    else
                    {
                        SendMessageToMoConter(122, L"无服务器列表");
                    }
                    Sleep(10000);
                    continue;
                }
                continue;
            }
            else if (界面状态 == 5)
            {
                if (登陆::是否在准备界面())
                {
                    SendMessageToMoConter(122, L"进入服务器成功");
                    vector<登陆角色信息_> vsk;
                    登陆::get_CharacterList(vsk);
                    if (vsk.size() > 0)
                    {
                        登陆角色信息_ temp = 登陆::getCharacterInfoByIndex(_ttoi(角色序号) - 1);
                        if (temp.名称 != L"")
                        {
                            登陆::CALL_进入游戏(temp.dIndex);
                            MyTrace(L"进入游戏 %d %s", temp.dIndex, temp.名称);
                            Sleep(20000);
                            continue;
                        }
                        else
                        {
                            MyTrace(L"打开[%d]号创建角色界面", _ttoi(角色序号));
                            登陆::CALL_打开创建角色(_ttoi(角色序号) - 1);
                            Sleep(2000);
                            continue;
                        }
                    }
                    else
                    {
                        MyTrace(L"打开[1]号创建角色界面");
                        登陆::CALL_打开创建角色(0);
                        Sleep(2000);
                        continue;
                    }

                }
                if (登陆::是否在选择职业界面())
                {
                    登陆::CALL_选择职业(L"魔法师");
                    MyTrace(L"选择职业界面");
                    Sleep(8000);
                    continue;
                }
                if (登陆::是否在创建角色界面())
                {
                    MyTrace(L"创建角色界面");
                    登陆::CALL_创建角色(1);
                    Sleep(8000);
                    continue;
                }
                continue;
            }
            else if (界面状态 == 9)
            {
                DWORD 地图ID = 地图::取地图ID();
                if (地图ID != 0 && !环境::是否在加载页面2())
                {
                    MyTrace(L"大陆ID %d 当前地图ID %d ", 地图::取当前大陆ID(), 地图::取地图ID());

                    if (脚本任务 == L"筛选签到箱子")
                    {
                        if (UI功能::经验条界面是否显示())
                        {
                            for (size_t i = 0; i < 2; i++)
                            {
                                签到邮件::邮件领取();

                            }
                            int 箱子数量 = 背包::返回指定物品数量(0x26BB5B5);
                            if (箱子数量 >= 5) //Honing Leapstone Selection Chest II 淬火突破石选择箱
                            {
                                SendMessageToMoConter(778, L"签到完成 箱子" + 整数到文本(箱子数量));
                            }
                            else
                            {
                                SendMessageToMoConter(778, L"签到未完成 箱子" + 整数到文本(箱子数量));
                            }
                        }

                        Sleep(5000);
                        continue;
                    }
                    if (脚本任务 == L"签到")
                    {
                        //MyTrace(L"角色动作值 %d", 本人::取角色信息().当前动作);
                        ActorInfo_ 角色信息 = 本人::取角色信息();
                        /*  if (角色信息.等级 >= 11)
                          {
                              if (UI功能::经验条界面是否显示())
                              {
                                  if (功能::签到领取邮件奖励())
                                  {
                                      SendMessageToMoConter(777, 脚本任务);
                                      MyTrace(L"签到已完成,通知控制台");
                                  }
                              }
                          }
                          else
                          {*/
                        if (取启动时间() - 判断推荐装备时间 >= 10 * 1000)
                        {
                            MyTrace(L"自定装备推荐装备处理开始");
                            背包::自定装备推荐装备();
                            MyTrace(L"自定装备推荐装备处理结束");
                            判断推荐装备时间 = 取启动时间();
                        }
                        if (取启动时间() - 判断背包物品处理时间 >= 15 * 1000)
                        {
                            MyTrace(L"背包物品处理开始");
                            背包::背包物品处理();
                            MyTrace(L"背包物品处理完毕");
                            判断背包物品处理时间 = 取启动时间();
                        }
                        QuestInfo_ 主线任务 = 任务::取出主线任务();
                        MyTrace(L"Type:%d QuestID:%d QuestName:%s 阶段:%d  状态:%d 当前地图ID:%d 子任务数量:%d 主线任务目标:%d 操作:%s", 主线任务.dType, 主线任务.dQuestId, 主线任务.QuestName, 主线任务.dStep, 主线任务.dState, 地图::取地图ID(), 主线任务.子任务进度.size(), 主线任务.TargetId, 主线任务.QuestOption);


                        if (功能::开启传送点())
                        {
                            MyTrace(L"4");
                            if (游戏::执行触发任务())
                            {
                                if (!游戏::执行副本任务())
                                {
                                    Sleep(500);
                                    continue;
                                }
                                MyTrace(L"3");
                                if (游戏::执行支线任务())
                                {
                                    if (!游戏::执行紫色任务())
                                    {
                                        Sleep(500);
                                        continue;
                                    }
                                    MyTrace(L"2");
                                    if (游戏::执行指引任务())
                                    {

                                        MyTrace(L"1");
                                        QuestInfo_ 主线任务 = 任务::取出主线任务();
                                        MyTrace(L"Type:%d QuestID:%d QuestName:%s 阶段:%d  状态:%d 当前地图ID:%d 子任务数量:%d 主线任务目标:%d 操作:%s", 主线任务.dType, 主线任务.dQuestId, 主线任务.QuestName, 主线任务.dStep, 主线任务.dState, 地图::取地图ID(), 主线任务.子任务进度.size(), 主线任务.TargetId, 主线任务.QuestOption);
                                        if (游戏::主线_序章(主线任务))
                                        {
                                            if (UI功能::经验条界面是否显示())
                                            {
                                                if (功能::签到领取邮件奖励())
                                                {
                                                    SendMessageToMoConter(777, 脚本任务);
                                                    MyTrace(L"签到已完成,通知控制台");
                                                }
                                            }
                                        }
                                        /*游戏::主线_莱文哈特罗格尔(主线任务);
                                        游戏::主线_安格莫斯山麓(主线任务);*/
                                    }
                                }
                            }
                        }
                        //}


                        Sleep(5000);
                        continue;

                    }
                    if (脚本任务 == L"主线1-50")
                    {
                        if (!判断签到邮件领取)
                        {
                            /*签到邮件::get_AttendanceList();
                            Sleep(500);
                            签到邮件::邮件领取();*/
                            if (UI功能::经验条界面是否显示())
                            {
                                MyTrace(L"领取奖励");
                                if (功能::签到领取邮件奖励() == true)
                                {
                                    判断签到邮件领取 = true;
                                }
                                continue;
                            }


                        }
                        ActorInfo_ 角色信息 = 本人::取角色信息();
                        double 血量百分比 = ((double)角色信息.当前血 / (double)角色信息.最大血) * 100;
                        坐标_ 角色坐标 = 本人::取坐标();
                        MyTrace(L"角色坐标 %0.3f,%0.3f,%0.3f", 角色坐标.x, 角色坐标.y, 角色坐标.z);
                        MyTrace(L"取角色信息 等级%d 名称 %s 动作值 %d 举起状态%d  血量百分比%d", 角色信息.等级, 角色信息.名称, 角色信息.当前动作, 角色信息.举起状态, 血量百分比);
                        //vector<objInfo_>环境对象数组;
                        //环境::遍历全部环境对象(环境对象数组);
                        //MyTrace(L"遍历全部环境对象 数量%d", 环境对象数组.size());
                        //for (size_t i = 0; i < 环境对象数组.size(); i++)
                        //{
                        //    MyTrace(L"距离 %d 全对象 0x%I64X Type: %d, 名称:%s modid:%d resid:%d 是否隐藏:%d 是否敌人:%d HP:%d/%d 击打道具是否死亡 %d dResShow %d dResDead %d 坐标 %0.3f,%0.3f,%0.3f",
                        //        距离计算(角色坐标.x, 角色坐标.y, 角色坐标.z, 环境对象数组[i].坐标.x, 环境对象数组[i].坐标.y, 环境对象数组[i].坐标.z), 环境对象数组[i].objBase, 环境对象数组[i].dType, 环境对象数组[i].wName, 环境对象数组[i].ModId, 环境对象数组[i].dResId, 环境对象数组[i].IsHide, 环境对象数组[i].IsEnemy, 环境对象数组[i].dCurHp, 环境对象数组[i].dMaxHp, 环境::击打道具是否死亡(环境对象数组[i].objBase), 环境对象数组[i].dResShow, 环境对象数组[i].dIsDead, 环境对象数组[i].坐标.x, 环境对象数组[i].坐标.y, 环境对象数组[i].坐标.z);
                        //}
                        if (本人::获取InteractPropState状态() != 0)
                        {
                            Sleep(500);
                            continue;
                        }
                        //if (取启动时间() - 判断技能加点时间 >= 5 * 1000)
                        //{
                        //    if (角色信息.等级 >= 10)
                        //    {
                        //        MyTrace(L"判断技能加点时间1");
                        //        技能::摆放与学习技能();
                        //        判断技能加点时间 = 取启动时间();
                        //    }

                        //}
                        if (取启动时间() - 判断推荐装备时间 >= 10 * 1000)
                        {
                            MyTrace(L"自定装备推荐装备处理开始");
                            背包::自定装备推荐装备();
                            MyTrace(L"自定装备推荐装备处理结束");
                            判断推荐装备时间 = 取启动时间();
                        }
                        if (取启动时间() - 判断背包物品处理时间 >= 15 * 1000)
                        {
                            MyTrace(L"背包物品处理开始");
                            背包::背包物品处理();
                            MyTrace(L"背包物品处理完毕");
                            判断背包物品处理时间 = 取启动时间();
                        }
                        if (取启动时间() - 判断成就签到奖励处理时间 >= 5 * 60 * 1000)
                        {
                            MyTrace(L"远征队奖励判断");
                            if (角色信息.等级 >= 10)
                            {
                                成就领取::getExpeditionInfo();
                                MyTrace(L"大陆书奖励判断");
                                成就领取::get_BookListInfo();
                            }
                            // MyTrace(L"邮件领取");
                            判断成就签到奖励处理时间 = 取启动时间();

                        }
                        if (取启动时间() - 判断邮件领取 >= 0.5 * 60 * 1000)
                        {

                            MyTrace(L"邮件领取");
                            功能::签到领取邮件奖励();
                            判断邮件领取 = 取启动时间();
                        }
                        //MyTrace(L"测试开始");
                        //MyTrace(L"角色动作值 %d", 本人::取角色信息().当前动作);
                        //MyTrace(L"测试结束");
                        //continue;
                      // 环境::获取对象释放技能组(本人::取真实对象());
                        MyTrace(L"修理装备");
                        if (NPC商店::修理装备())
                        {
                            MyTrace(L"存在需要修理的装备和修理工");
                            Sleep(500);
                            continue;
                        }
                        MyTrace(L"补充药水");
                        if (NPC商店::补充药水())
                        {
                            MyTrace(L"需要补充药水");
                            Sleep(500);
                            continue;
                        }

                        MyTrace(L"5");
                        if (功能::开启传送点())
                        {
                            /*  Sleep(500);
                              continue;*/
                            MyTrace(L"4");
                            if (游戏::执行触发任务())
                            {
                                if (!游戏::执行副本任务())
                                {
                                    Sleep(500);
                                    continue;
                                }
                                MyTrace(L"3");
                                if (游戏::执行支线任务())
                                {
                                    if (!游戏::执行紫色任务())
                                    {
                                        Sleep(500);
                                        continue;
                                    }
                                    MyTrace(L"2");
                                    if (游戏::执行指引任务())
                                    {

                                        MyTrace(L"1");
                                        QuestInfo_ 主线任务 = 任务::取出主线任务();
                                        MyTrace(L"Type:%d QuestID:%d<%I64X> QuestName:%s 阶段:%d  状态:%d 当前地图ID:%d 子任务数量:%d 主线任务目标:%d 操作:%s", 主线任务.dType, 主线任务.dQuestId, 主线任务.dQuestId, 主线任务.QuestName, 主线任务.dStep, 主线任务.dState, 地图::取地图ID(), 主线任务.子任务进度.size(), 主线任务.TargetId, 主线任务.QuestOption);
                                        游戏::主线_序章(主线任务);
                                        游戏::主线_莱文哈特罗格尔(主线任务);
                                        游戏::主线_安格莫斯山麓(主线任务);
                                        游戏::主线_国境地带(主线任务);
                                        游戏::主线_萨尔兰德丘陵(主线任务);
                                        游戏::主线_奥兹霍丘陵(主线任务);
                                        游戏::主线_扎格拉斯山(主线任务);
                                        游戏::主线_雷科巴(主线任务);
                                        游戏::主线_梅德里克修道院(主线任务);
                                        游戏::主线_比尔布森林(主线任务);
                                        游戏::主线_激战平原(主线任务);
                                        游戏::主线_卢特兰城(主线任务);
                                        游戏::主线_迪奥利卡平原(主线任务);
                                        游戏::主线_圆虹之丘(主线任务);
                                        游戏::主线_梨树栖息地(主线任务);
                                        游戏::主线_黑玫瑰教堂(主线任务);
                                        游戏::主线_拉伊亚阶地(主线任务);
                                        游戏::主线_博伦亚领地(主线任务);
                                        游戏::主线_鬃波港(主线任务);
                                        游戏::主线_科罗克尼斯渔村(主线任务);
                                        游戏::世界1(主线任务);
                                        游戏::世界2(主线任务);
                                        游戏::世界3(主线任务);
                                        游戏::世界4(主线任务);
                                        /*if (!游戏::执行世界任务())
                                        {
                                            Sleep(500);
                                            continue;
                                        }*/
                                    }

                                }
                            }

                        }
                        Sleep(400);
                        continue;
                    }
                    if (脚本任务 == L"跑岛")
                    {
                        if (LUA脚本名称 != L"")
                        {
                            if (Lua开关 == true)
                            {
                                CStringA aa(LUA脚本名称);
                                const char* LUA脚本名称bb = aa;
                                if (!执行lua(L, LUA脚本名称bb))
                                {
                                    break;
                                }
                            }
                            else
                            {
                                SendMessageToMoConter(111, L"Lua开关=未开启");
                                Sleep(5000);
                            }

                            //string str(LUA脚本名称.GetString());
                        }
                        else
                        {
                            Sleep(5000);
                            SendMessageToMoConter(111, L"LUA脚本名称=空");
                        }

                    }
                    else
                    {
                        if (LUA脚本名称 != L"")
                        {
                            //MyTrace(L"Lua开关 %d", Lua开关);
                            if (Lua开关 == true)
                            {
                                // string str = CStringA(LUA脚本名称);
                                 //char* aa = LUA脚本名称.GetBuffer();
                                CStringA aa(LUA脚本名称);
                                //const char* LUA脚本名称bb = "D:\\起号.lua";
                                //MyTrace(L"LUA脚本名称 %s", aa);
                                if (!执行lua(L, aa))
                                {
                                    break;
                                }
                                Sleep(2000);
                                break;
                            }
                            else
                            {
                                SendMessageToMoConter(110, L"Lua开关=未开启");
                                Sleep(5000);
                            }

                            //string str(LUA脚本名称.GetString());
                        }
                        else
                        {
                            Sleep(5000);
                            SendMessageToMoConter(111, L"LUA脚本名称=空");
                        }
                    }
                }
                continue;
            }
            else
            {
                MyTrace(L"未知状态页面");
                Sleep(5000);
            }







            // MyTrace(L"LOASTARK newbee");
            //vector<objInfo_>环境对象数组;
            //环境::遍历怪物(环境对象数组);
            //for (size_t i = 0; i < 环境对象数组.size(); i++)
            //{
            //    测试打怪(环境对象数组[i].objBase);
            //    MyTrace(L"怪物 0x%I64X Type: %d, 名称:%s modid:%d id:%d 是否隐藏:%d 是否敌人:%d HP:%d/%d", 环境对象数组[i].objBase, 环境对象数组[i].dType, 环境对象数组[i].wName, 环境对象数组[i].ModId, 环境对象数组[i].dObjId, 环境对象数组[i].IsHide, 环境对象数组[i].IsEnemy, 环境对象数组[i].dCurHp, 环境对象数组[i].dMaxHp);

            //    break;
            //}
            ////MyTrace(L"LOASTARK newbee");
            Sleep(200);
        }
        lua_close(L);
        if (0)
        {
            SetHardwareBreakPointoffWIN10Version(MainThreadid);
        }
        else
        {
            char 校验[] = { 0xE8 };
            写内存字节集((HANDLE)-1, (LPVOID)(游戏模块 + 基址_鼠标_鼠标写入地址), LPVOID(&校验), 1);
        }
        SendMessageToMoConter(113, L"线程跳出");
        MyTrace(L"跳出循环");
        卸载主线程();
        return TRUE;
    }
};
CMyThread2 mythread2;


class CMyThread3 : public CXThread
{
public:
    virtual BOOL Run()
    {
        while (循环跳出 == false)
        {
            坐标_ 角色坐标 = 本人::取坐标();

            int 距离1 = 距离计算3(角色坐标.x, 角色坐标.y, 角色坐标.z, 8191.94, 4970.83, 4745.49);
            int 距离2 = 距离计算3(角色坐标.x, 角色坐标.y, 角色坐标.z, 8635.85, 5583.67, 4745.52);
            int 距离3 = 距离计算3(角色坐标.x, 角色坐标.y, 角色坐标.z, 8473, 4514.11, 4740.89);
            int 距离4 = 距离计算3(角色坐标.x, 角色坐标.y, 角色坐标.z, 8789, 4497, 4744.95);
            int 距离5 = 距离计算3(角色坐标.x, 角色坐标.y, 角色坐标.z, 8470, 6036, 4744.55);

            MyTrace(L"角色坐标 %0.3f  %0.3f  %0.3f    距离1 %d    距离2  %d   距离3  %d", 角色坐标.x, 角色坐标.y, 角色坐标.z, 距离1, 距离2, 距离3);
            MyTrace(L"角色坐标 %0.3f  %0.3f  %0.3f    安全点距离1 %d    安全点距离2  %d  ", 角色坐标.x, 角色坐标.y, 角色坐标.z, 距离4, 距离5);

            Sleep(200);
        }
        return true;
    }
};

CMyThread3 mythread3;

LRESULT __stdcall hkWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    //if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam)) return true;
    if (uMsg == WM_KEYDOWN)
    {
        if (wParam == VK_END) //呼出
        {
      
                MyTrace(L"调试开关=1");
            调试开关 = 1;

            循环跳出 = true;
            return true;
        }
        if (wParam == VK_HOME)
        {
            调试开关 = 0;
            MyTrace(L"调试开关=0");
            //SetHardwareBreakPointWIN10Version(MainThreadid);
           /* 坐标_ 角色坐标 = 本人::取坐标();
            vector<objInfo_>vsk;
            环境::遍历传送门(vsk);
            for (size_t i = 0; i < vsk.size(); i++)
            {
                MyTrace(L"传送门 0x%I64x ,ID:%d 坐标:%0.3f,%0.3f,%0.3f 距离 %0.3f 相对于角色角度 %d", vsk[i].objBase, vsk[i].dResId, vsk[i].坐标.x, vsk[i].坐标.y, vsk[i].坐标.z, vsk[i].fDis, DWORD(Get_Rel_Angle(角色坐标.x, 角色坐标.y, vsk[i].坐标.x, vsk[i].坐标.y)*0.00549317));
            }*/
            /* 循环跳出 = false;
             mythread2.Start();*/
            return true;
        }
        if (wParam == VK_F3)
        {

        }
    }
    if (uMsg == 0x9999)
    {
        if (wParam == 0x1) //
        {
            Lua开关 = true;
            return true;
        }
        if (wParam == 0x2) //
        {
            Lua开关 = false;
            return true;
        }
        if (wParam == 0x3) //
        {
            脚本任务 = 配置::获取指定设置文本(L"脚本配置.ini", L"测试窗口", L"脚本任务");
            CString 脚本 = 配置::获取指定设置文本(L"脚本配置.ini", L"测试窗口", L"LUA脚本");
            if (脚本.Find(L".lua") != -1)
            {
                //Lua开关 = true;
                LUA脚本名称 = 脚本;
            }
            return true;
        }
    }
    // 拦截鼠标消息不发送到游戏窗口
    switch (uMsg)
    {

        /* case WM_LBUTTONDOWN: case WM_LBUTTONDBLCLK:
         case WM_RBUTTONDOWN: case WM_RBUTTONDBLCLK:
         case WM_MBUTTONDOWN: case WM_MBUTTONDBLCLK:
         case WM_XBUTTONDOWN: case WM_XBUTTONDBLCLK:
         case WM_MOUSEWHEEL: case WM_MOUSEHWHEEL:
         case WM_MOUSEMOVE:case WM_MOUSELEAVE:
         case WH_MOUSE:case WH_MOUSE_LL:*/
         // return true;
        if (b鼠标消息影响游戏) return true;
    }

    // 我们自己的消息类型处理
    return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}
wchar_t* 尾5[] = { L"jan",L"feb",L"mar",L"apr",L"may",L"jun",L"jul",L"aug",L"sept",L"oct",L"nov",L"dec" };
wchar_t* 尾6[] = { L"mon",L"tues",L"wed",L"thur",L"fri",L"sat",L"sun" };
wchar_t* 尾7[] = { L"spr",L"sum",L"aut",L"win" };
wchar_t* 尾8[] = { L"east",L"west",L"nort",L"sort" };
BOOL APIENTRY DllMain(HMODULE hModule, DWORD  reason_call, LPVOID lpReserved)
{
    switch (reason_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        // 优化dll线程
        DisableThreadLibraryCalls(hModule);
        //   MyOutputDebugStringW(L"隐藏前");
        //   XHideDll::PrintModuleList();
        //XHideDll::HideInLoadOrderLinks(hModule);
        //XHideDll::HideInMemoryOrderLinks(hModule);
        //XHideDll::HideInInitializationOrderLinks(hModule);
        //MyOutputDebugStringW(L"隐藏后");
        //XHideDll::PrintModuleList();
        DWORD 当前PID = GetCurrentProcessId();
        TCHAR 当前进程名[MAX_PATH];
        GetCurrentProcessName(当前进程名);
        MyTrace(L"Ricardogame64加载:%s ->  PID=%d>> exe=%s line=%d\n", UTF82WCS( __FUNCDNAME__), 当前PID, 当前进程名, __LINE__);
        if (WaitGameCreate(160) == true)
        {
            OutputDebugStringW(L"挂接主线程");
            挂接主线程();
        }
        GameIndex = _ttoi(getCommandIndex());
        if (GameIndex >= 1 && GameIndex <= 40)
        {
            配置::读取脚本配置();
        }
        else
        {
            脚本任务 = 配置::获取指定设置文本(L"脚本配置.ini", L"测试窗口", L"脚本任务");
            CString 脚本 = 配置::获取指定设置文本(L"脚本配置.ini", L"测试窗口", L"LUA脚本");
            if (脚本.Find(L".lua") != -1)
            {
                // Lua开关 = true;Lua开关 = true;
                LUA脚本名称 = 脚本;
            }
        }

        游戏模块 = (UINT64)GetModuleHandleA("LOSTARK.exe");
        游戏模块_EFEngine = (UINT64)GetModuleHandleA("EFEngine.dll");
        g_dwBreakpoint = 游戏模块 + 基址_鼠标_鼠标写入地址;
        //g_dwBreakpoint2 = 游戏模块 + 基址_鼠标_鼠标写入地址2;
        //g_dwBreakpoint2 = 游戏模块 + 基址_登录_选择职业call + 0x6A;
        注册消息值 = RegisterWindowMessageA("ARKMsg");
        if (1)
        {
            /* CString cmdstr= GetCommandLineW();
             MyTrace(L"Cmd %s", cmdstr);*/
         //   脚本任务 = L"主线1-50";
            脚本任务 = L"lua";
            Lua开关 = true;
            MyTrace(L"脚本任务%s",脚本任务);
            //脚本任务 = L"签到";
            LUA脚本名称 = L"D:\\起号.lua";
            配置服务器 = L"Mari";
            角色序号 = L"1";
            MainThreadid = GetCurrentThreadId();
            AddVectoredExceptionHandler(1, (PVECTORED_EXCEPTION_HANDLER)ExceptionHandler);
            mythread2.Start();
             吃药线程.Start();
        }
        else
        {
            //地图::传送(0xBBA60);
            //oid UI功能::getNpcTalkSelectList(vector<CString>&对话组)
            //mythread3.Start();
            //************判断任务****************
            //QuestInfo_ 触发任务 = 任务::取出触发任务();
            //QuestInfo_ 主线任务 = 任务::取出副本任务();
            //QuestInfo_ 可接指引 = 任务::取出可接指引任务();
            //QuestInfo_ 主线任务2 = 任务::取出主线任务();
            //MyTrace(L"触发任务 %d 主线任务 %d 可接指引 %d 主线任务2 %d<%I64X>", 触发任务.dQuestId, 主线任务.dQuestId, 可接指引.dQuestId, 主线任务2.dQuestId, 主线任务2.dQuestId);
            //vector<DWORD>vsk;
            //任务::get_FinishQuestList(vsk);
            //for (int i = 0;  i < vsk.size(); i++)
            //{
            //    MyTrace(L"get_FinishQuestList %d",vsk[i]);
            //}
            //MyTrace(L"get_FinishQuestList done");
            //************判断任务 done****************

            //UI功能::getMsgBoxTextList();
            //背包::自定装备推荐装备();
           /* vector<objInfo_>击打道具数组;
            环境::遍历击打道具(击打道具数组);
            MyTrace(L"击打道具数组 %d ", 击打道具数组.size());*/
            // 环境::CALL_退出NPC();
          /*  lua_State* L = initLua();
            RegLuaScript(L);
            string str = CStringA(LUA脚本名称);
            if (!执行lua(L, str))
            {
            }*/
            // RegLuaScript();
             /*vector<CString>vsk;
             登陆::服务器遍历(vsk);
             for (size_t i = 0; i < vsk.size(); i++)
             {
                 MyTrace(L"%s", vsk[i]);
             }*/
             /* UI功能::Fun_NarrationAssistance_OnOff(1);
              UI功能::Fun_NarrationAssistance_Continue();*/
              //MyCallFun::test();
              //MyTrace(L"开始测试");
              //MyTrace(L"判断是否加载中 %d", 环境::是否在加载页面2());
              //登陆::CALL_创建角色(1);;
              //登陆::CALL_打开创建角色(1);
              //RegLuaScript();
             // 技能::自动升级女巫技能();
              //研磨::getItemBuildUpItemList();
              //诞生石::getmarbleWndItemList();
             // 技能::自动升级女巫技能();
             // 环境::CALL_退出NPC();
          /*  MyTrace(L"大陆ID %d 当前地图ID %d ", 地图::取当前大陆ID(), 地图::取地图ID());
            坐标_ 角色坐标 = 本人::取坐标();
            MyTrace(L"角色坐标 %0.3f  %0.3f  %0.3f", 角色坐标.x, 角色坐标.y, 角色坐标.z);
            ActorInfo_ 角色信息 = 本人::取角色信息();
            MyTrace(L"角色名称%s 等级%d 坐标%0.3f,%0.3f,%0.3f 血量%d/%d 装评 %d", 角色信息.名称, 角色信息.等级, 角色信息.坐标.x, 角色信息.坐标.y, 角色信息.坐标.z, 角色信息.当前血, 角色信息.最大血, 角色信息.装备评分);*/


            //QuestInfo_ 主线任务 = 任务::取出主线任务();
            //MyTrace(L"主线任务 %s ，第 %d 步 ", 主线任务.QuestName, 主线任务.dStep);
            //坐标_ 本人 = 本人::取坐标();
            //if (本人.x > -28600 && 本人.x < -23700 && 本人.y >-7300 && 本人.y < -4153 && 本人.z >500 && 本人.z < 800)
            //{
            //    MyTrace(L"1111");
            //    功能::移动打怪(-28601, -3714, 1170.999878, 0, 2000, 300, true, 100);//1
            //}


            //vector<ShortCutInfo_>vsk;
            //技能::get_SkillShortList(vsk);
            //for (size_t i = 0; i < vsk.size(); i++)
            //{
            //    MyTrace(L"Page %d 键位 %d 技能ID %d 是否冷却 %d 技能状态 %d", vsk[i].dPage,vsk[i].键位, vsk[i].dId, vsk[i].是否冷却, vsk[i].技能状态);
            //}
            //成就领取::getExpeditionInfo();
            //成就领取::get_BookListInfo();
            //UI功能::Fun_UiShowCtrl(0x25);
            //本人::CALL_打开分解();
            //MyTrace(L"是否可达 %d", 地图::指定地点是否可到达_M(-5190, -32768, -6430));
            //srand(time(NULL));
            //CString 名称;
            ////CString 首字 = 随机生成英文名字(1);
            //switch ((rand() % 4))
            //{
            //case 1:
            //    名称 = randstr(Random(6, 16)) + 尾5[Random(0, 11)];
            //    break;
            //case 2:
            //    名称 = randstr(Random(6, 16)) + 尾6[Random(0, 6)];
            //    break;
            //case 3:
            //    名称 = randstr(Random(6, 16)) + 尾7[Random(0, 3)];
            //    break;
            //default:
            //    名称 = randstr(Random(6, 16)) + 尾8[Random(0, 3)];
            //    break;
            //}
            //=================================================================================
           // MyTrace(L"生成名称 %s", 名称);
           // 登陆::CALL_选择服务器(L"Mari");
            //vector<登陆角色信息_>vsk;
            //登陆::get_CharacterList(vsk);
            //for (size_t i = 0; i < vsk.size(); i++)
            //{
            //    MyTrace(L"角色列表 SrvId 0x%I64x Index %d Name:%s Job %X Lev %d",vsk[i].SrvId, vsk[i].dIndex, vsk[i].名称, vsk[i].dJob, vsk[i].等级);
            //    登陆::CALL_进入游戏(1);
            //}

            ////====================================================================================
            ////登陆::CALL_创建角色(1);
            //MyTrace(L"距离 %d", 距离计算(-22303, 33050, 1, 31801, 48544, 1));
            //UI功能::getMsgBoxTextList();
            //MyTrace(L"获取当前电梯ID %d", 环境::获取当前电梯ID());
            //循环跳出 = true;
            //签到邮件::邮件领取();
            //vector<MailInfo_>vsk;
            //签到邮件::get_ExpressMailList(vsk);
           //vector<Inventoryinfo_>vsk2;
           // 背包::get_InventoryItemList(vsk2);
           // for (size_t i = 0; i < vsk2.size(); i++)
           // {

           // }
            //背包::使用物品(80);
            //=============================================================================
            //vector<Inventoryinfo_>vsk;
            //NPC商店::get_ShopItemList(vsk);
           //NPC商店::Fun_ShopBuyAddItem(2,1);
           //=================================================================================
           //mythread2.Start();
           /*
           //============================================================================
           //vector<INT64>ID组;
            本人::遍历宠物(ID组);
            for (size_t i = 0; i < ID组.size(); i++)
            {
                MyTrace(L"0x%I64X", ID组[i]);
            }*/
            //本人::召唤宠物();
            //=============================================================================
            /*vector<CString>对话组;
            UI功能::getNpcTalkSelectList(对话组);*/
            //vector<QuestInfo_>vsk;
            //任务::get_GuideList(vsk);
           /* float fangle = 获取对象角度值(本人::取真实对象());

            坐标_ 本人坐标 = 本人::取坐标();
            MyTrace(L"本人当前角度   %f 面向指定坐标角度:%f",  fangle * 0.00549317, Get_Rel_Angle(本人坐标.x, 本人坐标.y, 18384, 47762) * 0.00549317);*/

            /*  vector<传送点信息_>已激活传送点;
              地图::遍历已激活传送点(已激活传送点);
              for (size_t i = 0; i < 已激活传送点.size(); i++)
              {
                  MyTrace(L"已激活传送点 名称 %s ID %d  所属Map %d", 已激活传送点[i].cTeleportName, 已激活传送点[i].dTeleportId, 已激活传送点[i].Mapid);
              }*/


              //MyTrace(L"副本obj 0x%I64X", UI功能::getUiObjById(168));
              //vector<录制坐标_>录制坐标组;
              //配置::取录制坐标(10211, 录制坐标组);
         /*     vector<UIinfo_>vsk3;
              UI功能::getUiList(vsk3);
              MyTrace(L"控件数量:%d", vsk3.size());
              for (size_t i = 0; i < vsk3.size(); i++)
              {
                  MyTrace(L"索引%X 对象地址0x%I64X ID %X 是否显示%d %s\r\n", vsk3[i].dIndex, vsk3[i].UIObj, vsk3[i].dId, vsk3[i].bShow, vsk3[i].CName);
              }*/
              //vector<Inventoryinfo_>vsk2;
              //vector<Equipinfo_>vsk3;
              //vector<乐谱信息_>vsk4;

            //背包::get_EquipList(vsk3);
            ////本人::改移动速度(true,1000);
            //MyTrace(L"大陆ID: %d 地图ID: % d 大地图名 : % s 小地图名 : % s", 地图::取当前大陆ID(), 地图::取地图ID(), 地图::取大地图名(),地图::取小地图名());
            //本人::乐谱遍历(vsk4);
            //ActorInfo_ 角色信息=本人::取角色信息();
            //MyTrace(L"角色名称%s 等级%d 坐标%0.3f,%0.3f,%0.3f 血量%d/%d", 角色信息.名称, 角色信息.等级, 角色信息.坐标.x, 角色信息.坐标.y, 角色信息.坐标.z,角色信息.当前血,角色信息.最大血);


         /*   vector<objInfo_>环境对象数组;
            环境::遍历全部环境对象(环境对象数组);
            MyTrace(L"遍历全部环境对象 数量%d", 环境对象数组.size());
            坐标_ 本人坐标temp = 本人::取坐标();
            MyTrace(L"本人坐标.x %0.3f 本人坐标.y %0.3f 本人坐标.z %0.3f", 本人坐标temp.x, 本人坐标temp.y, 本人坐标temp.z);

            for (size_t i = 0; i < 环境对象数组.size(); i++)
            {
                MyTrace(L"距离 %d 全对象 0x%I64X Type: %d, 名称:%s modid:%d resid:%d 是否隐藏:%d 是否敌人:%d HP:%d/%d 击打道具是否死亡 %d dResShow %d dResDead %d 坐标 %0.3f,%0.3f,%0.3f",
                    距离计算(本人坐标temp.x, 本人坐标temp.y, 本人坐标temp.z, 环境对象数组[i].坐标.x, 环境对象数组[i].坐标.y, 环境对象数组[i].坐标.z), 环境对象数组[i].objBase, 环境对象数组[i].dType, 环境对象数组[i].wName, 环境对象数组[i].ModId, 环境对象数组[i].dResId, 环境对象数组[i].IsHide, 环境对象数组[i].IsEnemy, 环境对象数组[i].dCurHp, 环境对象数组[i].dMaxHp, 环境::击打道具是否死亡(环境对象数组[i].objBase), 环境对象数组[i].dResShow, 环境对象数组[i].dIsDead, 环境对象数组[i].坐标.x, 环境对象数组[i].坐标.y, 环境对象数组[i].坐标.z);
            }*/


            //MyTrace(L"=============================================================");
             //环境::遍历怪物(环境对象数组);
             //for (size_t i = 0; i < 环境对象数组.size(); i++)
             //{
             //    MyTrace(L"怪物 0x%I64X Type: %d, 名称:%s modid:%d id:%d 是否隐藏:%d 是否敌人:%d HP:%d/%d", 环境对象数组[i].objBase, 环境对象数组[i].dType, 环境对象数组[i].wName, 环境对象数组[i].ModId, 环境对象数组[i].dObjId, 环境对象数组[i].IsHide, 环境对象数组[i].IsEnemy, 环境对象数组[i].dCurHp, 环境对象数组[i].dMaxHp);
             //}
            /* vector<SkillInfo_>技能数组;
             技能::get_SkillList(技能数组);
             for (size_t i = 0; i < 技能数组.size(); i++)
             {
                 if (技能数组[i].键位 != -1)
                 {
                     MyTrace(L"技能: %s %d 键位:%d 冷却:%d 天赋:%d %d %d 是否可升级:%d", 技能数组[i].名称, 技能数组[i].dSkillId, 技能数组[i].键位,技能数组[i].是否冷却,技能数组[i].天赋1, 技能数组[i].天赋2, 技能数组[i].天赋3, 技能数组[i].dCanUpGrade);
                 }
             }
              vector<ShortCutInfo_>快捷栏数组;
              技能::get_RightShortList(快捷栏数组);
              for (size_t i = 0; i < 快捷栏数组.size(); i++)
              {
                  if (快捷栏数组[i].键位 != -1)
                  {
                      MyTrace(L"快捷栏: %s %d  类型%d 键位%d", 快捷栏数组[i].名称, 快捷栏数组[i].dId, 快捷栏数组[i].type, 快捷栏数组[i].键位);
                  }
              }*/
              //UI功能::内存按键(87);
              //MyTrace(L"=============================================================");
            /*  环境::遍历NPC(环境对象数组);
              for (size_t i = 0; i < 环境对象数组.size(); i++)
              {
                  MyTrace(L"NPC 0x%I64X Type: %d, 名称:%s modid:%d id:%d 是否隐藏:%d 是否敌人:%d HP:%d/%d", 环境对象数组[i].objBase, 环境对象数组[i].dType, 环境对象数组[i].wName, 环境对象数组[i].ModId, 环境对象数组[i].IsHide, 环境对象数组[i].IsEnemy, 环境对象数组[i].dCurHp, 环境对象数组[i].dMaxHp);
              }*/
              //MyTrace(L"=============================================================");
              //环境::遍历采集物(环境对象数组);
              //for (size_t i = 0; i < 环境对象数组.size(); i++)
              //{
              //    MyTrace(L"采集物 0x%I64X Type: %d, 名称:%s modid:%d id:%d 是否隐藏:%d 是否敌人:%d HP:%d/%d",  环境对象数组[i].objBase, 环境对象数组[i].dType, 环境对象数组[i].wName, 环境对象数组[i].ModId, 环境对象数组[i].IsHide, 环境对象数组[i].IsEnemy, 环境对象数组[i].dCurHp, 环境对象数组[i].dMaxHp);
              //}
              //MyTrace(L"=============================================================");
           /* 环境::遍历击打道具(环境对象数组);
            for (size_t i = 0; i < 环境对象数组.size(); i++)
            {
                MyTrace(L"击打道具 0x%I64X 是否死亡 %d,Type: %d, 名称:%s modid:%d id:%d 是否隐藏:%d 是否敌人:%d HP:%d/%d", 环境对象数组[i].objBase, 环境::击打道具是否死亡(环境对象数组[i].objBase), 环境对象数组[i].dType, 环境对象数组[i].wName, 环境对象数组[i].ModId, 环境对象数组[i].IsHide, 环境对象数组[i].IsEnemy, 环境对象数组[i].dCurHp, 环境对象数组[i].dMaxHp);
            }*/
            //MyTrace(L"=============================================================");
            //环境::遍历电梯(环境对象数组);
            //for (size_t i = 0; i < 环境对象数组.size(); i++)
            //{
            //    MyTrace(L"电梯 0x%I64X Type: %d, 名称:%s modid:%d id:%d 是否隐藏:%d 是否敌人:%d HP:%d/%d", 环境对象数组[i].objBase, 环境对象数组[i].dType, 环境对象数组[i].wName, 环境对象数组[i].ModId, 环境对象数组[i].IsHide, 环境对象数组[i].IsEnemy, 环境对象数组[i].dCurHp, 环境对象数组[i].dMaxHp);
            //}
         /*环境::遍历地面物品(环境对象数组);
            for (size_t i = 0; i < 环境对象数组.size(); i++)
            {
                MyTrace(L" 0x%I64X Type: %d, 名称:%s modid:%d id:%d 是否隐藏:%d 是否敌人:%d HP:%d/%d", 环境对象数组[i].objBase, 环境对象数组[i].dType, 环境对象数组[i].wName, 环境对象数组[i].ModId, 环境对象数组[i].IsHide, 环境对象数组[i].IsEnemy, 环境对象数组[i].dCurHp, 环境对象数组[i].dMaxHp);
            }*/
            // hook_api::hookNtCursorPos(1);
             /*屏蔽鼠标开关 = true;
             hook鼠标坐标.x = 125;
             hook鼠标坐标.y = 756;*/
             //背包::使用物品(1);
             //mythread2.Start();

             //MyTrace(L"大地图名称 %s", 地图::取大地图名());
             //vector<QuestInfo_>vsk5;
             //任务::get_CurQuestList(vsk5);
             //for (size_t i = 0; i < vsk5.size(); i++)
             //{
             //    MyTrace(L"dobj 0x%I64X,resaddr 0x%I64X,类型 %d 任务名称 %s 当前阶段：%d 任务ID：%d 任务目标iD:%d 目标数量:%d,当前数量:%d 需求数量:%d", vsk5[i].objBase, vsk5[i].dResAddr,vsk5[i].dType, vsk5[i].QuestName, vsk5[i].dStep, vsk5[i].dQuestId, vsk5[i].TargetId, vsk5[i].TargetNum, vsk5[i].CurNum, vsk5[i].NeedNum);
             //    MyTrace(L"任务状态 %d  ==>是否完成 %d", vsk5[i].dState,vsk5[i].IsFinish);
             //    MyTrace(L"描述 %s \r\n", vsk5[i].DescribeName);
             //    MyTrace(L"-----------------------------------------------------------");
             //    坐标_ 任务坐标 = 任务::CALL_取任务坐标(vsk5[i].dQuestId, vsk5[i].objBase, vsk5[i].dResAddr);
             //    MyTrace(L"任务坐标:大陆ID:%d,X:%0.3f Y:%0.3f Z:%0.3f", 任务坐标.大陆ID, 任务坐标.x, 任务坐标.y, 任务坐标.z);
             //    MyTrace(L"===========================================================");
             //    //地图::本地图寻路(任务坐标.x, 任务坐标.y, 任务坐标.z,0);
             //}
             //MyTrace(L"小地图名称 %s", 地图::取小地图名());
             //地图::本地图寻路(本人::取坐标().x+100, 本人::取坐标().y, 本人::取坐标().z, 0);
             //MyTrace(L"目标是否可达:%d", 地图::指定地点是否可到达(2000, 252, 1728));
        }


        break;
    }
    case DLL_THREAD_ATTACH: break;
    case DLL_THREAD_DETACH: break;
    case DLL_PROCESS_DETACH:unLoad(); break;
    }
    return TRUE;
}
