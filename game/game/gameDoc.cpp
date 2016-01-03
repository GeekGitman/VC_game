
// gameDoc.cpp : CgameDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "game.h"
#endif

#include "gameDoc.h"

#include <propkey.h>

#include "NewDlg.h"
#include "DlgSAVE.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CgameDoc

IMPLEMENT_DYNCREATE(CgameDoc, CDocument)

BEGIN_MESSAGE_MAP(CgameDoc, CDocument)
//	ON_COMMAND(ID_New, &CgameDoc::OnNew)
	ON_COMMAND(ID_FILE_NEW, &CgameDoc::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CgameDoc::OnFileOpen)
	ON_COMMAND(ID_FILE_REBOOT, &CgameDoc::OnFileReboot)
	ON_COMMAND(ID_FILE_SAVE, &CgameDoc::OnFileSave)
	ON_COMMAND(ID_EDIT_UNDO, &CgameDoc::OnEditUndo)
	ON_COMMAND(ID_EDIT_RECORD, &CgameDoc::OnEditRecord)
//	ON_COMMAND(ID_EDIT_LSHOW, &CgameDoc::OnEditLshow)
    ON_COMMAND(ID_EDIT_MUSIC, &CgameDoc::OnEditMusic)
	ON_COMMAND(ID_HELP_SHOW, &CgameDoc::OnHelpShow)
END_MESSAGE_MAP()


// CgameDoc 构造/析构

CgameDoc::CgameDoc()
{
	// TODO: 在此添加一次性构造代码
	size=0;m=0;n=0;step=0;
	THISMAP=NULL;
	copypath="";
	m_sign=false;
	deviceID=0;
}

CgameDoc::~CgameDoc()
{
}

BOOL CgameDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CgameDoc 序列化

void CgameDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CgameDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CgameDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:  strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CgameDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CgameDoc 诊断

#ifdef _DEBUG
void CgameDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CgameDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CgameDoc 命令


//void CgameDoc::OnNew()
//{
//	// TODO: 在此添加命令处理程序代码
//	CDialog newgame;
//	if(newgame.DoModal()==IDOK){
//		UpdateAllViews(NULL);
//	}
//}


void CgameDoc::OnFileNew()
{
	// TODO: 在此添加命令处理程序代码
	
	//
	CNewDlg newgame;
	CString k1("3*3");CString k2("4*4");CString k3("5*5");CString k4("随机");
	if(newgame.DoModal()==IDOK){
		if(THISMAP) delete THISMAP;
		AfxGetMainWnd()->GetMenu()->GetSubMenu(1)->CheckMenuItem(3, MF_UNCHECKED | MF_BYPOSITION);
		if(newgame.m_size==k1) {size=3;m=3;n=3;}
		else if(newgame.m_size==k2) {size=4;m=4;n=4;}
		else if(newgame.m_size==k3) {size=5;m=5;n=5;}
		else {size=0;
		      m=newgame.m_inty; n=newgame.m_intx;}
		if(size==0)
			THISMAP=new map(m,n);
		else
			THISMAP=new map(size);
		UpdateAllViews(NULL);
	}
}


void CgameDoc::OnFileOpen()
{
	// TODO: 在此添加命令处理程序代码
	//
	CString text("文件打开失败！");
	CString cap("错误");
	CString path; char* p =new char[50];
	CFileDialog dlg(true,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,(LPCTSTR)_TEXT("map FILES (*.gmap)|*.gmap||"),NULL);
	if(dlg.DoModal()==IDOK){
		path=dlg.GetPathName();
		USES_CONVERSION;
		p=W2A(path);
	}
	else return;
	if(THISMAP) delete THISMAP;
	THISMAP=new map();
	AfxGetMainWnd()->GetMenu()->GetSubMenu(1)->CheckMenuItem(3, MF_UNCHECKED | MF_BYPOSITION);
	THISMAP->SETCOPY(false,false);
	if(!THISMAP->LOAD(p)) MessageBox(0,text,cap,MB_ICONERROR);
	int* s=THISMAP->THISSIZE();
	m=s[0];n=s[1];
	UpdateAllViews(NULL);
}


