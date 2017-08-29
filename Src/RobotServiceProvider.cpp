/*******************************************************************
** �ļ���:	e:\Rocket\Server\ZoneServer\Src\RobotServiceProvider.h
** ��  Ȩ:	(C) ()
** ������:	
** ��  ��:	2008/1/10  11:30
** ��  ��:	1.0
** ��  ��:	�������ķ����ṩ��
** Ӧ  ��:  	

**************************** �޸ļ�¼ ******************************
** �޸���: 
** ��  ��: 
** ��  ��: 
********************************************************************/
#include "stdafx.h"
#include "RobotServiceProvider.h"
#include "ZoneServerControl.h"
#include "ExternalFacade.h"
#include "ZoneServer.h"
#include "DbgHelp.h"
#include "IDictionary.h"
#include "ISnkDatabaseDef.h"
#include "Svr2SvrMsg.h"
#include "DGlobalEvent_System.h"
#include "IProtoBuf.h"
#include "IStackWalk.h"
#include "AutoRelease.h"
#include "deelx.h"
#include "DebugNew.h"
#include "DGlobalEvent_Person.h"
#include "DGlobalEvent_Battle.h"
#include "TraceMemory.h"
#include <sstream>
#include <stdio.h>
#include <json/json.h>
#include <sys/stat.h>
#include "mmsystem.h"


#define CREATE_SERVICER(desc, p, f)	\
	p = f; \
	if(p == NULL)\
	{\
		ErrorLn("����[" << desc << "]ʧ��");\
		return false;\
	}\
	TraceLn("����[" << desc << "]�ɹ�");


CRobotServiceProvider * g_pServiceProvider = NULL;
CSchemeRobotConfig *	g_pSchemeRobotConfig = NULL;



void ParseStrItem(std::vector<std::pair<int, int> >& coll, const char* src)
{
	CRegexpA reg("(\\d+)\\s*_\\s*(\\d+)");
	int start = -1;

	for (;;)
	{
		MatchResult mr = reg.Match(src, start);

		if (mr.IsMatched())
		{
			start = mr.GetEnd();
			int groupCount = mr.MaxGroupNumber();
			int prop = 0;
			int count = 0;

			for (int i = 1; i <= 2; ++i)
			{
				int begin = mr.GetGroupStart(i);
				int end = mr.GetGroupEnd(i);

				if (i == 1)
				{
					std::string s(src + begin, end - begin);

					prop = atoi(s.c_str());
				}
				else if (i == 2)
				{
					std::string s(src + begin, end - begin);
					count = atoi(s.c_str());
				}
			}

			if (prop > 0 && count > 0)
			{
				coll.push_back(std::make_pair(prop, count));
			}
		}
		else
		{
			break;
		}
	}
}


/** 
@param   
@param   
@return  
*/
CRobotServiceProvider::CRobotServiceProvider(void):m_checkBillboardCount(0)
, m_logicErrorLocate(false)
{
	setGlobal(this);

	m_TimeAxis = new TimerAxis();

	// ����Ŀ¼
	memset(m_szWorkDir, 0, sizeof(m_szWorkDir));

	// ��������
	m_pSchemeEngine = NULL;

	// �¼�����
	m_pEventEngine = NULL;
	//
	m_pClientManager = NULL;

	// �����ھ��
	m_hMainWnd = NULL;

	m_hWaitDB = NULL;


	m_netMsgParse = NULL;
}
/** 
@param   
@param   
@return  
*/
CRobotServiceProvider::~CRobotServiceProvider(void)
{
	setGlobal(NULL);
}

