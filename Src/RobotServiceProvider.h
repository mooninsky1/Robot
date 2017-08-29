/*******************************************************************
** �ļ���:	e:\Rocket\Server\ZoneServer\Src\RobotServiceProvider.h
** ��  Ȩ:	(C) ()
** ������:	
** ��  ��:	2008/1/10  11:30
** ��  ��:	1.0
** ��  ��:	�������ķ����ṩ��
** Ӧ  ��:  	

**************************** �޸ļ�¼ ******************************
** �޸���: 
** ��  ��: 
** ��  ��: 
********************************************************************/
#pragma once
#define WM_CALCULA_PERSON	(WM_USER+1978)
#define WM_CLOSE_SERVER		(WM_USER+1979)
#define WM_CLOSE_PROGRAM	(WM_USER+1980)
#define WM_CALCULA_PERSON_REAL	(WM_USER+1981)
#define WM_MYPRINT	(WM_USER+1982)
#define WM_UPDATE_UI	(WM_USER+1983)
#include "IEventEngine.h"
#include "ISchemeEngine.h"
#include "LogicThread.h"
#include "net.h"
#include "ClientManger.h"
#include "IProtoBuf.h"
#include "SchemeRobotConfig.h"

class CRobotServiceProvider :  public IEventExecuteSink, public TimerHandler
{
	enum
	{
		ETimerEventID_CloseService = 1,
	};
public:
	/////////////////////////IZoneServiceProvider//////////////////////


	/** ȡ�ó������Ĺ���Ŀ¼
	@param   
	@param   
	@return  
	*/
	virtual	LPCSTR						GetWorkDir(void);

	/** ȡ��ʱ����
	@param   
	@param   
	@return  
	*/
	virtual TimerAxis *					GetTimeAxis(void);

	/** ȡ����������
	@param   
	@param   
	@return  
	*/
	ISchemeEngine *	GetSchemeEngine(void)
	{
		return m_pSchemeEngine;
	}


	/** ȡ���¼�����
	@param   
	@param   
	@return  
	*/
	virtual IEventEngine *				GetEventEngine(void);

	/** ȡ��ȫ���̳߳�
	@param   
	@param   
	@return  
	*/
	virtual ThreadPool *				GetGlobalThreadPool(void);

	/** ȡ���߼��߳�
	@param   
	@param   
	@return  
	*/
	virtual ILogicThread *				GetLogicThread(void);




	/*!
	 * name:	openClientGate
	 * brief:	ĳЩģ��������ݿ�,�ȴ����ݿ���ɺ�����ͻ��˵�ͨѶ
	 * @prama:
	 * @prama:
	 */
	bool openClientGate();


	virtual INetMsgParse*					GetNetMsgParse();

	//////////////////// IEventExecuteSink ////////////////////////////////////	
	/** �¼�����
	@param   
	@param   
	@return  
	*/
	virtual void OnExecute(WORD wEventID, BYTE bSrcType, DWORD dwSrcID, LPCSTR pszContext, int nLen);

	//////////////////////////ITimeAxis///////////////////////////////
	/**
	@purpose          : ��ʱ��������ص�,������������д�������
	@param	 dwTimerID: ��ʱ��ID,�����������ĸ���ʱ��
	@return		      : empty
	*/
	virtual void		OnTimer( unsigned long dwTimerID );

	/////////////////////////CRobotServiceProvider//////////////////////
	/** ��ʼ����������
	@param   
	@param   
	@return  
	*/
	bool								InitEnvironment(void);

	/** ��������
	@param   
	@param   
	@return  
	*/
	bool								StartService(void);

	/** �رշ���
	@param   
	@param   
	@return  
	*/
	bool								CloseService(void);
	
	/** �����¼�
	@param   
	@param   
	@return  
	*/
	void                                Subscriber();
	
	/** ȡ�������¼�
	@param   
	@param   
	@return  
	*/
	void                                UnSubscriber();

	/** ���������ھ��
	@param   
	@param   
	@return  
	*/
	virtual void						SetMainWnd(HWND hWnd);

	/** ��ȡ�����ھ��
	@param   
	@param   
	@return  
	*/
	virtual HWND						GetMainWnd(void);

	/** 
	@param   
	@param   
	@return  
	*/
	CRobotServiceProvider(void);

	/** 
	@param   
	@param   
	@return  
	*/
	virtual ~CRobotServiceProvider(void);





	virtual bool						LogicErrorLocate();

	virtual void						SetLogicErrorLocate(bool enable);


public:
	void Login();
private:


	/*!
	 * name:		OnReturn				
	 * brief:		���loginSvrdInfo�ص�
	 * @prama:
	 * @prama:
	 */
	void								OnReturn(int nCmdID, int nDBRetCode, char* pszDBRetDesc, int nQueueIndex, char* pOutData, int nOutLen, char * pInData, int nInLen,LPCSTR pszContext=NULL,int nContextLen=0);

private:
	//std::map<std::string, SCDKeyInfo> m_CDKEYList;
	// ����Ŀ¼
	char								m_szWorkDir[MAX_PATH];

	// s
	TimerAxis* 							m_TimeAxis;

	// ��������
	ISchemeEngine *						m_pSchemeEngine;

	// �¼�����
	IEventEngine *						m_pEventEngine;



	// ȫ���̳߳�
	ThreadPool							m_GlobalThreadPool;

	// �߼��߳�
	CLogicThread						m_LogicThread;

	///////////////////////////////////////////////////////////////////
	// ʱ�����task
	CTimerAxisTask						m_TimerAxisTask;

	// ���������task
	CNetworkTask						m_NetworkTask;

	//�����ھ��
	HWND								m_hMainWnd;

	/*!
	 *��һ�Σ������þ�ɾ��
	 */
	HANDLE								m_hWaitDB;

	int									m_checkBillboardCount;

	// proto buf ������
	INetMsgParse*						m_netMsgParse;

	bool								m_logicErrorLocate;

	CClientManager*						m_pClientManager;
private:

};

extern CRobotServiceProvider *			g_pServiceProvider;
extern CSchemeRobotConfig *				g_pSchemeRobotConfig;