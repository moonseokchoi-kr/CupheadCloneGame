#include "pch.h"
#include "CGameObject.h"
#include "CCollider.h"


#include "CSceneManager.h"
#include "CKeyManager.h"
#include "CCamera.h"
#include "SelectGDI.h"

CGameObject::CGameObject()
{
	m_gameObjectArray[TYPE_NUMBER(GAMEOBJECT_TYPE::FLOWER_PLATFORM_A)] = L"FLOWER_PLATFORM_A";
	m_gameObjectArray[TYPE_NUMBER(GAMEOBJECT_TYPE::FLOWER_PLATFORM_B)] = L"FLOWER_PLATFORM_B";
	m_gameObjectArray[TYPE_NUMBER(GAMEOBJECT_TYPE::FLOWER_PLATFORM_C)] = L"FLOWER_PLATFORM_C";
	m_gameObjectArray[TYPE_NUMBER(GAMEOBJECT_TYPE::GROUND)] = L"GROUND";
	m_gameObjectArray[TYPE_NUMBER(GAMEOBJECT_TYPE::DARK_TOWER)] = L"DARK_TOWER";
	m_gameObjectArray[TYPE_NUMBER(GAMEOBJECT_TYPE::NOMAL_TOWER)] = L"NORMAL_TOWER";
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

	if (pos.x <= mousePos.x && mousePos.x <= pos.x + scale.x && pos.y <= mousePos.y && mousePos.y <= pos.y + scale.y)
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
		Vec2 diff = MOUSE_POS - m_dragStart;
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
