// ZoneServer.cpp : 定义应用程序的类行为。
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



// CZoneServerApp 构造

CZoneServerApp::CZoneServerApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中

	GOOGLE_PROTOBUF_VERIFY_VERSION;
}


// 唯一的一个 CZoneServerApp 对象

CZoneServerApp theApp;

void myPurecallHandler(void)
{
	ErrorLn("虚函数调用异常！！！");

	//__asm{int 3};
	DebugBreak();
}

int memNotEnough(size_t s)
{
	//::MessageBox(NULL, "内存不足", "error", MB_OK|MB_ICONERROR);
	ErrorLn("内存不足!!! 无法分配："<< s << "B");
	//__asm{int 3};
	return 0;
}

// CZoneServerApp 初始化

BOOL CZoneServerApp::InitInstance()
{
	_set_purecall_handler(myPurecallHandler);
#ifdef RELEASEDEBUG
	_set_new_mode(1);
	_set_new_handler(memNotEnough);
#endif

	LoadLibrary("RICHED32.DLL");
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

    //  这里暂时将这个处理屏蔽，引入MFC自动化类会导致出现IEntity重复定义的错误，由于在项目实现中，除去对AfxEnableControlContainer()
    //  的调用外，并没有其他必需的Com支持，而对自定义的IEntity进行修改的话，不管是重命名还是使用命名空间，改动量和风险都较大，因此
    //  采用了将和Com相关的使用全部屏蔽的处理；
    //  如果后续开发中有迫切的Com支持需求，可以再考虑使用其他规避方法；
    //  added by wuhao，2009－11－09；
	//AfxEnableControlContainer();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	CZoneServerDlg dlg;
	m_pMainWnd = &dlg;

	INT_PTR nResponse = dlg.DoModal();

	if (nResponse == IDOK)
	{
		// TODO: 在此处放置处理何时用“确定”来关闭
		//  对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用“取消”来关闭
		//  对话框的代码
	}

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
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