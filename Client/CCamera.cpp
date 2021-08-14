#include "pch.h"
#include "CCamera.h"


#include "CObject.h"
#include "CTexture.h"


#include "CKeyManager.h"
#include "CTimeManager.h"
#include "CCore.h"
#include "CResourceManager.h"

CCamera::CCamera()
	: m_targetObject(nullptr)
	, m_moveSpeed(0)
	, m_moveTime(3.f)
	, m_accTime(0.f)
	, m_cameraType(CAMERA_TYPE::DEFALT)
	, m_cameramove(false)
	, m_veilTexture(nullptr)
{
 
}

CCamera::~CCamera()
{

}
void CCamera::Init()
{
	Vec2 resolution = CCore::GetInst()->GetResolution();
	m_veilTexture = CResourceManager::GetInst()->CreateTexture(L"VeilTexture", (UINT)resolution.x, (UINT)resolution.y);
}
void CCamera::Update()
{
	if (m_targetObject)
	{
		if (m_targetObject->IsDead())
		{
			m_targetObject = nullptr;
		}
		else
		{
			m_lookAt = m_targetObject->GetPos();
		}
	}
	
	if (KEY_HOLD(KEY::LEFT))
	{
		m_lookAt.x -= 500.f * fDT;
	}
	if (KEY_HOLD(KEY::RIGHT))
	{
		m_lookAt.x += 500.f * fDT;
	}
	if (KEY_HOLD(KEY::UP))
	{
		m_lookAt.y -= 500.f * fDT;
	}
	if (KEY_HOLD(KEY::DOWN))
	{
		m_lookAt.y += 500.f * fDT;
	}
	
	CalDiff();
}

void CCamera::Render(HDC _dc)
{
	if (m_camEffects.empty())
		return;
	camEffect& ef = m_camEffects.front();
	ef.currentTime += fDT;

	float ratio = ef.currentTime / ef.duration;
	if (ratio < 0.f)
		ratio = 0.f;
	if (1.f < ratio)
		ratio = 1.f;
	int alpha = 0;

	if (CAMERA_EFFECT::FADE_OUT == ef.effect)
	{
		alpha = (int)(255.f * ratio);

	}
	if (CAMERA_EFFECT::FADE_IN == ef.effect)
	{
		alpha = (int)(255.f * (1 - ratio));
	}

	BLENDFUNCTION bf = {};
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = 0;
	bf.SourceConstantAlpha = alpha;

	AlphaBlend(
		_dc
		, 0, 0
		, m_veilTexture->Width()
		, m_veilTexture->Height()
		, m_veilTexture->GetDC()
		, 0, 0
		, m_veilTexture->Width()
		, m_veilTexture->Height()
		, bf
	);
	if (ef.duration < ef.currentTime)
	{
		m_camEffects.pop_front();
		return;
	}
}

void CCamera::CalDiff()
{
	///
	/// 부드럽게 움직이기
	/// 
	Vec2 resolution = CCore::GetInst()->GetResolution();
	Vec2 center = resolution / 2;
	if (m_cameraType == CAMERA_TYPE::DEFALT)
	{
		defaultCameraMove();
	}
	else if (m_cameraType == CAMERA_TYPE::SMOOTH)
	{
		m_moveSpeed = 0;
		smoothCameraMove();
	}

	m_difference = m_currentLookAt - center;

	m_prevLookAt = m_currentLookAt;
}

void CCamera::defaultCameraMove()
{
	m_accTime += fDT;

	if (m_currentLookAt == m_lookAt)
		return;
	if (m_moveTime <= m_accTime )
	{
		m_currentLookAt = m_lookAt;
	}
	else
	{
		Vec2 dir = m_lookAt - m_prevLookAt;
		m_currentLookAt = m_prevLookAt + dir.Normalize() * m_moveSpeed * fDT;
	}
}

void CCamera::smoothCameraMove()
{
	m_accTime += fDT;
	if (m_currentLookAt == m_lookAt)
	{
		return;
	}
	else if (m_moveTime <= m_accTime)
	{
		m_currentLookAt = m_lookAt;
	}
	else
	{
		Vec2 dir = m_lookAt - m_prevLookAt;
		m_moveSpeed = dir.Distance() / m_moveTime;
		if (m_moveSpeed < m_minMoveSpeed)
		{
			m_moveSpeed = m_minMoveSpeed;
		}
		m_currentLookAt = m_prevLookAt + dir.Normalize() * m_moveSpeed * fDT;
	}
}
