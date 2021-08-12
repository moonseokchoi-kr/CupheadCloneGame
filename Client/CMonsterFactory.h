#pragma once

class CMonster;

enum class MON_TYPE
{
	NORMAL,
	RANGE,
	NONE,
};

class CMonsterFactory
{
public:
	static CMonster* CreateMonster(MON_TYPE _type, Vec2 _vPos);
private:
	CMonsterFactory() = delete;
	~CMonsterFactory() = delete;
};

