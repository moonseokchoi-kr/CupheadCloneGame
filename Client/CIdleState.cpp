#include "pch.h"
#include "CIdleState.h"
#include "CPlayer.h"
#include "CMonster.h"

#include "CSceneManager.h"
CIdleState::CIdleState()
	:CState(MON_STATE::IDLE)
{
}

CIdleState::~CIdleState()
{
}

void CIdleState::Enter()
{
}

void CIdleState::Exit()
{
}

void CIdleState::Update()
{
	CPlayer* player = CSceneManager::GetInst()->GetCurrentScene()->GetPlayer();
	if (nullptr == player)
	{
		return;
	}
	Vec2 playerPos = player->GetPos();

	//�������� ������ ��ô���� ��ȯ
	CMonster* monster = GetMonster();
	Vec2 monsterPos = monster->GetPos();

	Vec2 diff = playerPos - monsterPos;

	float len = diff.Distance();
	if (len < monster->GetInfo().eyesightRange)
	{
		ChangeAIState(GetAI(), MON_STATE::TRACE);
	}
}
