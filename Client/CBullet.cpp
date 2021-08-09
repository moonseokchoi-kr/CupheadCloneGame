#include "pch.h"
#include "CBullet.h"
#include "CCollider.h"
#include "CTexture.h"
#include "CAnimator.h"

#include "CSceneManager.h"
#include "CTimeManager.h"
#include "CResourceManager.h"

CBullet::CBullet()
	: m_bulletDamege(1)
	, m_bulletDirection(Vec2(1.f, 0.f))
	, m_bulletSpeed(1000.f)
	, m_range(600.f)
	, m_theata(0.f)
{
	m_bulletDirection.Normalize();
	CreateCollider();
	GetCollider()->SetScale(Vec2(10.f, 10.f));
	
	CTexture* tex = CResourceManager::GetInst()->LoadTexture(L"PLAYER_BULLET", L"texture\\miko_bullet.bmp");

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"PLAYER_BULLET", tex, Vec2(0, 0), Vec2(40, 80), Vec2(40, 0), 0.1f, 15,false);
	
	GetAnimator()->Play(L"PLAYER_BULLET", false);
}

CBullet::CBullet(const wstring& _name, const wstring& _relatviePath)
	: m_bulletDamege(0)
	, m_bulletDirection(Vec2(1.f, 0.f))
	, m_bulletSpeed(500.f)
	, m_range(600.f)
	, m_theata(0.f)
{
	m_bulletDirection.Normalize();
	CreateCollider();
	GetCollider()->SetScale(Vec2(10.f, 10.f));

	CTexture* tex = CResourceManager::GetInst()->LoadTexture(_name, _relatviePath);

	CreateAnimator();
	GetAnimator()->CreateAnimation(_name, tex, Vec2(0, 0), Vec2(40, 80), Vec2(40, 0), 0.1f, 1,false);

	GetAnimator()->Play(_name, true);
}

CBullet::~CBullet()
{
}

void CBullet::Update()
{
	Vec2 position = GetPos();
	
	
	position.x += m_bulletDirection.x * m_bulletSpeed*fDT;
	position.y += m_bulletDirection.y * m_bulletSpeed*fDT;

	SetPos(position);
	
	//사거리를 벗어나는 탄환삭제

  	if (IsOutOfRange())
	{
		DeleteObject(this);
	}
	GetAnimator()->FinalUpdate();
}

void CBullet::Render(HDC _dc)
{
	ComponentRender(_dc);
}

bool CBullet::IsOutOfRange()
{
	return m_range - m_bulletShootPos.Distance(GetPos()) < 0;
}

void CBullet::OnCollisionEnter(CCollider* _col)
{
	
}

void CBullet::OnCollision(CCollider* _col)
{
	if (_col->GetOwner()->GetName() == L"Monster")
	{
		DeleteObject(this);
	}
	else if (_col->GetOwner()->GetName() == L"Player")
	{
		DeleteObject(this);
	}
}

void CBullet::FinalUpdate()
{
	CObject::FinalUpdate();
}


