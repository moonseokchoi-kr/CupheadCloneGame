#include "pch.h"
#include "PlayerSubweapon.h"
#include "CPlayer.h"
#include "CTexture.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CHomingBullet.h"

#include "CResourceManager.h"
#include "CTimeManager.h"
#include "CKeyManager.h"
PlayerSubweapon::PlayerSubweapon()
	: m_weaponMode(1)
	, m_cooltime(1.f)
	, m_owner(nullptr)
	, m_acc(0)
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(30.f, 30.f));

	SetScale(Vec2(77.f, 74.f));
	CTexture* tex = CResourceManager::GetInst()->LoadTexture(L"SUBWEAPON_ATTACK", L"texture\\subweapon.bmp");
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"SUBWEAPON_ATTACK", tex, Vec2(0, 0), Vec2(77.6f, 74.f), Vec2(77.6f, 0.f), 0.1f, 5,false);
	GetAnimator()->Play(L"SUBWEAPON_ATTACK", true);
}

PlayerSubweapon::~PlayerSubweapon()
{
}

void PlayerSubweapon::Update()
{
	if (nullptr != m_owner)
	{
		Vec2 pos = m_owner->GetPos();
		pos.x -= (GetScale().x / 2.f +30.f);
		pos.y -= GetScale().y / 1.5f;
		SetPos(pos);

		m_acc += fDT;

		if (m_acc >= m_cooltime)
		{
			fire();
			m_acc = 0;
		}
	}
	else
	{
		DeleteObject(this);
	}
	if(KEY_TAP(KEY::Q))
	{
		++m_weaponMode;
		if (m_weaponMode > 3)
		{
			m_weaponMode = 1;
		}
	}
	GetAnimator()->FinalUpdate();
}

void PlayerSubweapon::Render(HDC _dc)
{
	ComponentRender(_dc);
}

void PlayerSubweapon::FinalUpdate()
{
	CObject::FinalUpdate();
}

void PlayerSubweapon::OnCollisionEnter(CCollider* _col)
{
	if (_col->GetOwner()->GetName() == L"Monster")
	{
		DeleteObject(this);
	}
}

void PlayerSubweapon::fire()
{
	Vec2 pos = GetPos();
	CHomingBullet* bullet;
	switch (m_weaponMode)
	{
	case 3:
	{
		bullet = new CHomingBullet();
		bullet->SetDirection(Vec2(1.f, 1.f));
		bullet->SetName(L"SubweaponBullet");
		CreateObject(bullet, GROUP_TYPE::PLAYER_BULLET, Vec2(pos.x - GetScale().x, pos.y + GetScale().y), Vec2(50.f, 60.f));
	}
	case 2:
	{
		bullet = new CHomingBullet();
		bullet->SetDirection(Vec2(1.f, -1.f));
		bullet->SetName(L"SubweaponBullet");
		CreateObject(bullet, GROUP_TYPE::PLAYER_BULLET, Vec2(pos.x - GetScale().x, pos.y - GetScale().y), Vec2(50.f, 60.f));
	}
	case 1:
	{
		bullet = new CHomingBullet();
		bullet->SetDirection(Vec2(1.f, 0.f));
		bullet->SetName(L"SubweaponBullet");
		CreateObject(bullet, GROUP_TYPE::PLAYER_BULLET, Vec2(pos.x - GetScale().x, pos.y), Vec2(50.f, 60.f));
	}
	break;

	default:
		break;
	}
	
	



	

	

}
