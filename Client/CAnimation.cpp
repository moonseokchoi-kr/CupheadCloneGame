#include "pch.h"
#include "CAnimation.h"

#include "CTimeManager.h"

#include "CAnimator.h"
#include "CTexture.h"
#include "CObject.h"
#include "CCamera.h"
CAnimation::CAnimation()
	:m_animator(nullptr)
	,m_tex(nullptr)
	,m_currentFrame(0)
	,m_accTime(0.f)
	,m_finish(false)
{
}

CAnimation::~CAnimation()
{
}

void CAnimation::Update()
{
	if (m_finish)
		return;
	m_accTime += fDT;

	if (m_frames[m_currentFrame].duration < m_accTime)
	{
		++m_currentFrame;

		if (m_frames.size() <= m_currentFrame)
		{
			m_currentFrame = 0;
			m_finish = true;
			m_accTime = 0.f;
			return;
		}
		
		m_accTime -= m_frames[m_currentFrame].duration;
	}
}

void CAnimation::Render(HDC _dc)
{
	if (m_finish)
		return;

	CObject* obj = m_animator->GetObject();
	Vec2 pos = obj->GetPos();
	
	pos += m_frames[m_currentFrame].offset;
	pos = CCamera::GetInst()->GetRenderPos(pos);
// 	TransparentBlt(_dc
// 		, (int)(pos.x - m_frames[m_currentFrame].slice.x / 2.f)
// 		, (int)(pos.y - m_frames[m_currentFrame].slice.y / 2.f)
// 		, (int)(m_frames[m_currentFrame].slice.x)
// 		, (int)(m_frames[m_currentFrame].slice.y)
// 		, m_tex->GetDC()
// 		, (int)(m_frames[m_currentFrame].lt.x)
// 		, (int)(m_frames[m_currentFrame].lt.y)
// 		, (int)(m_frames[m_currentFrame].slice.x)
// 		, (int)(m_frames[m_currentFrame].slice.y)
// 		, RGB(255, 0, 255)
// 	);

	BLENDFUNCTION bf = {};
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = AC_SRC_ALPHA;
	bf.SourceConstantAlpha = 255;

	AlphaBlend(
		_dc
		, (int)(pos.x - m_frames[m_currentFrame].slice.x / 2.f)
 		, (int)(pos.y - m_frames[m_currentFrame].slice.y / 2.f)
 		, (int)(m_frames[m_currentFrame].slice.x)
 		, (int)(m_frames[m_currentFrame].slice.y)
 		, m_tex->GetDC()
 		, (int)(m_frames[m_currentFrame].lt.x)
 		, (int)(m_frames[m_currentFrame].lt.y)
 		, (int)(m_frames[m_currentFrame].slice.x)
 		, (int)(m_frames[m_currentFrame].slice.y)
		, bf
	);
}

void CAnimation::Create(CTexture* _tex, Vec2 _lt, Vec2 _sliceSize, Vec2 _step, float _duration, UINT _frameCount, bool _reverse)
{
	m_tex = _tex;
	animFrame frame = {};
	for (UINT i = 0; i < _frameCount; ++i)
	{
		frame.duration = _duration;
		frame.slice = _sliceSize;
		frame.lt = _lt + _step * (float)i;

		m_frames.push_back(frame);
	}
	if (_reverse)
		reverse(m_frames.begin(), m_frames.end());
		
}
