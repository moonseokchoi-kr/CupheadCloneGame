#pragma once
#include "CState.h"
class CSlimeBossIntroState :
    public CState
{
public:
    CSlimeBossIntroState();
    ~CSlimeBossIntroState();
public:

    // CState을(를) 통해 상속됨
    virtual void Enter() override;

    virtual void Exit() override;

    virtual void Update() override;

};