/** ��ʼ����������
@param   
@param   
@return  
*/
bool CRobotServiceProvider::InitEnvironment(void)
{
	// ȡ�ñ���·��
	int nDirLen = sizeof(m_szWorkDir);
	safeStrncpy(m_szWorkDir, getWorkDir());
	getFileSystem()->addFindPath(m_szWorkDir);

	// �Ƿ���logĿ¼
	char szLogAbsolutePath[512] = { 0 };
	_snprintf_s(szLogAbsolutePath, _TRUNCATE, "%s/Log/Robot", m_szWorkDir);
	bool isAbsolutePath = true; uint attrib = 0;
	if(!rkt::checkPath(szLogAbsolutePath, isAbsolutePath, attrib))
	{
		// ����logĿ¼
		rkt::createDirectoryRecursive(szLogAbsolutePath);
	}

	// trace�ļ���ַ	
	time_t	long_time;
	struct tm local_time;
	time(&long_time); 
	localtime_s(&local_time, &long_time);

	char szTraceFileName[512] = { 0 };
	_snprintf_s(szTraceFileName, _TRUNCATE, "%s/Log/Robot/%02d-%02d %02d.%02d.%02d_Trace", m_szWorkDir,
																		 local_time.tm_mon + 1,
																		 local_time.tm_mday,
																		 local_time.tm_hour,
																		 local_time.tm_min,
																		 local_time.tm_sec);

	char szCrashFileName[512] = { 0 };
	_snprintf_s(szCrashFileName, _TRUNCATE, "%s/Log/Robot/%02d-%02d %02d.%02d.%02d_Crash.txt", m_szWorkDir,
																		 local_time.tm_mon + 1,
																		 local_time.tm_mday,
																		 local_time.tm_hour,
																		 local_time.tm_min,
																		 local_time.tm_sec);
	char szDumpFileName[512] = { 0 };
	_snprintf_s(szDumpFileName, _TRUNCATE, "%s/Log/Robot/%02d-%02d %02d.%02d.%02d_Stack.dmp",  m_szWorkDir,
																		local_time.tm_mon + 1,
																		local_time.tm_mday,
																		local_time.tm_hour,
																		local_time.tm_min,
																		local_time.tm_sec);

	TraceListener * pTraceListener = output2File(szTraceFileName, levelAll, true);


	// dump
	IStackWalk * pStackWalk = createStackWalkProc();
	if(pStackWalk == NULL)
	{
		return false;
	}

	// dump����
	pStackWalk->setDumpType(MiniDumpWithFullMemory);

	// dump�ļ�
	pStackWalk->setLogFileName(szCrashFileName);
	pStackWalk->setDumpFileName(szDumpFileName);
	
	SYSTEM_INFO si;
	GetSystemInfo(&si);

	// ��ʼ��ͨѶ��
	if (InitializeNetwork((si.dwNumberOfProcessors + 1) * 2) != 1)
	{
		return false;
	}		

	// ���������task
	GetLogicThread()->AttachTask(static_cast<ILogicThreadTask *>(&m_NetworkTask), "��������");

	// ʱ�����task
	GetLogicThread()->AttachTask(static_cast<ILogicThreadTask *>(&m_TimerAxisTask), "ʱ����");

	// �����߼��߳�
	GetGlobalThreadPool()->add(static_cast<IRunnable *>(&m_LogicThread), "�߼��߳�");

	CREATE_SERVICER("��������", m_pSchemeEngine, CreateSchemeEngineProc());

	g_pSchemeRobotConfig = new CSchemeRobotConfig();
	g_pSchemeRobotConfig->LoadScheme();
	
	CREATE_SERVICER("�¼�����", m_pEventEngine, CreateEventEngineProc());

	m_pClientManager = new CClientManager;

	GetLogicThread()->AttachTask(static_cast<ILogicThreadTask *>(&g_ZoneServerControl), "������������");

	return true;
}


/** ��������
@param   
@param   
@return  
*/

bool CRobotServiceProvider::StartService(void)
{
	return true;
}


bool CRobotServiceProvider::openClientGate()
{
	TraceLn("����ɡ�������������");

	return true;
}


/** �رշ���
@param   
@param   
@return  
*/
bool CRobotServiceProvider::CloseService(void)
{
	return true;
}




/** ȡ�ó������Ĺ���Ŀ¼
@param   
@param   
@return  
*/
LPCSTR CRobotServiceProvider::GetWorkDir(void)
{
	return m_szWorkDir;
}

/** ȡ��ʱ����
@param   
@param   
@return  
*/
TimerAxis *	CRobotServiceProvider::GetTimeAxis(void)
{
	return m_TimeAxis;
}



