#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CNewDlg �Ի���

class CNewDlg : public CDialog
{
	DECLARE_DYNAMIC(CNewDlg)

public:
	CNewDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CNewDlg();

// �Ի�������
	enum { IDD = ID_New };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
