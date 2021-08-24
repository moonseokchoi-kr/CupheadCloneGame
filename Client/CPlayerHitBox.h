#pragma once
#include "CHitBox.h"

class CPlayer;
class CPlayerHitBox :
    public CHitBox
{
public:
    CPlayerHitBox();
    ~CPlayerHitBox();
    CLONE(CPlayerHitBox);
public:
	// CHitBox��(��) ���� ��ӵ�
	virtual void Update() override;
    virtual void OnCollision(CCollider* _col);
    virtual void OnCollisionEnter(CCollider* _col);
    virtual void OnCollisionExit(CCollider* _col);
private:
    CPlayer* m_owner;

    friend class CPlayer;


};

