#pragma once
#include "CAttackState.h"
class CSlimAttackState :
    public CAttackState
{
public:
    CSlimAttackState();
    ~CSlimAttackState();
public:
    // CAttackState을(를) 통해 상속됨
    virtual void Enter() override;

    virtual void Exit() override;

    virtual void Update() override;

public:
    
};

