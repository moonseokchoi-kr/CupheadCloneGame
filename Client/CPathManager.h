#pragma once
/// <summary>
/// ���ҽ����� �����ϴ� ���丮 �������� ��θ� 
/// �����ϴ� ������ �����ϴ� Ŭ����
/// 
/// �ۼ��� : �ֹ���
/// 
/// �ۼ��Ͻ� : 2021-07-03
/// 
/// ���� : 
/// 1.0 - �ʱ�ȭ�Լ� ����
/// </summary>
class CPathManager
{
	SINGLE(CPathManager);

public:
	void Init();

	const wchar_t* GetContentPath() { return m_contentPath; }
	wstring GetRelativePath(const wchar_t* _fullPath);
private:
	wchar_t m_contentPath[255];

};

