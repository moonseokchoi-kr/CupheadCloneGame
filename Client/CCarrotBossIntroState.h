#pragma once
#include "CState.h"
class CCarrotBossIntroState :
    public CState
{
public:
    CCarrotBossIntroState();
    ~CCarrotBossIntroState();
public:

    // CState��(��) ���� ��ӵ�
    virtual void Enter() override;

    virtual void Exit() override;

    virtual void Update() override;

};

