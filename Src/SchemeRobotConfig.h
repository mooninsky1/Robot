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
#pragma once

#include "DGlobalGame.h"
#include "ISchemeEngine.h"

struct SRobotConfigInfo
{
	char			szLoginServerIP[32];			// ��¼��IP
	int				nLoginServerPort;				// ��¼���˿�
	int				nRobotCount;					// ����������
	char			szRobotName[32];				// ����������
	char			szPasswd[32];					// ����
	int				nZoneID;						// ��¼����ID
};
// ���������ñ�
#define ROBOTCONFIG_SCHEME_FILENAME		"\\Robot\\RobotConfig.xml"

class CSchemeRobotConfig : public ISchemeUpdateSink
{
public:
	///////////////////////////////ISchemeUpdateSink///////////////////	
	/** CSV��������ʱ֪ͨ
	@param   pCSVReader����ȡCSV�ķ��ؽӿ�
	@param   szFileName�������ļ���
	@param   
	@return  
	@note     
	@warning ��Ҫ�ڴ˷����ͷ�pCSVReader����pTiXmlDocument,��Ϊһ���ļ���Ӧ���sink
	@retval buffer 
	*/ 
	virtual bool				OnSchemeLoad(ICSVReader * pCSVReader,const char* szFileName);

	/** XML��������ʱ֪ͨ
	@param   pTiXmlDocument����ȡXML�ķ��ؽӿ�
	@param   szFileName�������ļ���
	@param   
	@return  
	@note     
	@warning ��Ҫ�ڴ˷����ͷ�pCSVReader����pTiXmlDocument,��Ϊһ���ļ���Ӧ���sink
	@retval buffer 
	*/
	virtual bool				OnSchemeLoad(TiXmlDocument * pTiXmlDocument,const char* szFileName);

	/** ���ö�̬����ʱ֪ͨ
	@param   pCSVReader����ȡCSV�ķ��ؽӿ�
	@param   szFileName�������ļ���
	@param   
	@return  
	@note     
	@warning ��Ҫ�ڴ˷����ͷ�pCSVReader����pTiXmlDocument,��Ϊһ���ļ���Ӧ���sink
	@retval buffer 
	*/
	virtual bool				OnSchemeUpdate(ICSVReader * pCSVReader, const char* szFileName);

	/** ���ö�̬����ʱ֪ͨ
	@param   pTiXmlDocument����ȡXML�ķ��ؽӿ�
	@param   szFileName�������ļ���
	@param   
	@return  
	@note     
	@warning ��Ҫ�ڴ˷����ͷ�pCSVReader����pTiXmlDocument,��Ϊһ���ļ���Ӧ���sink
	@retval buffer 
	*/
	virtual bool				OnSchemeUpdate(TiXmlDocument * pTiXmlDocument, const char* szFileName);


	virtual bool				OnSchemeLoad(IBinarySerialize* bianrySerialize, const char* filename)/* = 0*/;

	virtual bool OnSchemeLoad( ICSVReader2 * pCSVReader,const char* szFileName );

	virtual bool				OnSchemeUpdate(IBinarySerialize* bianrySerialize, const char* filename)/* = 0*/;

	virtual bool OnSchemeUpdate( ICSVReader2 * pCSVReader, const char* szFileName );

	///////////////////////////////CSchemeEntity////////////////////////
	/** ����ű�
	@param   
	@param   
	@return  
	*/
	bool						LoadScheme(void);

	/** �ر�
	@param   
	@param   
	@return  
	*/
	void						Close(void);

	/** ȡ�ó������������
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
	// �������������
	SRobotConfigInfo		m_RobotConfig;
	std::set<int>			m_SetInt;
};

