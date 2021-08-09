#pragma once
#include "CObject.h"

struct monsterInfo
{
    float hp;
    float attackDamege;
    float eyesightRange;
    float attackRange;
    float attackSpeed;
    float moveSpeed;
};


/// <summary>
/// 몬스터들의 부모클래스
/// 
/// 버전
/// 1.0 - 기본 몬스터클래스 구조 작성 2021-08-01
/// </summary>
/// 

class FSMAI;

class CMonster :
    public CObject
{
public:
    CMonster();
    ~CMonster();
public:
    // CObject을(를) 통해 상속됨
    virtual void Update() override;
    virtual void FinalUpdate() override;
    virtual void Render(HDC _dc);

    virtual void OnCollisionEnter(CCollider* _col);
    CLONE(CMonster);
public:
    monsterInfo GetInfo() { return m_info; }
    void SetInfo(monsterInfo _info) { m_info = _info; }
    void SetAi(FSMAI* _ai);
private:
    monsterInfo m_info;
    FSMAI* m_ai;

};

