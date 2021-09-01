#include "pch.h"
#include "CSalAttackBox.h"
#include "CSound.h"
#include "CAnimation.h"
#include "CTexture.h"
#include "CResourceManager.h"
#include "CAnimator.h"
#include "CSalBullet.h"
#include "CTimeManager.h"


CSalAttackBox::CSalAttackBox()
	:m_shootCount(0)
	,m_bulletSpeed(600.f)
{
	SetOffset(Vec2(-150.f, 150.f));
	CreateAnimator();
	CTexture* shootDustTex = CResourceManager::GetInst()->FindTexture(L"PotatoShootDustTex");
	GetAnimator()->CreateAnimation(L"POATAO_SHOOT_DUST", shootDustTex, Vec2(0.f, 0.f), Vec2(235.f, 404.f), Vec2(235.f, 0.f), 1 / 30.f, 13, false);
}

CSalAttackBox::~CSalAttackBox()
{
}

void CSalAttackBox::Fire()
{
	
	Vec2 finalpos = GetPos();
	CSalBullet* salBullet = new CSalBullet;
	salBullet->SetPos(finalpos);
	salBullet->SetMoveDir(Vec2(-1, 0));
	salBullet->SetName(L"MonsterBullet");
	bulletInfo info = salBullet->GetInfo();
	info.bulletSpeed = m_bulletSpeed;
	salBullet->SetInfo(info);
	GetAnimator()->Play(L"POATAO_SHOOT_DUST", false);
	GetAnimator()->GetCurrentAnim()->SetFrame(0);
	if (m_shootCount == 3)
	{
		SetSFX(L"POTATO_WORM");
		GetSFX()->Play(false);
		GetSFX()->SetPosition(50.f);
		GetSFX()->SetVolume(100.f);
		salBullet->SetBulletType(SAL_BULLET_TYPE::WORM);
	}
	else
	{
		SetSFX(L"POTATO_DUST_" + to_wstring(m_shootCount + 1));
		GetSFX()->Play(false);
		GetSFX()->SetPosition(50.f);
		GetSFX()->SetVolume(100.f);
		salBullet->SetBulletType(SAL_BULLET_TYPE::DUST);

	}
	
	salBullet->Start();
	CreateObject(salBullet, GROUP_TYPE::MONSTER_BULLET);

	++m_shootCount;

	if(m_shootCount >3)
		m_shootCount = 0;
	
}

void CSalAttackBox::Render(HDC _dc)
{
	ComponentRender(_dc);
}
