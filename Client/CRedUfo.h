#include "CObject.h"


class CTexture;

class CRedUfo :
	public CObject
{
public:
	CRedUfo();
	~CRedUfo();
public:
	virtual void Update() override;
	virtual void Render(HDC _dc);
	virtual void FinalUpdate();
	CLONE(CRedUfo);
public:
	void SetCenterPos(const Vec2& _pos) {
		m_centerPos = _pos;
	}
	Vec2 GetCenterPos() { return m_centerPos; }
	void SetMoveDist(const float _dist) { m_moveDistance = _dist; }
	void SetMoveSpeed(const float _speed) { m_moveSpeed = _speed; }
	void SetCoolTime(const float _time) { m_coolTime = _time; }

	void SetShootDir(Vec2 _dir) { m_shootDir = _dir.Normalize(); }
	virtual void OnCollisionEnter(CCollider* _col);
private:
	void fire();
private:
	Vec2 m_centerPos;
	float m_moveSpeed;
	float m_moveDistance;
	Vec2 m_moveDir;
	float m_coolTime;
	float m_theata;
	Vec2 m_shootDir;
	float m_Acc;
	float m_health;
};