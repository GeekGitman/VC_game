#pragma once


// DlgSAVE 对话框

class DlgSAVE : public CDialog
{
	DECLARE_DYNAMIC(DlgSAVE)

public:
	DlgSAVE(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DlgSAVE();

// 对话框数据
	enum { IDD = IDD_SAVE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
//	CEdit m_File;
	CString m_File;
	BOOL m_check;
	CString ifshow;
};
