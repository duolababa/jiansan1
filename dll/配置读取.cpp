#include "���ö�ȡ.h"
CString ��ȡ¼�������ı�(CString ��ͼID)
{
	CString ���ýڵ�, ����������, path;
	CString ���ܺ��ı�;
	if (����λ�� == L"")
	{
		����::��ȡ����λ��();
	}
	if (����λ�� != L"")
	{
		path = ����λ�� + L"\\Map\\" + ��ͼID + L".txt";
	}
	else
	{
		path = L"D:\\LostArkLUA\\Map\\" + ��ͼID + L".txt";
	}

	OutputDebugStringW(path);

	HANDLE �ļ����;
	char �ı�[2048] = "";
	�ļ���� = ���ļ�(path);
	if (�ļ���� == INVALID_HANDLE_VALUE)
	{
		return L"�ļ������ʧ��";
	}
	int filesucc = ���ļ�(�ļ����, �ı�, 2048);

	if (filesucc == 0)
	{
		return L"��ȡ�ļ�ʧ��";
	}
	int fileSize = GetFileSize(�ļ����, NULL);

	CloseHandle(�ļ����);
	���ܺ��ı� = �ı�;
	return ���ܺ��ı�;
}
void �ı��ָ�(CString strSource, char ch, CArray<CString, CString>* �����ı���)
{
	�����ı���->RemoveAll();
	CString strTmp;
	//CArray<CString, CString> vecString;
	int iPos = 0;
	while (AfxExtractSubString(strTmp, strSource, iPos, ch))
	{
		iPos++;
		�����ı���->Add(strTmp);
	}

}
void ���������ı�(CString �����ı�, vector<¼������_>& ��_¼��������, int ��ͼ��ʶ)
{
	int �ı�λ�� = -1;
	��_¼��������.clear();
	¼������_ ��_¼������;
	CArray<CString, CString>���������ı���;
	CArray<CString, CString>�����ı���;
	CArray<CString, CString>���������;
	CString ��ʶ�ı�;
	�����ı�.Replace(L"\r\n", L"}");
	�����ı�.Replace(L"//", L"");
	�ı��ָ�(�����ı�, '}', &���������ı���);
	for (size_t i = 0; i < ���������ı���.GetCount(); i++)
	{
		�ı��ָ�(���������ı���[i], ',', &�����ı���);
		if (�����ı���.GetCount() == 11)
		{
			��_¼������.x1 = _ttof(�����ı���[0]);
			��_¼������.y1 = _ttof(�����ı���[1]);
			��_¼������.z1 = _ttof(�����ı���[2]);
			��_¼������.x2 = _ttof(�����ı���[3]);
			��_¼������.y2 = _ttof(�����ı���[4]);
			��_¼������.z2 = _ttof(�����ı���[5]);
			��_¼������.���� = _ttoi(�����ı���[6]);
			��_¼������.��· = _ttoi(�����ı���[7]);
			��_¼������.��·�ֶ� = _ttoi(�����ı���[8]);
			��_¼������.δ֪1 = _ttoi(�����ı���[9]);
			��_¼������.δ֪2 = _ttoi(�����ı���[10]);
			��_¼������.��ͼID = ��ͼ��ʶ;
			//��_¼������.��ͼ��ʶ = false;
			��_¼��������.push_back(��_¼������);
		}
	}
}
void ����::ȡ¼������(int ��ͼ��ʶ, vector<¼������_>& ¼��������)
{
	if (��ͼ��ʶ == 0)
	{
		return;
	}
	CString ��ͼstr;
	��ͼstr.Format(L"%d", ��ͼ��ʶ);
	CString �����ı� = ��ȡ¼�������ı�(��ͼstr);
	���������ı�(�����ı�, ¼��������, ��ͼ��ʶ);
	//MyTrace(L"%d ȡ��¼��������:%d ��", ��ͼ��ʶ, ¼��������.size());
}
CString ��ȡLAconfig����Ŀ¼()
{
	CString �����ı� = L"";

	CString path = L"C:\\LAconfig.ini";
	GetPrivateProfileString(L"ȫ������", L"����Ŀ¼", L"", �����ı�.GetBuffer(4096), 4096, path);
	�����ı�.ReleaseBuffer();
	return �����ı�;
}
void ����::��ȡ����λ��()
{
	����λ�� = ��ȡLAconfig����Ŀ¼();
	//����λ�� = ȡģ��·��("debugreport.dll");
	if (����λ�� != L"")
	{
		OutputDebugStringW(L"����λ��:" + ����λ��);
	}
	else
	{
		OutputDebugStringW(L"����λ�ô���:" + ����λ��);
	}

}
CString ����::��ȡָ�������ı�(CString �����ļ�����, CString ���ýڵ�, CString ����������)
{
	CString �����ı� = L"", path;
	if (����λ�� == L"")
	{
		��ȡ����λ��();
	}
	path = ����λ�� + L"\\" + �����ļ�����;
	GetPrivateProfileString(���ýڵ�, ����������, L"", �����ı�.GetBuffer(4096), 4096, path);
	�����ı�.ReleaseBuffer();
	return �����ı�;
}

//void ����::��ȡ�ű�����()
//{
//	�ű����� = ��ȡָ�������ı�(L"�ű�����.ini", L"LostArk" + �������ı�(GameIndex), L"�ű�����");
//	��ɫ��� = ��ȡָ�������ı�(L"�ű�����.ini", L"LostArk" + �������ı�(GameIndex), L"��ɫ");
//	����
//  = ��ȡָ�������ı�(L"�ű�����.ini", L"LostArk" + �������ı�(GameIndex), L"������");
//	//MyTrace(L"��� %d �ű����� %s ��ɫ��� %s ������: %s", GameIndex, �ű�����, ��ɫ���, ���÷�����);
//}