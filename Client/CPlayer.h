#pragma once
#include "CObject.h"
#include "CTexture.h"

class PlayerSubweapon;
/// <summary>
/// ���� �÷��̾� ĳ���� Ŭ����
/// </summary>
/// 
/// �ۼ��� �ֹ���
/// 
/// ���� :
/// 1.0 - �⺻ ���� �ۼ�
/// 1.1 - �ݶ��̴� �߰�
/// 1.2 - �ִϸ��̼� �߰�
/// 
/// 
///
// 2021-08-04
// TODO : �÷��̾� ���� �ӽ� �ۼ�
class CPlayer :
    public CObject
{
public:
    CPlayer();
    ~CPlayer();
public:
    // CObject��(��) ���� ��ӵ�
    virtual void Update() override;

    virtual void Render(HDC _dc);

    virtual void OnCollisionEnter(CCollider* _col);
    virtual void FinalUpdate();
    CLONE(CPlayer);
private:
    void fire();
   
private:
    PlayerSubweapon* m_subweapon;
    float m_moveSpeed;
    float m_moveDir;
    Vec2  m_shootDir;
    UINT m_weaponMode;
    float m_health;
    friend class PlayerSubweapon;
};
