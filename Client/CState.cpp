#include "pch.h"
#include "CState.h"
#include "CSound.h"
#include "CResourceManager.h"
#include "FSMAI.h"
CState::CState(MON_STATE _state)
	:m_stateAccTime(_state)
	, m_ai(nullptr)
	,m_sfx(nullptr)
{
}

CState::~CState()
{
}
CMonster* CState::GetMonster()
{
	return m_ai->GetOwner();
}

void CState::SetSFX(const wstring& _name)
{
	m_sfx = CResourceManager::GetInst()->FindSound(_name);
}


