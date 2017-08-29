#include "stdafx.h"
#include "Client.h"
#include "Login.pb.h"
#include "IProtoBuf.h"
#include "NetMsgHead.pb.h"
#include "Packer.h"
#include "Login.pb.h"
#include "Person.pb.h"
#include "Battle.pb.h"

using namespace rkt;
using namespace ShiHun;
using namespace Login;
using namespace Person;
using namespace Battle;

void CClient::TestBattle()
{
	DECLARE_NET_MSG(SMsgC2ZS_EnterGameLevel, msg, content)
	::ShiHun::NetMsgHead::ClientID* pclient = content->mutable_clientid();
	pclient->set_actorid(1);
	pclient->set_actoridcoded(1);
	content->set_mapid(101);
	content->set_battletype(1);
	int len = msg.ByteSize();
	if (MAX_NET_PACKAGE_SIZE < len)
		return ;

	char buf[MAX_NET_PACKAGE_SIZE];
	msg.SerializeToArray(buf, MAX_NET_PACKAGE_SIZE);
	m_pConnectionZone->SendData(buf, len, NO_COPY);
	Fight();
}

void CClient::Fight()
{
	DECLARE_NET_MSG(SMsgC2ZS_BattleFight, msg, content)
	::ShiHun::NetMsgHead::ClientID* pclient = content->mutable_clientid();
	pclient->set_actorid(1);
	pclient->set_actoridcoded(1);
	content->set_battletype(1);
	content->set_win(1);
	::ShiHun::Battle::SContextFight* pfight = content->mutable_fight();
	
	int len = msg.ByteSize();
	if (MAX_NET_PACKAGE_SIZE < len)
		return ;

	char buf[MAX_NET_PACKAGE_SIZE];
	msg.SerializeToArray(buf, MAX_NET_PACKAGE_SIZE);
	m_pConnectionZone->SendData(buf, len, NO_COPY);
}