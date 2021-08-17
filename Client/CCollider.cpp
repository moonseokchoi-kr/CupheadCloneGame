#include "pch.h"
#include "CCollider.h"
#include "CObject.h"
#include "SelectGDI.h"
#include "CCamera.h"
UINT CCollider::g_nextId = 0;

CCollider::CCollider()
	:m_owner(nullptr)
	,m_id(g_nextId++)
	,m_col(0)
{
}

CCollider::CCollider(const CCollider& _origin)
	:m_owner(nullptr)
	,m_id(g_nextId++)
	,m_col(0)
	,m_offset(_origin.m_offset)
	,m_scale(_origin.m_scale)
{
}

CCollider::~CCollider()
{
}

void CCollider::FinalUpdate()
{
	Vec2 objectPos = m_owner->GetPos();

	m_finalPos = objectPos + m_offset;

	assert(0 <= m_col);
}

void CCollider::Render(HDC _dc)
{
	PEN_TYPE pen = PEN_TYPE::GREEN;

	if (m_col)
		pen = PEN_TYPE::RED;

	SelectGDI p(_dc, pen);
	SelectGDI b(_dc, BRUSH_TYPE::HOLLOW);

	Vec2 renderPos = CCamera::GetInst()->GetRenderPos(m_finalPos);

	Rectangle(_dc,
		(int)(renderPos.x - m_scale.x / 2.f),
		(int)(renderPos.y - m_scale.y / 2.f),
		(int)(renderPos.x + m_scale.x / 2.f),
		(int)(renderPos.y + m_scale.y / 2.f)
	);

}

void CCollider::OnCollision(CCollider* _col)
{
	m_owner->OnCollision(_col);
}

void CCollider::OnCollisionEnter(CCollider* _col)
{
	m_owner->OnCollisionEnter(_col);
	++m_col;
}

void CCollider::OnCollisionExit(CCollider* _col)
{
	m_owner->OnCollisionExit(_col);
	--m_col;
}
