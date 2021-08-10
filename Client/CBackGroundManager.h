#pragma once

class CBackGround;
/// <summary>
/// background 오브젝트를 일괄 관리하는 클래스
/// </summary>
class CBackGroundManager
{
	SINGLE(CBackGroundManager);

public:
	void Update();
public:
	CBackGround* GetFocusBack() { return m_focusedBack; }
private:
	CBackGround* getFocusedObj();
private:
	CBackGround* m_focusedBack;
	CBackGround* m_prevTargetBack;

};

