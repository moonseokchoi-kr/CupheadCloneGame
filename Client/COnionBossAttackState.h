#pragma once
#include "CAttackState.h"
class COnionBossAttackState :
    public CAttackState
{
public:
    COnionBossAttackState();
    ~COnionBossAttackState();
public:
    // CAttackState을(를) 통해 상속됨
    virtual void Enter() override;

    virtual void Exit() override;

    virtual void Update() override;

private:
    float m_accTime;
    float m_attackCount;
    float m_maxattackCount;
};

