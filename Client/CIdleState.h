#pragma once
#include "CState.h"
class CIdleState :
    public CState
{
public:
    CIdleState();
    ~CIdleState();
public:
    // CState��(��) ���� ��ӵ�
    virtual void Enter() override;
    virtual void Exit() override;
    virtual void Update() override;
};

