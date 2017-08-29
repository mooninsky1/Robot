/*******************************************************************
** 文件名:	e:\Rocket\Server\EntityServer\Src\ExternalFacade.h
** 版  权:	(C) ()
** 创建人:	
** 日  期:	2008/1/23  10:33
** 版  本:	1.0
** 描  述:	外部接口外观类
** 应  用:  	

**************************** 修改记录 ******************************
** 修改人: 
** 日  期: 
** 描  述: 
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

/** 启用定时器
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

/** 销毁定时器
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



/** 取得实体



/** 取得工作目录
@param   
@param   
@return  
*/
LPCSTR CExternalFacade::GetWorkDir(void)
{
	return g_pServiceProvider->GetWorkDir();
}

/** 生成一个随机数
@param   
@param   
@return  
*/
DWORD CExternalFacade::MakeRandNum(void)
{
	static bool bInitFlag = false;
	if(!bInitFlag)
	{
		// 播种
		m_RandGenerator.Seed();

		bInitFlag = true;
	}

	return m_RandGenerator.GetDWORD();
}

/** 事件引擎
@param   
@param   
@return  
*/
IEventEngine * CExternalFacade::GetEventEngine(void)
{
	return g_pServiceProvider->GetEventEngine();
}


/** 发送事件，包括投票事件和执行事件一起发
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

	// 发送投票事件，
	if(!pEventEngine->FireVote(wEventID, bSrcType, dwSrcID, pszContext, nLen))
	{
		return;
	}

	// 发送执行事件
	pEventEngine->FireExecute(wEventID, bSrcType, dwSrcID, pszContext, nLen);
}

/** 发送投票事件
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

	// 发送投票事件，
	return pEventEngine->FireVote(wEventID, bSrcType, dwSrcID, pszContext, nLen);
}

/** 发送执行事件
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

	// 发送执行事件
	return pEventEngine->FireExecute(wEventID, bSrcType, dwSrcID, pszContext, nLen);
}

