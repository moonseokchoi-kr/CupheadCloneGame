#pragma once

class CBackGround;
/// <summary>
/// background ������Ʈ�� �ϰ� �����ϴ� Ŭ����
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

