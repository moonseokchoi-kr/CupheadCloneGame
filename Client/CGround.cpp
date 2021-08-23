#include "pch.h"
#include "CGround.h"
#include "CCollider.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CTexture.h"
#include "CPropeller.h"
#include "CGravity.h"
#include "CResourceManager.h";
#include "CSceneManager.h"
#include "CCamera.h"
#include "SelectGDI.h"


CGround::CGround()
	:m_propeller(nullptr)
	,m_currentCollide(COLLIDE_TYPE::COLLIDE_IDLE)
{
	CreateCollider();
	SetScale(Vec2(100, 60));
}

CGround::~CGround()
{
}

void CGround::Start()
{

	switch (GetType())
	{
	case GAMEOBJECT_TYPE::FLOWER_PLATFORM_A:
	case GAMEOBJECT_TYPE::FLOWER_PLATFORM_B:
	case GAMEOBJECT_TYPE::FLOWER_PLATFORM_C:
	{
		SetName(L"Platform");
		CreateAnimator();
		CTexture* tex = CResourceManager::GetInst()->LoadTexture(L"platform", L"texture\\cuphead\\obj\\PlatformSprite.bmp");
		GetAnimator()->CreateAnimation(L"platform_A_anim", tex, Vec2(0, 0), Vec2(160, 93), Vec2(160, 0), 0.15f, 3, false);
		GetAnimator()->CreateAnimation(L"platform_B_anim", tex, Vec2(480, 0), Vec2(160, 93), Vec2(160, 0), 0.15f, 3, false);
		GetAnimator()->CreateAnimation(L"platform_C_anim", tex, Vec2(960, 0), Vec2(160, 93), Vec2(160, 0), 0.15f, 3, false);

		SetScale(Vec2(160, 93));
		GetCollider()->SetScale(GetScale()-Vec2(20.f,50.f));
		GetCollider()->SetOffsetPos(Vec2(0.f, -10.f));
		m_propeller = new CPropeller;
		m_propeller->SetParent(this);
		m_propeller->SetPosOffset(Vec2(5.f, 60.f));
		return;
	}
		break;
	case GAMEOBJECT_TYPE::GROUND:
	{
		SetName(L"Ground");
	}
		break;
	case GAMEOBJECT_TYPE::END:
		break;
	default:
		break;
	}
	if(nullptr != GetCollider())
		GetCollider()->SetScale(GetScale());
}

void CGround::Update()
{
}

void CGround::FinalUpdate()
{
	CGameObject::FinalUpdate();
	if (nullptr != m_propeller)
		m_propeller->FinalUpdate();
}

void CGround::Render(HDC _dc)
{
	Vec2 renderPos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 scale = GetScale();
	if (nullptr != m_propeller)
		m_propeller->Render(_dc);
	switch (GetType())
	{
	case GAMEOBJECT_TYPE::FLOWER_PLATFORM_A:
	{
		GetAnimator()->Play(L"platform_A_anim", true);
	}
	break;
	case GAMEOBJECT_TYPE::FLOWER_PLATFORM_B:
	{
		GetAnimator()->Play(L"platform_B_anim", true);
	}
	break;
	case GAMEOBJECT_TYPE::FLOWER_PLATFORM_C:
	{
		GetAnimator()->Play(L"platform_C_anim", true);
	}
	break;
	default:
	{
		SelectGDI gdi(_dc, BRUSH_TYPE::HOLLOW);
		SelectGDI gdi1(_dc, PEN_TYPE::WHITE);
		Rectangle(_dc,
			(int)(renderPos.x - scale.x / 2.f),
			(int)(renderPos.y - scale.y / 2.f),
			(int)(renderPos.x + scale.x / 2.f),
			(int)(renderPos.y + scale.y / 2.f)
		);
	}
	break;
	}

	ComponentRender(_dc);

	

}

