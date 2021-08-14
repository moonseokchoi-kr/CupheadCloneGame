#include "pch.h"
#include "CGround.h"
#include "CCollider.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CTexture.h"
#include "CPropeller.h"

#include "CResourceManager.h";
#include "CSceneManager.h"
#include "CCamera.h"
#include "SelectGDI.h"


CGround::CGround()
	:m_propeller(nullptr)
{
	CreateCollider();
}

CGround::~CGround()
{
}

void CGround::Start()
{
	SetScale(Vec2(100, 60));
	
	switch (GetType())
	{
	case GAMEOBJECT_TYPE::FLOWER_PLATFORM_A:
	case GAMEOBJECT_TYPE::FLOWER_PLATFORM_B:
	case GAMEOBJECT_TYPE::FLOWER_PLATFORM_C:
	{
		CreateAnimator();
		CTexture* tex = CResourceManager::GetInst()->LoadTexture(L"platform", L"texture\\cuphead\\obj\\PlatformSprite.bmp");
		GetAnimator()->CreateAnimation(L"platform_A_anim", tex, Vec2(0, 0), Vec2(160, 93), Vec2(160, 0), 0.15f, 3, false);
		GetAnimator()->CreateAnimation(L"platform_B_anim", tex, Vec2(480, 0), Vec2(160, 93), Vec2(160, 0), 0.15f, 3, false);
		GetAnimator()->CreateAnimation(L"platform_C_anim", tex, Vec2(960, 0), Vec2(160, 93), Vec2(160, 0), 0.15f, 3, false);

		SetScale(Vec2(160, 93));
		m_propeller = new CPropeller;
		m_propeller->SetParent(this);
		m_propeller->SetPosOffset(Vec2(30.5f, 75.f));
	}
		break;
	case GAMEOBJECT_TYPE::GROUND:
		break;
	case GAMEOBJECT_TYPE::END:
		break;
	default:
		break;
	}

	GetCollider()->SetScale(GetScale());
}

void CGround::Update()
{
}

void CGround::FinalUpdate()
{
	CGameObject::FinalUpdate();
	if (nullptr != m_propeller)
		m_propeller->FinalUpdate();
}

void CGround::Render(HDC _dc)
{
	Vec2 renderPos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 scale = GetScale();
	if (nullptr != m_propeller)
		m_propeller->Render(_dc);
	switch (GetType())
	{
	case GAMEOBJECT_TYPE::FLOWER_PLATFORM_A:
	{
		GetAnimator()->Play(L"platform_A_anim", true);
	}
	break;
	case GAMEOBJECT_TYPE::FLOWER_PLATFORM_B:
	{
		GetAnimator()->Play(L"platform_B_anim", true);
	}
	break;
	case GAMEOBJECT_TYPE::FLOWER_PLATFORM_C:
	{
		GetAnimator()->Play(L"platform_C_anim", true);
	}
	break;
	default:
	{
		SelectGDI gdi(_dc, BRUSH_TYPE::HOLLOW);
		Rectangle(_dc,
			(int)(renderPos.x),
			(int)(renderPos.y),
			(int)(renderPos.x + scale.x),
			(int)(renderPos.y + scale.y)
		);
	}
	break;
	}

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
