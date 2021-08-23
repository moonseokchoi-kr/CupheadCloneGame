#pragma once
#include "CGameObject.h"

enum class COLLIDE_TYPE
{
    COLLIDE_TOP,
    COLLIDE_LEFT,
    COLLIDE_RIGHT,
    COLLIDE_BOTTOM,
    COLLIDE_IDLE,
};

/// <summary>
/// 게임내 땅역할을 수행하는 오브젝트 클래스
/// 
/// 버전
/// 1.0- 기본구조 작성 2021-08-11
/// 1.1- 플랫폼 오브젝트 확장 추가 2021-08-14
/// 
/// </summary>
/// 


class CPropeller;

class CGround :
    public CGameObject
{
public:
    CGround();
    ~CGround();
    CLONE(CGround);
public:
    virtual void Start();
    virtual void Update();
    virtual void FinalUpdate();
    virtual void Render(HDC _dc);

    virtual void OnCollisionEnter(CCollider* _col);
    virtual void OnCollision(CCollider* _col);
    virtual void OnCollisionExit(CCollider* _col);

	virtual void Save(FILE* _file);
	virtual void Load(FILE* _file);
private:
    float calColliderDiff(float  _objPos, float _objScale, float _colPos, float _colScale);
private:
   
    CPropeller* m_propeller;

    COLLIDE_TYPE m_currentCollide;
};

