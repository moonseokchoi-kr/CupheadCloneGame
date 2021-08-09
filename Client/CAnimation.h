#pragma once

class CAnimator;
class CTexture;

struct animFrame
{
	Vec2 lt;
	Vec2 slice;
	Vec2 offset;
	float duration;
};
/// <summary>
/// �ִϸ��̼��� ǥ���� Ŭ����
/// </summary>
/// 
/// �ۼ��� : �ֹ���
/// 
/// ���� 
/// 
/// 1.0 - �⺻���� Ŭ���� ���� �ۼ� 2021-07-11
/// 1.1 - offset �߰�
class CAnimation
{
public:
	CAnimation();
	CAnimation(const CAnimation& _origin);
	~CAnimation();
public:
	const wstring& GetName() { return m_name; }
	void SetName(const wstring& _str) { m_name = _str; }

	bool IsFinish() { return m_finish; }
	void SetFrame(int _frame)
	{
		m_finish = false;
		m_currentFrame = _frame;
		m_accTime = 0.f;
	}
public:
	void Update();
	void Render(HDC _dc);
	void Create(CTexture* _tex, Vec2 _lt, Vec2 _sliceSize, Vec2 _step, float _duration, UINT _frameCount, bool _reverse);
private:
	wstring m_name;
	CAnimator* m_animator;
	CTexture* m_tex;

	vector<animFrame> m_frames;

	int m_currentFrame;
	float m_accTime;
	bool m_finish;

	friend class CAnimator;
};

