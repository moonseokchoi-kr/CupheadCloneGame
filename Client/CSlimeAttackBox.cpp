#include "pch.h"
#include "CSlimeAttackBox.h"
#include "CCollider.h"
#include "CSlime.h"
CSlimeAttackBox::CSlimeAttackBox()
	:m_attackCount(0)
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(300.f,300.f));
}

CSlimeAttackBox::~CSlimeAttackBox()
{
}

void CSlimeAttackBox::Update()
{
	//펀치 공격에만 동작
	//페이즈 1의 펀치인지 2의 펀치인지를 잘 파악해서 동작
	Vec2 pos = GetOwner()->GetPos();
	SetPos(pos + m_offset);
}

void CSlimeAttackBox::Fire()
{
}

void CSlimeAttackBox::Render(HDC _dc)
{
}
