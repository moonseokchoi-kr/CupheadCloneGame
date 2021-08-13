#pragma once
#include "CGameObject.h"
class CWall :
    public CGameObject
{
public:
    CWall();
    ~CWall();
    CLONE(CWall);
public:
	virtual void Start();
	virtual void Update();
	virtual void FinalUpdate();
	virtual void Render(HDC _dc);

	virtual void OnCollisionEnter(CCollider* _col);
	virtual void OnCollision(CCollider* _col);
	virtual void OnCollisionExit(CCollider* _col);
};

