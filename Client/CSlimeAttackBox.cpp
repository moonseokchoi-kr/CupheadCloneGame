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
	//��ġ ���ݿ��� ����
	//������ 1�� ��ġ���� 2�� ��ġ������ �� �ľ��ؼ� ����
	Vec2 pos = GetOwner()->GetPos();
	SetPos(pos + m_offset);
}

void CSlimeAttackBox::Fire()
{
}

void CSlimeAttackBox::Render(HDC _dc)
{
}
