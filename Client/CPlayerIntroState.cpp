#include "pch.h"
#include "CPlayerIntroState.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CPlayerHitBox.h"
#include "CCollider.h"
#include "CPlayer.h"
CPlayerIntroState::CPlayerIntroState()
	:CPlayerState(PLAYER_STATE::INTRO)
{
}

CPlayerIntroState::~CPlayerIntroState()
{
}

void CPlayerIntroState::Enter()
{
}

void CPlayerIntroState::Update()
{
	GetPlayer()->GetHitBox()->GetCollider()->SetAvaCollide(false);
	if (GetPlayer()->GetAnimator()->GetCurrentAnim()->IsFinish() && GetPlayer()->GetAnimator()->GetCurrentAnim()->GetName() == L"PLAYER_INTRO_1")
	{
		GetPlayer()->GetAnimator()->Play(L"PLAYER_INTRO_2", false);
	}
	else if (GetPlayer()->GetAnimator()->GetCurrentAnim()->IsFinish() && GetPlayer()->GetAnimator()->GetCurrentAnim()->GetName() == L"PLAYER_INTRO_2")
	{
		ChangePlayerState(GetAI(), PLAYER_STATE::IDLE);
	}
}

void CPlayerIntroState::Exit()
{
	GetPlayer()->GetHitBox()->GetCollider()->SetAvaCollide(true);
}


