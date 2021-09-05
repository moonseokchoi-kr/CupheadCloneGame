#include "pch.h"
#include "CButtonUI.h"
#include "CTexture.h"
#include "CCamera.h"
#include "CSound.h"
#include "CResourceManager.h"
CButtonUI::CButtonUI(bool _cameraAffeted)
	:CUI(_cameraAffeted)
	,m_callBackFuction(nullptr)
	,m_param1(0)
	,m_param2(0)
	,m_tex(nullptr)
{
	m_sfx = CResourceManager::GetInst()->FindSound(L"PLAYER_MENU_SELECT");
}

CButtonUI::~CButtonUI()
{
}

void CButtonUI::Render(HDC _dc)
{
	if (nullptr == m_tex)
	{
		CUI::Render(_dc);
		return;
	}
	Vec2 pos = GetFinalPos();
	Vec2 scale = GetScale();
	if (IsCameraAffed())
	{
		pos = CCamera::GetInst()->GetRenderPos(pos);
	}
	if (IsLButtonDown())
	{
		BitBlt(
			_dc,
			(int)pos.x - 1,
			(int)pos.y - 1,
			(int)scale.x + 1,
			(int)scale.y + 1,
			m_tex->GetDC(),
			0,
			0,
			SRCCOPY);
	}
	BitBlt(
		_dc,
		(int)pos.x,
		(int)pos.y,
		(int)scale.x,
		(int)scale.y,
		m_tex->GetDC(),
		0,
		0,
		SRCCOPY);
}

void CButtonUI::MouseOn()
{
}

void CButtonUI::MouseLButtonDown()
{
}

void CButtonUI::MouseLButtonUp()
{
}

void CButtonUI::MouseLButtonClicked()
{
	if (nullptr != m_sceneVoidFunction)
	{
		m_sceneVoidFunction();
	}
	if (nullptr != m_callBackFuction)
	{
		m_callBackFuction(m_param1, m_param2);
	}
	if (m_sceneInst && m_sceneFunction)
	{
		m_sfx->Play(false);
		m_sfx->SetPosition(50.f);
		m_sfx->SetVolume(100.f);
		((*m_sceneInst).*m_sceneFunction)();
	}
	if (m_sceneInst && m_sceneIntFunction)
	{
		((*m_sceneInst).*m_sceneIntFunction)((int)m_param1);
	}
	if (nullptr != m_sceneTypeFunction)
	{
		m_sfx->Play(false);
		m_sfx->SetPosition(50.f);
		m_sfx->SetVolume(100.f);
		m_sceneTypeFunction((SCENE_TYPE)m_param1);
	}
}
