/*******************************************************************
** 文件名:	e:\Rocket\Server\ZoneServer\Src\LogicThread.h
** 版  权:	(C) 
** 创建人:	pdata
** 日  期:	2008/1/31  11:16
** 版  本:	1.0
** 描  述:	逻辑线程，游戏逻辑主线程
** 应  用:  	

**************************** 修改记录 ******************************
** 修改人: 
** 日  期: 
** 描  述: 
********************************************************************/
#include "StdAfx.h"
#include "LogicThread.h"
#include "net.h"
#include "RobotServiceProvider.h"
#include "Config.h"
#include "DebugNew.h"

/** 逻辑线程信号到时，会调此接口
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

/** 逻辑线程信号到时，会调此接口
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
	// 当前正在用的任务
	memset(m_UsingTask, 0, sizeof(m_UsingTask));
	m_dwUsingQty = 0;

	// 备份
	memset(m_BackTask, 0, sizeof(m_BackTask));
	m_dwBackQty = 0;

	// 是否改变
	m_bIsChange = false;

	// 是否停止线程
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
		// 设置一个32毫秒超时
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
					ErrorLn("逻辑线程非法！逻辑线程非法！描述 = "<<m_UsingTask[n].szDebug);					
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
	// 当前正在用的任务
	memset(m_UsingTask, 0, sizeof(m_UsingTask));
	m_dwUsingQty = 0;

	// 备份
	memset(m_BackTask, 0, sizeof(m_BackTask));
	m_dwBackQty = 0;

	// 是否改变
	m_bIsChange = false;

	// 是否停止线程
	m_bStopThread = false;
}

/** 在逻辑线程上挂一个任务
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

/** 在逻辑线程上取消一个任务
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

/** 停止线程
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
