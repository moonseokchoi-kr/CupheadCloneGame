#pragma once
#include "CObject.h"
class CGround
	: public CObject
{
public:
	CGround();
	~CGround();


public:
	// CObject��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render(HDC _dc);
	virtual void FinalUpdate();
	CLONE(CGround)
};

