#include "pch.h"
#include "CSlimeBossIntroState.h"
#include "CAnimator.h"
#include "CRigidBody.h"
#include "CMonsterHitBox.h"
#include "CCollider.h"
#include "CAnimation.h"
#include "CSlime.h"
CSlimeBossIntroState::CSlimeBossIntroState()
	:CState(MON_STATE::INTRO)
{
}

CSlimeBossIntroState::~CSlimeBossIntroState()
{
}

void CSlimeBossIntroState::Enter()
{

}

void CSlimeBossIntroState::Exit()
{
	GetMonster()->GetRigidBody()->SetActive(true);
	GetMonster()->GetHitBox()->GetCollider()->SetAvaCollide(true);
	if (((CSlime*)GetMonster())->GetCurrentPhase() == PHASE::PHASE2)
	{

		GetMonster()->GetHitBox()->GetCollider()->SetScale(Vec2(320.f, 300.f));
		GetMonster()->GetCollider()->SetScale(Vec2(360.f, 340.f));
	}

}

void CSlimeBossIntroState::Update()
{
	GetMonster()->GetRigidBody()->SetActive(false);
	GetMonster()->GetHitBox()->GetCollider()->SetAvaCollide(false);
	if (GetMonster()->GetAnimator()->GetCurrentAnim()->IsFinish())
	{
		if (GetMonster()->GetAnimator()->GetCurrentAnim()->GetName() == L"SLIME_MORPH_RIGHT_1")
		{
			GetMonster()->GetAnimator()->Play(L"SLIME_MORPH_RIGHT_2", false);
		}
		else if (GetMonster()->GetAnimator()->GetCurrentAnim()->GetName() == L"SLIME_MORPH_LEFT_1" )
		{
			GetMonster()->GetAnimator()->Play(L"SLIME_MORPH_LEFT_2", false);
		}
		else if (GetMonster()->GetAnimator()->GetCurrentAnim()->GetName() == L"SLIME_INTRO_1")
		{
			GetMonster()->GetAnimator()->Play(L"SLIME_INTRO_2", false);
		}
		else if (GetMonster()->GetAnimator()->GetCurrentAnim()->GetName() == L"SLIME_INTRO_2")
		{
			GetMonster()->GetAnimator()->Play(L"SLIME_INTRO_3", false);
		}
		else
		{
			ChangeAIState(GetAI(), MON_STATE::ATTACK);
		}
	}
}
