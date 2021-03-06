#pragma once
#include "CState.h"
class CIntroState :
    public CState
{
public:
    CIntroState();
    virtual ~CIntroState();
public:
    // CState을(를) 통해 상속됨
    virtual void Enter() override;

    virtual void Exit() override;

    virtual void Update() override;
public:
private:
};

