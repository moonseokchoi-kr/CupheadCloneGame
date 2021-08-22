#include "pch.h"
#include "CPlayerHitState.h"
#include "CPlayerStateMachine.h"
#include "CTimeManager.h"
CPlayerHitState::CPlayerHitState()
	:CPlayerState(PLAYER_STATE::HIT)
	,m_accTime(0)
	,m_mainTime(0.15f)
{
}

CPlayerHitState::~CPlayerHitState()
{
}

void CPlayerHitState::Enter()
{
}

void CPlayerHitState::Exit()
{
}

void CPlayerHitState::Update()
{
	m_accTime += fDT;
	if (m_accTime >= m_mainTime)
	{
		ChangePlayerState(GetAI(), GetAI()->GetPrevState()->GetState());
	}
}
