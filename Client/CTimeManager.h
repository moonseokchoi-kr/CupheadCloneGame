#pragma once
/// <summary>
/// ���ӳ� �����Ӵ� �ð��� �����ϴ� �ð��Ŵ��� Ŭ����
/// </summary>
/// 
/// �ۼ���: �ֹ���
/// �ۼ��Ͻ� : 2021-06-30
/// ����: 1.0
/// ��������: �⺻���� ���� �ۼ�
class CTimeManager
{
	SINGLE(CTimeManager);

public:
	void Init();
	void Update();

public:
	double GetDeltaTime() { return m_dDeltaTime; }
	float GetfDeltaTime() { return (float)m_dDeltaTime; }
	wchar_t* GetTitle() { return szBuffer; }
private:
	//FPS
	//1�����Ӵ� �ð�(delta time)
	//��ǻ�ͻ���� �׻� ������ �� �����Ƿ� ���α׷�
	//�����ϴ� �ð����� ��� ���Ǿ����
	//GetTickCount() 1�ʴ� 1000�� ����
	//QueryPerformanceCounter() 1�ʴ� 100���� ����.
	LARGE_INTEGER m_llCurCount;
	LARGE_INTEGER m_llFrequency;
	LARGE_INTEGER m_llPrevCount;

	double		  m_dDeltaTime;
	double		  m_dAcc;
	UINT		  m_iCallCount;
	UINT		  m_iFps;
	wchar_t		  szBuffer[255] = {};
};
