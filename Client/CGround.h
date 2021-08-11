#pragma once
#include "CGameObject.h"

/// <summary>
/// ���ӳ� �������� �����ϴ� ������Ʈ Ŭ����
/// 
/// ����
/// 1.0- �⺻���� �ۼ� 2021-08-11
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

