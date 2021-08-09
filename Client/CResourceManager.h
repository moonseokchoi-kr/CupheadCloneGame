#pragma once
class CTexture;
class CResource;

class CResourceManager
{
	SINGLE(CResourceManager);
public:
	CTexture* LoadTexture(const wstring& _key, const wstring& _relativePath);
	CTexture* CreateTexture(const wstring& _key, UINT _width, UINT _height);
	CTexture* FindTexture(const wstring& _key);
private:
	unordered_map<wstring, CResource*> m_mapTex;
};

