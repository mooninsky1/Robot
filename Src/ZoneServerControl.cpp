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
	// ��ǰUI����״̬
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
	// ��ǰUI����״̬
	m_dwUIControlState = EZoneServer_UIControl_Idlesse;
}

/** �߼��߳��źŵ�ʱ������˽ӿ�
@param   
@param   
@return  
*/
typedef void * (CZoneServerControl::* UICONTROL)(void);
void CZoneServerControl::OnDo(void)
{
	static UICONTROL uicontrol[EZoneServer_UIControl_Max] =
	{		
		(UICONTROL)0,											// ����״̬
		(UICONTROL)&CZoneServerControl::OnStartService,			// ��������
		(UICONTROL)&CZoneServerControl::OnStopService,			// ֹͣ����
	};

	if(m_dwUIControlState <= EZoneServer_UIControl_Idlesse || m_dwUIControlState >= EZoneServer_UIControl_Max)
	{
		return;
	}

	(this->*uicontrol[m_dwUIControlState])();
	m_dwUIControlState = EZoneServer_UIControl_Idlesse;
}

/** ���õ�ǰ����̬
@param   
@param   
@return  
*/
void CZoneServerControl::SetUIControl(DWORD dwState)
{
	// ��ǰUI����״̬
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
