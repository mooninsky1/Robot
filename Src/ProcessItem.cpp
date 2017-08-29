#include "stdafx.h"
#include "Client.h"
#include "Login.pb.h"
#include "IProtoBuf.h"
#include "NetMsgHead.pb.h"
#include "Packer.h"
#include "Login.pb.h"
#include "Person.pb.h"
#include "Item.pb.h"

using namespace rkt;
using namespace ShiHun;
using namespace Login;
using namespace Person;
using namespace Item;

void CClient::TestAddItem()
{
	DECLARE_NET_MSG(SMsgC2ZS_GMAddItem, msg, content)
	content->set_resoureid(1);
	content->set_itemnum(2);
	int len = msg.ByteSize();
	if (MAX_NET_PACKAGE_SIZE < len)
		return ;

	char buf[MAX_NET_PACKAGE_SIZE];
	msg.SerializeToArray(buf, MAX_NET_PACKAGE_SIZE);
	m_pConnectionZone->SendData(buf, len, NO_COPY);
}
void CClient::GetBagData()
{
	DECLARE_NET_MSG(SMsgC2ZS_GetBagData, msg, content)
	::ShiHun::NetMsgHead::ClientID* pclient = content->mutable_clientid();
	pclient->set_actorid(1);
	pclient->set_actoridcoded(1);
	int len = msg.ByteSize();
	if (MAX_NET_PACKAGE_SIZE < len)
		return ;

	char buf[MAX_NET_PACKAGE_SIZE];
	msg.SerializeToArray(buf, MAX_NET_PACKAGE_SIZE);
	m_pConnectionZone->SendData(buf, len, NO_COPY);
}

void CClient::GetBagDataRsp(SMsgZS2C_ActorItemsData* extendMsg)
{
	int cardsize = extendMsg->cards_size();
	if (cardsize > 0 )
	{
		for (int i=0; i<cardsize; i++)
		{
			int serverid = 0;
			int resid = 0;
			int count = 0;
			int level =0;
			const ::ShiHun::NetMsgHead::ItemIDCount& pItem = extendMsg->cards(0);
			const ::ShiHun::NetMsgHead::ItemID& Itemid = pItem.itemid();
			serverid = Itemid.itemserverid();
			resid = Itemid.itemprop().resourceid();
			level = Itemid.itemprop().level();
			count = pItem.count();
			TraceLn("iteid:"<<resid<<"count:"<<count<<"level:"<<level)
			if (0 == i )
			{
				DECLARE_NET_MSG(SMsgC2ZS_ItemLevelup, msg, content)
				content->set_itemserverid(serverid);
				int len = msg.ByteSize();
				if (MAX_NET_PACKAGE_SIZE < len)
					return ;

				char buf[MAX_NET_PACKAGE_SIZE];
				msg.SerializeToArray(buf, MAX_NET_PACKAGE_SIZE);
				m_pConnectionZone->SendData(buf, len, NO_COPY);
			}
			
		}
		

	}
}