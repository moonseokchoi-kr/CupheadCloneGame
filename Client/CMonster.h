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
/// ���͵��� �θ�Ŭ����
/// 
/// ����
/// 1.0 - �⺻ ����Ŭ���� ���� �ۼ� 2021-08-01
/// </summary>
/// 

class FSMAI;
class CAttackBox;
class CMonsterHitBox;
class CMonster :
    public CObject
{
public:
    CMonster();
    virtual ~CMonster();
public:
    // CObject��(��) ���� ��ӵ�
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
public:
    monsterInfo GetInfo() { return m_info; }
    void SetInfo(monsterInfo _info) { m_info = _info; }
    FSMAI* GetAi() { return m_ai; }
    void SetAi(FSMAI* _ai);
    CAttackBox* GetAttackBox() { return m_attackBox; }
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
    CObject* m_target;
    CMonsterHitBox* m_hitBox;
    bool m_isHit;
};

