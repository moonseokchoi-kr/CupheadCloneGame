#include "pch.h"
#include "COnionBossIdleState.h"
#include "CMonster.h"
#include "CAnimator.h"
#include "CAnimation.h"
COnionBossIdleState::COnionBossIdleState()
	:CState(MON_STATE::IDLE)
{
}

COnionBossIdleState::~COnionBossIdleState()
{
}

void COnionBossIdleState::Enter()
{
	GetMonster()->GetAnimator()->Play(L"ONION_IDLE_2", false);
	m_prevAnim = L"ONION_IDLE_2";
}

void COnionBossIdleState::Exit()
{
}

void COnionBossIdleState::Update()
{
	if (GetMonster()->GetAnimator()->GetCurrentAnim()->IsFinish())
	{
		GetMonster()->GetAnimator()->GetCurrentAnim()->SetFrame(0);
		if (m_prevAnim == L"ONION_IDLE_1")
		{
			GetMonster()->GetAnimator()->Play(L"ONION_IDLE_2", false);
			m_prevAnim = L"ONION_IDLE_2";
		}
		else
		{
			GetMonster()->GetAnimator()->Play(L"ONION_IDLE_1", false);
			m_prevAnim = L"ONION_IDLE_1";
		}
	}
}
