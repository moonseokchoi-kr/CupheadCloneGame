#pragma once
#include "CAttackState.h"



class CCarrotBossAttackState :
    public CAttackState
{
public:
    CCarrotBossAttackState();
    ~CCarrotBossAttackState();
public:
    // CAttackState��(��) ���� ��ӵ�
    virtual void Enter() override;

    virtual void Exit() override;

    virtual void Update() override;
protected:
    virtual void updateAnimation() override;
    void updateSubState();
private:
    float m_attackChangeinterval;
    float m_interval;
    float m_beamInterval;
    float m_attackCount;
    float m_maxAttackCount;
    float m_beamAttackCount;
    float m_beamAccTime;
    float m_accTime;
    float m_changeAccTime;
};

