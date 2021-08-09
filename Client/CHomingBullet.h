#pragma once
#include "CObject.h"
///<summary>
/// 자동으로 적을 추적하여 격추시키는 미사일을 구현하는 클래스
/// 
/// 작성자 : 최문석
/// 작성일시 : 2021-07-04
/// 버전:
/// 1.0 - 기본구조 제작
///<summary> 

class CHomingBullet :
	public CObject
{
public:
	CHomingBullet();
	~CHomingBullet();
public:
	// CObject을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render(HDC _dc);
	virtual void FinalUpdate();
	void SetDirection(Vec2 _dir) { m_bulletDirection = _dir.Normalize(); }

	float GetDamege() { return m_bulletDamege; }


	virtual void OnCollisionEnter(CCollider* _col);

	CLONE(CHomingBullet)
private:
	void TraceTarget(vector<CObject*> _monsters);
private:
	float m_bulletSpeed;
	Vec2 m_bulletDirection;
	Vec2 m_bulletShootPos;
	float m_bulletDamege;
	float m_theata;
	float m_targetDist;
	CObject* m_target;
	float m_distance;

};

