#pragma once
class CGravity
{
public:
	CGravity();
	~CGravity();
public:
	CObject* GetOwner() { return m_owner; }
	void SetGround(bool _b) {
		m_isGround = _b;
	}
	bool IsGround() { return m_isGround; }
public:
	void Finalupdate();

private:
	CObject* m_owner;
	bool m_isGround;

	friend class CObject;
};

