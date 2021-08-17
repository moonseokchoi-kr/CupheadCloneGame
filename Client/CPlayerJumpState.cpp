#include "pch.h"
#include "CPlayerJumpState.h"
#include "CPlayer.h"
#include "CRigidBody.h"
#include "CGravity.h"
#include "CAnimation.h"
#include "CAnimator.h"


#include "CKeyManager.h"
#include "CTimeManager.h"
CPlayerJumpState::CPlayerJumpState()
	:CPlayerState(PLAYER_STATE::JUMP)
{
}

CPlayerJumpState::~CPlayerJumpState()
{
}

void CPlayerJumpState::Enter()
{
	
}

void CPlayerJumpState::Exit()
{
}

void CPlayerJumpState::Update()
{
	m_accTime += fDT;
	GetPlayer()->UpdateMove();
	updateSubState();
	updateAnimation();
	//다시 Idle로 돌아가는법
	if (GetPlayer()->GetGravity()->IsGround() && m_accTime>=0.15f)
	{
		m_accTime = 0.f;
		ChangePlayerState(GetAI(), PLAYER_STATE::IDLE);
	}
}

void CPlayerJumpState::updateAnimation()
{
	Vec2 moveDir = GetPlayer()->GetMoveDir();
	if (1 == moveDir.x)
	{
		GetPlayer()->GetAnimator()->Play(L"PLAYER_JUMP_RIGHT", true);
	}
	else
	{
		GetPlayer()->GetAnimator()->Play(L"PLAYER_JUMP_LEFT", true);
	}

}

void CPlayerJumpState::updateSubState()
{
	//점프중에 가능한 행동
	//방향전환
	if (KEY_TAP(KEY::LEFT))
	{
		GetPlayer()->SetMoveDir(-1, GetPlayer()->GetMoveDir().y);
	}

	if (KEY_TAP(KEY::RIGHT))
	{
		GetPlayer()->SetMoveDir(1, GetPlayer()->GetMoveDir().y);
	}
	
	//대시
	if (KEY_TAP(KEY::LSHIFT))
	{
		ChangePlayerState(GetAI(), PLAYER_STATE::DASH);
	}
	
	//어택
}
