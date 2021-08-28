#pragma once
#include "CBullet.h"
class CPeaShootBullet :
    public CBullet
{
public:
	CPeaShootBullet();
	~CPeaShootBullet();
	CLONE(CPeaShootBullet);
public:
	// CObject��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render(HDC _dc) override;

	virtual void OnCollisionEnter(CCollider* _col) override;
	virtual void OnCollision(CCollider* _col)override;
	virtual void OnCollisionExit(CCollider* _col)override;

	void SetAnimName(const wstring& _name) { m_animName = _name; }
private:
	bool m_isDead;
	wstring m_animName;
};

