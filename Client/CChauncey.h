#pragma once
#include "CMonster.h"

/// <summary>
/// ��� ���� Ŭ����
/// 
/// ���� ������ �� ���ݰ�, �����̻��� ���� 2������ ������,
/// ���� �̻����� �÷��̾� ��ġ�� �ѹ��������Ͽ� �Ѵ´�.
/// 
/// ������Ʈ
/// intro
/// idle
/// attack
/// Death
/// </summary>
/// 
class CCarrotEyes;

class CChauncey :
    public CMonster
{
public:
    CChauncey();
    ~CChauncey();
    CLONE(CChauncey);
public:
    virtual void Start();
    virtual void Update();
    virtual void Render(HDC _dc);
    virtual void FinalUpdate();
    virtual void OnCollision(CCollider* _col);
    virtual void OnCollisionEnter(CCollider* _col);
public:
    void CreateAttackBox();
private:
    void CreateEyes();
private:
    CCarrotEyes* m_eyes;

    friend class CCarrotEyes;
};

