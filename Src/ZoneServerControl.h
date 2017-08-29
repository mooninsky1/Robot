/*******************************************************************
** �ļ���:	e:\Rocket\Server\ZoneServer\Src\ZoneServerControl.h
** ��  Ȩ:	(C) 
** ������:	pdata
** ��  ��:	2008/1/30  23:41
** ��  ��:	1.0
** ��  ��:	������������
** Ӧ  ��:  	
	
**************************** �޸ļ�¼ ******************************
** �޸���: 
** ��  ��: 
** ��  ��: 
********************************************************************/
#pragma once

#include "TimerHandler.h"
#include "LogicThread.h"

enum
{
	EZoneServer_UIControl_Idlesse = 0,		// ����״̬
	EZoneServer_UIControl_StartService,		// ��������
	EZoneServer_UIControl_StopService,		// ֹͣ����
	EZoneServer_UIControl_UpdateScheme,		// ��������
	//EZoneServer_UIControl_UpdateLua,		// ����lua
	EZoneServer_UIControl_Max				// ���̬
};


class CZoneServerControl : public ILogicThreadTask
	, public TimerHandler
{
	enum
	{
		TIMER_NONE,
		TIMER_WAIT_DB_IDLE_TO_CLOSE_SERVER,
		TIMER_WAIT_DB_IDLE_TO_OPEN_CLIENT_GATE,
	};

public:
	/////////////////////////////ILogicThreadTask/////////////////////
	/** �߼��߳��źŵ�ʱ������˽ӿ�
	@param   
	@param   
	@return  
	*/
	virtual void			OnDo(void);

	/////////////////////////////CZoneServerControl////////////////////
	/** ���õ�ǰ����̬
	@param   
	@param   
	@return  
	*/
	void					SetUIControl(DWORD dwState);

	/** 
	@param   
	@param   
	@return  
	*/
	CZoneServerControl(void);

	/** 
	@param   
	@param   
	@return  
	*/
	virtual ~CZoneServerControl(void);

	virtual void			OnTimer(unsigned long dwTimerID);


	/*!
	 * name:	ActiveOpenClientGateTimer
	 * brief:	ĳЩģ��������ݿ�,�ȴ����ݿ���ɺ�����ͻ��˵�ͨѶ
	 * @prama:
	 * @prama:
	 */
	void					ActiveOpenClientGateTimer();

private:
	/** 
	@param   
	@param   
	@return  
	*/
	void					OnStartService(void);

	/** 
	@param   
	@param   
	@return  
	*/
	void					OnStopService(void);


	/** 
	@param   
	@param   
	@return  
	*/
	//void					OnUpdateLua(void);

public:
	// ��ǰUI����״̬
	DWORD					m_dwUIControlState;

	// ���ö�̬��������
	std::string					m_stringWaitDynamic;
};
extern CZoneServerControl   g_ZoneServerControl;