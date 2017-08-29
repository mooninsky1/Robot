/*******************************************************************
** �ļ���:	e:\Rocket\Server\ZoneServer\Src\LogicThread.h
** ��  Ȩ:	(C) 
** ������:	pdata
** ��  ��:	2008/1/31  11:16
** ��  ��:	1.0
** ��  ��:	�߼��̣߳���Ϸ�߼����߳�
** Ӧ  ��:  	

**************************** �޸ļ�¼ ******************************
** �޸���: 
** ��  ��: 
** ��  ��: 
********************************************************************/
#include "StdAfx.h"
#include "LogicThread.h"
#include "net.h"
#include "RobotServiceProvider.h"
#include "Config.h"
#include "DebugNew.h"

/** �߼��߳��źŵ�ʱ������˽ӿ�
@param   
@param   
@return  
*/
void CTimerAxisTask::OnDo(void)
{
	TRY_BEGIN
	{
		if(g_pServiceProvider != NULL)
		{
			g_pServiceProvider->GetTimeAxis()->CheckTimer();
			g_pServiceProvider->GetTimeAxis()->CheckFixTimer();
		}
	}
	CATCH_ALL
	{
	}
	CATCH_END
};

/** �߼��߳��źŵ�ʱ������˽ӿ�
@param   
@param   
@return  
*/
void CNetworkTask::OnDo(void)
{
	DispatchNetworkEvents();
}

/** 
@param   
@param   
@return  
*/
CLogicThread::CLogicThread(void)
{
	// ��ǰ�����õ�����
	memset(m_UsingTask, 0, sizeof(m_UsingTask));
	m_dwUsingQty = 0;

	// ����
	memset(m_BackTask, 0, sizeof(m_BackTask));
	m_dwBackQty = 0;

	// �Ƿ�ı�
	m_bIsChange = false;

	// �Ƿ�ֹͣ�߳�
	m_bStopThread = false;
}

/** 
@param   
@param   
@return  
*/
CLogicThread::~CLogicThread(void)
{

}

/** 
@param   
@param   
@return  
*/
void CLogicThread::run()
{
	while(true)
	{
		// ����һ��32���볬ʱ
		DWORD dwEventIndex = WaitForSingleObject(GetNetworkEventHandle(), 16);

		if(m_bStopThread)
		{
			break;
		}
		
		if(m_bIsChange)
		{
			memcpy(m_UsingTask, m_BackTask, sizeof(m_UsingTask));
			m_dwUsingQty = m_dwBackQty;
			m_bIsChange = false;
		}

		for(DWORD n = 0; n < m_dwUsingQty; n++)
		{
			if(m_UsingTask[n].pTask != NULL)
			{
				TRY_BEGIN
				{
					m_UsingTask[n].pTask->OnDo();
				}
				CATCH_ALL
				{
					ErrorLn("�߼��̷߳Ƿ����߼��̷߳Ƿ������� = "<<m_UsingTask[n].szDebug);					
				}	
				CATCH_END
			}
		}
	}

	ExitThread(0);
}

/** 
@param   
@param   
@return  
*/
void CLogicThread::release()
{
	// ��ǰ�����õ�����
	memset(m_UsingTask, 0, sizeof(m_UsingTask));
	m_dwUsingQty = 0;

	// ����
	memset(m_BackTask, 0, sizeof(m_BackTask));
	m_dwBackQty = 0;

	// �Ƿ�ı�
	m_bIsChange = false;

	// �Ƿ�ֹͣ�߳�
	m_bStopThread = false;
}

/** ���߼��߳��Ϲ�һ������
@param   
@param   
@return  
*/
bool CLogicThread::AttachTask(ILogicThreadTask * pTask, LPCSTR pszDebug)
{
	if(m_dwBackQty >= ATTACH_TASK_MAXQYT || pszDebug == NULL)
	{
		return false;
	}

	m_BackTask[m_dwBackQty].pTask = pTask;
	safeStrncpy(m_BackTask[m_dwBackQty].szDebug, pszDebug);

	m_dwBackQty++;

	m_bIsChange = true;

	return true;
}

/** ���߼��߳���ȡ��һ������
@param   
@param   
@return  
*/
void CLogicThread::DetachTask(ILogicThreadTask * pTask)
{
	for(int i = 0; i < ATTACH_TASK_MAXQYT; i++)
	{
		if(m_BackTask[i].pTask == pTask)
		{
			for(DWORD n = i + 1; n < m_dwBackQty; n++)
			{
				memcpy(&m_BackTask[n - 1], &m_BackTask[n], sizeof(STaskInfo));				
			}
			memset(&m_BackTask[m_dwBackQty - 1], 0, sizeof(STaskInfo));			
			m_dwBackQty--;

			m_bIsChange = true;
		}
	}
}

/** ֹͣ�߳�
@param   
@param   
@return  
*/
void CLogicThread::StopThread(void)
{
	m_bStopThread = true;
}

void CLogicThread::BreakThread()
{
	StopThread();
}
