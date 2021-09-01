#include "pch.h"
#include "CAttackBox.h"
#include "CCollider.h"
#include "CPlayer.h"
#include "CBullet.h"
#include "CCamera.h"
#include "CResourceManager.h"


#include "SelectGDI.h"

#include "CTimeManager.h"

CAttackBox::CAttackBox()
	:m_accTime(0.f)
	,m_current_Bullet(BULLET_TYPE::END)
	,m_owner(nullptr)
	,m_sfx(nullptr)
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(40.f, 40.f));
}

CAttackBox::~CAttackBox()
{
}


void CAttackBox::Update()
{
	Vec2 offset = GetPos();
	Vec2 ownerPos = m_owner->GetPos();
	m_finalPos = ownerPos+ offset;
}

void CAttackBox::Render(HDC _dc)
{
	SelectGDI gdi(_dc, PEN_TYPE::BLUE_BOLD);
	Vec2 renderPos = CCamera::GetInst()->GetRenderPos(m_finalPos);
	Vec2 scale = GetScale();
	Rectangle(
		_dc,
		(int)(renderPos.x - scale.x / 2.f),
		(int)(renderPos.y - scale.y / 2.f),
		(int)(renderPos.x + scale.x / 2.f),
		(int)(renderPos.y + scale.y / 2.f)
	);
}

void CAttackBox::AddBullet(CBullet* _bullet)
{
	m_bulletVec.insert(make_pair(_bullet->GetType(), _bullet));
	_bullet->m_attackBox = this;
}


CBullet* CAttackBox::GetBullet(BULLET_TYPE _type)
{
	unordered_map<BULLET_TYPE, CBullet*>::iterator iter = m_bulletVec.find(_type);
	if (m_bulletVec.end() == iter)
		return nullptr;
	return iter->second;
}

void CAttackBox::SetSFX(const wstring& _name)
{
	m_sfx = CResourceManager::GetInst()->FindSound(_name);
}
