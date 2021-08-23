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
#define BACKGROUND_WIDTH 1600
#define BACKGROUND_HEIGHT 960


#define PI 3.141592


#define CLONE(type) type* Clone() {return new type(*this);}
#define MOUSE_POS CKeyManager::GetInst()->GetMousePos()
#define RESOLUTION Vec2(WINDOW_WIDTH, WINDOW_HEIGHT)
enum class GROUP_TYPE
{
	BACK_GROUND,
	GROUND,
	GAME_OBJ, //부모그룹 사용하지 않음
	SPAWN_OBJ,
	PLATFORM_OBJ,
	BOSS,
	MONSTER,
	MONSTER_BULLET,
	PLAYER,
	PLAYER_BULLET,

	FORE_GROUND,
	TILE,
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

enum class BACKGROUND_TYPE
{
	BOTANIC_BACKGROUND =0,
	BOTANIC_CLOUD_1,
	BOTANIC_CLOUD_2,
	BOTANIC_CLOUD_3,
	BOTANIC_CLOUD_4,
	BOTANIC_CLOUD_5,
	BOTANIC_TREE_1,
	BOTANIC_TREE_2,
	BOTANIC_TREE_3,
	BOTANIC_TREE_4,
	BOTANIC_TREE_5,
	BOTANIC_PLANT_1,
	BOTANIC_PLANT_2,
	BOTANIC_PLANT_3,
	BOTANIC_PLANT_4,
	BOTANIC_PLANT_5,
	BOTANIC_PLANT_6,
	BOTANIC_GROUND,
	BOTANIC_SKY,
	CANEGY_SKY,
	CANEGY_BACKGROUND,
	CANEGY_YARD,

	END = 37,
};

enum class FOREGROUND_TYPE
{
	CANETION_STONE = 24,
	BOTANIC_PLANT,
	BOTANIC_PENSE,

	END = 38,
};

enum class GAMEOBJECT_TYPE
{
	FLOWER_PLATFORM_A=30,
	FLOWER_PLATFORM_B,
	FLOWER_PLATFORM_C,
	GROUND,
	SPAWN,
	
	END = 39,
};

enum class BRUSH_TYPE
{
	HOLLOW,
	BLACK,
	RED,
	BLUE,
	GREEN,
	PURPLE,
	END,
};

enum class PEN_TYPE
{
	RED,
	RED_BOLD,
	GREEN,
	GREEN_BOLD,
	BLUE,
	BLUE_BOLD,
	BLACK,
	WHITE,
	HOLLOW,
	END,
};

enum class EVENT_TYPE
{
	CREATE_OBJECT,
	DELETE_OBJECT,
	SCENE_CHANGE,
	STATE_CHANGE,
	PLAYER_STATE_CHANGE,
};

enum class MON_STATE
{
	INTRO,		//등장
	IDLE,		//대기
	PATROL,		//순찰
	TRACE,		//추격
	ATTACK,		//공격
	MADE_OFF,	//도망
	DEAD,		//죽음
};

enum class PLAYER_STATE
{
	IDLE,
	TURN,
	RUN,
	DASH,
	HIT,
	ATTACK,
	JUMP,
	DEAD
};

enum class MON_TYPE
{
	NORMAL,
	RANGE,
	CAGNEY,
	OLLIE,
	CHAUNCEY,
	SAL,
	NONE,
};

enum class BULLET_TYPE
{
	PEASHOOT,
	PEASHOOT_EX,
	SPREAD,
	SPREAD_EX,
	ROUNDABOUT,
	ROUNDABOUT_EX,
	SAL_BULLET,
	CARROT_MISSILE,
	BEAM_BULLET,
	TEAR_BULLET,
	FACE_ATTACK,
	MON_SEED_BULLET,
	SEED_BULLET,
	BOOMERANG_BULLET,
	END,
};

enum class ATTACK_PATT
{
	PATT1,
	PATT2,
	PATT3,
	PATT4,
	END,
};