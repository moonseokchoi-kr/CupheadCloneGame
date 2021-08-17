#pragma once

/// <summary>
/// ��ü�� �������� ȿ���� �����Ű�� Ŭ����
/// 
/// �ۼ���: �ֹ���
/// 
/// ����
/// 1.0 ��ü Ŭ���� �⺻���� �ۼ� 2021-08-03
/// </summary>
/// 
/// 

//2021-08-04
//TODO : �ʿ信 ���� �߷°��ӵ��� ������� �� �ֵ��� ����
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

	Vec2	m_force;		//���� ũ��,��
	Vec2	m_accel;		//���� ���� ���ӵ�
	Vec2	m_velocity;		//���� ���� �ӵ�
	Vec2	m_accelAdd;

	float	m_mass;			//��ü�� ����
	float	m_maxVelocity;	//��ü�� �ִ�ӷ�

	float	m_fricCoef;		//�������

	friend class CObject;
};

