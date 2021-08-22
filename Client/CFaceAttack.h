#pragma once
#include "CBullet.h"
class CFaceAttack :
    public CBullet
{
public:
    CFaceAttack();
    ~CFaceAttack();
    CLONE(CFaceAttack);
public:
    // CBullet을(를) 통해 상속됨
    virtual void Update() override;
    virtual void Render(HDC _dc) override;
    
public:
    virtual void OnCollisionEnter(CCollider* _col) override;
    virtual void OnCollision(CCollider* _col) override;
    bool isAttackFinish() { return m_isAttackFinish; }
public:
    float m_mainTime;
    float m_initTime;
    float m_accTime;
    float m_maxSize;

    bool m_isAttackFinish;
};

