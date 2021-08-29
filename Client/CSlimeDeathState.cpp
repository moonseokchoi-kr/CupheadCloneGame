#include "pch.h"
#include "CSlimeDeathState.h"
#include "CRigidBody.h"
#include "CMonsterHitBox.h"
#include "CCollider.h"
#include "CSlime.h"
#include "CAnimation.h"
#include "CAnimator.h"
CSlimeDeathState::CSlimeDeathState()
	:CState(MON_STATE::DEAD)
{
}

CSlimeDeathState::~CSlimeDeathState()
{
}

void CSlimeDeathState::Enter()
{
	GetMonster()->GetRigidBody()->SetActive(false);
	GetMonster()->GetHitBox()->GetCollider()->SetAvaCollide(false);
	Vec2 m_moveDir = GetMonster()->GetMoveDir();
	if (m_moveDir.x < 0)
	{
		GetMonster()->GetAnimator()->Play(L"LG_SLIME_DEATH_LEFT_1", false);
	}
	else
	{
		GetMonster()->GetAnimator()->Play(L"LG_SLIME_DEATH_RIGHT_1", false);
	}
}

void CSlimeDeathState::Exit()
{
}

void CSlimeDeathState::Update()
{
	if (GetMonster()->GetAnimator()->GetCurrentAnim()->IsFinish() && m_moveDir.x < 0)
	{
		GetMonster()->GetAnimator()->Play(L"LG_SLIME_DEATH_LEFT_2", false);
		if (GetMonster()->GetAnimator()->GetCurrentAnim()->IsFinish())
		{
			DeleteObject(GetMonster());
		}
	}
	else
	{
		GetMonster()->GetAnimator()->Play(L"LG_SLIME_DEATH_RIGHT_2", false);
		if (GetMonster()->GetAnimator()->GetCurrentAnim()->IsFinish())
		{
			DeleteObject(GetMonster());
		}
	}

}
