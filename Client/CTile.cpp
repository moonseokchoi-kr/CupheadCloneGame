#include "pch.h"
#include "CTile.h"
#include "CTexture.h"
#include "CCamera.h"
#include "SelectGDI.h"

CTile::CTile()
	:m_tex(nullptr)
	,m_imgIdx(0)
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
	if (nullptr == m_tex)
	{
		return;
	}
	Vec2 renderPos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 scale = GetScale();
	if (-1 == m_imgIdx)
	{
		SelectGDI select(_dc, PEN_TYPE::GREEN);
		SelectGDI gdi(_dc, BRUSH_TYPE::HOLLOW);
		Rectangle(
			_dc,
			int(renderPos.x),
			int(renderPos.y),
			int(renderPos.x + scale.x),
			int(renderPos.y + scale.y)
		);
		return;
	}
	//Ÿ�� �ؽ����� ���� ��������
	UINT width = m_tex->Width();
	UINT height = m_tex->Height();
	//�ִ� ��� ���� ���� ���ϱ�
	UINT maxCol = width / TILE_SIZE;
	UINT maxRow = height / TILE_SIZE;
	//�� �ε����� �࿭ ��ġ ���ϱ�
	UINT curRow = (UINT)m_imgIdx / maxCol;
	UINT curCol = (UINT)m_imgIdx % maxCol;

	if (maxRow <= curRow)
	{
		assert(nullptr);
	}

	

	BitBlt(
		_dc,
		(int)renderPos.x,
		(int)renderPos.y,
		(int)scale.x,
		(int)scale.y,
		m_tex->GetDC(),
		curCol * TILE_SIZE,
		curRow * TILE_SIZE,
		SRCCOPY	);
}

void CTile::FinalUpdate()
{
	CObject::FinalUpdate();
}

void CTile::Save(FILE* _file)
{
	fwrite(&m_imgIdx, sizeof(int), 1, _file);
}

void CTile::Load(FILE* _file)
{
	fread(&m_imgIdx, sizeof(int), 1, _file);
}

