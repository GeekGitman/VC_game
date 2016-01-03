// DlgSAVE.cpp : 实现文件
//

#include "stdafx.h"
#include "game.h"
#include "DlgSAVE.h"
#include "afxdialogex.h"


// DlgSAVE 对话框

IMPLEMENT_DYNAMIC(DlgSAVE, CDialog)

DlgSAVE::DlgSAVE(CWnd* pParent /*=NULL*/)
	: CDialog(DlgSAVE::IDD, pParent)
	, ifshow(_T(""))
{

	m_File = _T("");
}

DlgSAVE::~DlgSAVE()
{
}

void DlgSAVE::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_EDIT1, m_File);
	DDX_Text(pDX, IDC_EDIT1, m_File);
	DDX_Check(pDX, IDC_CHECK1, m_check);
	DDX_Text(pDX, IDC_ifshow, ifshow);
}


BEGIN_MESSAGE_MAP(DlgSAVE, CDialog)
END_MESSAGE_MAP()


// DlgSAVE 消息处理程序

