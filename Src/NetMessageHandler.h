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
#pragma once

class CNetMessageHandler : public IDBServerMessageHandler,
						   public ILoginServerMessageHandler
{
public:
	/////////////////////////////IGatewayMessageHandler/////////////////
	/**
	@name         : 网关服务器通知游戏服务器有一个新的客户端连进来
	@param  client: 该客户端在网关服务器上的ID
	@return       :
	*/
	virtual void HandleClientIncoming(ClientID client);

	/**
	@name         : 网关服务器通知游戏服务器有新的数据包到达
	@brief        : 该数据包是客户端发给该游戏服务器的,通过数据包包头的wKeyServer字节指定
	@param client : 发送数据的客户端ID
	@param pData  : 数据缓冲区位置
	@param wDataLen:数据长度
	*/
	virtual void HandleReceivedData(ClientID client,LPVOID pData,WORD wDataLen);

	/**
	@name         : 网关服务器通知游戏服务器有连接断开
	@param client : 断开连接的客户端ID
	@param dwReason:断开的原因或错误码
	*/
	virtual void HandleClientDisconnect(ClientID client,DWORD dwReason);

	/////////////////////////ICenterServerMessageHandler////////////////
	/**
	@name         : 通知服务器列表已经更新
	@brief        : 具体的列表调用ICenterServerConnector::GetServerList获得
	*/
	//virtual void HandleServerListUpdated();

	/**
	@name         : 通知服务器信息更新
	@brief        : 例如服务器人数变化等等
	*/	
	//virtual void HandleServerInfoUpdated(CSID ServerID,SERVER_STATE nState,ServerData * pInfo);

	/**
	@name         : 处理其他服务器通过中心服务器转发的消息
	@brief        : 具体内容不清楚
	*/
	virtual void HandlePostMessage(CGID server, const char * pData,WORD wDataLen);

	/**
	@name         : 收到请求,执行一个命令
	@brief        : 
	@param server : 发送命令的服务器ID
	@param szCommand : 命令行
	@return       : 执行后调用ICenterServerConnector::SendCommandResponse返回命令执行结果
	*/
	virtual void HandleCommandRequest(CGID server,const char * szCommand);

	/**
	@name          : 处理命令执行的结果
	@brief         :
	@param szCommand:执行的命令字符串
	@param bSuccess: 命令是否执行成功
	@param szOutput: 输出的提示信息
	@return        :
	*/
	virtual void HandleCommandResponse(const char * szCommand,bool bSuccess,const char * szOutput);

	/////////////////////////////CNetMessageHandler///////////////////
	/** 
	@param   
	@param   
	@return  
	*/
	CNetMessageHandler(void);

	/** 
	@param   
	@param   
	@return  
	*/
	virtual ~CNetMessageHandler(void);
};
							