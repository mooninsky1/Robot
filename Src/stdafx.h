// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN		// �� Windows ͷ���ų�����ʹ�õ�����
#endif

// ���������ʹ��������ָ����ƽ̨֮ǰ��ƽ̨�����޸�����Ķ��塣
// �йز�ͬƽ̨����Ӧֵ��������Ϣ����ο� MSDN��
#ifndef WINVER				// ����ʹ���ض��� Windows XP ����߰汾�Ĺ��ܡ�
#define WINVER 0x0501		// ����ֵ����Ϊ��Ӧ��ֵ���������� Windows �������汾��
#endif

#ifndef _WIN32_WINNT		// ����ʹ���ض��� Windows XP ����߰汾�Ĺ��ܡ�
#define _WIN32_WINNT 0x0501	// ����ֵ����Ϊ��Ӧ��ֵ���������� Windows �������汾��
#endif						

#ifndef _WIN32_WINDOWS		// ����ʹ���ض��� Windows 98 ����߰汾�Ĺ��ܡ�
#define _WIN32_WINDOWS 0x0410 // ��������Ϊ�ʺ� Windows Me ����߰汾����Ӧֵ��
#endif

#ifndef _WIN32_IE			// ����ʹ���ض��� IE 6.0 ����߰汾�Ĺ��ܡ�
#define _WIN32_IE 0x0600	// ����ֵ����Ϊ��Ӧ��ֵ���������� IE �������汾��ֵ��
#endif

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// ĳЩ CString ���캯��������ʽ��

// �ر� MFC ��ĳЩ�����������ɷ��ĺ��Եľ�����Ϣ������

#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ

//  ������ʱ������������Σ�����MFC�Զ�����ᵼ�³���IEntity�ظ�����Ĵ�����������Ŀʵ���У���ȥ��AfxEnableControlContainer()
//  �ĵ����⣬��û�����������Com֧�֣������Զ����IEntity�����޸ĵĻ�������������������ʹ�������ռ䣬�Ķ����ͷ��ն��ϴ����
//  �����˽���Com��ص�ʹ��ȫ�����εĴ���
//  ������������������е�Com֧�����󣬿����ٿ���ʹ��������ܷ�����
//  added by wuhao��2009��11��09��
//#include <afxdisp.h>        // MFC �Զ�����

#ifndef _AFX_NO_OLE_SUPPORT
//  ������ʱ������������Σ�����MFC�Զ�����ᵼ�³���IEntity�ظ�����Ĵ�����������Ŀʵ���У���ȥ��AfxEnableControlContainer()
//  �ĵ����⣬��û�����������Com֧�֣������Զ����IEntity�����޸ĵĻ�������������������ʹ�������ռ䣬�Ķ����ͷ��ն��ϴ����
//  �����˽���Com��ص�ʹ��ȫ�����εĴ���
//  ������������������е�Com֧�����󣬿����ٿ���ʹ��������ܷ�����
//  added by wuhao��2009��11��09��
//#include <afxdtctl.h>		// MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT


#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif

// #if defined(_DEBUG)
// 
// #pragma message("�����ڴ�й¶���")
// 
// #define _CRTDBG_MAP_ALLOC
// 
// #include <stdlib.h>
// #include <crtdbg.h>
// 
// #endif

#include "Base.h"
//#define new RKT_NEW
using namespace rkt;
//#include "TimerAxis.h"
#pragma comment(lib, MAKE_DLL_LIB_NAME(Base))

//#include "DGlobalGame.h"
//#include "DGlobalMessage.h"
//#include "DEntityProp.h"
//#include "DEntityBuild.h"
//#include "DGlobalEvent.h"
//#include "DTaskServer.h"
//
//#include "tinyxml.h"
//#include "tinystr.h"
//#include "IEventEngine.h"
//#include "ILuaEngine.h"
//#include "ISchemeEngine.h"
//#include "IDBEngine.h"
//#include "ILuaServer.h"
//#include "IZoneManager.h"
//#include "IEntityServer.h"
//#include "net.h"
//#include "IBuffServer.h"
//#include "IEffectServer.h"
//#include "IAttackServer.h"
//#include "ISkillManager.h"
//#include "IFreezeServer.h"
//#include "ITrackServer.h"
//#include "ILoginServerConnector.h"
//#include "ICampServer.h"
//#include "IAIServer.h"
//#include "IPKModeServer.h"
//#include "IGoodsFunctionServer.h"
//#include "ITradeServer.h"
//#include "IStackWalk.h"
//#include "ICollectionServer.h"
//#include "IOnlineShopServer.h"
//#include "IClientConnectionManager.h"
//using namespace LoginServerConnector;
