
// gameDoc.h : CgameDoc 类的接口
//


#pragma once
#include "map.h"

class CgameDoc : public CDocument
{
protected: // 仅从序列化创建
	CgameDoc();
	DECLARE_DYNCREATE(CgameDoc)

// 特性
public:
	int size;
	int m,n;
	int step;
	map* THISMAP;
	CString copypath;
	bool m_sign;     //正在播放标识
	MCIDEVICEID deviceID;  //设备ID
// 操作
public:
	bool OnTime();

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CgameDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
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
