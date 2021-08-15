#include "pch.h"
#include "CPlayerStateMachine.h"
#include "CPlayerState.h"

CPlayerStateMachine::CPlayerStateMachine()
	:m_currentState(nullptr)
	,m_prevState(nullptr)
{
}

CPlayerStateMachine::~CPlayerStateMachine()
{
	Safe_Delete_Map(m_stateMap);
}


void CPlayerStateMachine::Update()
{
	m_currentState->Update();
}

void CPlayerStateMachine::AddState(CPlayerState* _state)
{
	CPlayerState* state = GetState(_state->GetState());
	if (nullptr != state)
		return;
	m_stateMap.insert(make_pair(_state->GetState(), _state));
	_state->m_ai = this;
}

CPlayerState* CPlayerStateMachine::GetState(PLAYER_STATE _state)
{
	unordered_map<PLAYER_STATE, CPlayerState*>::iterator iter = m_stateMap.find(_state);
	if (m_stateMap.end() == iter)
		return nullptr;
	return iter->second;
}

void CPlayerStateMachine::SetCurrentState(PLAYER_STATE _state)
{
	m_currentState = GetState(_state);
	assert(m_currentState);
}

void CPlayerStateMachine::ChangeState(PLAYER_STATE _nextState)
{
	m_prevState = m_currentState;
	m_currentState = GetState(_nextState);
	assert(m_prevState != m_currentState);
	m_prevState->Exit();
	m_currentState->Enter();
}
