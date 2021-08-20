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
class CChauncey :
    public CMonster
{
public:
    CChauncey();
    ~CChauncey();
    CLONE(CChauncey);
public:
    virtual void Update();
    virtual void Render(HDC _dc);
public:
    void CreateAttackBox();
};

