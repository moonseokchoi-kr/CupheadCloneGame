#pragma once
class SelectGDI
{
public:
	SelectGDI(HDC _dc, PEN_TYPE _penType);
	SelectGDI(HDC _dc, BRUSH_TYPE _penType);
	~SelectGDI();
private:
	HPEN m_defaultPen;
	HBRUSH m_defaultBrush;
	HDC m_hdc;

};

