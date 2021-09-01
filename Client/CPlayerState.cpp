#include "pch.h"
#include "CPlayerState.h"
#include "CPlayerStateMachine.h"
#include "CResourceManager.h"
#include "CSound.h"
CPlayerState::CPlayerState(PLAYER_STATE _state)
	:m_state(_state)
	,m_ai(nullptr)
	,m_subState(PLAYER_STATE::IDLE)
{
}

CPlayerState::~CPlayerState()
{
}
CPlayer* CPlayerState::GetPlayer()
{
	return m_ai->GetOwner();
}

void CPlayerState::SetSFX(const wstring& _name)
{
	m_sfx = CResourceManager::GetInst()->FindSound(_name);
}


