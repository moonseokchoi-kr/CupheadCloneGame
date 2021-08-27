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
	CResourceManager::GetInst()->LoadTexture(L"canetion_background_sky", L"texture\\cuphead\\background\\canetion_background.bmp");
	CResourceManager::GetInst()->LoadTexture(L"canetion_background_yard", L"texture\\cuphead\\background\\canetion_background_tree.bmp");
	CResourceManager::GetInst()->LoadTexture(L"canetion_background_tree", L"texture\\cuphead\\background\\canetion_tree.bmp");
	CResourceManager::GetInst()->LoadTexture(L"botanic_background_1", L"texture\\cuphead\\background\\botanic_background_1.bmp");
	CResourceManager::GetInst()->LoadTexture(L"botanic_ground", L"texture\\cuphead\\background\\botanic_ground.bmp");
	CResourceManager::GetInst()->LoadTexture(L"botanic_background_cloud_1", L"texture\\cuphead\\background\\botanic_background_cloud_1.bmp");
	CResourceManager::GetInst()->LoadTexture(L"botanic_background_cloud_2", L"texture\\cuphead\\background\\botanic_background_cloud_2.bmp");
	CResourceManager::GetInst()->LoadTexture(L"botanic_background_cloud_3", L"texture\\cuphead\\background\\botanic_background_cloud_3.bmp");
	CResourceManager::GetInst()->LoadTexture(L"botanic_background_cloud_4", L"texture\\cuphead\\background\\botanic_background_cloud_4.bmp");
	CResourceManager::GetInst()->LoadTexture(L"botanic_background_cloud_5", L"texture\\cuphead\\background\\botanic_background_cloud_5.bmp");
	CResourceManager::GetInst()->LoadTexture(L"botanic_background_tree_1", L"texture\\cuphead\\background\\botanic_background_tree_1.bmp");
	CResourceManager::GetInst()->LoadTexture(L"botanic_background_tree_2", L"texture\\cuphead\\background\\botanic_background_tree_2.bmp");
	CResourceManager::GetInst()->LoadTexture(L"botanic_background_tree_3", L"texture\\cuphead\\background\\botanic_background_tree_3.bmp");
	CResourceManager::GetInst()->LoadTexture(L"botanic_background_tree_4", L"texture\\cuphead\\background\\botanic_background_tree_4.bmp");
	CResourceManager::GetInst()->LoadTexture(L"botanic_background_tree_5", L"texture\\cuphead\\background\\botanic_background_tree_5.bmp");
	CResourceManager::GetInst()->LoadTexture(L"botanic_ground", L"texture\\cuphead\\background\\botanic_ground.bmp");
	CResourceManager::GetInst()->LoadTexture(L"botanic_plant_1", L"texture\\cuphead\\background\\botanic_plant_1.bmp");
	CResourceManager::GetInst()->LoadTexture(L"botanic_plant_2", L"texture\\cuphead\\background\\botanic_plant_2.bmp");
	CResourceManager::GetInst()->LoadTexture(L"botanic_plant_3", L"texture\\cuphead\\background\\botanic_plant_3.bmp");
	CResourceManager::GetInst()->LoadTexture(L"botanic_plant_4", L"texture\\cuphead\\background\\botanic_plant_4.bmp");
	CResourceManager::GetInst()->LoadTexture(L"botanic_plant_5", L"texture\\cuphead\\background\\botanic_plant_5.bmp");
	CResourceManager::GetInst()->LoadTexture(L"botanic_plant_6", L"texture\\cuphead\\background\\botanic_plant_6.bmp");
	CResourceManager::GetInst()->LoadTexture(L"botanic_sky", L"texture\\cuphead\\background\\botanic_sky.bmp");
	
	
	m_backGroundArray[TYPE_NUMBER(BACKGROUND_TYPE::CANEGY_SKY)] = L"canetion_background_sky";
	m_backGroundArray[TYPE_NUMBER(BACKGROUND_TYPE::CANEGY_BACKGROUND)] = L"canetion_background_tree";
	m_backGroundArray[TYPE_NUMBER(BACKGROUND_TYPE::SLIME_BACKGROUND)] = L"canetion_background_yard";
	m_backGroundArray[TYPE_NUMBER(BACKGROUND_TYPE::VEGGIE_BACKGROUND)] = L"botanic_background_1";
	m_backGroundArray[TYPE_NUMBER(BACKGROUND_TYPE::BOTANIC_GROUND)] = L"botanic_ground";
	m_backGroundArray[TYPE_NUMBER(BACKGROUND_TYPE::BOTANIC_CLOUD_1)] = L"botanic_background_cloud_1";
	m_backGroundArray[TYPE_NUMBER(BACKGROUND_TYPE::BOTANIC_CLOUD_2)] = L"botanic_background_cloud_2";
	m_backGroundArray[TYPE_NUMBER(BACKGROUND_TYPE::BOTANIC_CLOUD_3)] = L"botanic_background_cloud_3";
	m_backGroundArray[TYPE_NUMBER(BACKGROUND_TYPE::BOTANIC_CLOUD_4)] = L"botanic_background_cloud_4";
	m_backGroundArray[TYPE_NUMBER(BACKGROUND_TYPE::BOTANIC_CLOUD_5)] = L"botanic_background_cloud_5";
	m_backGroundArray[TYPE_NUMBER(BACKGROUND_TYPE::BOTANIC_TREE_1)] = L"botanic_background_tree_1";
	m_backGroundArray[TYPE_NUMBER(BACKGROUND_TYPE::BOTANIC_TREE_2)] = L"botanic_background_tree_2";
	m_backGroundArray[TYPE_NUMBER(BACKGROUND_TYPE::BOTANIC_TREE_3)] = L"botanic_background_tree_3";
	m_backGroundArray[TYPE_NUMBER(BACKGROUND_TYPE::BOTANIC_TREE_4)] = L"botanic_background_tree_4";
	m_backGroundArray[TYPE_NUMBER(BACKGROUND_TYPE::BOTANIC_TREE_5)] = L"botanic_background_tree_5";
	m_backGroundArray[TYPE_NUMBER(BACKGROUND_TYPE::BOTANIC_PLANT_1)] = L"botanic_plant_1";
	m_backGroundArray[TYPE_NUMBER(BACKGROUND_TYPE::BOTANIC_PLANT_2)] = L"botanic_plant_2";
	m_backGroundArray[TYPE_NUMBER(BACKGROUND_TYPE::BOTANIC_PLANT_3)] = L"botanic_plant_3";
	m_backGroundArray[TYPE_NUMBER(BACKGROUND_TYPE::BOTANIC_PLANT_4)] = L"botanic_plant_4";
	m_backGroundArray[TYPE_NUMBER(BACKGROUND_TYPE::BOTANIC_PLANT_5)] = L"botanic_plant_5";
	m_backGroundArray[TYPE_NUMBER(BACKGROUND_TYPE::BOTANIC_PLANT_6)] = L"botanic_plant_6";
	m_backGroundArray[TYPE_NUMBER(BACKGROUND_TYPE::BOTANIC_SKY)] = L"botanic_sky";


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



