#pragma once
#include "CPlayerState.h"
class CPlayerAttackState :
    public CPlayerState
{
public:
    CPlayerAttackState();
    ~CPlayerAttackState();
public:
    // CPlayerState을(를) 통해 상속됨
    virtual void Enter() override;

    virtual void Exit() override;

    virtual void Update() override;
protected:
    virtual void updateSubState();
    virtual void updateAnimation();
};

