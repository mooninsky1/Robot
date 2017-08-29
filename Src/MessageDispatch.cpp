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

/** ����
@param moduleId
*/
MessageDispatch::MessageDispatch()
{
}

/** ����
@param moduleId
*/
MessageDispatch::~MessageDispatch()
{

}

/** �ַ�ָ������Ϣ
@param buf ������������Ϣ����
@param len ����������
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
			ErrorLn("msg ID:"<<num<<"�����쳣");
		}
		
		
	}
	else
	{
		WarningLn("δ�������Ϣ��num = " << num);
	}
	
}

/** ע����Ϣ������
@param
@param hander ��Ϣ������ʵ��
*/
void MessageDispatch::RegisterMessageHandler(int num, IMessageHandler* handler)
{
	if (m_msgHandler.find(num) == m_msgHandler.end())
	{
		m_msgHandler[num] = handler;
	}
	else
	{

		ErrorLn("num�ظ���num = " << num);
	}
}

/** ȡ��ע����Ϣ������
@param
*/
void MessageDispatch::UnregisterMessageHandler(int num)
{
	m_msgHandler.erase(num);
}

/** ע����Ϣ������
@param
@param hander ��Ϣ������ʵ��
*/
void MessageDispatch::RegisterMessageHandler(int numBegin, int numEnd, IMessageHandler* handler)
{
	for (int i = numBegin; i <= numEnd; ++i)
	{
		RegisterMessageHandler(i, handler);
	}
}

/** ȡ��ע����Ϣ������
@param
*/
void MessageDispatch::UnregisterMessageHandler(int numBegin, int numEnd)
{
	for (int i = numBegin; i <= numEnd; ++i)
	{
		UnregisterMessageHandler(i);
	}
}