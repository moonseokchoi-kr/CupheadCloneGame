#pragma once
#include "CGameObject.h"



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

