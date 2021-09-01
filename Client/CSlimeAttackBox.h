#pragma once
#include "CAttackBox.h"
class CSlimeAttackBox :
    public CAttackBox
{
public:
    CSlimeAttackBox();
    ~CSlimeAttackBox();
    CLONE(CSlimeAttackBox);
public:
    virtual void Start() override;
    virtual void Update() override;
    // CAttackBox을(를) 통해 상속됨
    virtual void Fire() override;
    virtual void Render(HDC _dc) override;
    virtual void OnCollisionEnter(CCollider* _col) override;
    virtual void OnCollision(CCollider* _col) override;
    virtual void OnCollisionExit(CCollider* _col) override;
public:
    Vec2 GetOffset() { return m_offset; }
    void SetOffset(Vec2 _v) { m_offset = _v; }
    ATTACK_PATT GetCurrentPatt() { return m_currentAttackPatt; }
    void SetCurrentPatt(ATTACK_PATT _patt) { m_currentAttackPatt = _patt; }
    Vec2 GetTargetDiff();
public:
    Vec2 m_offset;
    float m_attackCount;
    
    ATTACK_PATT m_currentAttackPatt;
};

