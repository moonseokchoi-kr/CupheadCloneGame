#pragma once
#include "CIdleState.h"
class CSlimeIdleState :
    public CIdleState
{
public:
    CSlimeIdleState();
    ~CSlimeIdleState();
public:
    virtual void Enter();
    virtual void Update();
    virtual void Exit();

};

