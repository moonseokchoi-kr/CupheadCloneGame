#pragma once
#include "CAttackState.h"
class CSlimAttackState :
    public CAttackState
{
public:
    CSlimAttackState();
    ~CSlimAttackState();
public:
    // CAttackState��(��) ���� ��ӵ�
    virtual void Enter() override;

    virtual void Exit() override;

    virtual void Update() override;

public:
    
};

