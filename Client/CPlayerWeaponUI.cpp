#include "pch.h"
#include "CPlayerWeaponUI.h"
#include "CTexture.h"
#include "CResourceManager.h"
#include "CPlayerAttackBox.h"
#include "CTimeManager.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "vector.h"
CPlayerWeaponUI::CPlayerWeaponUI()
	:CUI(false)
	,m_owner(nullptr)
	,m_isActive(false)
	,m_meaningTime(0.5f)
	,m_accTime(0.f)
	,m_bulletType(BULLET_TYPE::END)
{
	CTexture* weaponUITex = CResourceManager::GetInst()->FindTexture(L"weaponUITex");
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"CHASER_UI", weaponUITex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(80.f, 0.f), 1 / 30.f, 3, false);
	GetAnimator()->CreateAnimation(L"PEASHOOT_UI", weaponUITex, Vec2(240.f, 0.f), Vec2(80.f, 80.f), Vec2(80.f, 0.f), 1 / 30.f, 3, false);
	SetScale(Vec2(80.f, 80.f));
	SetPos(Vec2(120.f, 840.f));

}

CPlayerWeaponUI::~CPlayerWeaponUI()
{
}

void CPlayerWeaponUI::Update()
{
	if (!m_isActive)
		return;
	if (m_owner->GetCurrentBullet() != m_bulletType)
	{
		if (m_bulletType == BULLET_TYPE::CHASER)
		{
			m_bulletType = m_owner->GetCurrentBullet();
			GetAnimator()->Play(L"PEASHOOT_UI", true);
		}
		else if (m_bulletType == BULLET_TYPE::PEASHOOT)
		{
			m_bulletType = m_owner->GetCurrentBullet();
			GetAnimator()->Play(L"CHASER_UI", true);
		}
	}
	Vec2 pos = GetPos();

	if (m_toggle)
	{
		m_accTime += fDT;
	
		if (m_accTime>=m_meaningTime)
		{
			pos.y += (80.f / m_meaningTime) * fDT;
		}
		if(840<= pos.y)
		{
			pos.y = 840.f;
			m_accTime = 0;
			m_isActive = false;
			m_toggle = false;
			SetPos(pos);
			return;
		}
	}
	else if(!m_toggle)
	{
		if (800.f >= pos.y)
		{
			m_toggle = true;
		}
		pos.y -= (80.f / m_meaningTime) * fDT;
		
	}
		
	SetPos(pos);
}

void CPlayerWeaponUI::Render(HDC _dc)
{
	if (!m_isActive)
		return;
	ComponentRender(_dc);
}
