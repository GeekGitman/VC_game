
// gameView.h : CgameView 类的接口
//

#pragma once


class CgameView : public CView
{
protected: // 仅从序列化创建
	CgameView();
	DECLARE_DYNCREATE(CgameView)

// 特性
public:
	CgameDoc* GetDocument() const;
	int** themap;
	int m,n,lefttopx,lefttopy;
	bool lockmouse;
// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CgameView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
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

#ifndef _DEBUG  // gameView.cpp 中的调试版本
inline CgameDoc* CgameView::GetDocument() const
   { return reinterpret_cast<CgameDoc*>(m_pDocument); }
#endif

