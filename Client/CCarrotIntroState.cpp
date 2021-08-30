#include "pch.h"
#include "CCarrotIntroState.h"
#include "CMonster.h"
#include "CMonsterHitBox.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CCollider.h"
CCarrotIntroState::CCarrotIntroState()
	:CState(MON_STATE::INTRO)
{
}

CCarrotIntroState::~CCarrotIntroState()
{
}

void CCarrotIntroState::Enter()
{
}

void CCarrotIntroState::Exit()
{
	GetMonster()->GetHitBox()->GetCollider()->SetAvaCollide(true);
}

void CCarrotIntroState::Update()
{
	GetMonster()->GetHitBox()->GetCollider()->SetAvaCollide(false);
	bool isFinish = GetMonster()->GetAnimator()->GetCurrentAnim()->IsFinish();
	if (isFinish)
		ChangeAIState(GetAI(), MON_STATE::ATTACK);
}
