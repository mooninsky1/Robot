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
#pragma once

#include "DGlobalGame.h"
#include "ISchemeEngine.h"

struct SRobotConfigInfo
{
	char			szLoginServerIP[32];			// 登录服IP
	int				nLoginServerPort;				// 登录服端口
	int				nRobotCount;					// 机器人数量
	char			szRobotName[32];				// 机器人名字
	char			szPasswd[32];					// 密码
	int				nZoneID;						// 登录区服ID
};
// 机器人配置表
#define ROBOTCONFIG_SCHEME_FILENAME		"\\Robot\\RobotConfig.xml"

class CSchemeRobotConfig : public ISchemeUpdateSink
{
public:
	///////////////////////////////ISchemeUpdateSink///////////////////	
	/** CSV配置载入时通知
	@param   pCSVReader：读取CSV的返回接口
	@param   szFileName：配置文件名
	@param   
	@return  
	@note     
	@warning 不要在此方法释放pCSVReader或者pTiXmlDocument,因为一个文件对应多个sink
	@retval buffer 
	*/ 
	virtual bool				OnSchemeLoad(ICSVReader * pCSVReader,const char* szFileName);

	/** XML配置载入时通知
	@param   pTiXmlDocument：读取XML的返回接口
	@param   szFileName：配置文件名
	@param   
	@return  
	@note     
	@warning 不要在此方法释放pCSVReader或者pTiXmlDocument,因为一个文件对应多个sink
	@retval buffer 
	*/
	virtual bool				OnSchemeLoad(TiXmlDocument * pTiXmlDocument,const char* szFileName);

	/** 配置动态更新时通知
	@param   pCSVReader：读取CSV的返回接口
	@param   szFileName：配置文件名
	@param   
	@return  
	@note     
	@warning 不要在此方法释放pCSVReader或者pTiXmlDocument,因为一个文件对应多个sink
	@retval buffer 
	*/
	virtual bool				OnSchemeUpdate(ICSVReader * pCSVReader, const char* szFileName);

	/** 配置动态更新时通知
	@param   pTiXmlDocument：读取XML的返回接口
	@param   szFileName：配置文件名
	@param   
	@return  
	@note     
	@warning 不要在此方法释放pCSVReader或者pTiXmlDocument,因为一个文件对应多个sink
	@retval buffer 
	*/
	virtual bool				OnSchemeUpdate(TiXmlDocument * pTiXmlDocument, const char* szFileName);


	virtual bool				OnSchemeLoad(IBinarySerialize* bianrySerialize, const char* filename)/* = 0*/;

	virtual bool OnSchemeLoad( ICSVReader2 * pCSVReader,const char* szFileName );

	virtual bool				OnSchemeUpdate(IBinarySerialize* bianrySerialize, const char* filename)/* = 0*/;

	virtual bool OnSchemeUpdate( ICSVReader2 * pCSVReader, const char* szFileName );

	///////////////////////////////CSchemeEntity////////////////////////
	/** 载入脚本
	@param   
	@param   
	@return  
	*/
	bool						LoadScheme(void);

	/** 关闭
	@param   
	@param   
	@return  
	*/
	void						Close(void);

	/** 取得场景服相关配置
	@param   
	@param   
	@return  
	*/
	SRobotConfigInfo *		GetRobotConfigInfo(void);

	/** 
	@param   
	@param   
	@return  
	*/
	bool						InputRobotConfigInfo(SRobotConfigInfo * pInfo);

	/** 
	@param   
	@param   
	@return  
	*/
	CSchemeRobotConfig(void);

	/** 
	@param   
	@param   
	@return  
	*/
	virtual ~CSchemeRobotConfig(void);

	virtual const std::set<int>& GetIDS();

	virtual void* GetScheme(int id);

private:
	// 场景服相关配置
	SRobotConfigInfo		m_RobotConfig;
	std::set<int>			m_SetInt;
};

