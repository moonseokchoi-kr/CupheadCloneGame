#pragma once
#include "CObject.h"
enum class VFX_TYPE
{
	DASH_BOMB,
	JUMP_DUST,
    LEVEL_START,
    YOU_DIED,
    SCENE_CHANGE_INTRO,
    SCENE_CHANGE_OUTRO,
    INTRO_DUST,
    SHOOT_DUST,
    BIG_TEAR_LEFT,
    BIG_TEAR_RIGHT,
    END
};
class CTexture;
class CVFXObject :
    public CObject
{
public:
    CVFXObject();
    ~CVFXObject();
    CLONE(CVFXObject);
public:
    virtual void Update();
    virtual void Render(HDC _dc);
public:
    void SetOffset(Vec2 _v) { m_offSet = _v; }
    Vec2 GetOffset() { return m_offSet; }
public:
	void SetType(VFX_TYPE _vfx);
private:
    CObject* m_owner;
    CTexture* m_tex;
    Vec2 m_offSet;
    VFX_TYPE m_currentType;
    array<wstring, TYPE_NUMBER(VFX_TYPE::END)> m_arrayVFX;
    friend class CPlayer;
    friend class COnion;
    friend class CMonster;
};

