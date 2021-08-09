#pragma once
/// <summary>
/// ��� ���ҽ����� �θ�Ŭ������ ����� �޾� ����Ѵ�.
/// 
/// �ۼ���: �ֹ���
/// �ۼ��Ͻ�: 2021-07-03
/// ����:
/// 1.0 - �⺻ ���� �ۼ�
/// </summary>
class CResource
{
public:
	CResource();
	virtual ~CResource();
public:
	virtual bool Load(const wstring& _path) = 0;
	void SetKey(const wstring& _key) { m_resourceKey = _key; }
	void SetRelateivePath(const wstring& _path) { m_relativePath = _path; }

	const wstring& GetKey() { return m_resourceKey; }
	const wstring& GetRelativePath() { return m_relativePath; }
private:
	wstring m_resourceKey;
	wstring m_relativePath;
};
