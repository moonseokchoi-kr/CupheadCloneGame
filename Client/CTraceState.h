#pragma once
#include "CState.h"
class CTraceState :
    public CState
{
public:
    CTraceState();
    ~CTraceState();
public:
    // CState��(��) ���� ��ӵ�
    virtual void Enter() override;
    virtual void Exit() override;
    virtual void Update() override;
};

