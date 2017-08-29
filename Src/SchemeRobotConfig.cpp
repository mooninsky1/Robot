/*******************************************************************
** �ļ���:	e:\Rocket\Server\ZoneServer\Src\SchemeZoneServer.h
** ��  Ȩ:	(C) 
** ������:	pdata
** ��  ��:	2008/3/4  10:46
** ��  ��:	1.0
** ��  ��:  ����������
** Ӧ  ��:  	

**************************** �޸ļ�¼ ******************************
** �޸���: 
** ��  ��: 
** ��  ��: 
********************************************************************/
#include "stdafx.h"
#include "SchemeRobotConfig.h"
#include "ExternalFacade.h"
#include <string>
#include "DebugNew.h"
using namespace std;


/** 
@param   
@param   
@return  
*/
CSchemeRobotConfig::CSchemeRobotConfig(void)
{
	// �������������
	memset(&m_RobotConfig, 0, sizeof(m_RobotConfig));	
}

/** 
@param   
@param   
@return  
*/
CSchemeRobotConfig::~CSchemeRobotConfig(void)
{

}

/** 
@param   
@param   
@return  
*/
bool CSchemeRobotConfig::LoadScheme(void)
{
	ISchemeEngine * pSchemeEngine = g_pServiceProvider->GetSchemeEngine();
	if(pSchemeEngine == NULL)
	{
		return false;
	}

	// ���ؽű�
	string stringPath = g_ExternalFacade.GetWorkDir();	
	stringPath += ROBOTCONFIG_SCHEME_FILENAME;

	bool bResult = pSchemeEngine->LoadScheme(stringPath.c_str(), (ISchemeUpdateSink *)this, false);
	if(!bResult)
	{
		ErrorLn("���������ļ�ʧ�ܡ��ļ��� = " << stringPath.c_str());

		return false;
	}	

	g_pSchemeRobotConfig = this;

	return true;
}

/** �ر�
@param   
@param   
@return  
*/
void CSchemeRobotConfig::Close(void)
{	

}

/** CSV��������ʱ֪ͨ
@param   pCSVReader����ȡCSV�ķ��ؽӿ�
@param   szFileName�������ļ���
@param   
@return  
@note     
@warning ��Ҫ�ڴ˷����ͷ�pCSVReader����pTiXmlDocument,��Ϊһ���ļ���Ӧ���sink
@retval buffer 
*/ 
bool CSchemeRobotConfig::OnSchemeLoad(ICSVReader * pCSVReader,LPCSTR szFileName)
{
	return false;	
}

/** XML��������ʱ֪ͨ
@param   pTiXmlDocument����ȡXML�ķ��ؽӿ�
@param   szFileName�������ļ���
@param   
@return  
@note     
@warning ��Ҫ�ڴ˷����ͷ�pCSVReader����pTiXmlDocument,��Ϊһ���ļ���Ӧ���sink
@retval buffer 
*/
bool CSchemeRobotConfig::OnSchemeLoad(TiXmlDocument * pTiXmlDocument,LPCSTR szFileName)
{
	if(pTiXmlDocument == NULL)
	{
		return false;
	}

	// �������������
	memset(&m_RobotConfig, 0, sizeof(m_RobotConfig));	

	// [scheme]
	TiXmlElement * pRootElement = pTiXmlDocument->FirstChildElement("scheme");
	if(pRootElement == NULL)
	{
		return false;
	}

	
	TiXmlElement * pSubElement = pRootElement->FirstChildElement("loginserverip");
	if(pSubElement == NULL)
	{
		return false;
	}
	LPCSTR pszAttrProp = pSubElement->Attribute("ip");
	if(pszAttrProp == NULL )
	{
		return false;
	}
	safeStrncpy(m_RobotConfig.szLoginServerIP, pszAttrProp);
	
	pSubElement = pRootElement->FirstChildElement("loginserverport");
	if(pSubElement == NULL)
	{
		return false;
	}
	pszAttrProp = pSubElement->Attribute("port", &m_RobotConfig.nLoginServerPort);
	if(pszAttrProp == NULL || m_RobotConfig.nLoginServerPort < 0)
	{
		return false;
	}

	pSubElement = pRootElement->FirstChildElement("robotcount");
	if(pSubElement == NULL)
	{
		return false;
	}
	pszAttrProp = pSubElement->Attribute("count", &m_RobotConfig.nRobotCount);
	if(pszAttrProp == NULL || m_RobotConfig.nRobotCount < 0)
	{
		return false;
	}
	
	pSubElement = pRootElement->FirstChildElement("robotnmae");
	if(pSubElement == NULL)
	{
		return false;
	}
	pszAttrProp = pSubElement->Attribute("name");
	if(pszAttrProp == NULL )
	{
		return false;
	}
	safeStrncpy(m_RobotConfig.szRobotName, pszAttrProp);
	
	pSubElement = pRootElement->FirstChildElement("passwd");
	if(pSubElement == NULL)
	{
		return false;
	}
	pszAttrProp = pSubElement->Attribute("pd");
	if(pszAttrProp == NULL )
	{
		return false;
	}
	safeStrncpy(m_RobotConfig.szPasswd, pszAttrProp);

	pSubElement = pRootElement->FirstChildElement("zoneid");
	if(pSubElement == NULL)
	{
		return false;
	}
	pszAttrProp = pSubElement->Attribute("id", &m_RobotConfig.nZoneID);
	if(pszAttrProp == NULL || m_RobotConfig.nZoneID < 0)
	{
		return false;
	}
	
	return true;
}

