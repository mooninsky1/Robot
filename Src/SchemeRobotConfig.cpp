/*******************************************************************
** 文件名:	e:\Rocket\Server\ZoneServer\Src\SchemeZoneServer.h
** 版  权:	(C) 
** 创建人:	pdata
** 日  期:	2008/3/4  10:46
** 版  本:	1.0
** 描  述:  场景服配置
** 应  用:  	

**************************** 修改记录 ******************************
** 修改人: 
** 日  期: 
** 描  述: 
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
	// 场景服相关配置
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

	// 加载脚本
	string stringPath = g_ExternalFacade.GetWorkDir();	
	stringPath += ROBOTCONFIG_SCHEME_FILENAME;

	bool bResult = pSchemeEngine->LoadScheme(stringPath.c_str(), (ISchemeUpdateSink *)this, false);
	if(!bResult)
	{
		ErrorLn("加载配置文件失败。文件名 = " << stringPath.c_str());

		return false;
	}	

	g_pSchemeRobotConfig = this;

	return true;
}

/** 关闭
@param   
@param   
@return  
*/
void CSchemeRobotConfig::Close(void)
{	

}

/** CSV配置载入时通知
@param   pCSVReader：读取CSV的返回接口
@param   szFileName：配置文件名
@param   
@return  
@note     
@warning 不要在此方法释放pCSVReader或者pTiXmlDocument,因为一个文件对应多个sink
@retval buffer 
*/ 
bool CSchemeRobotConfig::OnSchemeLoad(ICSVReader * pCSVReader,LPCSTR szFileName)
{
	return false;	
}

/** XML配置载入时通知
@param   pTiXmlDocument：读取XML的返回接口
@param   szFileName：配置文件名
@param   
@return  
@note     
@warning 不要在此方法释放pCSVReader或者pTiXmlDocument,因为一个文件对应多个sink
@retval buffer 
*/
bool CSchemeRobotConfig::OnSchemeLoad(TiXmlDocument * pTiXmlDocument,LPCSTR szFileName)
{
	if(pTiXmlDocument == NULL)
	{
		return false;
	}

	// 场景服相关配置
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

/** 配置动态更新时通知
@param   pCSVReader：读取CSV的返回接口
@param   szFileName：配置文件名
@param   
@return  
@note     
@warning 不要在此方法释放pCSVReader或者pTiXmlDocument,因为一个文件对应多个sink
@retval buffer 
*/
bool CSchemeRobotConfig::OnSchemeUpdate(ICSVReader * pCSVReader, LPCSTR szFileName)
{
	return false;
}

/** 配置动态更新时通知
@param   pTiXmlDocument：读取XML的返回接口
@param   szFileName：配置文件名
@param   
@return  
@note     
@warning 不要在此方法释放pCSVReader或者pTiXmlDocument,因为一个文件对应多个sink
@retval buffer 
*/
bool CSchemeRobotConfig::OnSchemeUpdate(TiXmlDocument * pTiXmlDocument, LPCSTR szFileName)
{
	return false;
}

/** 取得人物属性兑换比率
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

	// 加载脚本
	string stringPath = g_ExternalFacade.GetWorkDir();	
	stringPath += ROBOTCONFIG_SCHEME_FILENAME;

	// 打开配置
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
