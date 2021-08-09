#include "pch.h"
#include "CGround.h"
#include "CCollider.h"
CGround::CGround()
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(1280.f,50.f));
	SetName(L"Ground");
}

CGround::~CGround()
{
}

void CGround::Update()
{

}

void CGround::Render(HDC _dc)
{
	ComponentRender(_dc);
}

void CGround::FinalUpdate()
{
	CObject::FinalUpdate();
}
