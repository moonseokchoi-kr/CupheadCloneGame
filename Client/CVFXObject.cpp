#include "pch.h"
#include "CVFXObject.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CTexture.h"
#include "CResourceManager.h"
CVFXObject::CVFXObject()
	:m_owner(nullptr)
{
	CreateAnimator();
	CTexture* levelTex = CResourceManager::GetInst()->FindTexture(L"LevelStratTex");
	CTexture* slimeDustTex = CResourceManager::GetInst()->FindTexture(L"LgSlimeJumpDustTex");
	CTexture* dashBombTex = CResourceManager::GetInst()->FindTexture(L"PlayerDashBombTex");
	CTexture* jumpDustTex = CResourceManager::GetInst()->FindTexture(L"PlayerJumpDustTex");
	CTexture* introDustTex = CResourceManager::GetInst()->FindTexture(L"PotatoIntroDustTex");

	CTexture* bigTearTex = CResourceManager::GetInst()->FindTexture(L"OnionTearBigTex");
	CTexture* screenChangeTex = CResourceManager::GetInst()->FindTexture(L"ScreenChangeTex");
	CTexture* youDiedTex = CResourceManager::GetInst()->FindTexture(L"YouDiedTex");

	m_tex = CResourceManager::GetInst()->FindTexture(L"VeilTexture");
	GetAnimator()->CreateAnimation(L"LEVEL_START_1", levelTex, Vec2(0.f, 0.f), Vec2(1280.f, 720.f), Vec2(1280.f, 0.f), 1 / 30.f, 7, false);
	GetAnimator()->CreateAnimation(L"LEVEL_START_2", levelTex, Vec2(0.f, 720.f), Vec2(1280.f, 720.f), Vec2(1280.f, 0.f), 1 / 30.f, 7, false);
	GetAnimator()->CreateAnimation(L"YOU_DIED", youDiedTex, Vec2(0.f, 0.f), Vec2(1076.f, 232.f), Vec2(1076.f, 0.f), 1 / 30.f, 10, false);
	GetAnimator()->CreateAnimation(L"SCENE_CHANGE_INTRO", screenChangeTex, Vec2(0.f, 0.f), Vec2(480.f, 288.f), Vec2(480.f, 0.f), 1 / 30.f, 16, false);
	GetAnimator()->CreateAnimation(L"SCENE_CHANGE_OUTRO", screenChangeTex, Vec2(0.f, 0.f), Vec2(480.f, 288.f), Vec2(480.f, 0.f), 1 / 30.f, 16, true);
	
	
	GetAnimator()->CreateAnimation(L"LG_SLIME_JUMP_DUST", slimeDustTex, Vec2(0.f, 0.f), Vec2(843.f, 322.f), Vec2(843.f, 0.f), 1 / 30.f, 16, false);
	
	GetAnimator()->CreateAnimation(L"PLAYER_DASH_BOMB", dashBombTex, Vec2(0.f, 0.f), Vec2(262.f, 240.f), Vec2(262.f, 0.f), 1 / 30.f, 16, false);
	GetAnimator()->CreateAnimation(L"PLAYER_JUMP_DUST", jumpDustTex, Vec2(0.f, 0.f), Vec2(288.f, 152.f), Vec2(288.f, 0.f), 1 / 30.f, 16, false);
	
	GetAnimator()->CreateAnimation(L"POTATO_INTRO_DUST", introDustTex, Vec2(0.f, 0.f), Vec2(592.f, 454.f), Vec2(592.f, 0.f), 1 / 30.f, 18, false);
	
	
	GetAnimator()->CreateAnimation(L"ONION_BIG_TEAR_LEFT", bigTearTex, Vec2(0.f, 0.f), Vec2(663.f, 411.f), Vec2(663.f, 0.f), 1 / 30.f, 16, false);
	GetAnimator()->CreateAnimation(L"ONION_BIG_TEAR_RIGHT", bigTearTex, Vec2(0.f, 411.f), Vec2(663.f, 411.f), Vec2(663.f, 0.f), 1 / 30.f, 16, true);

	m_arrayVFX[TYPE_NUMBER(VFX_TYPE::LEVEL_START)] = L"LEVEL_START_1";
	m_arrayVFX[TYPE_NUMBER(VFX_TYPE::YOU_DIED)] = L"YOU_DIED";
	m_arrayVFX[TYPE_NUMBER(VFX_TYPE::SCENE_CHANGE_INTRO)] = L"SCENE_CHANGE_INTRO";
	m_arrayVFX[TYPE_NUMBER(VFX_TYPE::SCENE_CHANGE_OUTRO)] = L"SCENE_CHANGE_OUTRO";
	m_arrayVFX[TYPE_NUMBER(VFX_TYPE::JUMP_DUST)] = L"LG_SLIME_JUMP_DUST";
	m_arrayVFX[TYPE_NUMBER(VFX_TYPE::INTRO_DUST)] = L"POTATO_INTRO_DUST";
	m_arrayVFX[TYPE_NUMBER(VFX_TYPE::JUMP_DUST)] = L"PLAYER_JUMP_DUST";
	m_arrayVFX[TYPE_NUMBER(VFX_TYPE::DASH_BOMB)] = L"PLAYER_DASH_BOMB";
	m_arrayVFX[TYPE_NUMBER(VFX_TYPE::BIG_TEAR_LEFT)] = L"ONION_BIG_TEAR_LEFT";
	m_arrayVFX[TYPE_NUMBER(VFX_TYPE::BIG_TEAR_RIGHT)] = L"ONION_BIG_TEAR_RIGHT";
}

