#pragma once
#include "CBullet.h"


class CSalBullet :
    public CBullet
{
public:
    CSalBullet();
    ~CSalBullet();
    CLONE(CSalBullet);
public:
    virtual void Update();
    virtual void Render(HDC _dc);
    virtual void OnCollisionEnter(CCollider* _col);
    virtual void OnCollision(CCollider* _col);
    virtual void OnCollisionExit(CCollider* _col);
public:
    void SetAnim(wstring _anim) { m_animName = _anim; }
private:
    wstring m_animName;
};

