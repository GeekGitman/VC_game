
// gameDoc.h : CgameDoc ��Ľӿ�
//


#pragma once
#include "map.h"

class CgameDoc : public CDocument
{
protected: // �������л�����
	CgameDoc();
	DECLARE_DYNCREATE(CgameDoc)

// ����
public:
	int size;
	int m,n;
	int step;
	map* THISMAP;
	CString copypath;
	bool m_sign;     //���ڲ��ű�ʶ
	MCIDEVICEID deviceID;  //�豸ID
// ����
public:
	bool OnTime();

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CgameDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
//	afx_msg void OnNew();
	afx_msg void OnFileNew();
	afx_msg void OnFileOpen();
	afx_msg void OnFileReboot();
	afx_msg void OnFileSave();
	afx_msg void OnEditUndo();
	afx_msg void OnEditRecord();
//	afx_msg void OnEditLshow();
	afx_msg void OnEditMusic();
	afx_msg void OnHelpShow();
};
