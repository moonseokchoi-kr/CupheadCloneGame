#include "pch.h"
#include "CSlime.h"
#include "CCollider.h"
#include "CSlimeAttackBox.h"
#include "CMonsterHitBox.h"
#include "SelectGDI.h"
CSlime::CSlime()
{
	CreateCollider();
	SetScale(Vec2(340.f, 616.f));
	GetCollider()->SetScale(Vec2(340.f, 616.f));	
}

CSlime::~CSlime()
{
}

void CSlime::Start()
{
}

void CSlime::Update()
{
	CMonster::Update();
}

void CSlime::Render(HDC _dc)
{
	Vec2 renderPos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 scale = GetScale();
	SelectGDI gdi(_dc, BRUSH_TYPE::BLUE);
	Ellipse(
		_dc,
		renderPos.x - scale.x / 2.f,
		renderPos.y - scale.y / 2.f,
		renderPos.x + scale.x / 2.f,
		renderPos.y + scale.y / 2.f
	);
}

void CSlime::CreateAttackBox()
{
	m_attackBox = new CSlimeAttackBox;
	m_attackBox->m_owner = this;
}
