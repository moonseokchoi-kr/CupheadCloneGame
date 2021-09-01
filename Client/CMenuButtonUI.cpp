#include "pch.h"
#include "CMenuButtonUI.h"
#include "CTexture.h"
#include "CResourceManager.h"
CMenuButtonUI::CMenuButtonUI()
	:CButtonUI(false)
	, m_width(320)
	, m_heigth(78)
	, m_index(0)
{
	m_tex = CResourceManager::GetInst()->FindTexture(L"MenuButtonTex");
}

CMenuButtonUI::~CMenuButtonUI()
{
}

void CMenuButtonUI::Render(HDC _dc)
{
	int index = m_index;
	if (nullptr == m_tex)
	{
		return;
	}
	if (IsMouseOn())
	{
		index += 6;
	}
	else
	{
		index = m_index;
	}
	//Ÿ�� �ؽ����� ���� ��������
	UINT width = m_tex->Width();
	UINT height = m_tex->Height();
	//�ִ� ��� ���� ���� ���ϱ�
	UINT maxCol = width / m_width;
	UINT maxRow = height / m_heigth;
	//�� �ε����� �࿭ ��ġ ���ϱ�
	UINT curRow = (UINT)index / maxCol;
	UINT curCol = (UINT)index % maxCol;

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
	BLENDFUNCTION bf = {};
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = AC_SRC_ALPHA;
	bf.SourceConstantAlpha = 255;

	AlphaBlend(
		_dc
		, (int)pos.x
		, (int)pos.y
		, (int)m_width
		, (int)m_heigth
		, m_tex->GetDC()
		, (int)curCol * m_width
		, (int)curRow * m_heigth
		, (int)m_width
		, (int)m_heigth
		, bf
	);
}





