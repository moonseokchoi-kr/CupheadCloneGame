#pragma once
class CTexture;
class CResource;
class CSound;
class CResourceManager
{
	SINGLE(CResourceManager);
public:
	CTexture* LoadTexture(const wstring& _key, const wstring& _relativePath);
	CTexture* CreateTexture(const wstring& _key, UINT _width, UINT _height);
	CTexture* FindTexture(const wstring& _key);

	CSound* LoadSound(const wstring& _strKey, const wstring& _strRelativePath);
	CSound* FindSound(const wstring& _strKey);
private:
	unordered_map<wstring, CResource*> m_mapTex;
	unordered_map<wstring, CResource*> m_mapSound;
};

