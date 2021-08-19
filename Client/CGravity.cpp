#include "pch.h"
#include "CGravity.h"
#include "CObject.h"
#include "CRigidBody.h"
CGravity::CGravity()
	:m_owner(nullptr)
	, m_isGround(false)
{
}

CGravity::~CGravity()
{
}

void CGravity::Finalupdate()
{
	if (!m_isGround)
	{
		m_owner->GetRigidBody()->SetAddAccel(Vec2(0.f, 1400.f));
	}
}
