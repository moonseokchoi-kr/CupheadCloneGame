#pragma once
#include "CPlayerState.h"
class CPlayerAttackState :
    public CPlayerState
{
public:
    CPlayerAttackState();
    ~CPlayerAttackState();
public:
    // CPlayerState��(��) ���� ��ӵ�
    virtual void Enter() override;

    virtual void Exit() override;

    virtual void Update() override;
protected:
    virtual void updateSubState();
    virtual void updateAnimation();
};

