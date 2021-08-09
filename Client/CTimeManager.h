#pragma once
/// <summary>
/// 게임내 프레임당 시간을 관리하는 시간매니저 클래스
/// </summary>
/// 
/// 작성자: 최문석
/// 작성일시 : 2021-06-30
/// 버전: 1.0
/// 버전내용: 기본적인 구조 작성
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
	//1프레임당 시간(delta time)
	//컴퓨터사양이 항상 일정할 수 없으므로 프로그램
	//실행하는 시간동안 계속 계산되어야함
	//GetTickCount() 1초당 1000을 센다
	//QueryPerformanceCounter() 1초당 100만을 센다.
	LARGE_INTEGER m_llCurCount;
	LARGE_INTEGER m_llFrequency;
	LARGE_INTEGER m_llPrevCount;

	double		  m_dDeltaTime;
	double		  m_dAcc;
	UINT		  m_iCallCount;
	UINT		  m_iFps;
	wchar_t		  szBuffer[255] = {};
};
