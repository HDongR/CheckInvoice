
// testInvoiceCheckDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "testInvoiceCheck.h"
#include "testInvoiceCheckDlg.h"
#include "afxdialogex.h"
#include "PDFParser.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CtestInvoiceCheckDlg::CtestInvoiceCheckDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TESTINVOICECHECK_DIALOG, pParent)
{

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CtestInvoiceCheckDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listConfirm);
	DDX_Control(pDX, IDC_LIST2, m_listInvoice);
	DDX_Control(pDX, IDC_STATIC_CONFIRM, m_staticConfirm);
	DDX_Control(pDX, IDC_STATIC_INVOICE, m_staticInvoice);
}

BEGIN_MESSAGE_MAP(CtestInvoiceCheckDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_BUTTON1, &CtestInvoiceCheckDlg::OnBnClickedButton1)
	ON_LBN_SELCHANGE(IDC_LIST1, &CtestInvoiceCheckDlg::OnLbnSelchangeList1)
	ON_LBN_SELCHANGE(IDC_LIST2, &CtestInvoiceCheckDlg::OnLbnSelchangeList2)
	ON_BN_CLICKED(IDC_BUTTON2, &CtestInvoiceCheckDlg::OnBnClickedButton2)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CtestInvoiceCheckDlg 메시지 처리기

BOOL CtestInvoiceCheckDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	pdf = new PDFParser();


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CtestInvoiceCheckDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialogEx::OnSysCommand(nID, lParam);
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CtestInvoiceCheckDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CtestInvoiceCheckDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

HBRUSH CtestInvoiceCheckDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if ((nCtlColor == CTLCOLOR_STATIC && pWnd->GetSafeHwnd() == GetDlgItem(IDC_STATIC_CONFIRM)->GetSafeHwnd())
		||
		(nCtlColor == CTLCOLOR_STATIC && pWnd->GetSafeHwnd() == GetDlgItem(IDC_STATIC_INVOICE)->GetSafeHwnd())) {
		pDC->SetTextColor(RGB(255, 0, 0));
	}

	return hbr;
}

bool CtestInvoiceCheckDlg::checkListBox(CListBox* box) {
	int index = box->GetCurSel();
	if (index == LB_ERR)
		return false;
	int cntListSelec = box->GetSelCount();
	if (cntListSelec == 0)
		return false;
	return true;
}

void CtestInvoiceCheckDlg::makeHorizontalScroll(CListBox* box) {
	CString str; CSize sz; int dx = 0;
	CDC* pDC = box->GetDC();

	for (int i = 0; i < box->GetCount(); i++)
	{
		box->GetText(i, str);
		sz = pDC->GetTextExtent(str);

		if (sz.cx > dx)
			dx = sz.cx;
	}
	box->ReleaseDC(pDC);

	if (box->GetHorizontalExtent() < dx)
	{
		box->SetHorizontalExtent(dx);
		//ASSERT(m_at_list.GetHorizontalExtent() == dx);
	}

}

void CtestInvoiceCheckDlg::OnLbnSelchangeList1()
{
	if (!checkListBox(&m_listConfirm))
		return;

	makeHorizontalScroll(&m_listConfirm);

	CString selText;
	m_listConfirm.GetText(m_listConfirm.GetCurSel(), selText);

	int s = selText.ReverseFind('\\');
	m_staticConfirm.SetWindowTextW(selText.Mid(s + 1));
}

void CtestInvoiceCheckDlg::OnLbnSelchangeList2()
{
	if (!checkListBox(&m_listInvoice))
		return;

	makeHorizontalScroll(&m_listInvoice);

	CString selText;
	m_listInvoice.GetText(m_listInvoice.GetCurSel(), selText);

	int s = selText.ReverseFind('\\');
	m_staticInvoice.SetWindowTextW(selText.Mid(s + 1));
}

void CtestInvoiceCheckDlg::OnBnClickedButton2()
{
	m_listConfirm.ResetContent();
	m_listInvoice.ResetContent();
	m_staticConfirm.SetWindowTextW(_T(""));
	m_staticInvoice.SetWindowTextW(_T(""));
}

void CtestInvoiceCheckDlg::OnBnClickedButton1()
{
	if (!checkListBox(&m_listConfirm))
		return;
	if (!checkListBox(&m_listInvoice))
		return;
	
	CString selTextConfirm;
	m_listConfirm.GetText(m_listConfirm.GetCurSel(), selTextConfirm);

	CString selTextInvoice;
	m_listInvoice.GetText(m_listInvoice.GetCurSel(), selTextInvoice);
	 
	int s = selTextConfirm.ReverseFind('.');
	CString extensionConfirm = selTextConfirm.Mid(s + 1);

	int s2 = selTextInvoice.ReverseFind('.');
	CString extensionInvoice = selTextInvoice.Mid(s2 + 1);

	if (extensionConfirm.Compare(_T("pdf")) == 0) {
		std::wstring kk(selTextConfirm);
		pdf->load(&kk);
	}
	else if (extensionConfirm.Compare(_T("excel")) == 0) {
		//excel
	}

	if (extensionInvoice.Compare(_T("pdf")) == 0) {
		std::wstring kk(selTextConfirm);
		pdf->load(&kk);
	}
	else if (extensionInvoice.Compare(_T("excel")) == 0) {
		//excel
	}


}

BOOL CtestInvoiceCheckDlg::DestroyWindow()
{
	delete pdf;

	return CDialogEx::DestroyWindow();
}