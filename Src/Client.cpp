#include "stdafx.h"
#include "Client.h"
#include "Login.pb.h"
#include "IProtoBuf.h"
#include "NetMsgHead.pb.h"
#include "Packer.h"
#include "Login.pb.h"
#include "Person.pb.h"
#include "..\Common\DEntityProp.h"
#include "RobotServiceProvider.h"

using namespace rkt;
using namespace ShiHun;
using namespace Login;
using namespace Person;

void CClient::OnAccept( IConnection * pIncomingConn,IConnectionEventHandler ** ppHandler )
{

}

void CClient::OnConnected( IConnection * conn )
{
	if (ECONNECT_LOGINING == m_ClientState)
	{
		m_ClientState = ECONNECT_LOGIN;
		//lihf 2017/03/03 œ»∑¢ÀÕ√‹‘ø
		SendLoginKey();
//		LoginLoginServer();
	}
	else if (ECONNECT_ZONEING == m_ClientState)
	{
		m_ClientState = ECONNECT_ZONE;
		sendZoneKey();
	}
}

void CClient::OnDisconnected( IConnection * conn,DWORD reason )
{

}

void CClient::OnRecv( IConnection * conn,LPVOID pData,DWORD dwDataLen )
{
	int num = 0; 
	NetMsgHead::NetMsgHead msg;
	if(NULL == m_netMsgParse)
	{
		ErrorLn("m_netMsgParse is null");
		return;
	}

	if (m_netMsgParse->ParseProtoBuf(pData, dwDataLen, num, msg))
	{
		NetMsgHead::NetMsgHead* realMsg = static_cast<NetMsgHead::NetMsgHead*>(&msg);
		switch(num)
		{
		case NET_CMD(SMsgLoginServer_Login_rsp):
			{
				SMsgLoginServer_Login_rsp* extendMsg = MUTABLE_EXTENSION(realMsg, SMsgLoginServer_Login_rsp);
				if (extendMsg->ret() != 0)
				{

				}
				else
				{
					m_uActorid = extendMsg->actorid();
					m_uActorIDCoded = extendMsg->actoridcoded();
					TraceLn("µ«¬ºloginser≥…π¶");
					m_ClientState = ELOGIN_LOGINSERVER;
					ConnectZoneServer(extendMsg->regionip().c_str(),extendMsg->port());

				}
				break;
			}
		case NET_CMD(SMsgZoneServer_Login_rsp):
			{
				SMsgLoginServer_Login_rsp* extendMsg = MUTABLE_EXTENSION(realMsg, SMsgLoginServer_Login_rsp);
				if (extendMsg->ret() != 0)
				{
					ErrorLn("µ«¬º ß∞‹:"<<extendMsg->ret())
				}
				else
				{
					TraceLn("µ«¬ºzoneserver≥…π¶");
					m_ClientState = ELOGIN_ZONESERVER;
					LoginSuccess();
				}
				break;
			}
		case NET_CMD(SMsgSZ2C_Move):
			{
				SMsgSZ2C_Move* extendMsg = MUTABLE_EXTENSION(realMsg, SMsgSZ2C_Move);
				TraceLn("move syncobj:"<<extendMsg->vmapsynobj().actorid()<<"x:"<<extendMsg->dx()<<"Y:"<<extendMsg->dy());
				break;
			}
		case NET_CMD(SMsgSZ2C_EnterMap):
			{
				SMsgSZ2C_EnterMap* extendMsg = MUTABLE_EXTENSION(realMsg, SMsgSZ2C_EnterMap);
				TraceLn("add syncobj:"<<extendMsg->vmapsynobj().actorid()<<"x:"<<extendMsg->posx()<<"Y:"<<extendMsg->posy());
				break;
			}
		case NET_CMD(SMsgSZ2C_ExitMap):
			{
				SMsgSZ2C_ExitMap* extendMsg = MUTABLE_EXTENSION(realMsg, SMsgSZ2C_ExitMap);
				TraceLn("remov syncobj:"<<extendMsg->actorid());
				break;
			}
		case NET_CMD(SMsgZS2C_ActorItemsData):
			{
				SMsgZS2C_ActorItemsData* extendMsg = MUTABLE_EXTENSION(realMsg, SMsgZS2C_ActorItemsData);
				GetBagDataRsp(extendMsg);
				break;
			}
		case NET_CMD(SMsgSZ2C_SetProp):
			{
				m_bInit = true;
				SMsgSZ2C_SetProp* extendMsg = MUTABLE_EXTENSION(realMsg, SMsgSZ2C_SetProp);
				int propsize = extendMsg->gameproperty32_size();
				for (int Indx = 0; Indx < propsize; Indx++)
				{
					const ::ShiHun::NetMsgHead::GameProperty32& prop = extendMsg->gameproperty32(Indx);
					if (CREATURE_PROP_POSX == prop.propname())
					{
						m_nPosx = prop.value32();
					}
					if (CREATURE_PROP_POSY == prop.propname())
					{
						m_nPosy = prop.value32();
					}
					if (CREATURE_PROP_POSZ == prop.propname())
					{
						m_nPosz = prop.value32();
					}

				}
				break;
			}
		}
	}
}

