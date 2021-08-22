#pragma once
#include "CBullet.h"
class CSeedBullet :
    public CBullet
{
public:
	CSeedBullet();
	~CSeedBullet();
	CLONE(CSeedBullet);
public:
	virtual void Start() override;
	virtual void Update() override;

	virtual void Render(HDC _dc) override;

	virtual void OnCollisionEnter(CCollider* _col) override;
	virtual void OnCollision(CCollider* _col) override;
private:
	bool randomPercent();
	void rotate();
private:
	float m_initTime;
	float m_accTime;
	bool m_targetSelect;
	Vec2 m_targetPos;
	Vec2 m_diff;
	Vec2 m_prevDiff;
};

