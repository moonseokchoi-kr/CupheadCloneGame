#include "pch.h"
#include "CResourceManager.h"
#include "CPathManager.h"
#include "CTexture.h"
#include "CSound.h"
CResourceManager::CResourceManager()
{

}

CResourceManager::~CResourceManager()
{
	Safe_Delete_Map(m_mapTex);
}

CTexture* CResourceManager::LoadTexture(const wstring& _key, const wstring& _relativePath)
{
	CTexture* tex = FindTexture(_key);

	if (nullptr !=  tex)
	{
		return tex;
	}
	wstring contentPath = CPathManager::GetInst()->GetContentPath();
	contentPath += _relativePath;

	tex = new CTexture;
	tex->Load(contentPath);

	tex->SetKey(_key);
	tex->SetRelativePath(_relativePath);

	m_mapTex.insert(make_pair(_key, tex));
	return tex;
}

CTexture* CResourceManager::CreateTexture(const wstring& _key, UINT _width, UINT _height)
{
	CTexture* tex = FindTexture(_key);

	if (nullptr != tex)
	{
		return tex;
	}

	tex = new CTexture;
	tex->Create(_width,_height);

	tex->SetKey(_key);

	m_mapTex.insert(make_pair(_key, tex));
	return tex;
}

CTexture* CResourceManager::FindTexture(const wstring& _key)
{
	unordered_map<wstring, CResource*>::iterator iter = m_mapTex.find(_key);

	if (iter == m_mapTex.end())
	{
		return nullptr;
	}
	return (CTexture*)iter->second;
}

CSound* CResourceManager::LoadSound(const wstring& _strKey, const wstring& _strRelativePath)
{
	assert(nullptr == FindSound(_strKey));

	CSound* pSound = new CSound;

	wstring strFilePath = CPathManager::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;
	HRESULT hr = pSound->Load(strFilePath.c_str());

	if (FAILED(hr))
	{
		MessageBox(nullptr, L"Sound 로딩 실패!!!", L"리소스 로딩 실패", MB_OK);
		delete pSound;
		return nullptr;
	}

	pSound->SetKey(_strKey);
	pSound->SetRelativePath(_strRelativePath);

	// map 에 등록
	m_mapSound.insert(make_pair(_strKey, pSound));

	return pSound;
}

CSound* CResourceManager::FindSound(const wstring& _strKey)
{
	unordered_map<wstring, CResource*>::iterator iter = m_mapSound.find(_strKey);

	if (iter == m_mapSound.end())
		return nullptr;

	return (CSound*)iter->second;
}
