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
#pragma once

#include "TimerAxis.h"
#include "RandGenerator.h"
#include "RobotServiceProvider.h"

// ����
class CExternalFacade
{
public:
	/** ���ö�ʱ��
	@param   
	@param   
	@return  
	*/ 
	virtual bool					SetTimer(DWORD timerID, DWORD interval, ITimerHandler * handler, LPCSTR debugInfo, DWORD callTimes = INFINITY_CALL);

	/** ���ٶ�ʱ��
	@param   
	@param   
	@return  
	*/
	virtual bool					KillTimer(DWORD timerID, ITimerHandler * handler);


	/** ȡ�ù���Ŀ¼
	@param   
	@param   
	@return  
	*/
	virtual LPCSTR					GetWorkDir(void);

	/** ����һ�������
	@param   
	@param   
	@return  
	*/
	virtual DWORD					MakeRandNum(void);

	/** �¼�����
	@param   
	@param   
	@return  
	*/
	virtual IEventEngine *			GetEventEngine(void);

	/** �����¼�������ͶƱ�¼���ִ���¼�һ��
	@param   
	@param   
	@return  
	*/
	virtual void					FireEvent(WORD wEventID, BYTE bSrcType, DWORD dwSrcID, LPCSTR pszContext, int nLen);

	/** ����ͶƱ�¼�
	@param   
	@param   
	@return  
	*/
	virtual bool					FireVote(WORD wEventID, BYTE bSrcType, DWORD dwSrcID, LPCSTR pszContext, int nLen);

	/** ����ִ���¼�
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
	// �����������
	CRandGenerator				m_RandGenerator;

};
extern CExternalFacade			g_ExternalFacade;