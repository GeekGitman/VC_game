// NewDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "game.h"
#include "NewDlg.h"
#include "afxdialogex.h"


// CNewDlg 对话框

IMPLEMENT_DYNAMIC(CNewDlg, CDialog)

CNewDlg::CNewDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNewDlg::IDD, pParent)
	
{
	
}

CNewDlg::~CNewDlg()
{
}

void CNewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, new_combo);
	DDX_Control(pDX, IDC_SLIDER1, slide_x);
	DDX_Control(pDX, IDC_SLIDER2, slide_y);
	DDX_Control(pDX, IDC_EDIT1, show_x);
	DDX_Control(pDX, IDC_EDIT2, show_y);
}


BEGIN_MESSAGE_MAP(CNewDlg, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CNewDlg::OnCbnSelchangeCombo1)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER1, &CNewDlg::OnReleasedcaptureSlider1)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER2, &CNewDlg::OnReleasedcaptureSlider2)
END_MESSAGE_MAP()


// CNewDlg 消息处理程序


void CNewDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString size; CString s("随机");
	new_combo.GetLBText(new_combo.GetCurSel(),size);
	if(size==s){
		slide_x.EnableWindow(true); slide_y.EnableWindow(true);
		show_x.ShowWindow(true);show_y.ShowWindow(true);
	}
	else{
		slide_x.EnableWindow(false); slide_y.EnableWindow(false);
		show_x.ShowWindow(false);show_y.ShowWindow(false);
	}
	m_size=size;
	m_intx=slide_x.GetPos();
	m_inty=slide_y.GetPos();
}


BOOL CNewDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	new_combo.ResetContent();
	CString a("3*3");CString b("4*4");CString c("5*5");CString d("随机");
	new_combo.AddString(a);
	new_combo.AddString(b);
	new_combo.AddString(c);
	new_combo.AddString(d);
	new_combo.SetCurSel(0);m_size="3*3";
	//下面初始化滚动条
	slide_x.SetRange(3,7);
	slide_x.SetPos(3);
	slide_y.SetRange(3,7);
	slide_y.SetPos(3);
	CString str("3");
	show_x.ReplaceSel(str); show_y.ReplaceSel(str);
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CNewDlg::OnReleasedcaptureSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;CString str1;
	str1.Format(_T("%d"),slide_x.GetPos()); 
	show_x.SetSel(0, -1); 
	show_x.ReplaceSel(str1); 
	m_intx=slide_x.GetPos();
	UpdateData(FALSE);
}


void CNewDlg::OnReleasedcaptureSlider2(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	CString str1;
	str1.Format(_T("%d"),slide_y.GetPos()); 
	show_y.SetSel(0, -1); 
	show_y.ReplaceSel(str1); 
	m_inty=slide_y.GetPos();
	UpdateData(FALSE);
}


//void CNewDlg::OnClickedButton1()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	CString size;
//	new_combo.GetLBText(new_combo.GetCurSel(),size);
//}
