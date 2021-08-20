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
		monster->SetInfo(info);
		FSMAI* ai = new FSMAI;
		ai->AddState(new CCarrotBossIntroState);
		ai->AddState(new CCarrotBossAttackState);
		ai->SetCurrentState(MON_STATE::INTRO);
		monster->SetAi(ai);
	}
	break;
	case MON_TYPE::RANGE:
		break;
	default:
		break;
	}

	assert(monster);

	return monster;
}
