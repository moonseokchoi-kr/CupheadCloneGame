#pragma once
class CUI;

/// <summary>
/// UI의 이벤트를 종합적으로 관리하는 매니저 클래스
/// 
/// 작성자 최문석
/// 
/// 버전
/// 
/// 1.0 - 매니저 클래스 작성 2021-07-19
/// 1.1 - 포커스 기능 추가 2021-07-22
/// </summary>
class CUIManager
{
	SINGLE(CUIManager);
public:
	void Update();
public:
	CUI* GetTargetedUI(CUI* _parentUI);
	CUI* GetFocusedUI();
	void SetFocusedUI(CUI* _ui);
private:
	CUI* m_focusedUI;
};

