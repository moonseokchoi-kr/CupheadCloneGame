#pragma once

class CMonster;

class CMonsterFactory
{
public:
	static CMonster* CreateMonster(MON_TYPE _type, Vec2 _vPos);
private:
	CMonsterFactory() = delete;
	~CMonsterFactory() = delete;
};

