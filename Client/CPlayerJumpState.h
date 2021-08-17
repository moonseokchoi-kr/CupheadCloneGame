#pragma once
#include "CPlayerState.h"
class CPlayerJumpState :
    public CPlayerState
{
public:
    CPlayerJumpState();
    ~CPlayerJumpState();
public:
    // CPlayerState��(��) ���� ��ӵ�
    virtual void Enter() override;

    virtual void Exit() override;

    virtual void Update() override;

protected:
    virtual void updateAnimation();
    virtual void updateSubState();

private:
    float m_accTime;
};

