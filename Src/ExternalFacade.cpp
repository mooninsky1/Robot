/*******************************************************************
** �ļ���:	e:\Rocket\Server\EntityServer\Src\ExternalFacade.h
** ��  Ȩ:	(C) ()
** ������:	
** ��  ��:	2008/1/23  10:33
** ��  ��:	1.0
** ��  ��:	�ⲿ�ӿ������
** Ӧ  ��:  	

**************************** �޸ļ�¼ ******************************
** �޸���: 
** ��  ��: 
** ��  ��: 
********************************************************************/
#include "stdafx.h"
#include "ExternalFacade.h"
#include "IEventEngine.h"
#include "DebugNew.h"

CExternalFacade	g_ExternalFacade;
/** 
@param   
@param   
@return  
*/
CExternalFacade::CExternalFacade(void)
{
}

/** 
@param   
@param   
@return  
*/
CExternalFacade::~CExternalFacade(void)
{

}

/** ���ö�ʱ��
@param   
@param   
@return  
*/ 
bool CExternalFacade::SetTimer(DWORD timerID, DWORD interval, ITimerHandler * handler, LPCSTR debugInfo, DWORD callTimes)
{
	TimerAxis * pTimerAxis = g_pServiceProvider->GetTimeAxis();
	if(pTimerAxis == NULL)
	{
		return false;
	}

	return pTimerAxis->SetTimer(timerID, interval, handler, callTimes, debugInfo);
}

/** ���ٶ�ʱ��
@param   
@param   
@return  
*/
bool CExternalFacade::KillTimer(DWORD timerID, ITimerHandler * handler)
{
	if (g_pServiceProvider == NULL)
		return false;

	TimerAxis * pTimerAxis = g_pServiceProvider->GetTimeAxis();
	if(pTimerAxis == NULL)
	{
		return false;
	}

	return pTimerAxis->KillTimer(timerID, handler);
}



/** ȡ��ʵ��



/** ȡ�ù���Ŀ¼
@param   
@param   
@return  
*/
LPCSTR CExternalFacade::GetWorkDir(void)
{
	return g_pServiceProvider->GetWorkDir();
}

/** ����һ�������
@param   
@param   
@return  
*/
DWORD CExternalFacade::MakeRandNum(void)
{
	static bool bInitFlag = false;
	if(!bInitFlag)
	{
		// ����
		m_RandGenerator.Seed();

		bInitFlag = true;
	}

	return m_RandGenerator.GetDWORD();
}

/** �¼�����
@param   
@param   
@return  
*/
IEventEngine * CExternalFacade::GetEventEngine(void)
{
	return g_pServiceProvider->GetEventEngine();
}


/** �����¼�������ͶƱ�¼���ִ���¼�һ��
@param   
@param   
@return  
*/
void CExternalFacade::FireEvent(WORD wEventID, BYTE bSrcType, DWORD dwSrcID, LPCSTR pszContext, int nLen)
{
	IEventEngine * pEventEngine = GetEventEngine();
	if(pEventEngine == NULL)
	{
		return;
	}

	// ����ͶƱ�¼���
	if(!pEventEngine->FireVote(wEventID, bSrcType, dwSrcID, pszContext, nLen))
	{
		return;
	}

	// ����ִ���¼�
	pEventEngine->FireExecute(wEventID, bSrcType, dwSrcID, pszContext, nLen);
}

/** ����ͶƱ�¼�
@param   
@param   
@return  
*/
bool CExternalFacade::FireVote(WORD wEventID, BYTE bSrcType, DWORD dwSrcID, LPCSTR pszContext, int nLen)
{
	IEventEngine * pEventEngine = GetEventEngine();
	if(pEventEngine == NULL)
	{
		return false;
	}

	// ����ͶƱ�¼���
	return pEventEngine->FireVote(wEventID, bSrcType, dwSrcID, pszContext, nLen);
}

/** ����ִ���¼�
@param   
@param   
@return  
*/
bool  CExternalFacade::FireExecute(WORD wEventID, BYTE bSrcType, DWORD dwSrcID, LPCSTR pszContext, int nLen)
{
	IEventEngine * pEventEngine = GetEventEngine();
	if(pEventEngine == NULL)
	{
		return false;
	}

	// ����ִ���¼�
	return pEventEngine->FireExecute(wEventID, bSrcType, dwSrcID, pszContext, nLen);
}

