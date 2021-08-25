#include "pch.h"
#include "CDeathState.h"
#include "CMonster.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CMonsterHitBox.h"
#include "CCollider.h"
CDeathState::CDeathState(const wstring& _anim)
	:CState(MON_STATE::DEAD)
	,m_animName(_anim)
	
{
}

CDeathState::CDeathState(const wstring& _anim, const wstring& _anim1)
	:CState(MON_STATE::DEAD)
	,m_animName(_anim)
	,m_animName1(_anim1)
{
}

CDeathState::~CDeathState()
{
}

void CDeathState::Enter()
{
	GetMonster()->GetHitBox()->GetCollider()->SetAvaCollide(false);
	if (!m_animName.empty())
	{
		GetMonster()->GetAnimator()->Play(m_animName, false);
		GetMonster()->GetCollider()->SetAvaCollide(false);
	}	
	else
		return;
}

void CDeathState::Exit()
{
}

void CDeathState::Update()
{
	if (GetMonster()->GetAnimator()->GetCurrentAnim()->IsFinish())
	{
		if (!m_animName1.empty())
		{
			GetMonster()->GetAnimator()->Play(m_animName1, false);
			if (GetMonster()->GetAnimator()->GetCurrentAnim()->IsFinish())
			{
				DeleteObject(GetMonster());
			}
		}
		else
		{
			DeleteObject(GetMonster());
		}
		
	}
}
