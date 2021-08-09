#pragma once
class CUI;

/// <summary>
/// UI�� �̺�Ʈ�� ���������� �����ϴ� �Ŵ��� Ŭ����
/// 
/// �ۼ��� �ֹ���
/// 
/// ����
/// 
/// 1.0 - �Ŵ��� Ŭ���� �ۼ� 2021-07-19
/// 1.1 - ��Ŀ�� ��� �߰� 2021-07-22
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

