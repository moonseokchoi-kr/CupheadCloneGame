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
	// CObject을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render(HDC _dc) override;

	virtual void OnCollisionEnter(CCollider* _col) override;
	virtual void OnCollision(CCollider* _col)override;
	virtual void OnCollisionExit(CCollider* _col)override;
private:

};

