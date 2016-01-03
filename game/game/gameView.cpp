
// gameView.cpp : CgameView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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

// CgameView ����/����

CgameView::CgameView()
{
	// TODO: �ڴ˴���ӹ������
	lockmouse=false;
}

CgameView::~CgameView()
{
}

BOOL CgameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CgameView ����

void CgameView::OnDraw(CDC* pDC)
{
	CgameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	if(pDoc->THISMAP==NULL) return;
	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
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
	//���²���
	int step=pDoc->THISMAP->THISSTEP();
	CString text; text.Format(_T("������ %d"),step); 
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


// CgameView ���

#ifdef _DEBUG
void CgameView::AssertValid() const
{
	CView::AssertValid();
}

void CgameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CgameDoc* CgameView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CgameDoc)));
	return (CgameDoc*)m_pDocument;
}
#endif //_DEBUG


// CgameView ��Ϣ�������


void CgameView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//Invalidate(FALSE);
	CgameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	if(pDoc->THISMAP==NULL) return;
	//�����ڸ��̽׶�ʱ
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
	//�������ڸ��̽׶�ʱ
	int x=point.x;int y=point.y;
	int xindex=(x-lefttopx)/80;int yindex=(y-lefttopy)/80;
	if((x-lefttopx)<0 || xindex>=pDoc->n || (y-lefttopy)<0 || yindex>=pDoc->m) return;
	USES_CONVERSION;
	bool win=(pDoc->THISMAP)->NEXT(yindex,xindex,W2A(pDoc->copypath));
	//����״̬������
	
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
	steps.Format(_T("%d��\n"),(pDoc->THISMAP)->THISSTEP());
	pDoc->THISMAP=NULL;
	CString message("��Ӯ�ˣ��ܹ�����");
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
	// TODO: �ڴ���������������
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CgameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//
	CString text("�ļ���ʧ�ܣ�");
	CString cap("����");
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
	//���ö�ʱ��
	SetTimer(1,1500,NULL);
}


//void CgameView::OnUpdateEditRecord(CCmdUI *pCmdUI)
//{
//	// TODO: �ڴ������������û����洦��������
//	check_lupan=(!check_lupan);
//	pCmdUI->SetCheck(check_lupan);
//}
