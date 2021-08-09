#include "pch.h"
#include "CRedUfo.h"

#include "CTexture.h"
#include "CBullet.h"
#include "CHomingBullet.h"
#include "CCollider.h"
#include "CResourceManager.h"
#include "CTimeManager.h"
#include "CAnimator.h"

CRedUfo::CRedUfo()
	:m_centerPos()
	, m_moveSpeed(150.f)
	, m_moveDir(Vec2(-1.f, 1.f))
	, m_coolTime(1.5f)
	, m_shootDir()
	, m_moveDistance(1000.f)
	, m_theata(0)
	, m_Acc(0)
	, m_health(1)
{

	CTexture* m_tex = CResourceManager::GetInst()->LoadTexture(L"UFO_ENEMIES", L"texture\\ufo_enemies.bmp");
	CreateCollider();
	GetCollider()->SetScale(Vec2(80.f, 80.f));
	SetName(L"Monster");
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"RED_UFO", m_tex, Vec2(0, 100), Vec2(96.f, 100.f), Vec2(96.f, 0.f), 0.3f, 4);
	GetAnimator()->Play(L"RED_UFO", true);
	random_device rd;
	mt19937  gen(rd());
	uniform_int_distribution<int> dist(0, 30);

	m_theata = (float)dist(gen);

}
CRedUfo::~CRedUfo()
{
}

void CRedUfo::Update()
{
	Vec2 pos = GetPos();
	if (pos.x > WINDOW_WIDTH - m_moveDistance)
	{
		pos.x += m_moveDir.x * m_moveSpeed * fDT;
		pos.y += sin(m_theata*fDT) * m_moveSpeed * fDT;
	}

	m_Acc += fDT;

	if (m_Acc >= m_coolTime)
	{
		fire();
		m_Acc = 0;
	}

	SetPos(pos);

	GetAnimator()->FinalUpdate();

	if (m_health <= 0)
	{
		DeleteObject(this);
	}
}

void CRedUfo::Render(HDC _dc)
{
	ComponentRender(_dc);
}

void CRedUfo::FinalUpdate()
{
	CObject::FinalUpdate();
}

void CRedUfo::OnCollisionEnter(CCollider* _col)
{
	if (_col->GetOwner()->GetName() == L"PlayerBullet")
	{
		CBullet* bullet = (CBullet*)_col->GetOwner();
		m_health -= bullet->GetDamege();
	}
	if (_col->GetOwner()->GetName() == L"SubweaponBullet")
	{
		CHomingBullet* bullet = (CHomingBullet*)_col->GetOwner();
		m_health -= bullet->GetDamege();
	}
}

void CRedUfo::fire()
{
	Vec2 pos = GetPos();
	CBullet* bullet;
	bullet = new CBullet(L"monster_bullet", L"texture\\Monster_Bullet.bmp");
	bullet->SetDirection(Vec2(-1.f, -1.f));
	bullet->SetFirePos(Vec2(pos.x - GetScale().x, pos.y - GetScale().y));
	bullet->SetName(L"MonsterBullet");
	CreateObject(bullet, GROUP_TYPE::MONSTER_BULLET, Vec2(pos.x - GetScale().x, pos.y - GetScale().y), Vec2(40.f, 80.f));

	bullet = new CBullet(L"monster_bullet", L"texture\\Monster_Bullet.bmp");
	bullet->SetDirection(Vec2(-1.f, 0.f));
	bullet->SetFirePos(Vec2(pos.x - GetScale().x, pos.y + GetScale().y));
	bullet->SetName(L"MonsterBullet");
	CreateObject(bullet, GROUP_TYPE::MONSTER_BULLET, Vec2(pos.x - GetScale().x, pos.y + GetScale().y), Vec2(40.f, 80.f));

	bullet = new CBullet(L"monster_bullet", L"texture\\Monster_Bullet.bmp");
	bullet->SetDirection(Vec2(-1.f, 1.f));
	bullet->SetFirePos(Vec2(pos.x - GetScale().x, pos.y));
	bullet->SetName(L"MonsterBullet");
	CreateObject(bullet, GROUP_TYPE::MONSTER_BULLET, Vec2(pos.x - GetScale().x, pos.y), Vec2(40.f, 80.f));
}

