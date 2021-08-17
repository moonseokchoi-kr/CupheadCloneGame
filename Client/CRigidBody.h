#pragma once

/// <summary>
/// 물체의 물리적인 효과를 적용시키는 클래스
/// 
/// 작성자: 최문석
/// 
/// 버전
/// 1.0 강체 클래스 기본구조 작성 2021-08-03
/// </summary>
/// 
/// 

//2021-08-04
//TODO : 필요에 따라 중력가속도를 적용받을 수 있도록 수정
class CRigidBody
{
public:
	CRigidBody();
	~CRigidBody();
public:
	void FinalUpdate();

public:
	void AddForce(Vec2 _f)
	{
		m_force = _f;
	}

	void SetMass(float _mass)
	{
		m_mass = _mass;
	}

	void AddVelocity(Vec2 _v)
	{
		m_velocity = _v;
	}

	void SetMaxVelocity(float _maxVelocity)
	{
		m_maxVelocity = _maxVelocity;
	}
	void SetFriction(float _fric)
	{
		m_fricCoef = _fric;
	}

	void SetAddAccel(Vec2 _accel) { m_accelAdd = _accel; }

	float GetMass() { return m_mass; }
	float GetSpeed() { return m_velocity.Distance(); }

private:
	void move();

private:
	CObject* m_owner;

	Vec2	m_force;		//힘의 크기,방
	Vec2	m_accel;		//힘의 따른 가속도
	Vec2	m_velocity;		//힘의 따른 속도
	Vec2	m_accelAdd;

	float	m_mass;			//물체의 질량
	float	m_maxVelocity;	//물체의 최대속력

	float	m_fricCoef;		//마찰계수

	friend class CObject;
};

