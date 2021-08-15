#include "pch.h"
#include "CPlayerIdleState.h"
#include "CPlayer.h"
#include "CAnimator.h"

#include "CKeyManager.h"
CPlayerIdleState::CPlayerIdleState()
	:CPlayerState(PLAYER_STATE::IDLE)
{
}

CPlayerIdleState::~CPlayerIdleState()
{
}

void CPlayerIdleState::Enter()
{
	CPlayer* owner = GetPlayer();

	if (-1 == owner->GetInfo().moveDir)
	{
		owner->GetAnimator()->Play(L"PLAYER_IDLE_LEFT", true);
	}
	else
	{
		owner->GetAnimator()->Play(L"PLAYER_IDLE_LEFT", true);
	}
}

void CPlayerIdleState::Exit()
{
}

void CPlayerIdleState::Update()
{
	CPlayer* owner = GetPlayer();
	playerInfo info = owner->GetInfo();

	updateSubState();
	updateAnimation();
	owner->UpdateMove();

	info.prevMoveDir = info.moveDir;

	owner->SetInfo(info);
}

void CPlayerIdleState::updateSubState()
{
	playerInfo info = GetPlayer()->GetInfo();
	if (KEY_TAP(KEY::LEFT))
	{
		info.moveDir = -1;
		if (info.moveDir != info.prevMoveDir)
			m_subState = PLAYER_STATE::TURN;

	}
	if (KEY_TAP(KEY::RIGHT))
	{
		info.moveDir = 1;
		if (info.moveDir != info.prevMoveDir)
			m_subState = PLAYER_STATE::TURN;
	}

	if (KEY_HOLD(KEY::LEFT))
	{
		info.moveDir = -1;
		m_subState = PLAYER_STATE::RUN;

	}
	if (KEY_HOLD(KEY::RIGHT))
	{
		info.moveDir = 1;
		m_subState = PLAYER_STATE::RUN;
	}
	if (KEY_TAP(KEY::Z))
	{
		ChangePlayerState(GetAI(), PLAYER_STATE::ATTACK);
	}
	if (KEY_TAP(KEY::X))
	{
	
	}
	if (KEY_TAP(KEY::LSHIFT))
	{

	}
	GetPlayer()->SetInfo(info);
}

void CPlayerIdleState::updateAnimation()
{
	CPlayer* owner = GetPlayer();
	playerInfo info = owner->GetInfo();

	switch (m_subState)
	{
	case PLAYER_STATE::IDLE:
	{
		if (-1 == info.moveDir)
			owner->GetAnimator()->Play(L"PLAYER_IDLE_LEFT", true);
		else
			owner->GetAnimator()->Play(L"PLAYER_IDLE_RIGHT", true);
	}
		break;
	case PLAYER_STATE::TURN:
	{
		if (-1 == info.prevMoveDir)
			owner->GetAnimator()->Play(L"PLAYER_RUN_TURN_RIGHT", true);
		else
			owner->GetAnimator()->Play(L"PLAYER_RUN_TURN_LEFT", true);
	}
		break;
	case PLAYER_STATE::RUN:
	{

		if (-1 == info.moveDir)
			owner->GetAnimator()->Play(L"PLAYER_NORMAL_RUN_LEFT", true);
		else
			owner->GetAnimator()->Play(L"PLAYER_NORMAL_RUN_RIGHT", true);

	}
	case PLAYER_STATE::DASH:
		break;
	case PLAYER_STATE::HIT:
		break;
	case PLAYER_STATE::DEAD:
		break;
	default:
		break;
	}
}
