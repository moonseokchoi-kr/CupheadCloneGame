#include "pch.h"
#include "CMonsterFactory.h"
#include "CMonster.h"
#include "FSMAI.h"
#include "CIdleState.h"
#include "CTraceState.h"

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
		ai->AddState(new CIdleState);
		ai->AddState(new CTraceState);
		ai->SetCurrentState(MON_STATE::IDLE);
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
