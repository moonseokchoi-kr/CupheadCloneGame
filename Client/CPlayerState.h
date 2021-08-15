#pragma once

class CPlayer;
class CPlayerStateMachine;


class CPlayerState
{
public:
	CPlayerState(PLAYER_STATE _state);
	virtual ~CPlayerState();

public:
	CPlayerStateMachine* GetAI() { return m_ai; }
	PLAYER_STATE GetState() { return m_state; }
	CPlayer* GetPlayer();
public:
	virtual void Enter() = 0;
	virtual void Exit() = 0;
	virtual void Update() = 0;

private:
	CPlayerStateMachine* m_ai;
	PLAYER_STATE m_state;

	friend class CPlayerStateMachine;
};