void CClient::OnError( IConnection * conn,DWORD dwErrorCode )
{

}

bool CClient::ConnectLoginServer()
{

	m_pConnectionLogin = CreateTCPConnection(
		0,this, DEFAULT_PACK, 1000);
	if ( m_pConnectionLogin==0 )
	{
		return false;
	}
	if (!m_pConnectionLogin->Connect(m_szLoginIP.c_str(),m_nLoginPort))
		return false;
	m_ClientState = ECONNECT_LOGINING;
	return true;
}

bool CClient::ConnectZoneServer(const char * szCSIP,WORD nCSPort)
{
	m_pConnectionZone = CreateTCPConnection(
		0,this, DEFAULT_PACK, 1000);
	if ( m_pConnectionZone==0 )
	{
		return false;
	}
	if (!m_pConnectionZone->Connect(szCSIP,nCSPort))
		return false;
	m_ClientState = ECONNECT_ZONEING;
	return true;
}

bool CClient::LoginLoginServer()
{
	DECLARE_NET_MSG_NS(SMsgLoginServer_Login_req, msg, content, ShiHun::Login)
	content->set_username(m_szName.c_str());
	content->set_password(m_szPasswd.c_str());
	content->set_regionid(m_nZoneid);
	content->set_chanel("0");
	int len = msg.ByteSize();
	if (MAX_NET_PACKAGE_SIZE < len)
		return false;

	char buf[MAX_NET_PACKAGE_SIZE];
	msg.SerializeToArray(buf, MAX_NET_PACKAGE_SIZE);
	m_pConnectionLogin->SendData(buf, len, NO_COPY);

}

bool CClient::LoginZoneServer()
{
	DECLARE_NET_MSG_NS(SMsgZoneServer_Login_req, msg, content, ShiHun::Login)
	content->set_actorid(m_uActorid);
	content->set_actoridcoded(m_uActorIDCoded);
	content->set_chanel("0");
	int len = msg.ByteSize();
	if (MAX_NET_PACKAGE_SIZE < len)
		return false;

	char buf[MAX_NET_PACKAGE_SIZE];
	msg.SerializeToArray(buf, MAX_NET_PACKAGE_SIZE);
	m_pConnectionZone->SendData(buf, len, NO_COPY);
}

CClient::CClient(const std::string& strIp,int nPort, const std::string& strName, const std::string strPasswd,int nzoeid)
{
	m_pConnectionLogin =NULL;
	m_pConnectionZone = NULL;
	m_ClientState = ELOGIN_NULL;
	m_netMsgParse = CreateNewNetMsgParseInstance();
	m_szName = strName;
	m_szPasswd = strPasswd;
	m_szLoginIP = strIp;
	m_nLoginPort = nPort;
	m_nZoneid = nzoeid;
	m_bInit = false;
	g_pServiceProvider->GetTimeAxis()->SetTimer(1,(/*rand()%10+*/2)*1000,this);

}

CClient::~CClient()
{

}

void CClient::SendLoginKey()
{
	std::string pubkey; 
	//std::string pubkey="abc"; 
	m_pConnectionLogin->GetEncrypt()->genKeyPair(pubkey);
	m_pConnectionLogin->SendData(pubkey.c_str(), pubkey.length(), PROTO_FLAG_SYMMREQ);
}
void CClient::sendZoneKey()
{
	LoginZoneServer();
// 	std::string pubkey;
// 	m_pConnectionZone->GetEncrypt()->genKeyPair(pubkey);
// 	m_pConnectionZone->SendData(pubkey.c_str(), pubkey.length(), PROTO_FLAG_SYMMREQ);
}
void CClient::OnRecvHead( IConnection * conn,LPVOID pData,DWORD dwDataLen )
{
	char* msg = (char*)pData;
	MSG_PROTO_HEAD* proto = (MSG_PROTO_HEAD*)msg;
 	if (proto->wPFlag&PROTO_FLAG_SYMMRSP)
 	{
		if (m_ClientState == ECONNECT_LOGIN)
		{
			LoginLoginServer();
		}
		else if (m_ClientState == ECONNECT_ZONE)
		{
			LoginZoneServer();
		}
 	}
}

void CClient::LoginSuccess()
{
	//lihf 2017/03/10 ≤‚ ‘“∆∂Ø
	{
		//TestMove();
	}
	
	//lihf 2017/03/15 ≤‚ ‘ÃÌº”ŒÔ∆∑
	//TestAddItem();
	//GetBagData();
	//TestCorps();

}

void CClient::OnTimer( unsigned long dwTimerID )
{
	if (!m_bInit)
	{
		return;
	}
	//lihf 2017/03/10 ≤‚ ‘“∆∂Ø
	{
		TestMove();
	}
}
