#include "pch.h"
#include "CGameObject.h"
#include "CCollider.h"


#include "CSceneManager.h"
#include "CKeyManager.h"
#include "CCamera.h"
#include "SelectGDI.h"

CGameObject::CGameObject()
	:m_parentObejct(nullptr)
	,m_mouseOn(false)
	,m_lButtonDown(false)
	,m_select(false)
	,m_type(GAMEOBJECT_TYPE::END)
{
	m_gameObjectArray[TYPE_NUMBER(GAMEOBJECT_TYPE::FLOWER_PLATFORM_A)] = L"FLOWER_PLATFORM_A";
	m_gameObjectArray[TYPE_NUMBER(GAMEOBJECT_TYPE::FLOWER_PLATFORM_B)] = L"FLOWER_PLATFORM_B";
	m_gameObjectArray[TYPE_NUMBER(GAMEOBJECT_TYPE::FLOWER_PLATFORM_C)] = L"FLOWER_PLATFORM_C";

}

CGameObject::~CGameObject()
{
}

void CGameObject::Start()
{
}

void CGameObject::Update()
{

}

void CGameObject::FinalUpdate()
{
	CObject::FinalUpdate();
	if(CSceneManager::GetInst()->GetCurrentScene()->GetSceneName() == L"Tool Scene")
		MouseOnCheck();

}

void CGameObject::Render(HDC _dc)
{
}

void CGameObject::MouseOnCheck()
{
	Vec2 pos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 mousePos = CCamera::GetInst()->GetRenderPos(MOUSE_POS);
	Vec2 scale = GetScale();
	
	if ((pos.x - scale.x / 2.f) <= mousePos.x && mousePos.x <= (pos.x + scale.x / 2.f) && (pos.y - scale.y / 2.f) <= mousePos.y && mousePos.y <= (pos.y + scale.y / 2.f))
	{
		m_mouseOn = true;
	}
	else
	{
		m_mouseOn = false;
	}



}

void CGameObject::ChangeSize(Vec2 _size)
{
	SetScale(_size);
	if(nullptr != GetCollider())
		GetCollider()->SetScale(_size);
}

void CGameObject::MouseOn()
{
	if (IsLButtonDown())
	{
		Vec2 diff =MOUSE_POS - m_dragStart;
		Vec2 curPos = GetPos();

		curPos += diff;
		
		SetPos(curPos);

		m_dragStart = MOUSE_POS;
	}
	
}

void CGameObject::MouseLButtonDown()
{
	m_dragStart = MOUSE_POS;
}

void CGameObject::MouseLButtonUp()
{
}

void CGameObject::Save(FILE* _file)
{
	Vec2 pos = GetPos();
	Vec2 scale = GetScale();
	int offset = GetOffset();

	//현재 위치
	fwrite(&pos, sizeof(Vec2), 1, _file);
	//크기
	fwrite(&scale, sizeof(Vec2), 1, _file);
	//렌더링 오프셋
	fwrite(&offset, sizeof(int), 1, _file);
}

void CGameObject::Load(FILE* _file)
{
	Vec2 pos = GetPos();
	Vec2 scale = GetScale();
	int offset = GetOffset();
	//현재 위치
	fread(&pos, sizeof(Vec2), 1, _file);
	//크기
	fread(&scale, sizeof(Vec2), 1, _file);
	//렌더링 오프셋
	fread(&offset, sizeof(int), 1, _file);


	SetPos(pos);
	SetScale(scale);
	SetOffset(offset);
}
