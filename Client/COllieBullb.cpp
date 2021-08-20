#include "pch.h"
#include "COllieBullb.h"
#include "CCollider.h"
#include "COnionBossAttackBox.h"
#include "FSMAI.h"
#include "CState.h"

#include "SelectGDI.h"
COllieBullb::COllieBullb()
{
	CreateCollider();
	SetScale(Vec2(300.f, 500.f));
	GetCollider()->SetScale(Vec2(300.f, 500.f));
}

COllieBullb::~COllieBullb()
{
}

void COllieBullb::Render(HDC _dc)
{
	Vec2 renderPos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 scale = GetScale();
	SelectGDI gdi(_dc, BRUSH_TYPE::GREEN);
	Rectangle(
		_dc,
		renderPos.x - scale.x / 2.f,
		renderPos.y - scale.y / 2.f,
		renderPos.x + scale.x / 2.f,
		renderPos.y + scale.y / 2.f
	);
}

void COllieBullb::OnCollisionEnter(CCollider* _col)
{
	if (_col->GetOwner()->GetName() == L"Player_bullet")
	{
		if (GetAi()->GetCurrentState()->GetState() == MON_STATE::IDLE)
		{
			ChangeAIState(GetAi(), MON_STATE::ATTACK);
		}
	}
}

void COllieBullb::CreateAttackBox()
{
	m_attackBox = new COnionBossAttackBox;
	m_attackBox->m_owner = this;
	m_attackBox->Start();
}
