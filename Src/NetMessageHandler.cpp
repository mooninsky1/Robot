/*******************************************************************
** 文件名:	e:\Rocket\Server\ZoneServer\Src\NetMessageHandler.h
** 版  权:	(C) 
** 创建人:	pdata
** 日  期:	2008/3/7  21:52
** 版  本:	1.0
** 描  述:	网络消息处理者（中心服、网关服）
** 应  用:  	

**************************** 修改记录 ******************************
** 修改人: 
** 日  期: 
** 描  述: 
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
@name         : 网关服务器通知游戏服务器有一个新的客户端连进来
@param  client: 该客户端在网关服务器上的ID
@return       :
*/
void CNetMessageHandler::HandleClientIncoming(ClientID client)
{

}

/**
@name         : 网关服务器通知游戏服务器有新的数据包到达
@brief        : 该数据包是客户端发给该游戏服务器的,通过数据包包头的wKeyServer字节指定
@param client : 发送数据的客户端ID
@param pData  : 数据缓冲区位置
@param wDataLen:数据长度
*/
void CNetMessageHandler::HandleReceivedData(ClientID client,LPVOID pData,WORD wDataLen)
{
// 	IEnterManager* p = g_pServiceProvider->GetEnterManager();
// 	
// 	if (p != NULL)
// 		p->HandleReceivedData(client, pData, wDataLen);
}

/**
@name         : 网关服务器通知游戏服务器有连接断开
@param client : 断开连接的客户端ID
@param dwReason:断开的原因或错误码
*/
void CNetMessageHandler::HandleClientDisconnect(ClientID client,DWORD dwReason)
{
// 	IEnterManager* p = g_pServiceProvider->GetEnterManager();
// 	
// 	if (p != NULL)
// 		p->HandleClientDisconnect(client, dwReason);
}

/**
@name          : 通知客户端迁移结果
@param client  : 被迁移的客户端
@param result  : 迁移的结果现场
*/
//void CNetMessageHandler::HandleMigrateResult(ClientID client,SMsgGatewayMigrateResult * result)
//{
// 	IEnterManager* p = g_pServiceProvider->GetEnterManager();
// 	
// 	if (p != NULL)
// 		p->HandleMigrateResult(client, (LPVOID)result, sizeof(SMsgGatewayMigrateResult));
//}

/**
@name         : 通知服务器信息更新
@brief        : 例如服务器人数变化等等
*/
//void CNetMessageHandler::HandleServerInfoUpdated(CSID ServerID,SERVER_STATE nState,ServerData * pInfo)
//{
//}

/**
@name         : 通知服务器列表已经更新
@brief        : 具体的列表调用ICenterServerConnector::GetServerList获得
*//*
void CNetMessageHandler::HandleServerListUpdated()
{
	// 取得场景服相关配置
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

	// 如果有网关服务器更新（启动/停止），则连接网关服务器（已连接的会忽略）
	ServerData * svrInfo[MAX_SERVER_COUNT];
	ulong count = pCenterServerConnector->GetServerList(svrInfo, MAX_SERVER_COUNT, INVALID_SERVER_ID, MSG_ENDPOINT_GATEWAY);

	Trace("Connect to GatewayServer, count = "<<count<<endl);

	// 逐个去连网关服
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

	// 向网关服务器注册本地服务器的信息
	pGatewayConnectorManager->RegisterServer(MSG_ENDPOINT_ZONE, pCenterServerConnector->GetLocalServerCSID());
}*/

/**
@name         : 处理其他服务器通过中心服务器转发的消息
@brief        : 具体内容不清楚
*/
void CNetMessageHandler::HandlePostMessage(CGID server, const char * pData,WORD wDataLen)
{
	// 分发
	//g_pServiceProvider->GetMessageDispatch()->dispatchTransmit(server, (LPVOID)pData, wDataLen);
}

/**
@name         : 收到请求,执行一个命令
@brief        : 
@param server : 发送命令的服务器ID
@param szCommand : 命令行
@return       : 执行后调用ICenterServerConnector::SendCommandResponse返回命令执行结果
*/
void CNetMessageHandler::HandleCommandRequest(CGID server,const char * szCommand)
{

}

/**
@name          : 处理命令执行的结果
@brief         :
@param szCommand:执行的命令字符串
@param bSuccess: 命令是否执行成功
@param szOutput: 输出的提示信息
@return        :
*/
void CNetMessageHandler::HandleCommandResponse(const char * szCommand,bool bSuccess,const char * szOutput)
{

}

