#pragma once



class CAnimation;
class CObject;
class CTexture;
/// <summary>
/// 애니메이션을 재생하고 관리하는 애니메이터 컴포넌트
/// </summary>
class CAnimator
{
public:
	CAnimator();
	~CAnimator();
public:
	CObject* GetObject() { return m_owner; }
public:
	void CreateAnimation(const wstring& _name,CTexture* _tex, Vec2 _lt, Vec2 _sliceSize, Vec2 _step, float _fDuration, UINT _frameCount, bool _reverse);
	CAnimation* FindAnimation(const wstring& _name);
	void Play(const wstring& _name, bool _repeat);
	bool IsFinish();
	CAnimation* GetCurrentAnim() { return m_curAnim; }
	int GetAlpha() { return m_alpha; }
	void SetAlpha(int _alpha) { m_alpha = _alpha; }
public:
	void FinalUpdate();
	void Render(HDC _dc);

private:
	unordered_map<wstring, CAnimation*> m_animations;
	CObject* m_owner;
	CAnimation* m_curAnim;
	int m_curFrame;
	int m_alpha;
	bool m_repeat;
	friend class CObject;
};

