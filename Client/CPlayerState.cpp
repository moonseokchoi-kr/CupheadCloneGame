#include "pch.h"
#include "CPlayerState.h"
#include "CPlayerStateMachine.h"

CPlayerState::CPlayerState(PLAYER_STATE _state)
	:m_state(_state)
	,m_ai(nullptr)
{
}

CPlayerState::~CPlayerState()
{
}
CPlayer* CPlayerState::GetPlayer()
{
	return m_ai->GetOwner();
}


