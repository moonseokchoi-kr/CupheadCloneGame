#pragma once
#include "CPlayerState.h"
class CPlayerDashState :
    public CPlayerState
{
public:
    CPlayerDashState();
    ~CPlayerDashState();
public:
    // CPlayerState��(��) ���� ��ӵ�
    virtual void Enter() override;

    virtual void Exit() override;

    virtual void Update() override;
private:


};

