// ZoneServerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include <Winsock2.h>
#include "ZoneServer.h"
#include "ZoneServerDlg.h"
#include "ZoneServerControl.h"
#include "RobotServiceProvider.h"
#include "ExternalFacade.h"
#include "DebugNew.h"

// #ifdef _DEBUG
// #define new DEBUG_NEW
// #endif


CZoneServerDlg * g_pZoneServerDlg = NULL;

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CZoneServerDlg �Ի���
CZoneServerDlg::CZoneServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CZoneServerDlg::IDD, pParent)
	, m_stringLuaFile(_T(""))
	, m_ZoneServerID(0)
	, m_ZoneServerName(_T(""))
	, m_CenterServerIP(_T(""))
	, m_CenterServerPort(0)
	, m_loginServerPort(0)
	, m_loginServerIP(0)
	, m_portForClient(0)
	, m_portForGM(0)
{
	//	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);	
	g_pZoneServerDlg = this;

	//m_pTraceListener = NULL;
}

void CZoneServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_COMBO_SCHEME, m_ComboScheme);
	DDX_Control(pDX, IDC_EDIT_LUA, m_EditLuaFile);
	DDX_Text(pDX, IDC_EDIT_LUA, m_stringLuaFile);
	DDX_Text(pDX, IDC_EDIT_ZONEID, m_ZoneServerID);
	DDV_MinMaxLong(pDX, m_ZoneServerID, 0, 2048);
	DDX_Text(pDX, IDC_EDIT_ZONENAME, m_ZoneServerName);
	DDX_Text(pDX, IDC_EDIT_CENTERIP, m_CenterServerIP);
	DDX_Text(pDX, IDC_EDIT_CENTERPORT, m_CenterServerPort);
	DDV_MinMaxLong(pDX, m_CenterServerPort, 0, 65535);
	DDX_Text(pDX, IDC_LOGIN_SERVER_PORT, m_loginServerPort);
	DDX_IPAddress(pDX, IDC_LOGIN_SERVER_IPADDRESS, m_loginServerIP);
	DDX_Text(pDX, IDC_EDIT_ZONE_PORT, m_portForClient);
	DDX_Text(pDX, IDC_EDIT_GM_PORT, m_portForGM);
}

BEGIN_MESSAGE_MAP(CZoneServerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()

	ON_BN_CLICKED(IDSTART, &CZoneServerDlg::OnBnClickedStart)
	ON_BN_CLICKED(IDCLOSE, &CZoneServerDlg::OnBnClickedClose)

	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_SCHEME, &CZoneServerDlg::OnBnClickedButtonScheme)
	ON_BN_CLICKED(IDC_BUTTON_LUA, &CZoneServerDlg::OnBnClickedButtonLua)
	ON_BN_CLICKED(IDC_BUTTON_SCANLUA, &CZoneServerDlg::OnBnClickedButtonScanlua)
	ON_CBN_SETFOCUS(IDC_COMBO_SCHEME, &CZoneServerDlg::OnCbnSetfocusComboScheme)
	ON_EN_CHANGE(IDC_EDIT_ZONEID, &CZoneServerDlg::OnEnChangeEditZoneID)
	ON_EN_CHANGE(IDC_EDIT_ZONENAME, &CZoneServerDlg::OnEnChangeEditZoneName)
	ON_EN_CHANGE(IDC_EDIT_CENTERIP, &CZoneServerDlg::OnEnChangeEditCenterIP)
	ON_EN_CHANGE(IDC_EDIT_CENTERPORT, &CZoneServerDlg::OnEnChangeEditCenterPort)
	ON_BN_CLICKED(IDC_BTN_CLEAR, &CZoneServerDlg::OnBnClickedBtnClear)
	ON_BN_CLICKED(IDC_CHECK_INFO, &CZoneServerDlg::OnBnClickedCheckInfo)
	ON_BN_CLICKED(IDC_CHECK_TRACE, &CZoneServerDlg::OnBnClickedCheckTrace)
	ON_BN_CLICKED(IDC_CHECK_WARNING, &CZoneServerDlg::OnBnClickedCheckWarning)
	ON_BN_CLICKED(IDC_CHECK_ERROR, &CZoneServerDlg::OnBnClickedCheckError)
	ON_EN_CHANGE(IDC_LOGIN_SERVER_PORT, &CZoneServerDlg::OnEnChangeLoginServerPort)
	ON_NOTIFY(IPN_FIELDCHANGED, IDC_LOGIN_SERVER_IPADDRESS, &CZoneServerDlg::OnIpnFieldchangedLoginServerIpaddress)
	ON_EN_CHANGE(IDC_EDIT_ZONE_PORT, &CZoneServerDlg::OnEnChangeEditZonePort)
	ON_EN_CHANGE(IDC_EDIT_GM_PORT, &CZoneServerDlg::OnEnChangeEditGMPort)
	ON_BN_CLICKED(IDC_LOGIC_ERROR_LOCATE, &CZoneServerDlg::OnBnClickedLogicErrorLocate)
END_MESSAGE_MAP()

