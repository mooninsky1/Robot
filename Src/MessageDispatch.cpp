//==========================================================================
/**
* @file	  : MessageDispatch.cpp
* @author : pk <>
* created : 2008-1-15   17:13
*/
//==========================================================================

#include "stdafx.h"
#include "MessageDispatch.h"
#include "NetMsgHead.pb.h"
#include "IClientConnectionManager.h"
#include "..\..\GameError.h"
#include "DebugNew.h"
#include "Login.pb.h"

using namespace ShiHun::Login;

/** 构造
@param moduleId
*/
MessageDispatch::MessageDispatch()
{
}

/** 构造
@param moduleId
*/
MessageDispatch::~MessageDispatch()
{

}

/** 分发指定的消息
@param buf 网络层输入的消息缓冲
@param len 缓冲区长度
*/
void MessageDispatch::DispatchMessage(IClientConnection* connection, int num, ::google::protobuf::Message& msg)
{
	if (m_msgHandler.find(num) != m_msgHandler.end())
	{
		IMessageHandler* handler = m_msgHandler[num];
		try
		{
			handler->onMessage(connection, num, msg);
		}
		catch (...)
		{
			ErrorLn("msg ID:"<<num<<"出现异常");
		}
		
		
	}
	else
	{
		WarningLn("未处理的消息号num = " << num);
	}
	
}

/** 注册消息处理者
@param
@param hander 消息处理者实例
*/
void MessageDispatch::RegisterMessageHandler(int num, IMessageHandler* handler)
{
	if (m_msgHandler.find(num) == m_msgHandler.end())
	{
		m_msgHandler[num] = handler;
	}
	else
	{

		ErrorLn("num重复，num = " << num);
	}
}

/** 取消注册消息处理者
@param
*/
void MessageDispatch::UnregisterMessageHandler(int num)
{
	m_msgHandler.erase(num);
}

/** 注册消息处理者
@param
@param hander 消息处理者实例
*/
void MessageDispatch::RegisterMessageHandler(int numBegin, int numEnd, IMessageHandler* handler)
{
	for (int i = numBegin; i <= numEnd; ++i)
	{
		RegisterMessageHandler(i, handler);
	}
}

/** 取消注册消息处理者
@param
*/
void MessageDispatch::UnregisterMessageHandler(int numBegin, int numEnd)
{
	for (int i = numBegin; i <= numEnd; ++i)
	{
		UnregisterMessageHandler(i);
	}
}