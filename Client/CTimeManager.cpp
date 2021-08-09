#include "pch.h"
#include "CTimeManager.h"

CTimeManager::CTimeManager() :
	m_llCurCount{}
	, m_llFrequency{}
	,m_llPrevCount{}
	, m_iCallCount{}
	, m_iFps{}
	, m_dDeltaTime(0)
	, m_dAcc(0)
{

}

CTimeManager::~CTimeManager()
{

}

void CTimeManager::Init()
{
	QueryPerformanceCounter(&m_llPrevCount);
	QueryPerformanceFrequency(&m_llFrequency);
}

void CTimeManager::Update()
{
	QueryPerformanceCounter(&m_llCurCount);

	m_dDeltaTime = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / m_llFrequency.QuadPart;

	m_llPrevCount = m_llCurCount;

	++m_iCallCount;

	m_dAcc += m_dDeltaTime;
	
#ifdef _DEBUG
	if (m_dDeltaTime >= (1.f / 60.f))
		m_dDeltaTime = 1.f / 60.f;
#endif
	if (m_dAcc >= 1.f)
	{
		m_iFps = m_iCallCount;
		m_dAcc = 0.f;
		m_iCallCount = 0;
		swprintf_s(szBuffer, L"FPS:%d, DT: %f", m_iFps, m_dDeltaTime);
	}
}
