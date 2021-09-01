#pragma once
#include "CResource.h"
class CTexture :
    public CResource
{
public:
    CTexture();
    ~CTexture();
public:
    // CResource을(를) 통해 상속됨
    bool Load(const wstring& _path);
	void Create(UINT _width, UINT _height);
    UINT Width() { return m_bitMapInfo.bmWidth; }
    UINT Height() { return m_bitMapInfo.bmHeight; }

    HDC GetDC() { return m_hdc; }
private:
    HBITMAP m_bitMap;
    HDC m_hdc;
    BITMAP m_bitMapInfo;
};

