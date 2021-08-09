#pragma once
#include "CObject.h"
///<summary>
/// �ڵ����� ���� �����Ͽ� ���߽�Ű�� �̻����� �����ϴ� Ŭ����
/// 
/// �ۼ��� : �ֹ���
/// �ۼ��Ͻ� : 2021-07-04
/// ����:
/// 1.0 - �⺻���� ����
///<summary> 

class CHomingBullet :
	public CObject
{
public:
	CHomingBullet();
	~CHomingBullet();
public:
	// CObject��(��) ���� ��ӵ�
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

