#pragma once


// DlgSAVE �Ի���

class DlgSAVE : public CDialog
{
	DECLARE_DYNAMIC(DlgSAVE)

public:
	DlgSAVE(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DlgSAVE();

// �Ի�������
	enum { IDD = IDD_SAVE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
//	CEdit m_File;
	CString m_File;
	BOOL m_check;
	CString ifshow;
};
