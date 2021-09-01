#pragma once

class FSMAI;
class CMonster;
class CSound;

class CState
{

public:
	CState(MON_STATE _state);
	virtual ~CState();
public:
	FSMAI* GetAI() { return m_ai; }
	MON_STATE GetState() { return m_stateAccTime; }
	CMonster* GetMonster();
public:
	virtual void Enter() = 0;
	virtual void Exit() = 0;
	virtual void Update() = 0;
public:
	void SetSFX(const wstring& _name);
	CSound* GetSFX() { return m_sfx; }
protected:
	virtual void updateAnimation() {}

private:
	FSMAI* m_ai;
	MON_STATE m_stateAccTime;
	CSound* m_sfx;
	friend class FSMAI;
	
};

