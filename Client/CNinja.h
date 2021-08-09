#pragma once
#include "CObject.h"
class CNinja :
    public CObject
{
public:
    CNinja();
    ~CNinja();
public:
    // CObject을(를) 통해 상속됨
    virtual void Update() override;
    virtual void Render(HDC _dc);
    virtual void FinalUpdate();
    virtual void OnCollisionEnter(CCollider* _col);


    CLONE(CNinja);

private:
    void fire();
public:
    float m_fallingSpeed;
    float m_walkingSpeed;
    float m_distance;
    float m_acc;
    float m_attackTime;

    bool m_bGround;
    bool m_attack;
    bool m_changeAnimation;
    Vec2 m_moveDirection;

    float m_health;


};

