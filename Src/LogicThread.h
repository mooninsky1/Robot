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
#pragma once

#include <list>
using namespace std;
#include "Thread.h"
using namespace rkt;

// 挂接任务最多个数
#define ATTACH_TASK_MAXQYT				12

/// 逻辑线程任务接口
struct ILogicThreadTask
{
	virtual ~ILogicThreadTask() {}
	/** 逻辑线程信号到时，会调此接口
	@param   
	@param   
	@return  
	*/
	virtual void						OnDo(void) = NULL;
};

/// 逻辑线程任务管理器
struct ILogicThread
{
	virtual ~ILogicThread() {}

	/** 在逻辑线程上挂一个任务
	@param   
	@param   
	@return  
	*/
	virtual bool						AttachTask(ILogicThreadTask * pTask, LPCSTR pszDebug) = NULL;

	/** 在逻辑线程上取消一个任务
	@param   
	@param   
	@return  
	*/
	virtual void						DetachTask(ILogicThreadTask * pTask) = NULL;
};

// 时间轴的task
class CTimerAxisTask : public ILogicThreadTask
{
public:
	/** 逻辑线程信号到时，会调此接口
	@param   
	@param   
	@return  
	*/
	virtual void				OnDo(void);
};

// 网络引擎的task
class CNetworkTask : public ILogicThreadTask
{
public:
	/** 逻辑线程信号到时，会调此接口
	@param   
	@param   
	@return  
	*/
	virtual void				OnDo(void);
};

// 逻辑线程
class CLogicThread : public ILogicThread, public IRunnable
{	
	struct STaskInfo
	{
		ILogicThreadTask *		pTask;

		// 调试信息
		char					szDebug[32];

		STaskInfo(void)
		{
			pTask = NULL;
			memset(szDebug, 0, sizeof(szDebug));
		}
	};

public:
	////////////////////////IRunnable//////////////////////////////////
	/** 
	@param   
	@param   
	@return  
	*/
	virtual void				run();

	/** 
	@param   
	@param   
	@return  
	*/
	virtual void				release();

	////////////////////////ILogicThread///////////////////////////////
	/** 在逻辑线程上挂一个任务
	@param   
	@param   
	@return  
	*/
	virtual bool				AttachTask(ILogicThreadTask * pTask, LPCSTR pszDebug);

	/** 在逻辑线程上取消一个任务
	@param   
	@param   
	@return  
	*/
	virtual void				DetachTask(ILogicThreadTask * pTask);

	///////////////////////CLogicThread////////////////////////////////
	/** 停止线程
	@param   
	@param   
	@return  
	*/
	void						StopThread(void);

	/** 
	@param   
	@param   
	@return  
	*/
	CLogicThread(void);

	/** 
	@param   
	@param   
	@return  
	*/
	virtual ~CLogicThread(void);

	virtual void BreakThread();

private:
	// 当前正在用的任务
	STaskInfo					m_UsingTask[ATTACH_TASK_MAXQYT];
	DWORD						m_dwUsingQty;

	// 备份
	STaskInfo					m_BackTask[ATTACH_TASK_MAXQYT];	
	DWORD						m_dwBackQty;

	// 是否改变
	bool						m_bIsChange;

	// 是否停止线程
	bool						m_bStopThread;
};