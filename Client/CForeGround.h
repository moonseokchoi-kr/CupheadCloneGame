#pragma once
#include "CGameObject.h"


class CTexture;

class CForeGround :
    public CGameObject
{
public:
	CForeGround();
	~CForeGround();
	CLONE(CForeGround);
public:
	virtual void Update();
	virtual void Render(HDC _dc);

	virtual void Save(FILE* _file);
	virtual void Load(FILE* _file);
public:
	void SetType(FOREGROUND_TYPE _t) { m_type = _t; setTexture(); }

private:
	void setTexture();
private:
	CTexture* m_currentTex;        //배경 텍스쳐
	FOREGROUND_TYPE m_type;




	array<const wchar_t*, TYPE_NUMBER(BACKGROUND_TYPE::END)> m_foreGroundArray;
};