void CGround::OnCollisionEnter(CCollider* _col)
{
	CObject* obj = _col->GetOwner();
	Vec2 objColPos = obj->GetCollider()->GetFinalPos();
	Vec2 objColScale = obj->GetCollider()->GetScale();
	Vec2 objPos = obj->GetPos();
	Vec2 objPrevPos = obj->GetCollider()->GetPrevFinalPos();
	Vec2 pos = GetCollider()->GetFinalPos();
	Vec2 scale = GetCollider()->GetScale();

	Vec2 platLT = Vec2(pos.x - scale.x / 2.f, pos.y - scale.y / 2.f);
	Vec2 platLB = Vec2(pos.x - scale.x / 2.f, pos.y + scale.y / 2.f);
	Vec2 platRB = Vec2(pos.x + scale.x / 2.f, pos.y + scale.y / 2.f);
	Vec2 objRBPos = Vec2(objColPos.x + objColScale.x / 2.f, objColPos.y + objColScale.y / 2.f);
	Vec2 objLBPos = Vec2(objColPos.x - objColScale.x / 2.f, objColPos.y + objColScale.y / 2.f);
	Vec2 objRBPrevPos = Vec2(objPrevPos.x + objColScale.x / 2.f, objPrevPos.y + objColScale.y / 2.f);
	Vec2 objLBPrevPos = Vec2(objPrevPos.x - objColScale.x / 2.f, objPrevPos.y + objColScale.y / 2.f);
	if (obj->GetName() == L"Player")
	{
		
		switch (GetType())
		{
		case GAMEOBJECT_TYPE::FLOWER_PLATFORM_A:
		case GAMEOBJECT_TYPE::FLOWER_PLATFORM_B:
		case GAMEOBJECT_TYPE::FLOWER_PLATFORM_C:
		{

			// 콜라이더 하단 충돌
			// 콜라이더의 이전 위치가 콜라이더의 하단보다 크고 현재 하단보다 작을경우
			// 콜라이더 상단 충돌
			// 콜라이더의 이전 위치가 콜라이더의 상단보다 작고 현재 상단보다 클경우
			if ((int)objRBPos.y <= (int)platLT.y && platLT.y>=objRBPrevPos.y)
			{
				obj->GetGravity()->SetGround(true, GROUND_TYPE::PLATFORM);
				m_currentCollide = COLLIDE_TYPE::COLLIDE_TOP;
			}
			else if (platLT.y < objRBPos.y <= platRB.y)
			{
				m_currentCollide = COLLIDE_TYPE::COLLIDE_IDLE;
			}
		}

			break;
		case GAMEOBJECT_TYPE::GROUND:
		{
			Vec2 moveDir = obj->GetMoveDir();
			
			//플렝이어의 이전 위치가 땅의 상단위치보다 작고 현재 위치가 플랫폼 좌상단 우상단보다 클경우
			if ((int)objRBPos.y >= (int)platLT.y && (int)objRBPrevPos.y<=(int)platLT.y)
			{
				obj->GetGravity()->SetGround(true, GROUND_TYPE::GROUND);
				m_currentCollide = COLLIDE_TYPE::COLLIDE_TOP;
			}
			else if (platLT.y < objRBPos.y <= platRB.y)
			{
				
				if (platRB.x >= objLBPos.x && objLBPrevPos.x>= platRB.x)
				{
					m_currentCollide= COLLIDE_TYPE::COLLIDE_LEFT;
				}
				else if (objRBPos.x >= platLT.x && objRBPrevPos.x<=platLT.x)
				{
					m_currentCollide = COLLIDE_TYPE::COLLIDE_RIGHT;
				}
			}
		}
			break;
		default:
			break;
		}
		
	}
	if (obj->GetName() == L"Monster")
	{
		if (GetType() == GAMEOBJECT_TYPE::GROUND)
		{
	

			//플렝이어의 이전 위치가 땅의 상단위치보다 작고 현재 위치가 플랫폼 좌상단 우상단보다 클경우
			if ((int)objRBPos.y >= (int)platLT.y && (int)objRBPos.y <= (int)platLT.y)
			{
				obj->GetGravity()->SetGround(true, GROUND_TYPE::GROUND);
				m_currentCollide = COLLIDE_TYPE::COLLIDE_TOP;
			}
			else if (platLT.y < objRBPos.y <= platRB.y)
			{

				if (platRB.x >= objLBPos.x && objLBPrevPos.x >= platRB.x)
				{
					m_currentCollide = COLLIDE_TYPE::COLLIDE_RIGHT;
				}
				else if (objRBPos.x >= platLT.x && objRBPos.x <= platLT.x)
				{
					m_currentCollide = COLLIDE_TYPE::COLLIDE_LEFT;
				}
			}
		}
	}
}

