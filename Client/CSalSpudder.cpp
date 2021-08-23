#include "pch.h"
#include "CSalSpudder.h"
#include "CSalAttackBox.h"
#include "CCollider.h"
#include "CRigidBody.h"
#include "CAnimator.h"
#include "SelectGDI.h"
#include "CSalBullet.h"
CSalSpudder::CSalSpudder()
{
	CreateCollider();
	CreateAnimator();
	GetCollider()->SetScale(Vec2(200.f, 200.f));
}

CSalSpudder::~CSalSpudder()
{
}
void CSalSpudder::Update()
{
	CMonster::Update();

}
void CSalSpudder::Render(HDC _dc)
{
	SelectGDI gdi(_dc, PEN_TYPE::GREEN_BOLD);

	ComponentRender(_dc);
}

void CSalSpudder::CreateAttackBox()
{
	m_attackBox = new CSalAttackBox;
	m_attackBox->m_owner = this;
}
