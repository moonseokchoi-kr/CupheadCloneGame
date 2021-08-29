#include "pch.h"
#include "CMonsterFactory.h"
#include "CSalSpudder.h"
#include "FSMAI.h"
#include "CIdleState.h"
#include "CIntroState.h"
#include "CDeathState.h"
#include "CSalAttackState.h"
#include "CSlimeBossIntroState.h"
#include "CCarrotBossAttackState.h"
#include "CChauncey.h"
#include "COllieBullb.h"
#include "COnionBossAttackState.h"
#include "COnionBossIdleState.h"
#include "CSlimeIdleState.h"
#include "CSlimAttackState.h"
#include "CSlimeDeathState.h"
#include "CSlimeBossIntroState.h"
#include "CSlime.h"
#include "CState.h"
CMonster* CMonsterFactory::CreateMonster(MON_TYPE _type, Vec2 _pos)
{
	CMonster* monster = nullptr;
	switch (_type)
	{
	case MON_TYPE::NORMAL:
	{
		monster = new CMonster;
		monster->SetPos(_pos);
		monsterInfo info = {};
		info.attackDamege = 10.f;
		info.attackRange = 50.f;
		info.eyesightRange = 300.f;
		info.hp = 100;
		info.attackSpeed = 1.f;
		info.moveSpeed = 200.f;
		monster->SetInfo(info);

		FSMAI* ai = new FSMAI;
		ai->AddState(new CIdleState(L""));
		//ai->AddState(new CTraceState);
		ai->SetCurrentState(MON_STATE::IDLE);
		monster->SetAi(ai);
	}
		break;
	case MON_TYPE::SAL:
	{
		monster = new CSalSpudder;
		monster->SetPos(_pos);
		monsterInfo info = {};
		info.attackDamege = 1;
		info.attackRange = 0;
		info.eyesightRange = 0;
		info.hp = 300.f;
		info.attackSpeed = 0.4f;
		info.moveSpeed = 100.f;
		monster->SetInfo(info);
		monster->SetName(L"Potato");
		monster->Start();
		FSMAI* ai = new FSMAI;
		ai->AddState(new CIdleState(L"POTATO_IDLE"));
		ai->AddState(new CIntroState);
		ai->AddState(new CSalAttackState);
		ai->AddState(new CDeathState(L"POTATO_DEATH"));
		ai->SetCurrentState(MON_STATE::INTRO);
		monster->SetAi(ai);
	}
		break;

	case MON_TYPE::CHAUNCEY:
	{
		monster = new CChauncey;
		monster->SetPos(_pos);
		monsterInfo info = {};
		info.attackDamege = 1;
		info.attackRange = 0;
		info.eyesightRange = 0;
		info.hp = 300.f;
		info.attackSpeed = 0.15;
		info.moveSpeed = 100.f;
		monster->SetName(L"Carrot");
		monster->Start();
		monster->SetInfo(info);
		FSMAI* ai = new FSMAI;
		ai->AddState(new CSlimeBossIntroState);
		ai->AddState(new CCarrotBossAttackState);
		ai->AddState(new CDeathState(L"CARROT_DEATH"));
		ai->SetCurrentState(MON_STATE::INTRO);
		monster->SetAi(ai);
	}
	break;
	case MON_TYPE::OLLIE:
	{
		monster = new COllieBullb;
		monster->SetPos(_pos);
		monsterInfo info = {};
		info.attackDamege = 1;
		info.attackRange = 0;
		info.eyesightRange = 0;
		info.hp = 300.f;
		info.attackSpeed = 0.5;
		info.moveSpeed = 100.f;
		monster->SetName(L"Onion");
		monster->Start();
		monster->SetInfo(info);
		FSMAI* ai = new FSMAI;
		ai->AddState(new CIntroState);
		ai->AddState(new COnionBossIdleState);
		ai->AddState(new COnionBossAttackState);
		ai->AddState(new CDeathState(L"ONION_DEATH_1", L"ONION_DEATH_2"));
		ai->SetCurrentState(MON_STATE::INTRO);
		monster->SetAi(ai);
	}
	break;
	case MON_TYPE::SLIME:
	{
		monster = new CSlime;
		monster->SetPos(_pos);
		monsterInfo info = {};
		info.attackDamege = 1;
		info.attackRange = 0;
		info.eyesightRange = 0;
		info.hp = 300.f;//300.f
		info.attackSpeed = 0.5;
		info.moveSpeed = 100.f;
		monster->SetName(L"Slime");
		monster->Start();
		monster->SetInfo(info);
		FSMAI* ai = new FSMAI;
		ai->AddState(new CSlimeBossIntroState);
		ai->AddState(new CSlimeIdleState);
		ai->AddState(new CSlimAttackState);
		ai->AddState(new CSlimeDeathState);
		ai->SetCurrentState(MON_STATE::INTRO);
		monster->SetAi(ai);
	}
	case MON_TYPE::RANGE:
		break;
	default:
		break;
	}

	assert(monster);

	return monster;
}
