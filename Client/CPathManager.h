#pragma once
/// <summary>
/// 리소스들을 저장하는 디렉토리 구조에서 경로를 
/// 관리하는 역할을 수행하는 클래스
/// 
/// 작성자 : 최문석
/// 
/// 작성일시 : 2021-07-03
/// 
/// 버전 : 
/// 1.0 - 초기화함수 제작
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

