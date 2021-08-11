#pragma once
#include "CTile.h"
class CGroundTile :
    public CTile
{
public:
    CGroundTile();
    ~CGroundTile();
    CLONE(CGroundTile);
public:
    virtual void Update() override;
    virtual void Render(HDC _dc) override;

    virtual void OnCollision(CCollider* _col);
    virtual void OnCollisionEnter(CCollider* _col);
    virtual void OnCollisionExit(CCollider* _col);
};

