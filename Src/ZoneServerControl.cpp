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
#include "StdAfx.h"
#include "ZoneServerControl.h"
#include "RobotServiceProvider.h"
#include "ExternalFacade.h"
#include "DGlobalEvent_System.h"
#include "DebugNew.h"

CZoneServerControl   g_ZoneServerControl;
/** 
@param   
@param   
@return  
*/
CZoneServerControl::CZoneServerControl(void)
{
	// 当前UI操作状态
	m_dwUIControlState = EZoneServer_UIControl_Idlesse;
}

/** 
@param   
@param   
@return  
*/

CZoneServerControl::~CZoneServerControl(void)
{
	g_ExternalFacade.KillTimer(TIMER_WAIT_DB_IDLE_TO_CLOSE_SERVER, this);
	g_ExternalFacade.KillTimer(TIMER_WAIT_DB_IDLE_TO_OPEN_CLIENT_GATE, this);
	// 当前UI操作状态
	m_dwUIControlState = EZoneServer_UIControl_Idlesse;
}

/** 逻辑线程信号到时，会调此接口
@param   
@param   
@return  
*/
typedef void * (CZoneServerControl::* UICONTROL)(void);
void CZoneServerControl::OnDo(void)
{
	static UICONTROL uicontrol[EZoneServer_UIControl_Max] =
	{		
		(UICONTROL)0,											// 空闲状态
		(UICONTROL)&CZoneServerControl::OnStartService,			// 启动服务
		(UICONTROL)&CZoneServerControl::OnStopService,			// 停止服务
	};

	if(m_dwUIControlState <= EZoneServer_UIControl_Idlesse || m_dwUIControlState >= EZoneServer_UIControl_Max)
	{
		return;
	}

	(this->*uicontrol[m_dwUIControlState])();
	m_dwUIControlState = EZoneServer_UIControl_Idlesse;
}

/** 设置当前控制态
@param   
@param   
@return  
*/
void CZoneServerControl::SetUIControl(DWORD dwState)
{
	// 当前UI操作状态
	m_dwUIControlState = dwState;
}

/** 
@param   
@param   
@return  
*/
void CZoneServerControl::OnStartService(void)
{
	if(g_pServiceProvider != NULL)
	{
		if (g_pServiceProvider->StartService())
		{
			g_ExternalFacade.FireEvent(EVENT_SYSTEM_STARTZONESERVER, SOURCE_TYPE_SYSTEM, 0, 0, 0);
		}		
	}
}

/** 
@param   
@param   
@return  
*/
void CZoneServerControl::OnStopService(void)
{
	HWND hWnd = g_pServiceProvider->GetMainWnd();
	if (hWnd != NULL)
	{
		::PostMessage(g_pServiceProvider->GetMainWnd(), WM_CLOSE_PROGRAM, 0, 0);
	}
}


void CZoneServerControl::ActiveOpenClientGateTimer()
{
	g_ExternalFacade.SetTimer(TIMER_WAIT_DB_IDLE_TO_OPEN_CLIENT_GATE, 1000, this, "");
}



void CZoneServerControl::OnTimer(unsigned long dwTimerID)
{
	
}
