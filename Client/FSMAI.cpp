#include "pch.h"
#include "FSMAI.h"
#include "CState.h"
FSMAI::FSMAI()
	: m_currentState(nullptr)
	, m_prevState(nullptr)
{
}

FSMAI::~FSMAI()
{
	Safe_Delete_Map(m_StateMap);
}

void FSMAI::Update()
{
	m_currentState->Update();
}

void FSMAI::AddState(CState* _state)
{
	CState* state = GetState(_state->GetState());
	if (nullptr != state)
		return;
	m_StateMap.insert(make_pair(_state->GetState(), _state));
	_state->m_ai = this;
}

CState* FSMAI::GetState(MON_STATE _state)
{
	unordered_map<MON_STATE, CState*>::iterator iter = m_StateMap.find(_state);

	if (iter == m_StateMap.end())
		return nullptr;

	return iter->second;
}

void FSMAI::SetCurrentState(MON_STATE _state)
{
	m_currentState = GetState(_state);
	m_currentState->Enter();
	assert(m_currentState);
}

void FSMAI::ChangeState(MON_STATE _nextState)
{
	m_prevState = m_currentState;
	m_currentState = GetState(_nextState);
	assert(m_prevState != m_currentState);

	m_prevState->Exit();
	m_currentState->Enter();
}
