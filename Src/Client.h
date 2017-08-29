#pragma once 
#include "net.h"
#include "IProtoBuf.h"
#include "Login.pb.h"
#include "Person.pb.h"

using namespace rkt;
using namespace ShiHun;
using namespace Login;
using namespace Person;
//#include "Arc4Rsa.h"
using namespace rkt;

class CClient:public IConnectionEventHandler,public TimerHandler
{
public:
	enum LoginSate
	{
		ELOGIN_NULL,
		ECONNECT_LOGINING,//正在连接登录服
		ECONNECT_LOGIN,//连接登录服成功，
		ELOGIN_LOGINSERVER,//登录登录服
		ECONNECT_ZONEING,//正在连接场景服
		ECONNECT_ZONE,	//连接场景服成功，
		ELOGIN_ZONESERVER,//登录场景服

	};
public:
	CClient(const std::string& strIp,int nPort, const std::string& strName, const std::string strPasswd,int nzoeid);
	
	~CClient();
public:
	/**
		@brief              : 收到被动连接
		@param pIncomingConn: 客户端连入的新连接
		@param ppHandler    : 处理该连接的Handler
		@warning            : 收到连接后一定要设置Handler
		*/
		virtual void OnAccept( IConnection * pIncomingConn,IConnectionEventHandler ** ppHandler ) ;

		/**
		@brief      : 连接成功
		@param conn : 连接对象指针
		*/
		virtual void OnConnected( IConnection * conn ) ;

		/**
		@brief      : 连接断开
		@param conn : 连接对象指针
		@param reason:断开原因(保留) 
		*/
		virtual void OnDisconnected( IConnection * conn,DWORD reason ) ;

		/**
		@brief        : 收到数据
		@param conn   : 连接对象指针
		@param pData  : 数据地址
		@pram dwDataLen:数据长度
		@return       :
		*/
		virtual void OnRecv( IConnection * conn,LPVOID pData,DWORD dwDataLen ) ;

		virtual void OnRecvHead(IConnection * conn,LPVOID pData,DWORD dwDataLen);
		/**
		@name             : 网络错误事件
		@brief            :
		@param conn       : 出现错误的套接字
		@param dwErrorCode: 错误码
		*/
		virtual void OnError( IConnection * conn,DWORD dwErrorCode ) ;

		virtual void OnTimer( unsigned long dwTimerID );
public:
	//lihf 2017/03/03 连接登录服
	bool ConnectLoginServer();
	//lihf 2017/03/03 连接场景服
	bool ConnectZoneServer(const char * szCSIP,WORD nCSPort);
	//lihf 2017/03/03 登录服登录
	bool LoginLoginServer();
	//lihf 2017/03/03 场景服登录
	bool LoginZoneServer();
	
	//lihf 2017/03/10 完全登录成功
	void LoginSuccess();
private:
	void SendLoginKey();
	void sendZoneKey();
private:
	//test
	void TestMove();
	void TestAddItem();
	void GetBagData();
	void GetBagDataRsp(SMsgZS2C_ActorItemsData* extendMsg);
	//batlle
	void TestBattle();
	void Fight();
	//coprs
	void TestCorps();
private:
	//lihf 2017/03/03 连接登录服客户端
	IConnection*	m_pConnectionLogin;
	//lihf 2017/03/07 连接场景服客户端
	IConnection*	m_pConnectionZone;
	LoginSate		m_ClientState;	
	INetMsgParse*	m_netMsgParse;
	UINT64			m_uActorid;
	UINT64			m_uActorIDCoded;
	
	std::string			m_szName;
	std::string			m_szPasswd;
	std::string			m_szLoginIP;
	int					m_nLoginPort;
	int					m_nZoneid;
	int					m_nPosx;
	int                 m_nPosy;
	int					m_nPosz;
	bool				m_bInit;
	int					m_nPosxEnd;
	int                 m_nPosyEnd;
};