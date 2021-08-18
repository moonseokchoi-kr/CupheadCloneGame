#include "pch.h"
#include "CAttackBox.h"
#include "CCollider.h";
#include "CPlayer.h"
#include "CBullet.h"
#include "CCamera.h"



#include "SelectGDI.h"

#include "CTimeManager.h"

CAttackBox::CAttackBox()
	:m_accTime(0.f)
	,m_current_Bullet(BULLET_TYPE::END)
	,m_owner(nullptr)
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
	rotateCreateBulletPos();
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

void CAttackBox::Fire()
{
	m_accTime += fDT;
	playerInfo pInfo = ((CPlayer*)m_owner)->GetInfo();
	if (m_accTime >= pInfo.attackSpeed)
	{
		CBullet* bullet = GetBullet(m_current_Bullet);
		if (m_finalPos.isZero())
			return;
		if (nullptr == bullet)
			return;
		CBullet* cloneBullet = bullet->Clone();
		cloneBullet->SetPos(m_finalPos);
		bulletInfo info = {};
		info.bulletSpeed = 300.f;
		info.damege = 5.f;
		info.range = 1600.f;
		info.moveDir = pInfo.shootDir;
		cloneBullet->SetInfo(info);
		CreateObject(cloneBullet, GROUP_TYPE::PLAYER_BULLET);
		m_accTime = 0.0f;
	}

}

void CAttackBox::ChangeBullet()
{
}

void CAttackBox::rotateCreateBulletPos()
{
	playerInfo info = ((CPlayer*)m_owner)->GetInfo();
	Vec2 pos = m_owner->GetPos();
	//플레이어의 위치에서 현재 어택박스 위치를 뺀다
	//나온 결과 백터를 방향 벡터(숫)에 곱한다.
	//플레이어의 위치와 결과벡터를 외적한다.
	//나온 벡터가 최종위치
	
	if (info.shootDir.isZero())
		return;
	Vec2 diff = m_finalPos - pos;
	float dist = diff.Distance();
	Vec2 p = info.shootDir * dist;
	m_finalPos = pos + p;
}

CBullet* CAttackBox::GetBullet(BULLET_TYPE _type)
{
	unordered_map<BULLET_TYPE, CBullet*>::iterator iter = m_bulletVec.find(_type);
	if (m_bulletVec.end() == iter)
		return nullptr;
	return iter->second;
}
