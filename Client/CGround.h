#pragma once
#include "CObject.h"
class CGround
	: public CObject
{
public:
	CGround();
	~CGround();


public:
	// CObject을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render(HDC _dc);
	virtual void FinalUpdate();
	CLONE(CGround)
};

