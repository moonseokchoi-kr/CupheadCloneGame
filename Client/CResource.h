#pragma once
/// <summary>
/// 모든 리소스들의 부모클래스로 상속을 받아 사용한다.
/// 
/// 작성자: 최문석
/// 작성일시: 2021-07-03
/// 버전:
/// 1.0 - 기본 구조 작성
/// </summary>
class CResource
{
public:
	CResource();
	virtual ~CResource();
public:
	void SetKey(const wstring& _key) { m_resourceKey = _key; }
	void SetRelativePath(const wstring& _path) { m_relativePath = _path; }

	const wstring& GetKey() { return m_resourceKey; }
	const wstring& GetRelativePath() { return m_relativePath; }
private:
	wstring m_resourceKey;
	wstring m_relativePath;
};

