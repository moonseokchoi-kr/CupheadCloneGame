#pragma once
#include "CState.h"
class CSlimeDeathState :
    public CState
{
public:
    CSlimeDeathState();
    ~CSlimeDeathState();
public:
    // CState을(를) 통해 상속됨
    virtual void Enter() override;

    virtual void Exit() override;

    virtual void Update() override;
private:
    Vec2 m_moveDir;
};

