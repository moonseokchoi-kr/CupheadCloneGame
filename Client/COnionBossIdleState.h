#pragma once
#include "CState.h"
class COnionBossIdleState :
    public CState
{
public:
    COnionBossIdleState();
    ~COnionBossIdleState();
public:
    // CState��(��) ���� ��ӵ�
    virtual void Enter() override;

    virtual void Exit() override;

    virtual void Update() override;

};

