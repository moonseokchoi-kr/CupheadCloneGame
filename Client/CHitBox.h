#include "CObject.h"
#pragma once
class CHitBox :
    public CObject
{
public:
    CHitBox();
    virtual ~CHitBox();
public:
    virtual void Start() override;
    virtual void Render(HDC _dc) override;
public:

    void SetOffset(Vec2 _v) { m_offset = _v; }
    Vec2 GetOffset() { return m_offset; }
private:
    Vec2 m_offset;
};

