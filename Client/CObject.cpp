#include "pch.h"
#include "CObject.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CCamera.h"
#include "CRigidBody.h"

CObject::CObject() 
	:m_objPos(Vec2(0, 0))
	, m_objScale(Vec2(10, 10))
	,m_collider(nullptr)
	,m_animator(nullptr)
	,m_rigidBody(nullptr)
	,m_dead(false)
{
}

CObject::CObject(const CObject& _origin)
	:m_objPos(_origin.m_objPos)
	,m_objScale(_origin.m_objScale)
	,m_collider(nullptr)
	,m_animator(nullptr)
	,m_rigidBody(nullptr)
	,m_dead(false)
{
	if (_origin.m_collider)
	{
		m_collider = new CCollider(*_origin.m_collider);
		m_collider->m_owner = this;
	}
	if (_origin.m_animator)
	{
		m_animator = new CAnimator(*_origin.m_animator);
		m_animator->m_owner = this;
	}
	if (_origin.m_rigidBody)
	{
		m_rigidBody = new CRigidBody(*_origin.m_rigidBody);
		m_rigidBody->m_owner = this;
	}
}

CObject::~CObject()
{
	if (nullptr != m_collider)
	{
		delete m_collider;
	}
	if (nullptr != m_animator)
	{
		delete m_animator;
	}
	if (nullptr != m_rigidBody)
	{
		delete m_rigidBody;
	}
}
void CObject::CreateCollider()
{
	m_collider = new CCollider;
	m_collider->m_owner = this;
}
void CObject::CreateAnimator()
{
	m_animator = new CAnimator;
	m_animator->m_owner = this;
}
void CObject::CreateRigidBody()
{
	m_rigidBody = new CRigidBody;
	m_rigidBody->m_owner = this;
}
/// <summary>
/// 오브젝트의 렌더링을 진행하는 함수
/// </summary>
/// <param name="_dc">렌더링의 결과를 저장할 Device Context</param>
void CObject::Render(HDC _dc)
{
	Vec2 renderPos = CCamera::GetInst()->GetRenderPos(m_objPos);
	Rectangle(_dc,
		(int)(renderPos.x / 2 - renderPos.x / 2),
		(int)(renderPos.y / 2 - renderPos.y / 2),
		(int)(renderPos.x / 2 + renderPos.x / 2),
		(int)(renderPos.y / 2 + renderPos.y / 2)
		);
	ComponentRender(_dc);
}

void CObject::FinalUpdate()
{
	if (m_collider)
		m_collider->FinalUpdate();
	if (m_animator)
		m_animator->FinalUpdate();
	if (m_rigidBody)
		m_rigidBody->FinalUpdate();
}

void CObject::ComponentRender(HDC _dc)
{
	if (nullptr != m_collider)
	{
		m_collider->Render(_dc);
	}
	if (nullptr != m_animator)
	{
		m_animator->Render(_dc);
	}
}
