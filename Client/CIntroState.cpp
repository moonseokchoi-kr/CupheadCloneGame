#include "pch.h"
#include "CIntroState.h"
#include "CMonster.h"
#include "CMonsterHitBox.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CCollider.h"
CIntroState::CIntroState()
	:CState(MON_STATE::INTRO)
{

}

CIntroState::~CIntroState()
{
}

void CIntroState::Enter()
{

}

void CIntroState::Exit()
{
	GetMonster()->GetHitBox()->GetCollider()->SetAvaCollide(true);
}

void CIntroState::Update()
{
	GetMonster()->GetHitBox()->GetCollider()->SetAvaCollide(false);
	if (nullptr == GetMonster()->GetAnimator()->GetCurrentAnim())
		return;
	bool isFinish = GetMonster()->GetAnimator()->GetCurrentAnim()->IsFinish();
	if (isFinish)
		ChangeAIState(GetAI(), MON_STATE::IDLE);
}
