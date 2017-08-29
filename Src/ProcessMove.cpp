#include "stdafx.h"
#include "Client.h"
#include "Login.pb.h"
#include "IProtoBuf.h"
#include "NetMsgHead.pb.h"
#include "Packer.h"
#include "Login.pb.h"
#include "Person.pb.h"

using namespace rkt;
using namespace ShiHun;
using namespace Login;
using namespace Person;

void CClient::TestMove()
{
	static bool  bsync = false;
	if (!bsync)
	{
		DECLARE_NET_MSG(SMsgC2SZ_Move, msg, content)
		content->set_sx(m_nPosx);
		content->set_sy(m_nPosy);
		m_nPosxEnd = m_nPosx+5-rand()%10;
		m_nPosyEnd = m_nPosy+5-rand()%10;
		m_nPosxEnd = max(0,min(140,m_nPosxEnd));
		m_nPosyEnd = max(0,min(99,m_nPosyEnd));
		content->set_dx(m_nPosxEnd);
		content->set_dy(m_nPosyEnd);
		content->set_dz(m_nPosz);
		int len = msg.ByteSize();
		if (MAX_NET_PACKAGE_SIZE < len)
			return ;

		char buf[MAX_NET_PACKAGE_SIZE];
		msg.SerializeToArray(buf, MAX_NET_PACKAGE_SIZE);
		m_pConnectionZone->SendData(buf, len, NO_COPY);
		bsync = !bsync;
	}
	if (bsync)
	{
		DECLARE_NET_MSG(SMsgC2SZ_MoveEnd, msg, content)
		content->set_dx(m_nPosxEnd);
		content->set_dy(m_nPosyEnd);
		content->set_dz(m_nPosz);
		int len = msg.ByteSize();
		if (MAX_NET_PACKAGE_SIZE < len)
			return ;

		char buf[MAX_NET_PACKAGE_SIZE];
		msg.SerializeToArray(buf, MAX_NET_PACKAGE_SIZE);
		m_pConnectionZone->SendData(buf, len, NO_COPY);
		bsync = !bsync;
	}
	
}