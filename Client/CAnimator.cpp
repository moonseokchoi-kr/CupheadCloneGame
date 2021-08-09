#include "pch.h"
#include "CAnimator.h"
#include "CAnimation.h"

CAnimator::CAnimator()
	:m_curAnim(nullptr)
	, m_curFrame(-1)
	, m_owner(nullptr)
	,m_repeat(false)
{
}

CAnimator::~CAnimator()
{

	Safe_Delete_Map(m_animations);
}

void CAnimator::CreateAnimation(const wstring& _name, CTexture* _tex, Vec2 _lt, Vec2 _sliceSize, Vec2 _step, float _duration, UINT _frameCount, bool _reverse)
{
	CAnimation* anim = FindAnimation(_name);
	assert(nullptr == anim);

	anim = new CAnimation;

	anim->SetName(_name);
	anim->m_animator = this;
	anim->Create(_tex, _lt, _sliceSize, _step, _duration, _frameCount, _reverse);

	m_animations.insert(make_pair(_name, anim));
}

CAnimation* CAnimator::FindAnimation(const wstring& _name)
{
	unordered_map<wstring, CAnimation*>::iterator iter = m_animations.find(_name);

	if(iter== m_animations.end())
		return nullptr;
	return iter->second;
}

void CAnimator::Play(const wstring& _name, bool _repeat)
{
	m_curAnim = FindAnimation(_name);
	m_repeat = _repeat;
}

bool CAnimator::IsFinish()
{
	return m_curAnim->m_finish; 
}


void CAnimator::FinalUpdate()
{
	if (nullptr != m_curAnim)
	{
		m_curAnim->Update();
		if (m_repeat && m_curAnim->IsFinish())
		{
			m_curAnim->SetFrame(0);
		}
	}
}

void CAnimator::Render(HDC _dc)
{
	if (nullptr != m_curAnim)
		m_curAnim->Render(_dc);
}

