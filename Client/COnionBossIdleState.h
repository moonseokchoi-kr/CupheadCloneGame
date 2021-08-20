#pragma once
#include "CState.h"
class COnionBossIdleState :
    public CState
{
public:
    COnionBossIdleState();
    ~COnionBossIdleState();
public:
    // CState을(를) 통해 상속됨
    virtual void Enter() override;

    virtual void Exit() override;

    virtual void Update() override;

};

