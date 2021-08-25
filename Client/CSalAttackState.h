#pragma once
#include "CAttackState.h"
class CSalAttackState :
    public CAttackState
{
public:
    CSalAttackState();
    ~CSalAttackState();
public:
    // CAttackState을(를) 통해 상속됨
    virtual void Enter() override;

    virtual void Exit() override;

    virtual void Update() override;
private:
    float m_initAttackSpeed;
    float m_curAttackSpeed;
    int m_bulletCount;
    float m_attackCount;
    float m_attackAccTime;
    float m_interval;
    float m_initInterval;
};

