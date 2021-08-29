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
    // CAttackBox��(��) ���� ��ӵ�
    virtual void Fire() override;
    virtual void Render(HDC _dc) override;
    virtual void OnCollisionEnter(CCollider* _col) override;
    virtual void OnCollision(CCollider* _col) override;
    virtual void OnCollisionExit(CCollider* _col) override;
public:
    Vec2 GetOffset() { return m_offset; }
    void SetOffset(Vec2 _v) { m_offset = _v; }
    ATTACK_PATT GetCurrentPatt() { return m_currentAttackPatt; }
    Vec2 GetTargetDiff();
public:
    Vec2 m_offset;
    float m_attackCount;
    Vec2 m_diff;
    ATTACK_PATT m_currentAttackPatt;
};

