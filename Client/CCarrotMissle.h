#pragma once
#include "CBullet.h"

class CPlayer;

class CCarrotMissle :
    public CBullet
{
public:
    CCarrotMissle();
    ~CCarrotMissle();
    CLONE(CCarrotMissle);
public:
    // CBullet을(를) 통해 상속됨
    virtual void Update() override;
    virtual void Render(HDC _dc) override;
    virtual void OnCollisionEnter(CCollider* _col)  override;
    virtual void OnCollision(CCollider* _col) override;
    virtual void OnCollisionExit(CCollider* _col) override;

public:
    void SetTarget(CPlayer* _target) { m_target = _target; }
private:
    CObject* m_target;
    Vec2 m_maxAngle;

};

