#pragma once
#include "CGameObject.h"



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
class CShadow;

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
   
    CPropeller* m_propeller;
    CShadow* m_shadow;

};

