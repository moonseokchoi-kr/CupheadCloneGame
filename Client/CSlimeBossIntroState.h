#pragma once
#include "CState.h"
class CSlimeBossIntroState :
    public CState
{
public:
    CSlimeBossIntroState();
    ~CSlimeBossIntroState();
public:

    // CState��(��) ���� ��ӵ�
    virtual void Enter() override;

    virtual void Exit() override;

    virtual void Update() override;

};

