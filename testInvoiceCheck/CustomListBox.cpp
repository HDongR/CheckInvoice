#include "pch.h"
#include "CustomListBox.h"
#include <string>

IMPLEMENT_DYNAMIC(CustomListBox, CListBox)
CustomListBox::CustomListBox()
{
}

CustomListBox::~CustomListBox() {
}

BEGIN_MESSAGE_MAP(CustomListBox, CListBox)
	ON_WM_DROPFILES()
	//	ON_WM_CREATE()
END_MESSAGE_MAP()

void CustomListBox::OnDropFiles(HDROP hDropInfo)
{
	int ucount = DragQueryFile(hDropInfo, 0xffffffff, nullptr, 0);

#ifdef _UNICODE

	LPWSTR buffer;

#else

	char* buffer;

#endif

	buffer = nullptr;

	// ������ ���ü��� ������ ���⼱ �ϳ��� ó��

	if (ucount > 1) {
		AfxMessageBox(_T("File�� �ϳ��� ó������, ù��° ���ϸ� ó���մϴ�."));
	}

	int nLength = DragQueryFile(hDropInfo, 0, nullptr, 0);

#ifdef _UNICODE

	buffer = (LPWSTR)malloc(2 * (nLength + 1)); // ���⼭ Uncode�� 2 Byte�̹Ƿ� 2��� ����� �Ѵ�.

#else

	buffer = (char*)malloc(nLength + 1);

#endif 
	DragQueryFile(hDropInfo, 0, buffer, nLength + 1);

	if (GetFileAttributes(buffer) == FILE_ATTRIBUTE_DIRECTORY) {

		AfxMessageBox(_T("Directory�� ó������ �ʽ��ϴ�."));

	}
	else {
		/*std::wstring ss(buffer);
		int s = ss.rfind('\\');
		std::wstring rst = ss.substr(s + 1, ss.length() - 1);

		AddString((LPTSTR)rst.c_str());*/
		AddString((LPTSTR)buffer);
	}

	if (buffer != nullptr) free(buffer);

	CListBox::OnDropFiles(hDropInfo);
}