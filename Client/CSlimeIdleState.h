#pragma once
#include "CState.h"
class CSlimeIdleState :
    public CState
{
public:
    CSlimeIdleState();
    ~CSlimeIdleState();
public:
    virtual void Enter();
    virtual void Update();
    virtual void Exit();

private:
    float m_accTime;
};


