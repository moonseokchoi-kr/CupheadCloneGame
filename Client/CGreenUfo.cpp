#include "pch.h"
#include "CGreenUfo.h"
#include "CResourceManager.h"
#include "CBullet.h"
#include "CHomingBullet.h"
#include "CTexture.h"
#include "CAnimator.h"
#include "CCollider.h"
#include "CTimeManager.h"
CGreenUfo::CGreenUfo()
	:m_centerPos()
	, m_moveSpeed(150.f)
	, m_moveDir(Vec2(-1.f, 1.f))
	, m_coolTime(1.5f)
	, m_shootDir()
	, m_moveDistance(1400.f)
	, m_theata(0)
	, m_Acc(0)
	, m_health(1)
{
	CTexture* m_tex = CResourceManager::GetInst()->LoadTexture(L"UFO_ENEMIES", L"texture\\ufo_enemies.bmp");
	CreateCollider();
	GetCollider()->SetScale(Vec2(80.f, 80.f));
	SetName(L"Monster");
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"GREEN_UFO", m_tex, Vec2(0, 0), Vec2(96.f, 100.f), Vec2(96.f, 0.f), 0.3f, 4);
	GetAnimator()->Play(L"GREEN_UFO", true);
	random_device rd;
	mt19937  gen(rd());
	uniform_int_distribution<int> dist(0, 30);

	m_theata = (float)dist(gen);
}

CGreenUfo::~CGreenUfo()
{
}

void CGreenUfo::Update()
{
	Vec2 pos = GetPos();
	if (pos.x > WINDOW_WIDTH - m_moveDistance)
	{
		m_theata += m_moveSpeed * fDT;
		pos.x += m_moveDir.x * m_moveSpeed * fDT;
		pos.y += sin(m_theata) * m_moveSpeed * fDT;
	}
	else
	{
		m_moveDir = Vec2(1, -50);
		m_moveDir.Normalize();
		pos.x += m_moveDir.x * m_moveSpeed*6.f * fDT;
		pos.y += m_moveDir.y * m_moveSpeed*7.f* fDT;
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

void CGreenUfo::Render(HDC _dc)
{
	ComponentRender(_dc);
}

void CGreenUfo::FinalUpdate()
{
	CObject::FinalUpdate();
}

void CGreenUfo::OnCollisionEnter(CCollider* _col)
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

void CGreenUfo::fire()
{
	CBullet* bullet = new CBullet(L"monster_bullet", L"texture\\Monster_Bullet.bmp");
	bullet->SetDirection(Vec2(-1, 0));
	bullet->SetFirePos(Vec2(GetPos().x - GetScale().x / 2, GetPos().y));
	bullet->SetName(L"MonsterBullet");
	CreateObject(bullet, GROUP_TYPE::MONSTER_BULLET, Vec2(GetPos().x - GetScale().x / 2, GetPos().y), Vec2(40,80));
}

