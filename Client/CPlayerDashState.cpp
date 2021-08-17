#include "pch.h"
#include "CPlayerDashState.h"

#include "CPlayer.h"
#include "CGravity.h"
#include "CRigidBody.h"

#include "CAnimator.h"
#include "CPlayerStateMachine.h"

#include "CTimeManager.h"
CPlayerDashState::CPlayerDashState()
	:CPlayerState(PLAYER_STATE::DASH)
{
}

CPlayerDashState::~CPlayerDashState()
{
}

void CPlayerDashState::Enter()
{
}

void CPlayerDashState::Exit()
{
}

void CPlayerDashState::Update()
{
	m_accTime += fDT;
	Vec2 moveDir = GetPlayer()->GetMoveDir();
	playerInfo info = GetPlayer()->GetInfo();
	Vec2 velocity = GetPlayer()->GetRigidBody()->GetVelocity();
	updateAnimation();
	GetPlayer()->GetRigidBody()->SetVelocity(Vec2(moveDir.x*500.f, 0.f));
	if (m_accTime >= info.dashDist / GetPlayer()->GetRigidBody()->GetSpeed())
	{
		m_accTime = 0.0f;
		GetPlayer()->GetRigidBody()->SetVelocity(velocity);
		ChangePlayerState(GetAI(), GetAI()->GetPrevState()->GetState());
	}
}

void CPlayerDashState::updateAnimation()
{
	Vec2 moveDir = GetPlayer()->GetMoveDir();
	bool isGround = GetPlayer()->GetGravity()->IsGround();
	if (isGround)
	{
		if (1 == moveDir.x)
			GetPlayer()->GetAnimator()->Play(L"PLAYER_DASH_GROUND_RIGHT", true);
		else
			GetPlayer()->GetAnimator()->Play(L"PLAYER_DASH_GROUND_LEFT", true);
	}
	else
	{
		if (1 == moveDir.x)
			GetPlayer()->GetAnimator()->Play(L"PLAYER_DASH_AIR_RIGHT", true);
		else
			GetPlayer()->GetAnimator()->Play(L"PLAYER_DASH_AIR_LEFT", true);
	}
}

void CPlayerDashState::updateSubState()
{
}
