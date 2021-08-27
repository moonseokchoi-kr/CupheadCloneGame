#include "pch.h"
#include "CCarrotBossAttackState.h"
#include "CCarrotBossAttackBox.h"
#include "CMonster.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CTimeManager.h"

CCarrotBossAttackState::CCarrotBossAttackState()
	:m_attackCount(0.0f)
	,m_maxAttackCount(0.f)
	,m_beamAttackCount(0.f)
	,m_interval(2.f)
	,m_beamInterval(0.8f)
	,m_patternAccTime(0)
	,m_patternTime(8.f)
	, m_attackChangeinterval(3.f)
{
}

CCarrotBossAttackState::~CCarrotBossAttackState()
{
}

void CCarrotBossAttackState::Enter()
{
	CCarrotBossAttackBox* attackBox = (CCarrotBossAttackBox*)GetMonster()->GetAttackBox();
	if (ATTACK_PATT::PATT1 == attackBox->GetCurrentPatt())
	{
		m_maxAttackCount = 4;
		m_interval = 0.5f;
	}
	else
	{
		m_maxAttackCount = 3;
		m_interval = 0.1f;
	}
}

void CCarrotBossAttackState::Exit()
{
	CCarrotBossAttackBox* attackBox = (CCarrotBossAttackBox*)GetMonster()->GetAttackBox();
	
}

void CCarrotBossAttackState::Update()
{
	if (!GetMonster()->GetTarget())
		return;
	CCarrotBossAttackBox* attackBox = (CCarrotBossAttackBox*)GetMonster()->GetAttackBox();
	if (ATTACK_PATT::PATT1 == attackBox->GetCurrentPatt())
	{
		GetMonster()->GetAnimator()->Play(L"CARROT_IDLE", true);
		//유도미사일
		if (m_patternAccTime <= m_patternTime)
		{
			m_patternAccTime += fDT;
			if (m_attackCount < m_maxAttackCount)
			{
				m_accTime += fDT;
				if (m_accTime >= m_interval)
				{
					attackBox->Fire();
					++m_attackCount;
					m_accTime = 0;
				}
			}
		}

		
	}
	else
	{
		if (m_attackCount < m_maxAttackCount)
		{
			//빔
			GetMonster()->GetAnimator()->Play(L"CARROT_SHOOT", true);
			if (m_beamAttackCount != 4)
			{
				m_accTime += fDT;

				if (m_accTime >= m_interval)
				{
					attackBox->Fire();
					++m_beamAttackCount;
					m_accTime = 0;
				}
			}
			else
			{
				m_beamAccTime += fDT;
				if (m_beamAccTime >= m_beamInterval)
				{
					++m_attackCount;
					m_beamAttackCount = 0;
					m_beamAccTime = 0;
				}

			}
		}
		
	}
	if (m_attackCount == m_maxAttackCount)
	{
		if (ATTACK_PATT::PATT1 == attackBox->GetCurrentPatt()&& m_patternAccTime <= m_patternTime)
		{
				return;	
		}
		else
		{
			m_patternAccTime = 0;
		}
			
		//변경
		m_changeAccTime += fDT;
		GetMonster()->GetAnimator()->Play(L"CARROT_TRANSIT", false);
		if (GetMonster()->GetAnimator()->GetCurrentAnim()->IsFinish())
		{
			
			attackBox->ChangeAttack();
			m_attackCount = 0;
			if (ATTACK_PATT::PATT1 == attackBox->GetCurrentPatt())
			{
				m_maxAttackCount = 4;
				m_interval = 0.3f;
			}
			else
			{
				m_maxAttackCount = 3;
				m_interval = 0.1f;
			}
			m_changeAccTime = 0;
		}
		
	}

}

void CCarrotBossAttackState::updateAnimation()
{
}

void CCarrotBossAttackState::updateSubState()
{
}
