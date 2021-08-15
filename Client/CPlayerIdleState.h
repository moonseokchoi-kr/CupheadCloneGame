#pragma once
#include "CPlayerState.h"
class CPlayerIdleState :
    public CPlayerState
{
public:
    CPlayerIdleState();
    ~CPlayerIdleState();
public:
    // CPlayerState��(��) ���� ��ӵ�
    virtual void Enter() override;

    virtual void Exit() override;

    virtual void Update() override;

protected:
    virtual void updateSubState();
    virtual void updateAnimation();
};

