#include "pch.h"
#include "SelectGDI.h"
#include "CCore.h"
SelectGDI::SelectGDI(HDC _dc, PEN_TYPE _penType)
	:m_hdc(_dc)
	,m_defaultBrush(nullptr)
	,m_defaultPen(nullptr)
{
	HPEN pen = CCore::GetInst()->GetPen(_penType);
	m_defaultPen = (HPEN)SelectObject(_dc, pen);
}

SelectGDI::SelectGDI(HDC _dc, BRUSH_TYPE _brushType)
	: m_hdc(_dc)
	, m_defaultBrush(nullptr)
	, m_defaultPen(nullptr)
{
	HBRUSH brush = CCore::GetInst()->GetBrush(_brushType);
	m_defaultPen = (HPEN)SelectObject(_dc, brush);
}

SelectGDI::~SelectGDI()
{
	SelectObject(m_hdc, m_defaultPen);
	SelectObject(m_hdc, m_defaultBrush);
}
