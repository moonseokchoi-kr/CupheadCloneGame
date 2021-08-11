#include "pch.h"
#include "CGroundTile.h"

CGroundTile::CGroundTile()
{
	SetType(TILE_TYPE::GROUND);
}

CGroundTile::~CGroundTile()
{
}

void CGroundTile::Update()
{
}

void CGroundTile::Render(HDC _dc)
{
	ComponentRender(_dc);
	CTile::Render(_dc);
}

void CGroundTile::OnCollision(CCollider* _col)
{
}

void CGroundTile::OnCollisionEnter(CCollider* _col)
{
}

void CGroundTile::OnCollisionExit(CCollider* _col)
{
}
