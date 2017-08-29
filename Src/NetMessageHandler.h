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
#pragma once

class CNetMessageHandler : public IDBServerMessageHandler,
						   public ILoginServerMessageHandler
{
public:
	/////////////////////////////IGatewayMessageHandler/////////////////
	/**
	@name         : ���ط�����֪ͨ��Ϸ��������һ���µĿͻ���������
	@param  client: �ÿͻ��������ط������ϵ�ID
	@return       :
	*/
	virtual void HandleClientIncoming(ClientID client);

	/**
	@name         : ���ط�����֪ͨ��Ϸ���������µ����ݰ�����
	@brief        : �����ݰ��ǿͻ��˷�������Ϸ��������,ͨ�����ݰ���ͷ��wKeyServer�ֽ�ָ��
	@param client : �������ݵĿͻ���ID
	@param pData  : ���ݻ�����λ��
	@param wDataLen:���ݳ���
	*/
	virtual void HandleReceivedData(ClientID client,LPVOID pData,WORD wDataLen);

	/**
	@name         : ���ط�����֪ͨ��Ϸ�����������ӶϿ�
	@param client : �Ͽ����ӵĿͻ���ID
	@param dwReason:�Ͽ���ԭ��������
	*/
	virtual void HandleClientDisconnect(ClientID client,DWORD dwReason);

	/////////////////////////ICenterServerMessageHandler////////////////
	/**
	@name         : ֪ͨ�������б��Ѿ�����
	@brief        : ������б����ICenterServerConnector::GetServerList���
	*/
	//virtual void HandleServerListUpdated();

	/**
	@name         : ֪ͨ��������Ϣ����
	@brief        : ��������������仯�ȵ�
	*/	
	//virtual void HandleServerInfoUpdated(CSID ServerID,SERVER_STATE nState,ServerData * pInfo);

	/**
	@name         : ��������������ͨ�����ķ�����ת������Ϣ
	@brief        : �������ݲ����
	*/
	virtual void HandlePostMessage(CGID server, const char * pData,WORD wDataLen);

	/**
	@name         : �յ�����,ִ��һ������
	@brief        : 
	@param server : ��������ķ�����ID
	@param szCommand : ������
	@return       : ִ�к����ICenterServerConnector::SendCommandResponse��������ִ�н��
	*/
	virtual void HandleCommandRequest(CGID server,const char * szCommand);

	/**
	@name          : ��������ִ�еĽ��
	@brief         :
	@param szCommand:ִ�е������ַ���
	@param bSuccess: �����Ƿ�ִ�гɹ�
	@param szOutput: �������ʾ��Ϣ
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
							