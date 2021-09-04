#include "pch.h"
#include "CPlayerDeathState.h"
#include "CPlayer.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CPlayerHitBox.h"
#include "CSound.h"
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

	SetSFX(L"PLAYER_DEATH");
	GetSFX()->Play(false);
	GetSFX()->SetPosition(50.f);
	GetSFX()->SetVolume(100.f);
}

void CPlayerDeathState::Exit()
{
}

void CPlayerDeathState::Update()
{

}
