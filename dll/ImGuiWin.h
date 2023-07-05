#pragma once



extern bool b鼠标消息影响游戏;
extern HWND g_hWnd;
//extern const UINT 注册消息值;
extern UINT64 全局模块句柄;
extern HMODULE hOPMOUDULE;
extern char InputText[1024 * 20];

void 显示游戏IMGUI窗口(bool* mainBeginSate);

/****
使用方法：
方法1、将本头文件放入到你的IMGUI项目里面，然后引入即可。
方法2、直接将本头文件内容复制、粘贴到你的项目里面。
****/


//颜色值
#define 颜色_粉色 ImVec4(1.0f, 0.0f, 1.0f, 1.0f)
#define 颜色_黄色 ImVec4(1.0f, 1.0f, 0.0f, 1.0f)
#define 颜色_艳青 = ImGui::ColorConvertU32ToFloat4(ImU32(0, 255, 255, 255))
#define 颜色_红色 = ImGui::ColorConvertU32ToFloat4(ImU32(255, 0, 0, 255))
#define 颜色_橙色 = ImGui::ColorConvertU32ToFloat4(ImU32(255, 165, 0, 255)
#define 颜色_白色 = ImGui::ColorConvertU32ToFloat4(ImU32(255, 255, 255, 255)
#define 颜色_绿色 = ImGui::ColorConvertU32ToFloat4(ImU32(0, 255, 0, 255))
#define 颜色_紫色 = ImGui::ColorConvertU32ToFloat4(ImU32(128, 0, 128, 255))
#define 颜色_天蓝 = ImGui::ColorConvertU32ToFloat4(ImU32(135, 206, 235, 255))
#define 颜色_深天蓝 = ImGui::ColorConvertU32ToFloat4(ImU32(0, 191, 255, 255))


#define IM_设置初始窗口坐标   ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);
#define IM_设置窗口_固定尺寸(宽,高) ImGui::SetNextWindowSize(ImVec2(宽, 高),0);
#define IM_设置窗口_不固定尺寸(宽,高) ImGui::SetNextWindowSize(ImVec2(宽, 高), ImGuiCond_FirstUseEver);
#define IM_开始(名字) ImGui::Begin(名字)
#define IM_结束 ImGui::End();
// 参数1：显示标题<类型：字符串>   
// 参数2：选中的标识<类型：bool> 
#define IM_选择框(显示标题,选中标识) ImGui::Checkbox(显示标题,选中标识)

#define IM_不换行 ImGui::SameLine();

#define IM_不换行EX(与最左边开始宽度,与前面的组件间隔) ImGui::SameLine(与最左边开始宽度,与前面的组件间隔);

#define IM_标签0(标题内容) ImGui::Text(标题内容);
#define IM_标签1(标题内容,参数1) ImGui::Text(标题内容,参数1);
#define IM_标签2(标题内容,参数1,参数2) ImGui::Text(标题内容,参数1,参数2);
#define IM_标签3(标题内容,参数1,参数2,参数3) ImGui::Text(标题内容,参数1,参数2,参数3);
#define IM_标签4(标题内容,参数1,参数2,参数3,参数4) ImGui::Text(标题内容,参数1,参数2,参数3,参数4);

#define IM_按钮(标题内容) ImGui::Button(标题内容)

#define IM_颜色按钮(标题内容,颜色,是否可编辑) ImGui::ColorButton(标题内容,颜色,是否可编辑)

// 参数1：标题<类型：字符串>
// 参数2：选中编号<类型：int>
// 参数3：项目列表<类型：字符串>
#define IM_组合框(标题,选中编号指针,项目列表) ImGui::Combo(标题,选中编号指针,项目列表)

#define IM_进度条_FLOAT(标题,返回FLOAT指针,最小值,最大值,序列字符串,标志) ImGui::SliderFloat(标题,返回FLOAT指针,最小值,最大值,序列字符串,标志);
#define IM_进度条_INT(标题,返回INT指针,最小值,最大值,序列字符串,标志) ImGui::SliderInt(标题,返回INT指针,最小值,最大值,序列字符串,标志);

#define IM_工具栏_整行(标题) ImGui::CollapsingHeader(标题)

#define IM_树形开始(标题) if(ImGui::TreeNode(标题)){
#define IM_树形结束 ImGui::TreePop();}

#define IM_TAB父工具栏_开始(标题,打开标识) if(ImGui::BeginTabBar(标题, 打开标识)){
#define IM_TAB父工具栏_结束 }ImGui::EndTabBar();

#define IM_TAB子工具栏_开始(标题) if(ImGui::BeginTabItem(标题)){
#define IM_TAB子工具栏_结束 ImGui::EndTabItem();}


//ImGui::InputText("Completion", buf1, 64, ImGuiInputTextFlags_CallbackCompletion, Funcs::MyCallback);
//ImGui::InputText("password (clear)", password, IM_ARRAYSIZE(password));
//ImGui::InputTextWithHint("password (w/ hint)", "<password>", password, IM_ARRAYSIZE(password), ImGuiInputTextFlags_Password);

#define IM_编辑框(标题,内容指针,行数,权限) ImGui::InputText(标题, 内容指针, 行数,权限)
#define IM_编辑框_多行(标题,内容指针,行数,权限)ImGui::InputTextMultiline(标题, 内容指针, IM_ARRAYSIZE(内容指针),ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() * 行数),权限)

#define IM_编辑框_INT(标题,显示内容,内容指针,内存占用大小) ImGui::InputTextWithHint(标题,显示内容, 内容指针, 内存占用大小)

#define IM_表格_横线 ImGui::Separator();
#define IM_表格_竖线 ImGui::NextColumn();

#define IM_表格_开始(列数,表格标识) ImGui::Columns(列数, 表格标识);ImGui::Separator();
#define IM_表格_结束 ImGui::Columns(1);ImGui::Separator();

