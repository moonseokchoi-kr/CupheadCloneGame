#pragma once
#include "CPlayerState.h"
class CPlayerIntroState :
    public CPlayerState
{
public:
    CPlayerIntroState();
    ~CPlayerIntroState();
public:
    // CPlayerState��(��) ���� ��ӵ�
    virtual void Enter() override;

    virtual void Exit() override;

    virtual void Update() override;
};

