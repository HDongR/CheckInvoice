
// testInvoiceCheckDlg.h: 헤더 파일
//

#pragma once
#include "CustomListBox.h"

class PDFParser;
// CtestInvoiceCheckDlg 대화 상자
class CtestInvoiceCheckDlg : public CDialogEx
{
	// 생성입니다.
public:
	CtestInvoiceCheckDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TESTINVOICECHECK_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	bool checkListBox(CListBox* box);
	void makeHorizontalScroll(CListBox* box);

public:
	CustomListBox m_listConfirm;
	CustomListBox m_listInvoice;
	afx_msg void OnBnClickedButton1();
	CStatic m_staticConfirm;
	CStatic m_staticInvoice;
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnLbnSelchangeList2();
	afx_msg void OnBnClickedButton2();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	PDFParser* pdf;
	virtual BOOL DestroyWindow();
};
