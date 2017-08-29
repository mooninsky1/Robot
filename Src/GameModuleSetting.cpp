#include "stdafx.h"
#include "GameModuleSetting.h"
#include "..\Src\ExternalFacade.h"
#include "ISchemeCenter.h"
#include "DebugNew.h"

#define REFERENCE_SETTING_SYMBOL(name) m_setting##name

#define FETCH_SETTING_FUN_NAME(name) FetchSetting##name

#define CALL_FETCH_SETTING_FUN(configIndex, name) FetchSetting##name(configIndex, schemeCenter)

#define FETCH_INT32_FIELD(name, field)	{ \
	std::string s; \
	 \
	if (!schemeCenter->GetGameModuleSettingString(configIndex, #field, s)) \
	{ \
		ErrorLn("GameModuleSetting[" << configIndex << "][" << #field << "]无此项") \
	} \
	else \
	{ \
		REFERENCE_SETTING_SYMBOL(name).field = atoi(s.c_str()); \
	} \
}

#define FETCH_STRING_FIELD(name, field) {\
	if (!schemeCenter->GetGameModuleSettingString(configIndex, #field, REFERENCE_SETTING_SYMBOL(name).field)) \
	{ \
	ErrorLn("GameModuleSetting[" << configIndex << "][" << #field << "]无此项") \
	} \
}


#define IMPLEMETN_GET_SETTING(name) SGameModuleSetting##name& CGameModuleSetting::GetSetting##name() \
{ \
	return REFERENCE_SETTING_SYMBOL(name); \
}

void CGameModuleSetting::FetchSetting()
{
	ISchemeCenter* schemeCenter = g_ExternalFacade.GetSchemeCenter();

	// 每个配置加一项
	//////////////////////////////////////////////////////////////////////////
	CALL_FETCH_SETTING_FUN(SCHEME_GAME_MODULE_INDEX_MAP_CLIMB, MapClimb);
	CALL_FETCH_SETTING_FUN(SCHEME_GAME_MODULE_INDEX_FRIEND, Friend);
	CALL_FETCH_SETTING_FUN(SCHEME_GAME_MODULE_INDEX_PLUNDER, Plunder);
	CALL_FETCH_SETTING_FUN(SCHEME_GAME_MODULE_INDEX_BUZHEN, Buzhen);
	CALL_FETCH_SETTING_FUN(SCHEME_GAME_MODULE_INDEX_GodBoss, GodBoss);
	CALL_FETCH_SETTING_FUN(SCHEME_GAME_MODULE_INDEX_WorldBoss, WorldBoss);
	CALL_FETCH_SETTING_FUN(SCHEME_GAME_MODULE_INDEX_CardTrain, CardTrain);
	CALL_FETCH_SETTING_FUN(SCHEME_GAME_MODULE_INDEX_SKILL, Skill);
	CALL_FETCH_SETTING_FUN(SCHEME_GAME_MODULE_INDEX_ARENA, Arena);
	CALL_FETCH_SETTING_FUN(SCHEME_GAME_MODULE_INDEX_TREASURE, Treasure);
	CALL_FETCH_SETTING_FUN(SCHEME_GAME_MODULE_INDEX_ZHAO_CAI, ZhaoCai);
	CALL_FETCH_SETTING_FUN(SCHEME_GAME_MODULE_INDEX_BATTLE_PRIZE_SILVER, BattlePrizeSilver);
	CALL_FETCH_SETTING_FUN(SCHEME_GAME_MODULE_INDEX_MELEE, Melee);
	CALL_FETCH_SETTING_FUN(SCHEME_GAME_MODULE_INDEX_FIGHT_HURT_FACTOR,HurtFactor);//yhf

	CALL_FETCH_SETTING_FUN(SCHEME_GAME_MODULE_INDEX_ROB_CIMELIA, RobCimelia);
	CALL_FETCH_SETTING_FUN(SCHEME_GAME_MODULE_INDEX_PVP_FACTOR, PVPFactor);

	CALL_FETCH_SETTING_FUN(SCHEME_GAME_MODULE_INDEX_RONG_LIAN, RongLian);
	CALL_FETCH_SETTING_FUN(SCHEME_GAME_MODULE_INDEX_FUND, Fund);
	CALL_FETCH_SETTING_FUN(SCHEME_GAME_MODULE_INDEX_FIGHT_FACTOR, FightFactor);
	CALL_FETCH_SETTING_FUN(SCHEME_GAME_MODULE_INDEX_LEVEL, LevelLimit);
	CALL_FETCH_SETTING_FUN(SCHEME_GAME_MODULE_INDEX_SWORD, Sword);
	CALL_FETCH_SETTING_FUN(SCHEME_GAME_MODULE_INDEX_EQUIP, Equip);
	CALL_FETCH_SETTING_FUN(SCHEME_GAME_MODULE_INDEX_WUDAOHUI, Wudaohui);
	CALL_FETCH_SETTING_FUN(SCHEME_GAME_MODULE_INDEX_JUHUN, Juhun);
	CALL_FETCH_SETTING_FUN(SCHEME_GAME_MODULE_INDEX_ONLINE_PRIZE, OnlinePrize);
	CALL_FETCH_SETTING_FUN(SCHEME_GAME_MODULE_INDEX_PVE_PARAM, PveBattleParam);// yhf
	CALL_FETCH_SETTING_FUN(SCHEME_GAME_MODULE_INDEX_SYSTEM, System);//yyk
	CALL_FETCH_SETTING_FUN(SCHEME_GAME_MODULE_INDEX_AOYINUM, AoyiNum);// yhf
	CALL_FETCH_SETTING_FUN(SCHEME_GAME_MODULE_INDEX_CORPS, Corps);// yhf
	CALL_FETCH_SETTING_FUN(SCHEME_GAME_MODULE_INDEX_CORPSRACE, CorpsRace);// yhf
	CALL_FETCH_SETTING_FUN(SCHEME_GAME_MODULE_INDEX_CorpsLilian, CorpsLilian);// yhf
	CALL_FETCH_SETTING_FUN(SCHEME_GAME_MODULE_INDEX_FISH, Fish);// yhf
	CALL_FETCH_SETTING_FUN(SCHEME_GAME_MODULE_INDEX_QUIZ, Quiz); //qinjc
	CALL_FETCH_SETTING_FUN(SCHEME_GAME_MODULE_INDEX_FENG_YIN, FengYin);
	CALL_FETCH_SETTING_FUN(SCHEME_GAME_MODULE_INDEX_DAOYUANWAR, DaoYuanWar);
	CALL_FETCH_SETTING_FUN(SCHEME_GAME_MODULE_INDEX_JINJIE, JinJie);
    CALL_FETCH_SETTING_FUN(SCHEME_GAME_MODULE_INDEX_ACTIVITY_PRAY, ActivityPray);
    CALL_FETCH_SETTING_FUN(SCHEME_GAME_MODULE_INDEX_MYSTERY_SHOP, MysteryShop);
	CALL_FETCH_SETTING_FUN(SCHEME_GAME_MODULE_INDEX_JINJIE, JinJie);
	CALL_FETCH_SETTING_FUN(SCHEME_GAME_MODULE_INDEX_PARTS, Parts);
	CALL_FETCH_SETTING_FUN(SCHEME_GAME_MODULE_INDEX_DAMO, Damo);
	CALL_FETCH_SETTING_FUN(SCHEME_GAME_MODULE_INDEX_CorpsManor, CorpsManor);
	CALL_FETCH_SETTING_FUN(SCHEME_GAME_MODULE_INDEX_WEIXIN_SHARED_REWARD, WeixinShareReward);
	CALL_FETCH_SETTING_FUN(SCHEME_GAME_MODULE_INDEX_ACTIVITY_BOSS, ActivityBoss);
}

// 每个配置加一项
//////////////////////////////////////////////////////////////////////////
void CGameModuleSetting::FETCH_SETTING_FUN_NAME(CorpsManor)(int configIndex, ISchemeCenter* schemeCenter)
{
	FETCH_INT32_FIELD(CorpsManor, openlevel)
	FETCH_INT32_FIELD(CorpsManor, openday)
	FETCH_INT32_FIELD(CorpsManor, opentime)
	FETCH_INT32_FIELD(CorpsManor,closetime)//领地争夺战关闭时间2（当天具体开启时间按秒计算）
	FETCH_INT32_FIELD(CorpsManor,killscore)//杀死一个敌方获得积分
	FETCH_INT32_FIELD(CorpsManor,keeptime)//多少时间获得积分
	FETCH_INT32_FIELD(CorpsManor,manor1score)//获得积分
	FETCH_INT32_FIELD(CorpsManor,manor2score)//获得积分
	FETCH_INT32_FIELD(CorpsManor,manor3score)//获得积分
	FETCH_INT32_FIELD(CorpsManor,manor4score)//获得积分
	FETCH_INT32_FIELD(CorpsManor,manor5score)//获得积分
	FETCH_INT32_FIELD(CorpsManor,relifetime)//复活时间（s）
	FETCH_INT32_FIELD(CorpsManor,protectiontime)//保护时间（s）
	FETCH_INT32_FIELD(CorpsManor,signtime)//领地争夺战报名时间（当天具体开启时间按秒计算）
	FETCH_INT32_FIELD(CorpsManor,addpercent)//鼓舞加成（万分比）
	FETCH_INT32_FIELD(CorpsManor,endtime)//领地争夺战报名时间（当天具体开启时间按秒计算）
	FETCH_INT32_FIELD(CorpsManor,rewardtime)
}
void CGameModuleSetting::FETCH_SETTING_FUN_NAME(MapClimb)(int configIndex, ISchemeCenter* schemeCenter)
{
	FETCH_INT32_FIELD(MapClimb, manualResetTimes)
	FETCH_INT32_FIELD(MapClimb, challengeTimes)
	FETCH_INT32_FIELD(MapClimb, resetTime)
	FETCH_INT32_FIELD(MapClimb, sweepCD)
	FETCH_INT32_FIELD(MapClimb, prestigeReward)
	FETCH_INT32_FIELD(MapClimb, coinReward)
    FETCH_INT32_FIELD(MapClimb, Resetexpend2);
    FETCH_INT32_FIELD(MapClimb, Resetexpend3);
    FETCH_INT32_FIELD(MapClimb, openlevel);
    FETCH_INT32_FIELD(MapClimb, openbox1);
    FETCH_INT32_FIELD(MapClimb, openbox2);
    FETCH_INT32_FIELD(MapClimb, zhouyinReward);
    FETCH_INT32_FIELD(MapClimb, happennum);
    FETCH_INT32_FIELD(MapClimb, eachhappennum);
    FETCH_INT32_FIELD(MapClimb, answerright);
    FETCH_INT32_FIELD(MapClimb, answerwrong);
    FETCH_INT32_FIELD(MapClimb, livetime);

}
void CGameModuleSetting::FETCH_SETTING_FUN_NAME(Juhun)(int configIndex, ISchemeCenter* schemeCenter)
{
	FETCH_INT32_FIELD(Juhun, rafflefactor)
	FETCH_INT32_FIELD(Juhun, newactor)
	FETCH_INT32_FIELD(Juhun, rafflefactor1)
}

void CGameModuleSetting::FETCH_SETTING_FUN_NAME(Friend)(int configIndex, ISchemeCenter* schemeCenter)
{
	FETCH_INT32_FIELD(Friend, maxFriendCount)
	FETCH_INT32_FIELD(Friend, maxInviterCount)
	FETCH_INT32_FIELD(Friend, maxReceivePhysicalCount)
	FETCH_INT32_FIELD(Friend, receivePhysicalCountPerTimes)

}

void CGameModuleSetting::FETCH_SETTING_FUN_NAME(Plunder)(int configIndex, ISchemeCenter* schemeCenter)
{
	FETCH_INT32_FIELD(Plunder, maxPracticeTimes)
	FETCH_INT32_FIELD(Plunder, resetTime)
	FETCH_INT32_FIELD(Plunder, maxShowPracticeCount)
	FETCH_INT32_FIELD(Plunder, maxRefreshTimes)
	FETCH_INT32_FIELD(Plunder, maxPlunderTimes)
	FETCH_INT32_FIELD(Plunder, protectLevelRange)
	FETCH_INT32_FIELD(Plunder, maxBePlunderedTimes)
	FETCH_INT32_FIELD(Plunder, maxProtectTimes)
	FETCH_INT32_FIELD(Plunder, protecterGain)
	FETCH_INT32_FIELD(Plunder, mapid)
	FETCH_INT32_FIELD(Plunder, openlevel)
	FETCH_INT32_FIELD(Plunder, doubleRewardOpen1)
	FETCH_INT32_FIELD(Plunder, doubleRewardClose1)
	FETCH_INT32_FIELD(Plunder, doubleRewardOpen2)
	FETCH_INT32_FIELD(Plunder, doubleRewardClose2)
	FETCH_INT32_FIELD(Plunder, listlevel)
	FETCH_INT32_FIELD(Plunder, listlength)
	FETCH_INT32_FIELD(Plunder, minPlundered)
}

void CGameModuleSetting::FETCH_SETTING_FUN_NAME(Buzhen)(int configIndex, ISchemeCenter* schemeCenter) //布阵 yhf
{
// 	FETCH_INT32_FIELD(Buzhen, tibu1)
// 	FETCH_INT32_FIELD(Buzhen, tibu2)
// 	FETCH_INT32_FIELD(Buzhen, tibu3)
// 	FETCH_INT32_FIELD(Buzhen, tibu4)
// 	FETCH_INT32_FIELD(Buzhen, qixinggong1)
// 	FETCH_INT32_FIELD(Buzhen, qixinggong2)
// 	FETCH_INT32_FIELD(Buzhen, qixinggong3)
// 	FETCH_INT32_FIELD(Buzhen, qixinggong4)
// 	FETCH_INT32_FIELD(Buzhen, qixinggong5)
// 	FETCH_INT32_FIELD(Buzhen, qixinggong6)
// 	FETCH_INT32_FIELD(Buzhen, qixinggong7)

}
void CGameModuleSetting::FETCH_SETTING_FUN_NAME(Skill)(int configIndex, ISchemeCenter* schemeCenter) //布阵 yhf
{
	FETCH_INT32_FIELD(Skill, openlevel)
}
void CGameModuleSetting::FETCH_SETTING_FUN_NAME(GodBoss)(int configIndex, ISchemeCenter* schemeCenter) //布阵 yhf
{
	FETCH_INT32_FIELD(GodBoss, commonattackconsume)
	FETCH_INT32_FIELD(GodBoss, powerattackconsume)
	FETCH_INT32_FIELD(GodBoss, powerattackopen)
	FETCH_INT32_FIELD(GodBoss, powerattackclose)
	FETCH_INT32_FIELD(GodBoss, doublefeatsopen)
	FETCH_INT32_FIELD(GodBoss, doublefeatsclose)
	FETCH_INT32_FIELD(GodBoss, bossprobability)
	FETCH_INT32_FIELD(GodBoss, joinbosslevel)
	FETCH_INT32_FIELD(GodBoss, CrusadeUP)
	FETCH_INT32_FIELD(GodBoss, Crusaderecover)
	FETCH_INT32_FIELD(GodBoss, featsfactor)
	FETCH_INT32_FIELD(GodBoss, damagefactor)
	FETCH_INT32_FIELD(GodBoss, id)					  //征讨令id
	FETCH_INT32_FIELD(GodBoss, mapid)					//地图id
	FETCH_INT32_FIELD(GodBoss, acttackfactor1)			//上阵1号位置攻击系数万分比
	FETCH_INT32_FIELD(GodBoss, acttackfactor2)			//上阵2号位置攻击系数万分比
	FETCH_INT32_FIELD(GodBoss, acttackfactor3)			//上阵3号位置攻击系数万分比
	FETCH_INT32_FIELD(GodBoss, acttackfactor4)			//上阵4号位置攻击系数万分比
	FETCH_INT32_FIELD(GodBoss, acttackfactor5)			//替补1号攻击系数万分比
	FETCH_INT32_FIELD(GodBoss, acttackfactor6)			//替补2号攻击系数万分比
	FETCH_INT32_FIELD(GodBoss, acttackfactor7)			//替补3号攻击系数万分比
	FETCH_INT32_FIELD(GodBoss, acttackfactor8)			//替补4号攻击系数万分比
	FETCH_INT32_FIELD(GodBoss, herofactor1)			//平衡型攻击系数万分比
	FETCH_INT32_FIELD(GodBoss, herofactor2)			//辅助型攻击系数万分比
	FETCH_INT32_FIELD(GodBoss, herofactor3)			//防御型攻击系数万分比
	FETCH_INT32_FIELD(GodBoss, herofactor4)			//攻击型攻击系数万分比
}
void CGameModuleSetting::FETCH_SETTING_FUN_NAME(WorldBoss)(int configIndex, ISchemeCenter* schemeCenter) 
{
	FETCH_INT32_FIELD(WorldBoss, openlevel)
	FETCH_INT32_FIELD(WorldBoss, dekaroncountdown)
	FETCH_INT32_FIELD(WorldBoss, addition)
	FETCH_INT32_FIELD(WorldBoss, acttackfactor1)
	FETCH_INT32_FIELD(WorldBoss, acttackfactor2)
	FETCH_INT32_FIELD(WorldBoss, acttackfactor3)
	FETCH_INT32_FIELD(WorldBoss, acttackfactor4)
	FETCH_INT32_FIELD(WorldBoss, acttackfactor5)
	FETCH_INT32_FIELD(WorldBoss, acttackfactor6)
	FETCH_INT32_FIELD(WorldBoss, acttackfactor7)
	FETCH_INT32_FIELD(WorldBoss, acttackfactor8)
	FETCH_INT32_FIELD(WorldBoss, herofactor1)
	FETCH_INT32_FIELD(WorldBoss, herofactor2)
	FETCH_INT32_FIELD(WorldBoss, herofactor3)
	FETCH_INT32_FIELD(WorldBoss, herofactor4)
}


void CGameModuleSetting::FETCH_SETTING_FUN_NAME(Wudaohui)(int configIndex, ISchemeCenter* schemeCenter) //武道会 yhf
{
	FETCH_INT32_FIELD(Wudaohui, openlevel)
	FETCH_INT32_FIELD(Wudaohui, wudaoopen)
	FETCH_INT32_FIELD(Wudaohui, wudaoclose)
	FETCH_INT32_FIELD(Wudaohui, weeklywarday)
	FETCH_INT32_FIELD(Wudaohui, V1winreward)
	FETCH_INT32_FIELD(Wudaohui, V1failreward)
	FETCH_INT32_FIELD(Wudaohui, V3winreward)
	FETCH_INT32_FIELD(Wudaohui, V3failreward)
	FETCH_INT32_FIELD(Wudaohui, Challengetimes)
	FETCH_INT32_FIELD(Wudaohui, doubleRewardOpen1)
	FETCH_INT32_FIELD(Wudaohui, doubleRewardClose1)
	FETCH_INT32_FIELD(Wudaohui, doubleRewardOpen2)
	FETCH_INT32_FIELD(Wudaohui, doubleRewardClose2)

	FETCH_INT32_FIELD(Wudaohui, Invitetimes)
	FETCH_INT32_FIELD(Wudaohui, PerfightJinglicost)
	FETCH_INT32_FIELD(Wudaohui, Levelupfightnum)
	FETCH_INT32_FIELD(Wudaohui, Levelupsuccessnum)
	FETCH_INT32_FIELD(Wudaohui, Levelupfailpoints)
	FETCH_INT32_FIELD(Wudaohui, Totalfightwinawardnum)
	FETCH_INT32_FIELD(Wudaohui, Perfightwinawardnum)
	FETCH_INT32_FIELD(Wudaohui, Dayrewardtime)
	FETCH_INT32_FIELD(Wudaohui, Monthrewardtime)
	FETCH_INT32_FIELD(Wudaohui, Clearallpointstime)
	FETCH_INT32_FIELD(Wudaohui, Leveldownfightnum)
	FETCH_INT32_FIELD(Wudaohui, Fightwithrobottime)
}

void CGameModuleSetting::FETCH_SETTING_FUN_NAME(AoyiNum)(int configIndex, ISchemeCenter* schemeCenter) //奥义恢复 yhf
{
	FETCH_INT32_FIELD(AoyiNum, aoyinum)
	FETCH_INT32_FIELD(AoyiNum, AoyiPublicCD) //奥义公共CD
	FETCH_INT32_FIELD(AoyiNum, BishaPublicCD) //必杀公共CD
}

void CGameModuleSetting::FETCH_SETTING_FUN_NAME(CardTrain)(int configIndex, ISchemeCenter* schemeCenter) //布阵 yhf
{
	FETCH_INT32_FIELD(CardTrain, basicvalue)
	FETCH_INT32_FIELD(CardTrain, hpfactor)
	FETCH_INT32_FIELD(CardTrain, attackfactor)
	FETCH_INT32_FIELD(CardTrain, defensefactor)
	FETCH_INT32_FIELD(CardTrain, hurtsubfactor)
	FETCH_INT32_FIELD(CardTrain, openlevel)
	FETCH_INT32_FIELD(CardTrain, minfactor)
	FETCH_INT32_FIELD(CardTrain, numberFactor)
}



void CGameModuleSetting::FETCH_SETTING_FUN_NAME(Arena)(int configIndex, ISchemeCenter* schemeCenter) //竞技场 yhf
{
	FETCH_INT32_FIELD(Arena,openlevel);	//开放等级
	FETCH_INT32_FIELD(Arena,prizetime);	//每日开奖时间
	//FETCH_INT32_FIELD(Arena,freetimes);	//每日免费次数
	FETCH_INT32_FIELD(Arena,resettime);	//每日重置时间
	FETCH_INT32_FIELD(Arena,cdtime);	//冷却时间 分钟
	FETCH_INT32_FIELD(Arena, consumeEnergy);//每次战斗消耗的精力值
	FETCH_INT32_FIELD(Arena, maxrecord);//最大对战记录条数
	FETCH_INT32_FIELD(Arena, prestigeFactor1);//战胜的声望奖励
	FETCH_INT32_FIELD(Arena, prestigeFactor2);//战胜的声望奖励
}

void CGameModuleSetting::FETCH_SETTING_FUN_NAME(Treasure)(int configIndex, ISchemeCenter* schemeCenter)
{
	FETCH_INT32_FIELD(Treasure, openTimes10MinVipLevel)
}

void CGameModuleSetting::FETCH_SETTING_FUN_NAME(ZhaoCai)(int configIndex, ISchemeCenter* schemeCenter)
{
	FETCH_INT32_FIELD(ZhaoCai, silverBase1)
	FETCH_INT32_FIELD(ZhaoCai, silverParam1)
	FETCH_INT32_FIELD(ZhaoCai, silverParam2)
	FETCH_INT32_FIELD(ZhaoCai, goldGrowFactor1)
	FETCH_INT32_FIELD(ZhaoCai, goldGrowFactor2)
	FETCH_INT32_FIELD(ZhaoCai, goldMaxRequired)
	FETCH_INT32_FIELD(ZhaoCai, goldRequired)
	FETCH_INT32_FIELD(ZhaoCai, openlevel)
}

void CGameModuleSetting::FETCH_SETTING_FUN_NAME(BattlePrizeSilver)(int configIndex, ISchemeCenter* schemeCenter)
{
	FETCH_INT32_FIELD(BattlePrizeSilver, gameMoneyFactor1)
	FETCH_INT32_FIELD(BattlePrizeSilver, gameMoneyFactor2)
}

void CGameModuleSetting::FETCH_SETTING_FUN_NAME(Melee)(int configIndex, ISchemeCenter* schemeCenter)
{
	FETCH_INT32_FIELD(Melee, equalLevelPro)
	FETCH_INT32_FIELD(Melee, downLevelPro)
	FETCH_INT32_FIELD(Melee, upLevelPro)
	FETCH_INT32_FIELD(Melee, consumeEnergy)
	FETCH_INT32_FIELD(Melee, meleeVictoryHonour)
	FETCH_INT32_FIELD(Melee, meleeFailureHonour)
	FETCH_INT32_FIELD(Melee, meleeVictoryScore)
	FETCH_INT32_FIELD(Melee, meleeFailureScore)
}


void CGameModuleSetting::FETCH_SETTING_FUN_NAME(RobCimelia)(int configIndex, ISchemeCenter* schemeCenter)
{
	FETCH_INT32_FIELD(RobCimelia, lootLevelRequired)
	FETCH_INT32_FIELD(RobCimelia, lootConsumeEnergy)
	FETCH_INT32_FIELD(RobCimelia, mapid)
	FETCH_INT32_FIELD(RobCimelia, newerid)
	FETCH_INT32_FIELD(RobCimelia, continuefightlevel)
	FETCH_INT32_FIELD(RobCimelia, vipneedlevel)
}

void CGameModuleSetting::FETCH_SETTING_FUN_NAME(PVPFactor)(int configIndex, ISchemeCenter* schemeCenter)
{
	FETCH_INT32_FIELD(PVPFactor, pvpFactor)
}


void CGameModuleSetting::FETCH_SETTING_FUN_NAME(RongLian)(int configIndex, ISchemeCenter* schemeCenter)
{
	FETCH_INT32_FIELD(RongLian, heroRebirth)
		FETCH_INT32_FIELD(RongLian, cimeliaRebirth)
}

void CGameModuleSetting::FETCH_SETTING_FUN_NAME(Fund)(int configIndex, ISchemeCenter* schemeCenter)
{
	FETCH_INT32_FIELD(Fund, vipLevelReq)
		FETCH_INT32_FIELD(Fund, goldCost)
}

void CGameModuleSetting::FETCH_SETTING_FUN_NAME(FightFactor)(int configIndex, ISchemeCenter* schemeCenter)
{
	FETCH_INT32_FIELD(FightFactor, factor1)
	FETCH_INT32_FIELD(FightFactor, factor2)
	FETCH_INT32_FIELD(FightFactor, factor3)
	FETCH_INT32_FIELD(FightFactor, factor4)
	FETCH_INT32_FIELD(FightFactor, factor5)
	FETCH_INT32_FIELD(FightFactor, factor6)
	FETCH_INT32_FIELD(FightFactor, factor7)
	FETCH_INT32_FIELD(FightFactor, factor8)
}

void CGameModuleSetting::FETCH_SETTING_FUN_NAME(HurtFactor)(int configIndex, ISchemeCenter* schemeCenter)
{
	FETCH_INT32_FIELD(HurtFactor, fightFactor1)
	FETCH_INT32_FIELD(HurtFactor, fightFactor2)
	FETCH_INT32_FIELD(HurtFactor, fightFactor3)
	FETCH_INT32_FIELD(HurtFactor, fightFactor4)
	FETCH_INT32_FIELD(HurtFactor, fightFactor5)
	FETCH_INT32_FIELD(HurtFactor, fightFactor6)
	FETCH_INT32_FIELD(HurtFactor, fightFactor7)
	FETCH_INT32_FIELD(HurtFactor, fightFactor8)
}

void CGameModuleSetting::FETCH_SETTING_FUN_NAME(PveBattleParam)(int configIndex, ISchemeCenter* schemeCenter)
{
	FETCH_INT32_FIELD(PveBattleParam,factor1)//系数1
	FETCH_INT32_FIELD(PveBattleParam,gongjifactor1)//攻击系数1
	FETCH_INT32_FIELD(PveBattleParam,fangyufactor1)//防御系数1
	FETCH_INT32_FIELD(PveBattleParam,mingzhongfactor1)//命中系数1
	FETCH_INT32_FIELD(PveBattleParam,baojifactor1)//暴击系数1
	FETCH_INT32_FIELD(PveBattleParam,shanbifactor1)//闪避系数1
	FETCH_INT32_FIELD(PveBattleParam,gedangfactor1)//格挡系数1
	FETCH_INT32_FIELD(PveBattleParam,factor2)//系数2
	FETCH_INT32_FIELD(PveBattleParam,gongjifactor2)//攻击系数2
	FETCH_INT32_FIELD(PveBattleParam,fangyufactor2)//防御系数2
	FETCH_INT32_FIELD(PveBattleParam,mingzhongfactor2)//命中系数2
	FETCH_INT32_FIELD(PveBattleParam,baojifactor2)//暴击系数2
	FETCH_INT32_FIELD(PveBattleParam,shanbifactor2)//闪避系数2
	FETCH_INT32_FIELD(PveBattleParam,gedangfactor2)//格挡系数2
	FETCH_INT32_FIELD(PveBattleParam,factor3)//系数3
	FETCH_INT32_FIELD(PveBattleParam,gongjifactor3)//攻击系数3
	FETCH_INT32_FIELD(PveBattleParam,fangyufactor3)//防御系数3
	FETCH_INT32_FIELD(PveBattleParam,mingzhongfactor3)//命中系数3
	FETCH_INT32_FIELD(PveBattleParam,baojifactor3)//暴击系数3
	FETCH_INT32_FIELD(PveBattleParam,shanbifactor3)//闪避系数3
	FETCH_INT32_FIELD(PveBattleParam,gedangfactor3)//格挡系数3
	FETCH_INT32_FIELD(PveBattleParam,gongjifactor4)//攻击系数4
	FETCH_INT32_FIELD(PveBattleParam,fangyufactor4)//防御系数4
	FETCH_INT32_FIELD(PveBattleParam,mingzhongfactor4)//命中系数4
	FETCH_INT32_FIELD(PveBattleParam,baojifactor4)//暴击系数4
	FETCH_INT32_FIELD(PveBattleParam,shanbifactor4)//闪避系数4
	FETCH_INT32_FIELD(PveBattleParam,gedangfactor4)//格挡系数4",
}

void CGameModuleSetting::FETCH_SETTING_FUN_NAME(LevelLimit)(int configIndex, ISchemeCenter* schemeCenter)
{
	FETCH_INT32_FIELD(LevelLimit, teamMaxLevel)
	FETCH_INT32_FIELD(LevelLimit, heroMaxLevel)
	FETCH_INT32_FIELD(LevelLimit, skillMaxLevel)
	FETCH_INT32_FIELD(LevelLimit, tupoMaxLevel)
	FETCH_INT32_FIELD(LevelLimit, equipintensifyMaxLevel)
	FETCH_INT32_FIELD(LevelLimit, equipmentconciseMaxLevel)
	FETCH_INT32_FIELD(LevelLimit, baowuintensifyMaxLevel)
	FETCH_INT32_FIELD(LevelLimit, baowuconciseMaxLevel)
	FETCH_INT32_FIELD(LevelLimit, equipintensifyFactor)
}

void CGameModuleSetting::FETCH_SETTING_FUN_NAME(Sword)(int configIndex, ISchemeCenter* schemeCenter)
{
	FETCH_INT32_FIELD(Sword, swordFactor)
	FETCH_INT32_FIELD(Sword, openlevel)
}

void CGameModuleSetting::FETCH_SETTING_FUN_NAME(Equip)(int configIndex, ISchemeCenter* schemeCenter)
{
	FETCH_INT32_FIELD(Equip, equipmentopenlevel)
	FETCH_INT32_FIELD(Equip, equipmentconopenlevel)
	FETCH_INT32_FIELD(Equip, cimeliaopenlevel)
	FETCH_INT32_FIELD(Equip, cimeliaconopenlevel)
}

void CGameModuleSetting::FETCH_SETTING_FUN_NAME(OnlinePrize)(int configIndex, ISchemeCenter* schemeCenter)
{
	FETCH_INT32_FIELD(OnlinePrize, openlevel)
}

void CGameModuleSetting::FETCH_SETTING_FUN_NAME(System)(int configIndex, ISchemeCenter* schemeCenter)
{
	FETCH_STRING_FIELD(System, dataEyeUrl)	// dataEye日志发送地址
	FETCH_STRING_FIELD(System, innerLogUrl)	// 内部日志系统发送地址
};

void CGameModuleSetting::FETCH_SETTING_FUN_NAME(Corps)(int configIndex, ISchemeCenter* schemeCenter)
{
	FETCH_INT32_FIELD(Corps, teamLevelNeed)	
	FETCH_INT32_FIELD(Corps, teamCost)
	FETCH_INT32_FIELD(Corps, teammapfree)//每日免费挑战军团副本次数
	FETCH_INT32_FIELD(Corps, teammapopentime)//每日军团副本开始时间（分钟）
	FETCH_INT32_FIELD(Corps, teammapclosetime)//每日军团副本结束时间（分钟）
	FETCH_INT32_FIELD(Corps, teammapbuy)//每日可购买军团挑战次数
	FETCH_INT32_FIELD(Corps, factor)//伤害兑换贡献系数（伤害/系数）
	FETCH_INT32_FIELD(Corps, teammapsetgoalopentime)//军团副本制定目标开始时间（分钟）
	FETCH_INT32_FIELD(Corps, teammapsetgoalclosetime)//军团副本制定目标结束时间（分钟）
	FETCH_INT32_FIELD(Corps, teammapclearDay)//军团副本进度清空天数（多少天后）
	FETCH_INT32_FIELD(Corps, teammapcleartime)//军团副本进度清空时间（多少天后第几分钟）
	FETCH_INT32_FIELD(Corps, acttackfactor1)//上阵1号位置攻击系数万分比
	FETCH_INT32_FIELD(Corps, acttackfactor2)//上阵2号位置攻击系数万分比
	FETCH_INT32_FIELD(Corps, acttackfactor3)//上阵3号位置攻击系数万分比
	FETCH_INT32_FIELD(Corps, acttackfactor4)//上阵4号位置攻击系数万分比
	FETCH_INT32_FIELD(Corps, acttackfactor5)//替补1号攻击系数万分比
	FETCH_INT32_FIELD(Corps, acttackfactor6)//替补2号攻击系数万分比
	FETCH_INT32_FIELD(Corps, acttackfactor7)//替补3号攻击系数万分比
	FETCH_INT32_FIELD(Corps, acttackfactor8)//替补4号攻击系数万分比
	FETCH_INT32_FIELD(Corps, herofactor1)//平衡型攻击系数万分比
	FETCH_INT32_FIELD(Corps, herofactor2)//辅助型攻击系数万分比
	FETCH_INT32_FIELD(Corps, herofactor3)//防御型攻击系数万分比
	FETCH_INT32_FIELD(Corps, herofactor4)//攻击型攻击系数万分比
};
void CGameModuleSetting::FETCH_SETTING_FUN_NAME(CorpsLilian)(int configIndex, ISchemeCenter* schemeCenter)
{
	FETCH_INT32_FIELD(CorpsLilian, occupypay1)
	FETCH_INT32_FIELD(CorpsLilian, goldoccupypay1)
	FETCH_INT32_FIELD(CorpsLilian, occupypay2)
	FETCH_INT32_FIELD(CorpsLilian, goldoccupypay2)
	FETCH_INT32_FIELD(CorpsLilian, roomopenlevel)
	FETCH_INT32_FIELD(CorpsLilian, roomtime1)
	FETCH_INT32_FIELD(CorpsLilian, roomtime2)
	FETCH_INT32_FIELD(CorpsLilian, roomadd1)
	FETCH_INT32_FIELD(CorpsLilian, roomadd2)
	FETCH_INT32_FIELD(CorpsLilian, roomadd3)
	FETCH_INT32_FIELD(CorpsLilian, roomadd4)
	FETCH_INT32_FIELD(CorpsLilian, initialnum1)
	FETCH_INT32_FIELD(CorpsLilian, initialnum2)
	FETCH_INT32_FIELD(CorpsLilian, extracost)
	FETCH_INT32_FIELD(CorpsLilian, extracosttimel)
	FETCH_INT32_FIELD(CorpsLilian, extracosttime2)
	FETCH_INT32_FIELD(CorpsLilian, extracosttime3)
	FETCH_INT32_FIELD(CorpsLilian, extracosttime4)
}
void CGameModuleSetting::FETCH_SETTING_FUN_NAME(CorpsRace)(int configIndex, ISchemeCenter* schemeCenter)
{
		FETCH_INT32_FIELD(CorpsRace, teamwaropenlv)	//军团参加军团战最低等级
		FETCH_INT32_FIELD(CorpsRace, teamwarentertime1)//军团战报名开启时间（周一，360分
		FETCH_INT32_FIELD(CorpsRace, teamwarentertime2)//军团战报名结束时间（周二，1439分）
		FETCH_INT32_FIELD(CorpsRace, teamwareditopentime1)//军团16进8战驻防编辑开启时间（周三，1分）
		FETCH_INT32_FIELD(CorpsRace, teamwareditclosetime1)//军团战16进8驻防编辑结束时间（周四，1199分）
		FETCH_INT32_FIELD(CorpsRace, teamwaropentime1)//军团战16进8开启时间（周四，1200分）
		FETCH_INT32_FIELD(CorpsRace, teamwarclosetime1)//军团战16进结束8时间（周五，299分）
		FETCH_INT32_FIELD(CorpsRace, teamwareditopenttime2)//军团战8进4驻防编辑开启时间（周五，300分）
		FETCH_INT32_FIELD(CorpsRace, teamwareditclosetime2)//军团战8进4驻防编辑结束时间（周五，1199分）
		FETCH_INT32_FIELD(CorpsRace, teamwaropentime2)//军团战8进4开启时间（周五，1200分）
		FETCH_INT32_FIELD(CorpsRace, teamwarclosetime2)//军团战8进4结束时间（周六，299分）
		FETCH_INT32_FIELD(CorpsRace, teamwareditopenttime3)//军团战4进2驻防编辑开启时间（周六，300分）
		FETCH_INT32_FIELD(CorpsRace, teamwareditclosetime3)//军团战4进2驻防编辑结束时间（周六，1199分）
		FETCH_INT32_FIELD(CorpsRace, teamwaropentime3)//军团战4进2开启时间（周六，1200分）
		FETCH_INT32_FIELD(CorpsRace, teamwarclosetime3)//军团战4进2结束时间（周日，299分）
		FETCH_INT32_FIELD(CorpsRace, teamwareditopenttime4)//军团战2进1驻防编辑开启时间（周日，300分）
		FETCH_INT32_FIELD(CorpsRace, teamwareditclosetime4)//军团战2进1驻防编辑结束时间（周日，1199分）
		FETCH_INT32_FIELD(CorpsRace, teamwaropentime4)//军团战2进1开启时间（周日，1200分）
		FETCH_INT32_FIELD(CorpsRace, teamwarclosetime4)//军团战2进1结束时间（周一，299分）
		FETCH_INT32_FIELD(CorpsRace, teamwarfactor1)//每次鼓舞增加战斗力系数（万分比）
		FETCH_INT32_FIELD(CorpsRace, teamwarfactor2)//最大鼓舞的次数
		FETCH_INT32_FIELD(CorpsRace, attackfactor1)//系数1万分比
		FETCH_INT32_FIELD(CorpsRace, attackfactor2)//系数2万分比
	
};


void CGameModuleSetting::FETCH_SETTING_FUN_NAME(Fish)(int configIndex, ISchemeCenter* schemeCenter)
{
	FETCH_INT32_FIELD(Fish, openlevel)
};

void CGameModuleSetting::FETCH_SETTING_FUN_NAME(Quiz)(int configIndex, ISchemeCenter* schemeCenter)
{
	FETCH_INT32_FIELD(Quiz, opentime)	
	FETCH_INT32_FIELD(Quiz, closetime)
	FETCH_INT32_FIELD(Quiz, openlevel)	
	FETCH_INT32_FIELD(Quiz, QuestionNum)
	FETCH_INT32_FIELD(Quiz, readtime)	
	FETCH_INT32_FIELD(Quiz, answertime)
	FETCH_INT32_FIELD(Quiz, judgetime)	
	FETCH_INT32_FIELD(Quiz, countspace)
	FETCH_INT32_FIELD(Quiz, questionopen)
    FETCH_INT32_FIELD(Quiz, silverfactor)
};
void CGameModuleSetting::FETCH_SETTING_FUN_NAME(DaoYuanWar)(int configIndex, ISchemeCenter* schemeCenter)
{
	FETCH_INT32_FIELD(DaoYuanWar, openlevel)	
	FETCH_INT32_FIELD(DaoYuanWar, firstCoin)
}
void CGameModuleSetting::FETCH_SETTING_FUN_NAME(FengYin)(int configIndex, ISchemeCenter* schemeCenter)
{
	FETCH_INT32_FIELD(FengYin, patrolVipLv1)	
	FETCH_INT32_FIELD(FengYin, patrolVipLv2)
	FETCH_INT32_FIELD(FengYin, patrolVipLv3)	
	FETCH_INT32_FIELD(FengYin, patrolTime1)
	FETCH_INT32_FIELD(FengYin, patrolTime2)	
	FETCH_INT32_FIELD(FengYin, patrolTime3)
	FETCH_INT32_FIELD(FengYin, patrolEnergy1)	
	FETCH_INT32_FIELD(FengYin, patrolEnergy2)
	FETCH_INT32_FIELD(FengYin, patrolEnergy3)
	FETCH_INT32_FIELD(FengYin, patrolMoney1)
	FETCH_INT32_FIELD(FengYin, patrolMoney2)
	FETCH_INT32_FIELD(FengYin, patrolMoney3)
	FETCH_INT32_FIELD(FengYin, riotPro1)
	FETCH_INT32_FIELD(FengYin, riotPro2)
	FETCH_INT32_FIELD(FengYin, riotPro3)
};

void CGameModuleSetting::FETCH_SETTING_FUN_NAME(ActivityPray)(int configIndex, ISchemeCenter* schemeCenter)
{
    FETCH_INT32_FIELD(ActivityPray, PrayValue)	
    FETCH_INT32_FIELD(ActivityPray, MaxPrayTimes)	
}

void CGameModuleSetting::FETCH_SETTING_FUN_NAME(MysteryShop)(int configIndex, ISchemeCenter* schemeCenter)
{
    FETCH_INT32_FIELD(MysteryShop, opentimespent)	
    FETCH_INT32_FIELD(MysteryShop, probability)
    FETCH_INT32_FIELD(MysteryShop, joinlevel)	
}

void CGameModuleSetting::FETCH_SETTING_FUN_NAME(JinJie)(int configIndex, ISchemeCenter* schemeCenter)
{
	FETCH_INT32_FIELD(JinJie, openlevel)	
	FETCH_INT32_FIELD(JinJie, coinopenlevel)
}

void CGameModuleSetting::FETCH_SETTING_FUN_NAME(Parts)(int configIndex, ISchemeCenter* schemeCenter)
{
	FETCH_INT32_FIELD(Parts, openlevel)
	FETCH_INT32_FIELD(Parts, awakengrow1)
	FETCH_INT32_FIELD(Parts, awakengrow2)
	FETCH_INT32_FIELD(Parts, awakengrow3)
	FETCH_INT32_FIELD(Parts, awakengrow4)
	FETCH_INT32_FIELD(Parts, awakengrow5)	
}
void CGameModuleSetting::FETCH_SETTING_FUN_NAME(Damo)(int configIndex, ISchemeCenter* schemeCenter)
{
		FETCH_INT32_FIELD(Damo, openlevel)
		FETCH_INT32_FIELD(Damo, silverdCost)
		FETCH_INT32_FIELD(Damo, AddItem)
		FETCH_INT32_FIELD(Damo, ExpRate)
		FETCH_INT32_FIELD(Damo, SilverCostcount)
		FETCH_INT32_FIELD(Damo, damohuiguanId)
		FETCH_INT32_FIELD(Damo, Silverlootid)
		FETCH_INT32_FIELD(Damo, GoldCost)
		FETCH_INT32_FIELD(Damo, Goldlootid)
		FETCH_INT32_FIELD(Damo, AddItemFirst)
}

void CGameModuleSetting::FETCH_SETTING_FUN_NAME(WeixinShareReward)(int configIndex, ISchemeCenter* schemeCenter)
{
	FETCH_INT32_FIELD(WeixinShareReward, openlevel)
	FETCH_INT32_FIELD(WeixinShareReward, goldaward)
}



void CGameModuleSetting::FETCH_SETTING_FUN_NAME(ActivityBoss)(int configIndex, ISchemeCenter* schemeCenter)
{
		FETCH_INT32_FIELD(ActivityBoss, openlevel     )
		FETCH_STRING_FIELD(ActivityBoss, togglename    )
		FETCH_INT32_FIELD(ActivityBoss, bossreliveCD  )
		FETCH_INT32_FIELD(ActivityBoss, costitem      )
		FETCH_INT32_FIELD(ActivityBoss, costitemnumber)
		FETCH_INT32_FIELD(ActivityBoss, acttackfactor1)
		FETCH_INT32_FIELD(ActivityBoss, acttackfactor2)
		FETCH_INT32_FIELD(ActivityBoss, acttackfactor3)
		FETCH_INT32_FIELD(ActivityBoss, acttackfactor4)
		FETCH_INT32_FIELD(ActivityBoss, acttackfactor5)
		FETCH_INT32_FIELD(ActivityBoss, acttackfactor6)
		FETCH_INT32_FIELD(ActivityBoss, acttackfactor7)
		FETCH_INT32_FIELD(ActivityBoss, acttackfactor8)
		FETCH_INT32_FIELD(ActivityBoss, herofactor1   )
		FETCH_INT32_FIELD(ActivityBoss, herofactor2   )
		FETCH_INT32_FIELD(ActivityBoss, herofactor3   )
		FETCH_INT32_FIELD(ActivityBoss, herofactor4   )
	
}



//////////////////////////////////////////////////////////////////////////
// 每个配置加一项
//////////////////////////////////////////////////////////////////////////
IMPLEMETN_GET_SETTING(MapClimb)
IMPLEMETN_GET_SETTING(Friend)
IMPLEMETN_GET_SETTING(Plunder)
IMPLEMETN_GET_SETTING(Buzhen)
IMPLEMETN_GET_SETTING(GodBoss)
IMPLEMETN_GET_SETTING(WorldBoss)
IMPLEMETN_GET_SETTING(CardTrain)
IMPLEMETN_GET_SETTING(Arena)
IMPLEMETN_GET_SETTING(Treasure)
IMPLEMETN_GET_SETTING(ZhaoCai)
IMPLEMETN_GET_SETTING(Skill)
IMPLEMETN_GET_SETTING(BattlePrizeSilver)
IMPLEMETN_GET_SETTING(Melee)
IMPLEMETN_GET_SETTING(RobCimelia)
IMPLEMETN_GET_SETTING(PVPFactor)
IMPLEMETN_GET_SETTING(RongLian)
IMPLEMETN_GET_SETTING(Fund)

IMPLEMETN_GET_SETTING(FightFactor)
IMPLEMETN_GET_SETTING(LevelLimit)
IMPLEMETN_GET_SETTING(Sword)
IMPLEMETN_GET_SETTING(Equip)
IMPLEMETN_GET_SETTING(HurtFactor);//yhf
IMPLEMETN_GET_SETTING(Wudaohui);//
IMPLEMETN_GET_SETTING(Juhun);//
IMPLEMETN_GET_SETTING(PveBattleParam);//yhf=======
IMPLEMETN_GET_SETTING(OnlinePrize);//
IMPLEMETN_GET_SETTING(System);//
IMPLEMETN_GET_SETTING(AoyiNum);// yhf
IMPLEMETN_GET_SETTING(Corps);// yyk
IMPLEMETN_GET_SETTING(CorpsRace);
IMPLEMETN_GET_SETTING(CorpsLilian);
IMPLEMETN_GET_SETTING(Fish);
IMPLEMETN_GET_SETTING(Quiz);
IMPLEMETN_GET_SETTING(FengYin);
IMPLEMETN_GET_SETTING(DaoYuanWar);
IMPLEMETN_GET_SETTING(ActivityPray);
IMPLEMETN_GET_SETTING(MysteryShop);
IMPLEMETN_GET_SETTING(JinJie);
IMPLEMETN_GET_SETTING(Parts);
IMPLEMETN_GET_SETTING(Damo);
IMPLEMETN_GET_SETTING(CorpsManor);
IMPLEMETN_GET_SETTING(WeixinShareReward);
IMPLEMETN_GET_SETTING(ActivityBoss);