void CgameDoc::OnFileReboot()
{
	// TODO: 在此添加命令处理程序代码
	CString text("您还没有开局！");
	CString cap("错误");
	if(THISMAP==NULL){
		MessageBox(0,text,cap,MB_ICONERROR);
		return;
	}
	bool is=THISMAP->RELOAD();
	if(!is)
		MessageBox(0,text,cap,MB_ICONERROR);
	UpdateAllViews(NULL);
}


void CgameDoc::OnFileSave()
{
	// TODO: 在此添加命令处理程序代码
	CString text("您还没有开局！");
	CString unsucc("保存失败!请检查文件是否已存在或文件名是否符合要求");
	CString unsucc2("保存失败！请检查文件名是否符合要求");
	CString cap("错误");
	if(THISMAP==NULL){
		MessageBox(0,text,cap,MB_ICONERROR);
		return;
	}
	DlgSAVE save;
	save.ifshow=CString("【注】您的文件将保存在项目根目录下的\"maps\"文件夹中");
	CString path;
	char* P; 
	if(save.DoModal()==IDOK){
		path=save.m_File;
		USES_CONVERSION;
		P=W2A(path);
		if(save.m_check){
			if(THISMAP->SAVE(P,1)){
				MessageBox(0,unsucc2,cap,MB_ICONERROR);
			}
		}
		else{
			if(!THISMAP->SAVE(P,0)){
				MessageBox(0,unsucc,cap,MB_ICONERROR);
			}
		}
	}
}


void CgameDoc::OnEditUndo()
{
	// TODO: 在此添加命令处理程序代码
	CString text("您还没有开局！");
	CString text1("不能后退！（当前步数等于0或已后退两步）");
	CString cap("错误");
	if(THISMAP==NULL){
		MessageBox(0,text,cap,MB_ICONERROR);
		return;
	}
	if(!THISMAP->PRESTEP()){
		MessageBox(0,text1,cap,MB_ICONERROR);
	}
	UpdateAllViews(NULL);
}


void CgameDoc::OnEditRecord()
{
	// TODO: 在此添加命令处理程序代码
	if(THISMAP==NULL){
		if(THISMAP==NULL){
		MessageBox(0,CString("您还没有开局！"),CString("错误"),MB_ICONERROR);
		return;
	}
	}
	CMenu *pMenu=AfxGetMainWnd()->GetMenu();
	ASSERT_VALID(pMenu);
	CMenu *pSubMenu=pMenu->GetSubMenu(1);
	ASSERT_VALID(pSubMenu);
	UINT state = pSubMenu->GetMenuState(3,MF_BYPOSITION);
	ASSERT(state != 0xFFFFFFFF);
	if (state & MF_CHECKED){
      pSubMenu->CheckMenuItem(3, MF_UNCHECKED | MF_BYPOSITION);
	  THISMAP->SETCOPY(false,false);
	}
   else{
      pSubMenu->CheckMenuItem(3, MF_CHECKED | MF_BYPOSITION);
	  DlgSAVE save;
	  save.ifshow=CString("【注】您的文件将保存在项目根目录下的\"reshow\"文件夹中");
	  CString path;
	  char* P; 
	  if(save.DoModal()==IDOK){
		  path=save.m_File;
		  //USES_CONVERSION;
		  //P=W2A(path);
		  THISMAP->SETCOPY(true,save.m_check);
		  copypath=path;
	  }
	  else{
		  pSubMenu->CheckMenuItem(3, MF_UNCHECKED | MF_BYPOSITION);
		  THISMAP->SETCOPY(false,false);
	  }
   }
}


//void CgameDoc::OnEditLshow()
//{
//	// TODO: 在此添加命令处理程序代码
//	CString text("文件打开失败！");
//	CString cap("错误");
//	CString path; char* p =new char[50];
//	CFileDialog dlg(true,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,(LPCTSTR)_TEXT("map FILES (*.re)|*.re||"),NULL);
//	if(dlg.DoModal()==IDOK){
//		path=dlg.GetPathName();
//		USES_CONVERSION;
//		p=W2A(path);
//	}
//	else return;
//	
//	if(THISMAP) delete THISMAP;
//	THISMAP=new map();
//	if(!THISMAP->LOADRESHOW(p)) {MessageBox(0,text,cap,MB_ICONERROR);return;}
//	int* s=THISMAP->THISSIZE();
//	m=s[0];n=s[1];
//	UpdateAllViews(NULL);
//	//下面开始动态显示
//	
//}

