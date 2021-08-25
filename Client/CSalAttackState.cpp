#include "pch.h"
#include "CSalAttackState.h"
#include "CMonster.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CSalAttackBox.h"
#include "CTimeManager.h"
CSalAttackState::CSalAttackState()
	:m_attackCount(0)
	, m_attackAccTime(0)
	, m_bulletCount(0)
	, m_curAttackSpeed(0)
	, m_initAttackSpeed(0)
	, m_initInterval(0)
{

}

CSalAttackState::~CSalAttackState()
{
}

void CSalAttackState::Enter()
{
	m_initAttackSpeed = GetMonster()->GetInfo().attackSpeed;
	m_curAttackSpeed = m_initAttackSpeed * (1 - m_attackCount * 0.2f);
	m_interval = m_initAttackSpeed * (1 - m_attackCount * 0.2f);
	m_attackAccTime = m_interval;
	if (m_attackCount > 0)
		((CSalAttackBox*)GetMonster()->GetAttackBox())->SetBulletSpeed(600.f * (1 - m_attackCount * 0.2f));
}

void CSalAttackState::Exit()
{
	m_bulletCount = 0;
	m_attackAccTime = 0;
	if (m_attackCount > 2)
		m_attackCount = 0;
}

void CSalAttackState::Update()
{
	m_attackAccTime += fDT;

	if (m_bulletCount < 4)
	{
		if (m_attackAccTime >= m_interval)
		{
			GetMonster()->GetAnimator()->Play(L"POTATO_SHOOT", false);
			if (GetMonster()->GetAnimator()->GetCurrentAnim()->GetCurrentFrame() == 13)
			{
			
				GetMonster()->GetAttackBox()->Fire();
				m_attackAccTime = 0;
				++m_bulletCount;
			}
		}
	}
	if (GetMonster()->GetAnimator()->GetCurrentAnim()->IsFinish())
	{
		GetMonster()->GetAnimator()->GetCurrentAnim()->SetFrame(0);
		if (m_bulletCount > 3)
		{
			ChangeAIState(GetAI(), MON_STATE::IDLE);
			++m_attackCount;
		}

	}
}
