#pragma once
#include "CHitBox.h"
class CMonster;
class CMonsterHitBox :
    public CHitBox
{
public:
	CMonsterHitBox();
	~CMonsterHitBox();
	CLONE(CMonsterHitBox);
public:
		// CHitBox��(��) ���� ��ӵ�
	virtual void Start() override;
	virtual void Update() override;
	virtual void FinalUpdate() override;
	virtual void OnCollision(CCollider* _col);
	virtual void OnCollisionEnter(CCollider* _col);
	virtual void OnCollisionExit(CCollider* _col);
private:
	CMonster* m_owner;
	float m_accTime;
	friend class CMonster;


};

