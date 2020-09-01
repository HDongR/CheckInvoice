#pragma once
#include <afxwin.h>
class CustomListBox :
	public CListBox
{
	DECLARE_DYNAMIC(CustomListBox)

public:
	CustomListBox();
	virtual ~CustomListBox();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDropFiles(HDROP hDropInfo);
};

