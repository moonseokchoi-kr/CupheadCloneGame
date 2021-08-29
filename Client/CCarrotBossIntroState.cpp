#include "pch.h"
#include "CCarrotBossIntroState.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CMonster.h"
CCarrotBossIntroState::CCarrotBossIntroState()
	:CState(MON_STATE::INTRO)
{
}

CCarrotBossIntroState::~CCarrotBossIntroState()
{
}

void CCarrotBossIntroState::Enter()
{
}

void CCarrotBossIntroState::Exit()
{
}

void CCarrotBossIntroState::Update()
{
	if(GetMonster()->GetAnimator()->GetCurrentAnim()->IsFinish())
		ChangeAIState(GetAI(), MON_STATE::ATTACK);
}
