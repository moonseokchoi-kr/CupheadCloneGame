#include "pch.h"
#include "CMonster.h"
#include "CCollider.h"
#include "FSMAI.h"

CMonster::CMonster()
	:m_info{}
	,m_ai(nullptr)
{
	CreateCollider();
	CreateRigidBody();
	CreateGravity();
	SetName(L"Monster");
	SetScale(Vec2(40.f, 40.f));
	GetCollider()->SetScale(Vec2(100.f, 100.f));
}

CMonster::~CMonster()
{
	if (nullptr != m_ai)
		delete m_ai;
}

void CMonster::Update()
{
	m_ai->Update();
}

void CMonster::FinalUpdate()
{
	CObject::FinalUpdate();
}

void CMonster::Render(HDC _dc)
{
	ComponentRender(_dc);
}

void CMonster::OnCollisionEnter(CCollider* _col)
{
}

void CMonster::SetAi(FSMAI* _ai)
{
	m_ai = _ai;
	_ai->m_owner = this;
}
