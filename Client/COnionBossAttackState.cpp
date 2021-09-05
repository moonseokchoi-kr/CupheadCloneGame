#include "pch.h"
#include "COnionBossAttackState.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "COnionBossAttackBox.h"
#include "COllieBullb.h"
#include "CSound.h"
#include "CVFXObject.h"
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
	SetSFX(L"ONION_CRYING");
	GetSFX()->SetPosition(50.f);
	GetSFX()->SetVolume(100.f);
	GetMonster()->GetVFX()->SetType(VFX_TYPE::BIG_TEAR_RIGHT);
	((COllieBullb*)GetMonster())->GetBigTear()->SetType(VFX_TYPE::BIG_TEAR_LEFT);
	
}

void COnionBossAttackState::Exit()
{
	m_accTime = 0;
	m_attackCount = 0;
	GetSFX()->Stop(true);
}

void COnionBossAttackState::Update()
{
	m_accTime += fDT;

	if (GetMonster()->GetVFX()->GetAnimator()->GetCurrentAnim()->GetCurrentFrame() == 9)
	{
		GetMonster()->GetVFX()->GetAnimator()->GetCurrentAnim()->SetFrame(4);
		((COllieBullb*)GetMonster())->GetBigTear()->GetAnimator()->GetCurrentAnim()->SetFrame(4);
	}
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
