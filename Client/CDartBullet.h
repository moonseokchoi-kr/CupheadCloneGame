#pragma once

#include "CObject.h"

class CDartBullet
	:public CObject
{
public:
	CDartBullet();
	~CDartBullet();
public:
	// CObject��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render(HDC _dc);
	virtual void OnCollisionEnter(CCollider* _col);
	virtual void FinalUpdate();
	CLONE(CDartBullet);

private:

	CObject* m_target;
	Vec2 m_dirction;
	float m_bulletSpeed;
	float m_range;

	bool m_isCal;

};