CWnd * g_pTempWnd = NULL;
#define ENABLE_WINDOW(itemid, flag)			\
	g_pTempWnd = GetDlgItem(itemid);		\
	if(g_pTempWnd != NULL)					\
{										\
	g_pTempWnd->EnableWindow(flag);	\
}

// CZoneServerDlg ��Ϣ�������
BOOL CZoneServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	ENABLE_WINDOW(IDC_EDIT_ZONEID, false);
	ENABLE_WINDOW(IDC_EDIT_ZONENAME, false);
	ENABLE_WINDOW(IDC_EDIT_CENTERIP, false);
	ENABLE_WINDOW(IDC_EDIT_CENTERPORT, false);
	ENABLE_WINDOW(IDC_LOGIN_SERVER_IPADDRESS, false);
	ENABLE_WINDOW(IDC_LOGIN_SERVER_PORT, false);
	ENABLE_WINDOW(IDC_EDIT_ZONE_PORT, false);
	ENABLE_WINDOW(IDC_EDIT_GM_PORT, false);

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		BOOL bRet = strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	CButton *btn = NULL;

	btn = (CButton*)GetDlgItem(IDC_CHECK_INFO);
	if (btn)	btn->SetCheck(FALSE);

	btn = (CButton*)GetDlgItem(IDC_CHECK_TRACE);
	if (btn)	btn->SetCheck(FALSE);

	btn = (CButton*)GetDlgItem(IDC_CHECK_WARNING);
	if (btn)	btn->SetCheck(FALSE);

	btn = (CButton*)GetDlgItem(IDC_CHECK_ERROR);
	if (btn)	btn->SetCheck(FALSE);
	SetViewLevel();

	CWnd *pRichedit = GetDlgItem(IDC_RICHEDIT_TRACE);
	m_MyTraceListener.SetWnd(pRichedit->GetSafeHwnd());
	m_MyTraceListener.SetMainWnd(GetSafeHwnd());
	m_MyTraceListener.SetMainThreadID(GetCurrentThreadId());
	m_MyTraceListener.SetPostWMsgIndex(WM_MYPRINT);
	m_MyTraceListener.setHasTime(true);
	registerTrace((rkt::TraceListener*)(&m_MyTraceListener));

	
	g_pServiceProvider = new CRobotServiceProvider();
	if(!g_pServiceProvider->InitEnvironment())
	{
		// ��ʼ������
		InitUIConfig();

		ErrorLn("��ʼ������������ʧ��... ...");
		return FALSE;
	}

	// ��ʼ������
	InitUIConfig();

	for (int i = 0; i < __argc; ++i)
	{
		TraceLn(__argv[i]);
	}

	Trace("��ʼ�������������ɹ�... ..." << endl);



	if (__argc >= 2)
	{
		if (strcmp(__argv[1], "autostart") == 0)
		{
			OnBnClickedStart();
		}
	}

	g_pServiceProvider->SetMainWnd( GetSafeHwnd() );

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CZoneServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CZoneServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CZoneServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// IDSTART
void CZoneServerDlg::OnBnClickedStart(void)
{
	
	ENABLE_WINDOW(IDSTART, false);
	/*
	ENABLE_WINDOW(IDC_EDIT_ZONEID, false);
	ENABLE_WINDOW(IDC_EDIT_ZONENAME, false);
	ENABLE_WINDOW(IDC_EDIT_CENTERIP, false);
	ENABLE_WINDOW(IDC_EDIT_CENTERPORT, false);
	ENABLE_WINDOW(IDC_LOGIN_SERVER_IPADDRESS, false);
	ENABLE_WINDOW(IDC_LOGIN_SERVER_PORT, false);
	ENABLE_WINDOW(IDC_EDIT_ZONE_PORT, false);
	*/
	g_pServiceProvider->Login();
	g_ZoneServerControl.SetUIControl(EZoneServer_UIControl_StartService);
}

// IDCLOSE
void CZoneServerDlg::OnBnClickedClose(void)
{
	ENABLE_WINDOW(IDCLOSE, false);

	if(getProfile())
	{
		getProfile()->WriteLog2File("ZoneServerPerfProf.txt");
	}
	g_ZoneServerControl.SetUIControl(EZoneServer_UIControl_StopService);
}

void CZoneServerDlg::OnCancel()
{
	if (IDYES != MessageBox("��ȷ���˳���", "����������", MB_ICONQUESTION | MB_YESNO))
	{
		return;
	}

	OnBnClickedClose();

	//CDialog::OnCancel();
}

// 
void CZoneServerDlg::OnBnClickedButtonScheme()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nCurSel = m_ComboScheme.GetCurSel();
	if(nCurSel < 0)
	{
		return;
	}

	CString rString;
	m_ComboScheme.GetLBText(nCurSel, rString);
	if(rString.IsEmpty())
	{
		return;
	}

	g_ZoneServerControl.m_stringWaitDynamic.clear();
	g_ZoneServerControl.m_stringWaitDynamic = rString;
	g_ZoneServerControl.SetUIControl(EZoneServer_UIControl_UpdateScheme);
}