/** ���ö�̬����ʱ֪ͨ
@param   pCSVReader����ȡCSV�ķ��ؽӿ�
@param   szFileName�������ļ���
@param   
@return  
@note     
@warning ��Ҫ�ڴ˷����ͷ�pCSVReader����pTiXmlDocument,��Ϊһ���ļ���Ӧ���sink
@retval buffer 
*/
bool CSchemeRobotConfig::OnSchemeUpdate(ICSVReader * pCSVReader, LPCSTR szFileName)
{
	return false;
}

/** ���ö�̬����ʱ֪ͨ
@param   pTiXmlDocument����ȡXML�ķ��ؽӿ�
@param   szFileName�������ļ���
@param   
@return  
@note     
@warning ��Ҫ�ڴ˷����ͷ�pCSVReader����pTiXmlDocument,��Ϊһ���ļ���Ӧ���sink
@retval buffer 
*/
bool CSchemeRobotConfig::OnSchemeUpdate(TiXmlDocument * pTiXmlDocument, LPCSTR szFileName)
{
	return false;
}

/** ȡ���������Զһ�����
@param   
@param   
@return  
*/
SRobotConfigInfo * CSchemeRobotConfig::GetRobotConfigInfo(void)
{
	return &m_RobotConfig;
}

/** 
@param   
@param   
@return  
*/
bool CSchemeRobotConfig::InputRobotConfigInfo(SRobotConfigInfo * pInfo)
{
	TiXmlDocument tixmldocument;

	// ���ؽű�
	string stringPath = g_ExternalFacade.GetWorkDir();	
	stringPath += ROBOTCONFIG_SCHEME_FILENAME;

	// ������
	tixmldocument.LoadFile(stringPath.c_str());

	// [scheme]
	TiXmlElement * pRootElement = tixmldocument.FirstChildElement("scheme");
	if(pRootElement == NULL)
	{
		return false;
	}

	
	TiXmlElement * pSubElement = pRootElement->FirstChildElement("loginserverip");
	if(pSubElement == NULL)
	{
		return false;
	}
	pSubElement->SetAttribute("ip", pInfo->szLoginServerIP);

	
	pSubElement = pRootElement->FirstChildElement("loginserverport");
	if(pSubElement == NULL)
	{
		return false;
	}
	pSubElement->SetAttribute("port", pInfo->nLoginServerPort);


	pSubElement = pRootElement->FirstChildElement("robotcount");
	if(pSubElement == NULL)
	{
		return false;
	}
	pSubElement->SetAttribute("count", pInfo->nRobotCount);

	
	pSubElement = pRootElement->FirstChildElement("robotnmae");
	if(pSubElement == NULL)
	{
		return false;
	}
	pSubElement->SetAttribute("name", pInfo->szRobotName);

	return true;
}

bool CSchemeRobotConfig::OnSchemeLoad(IBinarySerialize* bianrySerialize, const char* filename)
{
	return false;
}

bool CSchemeRobotConfig::OnSchemeLoad( ICSVReader2 * pCSVReader,const char* szFileName )
{
	return false;
}

bool CSchemeRobotConfig::OnSchemeUpdate(IBinarySerialize* bianrySerialize, const char* filename)
{
	return false;
}

bool CSchemeRobotConfig::OnSchemeUpdate( ICSVReader2 * pCSVReader, const char* szFileName )
{
	return false;
}

const std::set<int>& CSchemeRobotConfig::GetIDS()
{
	return m_SetInt;
}

void* CSchemeRobotConfig::GetScheme(int id)
{
	return NULL;
}
