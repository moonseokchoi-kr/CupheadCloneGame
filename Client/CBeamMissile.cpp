#include "pch.h"
#include "CBeamMissile.h"
#include "CCollider.h"
#include "CRigidBody.h"
#include "CScene.h"
#include "CSceneManager.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CTexture.h"
#include "CResourceManager.h"
#include "CSound.h"

#include "SelectGDI.h"


CBeamMissile::CBeamMissile()
	:CBullet(BULLET_TYPE::BEAM_BULLET)
	, isDead(false)
{
	CreateCollider();
	CreateRigidBody();
	CreateAnimator();

	SetScale(Vec2(173.f, 178.f));
	GetCollider()->SetScale(Vec2(95.f, 100.f));
	GetRigidBody()->SetMaxVelocity(400.f);
	bulletInfo info = {};
	info.bulletSpeed = 1000.f;
	info.damege = 1.f;
	info.range = 1600;
	SetInfo(info);

	CTexture* beamTex = CResourceManager::GetInst()->FindTexture(L"CarrotBeamTex");
	GetAnimator()->CreateAnimation(L"CARROT_BEAM_DEATH",beamTex,Vec2(0.f,0.f), Vec2(173.f,178.f),Vec2(173.f,0.f),1/16.f, 3, false);
	GetAnimator()->CreateAnimation(L"CARROT_BEAM_INTRO",beamTex,Vec2(519.f,0.f), Vec2(173.f,178.f),Vec2(173.f,0.f),1/16.f, 7, false);
	GetAnimator()->CreateAnimation(L"CARROT_BEAM_LOOP",beamTex,Vec2(1730.f,0.f), Vec2(173.f,178.f),Vec2(173.f,0.f),1/16.f, 5, false);

}

CBeamMissile::~CBeamMissile()
{
}

void CBeamMissile::Start()
{
	CBullet::Start();
	m_targetPos = CSceneManager::GetInst()->GetCurrentScene()->GetTarget(GROUP_TYPE::PLAYER, L"Player")->GetPos();
	m_diff = m_targetPos - GetPos();
	m_diff.Normalize();
}

void CBeamMissile::Update()
{
	GetAnimator()->Play(L"CARROT_BEAM_INTRO", false);
	if (GetAnimator()->GetCurrentAnim()->IsFinish())
		GetAnimator()->Play(L"CARROT_BEAM_LOOP", true);
	else
		return;
	GetRigidBody()->SetVelocity(m_diff * GetInfo().bulletSpeed);
	GetRigidBody()->AddVelocity(m_diff * GetInfo().bulletSpeed);

	DeleteBullet();
	if (isDead)
	{
		GetCollider()->SetAvaCollide(false);
		GetRigidBody()->SetActive(false);
		GetAnimator()->Play(L"CARROT_BEAM_DEATH", false);
		if (GetAnimator()->GetCurrentAnim()->IsFinish())
		{
			DeleteObject(this);
		}
	}
}

void CBeamMissile::Render(HDC _dc)
{
	ComponentRender(_dc);
}

void CBeamMissile::OnCollisionEnter(CCollider* _col)
{
	if (_col->GetOwner()->GetName() == L"Grond" || _col->GetOwner()->GetName() == L"PlayerHitBox")
	{

		isDead = true;
	}
}

void CBeamMissile::OnCollision(CCollider* _col)
{
	CObject* obj = _col->GetOwner();
	if (obj->GetName() == L"PlayerHitBox")
	{
		isDead = true;
	}
}

void CBeamMissile::OnCollisionExit(CCollider* _col)
{
}
