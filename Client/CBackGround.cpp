#include "pch.h"
#include "CBackGround.h"

#include "CTexture.h"

#include "CCamera.h"
#include "CKeyManager.h"
#include "CResourceManager.h"
#include "SelectGDI.h"




CBackGround::CBackGround()
	:m_type(BACKGROUND_TYPE::END)
	,m_currentTex(nullptr)
{
	CResourceManager::GetInst()->LoadTexture(L"VeggieBackgroundTex", L"texture\\cuphead\\background\\veggie_background.bmp");
	CResourceManager::GetInst()->LoadTexture(L"SlimeBackgroundTex", L"texture\\cuphead\\background\\slime_baground.bmp");

	m_backGroundArray[TYPE_NUMBER(BACKGROUND_TYPE::SLIME_BACKGROUND)] = L"SlimeBackgroundTex";
	m_backGroundArray[TYPE_NUMBER(BACKGROUND_TYPE::VEGGIE_BACKGROUND)] = L"VeggieBackgroundTex";


}

CBackGround::~CBackGround()
{
}
void CBackGround::Render(HDC _dc)
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
		(int)(pos.x-scale.x/2.f),
		(int)(pos.y-scale.y/2.f),
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
			(int)(pos.x-scale.x/2.f),
			(int)(pos.y-scale.y/2.f),
			(int)(pos.x+scale.x/2.f),
			(int)(pos.y+scale.y/2.f)
		);
	}
}
void CBackGround::Save(FILE* _file)
{
	CGameObject::Save(_file);
	//현재 타입
	int _type = TYPE_NUMBER(m_type);
	fwrite(&_type, sizeof(int), 1, _file);
}
void CBackGround::Load(FILE* _file)
{
	CGameObject::Load(_file);
	int _type = 0;
	fread(&_type, sizeof(int), 1, _file);
	m_type = (BACKGROUND_TYPE)_type;
	setTexture();
}
void CBackGround::Update()
{
	
}

void CBackGround::setTexture()
{
	m_currentTex = CResourceManager::GetInst()->FindTexture(m_backGroundArray[TYPE_NUMBER(m_type)]);
	SetScale(Vec2((float)m_currentTex->Width(), (float)m_currentTex->Height()));
}



