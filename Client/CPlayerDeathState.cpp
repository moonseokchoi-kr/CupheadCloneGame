#include "pch.h"
#include "CPlayerDeathState.h"

CPlayerDeathState::CPlayerDeathState()
	:CPlayerState(PLAYER_STATE::DEAD)
{
}

CPlayerDeathState::~CPlayerDeathState()
{
}

void CPlayerDeathState::Enter()
{
}

void CPlayerDeathState::Exit()
{
}

void CPlayerDeathState::Update()
{
	DeleteObject(GetPlayer());
}
