#include "pch.h"
#include "CHomingBulletTraile.h"
#include "CResourceManager.h"
#include "CTexture.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CChaserBullet.h"
CHomingBulletTraile::CHomingBulletTraile()
	:m_owner(nullptr)
{
	CTexture* trailTex = CResourceManager::GetInst()->FindTexture(L"TrailTex");
	//80,69
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"HOMING_BULLET_TRAIL", trailTex, Vec2(0.f, 0.f), Vec2(80.f, 69.f), Vec2(80.f, 0.f), 1 / 30.f, 12, false);
}

CHomingBulletTraile::~CHomingBulletTraile()
{
}

void CHomingBulletTraile::Update()
{
	Vec2 pos = m_owner->GetPos();
	pos += m_offSet;
	SetPos(pos);
	GetAnimator()->Play(L"HOMING_BULLET_TRAIL", false);
}

void CHomingBulletTraile::Render(HDC _dc)
{
	ComponentRender(_dc);
}
