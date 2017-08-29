#include "stdafx.h"
#include "Client.h"
#include "Login.pb.h"
#include "IProtoBuf.h"
#include "NetMsgHead.pb.h"
#include "Packer.h"
#include "Login.pb.h"
#include "Person.pb.h"
#include "Corps.pb.h"

using namespace rkt;
using namespace ShiHun;
using namespace Login;
using namespace Person;
using namespace Corps;

void CClient::TestCorps()
{
	DECLARE_NET_MSG(SMsgC2ZS_CreateCorps, msg, content)
	content->set_name("lhf");
	content->set_head(1);
	int len = msg.ByteSize();
	if (MAX_NET_PACKAGE_SIZE < len)
		return ;

	char buf[MAX_NET_PACKAGE_SIZE];
	msg.SerializeToArray(buf, MAX_NET_PACKAGE_SIZE);
	m_pConnectionZone->SendData(buf, len, NO_COPY);
}