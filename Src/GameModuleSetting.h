#pragma once
#include "IGameModuleSetting.h"

struct ISchemeCenter;

class CGameModuleSetting: public IGameModuleSetting
{
public:
	void FetchSetting();

#define DECLARE_GET_SETTING(name) virtual SGameModuleSetting##name& GetSetting##name()

	// 每个配置加一项
	//////////////////////////////////////////////////////////////////////////
	DECLARE_GET_SETTING(MapClimb);
	DECLARE_GET_SETTING(Friend);
	DECLARE_GET_SETTING(Plunder);
	DECLARE_GET_SETTING(Buzhen);
	DECLARE_GET_SETTING(GodBoss);
	DECLARE_GET_SETTING(WorldBoss);
	DECLARE_GET_SETTING(CardTrain);
	DECLARE_GET_SETTING(Arena);
	DECLARE_GET_SETTING(Treasure);
	DECLARE_GET_SETTING(ZhaoCai);
	DECLARE_GET_SETTING(BattlePrizeSilver);
	DECLARE_GET_SETTING(Melee);
	DECLARE_GET_SETTING(Skill);
	DECLARE_GET_SETTING(RobCimelia);
	DECLARE_GET_SETTING(PVPFactor);

	DECLARE_GET_SETTING(RongLian);
	DECLARE_GET_SETTING(Fund);
	DECLARE_GET_SETTING(FightFactor);
	DECLARE_GET_SETTING(LevelLimit);
	DECLARE_GET_SETTING(Sword);
	DECLARE_GET_SETTING(Equip);
	DECLARE_GET_SETTING(HurtFactor);//yhf
	DECLARE_GET_SETTING(Wudaohui);
	DECLARE_GET_SETTING(Juhun);
	DECLARE_GET_SETTING(PveBattleParam);//yhf
	DECLARE_GET_SETTING(OnlinePrize);
	DECLARE_GET_SETTING(System);	// yyk
	DECLARE_GET_SETTING(AoyiNum); // yhf
	DECLARE_GET_SETTING(Corps); // yyk
	DECLARE_GET_SETTING(CorpsRace); // yyk
	DECLARE_GET_SETTING(CorpsLilian); // yyk
	DECLARE_GET_SETTING(Quiz);
	DECLARE_GET_SETTING(Fish);
	DECLARE_GET_SETTING(FengYin);
	DECLARE_GET_SETTING(DaoYuanWar);
    DECLARE_GET_SETTING(ActivityPray);
    DECLARE_GET_SETTING(MysteryShop);
	DECLARE_GET_SETTING(JinJie);
	DECLARE_GET_SETTING(Parts);
	DECLARE_GET_SETTING(Damo);
	DECLARE_GET_SETTING(CorpsManor);
	DECLARE_GET_SETTING(WeixinShareReward);
	DECLARE_GET_SETTING(ActivityBoss);
private:

#define DECLARE_FETCH_FUN(name)	void FetchSetting##name(int configIndex, ISchemeCenter* schemeCenter)

	// 每个配置加一项
	//////////////////////////////////////////////////////////////////////////
	DECLARE_FETCH_FUN(MapClimb);
	DECLARE_FETCH_FUN(Friend);
	DECLARE_FETCH_FUN(Plunder);
	DECLARE_FETCH_FUN(Buzhen);
	DECLARE_FETCH_FUN(GodBoss);
	DECLARE_FETCH_FUN(WorldBoss);
	DECLARE_FETCH_FUN(CardTrain);
	DECLARE_FETCH_FUN(Arena);
	DECLARE_FETCH_FUN(Treasure);
	DECLARE_FETCH_FUN(ZhaoCai);
	DECLARE_FETCH_FUN(BattlePrizeSilver);
	DECLARE_FETCH_FUN(Melee);
	DECLARE_FETCH_FUN(Skill);
	DECLARE_FETCH_FUN(RobCimelia);
	DECLARE_FETCH_FUN(PVPFactor);

