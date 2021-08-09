#pragma once
#include "CObject.h"
class CBullet :
    public CObject
{
public:
    CBullet();
    CBullet(const wstring& _name, const wstring& _relatviePath);
    ~CBullet();

public:
    void SetDirection(float _theata)
    {
        m_theata = _theata*(float)PI/180.f;
    }
    void SetDirection(Vec2 _dir) 
    { 
        m_bulletDirection = _dir;
        m_bulletDirection.Normalize();
    }
    void SetFirePos(Vec2 _firePos)
    {
        m_bulletShootPos = _firePos;
    }

    float GetDamege() { return m_bulletDamege; }
public:
	// CObject을(를) 통해 상속됨
	virtual void Update() override;
    virtual void Render(HDC _dc);
    virtual void FinalUpdate() override;
    bool IsOutOfRange();

    virtual void OnCollisionEnter(CCollider* _col);
    virtual void OnCollision(CCollider* _col);

    CLONE(CBullet);
private:
    
private:

    float m_range;
    float m_bulletSpeed;
    Vec2 m_bulletDirection;
    Vec2 m_bulletShootPos;
    float m_bulletDamege;
    float m_theata;

   
   

};

