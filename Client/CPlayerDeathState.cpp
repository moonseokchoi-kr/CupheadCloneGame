#include "pch.h"
#include "CPlayerDeathState.h"
#include "CPlayer.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CPlayerHitBox.h"
#include "CCollider.h"
CPlayerDeathState::CPlayerDeathState()
	:CPlayerState(PLAYER_STATE::DEAD)
{
}

CPlayerDeathState::~CPlayerDeathState()
{
}

void CPlayerDeathState::Enter()
{
	GetPlayer()->GetHitBox()->GetCollider()->SetAvaCollide(false);

	GetPlayer()->GetAnimator()->Play(L"PLAYER_DEATH",false);
}

void CPlayerDeathState::Exit()
{
}

void CPlayerDeathState::Update()
{
	if(GetPlayer()->GetAnimator()->GetCurrentAnim()->IsFinish())
		DeleteObject(GetPlayer());
}
