#pragma once

class CPlayer;
class CPlayerState;

class CPlayerStateMachine
{
public:
	CPlayerStateMachine();
	~CPlayerStateMachine();

public:
	void Update();
	void AddState(CPlayerState* _state);
	CPlayerState* GetState(PLAYER_STATE _state);
	CPlayer* GetOwner() { return m_owner; }
	void SetCurrentState(PLAYER_STATE _state);
	void ChangeState(PLAYER_STATE _nextState);
private:
	unordered_map<PLAYER_STATE, CPlayerState*> m_stateMap;
	CPlayer* m_owner;
	CPlayerState* m_currentState;
	CPlayerState* m_prevState;

	friend class CPlayer;
};

