#include "pch.h"
#include "CGround.h"
#include "CCollider.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CTexture.h"
#include "CPropeller.h"
#include "CGravity.h"
#include "CResourceManager.h";
#include "CSceneManager.h"
#include "CCamera.h"
#include "SelectGDI.h"


CGround::CGround()
	:m_propeller(nullptr)
{
	CreateCollider();
	SetScale(Vec2(100, 60));
}

CGround::~CGround()
{
}

void CGround::Start()
{

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
		m_propeller->SetPosOffset(Vec2(5.f, 60.f));
	}
		break;
	case GAMEOBJECT_TYPE::GROUND:
		break;
	case GAMEOBJECT_TYPE::END:
		break;
	default:
		break;
	}
	if(nullptr != GetCollider())
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
		SelectGDI gdi1(_dc, PEN_TYPE::WHITE);
		Rectangle(_dc,
			(int)(renderPos.x - scale.x / 2.f),
			(int)(renderPos.y - scale.y / 2.f),
			(int)(renderPos.x + scale.x / 2.f),
			(int)(renderPos.y + scale.y / 2.f)
		);
	}
	break;
	}

	ComponentRender(_dc);

	

}

void CGround::OnCollisionEnter(CCollider* _col)
{
	CObject* obj = _col->GetOwner();
	if (obj->GetName() == L"Player")
	{
		obj->GetGravity()->SetGround(true);

		Vec2 objPos = obj->GetCollider()->GetFinalPos();
		Vec2 objScale = obj->GetCollider()->GetScale();

		Vec2 pos = GetCollider()->GetFinalPos();
		Vec2 scale = GetCollider()->GetScale();

		float fLen = abs(objPos.y - pos.y);
		float fDiff = (objScale.y / 2.f + scale.y / 2.f) - fLen;

		objPos = obj->GetPos();
		objPos.y -= (fDiff - 1.f);
		obj->SetPos(objPos);
	}
}

void CGround::OnCollision(CCollider* _col)
{
	CObject* obj = _col->GetOwner();
	if (obj->GetName() == L"Player")
	{
		Vec2 objPos = obj->GetCollider()->GetFinalPos();
		Vec2 objScale = obj->GetCollider()->GetScale();

		Vec2 pos = GetCollider()->GetFinalPos();
		Vec2 scale = GetCollider()->GetScale();

		float fLen = abs(objPos.y - pos.y);
		float fDiff = (objScale.y / 2.f + scale.y / 2.f) - fLen;

		objPos = obj->GetPos();
		objPos.y -= (fDiff - 1.f);
		obj->SetPos(objPos);
	}
}

void CGround::OnCollisionExit(CCollider* _col)
{
	CObject* obj = _col->GetOwner();
	if (obj->GetName() == L"Player")
	{
		obj->GetGravity()->SetGround(false);
	}
}

void CGround::Save(FILE* _file)
{
	CGameObject::Save(_file);
	int objType = TYPE_NUMBER(GetType());

	fwrite(&objType, sizeof(int), 1, _file);


}

void CGround::Load(FILE* _file)
{
	CGameObject::Load(_file);

	int objType = TYPE_NUMBER(GetType());

	fread(&objType, sizeof(int), 1, _file);

	SetType((GAMEOBJECT_TYPE)objType);
}
