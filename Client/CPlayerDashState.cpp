#include "pch.h"
#include "CPlayerDashState.h"

#include "CPlayer.h"
#include "CGravity.h"
#include "CRigidBody.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CPlayerStateMachine.h"
#include "CPlayerHitBox.h"
#include "CCollider.h"
#include "CTimeManager.h"
CPlayerDashState::CPlayerDashState()
	:CPlayerState(PLAYER_STATE::DASH)
	,m_accTime(0.0f)
{
}

CPlayerDashState::~CPlayerDashState()
{
}

void CPlayerDashState::Enter()
{
	GetPlayer()->GetHitBox()->GetCollider()->SetAvaCollide(false);
}

void CPlayerDashState::Exit()
{
	GetPlayer()->GetHitBox()->GetCollider()->SetAvaCollide(true);
}

void CPlayerDashState::Update()
{
	m_accTime += fDT;
	Vec2 moveDir = GetPlayer()->GetMoveDir();
	playerInfo info = GetPlayer()->GetInfo();
	Vec2 velocity = GetPlayer()->GetRigidBody()->GetVelocity();
	updateAnimation();
	GetPlayer()->GetRigidBody()->SetVelocity(Vec2(moveDir.x*500.f, 0.f));
	if (GetPlayer()->GetAnimator()->GetCurrentAnim()->IsFinish())
	{
		m_accTime = 0.0f;
		GetPlayer()->GetAnimator()->GetCurrentAnim()->SetFrame(0);
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
			GetPlayer()->GetAnimator()->Play(L"PLAYER_DASH_GROUND_RIGHT", false);
		else
			GetPlayer()->GetAnimator()->Play(L"PLAYER_DASH_GROUND_LEFT", false);
	}
	else
	{
		if (1 == moveDir.x)
			GetPlayer()->GetAnimator()->Play(L"PLAYER_DASH_AIR_RIGHT", false);
		else
			GetPlayer()->GetAnimator()->Play(L"PLAYER_DASH_AIR_LEFT", false);
	}
}

void CPlayerDashState::updateSubState()
{
}
