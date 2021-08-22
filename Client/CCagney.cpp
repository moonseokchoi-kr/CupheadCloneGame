#include "pch.h"
#include "CCagney.h"
#include "CCollider.h"
#include "CCagneyAttackBox.h"

#include "SelectGDI.h"
CCagney::CCagney()
{
	CreateCollider();
	SetScale(Vec2(340.f, 616.f));
	GetCollider()->SetScale(Vec2(340.f, 616.f));	
}

CCagney::~CCagney()
{
}

void CCagney::Update()
{
	CMonster::Update();
}

void CCagney::Render(HDC _dc)
{
	Vec2 renderPos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 scale = GetScale();
	SelectGDI gdi(_dc, BRUSH_TYPE::BLUE);
	Rectangle(
		_dc,
		renderPos.x - scale.x / 2.f,
		renderPos.y - scale.y / 2.f,
		renderPos.x + scale.x / 2.f,
		renderPos.y + scale.y / 2.f
	);
}

void CCagney::CreateAttackBox()
{
	m_attackBox = new CCagneyAttackBox;
	m_attackBox->m_owner = this;
}
