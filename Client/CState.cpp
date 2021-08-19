#include "pch.h"
#include "CState.h"
#include "FSMAI.h"
CMonster* CState::GetMonster()
{
	return m_ai->GetOwner();
}

CState::CState(MON_STATE _state)
	:m_stateAccTime(_state)
	,m_ai(nullptr)
{
}

CState::~CState()
{
}