/** ȡ���¼�����
@param   
@param   
@return  
*/
IEventEngine * CRobotServiceProvider::GetEventEngine(void)
{
	return m_pEventEngine;
}



/** ȡ��ȫ���̳߳�
@param   
@param   
@return  
*/
ThreadPool * CRobotServiceProvider::GetGlobalThreadPool(void)
{
	return &m_GlobalThreadPool;
}

/** ȡ���߼��߳�
@param   
@param   
@return  
*/
ILogicThread * CRobotServiceProvider::GetLogicThread(void)
{
	return &m_LogicThread;
}


void CRobotServiceProvider::OnExecute(WORD wEventID, BYTE bSrcType, DWORD dwSrcID, LPCSTR pszContext, int nLen)
{
	switch(wEventID)
	{
	case EVENT_SYSTEM_CLOSEZONESERVER:
		{
			// �ӳٹرգ���Ϊ�ر�ʱ��ر��¼�����
			m_TimeAxis->SetTimer(ETimerEventID_CloseService, 1000, static_cast<ITimerHandler *>(this), 1, "CRobotServiceProvider EVENT_SYSTEM_CLOSEZONESERVER");
		}
		break;
	case EVENT_PERSON_LEVEL_UP:
		{
			if (sizeof(SContext_EVENT_PERSON_LEVEL_UP) != nLen)
				break;

			SContext_EVENT_PERSON_LEVEL_UP* realContext = (SContext_EVENT_PERSON_LEVEL_UP*)pszContext;

		}
		break;
	default:
		break;
	}
}

void CRobotServiceProvider::OnTimer( unsigned long dwTimerID )
{
	switch(dwTimerID)
	{
	case ETimerEventID_CloseService:
		{
			HWND hWnd = g_pServiceProvider->GetMainWnd();
			if (hWnd != NULL)
			{
				::PostMessage(g_pServiceProvider->GetMainWnd(), WM_CLOSE_PROGRAM, 0, 0);
			}
			else
			{
				OutputDebugStr("g_pServiceProvider->GetMainWnd return NULL\n");
			}
			
		}
		break;
	default:
		break;
	}
}
/** �����¼�
@param   
@param   
@return  
*/
void  CRobotServiceProvider::Subscriber()
{
	IEventEngine* pEventEngine = g_ExternalFacade.GetEventEngine();
	if (NULL != pEventEngine)
	{
		pEventEngine->Subscibe(this, EVENT_SYSTEM_CLOSEZONESERVER, SOURCE_TYPE_SYSTEM, 0, "CRobotServiceProvider::Subscriber");
		pEventEngine->Subscibe(this, EVENT_PERSON_LEVEL_UP, SOURCE_TYPE_PERSON, 0, "CRobotServiceProvider::Subscriber");
	}
}

/** ȡ�������¼�
@param   
@param   
@return  
*/
void CRobotServiceProvider::UnSubscriber()
{
	IEventEngine* pEventEngine = g_ExternalFacade.GetEventEngine();
	if (NULL != pEventEngine)
	{
		pEventEngine->UnSubscibe(this, EVENT_SYSTEM_CLOSEZONESERVER, SOURCE_TYPE_SYSTEM, 0);
		pEventEngine->UnSubscibe(this, EVENT_PERSON_LEVEL_UP, SOURCE_TYPE_PERSON, 0);
	}
}

/** ���������ھ��
@param   
@param   
@return  
*/
void CRobotServiceProvider::SetMainWnd(HWND hWnd)
{
	m_hMainWnd = hWnd;
}

/** ��ȡ�����ھ��
@param   
@param   
@return  
*/
HWND CRobotServiceProvider::GetMainWnd(void)
{
	return m_hMainWnd;
}

INetMsgParse* CRobotServiceProvider::GetNetMsgParse()
{
	return m_netMsgParse;
}





void CRobotServiceProvider::SetLogicErrorLocate(bool enable)
{
	m_logicErrorLocate = enable;
}

bool CRobotServiceProvider::LogicErrorLocate()
{
	return m_logicErrorLocate;
}






void CRobotServiceProvider::Login()
{
	m_pClientManager->Login();
}
