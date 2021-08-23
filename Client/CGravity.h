#pragma once

enum class GROUND_TYPE
{
	PLATFORM,
	GROUND,
	NONE,
};

class CGravity
{
public:
	CGravity();
	~CGravity();
public:
	CObject* GetOwner() { return m_owner; }
	void SetGround(bool _b , GROUND_TYPE _type) {
		m_isGround = _b;
		m_groundType = _type;
	}
	bool IsGround() { return m_isGround; }
	GROUND_TYPE GetGroundType() { return m_groundType; }
public:
	void Finalupdate();

private:
	CObject* m_owner;
	bool m_isGround;
	GROUND_TYPE m_groundType;
	friend class CObject;
};

