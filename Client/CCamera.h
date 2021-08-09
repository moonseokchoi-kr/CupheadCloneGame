#pragma once


enum class CAMERA_TYPE
{
	DEFALT,
	SMOOTH,
	NONE,
};


enum class CAMERA_EFFECT
{
	FADE_IN,
	FADE_OUT,
};

struct camEffect
{
	CAMERA_EFFECT effect;
	float duration;
	float currentTime;
};
/// <summary>
/// �������� ������ ȭ���� �����ϴ� ī�޶� Ŭ����
/// </summary>
/// 
/// �ۼ��� �ֹ���
/// 
/// ����
/// 
/// 1.0 - ī�޶� �⺻���� �ۼ� 2021-07-12
/// 1.1 - SMOOTH CAMERA����߰�
/// 1.2 - FADEIN,FADEOUT �߰�


class CCamera
{
	SINGLE(CCamera);

public:
	void Init();
	void Update();
	void Render(HDC _dc);
	void CalDiff();
public:
	void SetLookAt(Vec2 _look)
	{
		m_lookAt = _look;
		m_currentLookAt = m_lookAt;
		float moveDist = (m_lookAt - m_prevLookAt).Distance();
		m_moveSpeed = moveDist / m_moveTime;
		m_minMoveSpeed = moveDist / m_moveTime * 0.5f;
		m_accTime = 0;
	}
	void SetTarget(CObject* _target) { m_targetObject = _target; }
	void SetType(CAMERA_TYPE _type) { m_cameraType = _type; }
	void SetCameraMove(bool _b) { m_cameramove = _b; }
	Vec2 GetLookAt() { return m_currentLookAt; }
	Vec2 GetRenderPos(Vec2 _objPos) { return _objPos - m_difference; }
	Vec2 GetRealPos(Vec2 _renderPos) { return _renderPos + m_difference; }
public:
	void SetCamEffect(float _time, CAMERA_EFFECT _effect)
	{
		camEffect ef = {};
		ef.effect = _effect;
		ef.duration = _time;
		ef.currentTime = 0.f;
		m_camEffects.push_back(ef);
	}
private:
	void defaultCameraMove();
	void smoothCameraMove();
private:
	Vec2 m_lookAt; //ī�޶� ���� ��ġ
	Vec2 m_prevLookAt; //������������ ���� ��ġ
	Vec2 m_currentLookAt; //���� �������� ���� ��ġ

	CObject* m_targetObject; //ī�޶� �� ������Ʈ
	Vec2 m_difference; //������ǥ�� ������ǥ ����

	CAMERA_TYPE  m_cameraType; //ī�޶��� Ÿ��
	
	float m_moveTime;
	float m_moveSpeed;
	float m_accTime;
	float m_minMoveSpeed;
	
	bool m_cameramove;

	CTexture* m_veilTexture;
	list<camEffect> m_camEffects;


};

