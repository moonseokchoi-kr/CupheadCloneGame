#pragma once

#define SINGLE(type) public:\
						static type* GetInst()\
						{\
							static type mgr;\
							return &mgr;\
						}\
					private:\
						type();\
						~type();


#define fDT CTimeManager::GetInst()->GetfDeltaTime()
#define DT CTimeManager::GetInst()->GetDeltaTime()

#define KEY_CHECK(key, state) CKeyManager::GetInst()->GetKeyState(key) == state
#define KEY_HOLD(key) KEY_CHECK(key,KEY_STATE::HOLD)
#define KEY_TAP(key) KEY_CHECK(key, KEY_STATE::TAP)
#define KEY_AWAY(key) KEY_CHECK(key, KEY_STATE::AWAY)
#define KEY_NONE(key) KEY_CHECK(key, KEY_STATE::NONE)

#define TYPE_NUMBER(_type) (UINT)_type

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 768

#define TOOL_WIDTH 1600
#define TOOL_HEIGHT 1200

#define MAP_SIZE 1280
#define TILE_SIZE 64
#define BACKGROND_WIDTH 1400
#define BACKGROND_HEIGHT 800


#define PI 3.141592


#define CLONE(type) type* Clone() {return new type(*this);}
#define MOUSE_POS CKeyManager::GetInst()->GetMousePos()
#define RESOLUTION Vec2(WINDOW_WIDTH, WINDOW_HEIGHT)
enum class GROUP_TYPE
{
	BACK_GROUND,
	
	PLAYER,
	PLAYER_BULLET,
	MONSTER,
	MONSTER_BULLET,
	WALL,
	TILE,
	FORE_GROUND,
	UI = 31,
	END = 32
};

enum class SCENE_TYPE
{
	TOOL,
	START,
	STAGE_01,
	STAGE_02,

	END,
};

enum class BRUSH_TYPE
{
	HOLLOW,
	BLACK,
	END,
};

enum class PEN_TYPE
{
	RED,
	GREEN,
	GREEN_BOLD,
	BLUE,
	BLACK,
	WHITE,
	END,
};

enum class EVENT_TYPE
{
	CREATE_OBJECT,
	DELETE_OBJECT,
	SCENE_CHANGE,
	STATE_CHANGE,
};

enum class MON_STATE
{
	IDLE,		//대기
	PATROL,		//순찰
	TRACE,		//추격
	ATTACK,		//공격
	HIT,		//공격받음
	MADE_OFF,	//도망
	DEAD,		//죽음
};

enum class PLAYER_STATE
{
	IDLE,
	WALK,
	RUN,
	HIT,
	ATTACK,
	DEAD
};
