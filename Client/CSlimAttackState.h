#pragma once
#include "CAttackState.h"

enum class SLIME_SUB_STATE
{
    GROUND,
    AIR,
    TURN,
    AIR_TURN,
};
class CSlimAttackState :
    public CAttackState
{
public:
    CSlimAttackState();
    ~CSlimAttackState();
public:
    // CAttackState��(��) ���� ��ӵ�
    virtual void Enter() override;

    virtual void Exit() override;

    virtual void Update() override;
private:
    void updateAnimation();
    void updateSubState();
private:
    void getTargetDiff();
    void randomPatt();
private:
    float m_accTime;
    float m_jumpCount; //���� ���� Ƚ��
    float m_maxJumpCount; //�ִ� ���� Ƚ��
    float m_limitHealth;
    Vec2 m_diff;
    bool m_isAttack;//���� ���������� ����������

    SLIME_SUB_STATE m_prevSubState;
    SLIME_SUB_STATE m_currSubState;

    ATTACK_PATT m_prevPatt;
    ATTACK_PATT m_currentPatt; //�����Լ��� ������ ����
};

