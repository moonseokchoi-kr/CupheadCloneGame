#include "pch.h"
#include "CTexture.h"
#include "CCore.h"
CTexture::CTexture()
    :m_bitMap(0)
    ,m_hdc(0)
    , m_bitMapInfo{}
{
}


CTexture::~CTexture()
{
    DeleteDC(m_hdc);
    DeleteObject(m_bitMap);
}

bool CTexture::Load(const wstring& _path)
{
    m_bitMap = (HBITMAP)LoadImage(nullptr, _path.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
    assert(m_bitMap);


    //비트맵과 연결할 DC
    m_hdc = CreateCompatibleDC(CCore::GetInst()->GetMainDC());
    
    HBITMAP hPrevBit = (HBITMAP)SelectObject(m_hdc, m_bitMap);
    DeleteObject(hPrevBit);
    //비트맵의 정보
    GetObject(m_bitMap, sizeof(BITMAP), &m_bitMapInfo);

    return true;
}

void CTexture::Create(UINT _width, UINT _height)
{
    HDC mainDC = CCore::GetInst()->GetMainDC();

	m_bitMap = CreateCompatibleBitmap(mainDC, _width, _height);

	m_hdc = CreateCompatibleDC(mainDC);

	HBITMAP hOldBit = (HBITMAP)SelectObject(m_hdc, m_bitMap);

	DeleteObject(hOldBit);

    GetObject(m_bitMap, sizeof(BITMAP), &m_bitMapInfo);
}
