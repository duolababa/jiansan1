#pragma once



extern bool b�����ϢӰ����Ϸ;
extern HWND g_hWnd;
//extern const UINT ע����Ϣֵ;
extern UINT64 ȫ��ģ����;
extern HMODULE hOPMOUDULE;
extern char InputText[1024 * 20];

void ��ʾ��ϷIMGUI����(bool* mainBeginSate);

/****
ʹ�÷�����
����1������ͷ�ļ����뵽���IMGUI��Ŀ���棬Ȼ�����뼴�ɡ�
����2��ֱ�ӽ���ͷ�ļ����ݸ��ơ�ճ���������Ŀ���档
****/


//��ɫֵ
#define ��ɫ_��ɫ ImVec4(1.0f, 0.0f, 1.0f, 1.0f)
#define ��ɫ_��ɫ ImVec4(1.0f, 1.0f, 0.0f, 1.0f)
#define ��ɫ_���� = ImGui::ColorConvertU32ToFloat4(ImU32(0, 255, 255, 255))
#define ��ɫ_��ɫ = ImGui::ColorConvertU32ToFloat4(ImU32(255, 0, 0, 255))
#define ��ɫ_��ɫ = ImGui::ColorConvertU32ToFloat4(ImU32(255, 165, 0, 255)
#define ��ɫ_��ɫ = ImGui::ColorConvertU32ToFloat4(ImU32(255, 255, 255, 255)
#define ��ɫ_��ɫ = ImGui::ColorConvertU32ToFloat4(ImU32(0, 255, 0, 255))
#define ��ɫ_��ɫ = ImGui::ColorConvertU32ToFloat4(ImU32(128, 0, 128, 255))
#define ��ɫ_���� = ImGui::ColorConvertU32ToFloat4(ImU32(135, 206, 235, 255))
#define ��ɫ_������ = ImGui::ColorConvertU32ToFloat4(ImU32(0, 191, 255, 255))


#define IM_���ó�ʼ��������   ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);
#define IM_���ô���_�̶��ߴ�(��,��) ImGui::SetNextWindowSize(ImVec2(��, ��),0);
#define IM_���ô���_���̶��ߴ�(��,��) ImGui::SetNextWindowSize(ImVec2(��, ��), ImGuiCond_FirstUseEver);
#define IM_��ʼ(����) ImGui::Begin(����)
#define IM_���� ImGui::End();
// ����1����ʾ����<���ͣ��ַ���>   
// ����2��ѡ�еı�ʶ<���ͣ�bool> 
#define IM_ѡ���(��ʾ����,ѡ�б�ʶ) ImGui::Checkbox(��ʾ����,ѡ�б�ʶ)

#define IM_������ ImGui::SameLine();

#define IM_������EX(������߿�ʼ���,��ǰ���������) ImGui::SameLine(������߿�ʼ���,��ǰ���������);

#define IM_��ǩ0(��������) ImGui::Text(��������);
#define IM_��ǩ1(��������,����1) ImGui::Text(��������,����1);
#define IM_��ǩ2(��������,����1,����2) ImGui::Text(��������,����1,����2);
#define IM_��ǩ3(��������,����1,����2,����3) ImGui::Text(��������,����1,����2,����3);
#define IM_��ǩ4(��������,����1,����2,����3,����4) ImGui::Text(��������,����1,����2,����3,����4);

#define IM_��ť(��������) ImGui::Button(��������)

#define IM_��ɫ��ť(��������,��ɫ,�Ƿ�ɱ༭) ImGui::ColorButton(��������,��ɫ,�Ƿ�ɱ༭)

// ����1������<���ͣ��ַ���>
// ����2��ѡ�б��<���ͣ�int>
// ����3����Ŀ�б�<���ͣ��ַ���>
#define IM_��Ͽ�(����,ѡ�б��ָ��,��Ŀ�б�) ImGui::Combo(����,ѡ�б��ָ��,��Ŀ�б�)

#define IM_������_FLOAT(����,����FLOATָ��,��Сֵ,���ֵ,�����ַ���,��־) ImGui::SliderFloat(����,����FLOATָ��,��Сֵ,���ֵ,�����ַ���,��־);
#define IM_������_INT(����,����INTָ��,��Сֵ,���ֵ,�����ַ���,��־) ImGui::SliderInt(����,����INTָ��,��Сֵ,���ֵ,�����ַ���,��־);

#define IM_������_����(����) ImGui::CollapsingHeader(����)

#define IM_���ο�ʼ(����) if(ImGui::TreeNode(����)){
#define IM_���ν��� ImGui::TreePop();}

#define IM_TAB��������_��ʼ(����,�򿪱�ʶ) if(ImGui::BeginTabBar(����, �򿪱�ʶ)){
#define IM_TAB��������_���� }ImGui::EndTabBar();

#define IM_TAB�ӹ�����_��ʼ(����) if(ImGui::BeginTabItem(����)){
#define IM_TAB�ӹ�����_���� ImGui::EndTabItem();}


//ImGui::InputText("Completion", buf1, 64, ImGuiInputTextFlags_CallbackCompletion, Funcs::MyCallback);
//ImGui::InputText("password (clear)", password, IM_ARRAYSIZE(password));
//ImGui::InputTextWithHint("password (w/ hint)", "<password>", password, IM_ARRAYSIZE(password), ImGuiInputTextFlags_Password);

#define IM_�༭��(����,����ָ��,����,Ȩ��) ImGui::InputText(����, ����ָ��, ����,Ȩ��)
#define IM_�༭��_����(����,����ָ��,����,Ȩ��)ImGui::InputTextMultiline(����, ����ָ��, IM_ARRAYSIZE(����ָ��),ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() * ����),Ȩ��)

#define IM_�༭��_INT(����,��ʾ����,����ָ��,�ڴ�ռ�ô�С) ImGui::InputTextWithHint(����,��ʾ����, ����ָ��, �ڴ�ռ�ô�С)

#define IM_���_���� ImGui::Separator();
#define IM_���_���� ImGui::NextColumn();

#define IM_���_��ʼ(����,����ʶ) ImGui::Columns(����, ����ʶ);ImGui::Separator();
#define IM_���_���� ImGui::Columns(1);ImGui::Separator();

