#include "pch.h"
#include "CMonsterFactory.h"
#include "CSalSpudder.h"
#include "FSMAI.h"
#include "CIdleState.h"
#include "CIntroState.h"
#include "CSalAttackState.h"
#include "CCarrotBossIntroState.h"
#include "CCarrotBossAttackState.h"
#include "CChauncey.h"
#include "COllieBullb.h"
#include "COnionBossAttackState.h"
#include "COnionBossIdleState.h"
#include "CCagney.h"
#include "CCagneyAttackState.h"
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
		info.attackSpeed = 2.f;
		info.moveSpeed = 100.f;
		monster->SetInfo(info);
		monster->Start();
		FSMAI* ai = new FSMAI;
		ai->AddState(new CIdleState(L""));
		ai->AddState(new CIntroState(L""));
		ai->AddState(new CSalAttackState);
		ai->SetCurrentState(MON_STATE::IDLE);
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
		monster->Start();
		monster->SetInfo(info);
		FSMAI* ai = new FSMAI;
		ai->AddState(new CCarrotBossIntroState);
		ai->AddState(new CCarrotBossAttackState);
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
		monster->Start();
		monster->SetInfo(info);
		FSMAI* ai = new FSMAI;
		ai->AddState(new CIntroState(L""));
		ai->AddState(new COnionBossIdleState);
		ai->AddState(new COnionBossAttackState);
		ai->SetCurrentState(MON_STATE::IDLE);
		monster->SetAi(ai);
	}
	case MON_TYPE::CAGNEY:
	{
		monster = new CCagney;
		monster->SetPos(_pos);
		monsterInfo info = {};
		info.attackDamege = 1;
		info.attackRange = 0;
		info.eyesightRange = 0;
		info.hp = 500.f;
		info.attackSpeed = 2.f;
		info.moveSpeed = 100.f;
		monster->Start();
		monster->SetInfo(info);
		FSMAI* ai = new FSMAI;
		ai->AddState(new CIntroState(L""));
		ai->AddState(new CCagneyAttackState);
		ai->AddState(new CIdleState(L""));
		ai->SetCurrentState(MON_STATE::IDLE);
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
