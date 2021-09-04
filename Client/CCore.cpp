#include "pch.h"
#include "CCore.h"
#include "CObject.h"

#include "CTimeManager.h"
#include "CKeyManager.h"
#include "CSceneManager.h"
#include "CPathManager.h"
#include "CColliderManager.h"
#include "CUIManager.h"
#include "CCamera.h"
#include "CResourceManager.h"
#include "CGameObjectManager.h"
#include "CTexture.h"
#include "CSoundManager.h"

#include "resource.h"
#include "SelectGDI.h"
CCore::CCore()
	:m_hDc(nullptr)
	, m_hWnd(nullptr)
	, m_ptMonitorResolution{}
	, m_ptResolution{}
	, m_memTex(nullptr)
	, m_menu{}
	, m_brushs{}
	, m_pens{}
	, m_isDebug(false)
{
}

CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hDc);

	for (int i = 0; i < m_pens.size(); ++i)
	{
		DeleteObject(m_pens[i]);
	}
	DestroyMenu(m_menu);
}

int CCore::InitCore(HWND _hwnd, POINT _resolution)
{
	m_hWnd = _hwnd;
	m_ptResolution = _resolution;
	m_ptToolResolution = { 1600,960 };
	m_ptMonitorResolution = { GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN) };

	changeWindowSize(Vec2((float)m_ptResolution.x,(float)m_ptResolution.y), false);
	//DeviceContext설정
	m_hDc = GetDC(m_hWnd);
	m_menu = LoadMenu(nullptr, MAKEINTRESOURCEW(IDC_CLIENT));
	m_memTex = CResourceManager::GetInst()->CreateTexture(L"BackBuffer", m_ptToolResolution.x, m_ptToolResolution.y);
	
	CKeyManager::GetInst()->Init();
	CTimeManager::GetInst()->Init();
	CPathManager::GetInst()->Init();
	CCamera::GetInst()->Init();
	CSoundManager::GetInst()->init();
	loadResource();
	CSceneManager::GetInst()->Init();
	

	CreateBrushPen();
	

	return S_OK;
}

void CCore::Progress()
{
	//Manager Update
	CTimeManager::GetInst()->Update();
	CKeyManager::GetInst()->Update();
	CCamera::GetInst()->Update();
	CUIManager::GetInst()->Update();


	// ============
	// Scene Update
	// ============
	CSceneManager::GetInst()->Update();
	
	/// ==========
	/// 충돌체크
	/// ===========
	CColliderManager::GetInst()->Update();

	//이벤트 체크

	CGameObjectManager::GetInst()->Update();

	///	============
	///	 Rendering	
	/// ============
	/// 
	Clear();

 	CSceneManager::GetInst()->Render(m_memTex->GetDC());
	CCamera::GetInst()->Render(m_memTex->GetDC());
	CCamera::GetInst()->GetCameraLT();
	BitBlt(m_hDc, 0, 0, m_ptResolution.x, m_ptResolution.y, m_memTex->GetDC(), 0, 0, SRCCOPY);

	SetWindowText(m_hWnd, CTimeManager::GetInst()->GetTitle());

	//이벤트 지연처리
	CEventManager::GetInst()->Update();
}

