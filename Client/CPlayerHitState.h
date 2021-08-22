#pragma once
#include "CPlayerState.h"
class CPlayerHitState :
    public CPlayerState
{
public:
    CPlayerHitState();
    ~CPlayerHitState();
public:
    // CPlayerState을(를) 통해 상속됨
    virtual void Enter() override;

    virtual void Exit() override;

    virtual void Update() override;

private:
    float m_accTime;
    float m_mainTime;
};

