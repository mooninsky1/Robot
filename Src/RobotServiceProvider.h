/*******************************************************************
** 文件名:	e:\Rocket\Server\ZoneServer\Src\RobotServiceProvider.h
** 版  权:	(C) ()
** 创建人:	
** 日  期:	2008/1/10  11:30
** 版  本:	1.0
** 描  述:	场景服的服务提供商
** 应  用:  	

**************************** 修改记录 ******************************
** 修改人: 
** 日  期: 
** 描  述: 
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


	/** 取得场景服的工作目录
	@param   
	@param   
	@return  
	*/
	virtual	LPCSTR						GetWorkDir(void);

	/** 取得时间轴
	@param   
	@param   
	@return  
	*/
	virtual TimerAxis *					GetTimeAxis(void);

	/** 取得配置引擎
	@param   
	@param   
	@return  
	*/
	ISchemeEngine *	GetSchemeEngine(void)
	{
		return m_pSchemeEngine;
	}


	/** 取得事件引擎
	@param   
	@param   
	@return  
	*/
	virtual IEventEngine *				GetEventEngine(void);

	/** 取得全局线程池
	@param   
	@param   
	@return  
	*/
	virtual ThreadPool *				GetGlobalThreadPool(void);

	/** 取得逻辑线程
	@param   
	@param   
	@return  
	*/
	virtual ILogicThread *				GetLogicThread(void);




	/*!
	 * name:	openClientGate
	 * brief:	某些模块需读数据库,等待数据库完成后开启与客户端的通讯
	 * @prama:
	 * @prama:
	 */
	bool openClientGate();


	virtual INetMsgParse*					GetNetMsgParse();

	//////////////////// IEventExecuteSink ////////////////////////////////////	
	/** 事件处理
	@param   
	@param   
	@return  
	*/
	virtual void OnExecute(WORD wEventID, BYTE bSrcType, DWORD dwSrcID, LPCSTR pszContext, int nLen);

	//////////////////////////ITimeAxis///////////////////////////////
	/**
	@purpose          : 定时器触发后回调,你可以在这里编写处理代码
	@param	 dwTimerID: 定时器ID,用于区分是哪个定时器
	@return		      : empty
	*/
	virtual void		OnTimer( unsigned long dwTimerID );

	/////////////////////////CRobotServiceProvider//////////////////////
	/** 初始化启动环境
	@param   
	@param   
	@return  
	*/
	bool								InitEnvironment(void);

	/** 启动服务
	@param   
	@param   
	@return  
	*/
	bool								StartService(void);

	/** 关闭服务
	@param   
	@param   
	@return  
	*/
	bool								CloseService(void);
	
	/** 订阅事件
	@param   
	@param   
	@return  
	*/
	void                                Subscriber();
	
	/** 取消订阅事件
	@param   
	@param   
	@return  
	*/
	void                                UnSubscriber();

	/** 设置主窗口句柄
	@param   
	@param   
	@return  
	*/
	virtual void						SetMainWnd(HWND hWnd);

	/** 获取主窗口句柄
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
	 * brief:		获得loginSvrdInfo回调
	 * @prama:
	 * @prama:
	 */
	void								OnReturn(int nCmdID, int nDBRetCode, char* pszDBRetDesc, int nQueueIndex, char* pOutData, int nOutLen, char * pInData, int nInLen,LPCSTR pszContext=NULL,int nContextLen=0);

private:
	//std::map<std::string, SCDKeyInfo> m_CDKEYList;
	// 工作目录
	char								m_szWorkDir[MAX_PATH];

	// s
	TimerAxis* 							m_TimeAxis;

	// 配置引擎
	ISchemeEngine *						m_pSchemeEngine;

	// 事件引擎
	IEventEngine *						m_pEventEngine;



	// 全局线程池
	ThreadPool							m_GlobalThreadPool;

	// 逻辑线程
	CLogicThread						m_LogicThread;

	///////////////////////////////////////////////////////////////////
	// 时间轴的task
	CTimerAxisTask						m_TimerAxisTask;

	// 网络引擎的task
	CNetworkTask						m_NetworkTask;

	//主窗口句柄
	HWND								m_hMainWnd;

	/*!
	 *用一次，启动好就删除
	 */
	HANDLE								m_hWaitDB;

	int									m_checkBillboardCount;

	// proto buf 解析器
	INetMsgParse*						m_netMsgParse;

	bool								m_logicErrorLocate;

	CClientManager*						m_pClientManager;
private:

};

extern CRobotServiceProvider *			g_pServiceProvider;
extern CSchemeRobotConfig *				g_pSchemeRobotConfig;