void CZoneServerDlg::OnBnClickedButtonLua()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
// 	if(m_stringLuaFile.IsEmpty())
// 	{
// 		return;
// 	}
// 
// 	g_ZoneServerControl.m_stringWaitDynamic.clear();
// 	g_ZoneServerControl.m_stringWaitDynamic = m_stringLuaFile;
// 	g_ZoneServerControl.SetUIControl(EZoneServer_UIControl_UpdateLua);
}

void CZoneServerDlg::OnBnClickedButtonScanlua()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	char szOldCurrentDirector[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, szOldCurrentDirector);	
	CFileDialog FileDialog(true, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "Lua Files (*.lua)|*.lua|All Files (*.*)|*.*||", this);
	FileDialog.DoModal();
	m_stringLuaFile = FileDialog.GetPathName();
	UpdateData(FALSE);
}

void CZoneServerDlg::OnCbnSetfocusComboScheme()
{
	
}

void CZoneServerDlg::OnEnChangeEditZoneID()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	OnEnChangeEdit();
}

void CZoneServerDlg::OnEnChangeEditZoneName()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	OnEnChangeEdit();
}

void CZoneServerDlg::OnEnChangeEditCenterIP()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	OnEnChangeEdit();
}

void CZoneServerDlg::OnEnChangeEditCenterPort()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	OnEnChangeEdit();
}

void CZoneServerDlg::OnEnChangeEdit(void)
{
	UpdateData(TRUE);
}

void CZoneServerDlg::InitUIConfig(void)
{
	UpdateData(FALSE);
}

void CZoneServerDlg::OnBnClickedBtnClear()
{
	m_MyTraceListener.ClearTrace();
}

void CZoneServerDlg::OnBnClickedCheckInfo()
{
	SetViewLevel();
}

void CZoneServerDlg::OnBnClickedCheckTrace()
{
	SetViewLevel();
}

void CZoneServerDlg::OnBnClickedCheckWarning()
{
	SetViewLevel();
}

void CZoneServerDlg::OnBnClickedCheckError()
{
	SetViewLevel();
}

void CZoneServerDlg::SetViewLevel()
{
	int level = 0;
	CButton *btn = NULL;
	
	btn = (CButton*)GetDlgItem(IDC_CHECK_INFO);
	if (btn && btn->GetCheck())
		level = level | rkt::levelInfo;

	btn = (CButton*)GetDlgItem(IDC_CHECK_TRACE);
	if (btn && btn->GetCheck())
		level = level | rkt::levelTrace;

	btn = (CButton*)GetDlgItem(IDC_CHECK_WARNING);
	if (btn && btn->GetCheck())
		level = level | rkt::levelWarning;

	btn = (CButton*)GetDlgItem(IDC_CHECK_ERROR);
	if (btn && btn->GetCheck())
		level = level | rkt::levelError;

	m_MyTraceListener.SetViewLevel((TraceLevel)level);
}

LRESULT CZoneServerDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CALCULA_PERSON:
		{
			char text[32] = "";

			_snprintf_s(text, _TRUNCATE, "%d", wParam);
			SetDlgItemText(IDC_STATIC_ONLINENUM, text);
		}
		break;
	case WM_CALCULA_PERSON_REAL:
		{
			char text[32] = "";

			_snprintf_s(text, _TRUNCATE, "%d", wParam);
			SetDlgItemText(IDC_STATIC_ONLINENUM_REAL, text);
		}
		break;
	case WM_CLOSE_SERVER:
		{
			ENABLE_WINDOW(IDSTART, true);
		}
		break;
	case WM_CLOSE_PROGRAM:
		{
			g_pServiceProvider->CloseService();
			delete g_pServiceProvider;
			unregisterTrace((rkt::TraceListener*)(&m_MyTraceListener));
			closeTrace();
			g_pServiceProvider = NULL;
			CDialog::OnCancel();
		}
		break;
	case WM_MYPRINT:
		{
			TraceLevel level = (TraceLevel)wParam;
			char *msg = (char*)lParam;

			if (wParam == NULL && msg == NULL)
			{
				m_MyTraceListener.ClearContent();
			}
			else
			{
				m_MyTraceListener.AddToRichEdit(level, msg, true);
			}
		}
		break;
	case WM_UPDATE_UI:
		{
			InitUIConfig();
		}
		break;
	default:
		break;
	}

	return CDialog::WindowProc(message, wParam, lParam);
}

void CZoneServerDlg::OnEnChangeLoginServerPort()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	OnEnChangeEdit();
}

void CZoneServerDlg::OnIpnFieldchangedLoginServerIpaddress(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMIPADDRESS pIPAddr = reinterpret_cast<LPNMIPADDRESS>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	OnEnChangeEdit();
}

void CZoneServerDlg::OnEnChangeEditZonePort()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	OnEnChangeEdit();
}

void CZoneServerDlg::OnEnChangeEditGMPort()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	OnEnChangeEdit();
}

void CZoneServerDlg::OnBnClickedLogicErrorLocate()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CButton *btn = (CButton*)GetDlgItem(IDC_LOGIC_ERROR_LOCATE);

	if (btn != NULL)
	{
		g_pServiceProvider->SetLogicErrorLocate((bool)btn->GetCheck());
	}
}
