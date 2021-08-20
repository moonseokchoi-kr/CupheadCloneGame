#include "pch.h"
#include "CChauncey.h"
#include "CCarrotBossAttackBox.h"
#include "CCollider.h"
#include "SelectGDI.h"
CChauncey::CChauncey()
{
	CreateCollider();
	CreateRigidBody();
	SetScale(Vec2(100.f,300.f));
	GetCollider()->SetScale(GetScale());
}

CChauncey::~CChauncey()
{
}

void CChauncey::Update()
{
	CMonster::Update();
}

void CChauncey::Render(HDC _dc)
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

void CChauncey::CreateAttackBox()
{
	m_attackBox = new CCarrotBossAttackBox;
	m_attackBox->m_owner = this;
}
