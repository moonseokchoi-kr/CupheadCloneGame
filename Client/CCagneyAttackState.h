#pragma once
#include "CAttackState.h"
class CCagneyAttackState :
    public CAttackState
{
public:
	CCagneyAttackState();
	~CCagneyAttackState();
public:
	// CAttackState을(를) 통해 상속됨
	virtual void Enter() override;

	virtual void Exit() override;

	virtual void Update() override;
protected:
	virtual void updateAnimation() override;
	void updateSubState();
private:
	float m_interval;
	float m_seedInterval;
	float m_attackCount;
	float m_maxAttackCount;
	float m_seedAccTime;
	float m_accTime;

	ATTACK_PATT m_currentPatt;
};

