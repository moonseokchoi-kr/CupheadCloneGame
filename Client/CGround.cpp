#include "pch.h"
#include "CGround.h"
#include "CCollider.h"

#include "CSceneManager.h"
#include "CCamera.h"
#include "SelectGDI.h"

CGround::CGround()
{
	SetScale(Vec2(100, 60));
	CreateCollider();
	GetCollider()->SetScale(GetScale());

}

CGround::~CGround()
{
}

void CGround::Start()
{
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
