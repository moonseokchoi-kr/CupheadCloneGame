#pragma once
#include "CState.h"
class CIdleState :
    public CState
{
public:
    CIdleState();
    ~CIdleState();
public:
    // CState을(를) 통해 상속됨
    virtual void Enter() override;
    virtual void Exit() override;
    virtual void Update() override;
};

