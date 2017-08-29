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
		ECONNECT_LOGINING,//�������ӵ�¼��
		ECONNECT_LOGIN,//���ӵ�¼���ɹ���
		ELOGIN_LOGINSERVER,//��¼��¼��
		ECONNECT_ZONEING,//�������ӳ�����
		ECONNECT_ZONE,	//���ӳ������ɹ���
		ELOGIN_ZONESERVER,//��¼������

	};
public:
	CClient(const std::string& strIp,int nPort, const std::string& strName, const std::string strPasswd,int nzoeid);
	
	~CClient();
public:
	/**
		@brief              : �յ���������
		@param pIncomingConn: �ͻ��������������
		@param ppHandler    : ��������ӵ�Handler
		@warning            : �յ����Ӻ�һ��Ҫ����Handler
		*/
		virtual void OnAccept( IConnection * pIncomingConn,IConnectionEventHandler ** ppHandler ) ;

		/**
		@brief      : ���ӳɹ�
		@param conn : ���Ӷ���ָ��
		*/
		virtual void OnConnected( IConnection * conn ) ;

		/**
		@brief      : ���ӶϿ�
		@param conn : ���Ӷ���ָ��
		@param reason:�Ͽ�ԭ��(����) 
		*/
		virtual void OnDisconnected( IConnection * conn,DWORD reason ) ;

		/**
		@brief        : �յ�����
		@param conn   : ���Ӷ���ָ��
		@param pData  : ���ݵ�ַ
		@pram dwDataLen:���ݳ���
		@return       :
		*/
		virtual void OnRecv( IConnection * conn,LPVOID pData,DWORD dwDataLen ) ;

		virtual void OnRecvHead(IConnection * conn,LPVOID pData,DWORD dwDataLen);
		/**
		@name             : ��������¼�
		@brief            :
		@param conn       : ���ִ�����׽���
		@param dwErrorCode: ������
		*/
		virtual void OnError( IConnection * conn,DWORD dwErrorCode ) ;

		virtual void OnTimer( unsigned long dwTimerID );
public:
	//lihf 2017/03/03 ���ӵ�¼��
	bool ConnectLoginServer();
	//lihf 2017/03/03 ���ӳ�����
	bool ConnectZoneServer(const char * szCSIP,WORD nCSPort);
	//lihf 2017/03/03 ��¼����¼
	bool LoginLoginServer();
	//lihf 2017/03/03 ��������¼
	bool LoginZoneServer();
	
	//lihf 2017/03/10 ��ȫ��¼�ɹ�
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
	//lihf 2017/03/03 ���ӵ�¼���ͻ���
	IConnection*	m_pConnectionLogin;
	//lihf 2017/03/07 ���ӳ������ͻ���
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