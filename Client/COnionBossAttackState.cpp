#include "pch.h"
#include "COnionBossAttackState.h"
#include "CMonster.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "COnionBossAttackBox.h"
#include "CTimeManager.h"
COnionBossAttackState::COnionBossAttackState()
	:m_maxattackCount(5)
	, m_accTime(0)
	, m_attackCount(0)
{
}

COnionBossAttackState::~COnionBossAttackState()
{
}

void COnionBossAttackState::Enter()
{
	GetMonster()->GetAnimator()->Play(L"ONION_CRYING", false);
}

void COnionBossAttackState::Exit()
{
	m_accTime = 0;
	m_attackCount = 0;
}

void COnionBossAttackState::Update()
{
	m_accTime += fDT;
	if (m_accTime >= GetMonster()->GetInfo().attackSpeed)
	{
		GetMonster()->GetAnimator()->GetCurrentAnim()->SetFrame(14);
		if (m_attackCount <= m_maxattackCount)
		{
			GetMonster()->GetAttackBox()->Fire();
			++m_attackCount;
			m_accTime = 0;
		}
		else
		{
			ChangeAIState(GetAI(), MON_STATE::IDLE);
		}
		
	}
}
