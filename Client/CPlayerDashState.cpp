#include "pch.h"
#include "CPlayerDashState.h"
#include "CVFXObject.h"
#include "CPlayer.h"
#include "CGravity.h"
#include "CRigidBody.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CPlayerStateMachine.h"
#include "CSound.h"
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
	Vec2 moveDir = GetPlayer()->GetMoveDir();
	GetPlayer()->GetHitBox()->GetCollider()->SetAvaCollide(false);
	GetPlayer()->GetRigidBody()->SetMaxVelocity(1000.f);
	SetSFX(L"PLAYER_DASH");
	GetSFX()->Play(true);
	GetSFX()->SetPosition(50.f);
	GetSFX()->SetVolume(100.f);
	GetPlayer()->GetVFX()->SetOffset(Vec2(-moveDir.x*90.f, 70.f));
	GetPlayer()->GetVFX()->SetType(VFX_TYPE::DASH_BOMB);
}

void CPlayerDashState::Exit()
{
	GetSFX()->Stop(true);
	GetPlayer()->GetHitBox()->GetCollider()->SetAvaCollide(true);
}

void CPlayerDashState::Update()
{
	m_accTime += fDT;
	Vec2 moveDir = GetPlayer()->GetMoveDir();
	playerInfo info = GetPlayer()->GetInfo();
	Vec2 velocity = GetPlayer()->GetRigidBody()->GetVelocity();
	updateAnimation();
	GetPlayer()->GetRigidBody()->SetVelocity(Vec2(moveDir.x*1000.f, 0.f));
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