void CCore::CreateBrushPen()
{
	m_brushs[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	m_brushs[TYPE_NUMBER(BRUSH_TYPE::BLACK)] = (HBRUSH)GetStockObject(BLACK_BRUSH);
	m_brushs[TYPE_NUMBER(BRUSH_TYPE::RED)] = CreateSolidBrush(RGB(255, 0, 0));
	m_brushs[TYPE_NUMBER(BRUSH_TYPE::GREEN)] = CreateSolidBrush(RGB(0, 255, 0));
	m_brushs[TYPE_NUMBER(BRUSH_TYPE::BLUE)] = CreateSolidBrush(RGB(0, 0, 255));
	m_brushs[TYPE_NUMBER(BRUSH_TYPE::PURPLE)] = CreateSolidBrush(RGB(255, 255, 0));
	m_pens[TYPE_NUMBER(PEN_TYPE::HOLLOW)] = (HPEN)GetStockObject(NULL_PEN);
	m_pens[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_pens[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0,255, 0));
	m_pens[TYPE_NUMBER(PEN_TYPE::GREEN_BOLD)] = CreatePen(PS_SOLID, 3, RGB(0, 255, 0));
	m_pens[TYPE_NUMBER(PEN_TYPE::RED_BOLD)] = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	m_pens[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	m_pens[(UINT)PEN_TYPE::BLUE_BOLD] = CreatePen(PS_SOLID, 3, RGB(0, 0, 255));
	m_pens[(UINT)PEN_TYPE::BLACK] = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	m_pens[(UINT)PEN_TYPE::WHITE] = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
}



void CCore::DockMenu()
{
	SetMenu(m_hWnd, m_menu);
	changeWindowSize(GetResolution(), true);
}

void CCore::DockMenu(Vec2 _resolution)
{
	SetMenu(m_hWnd, m_menu);
	m_ptResolution = {(int)_resolution.x, (int)_resolution.y};
	changeWindowSize(_resolution, true);
}

void CCore::UnDockMenu()
{
	SetMenu(m_hWnd, nullptr);
	changeWindowSize(Vec2(1280,768), false);
}

void CCore::changeWindowSize(Vec2 _resolution, bool _isDock)
{
	RECT rt = { 0,0,(LONG)_resolution.x, (LONG)_resolution.y };
	m_ptResolution = { (LONG)_resolution.x, (LONG)_resolution.y };
	//윈도우크기 계산
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, _isDock);
	//윈도우 창위치 설정, 크기설정
	SetWindowPos(m_hWnd, nullptr, m_ptMonitorResolution.x / 2 - _resolution.x / 2, m_ptMonitorResolution.y / 2 - _resolution.y / 2, rt.right - rt.left, rt.bottom - rt.top, 0);
}

void CCore::loadResource()
{
	//Texture resource Load
	CResourceManager::GetInst()->LoadTexture(L"CarrotBeamTex", L"texture\\cuphead\\boss\\carrot_beam.bmp");
	CResourceManager::GetInst()->LoadTexture(L"CarrotMissileTex", L"texture\\cuphead\\boss\\carrot_missile.bmp");

	CResourceManager::GetInst()->LoadTexture(L"TearBulletTex", L"texture\\cuphead\\boss\\onion_tear.bmp");
	CResourceManager::GetInst()->LoadTexture(L"TearBulletDeathTex", L"texture\\cuphead\\boss\\onion_tear_death.bmp");

	CResourceManager::GetInst()->LoadTexture(L"PotatoDustBullet", L"texture\\cuphead\\boss\\potato_bullet_dust.bmp");
	CResourceManager::GetInst()->LoadTexture(L"PotatoWormBullet", L"texture\\cuphead\\boss\\potato_bullet_worm.bmp");

	CResourceManager::GetInst()->LoadTexture(L"HomingBulletTex", L"texture\\cuphead\\bullet\\homing_bullet.bmp");
	CResourceManager::GetInst()->LoadTexture(L"HomingBulletDeathTex", L"texture\\cuphead\\bullet\\homing_bullet_death.bmp");
	CResourceManager::GetInst()->LoadTexture(L"TrailTex", L"texture\\cuphead\\bullet\\homing_bulle_trailt.bmp");

	CResourceManager::GetInst()->LoadTexture(L"PeashootTex", L"texture\\cuphead\\bullet\\peashoot_bullet_direction.bmp");
	CResourceManager::GetInst()->LoadTexture(L"PeashootDeathTex", L"texture\\cuphead\\bullet\\peashoot_bullet_death.bmp");

	CResourceManager::GetInst()->LoadTexture(L"VeggieBackgroundTex", L"texture\\cuphead\\background\\veggie_background.bmp");
	CResourceManager::GetInst()->LoadTexture(L"SlimeBackgroundTex", L"texture\\cuphead\\background\\slime_baground.bmp");
	CResourceManager::GetInst()->LoadTexture(L"TitleBackgroundTex", L"texture\\cuphead\\background\\title_menu.bmp");
	CResourceManager::GetInst()->LoadTexture(L"PauseBackgroundTex", L"texture\\cuphead\\background\\pause_menu.bmp");

	CResourceManager::GetInst()->LoadTexture(L"botanic_foreground_1", L"texture\\cuphead\\foreground\\botanic_foreground_1.bmp");
	CResourceManager::GetInst()->LoadTexture(L"botanic_foreground_2", L"texture\\cuphead\\foreground\\botanic_foreground_2.bmp");
	CResourceManager::GetInst()->LoadTexture(L"slime_bg_fg_mushrooms_1", L"texture\\cuphead\\foreground\\slime_bg_fg_mushrooms_left.bmp");
	CResourceManager::GetInst()->LoadTexture(L"slime_bg_fg_mushrooms_2", L"texture\\cuphead\\foreground\\slime_bg_fg_mushrooms_right.bmp");
	
	CResourceManager::GetInst()->LoadTexture(L"platform_propeller", L"texture\\cuphead\\obj\\PropellerSprite.bmp");
	CResourceManager::GetInst()->LoadTexture(L"platform", L"texture\\cuphead\\obj\\PlatformSprite.bmp");
	
	CResourceManager::GetInst()->LoadTexture(L"lgSlimeAirDownTex", L"texture\\cuphead\\boss\\lg_slime_air_down.bmp");
	CResourceManager::GetInst()->LoadTexture(L"lgSlimeAirUpTex", L"texture\\cuphead\\boss\\lg_slime_air_up.bmp");
	CResourceManager::GetInst()->LoadTexture(L"lgSlimeDeathTex", L"texture\\cuphead\\boss\\lg_slime_death.bmp");
	CResourceManager::GetInst()->LoadTexture(L"lgSlimeIdleTex", L"texture\\cuphead\\boss\\lg_slime_idle.bmp");
	CResourceManager::GetInst()->LoadTexture(L"lgSlimeJumpTex", L"texture\\cuphead\\boss\\lg_slime_jump.bmp");
	CResourceManager::GetInst()->LoadTexture(L"lgSlimePunchTex", L"texture\\cuphead\\boss\\lg_slime_punch.bmp");
	CResourceManager::GetInst()->LoadTexture(L"lgSlimeTurnPunchTex", L"texture\\cuphead\\boss\\lg_slime_turn_punch.bmp");
	CResourceManager::GetInst()->LoadTexture(L"lgSlimeUpDownTurnTex", L"texture\\cuphead\\boss\\lg_slime_Up_Down_Turn.bmp");
	CResourceManager::GetInst()->LoadTexture(L"slimeAirTurnTex", L"texture\\cuphead\\boss\\slime_air_up_down_turn.bmp");
	CResourceManager::GetInst()->LoadTexture(L"slimeIntroTex", L"texture\\cuphead\\boss\\slime_intro.bmp");
	CResourceManager::GetInst()->LoadTexture(L"slimeMorphTex", L"texture\\cuphead\\boss\\slime_morph.bmp");
	CResourceManager::GetInst()->LoadTexture(L"slimePunchTex", L"texture\\cuphead\\boss\\slime_punch.bmp");
	CResourceManager::GetInst()->LoadTexture(L"slimePunchTurnTex", L"texture\\cuphead\\boss\\slime_punch_turn.bmp");
	CResourceManager::GetInst()->LoadTexture(L"slimeJumpTex", L"texture\\cuphead\\boss\\slime_jump.bmp");
	
	CResourceManager::GetInst()->LoadTexture(L"CarrotEyeTex", L"texture\\cuphead\\boss\\carrot_eye.bmp");
	CResourceManager::GetInst()->LoadTexture(L"CarrotIntroTex", L"texture\\cuphead\\boss\\carrot_intro.bmp");
	CResourceManager::GetInst()->LoadTexture(L"CarrotIdleTex", L"texture\\cuphead\\boss\\carrot_idle.bmp");
	CResourceManager::GetInst()->LoadTexture(L"CarrotDeathTex", L"texture\\cuphead\\boss\\carrot_death.bmp");
	CResourceManager::GetInst()->LoadTexture(L"CarrotShootTex", L"texture\\cuphead\\boss\\carrot_shoot.bmp");
	CResourceManager::GetInst()->LoadTexture(L"CarrotTrasitTex", L"texture\\cuphead\\boss\\carrot_transition.bmp");
	
	CResourceManager::GetInst()->LoadTexture(L"OnionIntroTex", L"texture\\cuphead\\boss\\onion_intro.bmp");
	CResourceManager::GetInst()->LoadTexture(L"OnionIdleTex", L"texture\\cuphead\\boss\\onion_idle.bmp");
	CResourceManager::GetInst()->LoadTexture(L"OnionCryingTex", L"texture\\cuphead\\boss\\onion_crying.bmp");
	CResourceManager::GetInst()->LoadTexture(L"OnionDeathTex", L"texture\\cuphead\\boss\\onion_death.bmp");
	CResourceManager::GetInst()->LoadTexture(L"PotatoIdleTex", L"texture\\cuphead\\boss\\potato_idle.bmp");//5
	CResourceManager::GetInst()->LoadTexture(L"PotatoDeathTex", L"texture\\cuphead\\boss\\potato_death.bmp");//34
	CResourceManager::GetInst()->LoadTexture(L"PotatoIntroTex", L"texture\\cuphead\\boss\\potato_intro.bmp");//11
	CResourceManager::GetInst()->LoadTexture(L"PotatoShootTex", L"texture\\cuphead\\boss\\potato_shoot.bmp");//22

	CResourceManager::GetInst()->LoadTexture(L"PlayerIdleTex", L"texture\\cuphead\\player\\player_idle.bmp");
	CResourceManager::GetInst()->LoadTexture(L"PlayerIntroTex", L"texture\\cuphead\\player\\player_intro.bmp");
	CResourceManager::GetInst()->LoadTexture(L"PlayerDeathTex", L"texture\\cuphead\\player\\player_death.bmp");
	CResourceManager::GetInst()->LoadTexture(L"PlayerRunTurnTex", L"texture\\cuphead\\player\\player_turn.bmp");
	CResourceManager::GetInst()->LoadTexture(L"PlayerDucKTex", L"texture\\cuphead\\player\\player_duck.bmp");
	CResourceManager::GetInst()->LoadTexture(L"PlayerSpawnTex", L"texture\\cuphead\\bullet\\bullet_spawn.bmp");
	CResourceManager::GetInst()->LoadTexture(L"PlayerNormalRunTex", L"texture\\cuphead\\player\\player_run.bmp");

	CResourceManager::GetInst()->LoadTexture(L"PlayerAimTex", L"texture\\cuphead\\player\\player_aim.bmp");
	CResourceManager::GetInst()->LoadTexture(L"PlayerDashTex", L"texture\\cuphead\\player\\player_dash.bmp");

	CResourceManager::GetInst()->LoadTexture(L"PlayerShootTex", L"texture\\cuphead\\player\\player_shoot.bmp");
	CResourceManager::GetInst()->LoadTexture(L"PlayerExShootTex", L"texture\\cuphead\\player\\player_ex_shoot.bmp");
	CResourceManager::GetInst()->LoadTexture(L"PlayerExShootAirTex", L"texture\\cuphead\\player\\player_ex_shoot_air.bmp");

	CResourceManager::GetInst()->LoadTexture(L"PlayerJumpTex", L"texture\\cuphead\\player\\player_jump.bmp");
	CResourceManager::GetInst()->LoadTexture(L"PlayerHitTex", L"texture\\cuphead\\player\\player_hit.bmp");

	CResourceManager::GetInst()->LoadTexture(L"MenuButtonTex", L"texture\\cuphead\\ui\\text_sprite.bmp");
	CResourceManager::GetInst()->LoadTexture(L"PlayerHpTex", L"texture\\cuphead\\ui\\hp_sprite.bmp");
	CResourceManager::GetInst()->LoadTexture(L"weaponUITex", L"texture\\cuphead\\ui\\equip_wepon_sprite.bmp");

	//FX
	CResourceManager::GetInst()->LoadTexture(L"LevelStratTex", L"texture\\cuphead\\fx\\level_start_text.bmp");
	CResourceManager::GetInst()->LoadTexture(L"LgSlimeJumpDustTex", L"texture\\cuphead\\fx\\lg_slime_jump_dust.bmp");
	CResourceManager::GetInst()->LoadTexture(L"PlayerDashBombTex", L"texture\\cuphead\\fx\\player_dashbomb.bmp");
	CResourceManager::GetInst()->LoadTexture(L"PlayerJumpDustTex", L"texture\\cuphead\\fx\\player_jump_dust.bmp");
	CResourceManager::GetInst()->LoadTexture(L"PotatoIntroDustTex", L"texture\\cuphead\\fx\\potato_intro_dust.bmp");
	CResourceManager::GetInst()->LoadTexture(L"PotatoShootDustTex", L"texture\\cuphead\\fx\\potato_shoot_dust.bmp");
	CResourceManager::GetInst()->LoadTexture(L"OnionTearBigTex", L"texture\\cuphead\\fx\\onion_tear_big.bmp");
	CResourceManager::GetInst()->LoadTexture(L"ScreenChangeTex", L"texture\\cuphead\\fx\\screen_change_effect.bmp");
	CResourceManager::GetInst()->LoadTexture(L"YouDiedTex", L"texture\\cuphead\\fx\\you_died_text.bmp");
	//Sound Reasource

	//Player
	CResourceManager::GetInst()->LoadSound(L"PLAYER_DASH", L"sound\\player\\sfx_player_dash_01.wav");
	CResourceManager::GetInst()->LoadSound(L"PLAYER_DEATH", L"sound\\player\\sfx_player_death_01.wav");
	CResourceManager::GetInst()->LoadSound(L"PLAYER_FIRE_LOOP", L"sound\\player\\sfx_player_default_fire_loop_01.wav");
	CResourceManager::GetInst()->LoadSound(L"PLAYER_HIT", L"sound\\player\\sfx_player_hit_01.wav");
	CResourceManager::GetInst()->LoadSound(L"PLAYER_INTRO", L"sound\\player\\sfx_player_intro_cuphead.wav");
	CResourceManager::GetInst()->LoadSound(L"PLAYER_JUMP", L"sound\\player\\sfx_player_jump_01.wav");
	CResourceManager::GetInst()->LoadSound(L"PLAYER_SHOOT_HIT", L"sound\\player\\sfx_player_shoot_hit_01.wav");
	CResourceManager::GetInst()->LoadSound(L"PLAYER_HOMING_LOOP", L"sound\\player\\sfx_player_weapon_homing_loop_001.wav");
	CResourceManager::GetInst()->LoadSound(L"PLAYER_MENU_SELECT", L"sound\\player\\Menu_Category_Select.wav");

	//Slime
	CResourceManager::GetInst()->LoadSound(L"BGM_SLIME", L"sound\\slime\\MUS_Slime.wav");
	CResourceManager::GetInst()->LoadSound(L"SLIME_DEATH", L"sound\\slime\\sfx_slime_big_death_01.wav");
	CResourceManager::GetInst()->LoadSound(L"LG_SLIME_JUMP", L"sound\\slime\\sfx_slime_big_jump_01.wav");
	CResourceManager::GetInst()->LoadSound(L"LG_SLIME_LAND", L"sound\\slime\\sfx_slime_big_land_01.wav");
	CResourceManager::GetInst()->LoadSound(L"LG_SLIME_PUNCH", L"sound\\slime\\sfx_slime_big_punch_01.wav");
	CResourceManager::GetInst()->LoadSound(L"LG_SLIME_PUNCH_VOICE", L"sound\\slime\\sfx_slime_big_punch_voice_01.wav");
	CResourceManager::GetInst()->LoadSound(L"SLIME_INTRO", L"sound\\slime\\sfx_slime_small_intro_anim.wav");
	CResourceManager::GetInst()->LoadSound(L"SLIME_JUMP", L"sound\\slime\\sfx_slime_small_jump_01.wav");
	CResourceManager::GetInst()->LoadSound(L"SLIME_LAND", L"sound\\slime\\sfx_slime_small_land_01.wav");
	CResourceManager::GetInst()->LoadSound(L"SLIME_PUNCH", L"sound\\slime\\sfx_slime_small_stretch_punch_01.wav");
	CResourceManager::GetInst()->LoadSound(L"SLIME_MORPH", L"sound\\slime\\sfx_slime_small_transform.wav");
	CResourceManager::GetInst()->LoadSound(L"SLIME_TIPHAT", L"sound\\slime\\sfx_slime_tiphat_01.wav");

	//TITLE
	CResourceManager::GetInst()->LoadSound(L"BGM_TITLE", L"sound\\title\\bgm_title_screen.wav");

	//Veggie
	CResourceManager::GetInst()->LoadSound(L"BGM_VEGGIE", L"sound\\veggie\\bgm_level_veggies.wav");

	//Carrot
	CResourceManager::GetInst()->LoadSound(L"CARROT_DEATH", L"sound\\veggie\\sfx_level_veggies_Carrot_Die.wav");
	CResourceManager::GetInst()->LoadSound(L"CARROT_HURT", L"sound\\veggie\\sfx_level_veggies_carrot_hurt.wav");
	CResourceManager::GetInst()->LoadSound(L"CARROT_MIND_MEID_START", L"sound\\veggie\\sfx_level_veggies_Carrot_MindMeld_Start.wav");
	CResourceManager::GetInst()->LoadSound(L"CARROT_MIND_MEID_LOOP", L"sound\\veggie\\sfx_level_veggies_Carrot_MindMeld_Loop.wav");
	CResourceManager::GetInst()->LoadSound(L"CARROT_MIND_MEID_BEAM_FIRE", L"sound\\veggie\\sfx_level_veggies_Carrot_MindMeld_BeamFire_01.wav");
	CResourceManager::GetInst()->LoadSound(L"CARROT_INTRO", L"sound\\veggie\\sfx_level_veggies_Carrot_Rise.wav");
	CResourceManager::GetInst()->LoadSound(L"CARROT_MISSILE_DEATH", L"sound\\veggie\\sfx_level_veggies_Carrot_Bomb_Explode_01.wav");

	//ONION
	CResourceManager::GetInst()->LoadSound(L"ONION_DEATH", L"sound\\veggie\\sfx_level_veggies_Onion_Die.wav");
	CResourceManager::GetInst()->LoadSound(L"ONION_CRYING", L"sound\\veggie\\sfx_level_veggies_Onion_Crying.wav");
	CResourceManager::GetInst()->LoadSound(L"ONION_INTRO", L"sound\\veggie\\sfx_level_veggies_Onion_Rise.wav");
	CResourceManager::GetInst()->LoadSound(L"ONION_TEAR_DEATH", L"sound\\veggie\\sfx_level_veggies_Onion_Teardrop_01.wav");


	//Potato
	CResourceManager::GetInst()->LoadSound(L"POTATO_INTRO", L"sound\\veggie\\sfx_level_veggies_Potato_RiseGround.wav");
	CResourceManager::GetInst()->LoadSound(L"POTATO_DUST_1", L"sound\\veggie\\sfx_level_veggies_Potato_Spit_01.wav");
	CResourceManager::GetInst()->LoadSound(L"POTATO_DUST_2", L"sound\\veggie\\sfx_level_veggies_Potato_Spit_002.wav");
	CResourceManager::GetInst()->LoadSound(L"POTATO_DUST_3", L"sound\\veggie\\sfx_level_veggies_Potato_Spit_003.wav");
	CResourceManager::GetInst()->LoadSound(L"POTATO_WORM", L"sound\\veggie\\sfx_level_veggies_Potato_Spit_Worm_01.wav");
	CResourceManager::GetInst()->LoadSound(L"POTATO_WORM_DEATH", L"sound\\veggie\\sfx_level_veggies_Potato_Worm_Explode_01.wav");



}

void CCore::Clear()
{
	SelectGDI gdi(m_memTex->GetDC(), BRUSH_TYPE::BLACK);
	Rectangle(m_memTex->GetDC(), -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);
}



