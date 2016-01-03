
// gameView.cpp : CgameView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "game.h"
#endif

#include "gameDoc.h"
#include "gameView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CgameView

IMPLEMENT_DYNCREATE(CgameView, CView)

BEGIN_MESSAGE_MAP(CgameView, CView)
//	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
	ON_COMMAND(ID_EDIT_LSHOW, &CgameView::OnEditLshow)
//	ON_UPDATE_COMMAND_UI(ID_EDIT_RECORD, &CgameView::OnUpdateEditRecord)
END_MESSAGE_MAP()

// CgameView 构造/析构

CgameView::CgameView()
{
	// TODO: 在此处添加构造代码
	lockmouse=false;
}

CgameView::~CgameView()
{
}

BOOL CgameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CgameView 绘制

void CgameView::OnDraw(CDC* pDC)
{
	CgameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	if(pDoc->THISMAP==NULL) return;
	// TODO: 在此处为本机数据添加绘制代码
	themap=(pDoc->THISMAP)->THISMAP();
	if(!themap) return;
	CRect rectClient;
	GetClientRect(rectClient);
	CSize sizeClient=rectClient.Size();
	int kind=pDoc->size;
	m=pDoc->m; n=pDoc->n;
	//
	lefttopx=sizeClient.cx/2-n*40;
	lefttopy=sizeClient.cy/2-m*40;
	CBrush brush1(RGB(0,0,0)); CBrush brush2(RGB(255,255,255));
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			if(themap[i][j]==0) pDC->SelectObject(brush1);
			else pDC->SelectObject(brush2);
			pDC->RoundRect(lefttopx+j*80,lefttopy+i*80,lefttopx+j*80+80,lefttopy+i*80+80,10,10);
		}
	}
	//更新步数
	int step=pDoc->THISMAP->THISSTEP();
	CString text; text.Format(_T("步数： %d"),step); 
	CSize TextExt=pDC->GetTextExtent(text);
	pDC->TextOutW(sizeClient.cx-TextExt.cx-10,TextExt.cy,text);
}

void CgameView::OnRButtonUp(UINT  nFlags , CPoint point)
{
	//ClientToScreen(&point);
	//OnContextMenu(this, point);
	if(lockmouse==true){
		SetTimer(1,1500,NULL);
	}
}

//void CgameView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
//{
//#ifndef SHARED_HANDLERS
//	//theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
//#endif
//}


// CgameView 诊断

#ifdef _DEBUG
void CgameView::AssertValid() const
{
	CView::AssertValid();
}

void CgameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CgameDoc* CgameView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CgameDoc)));
	return (CgameDoc*)m_pDocument;
}
#endif //_DEBUG


// CgameView 消息处理程序


void CgameView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//Invalidate(FALSE);
	CgameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	if(pDoc->THISMAP==NULL) return;
	//当处在复盘阶段时
	if(lockmouse==true){             
		KillTimer(1);
		if(!pDoc->OnTime()){
			lockmouse=false;
		    delete pDoc->THISMAP;
		    pDoc->THISMAP=NULL;
		}
		Invalidate(FALSE);
		return;
	}                               
	//当不处在复盘阶段时
	int x=point.x;int y=point.y;
	int xindex=(x-lefttopx)/80;int yindex=(y-lefttopy)/80;
	if((x-lefttopx)<0 || xindex>=pDoc->n || (y-lefttopy)<0 || yindex>=pDoc->m) return;
	USES_CONVERSION;
	bool win=(pDoc->THISMAP)->NEXT(yindex,xindex,W2A(pDoc->copypath));
	//更新状态栏步数
	
	Invalidate(FALSE);
	if(win) IWIN();

	CView::OnLButtonUp(nFlags, point);
}

void CgameView::IWIN(){
	CgameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	if(pDoc->THISMAP==NULL) return;
	//
	Invalidate(TRUE);
	CString steps; 
	steps.Format(_T("%d步\n"),(pDoc->THISMAP)->THISSTEP());
	pDoc->THISMAP=NULL;
	CString message("你赢了！总共用了");
	message+=steps;
	MessageBox(message);
	AfxGetMainWnd()->GetMenu()->GetSubMenu(1)->CheckMenuItem(3, MF_UNCHECKED | MF_BYPOSITION);
}


void CgameView::OnTimer(UINT_PTR nIDEvent)
{
	CgameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	if(!pDoc->OnTime()){ 
		KillTimer(1);
		lockmouse=false;
		delete pDoc->THISMAP;
		pDoc->THISMAP=NULL;
	}
	Invalidate(FALSE);
	CView::OnTimer(nIDEvent);
}


void CgameView::OnEditLshow()
{
	// TODO: 在此添加命令处理程序代码
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CgameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//
	CString text("文件打开失败！");
	CString cap("错误");
	CString path; char* p =new char[50];
	CFileDialog dlg(true,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,(LPCTSTR)_TEXT("map FILES (*.re)|*.re||"),NULL);
	if(dlg.DoModal()==IDOK){
		path=dlg.GetPathName();
		USES_CONVERSION;
		p=W2A(path);
	}
	else return;
	//
	lockmouse=true;
	//
	if(pDoc->THISMAP) delete pDoc->THISMAP;
	pDoc->THISMAP=new map();
	if(!pDoc->THISMAP->LOADRESHOW(p)) {MessageBox(text);return;}
	int* s=pDoc->THISMAP->THISSIZE();
	pDoc->m=s[0];pDoc->n=s[1];
	Invalidate(FALSE);
	//设置定时器
	SetTimer(1,1500,NULL);
}


//void CgameView::OnUpdateEditRecord(CCmdUI *pCmdUI)
//{
//	// TODO: 在此添加命令更新用户界面处理程序代码
//	check_lupan=(!check_lupan);
//	pCmdUI->SetCheck(check_lupan);
//}