	DECLARE_FETCH_FUN(RongLian);
	DECLARE_FETCH_FUN(Fund);
	DECLARE_FETCH_FUN(FightFactor);
	DECLARE_FETCH_FUN(LevelLimit);
	DECLARE_FETCH_FUN(Sword);
	DECLARE_FETCH_FUN(Equip);
	DECLARE_FETCH_FUN(HurtFactor);//yhf
	DECLARE_FETCH_FUN(Wudaohui);
	DECLARE_FETCH_FUN(Juhun);
	DECLARE_FETCH_FUN(PveBattleParam);//yhf
	DECLARE_FETCH_FUN(OnlinePrize);
	DECLARE_FETCH_FUN(System);	//yyk
	DECLARE_FETCH_FUN(AoyiNum);// yhf
	DECLARE_FETCH_FUN(Corps);	// yyk
	DECLARE_FETCH_FUN(CorpsRace);
	DECLARE_FETCH_FUN(CorpsLilian);
	DECLARE_FETCH_FUN(Quiz);
	DECLARE_FETCH_FUN(Fish);
	DECLARE_FETCH_FUN(FengYin);
	DECLARE_FETCH_FUN(DaoYuanWar);
    DECLARE_FETCH_FUN(ActivityPray);
    DECLARE_FETCH_FUN(MysteryShop);
	DECLARE_FETCH_FUN(JinJie);
	DECLARE_FETCH_FUN(Parts);
	DECLARE_FETCH_FUN(Damo);
	DECLARE_FETCH_FUN(CorpsManor);
	DECLARE_FETCH_FUN(WeixinShareReward);
	DECLARE_FETCH_FUN(ActivityBoss);
private:

#define DECLARE_SETTING_SYMBOL(name) SGameModuleSetting##name m_setting##name

	// 每个配置加一项
	//////////////////////////////////////////////////////////////////////////
	DECLARE_SETTING_SYMBOL(MapClimb);
	DECLARE_SETTING_SYMBOL(Friend);
	DECLARE_SETTING_SYMBOL(Plunder);
	DECLARE_SETTING_SYMBOL(Buzhen);
	DECLARE_SETTING_SYMBOL(GodBoss);
	DECLARE_SETTING_SYMBOL(WorldBoss);
	DECLARE_SETTING_SYMBOL(CardTrain);
	DECLARE_SETTING_SYMBOL(Arena);
	DECLARE_SETTING_SYMBOL(Treasure);
	DECLARE_SETTING_SYMBOL(ZhaoCai);
	DECLARE_SETTING_SYMBOL(BattlePrizeSilver);
	DECLARE_SETTING_SYMBOL(Melee);
	DECLARE_SETTING_SYMBOL(Skill);
	DECLARE_SETTING_SYMBOL(RobCimelia);
	DECLARE_SETTING_SYMBOL(PVPFactor);

	DECLARE_SETTING_SYMBOL(RongLian);
	DECLARE_SETTING_SYMBOL(Fund);
	DECLARE_SETTING_SYMBOL(FightFactor);
	DECLARE_SETTING_SYMBOL(LevelLimit);
	DECLARE_SETTING_SYMBOL(Sword);
	DECLARE_SETTING_SYMBOL(Equip);
	DECLARE_SETTING_SYMBOL(HurtFactor);//yhf
	DECLARE_SETTING_SYMBOL(Wudaohui);
	DECLARE_SETTING_SYMBOL(Juhun);
	DECLARE_SETTING_SYMBOL(PveBattleParam);//yhf
	DECLARE_SETTING_SYMBOL(OnlinePrize);
	DECLARE_SETTING_SYMBOL(System);	//yyk
	DECLARE_SETTING_SYMBOL(AoyiNum);// yhf
	DECLARE_SETTING_SYMBOL(Corps);	//yyk
	DECLARE_SETTING_SYMBOL(CorpsRace);
	DECLARE_SETTING_SYMBOL(CorpsLilian);
	DECLARE_SETTING_SYMBOL(Quiz);
	DECLARE_SETTING_SYMBOL(Fish);
	DECLARE_SETTING_SYMBOL(FengYin);
	DECLARE_SETTING_SYMBOL(DaoYuanWar);
    DECLARE_SETTING_SYMBOL(ActivityPray);
    DECLARE_SETTING_SYMBOL(MysteryShop);
	DECLARE_SETTING_SYMBOL(JinJie);
	DECLARE_SETTING_SYMBOL(Parts);
	DECLARE_SETTING_SYMBOL(Damo);
	DECLARE_SETTING_SYMBOL(CorpsManor);
	DECLARE_SETTING_SYMBOL(WeixinShareReward);
	DECLARE_SETTING_SYMBOL(ActivityBoss);
};