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
	//�ٽ� Idle�� ���ư��¹�
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
	//�����߿� ������ �ൿ
	//������ȯ
	if (KEY_TAP(KEY::LEFT))
	{
		GetPlayer()->SetMoveDir(-1, GetPlayer()->GetMoveDir().y);
	}

	if (KEY_TAP(KEY::RIGHT))
	{
		GetPlayer()->SetMoveDir(1, GetPlayer()->GetMoveDir().y);
	}
	
	//���
	if (KEY_TAP(KEY::LSHIFT))
	{
		ChangePlayerState(GetAI(), PLAYER_STATE::DASH);
	}
	
	//����
}