void CGround::OnCollision(CCollider* _col)
{
	CObject* obj = _col->GetOwner();
	Vec2 moveDir = obj->GetMoveDir();
	Vec2 objColPos = obj->GetCollider()->GetFinalPos();
	Vec2 objColScale = obj->GetCollider()->GetScale();
	Vec2 objPos = obj->GetPos();
	Vec2 pos = GetCollider()->GetFinalPos();
	Vec2 scale = GetCollider()->GetScale();
	if (obj->GetName() == L"Player" )
	{
		switch (GetType())
		{
		case GAMEOBJECT_TYPE::FLOWER_PLATFORM_A:
		case GAMEOBJECT_TYPE::FLOWER_PLATFORM_B:
		case GAMEOBJECT_TYPE::FLOWER_PLATFORM_C:
		{
			

			
			
			if (m_currentCollide == COLLIDE_TYPE::COLLIDE_TOP)
			{
				obj->GetGravity()->SetGround(true, GROUND_TYPE::GROUND);
				float fDiff = calColliderDiff(objColPos.y, objColScale.y, pos.y, scale.y);
				objPos.y -= (fDiff);
				obj->SetPos(objPos);
			}
			else
			{
				obj->GetGravity()->SetGround(false, GROUND_TYPE::NONE);
			}
	
		}
		break;
		case GAMEOBJECT_TYPE::GROUND:
		{
			Vec2 moveDir = obj->GetMoveDir();
			switch (m_currentCollide)
			{
			case COLLIDE_TYPE::COLLIDE_TOP:
			{
				obj->GetGravity()->SetGround(true, GROUND_TYPE::GROUND);
				float fDiff = calColliderDiff(objColPos.y, objColScale.y, pos.y, scale.y);
				objPos.y -= (fDiff);
			}
				break;
			case COLLIDE_TYPE::COLLIDE_LEFT:
			{
				float fDiff = calColliderDiff(objColPos.x, objColScale.x, pos.x, scale.x);
				objPos.x += (fDiff);
			}
				break;
			case COLLIDE_TYPE::COLLIDE_RIGHT:
			{
				float fDiff = calColliderDiff(objColPos.x, objColScale.x, pos.x, scale.x);
				objPos.x -= (fDiff);
			}
				break;
			case COLLIDE_TYPE::COLLIDE_BOTTOM:
			{

			}
				break;
			case COLLIDE_TYPE::COLLIDE_IDLE:
				break;
			default:
				break;
			}
			obj->SetPos(objPos);
		}
		break;
		default:
			break;
		}
	}
	if (obj->GetName() == L"Monster")
	{
		if (GetType() == GAMEOBJECT_TYPE::GROUND)
		{
			Vec2 moveDir = obj->GetMoveDir();
			switch (m_currentCollide)
			{
			case COLLIDE_TYPE::COLLIDE_TOP:
			{
				obj->GetGravity()->SetGround(true,GROUND_TYPE::GROUND);
				float fDiff = calColliderDiff(objColPos.y, objColScale.y, pos.y, scale.y);
				objPos.y -= (fDiff);
			}
			break;
			case COLLIDE_TYPE::COLLIDE_LEFT:
			{
				float fDiff = calColliderDiff(objColPos.x, objColScale.x, pos.x, scale.x);
				objPos.x -= moveDir.x * fDiff;
			}
			break;
			case COLLIDE_TYPE::COLLIDE_RIGHT:
			{
				float fDiff = calColliderDiff(objColPos.x, objColScale.x, pos.x, scale.x);
				objPos.x += moveDir.x * fDiff;
			}
			break;
			case COLLIDE_TYPE::COLLIDE_BOTTOM:
			{

			}
			break;
			case COLLIDE_TYPE::COLLIDE_IDLE:
				break;
			default:
				break;
			}
			obj->SetPos(objPos);
		}
		
	}

}

void CGround::OnCollisionExit(CCollider* _col)
{
	CObject* obj = _col->GetOwner();
	if (obj->GetName() == L"Player" || obj->GetName() == L"Monster")
	{
		obj->GetGravity()->SetGround(false, GROUND_TYPE::NONE);
		m_currentCollide = COLLIDE_TYPE::COLLIDE_IDLE;
	}
}

void CGround::Save(FILE* _file)
{
	CGameObject::Save(_file);
	int objType = TYPE_NUMBER(GetType());

	fwrite(&objType, sizeof(int), 1, _file);


}

void CGround::Load(FILE* _file)
{
	CGameObject::Load(_file);

	int objType = TYPE_NUMBER(GetType());

	fread(&objType, sizeof(int), 1, _file);

	SetType((GAMEOBJECT_TYPE)objType);
}

float CGround::calColliderDiff(float  _objPos, float _objScale, float _colPos, float _colScale)
{
	float fLen = abs(_objPos - _colPos);
	return (_objScale / 2.f + _colScale / 2.f) - fLen;
}


