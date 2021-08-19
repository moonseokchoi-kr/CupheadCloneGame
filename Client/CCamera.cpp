#include "pch.h"
#include "CCamera.h"


#include "CObject.h"
#include "CTexture.h"


#include "CKeyManager.h"
#include "CTimeManager.h"
#include "CCore.h"
#include "CResourceManager.h"
#include "CSceneManager.h"
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
			m_initLookAt = m_lookAt;
		}
	}
	if (CSceneManager::GetInst()->GetCurrentScene()->GetSceneName() == L"Tool Scene")\
	{
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
	}
	
	vibeCamera();

	CalDiff();
}

void CCamera::Render(HDC _dc)
{
	//필요한 부분만 렌더링
	
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
	if (CAMERA_EFFECT::VIBRATION == ef.effect)
	{
		return;
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
	if (CSceneManager::GetInst()->GetCurrentScene()->GetSceneName() == L"Tool Scene")
	{
		m_currentLookAt = m_lookAt;
		Vec2 resolution = CCore::GetInst()->GetResolution();
		Vec2 center = resolution / 2;

		m_difference = m_currentLookAt - center;
		return;
	}
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

void CCamera::vibeCamera()
{
	if (CSceneManager::GetInst()->GetCurrentScene()->GetObjWithType(GROUP_TYPE::PLAYER).empty())
		return;
	if (m_camEffects.empty())
		return;
	camEffect& ef = m_camEffects.front();
	if (ef.effect != CAMERA_EFFECT::VIBRATION)
		return;
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(-1, 1);
	ef.currentTime += fDT;
	m_lookAt = m_initLookAt;
	float t = (ef.duration - ef.currentTime) * 0.01f;
	m_lookAt.y += dis(gen)*(sin(2.0f * 3.14159f * t * 3) * 30.0f +
		sin(2.0f * 3.14159f * t * 7 + 0.2f) * 10.1f +
		sin(2.0f * 3.14159f * t * 15 + 0.5f) * 1.1f)* (0.05f - t) / 0.15f;
	m_lookAt.x += dis(gen) * (sin(2.0f * 3.14159f * t * 3) * 30.0f +
		sin(2.0f * 3.14159f * t * 7 + 0.2f) * 10.1f +
		sin(2.0f * 3.14159f * t * 15 + 0.5f) * 1.1f) * (0.05f - t) / 0.15f;
	if (ef.duration < ef.currentTime)
		m_camEffects.pop_front();

}