bool CgameDoc::OnTime(){
	point* t;
	if(THISMAP->HASRESHOWNEXT()){
		//
		t=THISMAP->RESHOWNEXT();
		UpdateAllViews(NULL);
		return true;
	}
	else
		return false;
}


void CgameDoc::OnEditMusic()
{
	// TODO: 在此添加命令处理程序代码
	CMenu *pMenu=AfxGetMainWnd()->GetMenu();
	ASSERT_VALID(pMenu);
	CMenu *pSubMenu=pMenu->GetSubMenu(1);
	ASSERT_VALID(pSubMenu);
	UINT state = pSubMenu->GetMenuState(2,MF_BYPOSITION);
	ASSERT(state != 0xFFFFFFFF);
	if (state & MF_CHECKED){
        pSubMenu->CheckMenuItem(2, MF_UNCHECKED | MF_BYPOSITION);
	}
	//
	if(m_sign){
	    if(!mciSendCommand(deviceID, MCI_CLOSE, 0, NULL))
		    m_sign=false;
		return;
	}
	//首先判断有没有文件正在播放，如果有，关掉，退出
	CString filename; CString fileext; CString filepath;
	MCI_OPEN_PARMS mciOpenParms;
	CString pszFilter = _T("MP3 File (*.mp3)|*.mp3|WAV File(*.wav)|*.wav||");
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,pszFilter, NULL);
	dlg.m_ofn.lpstrInitialDir = _T("res\\music"); //设置对话框默认呈现的路径
	if (dlg.DoModal()==IDOK){
		filename = dlg.GetFileName();	// 获取打开的文件名
		fileext = dlg.GetFileExt();  // 获取打开的文件扩展名
		filepath = dlg.GetPathName(); // 获取打开文件的路径
		//先把菜单项打勾
	    //if (state & MF_UNCHECKED){
          //pSubMenu->CheckMenuItem(2, MF_UNCHECKED | MF_BYPOSITION);
          pSubMenu->CheckMenuItem(2, MF_CHECKED | MF_BYPOSITION);
	    //}
	//
	}
	else{     //点击取消，直接退出
		return;
	}
	//UpdateData(FALSE);
	if (!_tcscmp( _T("mp3"),fileext)) // 当后辍为mp3时
		mciOpenParms.lpstrDeviceType = _T("mpegvideo");
	else if (!_tcscmp( _T("wav"), fileext)) // 当后辍为wav时
		mciOpenParms.lpstrDeviceType= _T("waveaudio");
	mciOpenParms.lpstrElementName = filepath; // 将打开路径存入mciOpenParms结构体中
	//发送打开文件命令，MCI_OPEN_TYPE参数说明设备类型名包含在mciOpenParms结构体中，
	//MCI_OPEN_ELEMENT参数说明要打开的文件名包含在mciOpenParams结构体中
	mciSendCommand(0,MCI_OPEN,MCI_OPEN_TYPE|MCI_OPEN_ELEMENT,(DWORD)(LPVOID)&mciOpenParms);
	deviceID = mciOpenParms.wDeviceID;//将获取的设备ID值赋给全局变量m_MCIDeviceID
	m_sign=false;
	/*************播放文件****************/
	MCI_PLAY_PARMS mciPlayParms;
	if (!m_sign){
		//如果没有正在播放的声音	
		//mciPlayParms.dwCallback = (long)GetSafeHwnd(); // 为发送MM_MCINOTIFY消息指定窗口句柄
		mciPlayParms.dwFrom = 0;//设置播放位置为0（即从头开始播放）
		mciSendCommand(deviceID, MCI_PLAY, MCI_FROM|MCI_NOTIFY,(DWORD)(LPVOID)&mciPlayParms);
		// 开始播放声音，参数MCI_FROM说明开始播放的位置包含在mciPlayParms结构体中
		// 参数MCI_NOTIFY的意义是播放完后发送MM_MCINOTIFY消息
		m_sign=true;
	}
}


void CgameDoc::OnHelpShow()
{
	// TODO: 在此添加命令处理程序代码
	MessageBox(0,_T("亲爱的老师，我的vs2010无法添加多媒体所需的接口，不知道什么原因，所以我就没有做这一块。"),_T("T_T"),MB_ICONERROR);
}
