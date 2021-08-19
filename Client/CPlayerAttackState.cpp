#include "pch.h"
#include "CPlayerAttackState.h"

#include "CPlayerStateMachine.h"
#include "CPlayer.h"
#include "CRigidBody.h"
#include "CGravity.h"
#include "CAttackBox.h"
#include "CAnimation.h"
#include "CAnimator.h"

#include "CKeyManager.h"
#include "CCamera.h"
CPlayerAttackState::CPlayerAttackState()
	:CPlayerState(PLAYER_STATE::ATTACK)
{
}

CPlayerAttackState::~CPlayerAttackState()
{
}

void CPlayerAttackState::Enter()
{
	if (GetAI()->GetPrevState()->GetState() == PLAYER_STATE::IDLE)
	{
		if (GetAI()->GetPrevState()->GetSubState() == PLAYER_STATE::RUN)
		{
			m_subState = PLAYER_STATE::RUN;
		}
		else
		{
			m_subState = PLAYER_STATE::IDLE;
		}
	}
	else if ((GetAI()->GetPrevState()->GetState() == PLAYER_STATE::JUMP))
	{
		m_subState = PLAYER_STATE::JUMP;
	}

}

void CPlayerAttackState::Exit()
{
}

void CPlayerAttackState::Update()
{
	
	updateSubState();
	GetPlayer()->UpdateMove();
	updateAnimation();
	if (KEY_AWAY(KEY::Z) || KEY_NONE(KEY::Z))
	{
		ChangePlayerState(GetAI(), GetAI()->GetPrevState()->GetState());
	}
	playerInfo info = GetPlayer()->GetInfo();
	info.prevMoveDir = GetPlayer()->GetMoveDir();
	GetPlayer()->GetAttackBox()->Update();
}

void CPlayerAttackState::updateSubState()
{
	playerInfo info = GetPlayer()->GetInfo();
	if (KEY_TAP(KEY::LEFT))
	{
		GetPlayer()->SetMoveDir(-1, GetPlayer()->GetMoveDir().y);
		if (GetPlayer()->GetMoveDir() != info.prevMoveDir)
			m_subState = PLAYER_STATE::TURN;

	}
	if (KEY_TAP(KEY::RIGHT))
	{
		GetPlayer()->SetMoveDir(1, GetPlayer()->GetMoveDir().y);
		if (GetPlayer()->GetMoveDir() != info.prevMoveDir)
			m_subState = PLAYER_STATE::TURN;
	}


	if (KEY_HOLD(KEY::LEFT))
	{
		GetPlayer()->SetMoveDir(-1, GetPlayer()->GetMoveDir().y);
		m_subState = PLAYER_STATE::RUN;

	}
	if (KEY_HOLD(KEY::RIGHT))
	{
		GetPlayer()->SetMoveDir(1, GetPlayer()->GetMoveDir().y);
		m_subState = PLAYER_STATE::RUN;
	}
	if (KEY_HOLD(KEY::Z) || KEY_TAP(KEY::Z))
	{
		GetPlayer()->GetAttackBox()->Fire();
		//CCamera::GetInst()->SetCamEffect(0.1f, CAMERA_EFFECT::VIBRATION);
	}
	if (GetPlayer()->GetGravity()->IsGround())
	{
		if (KEY_TAP(KEY::X))
		{
			ChangePlayerState(GetAI(), PLAYER_STATE::JUMP);
		}
	}
	if (KEY_TAP(KEY::LSHIFT))
	{
		ChangePlayerState(GetAI(), PLAYER_STATE::DASH);
	}
	else if (0.f == GetPlayer()->GetRigidBody()->GetSpeed())
	{
		m_subState = PLAYER_STATE::IDLE;
	}
	GetPlayer()->SetInfo(info);
	
}

void CPlayerAttackState::updateAnimation()
{
	playerInfo info = GetPlayer()->GetInfo();
	switch (m_subState)
	{
	case PLAYER_STATE::IDLE:
	{
		if (info.shootDir.x == 1)
		{
			if (info.shootDir.y == -1)
			{
				GetPlayer()->GetAnimator()->Play(L"PLAYER_SHOOT_DIAGNOAL_UP_RIGHT", true);
			}
			else if (info.shootDir.y == 1)
			{
				GetPlayer()->GetAnimator()->Play(L"PLAYER_SHOOT_DIAGNOAL_DOWN_RIGHT", true);
			}
			else
			{
				GetPlayer()->GetAnimator()->Play(L"PLAYER_SHOOT_STRAGIHT_RIGHT", true);

			}

		}
		else if (info.shootDir.x == -1)
		{
			if (info.shootDir.y == -1)
			{
				GetPlayer()->GetAnimator()->Play(L"PLAYER_SHOOT_DIAGNOAL_UP_LEFT", true);
			}
			else if (info.shootDir.y == 1)
			{
				GetPlayer()->GetAnimator()->Play(L"PLAYER_SHOOT_DIAGNOAL_DOWN_LEFT", true);
			}
			else
			{
				GetPlayer()->GetAnimator()->Play(L"PLAYER_SHOOT_STRAGIHT_LEFT", true);
			}

		}
		else
		{
			if (info.shootDir.y == -1)
			{
				GetPlayer()->GetAnimator()->Play(L"PLAYER_SHOOT_UP", true);
			}
			else if (info.shootDir.y == 1)
			{
				GetPlayer()->GetAnimator()->Play(L"PLAYER_SHOOT_DOWN", true);
			}
		}
		break;
	case PLAYER_STATE::TURN:
	{
		
		if (-1 == info.prevMoveDir.x)
		{
			GetPlayer()->GetAnimator()->Play(L"PLAYER_SHOOT_RUN_TURN_RIGHT", true);
		}
		else
		{
			GetPlayer()->GetAnimator()->Play(L"PLAYER_SHOOT_RUN_TURN_LEFT", true);
		}
		if (info.shootDir.y == -1)
		{
			if (-1 == info.prevMoveDir.x)
			{
				GetPlayer()->GetAnimator()->Play(L"PLAYER_SHOOT_RUN_UP_TURN_RIGHT", true);
			}
			else
			{
				GetPlayer()->GetAnimator()->Play(L"PLAYER_SHOOT_RUN_UP_TURN_LEFT", true);
			}

		}

	}
	break;
	case PLAYER_STATE::RUN:
	{
		if (info.shootDir.x == 1)
		{
			if (info.shootDir.y == -1)
			{
				GetPlayer()->GetAnimator()->Play(L"PLAYER_SHOOT_RUN_UP_RIGHT", true);
			}
			else
			{
				GetPlayer()->GetAnimator()->Play(L"PLAYER_SHOOT_RUN_RIGHT", true);
			}
		}
		if (info.shootDir.x == -1)
		{
			if (info.shootDir.y == -1)
			{
				GetPlayer()->GetAnimator()->Play(L"PLAYER_SHOOT_RUN_UP_LEFT", true);
			}
			else
			{
				GetPlayer()->GetAnimator()->Play(L"PLAYER_SHOOT_RUN_LEFT", true);
			}
		}

	}
	break;
	case PLAYER_STATE::JUMP:
	{

	}
	break;
	default:
		break;
	}
	}
}

