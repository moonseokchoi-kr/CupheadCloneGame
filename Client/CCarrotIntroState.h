#pragma once
#include "CState.h"
class CCarrotIntroState :
    public CState
{
public:
    CCarrotIntroState();
    ~CCarrotIntroState();
public:
    // CState��(��) ���� ��ӵ�
    virtual void Enter() override;

    virtual void Exit() override;

    virtual void Update() override;

};

