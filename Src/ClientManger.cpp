#include "stdafx.h"
#include "ClientManger.h"
#include "SchemeRobotConfig.h"
#include "RobotServiceProvider.h"

void CClientManager::Login()
{
	SRobotConfigInfo* pConfig = g_pSchemeRobotConfig->GetRobotConfigInfo();
	for (int i=0; i<pConfig->nRobotCount; i++)
	{
		std::string name = pConfig->szRobotName;
		char szcunt[100];
		itoa(i,szcunt,10);
		name += szcunt;
		CClient* pClient = new CClient(pConfig->szLoginServerIP,pConfig->nLoginServerPort,name,pConfig->szPasswd,pConfig->nZoneID);
		pClient->ConnectLoginServer();
	}
	
	
}
