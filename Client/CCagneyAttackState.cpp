#include "pch.h"
#include "CCagneyAttackState.h"
#include "CMonster.h"
#include "CCagneyAttackBox.h"

#include "CTimeManager.h"
CCagneyAttackState::CCagneyAttackState()
	:m_accTime(0)
	,m_interval(0.15f)
	,m_attackCount(0)
	,m_maxAttackCount(3)
	,m_seedInterval(0.1f)
	,m_seedAccTime(0)
{
}

CCagneyAttackState::~CCagneyAttackState()
{
}

void CCagneyAttackState::Enter()
{
	updateSubState();
}

void CCagneyAttackState::Exit()
{
	m_accTime = 0;
	m_interval = 0.15f;
	m_attackCount = 0;
	m_maxAttackCount = 3;
	m_seedInterval = 0.1f;
	m_seedAccTime = 0;

}

void CCagneyAttackState::Update()
{
	switch (m_currentPatt)
	{
	case ATTACK_PATT::PATT1:
	case ATTACK_PATT::PATT2:
	{
		if (m_attackCount <= m_maxAttackCount)
		{
			m_accTime += fDT;
			if (m_accTime >= m_interval)
			{
				++m_attackCount;
				GetMonster()->GetAttackBox()->Fire();
			}
			
		}
		else
		{
			ChangeAIState(GetAI(), MON_STATE::IDLE);
		}
	
	}
	break;
	case ATTACK_PATT::PATT3:
	{
		if (m_attackCount <= m_maxAttackCount)
		{
			m_accTime += fDT;
			if (m_accTime >= m_interval)
			{
				++m_attackCount;
				GetMonster()->GetAttackBox()->Fire();
			}
			
		}
		else
		{
			ChangeAIState(GetAI(), MON_STATE::IDLE);
		}
	}
	break;
	case ATTACK_PATT::PATT4:
	{
		if (m_attackCount <= m_maxAttackCount)
		{
			m_accTime += fDT;
			if (m_accTime >= m_interval)
			{
				++m_attackCount;
				GetMonster()->GetAttackBox()->Fire();
				m_accTime = 0;
			}

		}
		else
		{
			ChangeAIState(GetAI(), MON_STATE::IDLE);
		}
	}
		break;

	default:
		break;
	}
}

void CCagneyAttackState::updateAnimation()
{
}

void CCagneyAttackState::updateSubState()
{
	random_device rd;
	std::mt19937_64 gen(rd());
	std::uniform_int_distribution<int>  dis(0, 1000);
	float percent = dis(gen) / 1000.f;
	if(percent <0.25f)
	{
		m_maxAttackCount = 1;
		m_interval = 0.15f;
		//상단 머리 공격
		m_currentPatt = ATTACK_PATT::PATT1;
	}
	if(0.25f<= percent && percent<0.5f)
	{

		m_maxAttackCount = 1;
		m_interval = 0.15f;
		//하단 머리공격
		m_currentPatt = ATTACK_PATT::PATT2;
	}
	if (0.5f <= percent && percent < 0.75f)
	{
		m_maxAttackCount = 2;
		m_interval = 0.15f;
		//유도씨앗 공격
		m_currentPatt = ATTACK_PATT::PATT3;
	}
	if(0.75f <= percent && percent < 1.f)
	{
		m_maxAttackCount = 4;
		m_interval = 0.15f;
		//씨앗 몬스터 공격
		m_currentPatt = ATTACK_PATT::PATT4;
	}

	((CCagneyAttackBox*)GetMonster()->GetAttackBox())->SetCurrnetPatt(m_currentPatt);
}
