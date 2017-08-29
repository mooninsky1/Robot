//==========================================================================
/**
* @file	  : MessageDispatch.h
* @author : pk <>
* created : 2008-1-15   17:13
* purpose : 网络消息分发器实现
*/
//==========================================================================

#ifndef __MESSAGEDISPATCH_H__
#define __MESSAGEDISPATCH_H__

#include "DGlobalMessage.h"
#include <map>
#include <google/protobuf/message.h>

/// 消息分发器
class MessageDispatch : public IMessageDispatch
{
public:
	
	/** 分发指定的消息
	@param buf 网络层输入的消息缓冲
	@param len 缓冲区长度
	*/
	virtual void						DispatchMessage(IClientConnection* connection, int num, ::google::protobuf::Message& msg);

	/** 注册消息处理者
	@param
	@param hander 消息处理者实例
	*/
	virtual void						RegisterMessageHandler(int num, IMessageHandler* handler);

	/** 取消注册消息处理者
	@param
	*/
	virtual void						UnregisterMessageHandler(int num);

	/** 注册消息处理者
	@param
	@param hander 消息处理者实例
	*/
	virtual void						RegisterMessageHandler(int numBegin, int numEnd, IMessageHandler* handler);

	/** 取消注册消息处理者
	@param
	*/
	virtual void						UnregisterMessageHandler(int numBegin, int numEnd);

	/** 构造
	@param moduleId
	*/
	MessageDispatch(void);

	/** 构造
	@param moduleId
	*/
	virtual ~MessageDispatch(void);

private:
	typedef std::map<int, IMessageHandler*> COLLECTION_MSG_HANDLER;

	COLLECTION_MSG_HANDLER					m_msgHandler;
};


#endif