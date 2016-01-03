#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CNewDlg 对话框

class CNewDlg : public CDialog
{
	DECLARE_DYNAMIC(CNewDlg)

public:
	CNewDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CNewDlg();

// 对话框数据
	enum { IDD = ID_New };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox new_combo;
	afx_msg void OnCbnSelchangeCombo1();
	CSliderCtrl slide_x;
	CSliderCtrl slide_y;
	CEdit show_x;
	CEdit show_y;
	virtual BOOL OnInitDialog();
	afx_msg void OnReleasedcaptureSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnReleasedcaptureSlider2(NMHDR *pNMHDR, LRESULT *pResult);
//	afx_msg void OnClickedButton1();
	CString m_size;
	int m_intx;
	int m_inty;
};
