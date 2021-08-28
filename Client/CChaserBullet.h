#pragma once
#include "CBullet.h"

class CHomingBulletTraile;
class CChaserBullet :
    public CBullet
{

public:
	CChaserBullet();
	~CChaserBullet();
	CLONE(CChaserBullet);
public:
	// CBullet을(를) 통해 상속됨
	virtual void Start() override;
	virtual void Update() override;
	virtual void FinalUpdate();
	virtual void Render(HDC _dc) override;
	virtual void OnCollisionEnter(CCollider* _col)  override;
	virtual void OnCollision(CCollider* _col) override;
	virtual void OnCollisionExit(CCollider* _col) override;
private:
	CObject* m_target;
	CHomingBulletTraile* m_fx;
	Vec2 m_maxAngle;
	bool m_isDead;
};

