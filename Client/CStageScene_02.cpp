#include "pch.h"
#include "CStageScene_02.h"
#include "CCore.h"
#include "CCamera.h"
#include "CMonster.h"
#include "CMonsterFactory.h"
#include "CPlayer.h"
#include "CColliderManager.h"
#include "CSpawnObject.h"
#include "CSound.h"
#include "CPlayerStateMachine.h"
#include "CPlayerState.h"
#include "CVFXObject.h"
#include "CMonsterDebugPanel.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CKeyManager.h"
CStageScene_02::CStageScene_02()
	:m_currentBoss(nullptr)
{
}

CStageScene_02::~CStageScene_02()
{
}

void CStageScene_02::Enter()
{
	Vec2 resolution = CCore::GetInst()->GetResolution();

	CScene::LoadMap(L"tile\\stage_2.tile");
	CScene::SetCurrnetState(SCENE_STATE::START);
	CColliderManager::GetInst()->CheckGroup(GROUP_TYPE::GROUND, GROUP_TYPE::PLAYER);
	CColliderManager::GetInst()->CheckGroup(GROUP_TYPE::GROUND, GROUP_TYPE::BOSS);
	CColliderManager::GetInst()->CheckGroup(GROUP_TYPE::PLATFORM_OBJ, GROUP_TYPE::PLAYER);
	CColliderManager::GetInst()->CheckGroup(GROUP_TYPE::BOSS, GROUP_TYPE::PLAYER_HITBOX);
	CColliderManager::GetInst()->CheckGroup(GROUP_TYPE::MONSTER_ATTACKBOX, GROUP_TYPE::PLAYER);
	CColliderManager::GetInst()->CheckGroup(GROUP_TYPE::PLAYER_BULLET, GROUP_TYPE::GROUND);
	CColliderManager::GetInst()->CheckGroup(GROUP_TYPE::PLAYER_BULLET, GROUP_TYPE::MONSTER_BULLET);
	CColliderManager::GetInst()->CheckGroup(GROUP_TYPE::PLAYER_BULLET, GROUP_TYPE::MONSTER_HITBOX);
	CColliderManager::GetInst()->CheckGroup(GROUP_TYPE::PLAYER_HITBOX, GROUP_TYPE::MONSTER_BULLET);
	CColliderManager::GetInst()->CheckGroup(GROUP_TYPE::PLAYER_HITBOX, GROUP_TYPE::MONSTER_HITBOX);
	CColliderManager::GetInst()->CheckGroup(GROUP_TYPE::MONSTER_BULLET, GROUP_TYPE::GROUND);
	CreatePauseUI();
	SetBGM(L"BGM_SLIME");
	GetBGM()->PlayToBGM(true);
	GetBGM()->SetPosition(50.f);
	GetBGM()->SetVolume(20.f);
	GetVFX()->SetType(VFX_TYPE::SCENE_CHANGE_INTRO);
	m_debugPanel = new CMonsterDebugPanel;
	m_debugPanel->SetPos(Vec2(780.f, 50.f));
	CreateObject(m_debugPanel, GROUP_TYPE::UI);
}

void CStageScene_02::Update()
{
	const vector<CObject*>& boss = GetObjWithType(GROUP_TYPE::BOSS);
	CScene::Update();
	if (GetCurrentState() == SCENE_STATE::START)
	{
		CSpawnObject* playerSpawn = ((CSpawnObject*)GetTarget(GROUP_TYPE::SPAWN_OBJ, L"Spawn_Player"));
		playerSpawn->Spawn();
		playerInfo info = ((CPlayer*)playerSpawn->GetSpawnObj())->GetInfo();
		info.health = GetHp();
		((CPlayer*)playerSpawn->GetSpawnObj())->SetInfo(info);
		CSpawnObject* salSpawn = ((CSpawnObject*)GetTarget(GROUP_TYPE::SPAWN_OBJ, L"Spawn_Slime"));
		salSpawn->Spawn();
		m_currentBoss = salSpawn->GetSpawnObj();
		m_debugPanel->SetOwner((CMonster*)m_currentBoss);
		m_prevBossName = m_currentBoss->GetName();
		CCamera::GetInst()->SetTarget(playerSpawn->GetSpawnObj());
		if (GetVFX()->GetAnimator()->GetCurrentAnim()->IsFinish())
		{
			if (GetVFX()->GetAnimator()->GetCurrentAnim()->GetName() == L"LEVEL_START_2")
			{
				SetCurrnetState(SCENE_STATE::PLAY);
			}
			if (GetVFX()->GetAnimator()->GetCurrentAnim()->GetName() != L"LEVEL_START_2")
			{
				GetVFX()->SetType(VFX_TYPE::LEVEL_START);
			}
		}
		return;
	}
	if (KEY_TAP(KEY::F1))
	{
		SetDebug();
	}
	if (KEY_TAP(KEY::ESC))
	{
		ShowPauseUI();
	}
	if (CCore::GetInst()->IsDebug())
	{
		if (KEY_TAP(KEY::F2))
		{
			SetDeadState((CMonster*)m_currentBoss);
		}
		if (KEY_TAP(KEY::F7))
		{
			ChangeScene(SCENE_TYPE::STAGE_01);
		}
	}

	if (m_currentBoss != nullptr && m_currentBoss->IsDead())
	{
		if (GetCurrentState() != SCENE_STATE::EXIT && GetVFX()->GetAnimator()->GetCurrentAnim()->IsFinish())
		{
			CCamera::GetInst()->SetCamEffect(1.f, CAMERA_EFFECT::VIBRATION);
			GetVFX()->SetType(VFX_TYPE::SCENE_CHANGE_OUTRO);
			SetCurrnetState(SCENE_STATE::EXIT);
		}
		else if (GetVFX()->GetAnimator()->GetCurrentAnim()->IsFinish())
		{		
			ChangeScene(SCENE_TYPE::START);
		}
	}
	if (((CPlayer*)GetTarget(GROUP_TYPE::PLAYER, L"Player"))->GetAi()->GetCurrentState()->GetState() == PLAYER_STATE::DEAD)
	{
		if (GetCurrentState() != SCENE_STATE::GAMEOVER && GetVFX()->GetAnimator()->GetCurrentAnim()->IsFinish())
		{
			GetVFX()->SetType(VFX_TYPE::YOU_DIED);
			SetCurrnetState(SCENE_STATE::GAMEOVER);
		}
		if (GetCurrentState() == SCENE_STATE::GAMEOVER && GetVFX()->GetAnimator()->GetCurrentAnim()->IsFinish())
		{
			if (GetVFX()->GetType() == VFX_TYPE::SCENE_CHANGE_OUTRO)
			{
				ChangeScene(SCENE_TYPE::START);
				return;
			}
			GetVFX()->SetType(VFX_TYPE::SCENE_CHANGE_OUTRO);

		}

	}
}


void CStageScene_02::Exit()
{
	DeleteAll();
	GetBGM()->Stop();
}
