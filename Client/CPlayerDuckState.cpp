#include "pch.h"
#include "CPlayerDuckState.h"
#include "CPlayer.h"
#include "CPlayerStateMachine.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CCollider.h"
#include "CPlayerAttackBox.h"
#include "CRigidBody.h"
#include "CKeyManager.h"
CPlayerDuckState::CPlayerDuckState()
	:CPlayerState(PLAYER_STATE::DUCK)
	,m_subState(PLAYER_STATE::IDLE)
{
}

CPlayerDuckState::~CPlayerDuckState()
{
}

void CPlayerDuckState::Enter()
{
	
	GetPlayer()->GetRigidBody()->SetVelocity(Vec2(0.f, 0.f));
	playerInfo info = GetPlayer()->GetInfo();
	if (GetPlayer()->GetMoveDir().x < 0)
	{
		info.shootDir = Vec2(-1, 0);
	}
	else
	{
		info.shootDir = Vec2(1, 0);
	}
	GetPlayer()->SetInfo(info);
	if (GetPlayer()->GetAi()->GetPrevState()->GetState() == PLAYER_STATE::IDLE)
	{
		m_subState = PLAYER_STATE::IDLE;
	}
	if (GetPlayer()->GetAi()->GetPrevState()->GetState() == PLAYER_STATE::ATTACK)
	{
		m_subState = PLAYER_STATE::ATTACK;
	}

}

void CPlayerDuckState::Exit()
{
}

void CPlayerDuckState::Update()
{
	updateSubState();
	updateAnimation();
}

void CPlayerDuckState::updateSubState()
{
	GetPlayer()->GetAttackBox()->SetPos(Vec2(70.f, 60.f));
	if (KEY_HOLD(KEY::Z))
	{
		m_subState = PLAYER_STATE::ATTACK;
		GetPlayer()->GetAttackBox()->Fire();
	}
	else
	{
		m_subState = PLAYER_STATE::IDLE;
	}


	if (KEY_AWAY(KEY::DOWN) || KEY_NONE(KEY::DOWN))
	{
		ChangePlayerState(GetPlayer()->GetAi(), PLAYER_STATE::IDLE);
	}
	playerInfo info = GetPlayer()->GetInfo();
	if (KEY_HOLD(KEY::DOWN))
	{
		if (KEY_HOLD(KEY::LEFT) || KEY_TAP(KEY::LEFT))
		{
			info.shootDir = Vec2(-1, 0);

		}
		if (KEY_HOLD(KEY::RIGHT) || KEY_TAP(KEY::RIGHT))
		{
			info.shootDir = Vec2(1, 0);
		}
		GetPlayer()->SetInfo(info);
	}
	
}

void CPlayerDuckState::updateAnimation()
{
	Vec2 moveDir = GetPlayer()->GetMoveDir();
	playerInfo info = GetPlayer()->GetInfo();
	switch (m_subState)
	{
	case PLAYER_STATE::IDLE:
	{
		if (info.shootDir.x < 0)
		{
			GetPlayer()->GetAnimator()->Play(L"PLAYER_DUCK_IDLE_LEFT", true);
		}
		else
		{
			GetPlayer()->GetAnimator()->Play(L"PLAYER_DUCK_IDLE_RIGHT", true);
		}
	}
		break;
	case PLAYER_STATE::ATTACK:
	{
		if (info.shootDir.x < 0)
		{
			GetPlayer()->GetAnimator()->Play(L"PLAYER_SHOOT_DUCK_LEFT", true);
		}
		else
		{
			GetPlayer()->GetAnimator()->Play(L"PLAYER_SHOOT_DUCK_RIGHT", true);
		}
	}
		break;
	default:
		break;
	}
}
