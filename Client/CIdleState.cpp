#include "pch.h"
#include "CIdleState.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CMonsterHitBox.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CSceneManager.h"
#include "CTimeManager.h"
CIdleState::CIdleState(wstring _anim)
	:CState(MON_STATE::IDLE)
	, m_animName(_anim)
{
}

CIdleState::~CIdleState()
{
}

void CIdleState::Enter()
{
	if (!m_animName.empty())
	{
		GetMonster()->GetAnimator()->Play(m_animName, true);
		GetMonster()->GetHitBox()->GetCollider()->SetAvaCollide(false);
	}
		
	else
		return;
}

void CIdleState::Exit()
{
	m_accTime = 0;
	GetMonster()->GetAnimator()->GetCurrentAnim()->SetFrame(0);
}

void CIdleState::Update()
{
	
	if (!GetMonster()->GetTarget())
		return;
	m_accTime += fDT;
	if (m_accTime >= GetMonster()->GetInfo().attackSpeed)
	{
		ChangeAIState(GetAI(), MON_STATE::ATTACK);
	}
	
	
}
