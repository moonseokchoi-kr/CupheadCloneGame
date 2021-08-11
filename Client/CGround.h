#pragma once
#include "CGameObject.h"

/// <summary>
/// 게임내 땅역할을 수행하는 오브젝트 클래스
/// 
/// 버전
/// 1.0- 기본구조 작성 2021-08-11
/// </summary>
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
};

