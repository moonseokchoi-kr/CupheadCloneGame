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
	,m_vibe(0.15f)
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
			m_currentLookAt = m_lookAt;
		}
		calLookAt();
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

Vec2 CCamera::GetCameraLT()
{
	Vec2 resolution = CCore::GetInst()->GetResolution();
	return m_lookAt - resolution / 2.f;
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
		sin(2.0f * 3.14159f * t * 15 + 0.5f) * 1.1f)* (0.05f - t) / m_vibe;
	m_lookAt.x += dis(gen) * (sin(2.0f * 3.14159f * t * 3) * 30.0f +
		sin(2.0f * 3.14159f * t * 7 + 0.2f) * 10.1f +
		sin(2.0f * 3.14159f * t * 15 + 0.5f) * 1.1f) * (0.05f - t) / m_vibe;
	if (ef.duration < ef.currentTime)
		m_camEffects.pop_front();

}

void CCamera::calLookAt()
{
	//맵 해상도 
	//1450.960
	m_mapResolution = Vec2(1450, 830);
	//카메라 해상도
	//1280,720
	//타겟이 있으면 타겟의 현재위치로 카메라 m_lookAt계산
	//현재 보는 위치에서 좌상단의 x좌표가 마이너스가 되거나 y좌표가 마이너스가 되면 카메라 이동 x



	Vec2 resolution = CCore::GetInst()->GetResolution();
	if (!m_targetObject)
	{
		return;
	}
	/// 타겟의 위치정보
	Vec2 targetPos = m_targetObject->GetPos();
	Vec2 targetScale = m_targetObject->GetScale();
	float targetT = targetPos.y - targetScale.y / 2.f;
	float targetR = targetPos.x + targetScale.x / 2.f;
	float targetL = targetPos.x - targetScale.x / 2.f;
	float targetB = targetPos.y + targetScale.y / 2.f;

	/// 카메라의 위치정보
	float cameraR = m_lookAt.x + resolution.x / 2.f;
	float cameraL = m_lookAt.x - resolution.x / 2.f;
	float cameraT = m_lookAt.y - resolution.y / 2.f;
	float cameraB = m_lookAt.y + resolution.y / 2.f;


	//여백공간
	float leftArea = (m_mapResolution.x - resolution.x) / 2.f;
	float topArea = (m_mapResolution.y - resolution.y) / 2.f;
	float rightArea = m_mapResolution.x - leftArea;
	float bottomArea = m_mapResolution.y - topArea;

	if (cameraL<= 0)
	{
		m_lookAt.x = resolution.x/2.f;
	}
	else if (cameraR >= m_mapResolution.x)
	{
		m_lookAt.x = m_mapResolution.x - resolution.x / 2.f;
	}
	else if (leftArea <= targetL && targetR <= rightArea)
	{
		m_lookAt.x = targetPos.x;
	}
	if (cameraT <= 0)
	{
		m_lookAt.y = targetPos.y + targetScale.y - resolution.y / +100.f;
	}
	else if (cameraB >= m_mapResolution.y)
	{
		m_lookAt.y = bottomArea - resolution.y / 2.f+ 100.f;
	}
	else if (topArea <= targetT && targetB <= bottomArea)
	{
		m_lookAt.y = resolution.y / 2.f+100.f;
	}
	
	else
		m_lookAt.y= targetPos.y;
	m_initLookAt = m_lookAt;
	m_currentLookAt = m_lookAt;
}
