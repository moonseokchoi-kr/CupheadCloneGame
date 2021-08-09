#include "pch.h"
#include "CTileButtonUI.h"
#include "CTexture.h"
#include "CResourceManager.h"
#include "SelectGDI.h"
#include "CCamera.h"
CTileButtonUI::CTileButtonUI(bool _cameraAffected)
	:CButtonUI(_cameraAffected)
	, m_callBackFuction(nullptr)
	, m_sceneInst(nullptr)
	,m_idx(0)
{
	SetScale(Vec2(64.f, 64.f));
	m_tex = CResourceManager::GetInst()->LoadTexture(L"Tile", L"texture\\tile\\TILE.bmp");
}

CTileButtonUI::~CTileButtonUI()
{
}

void CTileButtonUI::Render(HDC _dc)
{
	if (nullptr == m_tex)
	{
		return;
	}
	//Ÿ�� �ؽ����� ���� ��������
	UINT width = m_tex->Width();
	UINT height = m_tex->Height();
	//�ִ� ��� ���� ���� ���ϱ�
	UINT maxCol = width / TILE_SIZE;
	UINT maxRow = height / TILE_SIZE;
	//�� �ε����� �࿭ ��ġ ���ϱ�
	UINT curRow = (UINT)m_idx / maxCol;
	UINT curCol = (UINT)m_idx % maxCol;

	if (maxRow <= curRow)
	{
		assert(nullptr);
	}

	Vec2 pos = GetFinalPos();
	Vec2 scale = GetScale();
	if (IsCameraAffed())
	{
		pos = CCamera::GetInst()->GetRenderPos(pos);
	}
	
	BitBlt(
		_dc,
		(int)pos.x,
		(int)pos.y,
		(int)scale.x,
		(int)scale.y,
		m_tex->GetDC(),
		curCol * TILE_SIZE,
		curRow * TILE_SIZE,
		SRCCOPY);
	if (IsLButtonDown())
	{
		
		BitBlt(
			_dc,
			(int)pos.x - 1,
			(int)pos.y - 1,
			(int)scale.x + 1,
			(int)scale.y + 1,
			m_tex->GetDC(),
			curCol * TILE_SIZE,
			curRow * TILE_SIZE,
			SRCCOPY);
	}
	if (IsSelect())
	{
		SelectGDI select(_dc, PEN_TYPE::GREEN_BOLD);
		SelectGDI select1(_dc, BRUSH_TYPE::HOLLOW);
		Rectangle(
			_dc,
			(int)pos.x,
			(int)pos.y,
			(int)(pos.x + scale.x),
			(int)(pos.y + scale.y)
		);
	}
}

void CTileButtonUI::MouseOn()
{
}

void CTileButtonUI::MouseLButtonDown()
{
}

void CTileButtonUI::MouseLButtonUp()
{
}

void CTileButtonUI::MouseLButtonClicked()
{
	if (m_sceneInst && m_callBackFuction)
	{
		((*m_sceneInst).*m_callBackFuction)(m_idx);
	}
}
