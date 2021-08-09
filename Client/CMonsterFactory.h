#pragma once

class CMonster;

enum class MON_TYPE
{
	NORMAL,
	RANGE,
};

class CMonsterFactory
{
public:
	static CMonster* CreateMonster(MON_TYPE _type, Vec2 _vPos, Vec2 _scale);
private:
	CMonsterFactory() = delete;
	~CMonsterFactory() = delete;
};

