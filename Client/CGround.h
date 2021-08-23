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
/// ���ӳ� �������� �����ϴ� ������Ʈ Ŭ����
/// 
/// ����
/// 1.0- �⺻���� �ۼ� 2021-08-11
/// 1.1- �÷��� ������Ʈ Ȯ�� �߰� 2021-08-14
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

