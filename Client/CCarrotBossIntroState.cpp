#include "pch.h"
#include "CCarrotBossIntroState.h"

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
	ChangeAIState(GetAI(), MON_STATE::ATTACK);
}
