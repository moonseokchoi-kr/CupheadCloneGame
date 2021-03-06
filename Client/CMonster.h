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
class CAttackBox;
class CMonsterHitBox;
class CVFXObject;
class CMonster :
    public CObject
{
public:
    CMonster();
    virtual ~CMonster();
public:
    // CObject을(를) 통해 상속됨
    virtual void Start() override;
    virtual void Update() override;
    virtual void FinalUpdate() override;
    virtual void Render(HDC _dc);
    virtual void CreateAttackBox() {};
    virtual void OnCollisionEnter(CCollider* _col);
    virtual void OnCollision(CCollider* _col);
    virtual void OnCollisionExit(CCollider* _col);
    CLONE(CMonster);
public:
    virtual void CreateHitBox();
    void CreateVFX();
public:
    monsterInfo GetInfo() { return m_info; }
    void SetInfo(monsterInfo _info) { m_info = _info; }
    FSMAI* GetAi() { return m_ai; }
    void SetAi(FSMAI* _ai);
    CAttackBox* GetAttackBox() { return m_attackBox; }
    CVFXObject* GetVFX() { return m_fx; }
    CObject* GetTarget() { return m_target; }
    CMonsterHitBox* GetHitBox() { return m_hitBox; }
    bool IsHit() { return m_isHit; }
    void SetHit(bool _b) { m_isHit = _b; }
protected:
    CAttackBox* m_attackBox;
    bool m_renderToggle;
private:
    monsterInfo m_info;
    FSMAI* m_ai;
    CVFXObject* m_fx;
    CObject* m_target;
    CMonsterHitBox* m_hitBox;
    bool m_isHit;
};

