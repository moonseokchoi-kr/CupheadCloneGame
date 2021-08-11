#include "pch.h"
#include "CTile.h"
#include "CTexture.h"
#include "CCamera.h"
#include "SelectGDI.h"

CTile::CTile()
	:m_tileType(TILE_TYPE::NONE)
{
	SetScale(Vec2(TILE_SIZE, TILE_SIZE));
}

CTile::~CTile()
{
}

void CTile::Update()
{

}

void CTile::Render(HDC _dc)
{
	Vec2 renderPos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 scale = GetScale();
	SelectGDI gdi(_dc, BRUSH_TYPE::HOLLOW);
	switch (m_tileType)
	{
	case TILE_TYPE::NONE:
	{
		SelectGDI select(_dc, PEN_TYPE::HOLLOW);
	}
	break;
	case TILE_TYPE::GROUND:
	{
		SelectGDI select1(_dc, PEN_TYPE::GREEN);
	}
	break;
	case TILE_TYPE::STOP:
	{
		SelectGDI select2(_dc, PEN_TYPE::BLUE);
	}
	break;
	default:
		break;
	}
	Rectangle(
		_dc,
		int(renderPos.x),
		int(renderPos.y),
		int(renderPos.x + scale.x),
		int(renderPos.y + scale.y)
	);
}

void CTile::FinalUpdate()
{
	CObject::FinalUpdate();
}

void CTile::Save(FILE* _file)
{
	fwrite(&m_tileType, sizeof(TILE_TYPE), 1, _file);
}

void CTile::Load(FILE* _file)
{
	fread(&m_tileType, sizeof(TILE_TYPE), 1, _file);
}

