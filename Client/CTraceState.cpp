#include "pch.h"
#include "CTraceState.h"

#include "CPlayer.h"
#include "CMonster.h"

#include "CSceneManager.h"
#include "CTimeManager.h"
CTraceState::CTraceState()
	:CState(MON_STATE::TRACE)
{
}

CTraceState::~CTraceState()
{
}

void CTraceState::Enter()
{
}

void CTraceState::Exit()
{
}

void CTraceState::Update()
{
	CPlayer* player = CSceneManager::GetInst()->GetCurrentScene()->GetPlayer();

	Vec2 playerPos = player->GetPos();

	CMonster* monster = GetMonster();

	Vec2 monsterPos = monster->GetPos();

	Vec2 dir = playerPos - monsterPos;

	dir.Normalize();

	monsterPos += dir * monster->GetInfo().moveSpeed * fDT;
	monster->SetPos(monsterPos);
}
