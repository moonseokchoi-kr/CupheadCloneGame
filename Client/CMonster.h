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
class CMonster :
    public CObject
{
public:
    CMonster();
    ~CMonster();
public:
    // CObject��(��) ���� ��ӵ�
    virtual void Start() override;
    virtual void Update() override;
    virtual void FinalUpdate() override;
    virtual void Render(HDC _dc);
    virtual void CreateAttackBox() {};
    virtual void OnCollisionEnter(CCollider* _col);
    CLONE(CMonster);
public:
    
    monsterInfo GetInfo() { return m_info; }
    void SetInfo(monsterInfo _info) { m_info = _info; }
    void SetAi(FSMAI* _ai);
    CAttackBox* GetAttackBox() { return m_attackBox; }
    void SetTarget(CObject* _target) { m_target = _target; }
    CObject* GetTarget() { return m_target; }
protected:
    CAttackBox* m_attackBox;
private:
    CObject* m_target;
    monsterInfo m_info;
    FSMAI* m_ai;

};

