#pragma once
#include "CState.h"
class CIntroState :
    public CState
{
public:
    CIntroState();
    virtual ~CIntroState();
public:
    // CState��(��) ���� ��ӵ�
    virtual void Enter() override;

    virtual void Exit() override;

    virtual void Update() override;
public:
private:
};

