#include "pch.h"
#include "CSalAttackState.h"
#include "CMonster.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CAttackBox.h"
#include "CTimeManager.h"
CSalAttackState::CSalAttackState()
	:m_stateAccTime(0)
	,m_attackAccTime(0)
	,m_attackCount(0)
	,m_curAttackSpeed(0)
	,m_initAttackSpeed(0)
	,m_initInterval(2.f)
{

}

CSalAttackState::~CSalAttackState()
{
}

void CSalAttackState::Enter()
{
	m_initAttackSpeed = GetMonster()->GetInfo().attackSpeed;
	m_initInterval = m_initAttackSpeed / 4.f;
	m_curAttackSpeed = m_initAttackSpeed * (1 - m_attackCount * 0.2f);
	m_interval = m_initInterval * (1 - m_attackCount * 0.2f);

}

void CSalAttackState::Exit()
{
	++m_attackCount;
	if (m_attackCount > 2)
		m_attackCount = 0;
}

void CSalAttackState::Update()
{
	m_stateAccTime += fDT;
	m_attackAccTime += fDT;
	
	if (m_attackAccTime >= m_interval)
	{
		GetMonster()->GetAnimator()->Play(L"POTATO_SHOOT", false);
		GetMonster()->GetAnimator()->GetCurrentAnim()->SetFrame(0);
		GetMonster()->GetAnimator()->GetCurrentAnim()->SetDuration(m_interval);
		GetMonster()->GetAttackBox()->Fire();
		m_attackAccTime = 0;
	}
	if (m_stateAccTime >= m_curAttackSpeed)
	{
		ChangeAIState(GetAI(), MON_STATE::IDLE);
		m_stateAccTime = 0;
	}
}
