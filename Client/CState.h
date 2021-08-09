#pragma once

class FSMAI;
class CMonster;


class CState
{
public:
	FSMAI* GetAI() { return m_ai; }
	MON_STATE GetState() { return m_state; }
	CMonster* GetMonster();
public:
	virtual void Enter() = 0;
	virtual void Exit() = 0;
	virtual void Update() = 0;

public:
	CState(MON_STATE _state);
	virtual ~CState();
private:
	FSMAI* m_ai;
	MON_STATE m_state;

	friend class FSMAI;
	
};

