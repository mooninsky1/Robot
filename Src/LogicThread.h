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
#pragma once

#include <list>
using namespace std;
#include "Thread.h"
using namespace rkt;

// �ҽ�����������
#define ATTACH_TASK_MAXQYT				12

/// �߼��߳�����ӿ�
struct ILogicThreadTask
{
	virtual ~ILogicThreadTask() {}
	/** �߼��߳��źŵ�ʱ������˽ӿ�
	@param   
	@param   
	@return  
	*/
	virtual void						OnDo(void) = NULL;
};

/// �߼��߳����������
struct ILogicThread
{
	virtual ~ILogicThread() {}

	/** ���߼��߳��Ϲ�һ������
	@param   
	@param   
	@return  
	*/
	virtual bool						AttachTask(ILogicThreadTask * pTask, LPCSTR pszDebug) = NULL;

	/** ���߼��߳���ȡ��һ������
	@param   
	@param   
	@return  
	*/
	virtual void						DetachTask(ILogicThreadTask * pTask) = NULL;
};

// ʱ�����task
class CTimerAxisTask : public ILogicThreadTask
{
public:
	/** �߼��߳��źŵ�ʱ������˽ӿ�
	@param   
	@param   
	@return  
	*/
	virtual void				OnDo(void);
};

// ���������task
class CNetworkTask : public ILogicThreadTask
{
public:
	/** �߼��߳��źŵ�ʱ������˽ӿ�
	@param   
	@param   
	@return  
	*/
	virtual void				OnDo(void);
};

// �߼��߳�
class CLogicThread : public ILogicThread, public IRunnable
{	
	struct STaskInfo
	{
		ILogicThreadTask *		pTask;

		// ������Ϣ
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
	/** ���߼��߳��Ϲ�һ������
	@param   
	@param   
	@return  
	*/
	virtual bool				AttachTask(ILogicThreadTask * pTask, LPCSTR pszDebug);

	/** ���߼��߳���ȡ��һ������
	@param   
	@param   
	@return  
	*/
	virtual void				DetachTask(ILogicThreadTask * pTask);

	///////////////////////CLogicThread////////////////////////////////
	/** ֹͣ�߳�
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
	// ��ǰ�����õ�����
	STaskInfo					m_UsingTask[ATTACH_TASK_MAXQYT];
	DWORD						m_dwUsingQty;

	// ����
	STaskInfo					m_BackTask[ATTACH_TASK_MAXQYT];	
	DWORD						m_dwBackQty;

	// �Ƿ�ı�
	bool						m_bIsChange;

	// �Ƿ�ֹͣ�߳�
	bool						m_bStopThread;
};