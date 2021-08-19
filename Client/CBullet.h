#pragma once
#include "CObject.h"

struct bulletInfo
{
    float damege;
    float range;
    float bulletSpeed;
    
};

enum class BULLET_STATE
{
    LOOP,
    DEATH,
};

/// <summary>
/// 
/// ����ü ���� �θ�Ŭ����
/// 
/// �ۼ���: �ֹ���
/// ����
/// 
/// 1.0 - �⺻ ���� �ۼ� 2021-08-18 
/// </summary>
/// 

class CAttackBox;

class CBullet :
    public CObject
{
public:
    CBullet(BULLET_TYPE _type);
    ~CBullet();
public:
    // CObject��(��) ���� ��ӵ�
    virtual void Start() override;
    virtual void Render(HDC _dc) override;

    virtual void OnCollisionEnter(CCollider* _col) override;
    virtual void OnCollision(CCollider* _col)override;
    virtual void OnCollisionExit(CCollider* _col)override;

public:
    CAttackBox* GetAttackBox() { return m_attackBox; }
 
    BULLET_TYPE GetType() { return m_bulletType; }
    bulletInfo GetInfo() { return m_info; }
    void SetInfo(bulletInfo _info) { m_info = _info; }
    void SetOffSet(Vec2 _v) { m_offset = _v; }
    Vec2 GetFinalPos() { return m_finalPos; }
    Vec2 GetInitPos() { return m_initPos; }
    Vec2 GetMoveDir() { return m_moveDir; }
    void SetMoveDir(Vec2 _v) { m_moveDir = _v; }
protected:
    void DeleteBullet();
private:
    CAttackBox* m_attackBox;
    Vec2 m_offset;
    Vec2 m_finalPos;
    Vec2 m_initPos;
    bulletInfo m_info;
    CObject* m_deathFx;
    Vec2 m_moveDir;
    BULLET_TYPE m_bulletType;

    friend class CAttackBox;
    friend class CMonster;
};

