
// gameView.h : CgameView ��Ľӿ�
//

#pragma once


class CgameView : public CView
{
protected: // �������л�����
	CgameView();
	DECLARE_DYNCREATE(CgameView)

// ����
public:
	CgameDoc* GetDocument() const;
	int** themap;
	int m,n,lefttopx,lefttopy;
	bool lockmouse;
// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ʵ��
public:
	virtual ~CgameView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
//	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void IWIN();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnEditLshow();
//	afx_msg void OnUpdateEditRecord(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // gameView.cpp �еĵ��԰汾
inline CgameDoc* CgameView::GetDocument() const
   { return reinterpret_cast<CgameDoc*>(m_pDocument); }
#endif

