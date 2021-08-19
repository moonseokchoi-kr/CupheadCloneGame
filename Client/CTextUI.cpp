#include "pch.h"
#include "CTextUI.h"
#include "CGameObject.h"
#include "CCamera.h"
#include "CKeyManager.h"
CTextUI::CTextUI(bool _cameraAffeted)
	:CUI(_cameraAffeted)
{
}

void CTextUI::Update()
{
	if (isMouseAttached)
	{
		Vec2 pos = CCamera::GetInst()->GetRealPos(MOUSE_POS);
		pos += Vec2(20.f, 20.f);
		SetPos(pos);
		pos = GetPos();
		m_text = L"X: " + to_wstring((int)pos.x) + L" / Y: " + to_wstring((int)pos.y);
	}
}

void CTextUI::Render(HDC _dc)
{
	Vec2 pos = GetFinalPos();
	if (IsCameraAffed())
	{
		pos = CCamera::GetInst()->GetRenderPos(pos);
	}
	Vec2 scale = GetScale();
	TextOutW(
		_dc,
		pos.x,
		pos.y,
		m_text.c_str(),
		m_text.length()
	);

}