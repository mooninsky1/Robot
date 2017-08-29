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
#pragma once

#include "TimerAxis.h"
#include "RandGenerator.h"
#include "RobotServiceProvider.h"

// 定义
class CExternalFacade
{
public:
	/** 启用定时器
	@param   
	@param   
	@return  
	*/ 
	virtual bool					SetTimer(DWORD timerID, DWORD interval, ITimerHandler * handler, LPCSTR debugInfo, DWORD callTimes = INFINITY_CALL);

	/** 销毁定时器
	@param   
	@param   
	@return  
	*/
	virtual bool					KillTimer(DWORD timerID, ITimerHandler * handler);


	/** 取得工作目录
	@param   
	@param   
	@return  
	*/
	virtual LPCSTR					GetWorkDir(void);

	/** 生成一个随机数
	@param   
	@param   
	@return  
	*/
	virtual DWORD					MakeRandNum(void);

	/** 事件引擎
	@param   
	@param   
	@return  
	*/
	virtual IEventEngine *			GetEventEngine(void);

	/** 发送事件，包括投票事件和执行事件一起发
	@param   
	@param   
	@return  
	*/
	virtual void					FireEvent(WORD wEventID, BYTE bSrcType, DWORD dwSrcID, LPCSTR pszContext, int nLen);

	/** 发送投票事件
	@param   
	@param   
	@return  
	*/
	virtual bool					FireVote(WORD wEventID, BYTE bSrcType, DWORD dwSrcID, LPCSTR pszContext, int nLen);

	/** 发送执行事件
	@param   
	@param   
	@return  
	*/
	virtual bool					FireExecute(WORD wEventID, BYTE bSrcType, DWORD dwSrcID, LPCSTR pszContext, int nLen);

	/** 
	@param   
	@param   
	@return  
	*/
	CExternalFacade(void);

	/** 
	@param   
	@param   
	@return  
	*/
	virtual ~CExternalFacade(void);

private:
	// 随机数生成器
	CRandGenerator				m_RandGenerator;

};
extern CExternalFacade			g_ExternalFacade;