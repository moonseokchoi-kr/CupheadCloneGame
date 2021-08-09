#include "pch.h"
#include "CPathManager.h"

CPathManager::CPathManager()
	:m_contentPath{}
{

}
CPathManager::~CPathManager()
{

}
void CPathManager::Init()
{
	GetCurrentDirectory(255, m_contentPath);

	int iLen = (int)wcslen(m_contentPath);

	for (int i = iLen - 1; 0 <= i; --i)
	{
		if ('\\' == m_contentPath[i])
		{
			m_contentPath[i] = '\0';
			break;
		}
	}

	wcscat_s(m_contentPath, 255, L"\\bin\\content\\");

	printf("ContentPath: %ws", m_contentPath);
}

wstring CPathManager::GetRelativePath(const wchar_t* _fullPath)
{
	wstring fullPath = _fullPath;
	size_t fullLen = fullPath.length();
	size_t absLen = wcslen(m_contentPath);
	wstring relativePath = fullPath.substr(absLen, fullLen - absLen);
	return relativePath;
}
