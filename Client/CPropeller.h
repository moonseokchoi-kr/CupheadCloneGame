#pragma once
#include "CGameObject.h"

class CGround;

class CPropeller :
    public CGameObject
{
public:
    CPropeller();
    ~CPropeller();
    CLONE(CPropeller);
public:
    virtual void Update();
    virtual void Render(HDC _dc);
    virtual void FinalUpdate();

    void SetParent(CGround* _parent) { m_parent = _parent; }
    void SetPosOffset(Vec2 _v) { m_offset = _v; }
private:
    CGround* m_parent;
    Vec2 m_offset;
};

