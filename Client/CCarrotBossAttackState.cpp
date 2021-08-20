#include "pch.h"
#include "CCarrotBossAttackState.h"
#include "CCarrotBossAttackBox.h"
#include "CMonster.h"

#include "CTimeManager.h"

CCarrotBossAttackState::CCarrotBossAttackState()
	:m_attackCount(0.0f)
	,m_maxAttackCount(0.f)
	,m_beamAttackCount(0.f)
	,m_interval(0.15f)
	,m_beamInterval(0.8f)
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
		m_interval = 0.3f;
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
	else
	{
		if (m_attackCount < m_maxAttackCount)
		{
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
		m_changeAccTime += fDT;
		if (m_changeAccTime >= m_attackChangeinterval)
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
