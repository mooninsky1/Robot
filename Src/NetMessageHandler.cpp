/*******************************************************************
** �ļ���:	e:\Rocket\Server\ZoneServer\Src\NetMessageHandler.h
** ��  Ȩ:	(C) 
** ������:	pdata
** ��  ��:	2008/3/7  21:52
** ��  ��:	1.0
** ��  ��:	������Ϣ�����ߣ����ķ������ط���
** Ӧ  ��:  	

**************************** �޸ļ�¼ ******************************
** �޸���: 
** ��  ��: 
** ��  ��: 
********************************************************************/
#include "StdAfx.h"
#include <winsock2.h>
#include "NetMessageHandler.h"
#include "ZoneServiceProvider.h"
#include "DebugNew.h"

/** 
@param   
@param   
@return  
*/
CNetMessageHandler::CNetMessageHandler(void)
{

}

/** 
@param   
@param   
@return  
*/
CNetMessageHandler::~CNetMessageHandler(void)
{

}

/**
@name         : ���ط�����֪ͨ��Ϸ��������һ���µĿͻ���������
@param  client: �ÿͻ��������ط������ϵ�ID
@return       :
*/
void CNetMessageHandler::HandleClientIncoming(ClientID client)
{

}

/**
@name         : ���ط�����֪ͨ��Ϸ���������µ����ݰ�����
@brief        : �����ݰ��ǿͻ��˷�������Ϸ��������,ͨ�����ݰ���ͷ��wKeyServer�ֽ�ָ��
@param client : �������ݵĿͻ���ID
@param pData  : ���ݻ�����λ��
@param wDataLen:���ݳ���
*/
void CNetMessageHandler::HandleReceivedData(ClientID client,LPVOID pData,WORD wDataLen)
{
// 	IEnterManager* p = g_pServiceProvider->GetEnterManager();
// 	
// 	if (p != NULL)
// 		p->HandleReceivedData(client, pData, wDataLen);
}

/**
@name         : ���ط�����֪ͨ��Ϸ�����������ӶϿ�
@param client : �Ͽ����ӵĿͻ���ID
@param dwReason:�Ͽ���ԭ��������
*/
void CNetMessageHandler::HandleClientDisconnect(ClientID client,DWORD dwReason)
{
// 	IEnterManager* p = g_pServiceProvider->GetEnterManager();
// 	
// 	if (p != NULL)
// 		p->HandleClientDisconnect(client, dwReason);
}

/**
@name          : ֪ͨ�ͻ���Ǩ�ƽ��
@param client  : ��Ǩ�ƵĿͻ���
@param result  : Ǩ�ƵĽ���ֳ�
*/
//void CNetMessageHandler::HandleMigrateResult(ClientID client,SMsgGatewayMigrateResult * result)
//{
// 	IEnterManager* p = g_pServiceProvider->GetEnterManager();
// 	
// 	if (p != NULL)
// 		p->HandleMigrateResult(client, (LPVOID)result, sizeof(SMsgGatewayMigrateResult));
//}

/**
@name         : ֪ͨ��������Ϣ����
@brief        : ��������������仯�ȵ�
*/
//void CNetMessageHandler::HandleServerInfoUpdated(CSID ServerID,SERVER_STATE nState,ServerData * pInfo)
//{
//}

/**
@name         : ֪ͨ�������б��Ѿ�����
@brief        : ������б����ICenterServerConnector::GetServerList���
*//*
void CNetMessageHandler::HandleServerListUpdated()
{
	// ȡ�ó������������
	SZoneServerConfigInfo * pZoneServerConfing = g_pServiceProvider->GetSchemeCenter()->GetZoneServerConfigInfo();
	if(pZoneServerConfing == NULL)
	{
		return;
	}

	ICenterServerConnector * pCenterServerConnector = g_pServiceProvider->GetCenterServerConnector();
	if(pCenterServerConnector == NULL)
	{
		return;
	}

	IGatewayConnectorManager * pGatewayConnectorManager = g_pServiceProvider->GetGatewayConnectorManager();
	if(pGatewayConnectorManager == NULL)
	{
		return;
	}

	// ��������ط��������£�����/ֹͣ�������������ط������������ӵĻ���ԣ�
	ServerData * svrInfo[MAX_SERVER_COUNT];
	ulong count = pCenterServerConnector->GetServerList(svrInfo, MAX_SERVER_COUNT, INVALID_SERVER_ID, MSG_ENDPOINT_GATEWAY);

	Trace("Connect to GatewayServer, count = "<<count<<endl);

	// ���ȥ�����ط�
	for(ulong i = 0; i < count; i++)
	{
		if(svrInfo[i])
		{
			Assert(svrInfo[i]->wServerInfoLen == sizeof(ServerInfo_Gateway));
			ServerInfo_Gateway * edg = (ServerInfo_Gateway *)svrInfo[i]->pServerInfoData;

			in_addr addr;
			addr.s_addr = edg->dwGatewayIP;

			pGatewayConnectorManager->ConnectGatewayServer(inet_ntoa(addr), ntohs(edg->wGatewayPort));				
		}
	}

	// �����ط�����ע�᱾�ط���������Ϣ
	pGatewayConnectorManager->RegisterServer(MSG_ENDPOINT_ZONE, pCenterServerConnector->GetLocalServerCSID());
}*/

/**
@name         : ��������������ͨ�����ķ�����ת������Ϣ
@brief        : �������ݲ����
*/
void CNetMessageHandler::HandlePostMessage(CGID server, const char * pData,WORD wDataLen)
{
	// �ַ�
	//g_pServiceProvider->GetMessageDispatch()->dispatchTransmit(server, (LPVOID)pData, wDataLen);
}

/**
@name         : �յ�����,ִ��һ������
@brief        : 
@param server : ��������ķ�����ID
@param szCommand : ������
@return       : ִ�к����ICenterServerConnector::SendCommandResponse��������ִ�н��
*/
void CNetMessageHandler::HandleCommandRequest(CGID server,const char * szCommand)
{

}

/**
@name          : ��������ִ�еĽ��
@brief         :
@param szCommand:ִ�е������ַ���
@param bSuccess: �����Ƿ�ִ�гɹ�
@param szOutput: �������ʾ��Ϣ
@return        :
*/
void CNetMessageHandler::HandleCommandResponse(const char * szCommand,bool bSuccess,const char * szOutput)
{

}

