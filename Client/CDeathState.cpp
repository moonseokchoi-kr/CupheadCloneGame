#include "pch.h"
#include "CDeathState.h"
#include "CMonster.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
CDeathState::CDeathState(const wstring& _anim)
	:CState(MON_STATE::DEAD)
	,m_animName(_anim)
	
{
}

CDeathState::~CDeathState()
{
}

void CDeathState::Enter()
{

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
		DeleteObject(GetMonster());
	}
}
