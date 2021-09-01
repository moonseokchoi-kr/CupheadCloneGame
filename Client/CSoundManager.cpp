#include "pch.h"
#include "CSoundManager.h"
#include "CResourceManager.h"
#include "CSoundManager.h"
#include "CCore.h"
CSoundManager::CSoundManager()
    :m_pSound(nullptr)
    ,m_pBGM(nullptr)
{

}

CSoundManager::~CSoundManager()
{

}


int CSoundManager::init(void)
{
    if (FAILED(DirectSoundCreate8(NULL, &m_pSound, NULL)))
    {
        MessageBox(NULL, L"사운드디바이스 생성실패", L"SYSTEM ERROR", MB_OK);
        return false;
    }
    HWND hWnd = CCore::GetInst()->GetMainHwnd();
	if (FAILED(m_pSound->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE)))
	{
        MessageBox(NULL, L"사운드디바이스 협조레벨 설정", L"SYSTEM ERROR", MB_OK);
        return false;
	}
    return true;
}

void CSoundManager::RegisterToBGM(CSound* _pSound)
{
    if (m_pBGM != nullptr)
	    m_pBGM->Stop(true);

	m_pBGM = _pSound;
}
