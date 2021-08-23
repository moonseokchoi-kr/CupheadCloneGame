#include "pch.h"
#include "CPlayerHitState.h"
#include "CPlayerStateMachine.h"
#include "CRigidBody.h"
#include "CPlayer.h"
#include "CTimeManager.h"
CPlayerHitState::CPlayerHitState()
	:CPlayerState(PLAYER_STATE::HIT)
	,m_accTime(0)
	,m_mainTime(0.3f)
{
}

CPlayerHitState::~CPlayerHitState()
{
}

void CPlayerHitState::Enter()
{
	GetPlayer()->GetRigidBody()->SetVelocity(Vec2(0, 0));
}

void CPlayerHitState::Exit()
{
	
}

void CPlayerHitState::Update()
{
	m_accTime += fDT;
	if (m_accTime >= m_mainTime)
	{
		m_accTime = 0;
		ChangePlayerState(GetAI(), PLAYER_STATE::IDLE);
	}
}
