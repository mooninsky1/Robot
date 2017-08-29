//==========================================================================
/**
* @file	  : MessageDispatch.h
* @author : pk <>
* created : 2008-1-15   17:13
* purpose : ������Ϣ�ַ���ʵ��
*/
//==========================================================================

#ifndef __MESSAGEDISPATCH_H__
#define __MESSAGEDISPATCH_H__

#include "DGlobalMessage.h"
#include <map>
#include <google/protobuf/message.h>

/// ��Ϣ�ַ���
class MessageDispatch : public IMessageDispatch
{
public:
	
	/** �ַ�ָ������Ϣ
	@param buf ������������Ϣ����
	@param len ����������
	*/
	virtual void						DispatchMessage(IClientConnection* connection, int num, ::google::protobuf::Message& msg);

	/** ע����Ϣ������
	@param
	@param hander ��Ϣ������ʵ��
	*/
	virtual void						RegisterMessageHandler(int num, IMessageHandler* handler);

	/** ȡ��ע����Ϣ������
	@param
	*/
	virtual void						UnregisterMessageHandler(int num);

	/** ע����Ϣ������
	@param
	@param hander ��Ϣ������ʵ��
	*/
	virtual void						RegisterMessageHandler(int numBegin, int numEnd, IMessageHandler* handler);

	/** ȡ��ע����Ϣ������
	@param
	*/
	virtual void						UnregisterMessageHandler(int numBegin, int numEnd);

	/** ����
	@param moduleId
	*/
	MessageDispatch(void);

	/** ����
	@param moduleId
	*/
	virtual ~MessageDispatch(void);

private:
	typedef std::map<int, IMessageHandler*> COLLECTION_MSG_HANDLER;

	COLLECTION_MSG_HANDLER					m_msgHandler;
};


#endif