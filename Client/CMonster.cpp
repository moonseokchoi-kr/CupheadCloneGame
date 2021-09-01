#include "pch.h"
#include "CMonster.h"
#include "CCollider.h"
#include "CRigidBody.h"
#include "CAttackBox.h"
#include "FSMAI.h"
#include "CMonsterHitBox.h"
#include "CVFXObject.h"
#include "CSceneManager.h"
#include "CScene.h"
CMonster::CMonster()
	:m_info{}
	,m_ai(nullptr)
{
	CreateCollider();
	SetName(L"Monster");
	SetScale(Vec2(40.f, 40.f));
	GetCollider()->SetScale(Vec2(100.f, 100.f));

}

CMonster::~CMonster()
{
	if (nullptr != m_ai)
		delete m_ai;
	if (nullptr != m_attackBox && m_attackBox->GetName() != L"SlimeAttackBox")
		delete m_attackBox;
	if (nullptr != m_fx)
		delete m_fx;
	if (CSceneManager::GetInst()->GetCurrentScene()->GetSceneName() == L"Tool Scene")
		DeleteObject(m_hitBox);
}

void CMonster::Start()
{
	CreateAttackBox();
	CreateHitBox();
	CreateVFX();
}

void CMonster::Update()
{
	if (m_fx != nullptr)
	{
		m_fx->Update();
	}
	if (m_attackBox != nullptr)
	{
		m_attackBox->Update();
	}
	if (m_hitBox != nullptr)
	{
		m_hitBox->Update();
	}
	m_target = CSceneManager::GetInst()->GetCurrentScene()->GetTarget(GROUP_TYPE::PLAYER, L"Player");
	if (m_ai != nullptr)
	{
		m_ai->Update();
	}


}

void CMonster::FinalUpdate()
{
	if (CSceneManager::GetInst()->GetCurrentScene()->GetSceneName() == L"Tool Scene")
		return;
	m_hitBox->FinalUpdate();
	if (m_fx != nullptr)
	{
		m_fx->FinalUpdate();
	}
	if (m_attackBox != nullptr)
	{
		m_attackBox->FinalUpdate();
	}
	CObject::FinalUpdate();
}

void CMonster::Render(HDC _dc)
{
	if (m_fx != nullptr)
	{
		m_fx->Render(_dc);
	}
	ComponentRender(_dc);
	if (m_attackBox != nullptr)
	{
		m_attackBox->Render(_dc);
	}
#ifdef _DEBUG
	//m_hitBox->Render(_dc);
#endif
}

void CMonster::OnCollisionEnter(CCollider* _col)
{

}

void CMonster::OnCollision(CCollider* _col)
{

}


void CMonster::OnCollisionExit(CCollider* _col)
{
}

void CMonster::CreateHitBox()
{
	m_hitBox = new CMonsterHitBox;
	m_hitBox->m_owner = this;
}

void CMonster::CreateVFX()
{
	m_fx = new CVFXObject;
	m_fx->m_owner = this;
}


void CMonster::SetAi(FSMAI* _ai)
{
	m_ai = _ai;
	_ai->m_owner = this;
}
