#pragma once
#include "CBullet.h"
class CBeamMissile :
    public CBullet
{
public:
    CBeamMissile();
    ~CBeamMissile();
    CLONE(CBeamMissile);
public:

    // CBullet을(를) 통해 상속됨
    virtual void Start() override;
    virtual void Update() override;
    virtual void Render(HDC _dc) override;

    virtual void OnCollisionEnter(CCollider* _col) override;
    virtual void OnCollision(CCollider* _col);
    virtual void OnCollisionExit(CCollider* _col);
private:
    Vec2 m_targetPos;
    Vec2 m_diff;
};

