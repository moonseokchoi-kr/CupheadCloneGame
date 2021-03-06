#pragma once
#include "CPlayerState.h"
class CPlayerDeathState :
    public CPlayerState
{
public:
    CPlayerDeathState();
    ~CPlayerDeathState();
public:
    // CPlayerState을(를) 통해 상속됨
    virtual void Enter() override;

    virtual void Exit() override;

    virtual void Update() override;
};

