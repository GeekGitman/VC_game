
// gameDoc.cpp : CgameDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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


// CgameDoc ����/����

CgameDoc::CgameDoc()
{
	// TODO: �ڴ����һ���Թ������
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

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CgameDoc ���л�

void CgameDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}

#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void CgameDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
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

// ������������֧��
void CgameDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:  strSearchContent = _T("point;rectangle;circle;ole object;")��
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

// CgameDoc ���

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


// CgameDoc ����


//void CgameDoc::OnNew()
//{
//	// TODO: �ڴ���������������
//	CDialog newgame;
//	if(newgame.DoModal()==IDOK){
//		UpdateAllViews(NULL);
//	}
//}


void CgameDoc::OnFileNew()
{
	// TODO: �ڴ���������������
	
	//
	CNewDlg newgame;
	CString k1("3*3");CString k2("4*4");CString k3("5*5");CString k4("���");
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
	// TODO: �ڴ���������������
	//
	CString text("�ļ���ʧ�ܣ�");
	CString cap("����");
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
	// TODO: �ڴ���������������
	CString text("����û�п��֣�");
	CString cap("����");
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
	// TODO: �ڴ���������������
	CString text("����û�п��֣�");
	CString unsucc("����ʧ��!�����ļ��Ƿ��Ѵ��ڻ��ļ����Ƿ����Ҫ��");
	CString unsucc2("����ʧ�ܣ������ļ����Ƿ����Ҫ��");
	CString cap("����");
	if(THISMAP==NULL){
		MessageBox(0,text,cap,MB_ICONERROR);
		return;
	}
	DlgSAVE save;
	save.ifshow=CString("��ע�������ļ�����������Ŀ��Ŀ¼�µ�\"maps\"�ļ�����");
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
	// TODO: �ڴ���������������
	CString text("����û�п��֣�");
	CString text1("���ܺ��ˣ�����ǰ��������0���Ѻ���������");
	CString cap("����");
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
	// TODO: �ڴ���������������
	if(THISMAP==NULL){
		if(THISMAP==NULL){
		MessageBox(0,CString("����û�п��֣�"),CString("����"),MB_ICONERROR);
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
	  save.ifshow=CString("��ע�������ļ�����������Ŀ��Ŀ¼�µ�\"reshow\"�ļ�����");
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
//	// TODO: �ڴ���������������
//	CString text("�ļ���ʧ�ܣ�");
//	CString cap("����");
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
//	//���濪ʼ��̬��ʾ
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
	// TODO: �ڴ���������������
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
	//�����ж���û���ļ����ڲ��ţ�����У��ص����˳�
	CString filename; CString fileext; CString filepath;
	MCI_OPEN_PARMS mciOpenParms;
	CString pszFilter = _T("MP3 File (*.mp3)|*.mp3|WAV File(*.wav)|*.wav||");
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,pszFilter, NULL);
	dlg.m_ofn.lpstrInitialDir = _T("res\\music"); //���öԻ���Ĭ�ϳ��ֵ�·��
	if (dlg.DoModal()==IDOK){
		filename = dlg.GetFileName();	// ��ȡ�򿪵��ļ���
		fileext = dlg.GetFileExt();  // ��ȡ�򿪵��ļ���չ��
		filepath = dlg.GetPathName(); // ��ȡ���ļ���·��
		//�ȰѲ˵����
	    //if (state & MF_UNCHECKED){
          //pSubMenu->CheckMenuItem(2, MF_UNCHECKED | MF_BYPOSITION);
          pSubMenu->CheckMenuItem(2, MF_CHECKED | MF_BYPOSITION);
	    //}
	//
	}
	else{     //���ȡ����ֱ���˳�
		return;
	}
	//UpdateData(FALSE);
	if (!_tcscmp( _T("mp3"),fileext)) // �����Ϊmp3ʱ
		mciOpenParms.lpstrDeviceType = _T("mpegvideo");
	else if (!_tcscmp( _T("wav"), fileext)) // �����Ϊwavʱ
		mciOpenParms.lpstrDeviceType= _T("waveaudio");
	mciOpenParms.lpstrElementName = filepath; // ����·������mciOpenParms�ṹ����
	//���ʹ��ļ����MCI_OPEN_TYPE����˵���豸������������mciOpenParms�ṹ���У�
	//MCI_OPEN_ELEMENT����˵��Ҫ�򿪵��ļ���������mciOpenParams�ṹ����
	mciSendCommand(0,MCI_OPEN,MCI_OPEN_TYPE|MCI_OPEN_ELEMENT,(DWORD)(LPVOID)&mciOpenParms);
	deviceID = mciOpenParms.wDeviceID;//����ȡ���豸IDֵ����ȫ�ֱ���m_MCIDeviceID
	m_sign=false;
	/*************�����ļ�****************/
	MCI_PLAY_PARMS mciPlayParms;
	if (!m_sign){
		//���û�����ڲ��ŵ�����	
		//mciPlayParms.dwCallback = (long)GetSafeHwnd(); // Ϊ����MM_MCINOTIFY��Ϣָ�����ھ��
		mciPlayParms.dwFrom = 0;//���ò���λ��Ϊ0������ͷ��ʼ���ţ�
		mciSendCommand(deviceID, MCI_PLAY, MCI_FROM|MCI_NOTIFY,(DWORD)(LPVOID)&mciPlayParms);
		// ��ʼ��������������MCI_FROM˵����ʼ���ŵ�λ�ð�����mciPlayParms�ṹ����
		// ����MCI_NOTIFY�������ǲ��������MM_MCINOTIFY��Ϣ
		m_sign=true;
	}
}


void CgameDoc::OnHelpShow()
{
	// TODO: �ڴ���������������
	MessageBox(0,_T("�װ�����ʦ���ҵ�vs2010�޷���Ӷ�ý������Ľӿڣ���֪��ʲôԭ�������Ҿ�û������һ�顣"),_T("T_T"),MB_ICONERROR);
}
