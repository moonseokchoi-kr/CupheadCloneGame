#pragma once
#include "CPlayerState.h"
class CPlayerDeathState :
    public CPlayerState
{
public:
    CPlayerDeathState();
    ~CPlayerDeathState();
public:
    // CPlayerState��(��) ���� ��ӵ�
    virtual void Enter() override;

    virtual void Exit() override;

    virtual void Update() override;
};

