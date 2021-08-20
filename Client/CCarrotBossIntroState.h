#pragma once
#include "CState.h"
class CCarrotBossIntroState :
    public CState
{
public:
    CCarrotBossIntroState();
    ~CCarrotBossIntroState();
public:

    // CState을(를) 통해 상속됨
    virtual void Enter() override;

    virtual void Exit() override;

    virtual void Update() override;

};

