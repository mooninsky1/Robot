// ZoneServer.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "ZoneServer.h"
#include "ZoneServerDlg.h"
#include "NetMsgHead.pb.h"
#include "google\protobuf\stubs\common.h"
#include <afx.h>
#include "DebugNew.h"

// #ifdef _DEBUG
// #define new DEBUG_NEW
// #endif

// CZoneServerApp

BEGIN_MESSAGE_MAP(CZoneServerApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()



// CZoneServerApp ����

CZoneServerApp::CZoneServerApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��

	GOOGLE_PROTOBUF_VERIFY_VERSION;
}


// Ψһ��һ�� CZoneServerApp ����

CZoneServerApp theApp;

void myPurecallHandler(void)
{
	ErrorLn("�麯�������쳣������");

	//__asm{int 3};
	DebugBreak();
}

int memNotEnough(size_t s)
{
	//::MessageBox(NULL, "�ڴ治��", "error", MB_OK|MB_ICONERROR);
	ErrorLn("�ڴ治��!!! �޷����䣺"<< s << "B");
	//__asm{int 3};
	return 0;
}

// CZoneServerApp ��ʼ��

BOOL CZoneServerApp::InitInstance()
{
	_set_purecall_handler(myPurecallHandler);
#ifdef RELEASEDEBUG
	_set_new_mode(1);
	_set_new_handler(memNotEnough);
#endif

	LoadLibrary("RICHED32.DLL");
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

    //  ������ʱ������������Σ�����MFC�Զ�����ᵼ�³���IEntity�ظ�����Ĵ�����������Ŀʵ���У���ȥ��AfxEnableControlContainer()
    //  �ĵ����⣬��û�����������Com֧�֣������Զ����IEntity�����޸ĵĻ�������������������ʹ�������ռ䣬�Ķ����ͷ��ն��ϴ����
    //  �����˽���Com��ص�ʹ��ȫ�����εĴ���
    //  ������������������е�Com֧�����󣬿����ٿ���ʹ��������ܷ�����
    //  added by wuhao��2009��11��09��
	//AfxEnableControlContainer();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	CZoneServerDlg dlg;
	m_pMainWnd = &dlg;

	INT_PTR nResponse = dlg.DoModal();

	if (nResponse == IDOK)
	{
		// TODO: �ڴ˴����ô����ʱ�á�ȷ�������ر�
		//  �Ի���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ�á�ȡ�������ر�
		//  �Ի���Ĵ���
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

#if defined(_DEBUG)
int __cdecl AllocHook(int nAllocType,
					   void * pvData,
					   size_t nSize,
					   int nBlockUse,
					   long lRequest,
					   const unsigned char * szFileName,
					   int nLine)
{
// 	static bool e = false;
// 	static int n = 2088;
// 
// 	if (e && nSize == n)
// 	{
// 		//TraceLn("dbg : " << (const char*)szFileName << " "<< nLine);
// 		DebugBreak();
// 	}
	static int n1 = 0;
	static int n2 = 0;
	static int n3 = 0;
	static int n4 = 0;
	static int n5 = 0;

	if (false && lRequest > 1100000)
	{
		if (nSize == 24)
		{
			if (n1 == 0)
			{
				n1 = lRequest;
			}
			else if (n2 == 0)
			{
				if (lRequest - n1 == 2)
					n2 = lRequest;
				else if (lRequest - n1 > 2)
				{
					n1 = n2 = n3 = n4 = n5 = 0;
				}
			}
			else if (n3 == 0)
			{
				if (lRequest - n2 >= 200 && lRequest - n2 <= 230)
					n3 = lRequest;
				else if (lRequest - n2 > 230)
				{
					n1 = n2 = n3 = n4 = n5 = 0;
				}
			}
			else if (n4 == 0)
			{
				if (lRequest - n3 >= 70 && lRequest - n3 <= 75)
				{
					n4 = lRequest;
				}
				else if (lRequest - n3 > 75)
				{
					n1 = n2 = n3 = n4 = n5 = 0;
				}
			}
			else if (n5 == 0)
			{
				if (lRequest - n4 == 176)
				{
					n5 = lRequest;
					DebugBreak();
				}
				else if (lRequest - n4 > 176)
				{
					n1 = n2 = n3 = n4 = n5 = 0;
				}
			}
		}
		else
		{
			//n1 = n2 = n3 = n4 = n5 = 0;
		}

	}

	return 1;
}
#pragma init_seg(lib)

class CFirstObject
{
public:
	CFirstObject()
	{
		_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);

		_CrtSetAllocHook(AllocHook);
		//_CrtSetBreakAlloc(270810);
	}

	~CFirstObject()
	{
		//_CrtDumpMemoryLeaks();
	}

};

CFirstObject g_firstObject;
#endif