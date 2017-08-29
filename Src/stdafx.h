// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN		// 从 Windows 头中排除极少使用的资料
#endif

// 如果您必须使用下列所指定的平台之前的平台，则修改下面的定义。
// 有关不同平台的相应值的最新信息，请参考 MSDN。
#ifndef WINVER				// 允许使用特定于 Windows XP 或更高版本的功能。
#define WINVER 0x0501		// 将此值更改为相应的值，以适用于 Windows 的其他版本。
#endif

#ifndef _WIN32_WINNT		// 允许使用特定于 Windows XP 或更高版本的功能。
#define _WIN32_WINNT 0x0501	// 将此值更改为相应的值，以适用于 Windows 的其他版本。
#endif						

#ifndef _WIN32_WINDOWS		// 允许使用特定于 Windows 98 或更高版本的功能。
#define _WIN32_WINDOWS 0x0410 // 将它更改为适合 Windows Me 或更高版本的相应值。
#endif

#ifndef _WIN32_IE			// 允许使用特定于 IE 6.0 或更高版本的功能。
#define _WIN32_IE 0x0600	// 将此值更改为相应的值，以适用于 IE 的其他版本。值。
#endif

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// 某些 CString 构造函数将是显式的

// 关闭 MFC 对某些常见但经常可放心忽略的警告消息的隐藏

#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展

//  这里暂时将这个处理屏蔽，引入MFC自动化类会导致出现IEntity重复定义的错误，由于在项目实现中，除去对AfxEnableControlContainer()
//  的调用外，并没有其他必需的Com支持，而对自定义的IEntity进行修改的话，不管是重命名还是使用命名空间，改动量和风险都较大，因此
//  采用了将和Com相关的使用全部屏蔽的处理；
//  如果后续开发中有迫切的Com支持需求，可以再考虑使用其他规避方法；
//  added by wuhao，2009－11－09；
//#include <afxdisp.h>        // MFC 自动化类

#ifndef _AFX_NO_OLE_SUPPORT
//  这里暂时将这个处理屏蔽，引入MFC自动化类会导致出现IEntity重复定义的错误，由于在项目实现中，除去对AfxEnableControlContainer()
//  的调用外，并没有其他必需的Com支持，而对自定义的IEntity进行修改的话，不管是重命名还是使用命名空间，改动量和风险都较大，因此
//  采用了将和Com相关的使用全部屏蔽的处理；
//  如果后续开发中有迫切的Com支持需求，可以再考虑使用其他规避方法；
//  added by wuhao，2009－11－09；
//#include <afxdtctl.h>		// MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC 对 Windows 公共控件的支持
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
// #pragma message("开启内存泄露检测")
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
