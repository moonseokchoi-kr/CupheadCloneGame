#include "pch.h"
#include "CPlayerHitState.h"
#include "CPlayerStateMachine.h"
#include "CRigidBody.h"
#include "CPlayer.h"
#include "CTimeManager.h"
#include "CAnimation.h"
#include "CAnimator.h"
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
	GetPlayer()->GetRigidBody()->SetVelocity(Vec2(-GetPlayer()->GetMoveDir().x*200.f, 0.f));
	GetPlayer()->GetRigidBody()->SetVelocity(Vec2(-GetPlayer()->GetMoveDir().x *100.f, 0.f));
}

void CPlayerHitState::Exit()
{
	GetPlayer()->GetAnimator()->GetCurrentAnim()->SetFrame(0);
}

void CPlayerHitState::Update()
{
	updateAnimation();
	m_accTime += fDT;
	if (m_accTime >= 0.1f)
	{
		GetPlayer()->GetRigidBody()->SetVelocity(Vec2(0.f, 0.f));
	}
	if (GetPlayer()->GetAnimator()->GetCurrentAnim()->IsFinish())
	{
		m_accTime = 0;
		ChangePlayerState(GetAI(), PLAYER_STATE::IDLE);
	}
}

void CPlayerHitState::updateAnimation()
{
	Vec2 moveDir = GetPlayer()->GetMoveDir();
	if (GetPlayer()->IsAir())
	{
		if (moveDir.x < 0)
		{
			GetPlayer()->GetAnimator()->Play(L"PLAYER_HIT_AIR_LEFT",false);
		}
		else
		{
			GetPlayer()->GetAnimator()->Play(L"PLAYER_HIT_AIR_RIGHT", false);
		}
	}
	else
	{
		if (moveDir.x < 0)
		{
			GetPlayer()->GetAnimator()->Play(L"PLAYER_HIT_LEFT", false);
		}
		else
		{
			GetPlayer()->GetAnimator()->Play(L"PLAYER_HIT_RIGHT", false);
		}
	}
}
