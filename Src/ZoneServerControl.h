/*******************************************************************
** 文件名:	e:\Rocket\Server\ZoneServer\Src\ZoneServerControl.h
** 版  权:	(C) 
** 创建人:	pdata
** 日  期:	2008/1/30  23:41
** 版  本:	1.0
** 描  述:	场景服控制器
** 应  用:  	
	
**************************** 修改记录 ******************************
** 修改人: 
** 日  期: 
** 描  述: 
********************************************************************/
#pragma once

#include "TimerHandler.h"
#include "LogicThread.h"

enum
{
	EZoneServer_UIControl_Idlesse = 0,		// 空闲状态
	EZoneServer_UIControl_StartService,		// 启动服务
	EZoneServer_UIControl_StopService,		// 停止服务
	EZoneServer_UIControl_UpdateScheme,		// 更新配置
	//EZoneServer_UIControl_UpdateLua,		// 更新lua
	EZoneServer_UIControl_Max				// 最大态
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
	/** 逻辑线程信号到时，会调此接口
	@param   
	@param   
	@return  
	*/
	virtual void			OnDo(void);

	/////////////////////////////CZoneServerControl////////////////////
	/** 设置当前控制态
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
	 * brief:	某些模块需读数据库,等待数据库完成后开启与客户端的通讯
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
	// 当前UI操作状态
	DWORD					m_dwUIControlState;

	// 设置动态更新配置
	std::string					m_stringWaitDynamic;
};
extern CZoneServerControl   g_ZoneServerControl;