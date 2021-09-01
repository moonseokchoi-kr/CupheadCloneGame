#include "pch.h"
#include "CPlayerJumpState.h"
#include "CPlayer.h"
#include "CRigidBody.h"
#include "CCollider.h"
#include "CGravity.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CPlayerAttackBox.h"
#include "CSound.h"
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
	GetPlayer()->GetCollider()->SetScale(Vec2(70.f, 100.f));
	SetSFX(L"PLAYER_JUMP");
	GetSFX()->Play(false);
	GetSFX()->SetPosition(50.f);
	GetSFX()->SetVolume(100.f);
}

void CPlayerJumpState::Exit()
{
	GetPlayer()->GetCollider()->SetScale(Vec2(80.f, 120.f));
	GetPlayer()->GetRigidBody()->SetVelocity(Vec2(GetPlayer()->GetInfo().moveSpeed, 0.f));
}

void CPlayerJumpState::Update()
{
	m_accTime += fDT;
	GetPlayer()->UpdateMove();
	
	updateSubState();
	updateAnimation();
	//�ٽ� Idle�� ���ư��¹�
	if (GetPlayer()->GetGravity()->IsGround() && m_accTime>=0.05f)
	{
		m_accTime = 0.f;
		GetSFX()->Stop(true);
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
		//GetPlayer()->SetMoveDir(-1, GetPlayer()->GetMoveDir().y);
		//GetPlayer()->GetRigidBody()->AddForce(Vec2(-GetPlayer()->GetInfo().moveSpeed, 0.f));
	}

	if (KEY_TAP(KEY::RIGHT))
	{
		//GetPlayer()->SetMoveDir(1, GetPlayer()->GetMoveDir().y);
		//GetPlayer()->GetRigidBody()->AddForce(Vec2(-GetPlayer()->GetInfo().moveSpeed, 0.f));
	}
	
	//���
	if (KEY_TAP(KEY::LSHIFT))
	{
		ChangePlayerState(GetAI(), PLAYER_STATE::DASH);
	}
	
	//����
	if (KEY_HOLD(KEY::Z))
	{
		GetPlayer()->GetAttackBox()->Fire();
	}
}
