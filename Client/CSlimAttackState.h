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
    // CAttackState을(를) 통해 상속됨
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
    float m_jumpCount; //현재 점프 횟수
    float m_maxJumpCount; //최대 점프 횟수
    float m_limitHealth;
    Vec2 m_diff;
    bool m_isAttack;//현재 공격패턴이 진행중인지

    SLIME_SUB_STATE m_prevSubState;
    SLIME_SUB_STATE m_currSubState;

    ATTACK_PATT m_prevPatt;
    ATTACK_PATT m_currentPatt; //랜덤함수로 설정된 패턴
};

