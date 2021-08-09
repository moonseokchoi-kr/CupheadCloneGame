#pragma once
#include "CState.h"
class CTraceState :
    public CState
{
public:
    CTraceState();
    ~CTraceState();
public:
    // CState을(를) 통해 상속됨
    virtual void Enter() override;
    virtual void Exit() override;
    virtual void Update() override;
};

