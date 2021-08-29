#include "pch.h"
#include "CSlimeIdleState.h"
#include "define.h"
#include "CTimeManager.h"
#include "CAnimation.h"
#include "CSlime.h"
#include "FSMAI.h"
#include "CAnimator.h"
CSlimeIdleState::CSlimeIdleState()
	:CState(MON_STATE::IDLE)
	,m_accTime(0)
{
}

CSlimeIdleState::~CSlimeIdleState()
{
}

void CSlimeIdleState::Enter()
{
	if (((CSlime*)GetMonster())->GetCurrentPhase() == PHASE::PHASE1)
	{
		ChangeAIState(GetAI(), MON_STATE::ATTACK);
	}
	else
	{
		Vec2 moveDir = GetMonster()->GetMoveDir();

		if (moveDir.x < 0)
		{
			GetMonster()->GetAnimator()->Play(L"LG_SLIME_IDLE_LEFT", false);

		}
		else
		{
			GetMonster()->GetAnimator()->Play(L"LG_SLIME_IDLE_RIGHT", false);
		}
		GetMonster()->GetAnimator()->GetCurrentAnim()->SetFrame(0);
	}
}

void CSlimeIdleState::Update()
{
	m_accTime += fDT;

	if (GetMonster()->GetAnimator()->GetCurrentAnim()->IsFinish())
	{
		ChangeAIState(GetAI(), MON_STATE::ATTACK);
	}
}

void CSlimeIdleState::Exit()
{
	m_accTime = 0;
}
