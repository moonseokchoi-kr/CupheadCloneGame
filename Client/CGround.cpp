#include "pch.h"
#include "CGround.h"
#include "CCollider.h"

#include "CSceneManager.h"
#include "CCamera.h"
#include "SelectGDI.h"

#include "CPropeller.h"
#include "CShadow.h"

CGround::CGround()
	:m_propeller(nullptr)
	,m_shadow(nullptr)
{
	SetScale(Vec2(100, 60));
	CreateCollider();
	

}

CGround::~CGround()
{
}

void CGround::Start()
{
	GetCollider()->SetScale(GetScale());
	
	switch (GetType())
	{
	case GAMEOBJECT_TYPE::FLOWER_PLATFORM_A:
	case GAMEOBJECT_TYPE::FLOWER_PLATFORM_B:
	case GAMEOBJECT_TYPE::FLOWER_PLATFORM_C:
	{
		m_propeller = new CPropeller;
		m_shadow = new CShadow;
	}
		break;
	case GAMEOBJECT_TYPE::GROUND:
		break;
	case GAMEOBJECT_TYPE::END:
		break;
	default:
		break;
	}
}

void CGround::Update()
{
}

void CGround::FinalUpdate()
{
	CGameObject::FinalUpdate();
}

void CGround::Render(HDC _dc)
{
	Vec2 renderPos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 scale = GetScale();
	if (CSceneManager::GetInst()->GetCurrentScene()->GetSceneName() != L"Tool Scene") 
	{
		return;
	}
	SelectGDI gdi(_dc, BRUSH_TYPE::HOLLOW);

	Rectangle(_dc,
		(int)(renderPos.x - scale.x / 2.f),
		(int)(renderPos.y - scale.y / 2.f),
		(int)(renderPos.x + scale.x / 2.f),
		(int)(renderPos.y + scale.y / 2.f)
	);

	ComponentRender(_dc);

}

void CGround::OnCollisionEnter(CCollider* _col)
{
}

void CGround::OnCollision(CCollider* _col)
{
}

void CGround::OnCollisionExit(CCollider* _col)
{
}

void CGround::Save(FILE* _file)
{
	CGameObject::Save(_file);
}

void CGround::Load(FILE* _file)
{
	CGameObject::Load(_file);
}
