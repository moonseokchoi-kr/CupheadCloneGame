#include "pch.h"
#include "CMonster.h"
#include "CCollider.h"
#include "CRigidBody.h"
#include "CAttackBox.h"
#include "FSMAI.h"
#include "CSceneManager.h"
#include "CScene.h"
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
	if (nullptr != m_attackBox)
		delete m_attackBox;
}

void CMonster::Start()
{
	CreateAttackBox();
}

void CMonster::Update()
{
	m_target = CSceneManager::GetInst()->GetCurrentScene()->GetTarget(GROUP_TYPE::PLAYER, L"Player");
	if (m_ai != nullptr)
	{
		m_ai->Update();
	}
	if (m_attackBox != nullptr)
	{
		m_attackBox->Update();
	}
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
	CObject* obj = _col->GetOwner();
	Vec2 moveDir = _col->GetOwner()->GetMoveDir();
	if (obj->GetName() == L"Player")
	{
		obj->GetRigidBody()->SetVelocity(Vec2(0, 0));
		obj->GetRigidBody()->AddVelocity(-moveDir * 300.f);

	}
}

void CMonster::OnCollision(CCollider* _col)
{
	CObject* obj = _col->GetOwner();
	Vec2 moveDir = _col->GetOwner()->GetMoveDir();
	if (obj->GetName() == L"Player")
	{
		obj->GetRigidBody()->SetVelocity(Vec2(0, 0));
		obj->GetRigidBody()->AddVelocity(-moveDir * 300.f);

	}
}


void CMonster::OnCollisionExit(CCollider* _col)
{
}


void CMonster::SetAi(FSMAI* _ai)
{
	m_ai = _ai;
	_ai->m_owner = this;
}
