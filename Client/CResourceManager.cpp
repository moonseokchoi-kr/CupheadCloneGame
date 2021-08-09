#include "pch.h"
#include "CResourceManager.h"
#include "CPathManager.h"
#include "CTexture.h"
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
	tex->SetRelateivePath(_relativePath);

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
