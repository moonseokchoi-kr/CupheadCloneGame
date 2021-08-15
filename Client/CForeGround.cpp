#include "pch.h"
#include "CForeGround.h"
#include "CTexture.h"

#include "CCamera.h"
#include "CResourceManager.h"
#include "SelectGDI.h"

CForeGround::CForeGround()
{
	CResourceManager::GetInst()->LoadTexture(L"botanic_foreground_1", L"texture\\cuphead\\foreground\\botanic_foreground_1.bmp");
	CResourceManager::GetInst()->LoadTexture(L"botanic_foreground_2", L"texture\\cuphead\\foreground\\botanic_foreground_2.bmp");
	CResourceManager::GetInst()->LoadTexture(L"canetion_background_stone", L"texture\\cuphead\\foreground\\canetion_background_stone.bmp");

	m_foreGroundArray[TYPE_NUMBER(FOREGROUND_TYPE::BOTANIC_PLANT)] = L"botanic_foreground_1";
	m_foreGroundArray[TYPE_NUMBER(FOREGROUND_TYPE::BOTANIC_PENSE)] = L"botanic_foreground_2";
	m_foreGroundArray[TYPE_NUMBER(FOREGROUND_TYPE::CANETION_STONE)] = L"canetion_background_stone";

}

CForeGround::~CForeGround()
{
}

void CForeGround::Update()
{
}

void CForeGround::Render(HDC _dc)
{
	Vec2 pos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 scale = GetScale();
	BLENDFUNCTION bf = {};
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = AC_SRC_ALPHA;
	bf.SourceConstantAlpha = 255;

	AlphaBlend(
		_dc,
		(int)pos.x,
		(int)pos.y,
		(int)scale.x,
		(int)scale.y,
		m_currentTex->GetDC(),
		0, 0,
		(int)m_currentTex->Width(),
		(int)m_currentTex->Height(),
		bf
	);

	if (IsLButtonDown())
	{
		SelectGDI select(_dc, PEN_TYPE::GREEN_BOLD);
		SelectGDI select1(_dc, BRUSH_TYPE::HOLLOW);
		Rectangle(
			_dc,
			int(pos.x),
			int(pos.y),
			int(pos.x + scale.x),
			int(pos.y + scale.y)
		);
	}
}

void CForeGround::Save(FILE* _file)
{
	CGameObject::Save(_file);
	int _type = TYPE_NUMBER(m_type);
	fwrite(&_type, sizeof(int), 1, _file);
}

void CForeGround::Load(FILE* _file)
{
	CGameObject::Load(_file);
	int _type = 0;
	fread(&_type, sizeof(int), 1, _file);
	m_type = (FOREGROUND_TYPE)_type;
	setTexture();
}

void CForeGround::setTexture()
{
	m_currentTex = CResourceManager::GetInst()->FindTexture(m_foreGroundArray[TYPE_NUMBER(m_type)]);
	SetScale(Vec2((float)m_currentTex->Width(), (float)m_currentTex->Height()));
}
