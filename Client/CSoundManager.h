#pragma once

#include <mmsystem.h>
#include <dsound.h>
#include <dinput.h>

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dsound.lib")

class CSound;

class CSoundManager
{
	SINGLE(CSoundManager);

public:
	int init(void);
	LPDIRECTSOUND8 GetSoundDevice() { return m_pSound; }
	void RegisterToBGM(CSound* _pSound);

private:
	LPDIRECTSOUND8	m_pSound;	// ����ī�� ��ǥ ��ü
	CSound* m_pBGM;		// ���� ������ BGM Sound
};