CVFXObject::~CVFXObject()
{
}

void CVFXObject::Update()
{
	if (m_currentType == VFX_TYPE::LEVEL_START)
	{
		if (GetAnimator()->GetCurrentAnim()->IsFinish())
		{
			GetAnimator()->Play(L"LEVEL_START_2",false);
			GetAnimator()->GetCurrentAnim()->SetFrame(0);
		}
	}
	if (m_currentType == VFX_TYPE::INTRO_DUST)
	{
		if (GetAnimator()->GetCurrentAnim()->GetCurrentFrame() == 17)
		{
			GetAnimator()->GetCurrentAnim()->SetFrame(17);
		}
	}
}

void CVFXObject::Render(HDC _dc)
{
	if (m_currentType == VFX_TYPE::LEVEL_START || m_currentType == VFX_TYPE::YOU_DIED)
	{
		BLENDFUNCTION bf = {};
		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 0;
		bf.AlphaFormat = 0;
		bf.SourceConstantAlpha = 179;

		AlphaBlend(
			_dc
			, 0, 0
			, m_tex->Width()
			, m_tex->Height()
			, m_tex->GetDC()
			, 0, 0
			, m_tex->Width()
			, m_tex->Height()
			, bf
		);

	}
	if (m_currentType == VFX_TYPE::SCENE_CHANGE_INTRO || m_currentType == VFX_TYPE::SCENE_CHANGE_OUTRO)
	{
		BLENDFUNCTION bf = {};
		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 0;
		bf.AlphaFormat = 0;
		bf.SourceConstantAlpha = 255;

		AlphaBlend(
			_dc
			, 0, 0
			, m_tex->Width()
			, m_tex->Height()
			, m_tex->GetDC()
			, 0, 0
			, m_tex->Width()
			, m_tex->Height()
			, bf
		);
	}
	ComponentRender(_dc);
}

void CVFXObject::SetType(VFX_TYPE _vfx)
{
	m_currentType = _vfx;
	SetPos(m_owner->GetPos() += m_offSet);
	GetAnimator()->Play(m_arrayVFX[TYPE_NUMBER(_vfx)],false);
	GetAnimator()->GetCurrentAnim()->SetFrame(0);
}

