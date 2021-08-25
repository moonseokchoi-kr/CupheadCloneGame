#include "pch.h"
#include "CRigidBody.h"
#include "CObject.h"


#include "CTimeManager.h"

CRigidBody::CRigidBody()
	:m_owner(nullptr)
	,m_mass(1.f)
	,m_maxVelocity(200.f)
	,m_fricCoef(100.f)
	,m_isActive(true)
{
}

CRigidBody::~CRigidBody()
{
}

void CRigidBody::FinalUpdate()
{
	if (!m_isActive)
		return;
	if (!m_force.isZero())
	{
		m_accel = m_force / m_mass;
	}
	m_accel += m_accelAdd;

	m_velocity += m_accel * fDT;
	if (!m_velocity.isZero())
	{
		Vec2 fricDir = -m_velocity;
		Vec2 friction = fricDir.Normalize() * m_fricCoef * fDT;
		if (m_velocity.Distance() <= friction.Distance())
		{
			m_velocity = Vec2(0.f, 0.f);
		}
		else
		{
			m_velocity += friction;
		}
	}
	if (m_maxVelocity < m_velocity.Distance())
	{
		m_velocity.Normalize();
		m_velocity *= m_maxVelocity;
	}
	move();

	m_force = Vec2(0.f, 0.f);
	m_accel = Vec2(0.f, 0.f);
	m_accelAdd = Vec2(0.f, 0.f);
}

void CRigidBody::move()
{
	Vec2 pos = m_owner->GetPos();
	pos += m_velocity * fDT;
	m_owner->SetPos(pos);
}
