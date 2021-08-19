#include "pch.h"
#include "CIntroState.h"
#include "CMonster.h"
#include "CAnimator.h"
#include "CAnimation.h"
CIntroState::CIntroState(wstring _anim)
	:CState(MON_STATE::INTRO)
	, m_animName(_anim)
{
}

CIntroState::~CIntroState()
{
}

void CIntroState::Enter()
{
	if (m_animName.empty())
		GetMonster()->GetAnimator()->Play(m_animName, false);
	else
		return;
}

void CIntroState::Exit()
{
}

void CIntroState::Update()
{
	bool isFinish = GetMonster()->GetAnimator()->GetCurrentAnim()->IsFinish();
	if (isFinish)
		ChangeAIState(GetAI(), MON_STATE::IDLE);
}
