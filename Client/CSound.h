#pragma once
#include "CResource.h"
#include "CSoundManager.h"
class CSound :
    public CResource
{
public:
	CSound();
	virtual ~CSound();
public:
	int Load(const wchar_t* _strPath);

	// 일반 재생
	void Play(bool _bLoop = false);

	// BGM 으로 재생
	void PlayToBGM(bool _bLoop = false);

	void Stop(bool _bReset = false);

	// 볼륨 범위 (0 ~ 100)
	void SetVolume(float _fVolume);

	// 음악파일 위치 조정
	void SetPosition(float _fPosition); // 0 ~ 100 사이

private:
	bool LoadWaveSound(const wstring& _strPath);
	int GetDecibel(float _fVolume);

private:
	LPDIRECTSOUNDBUFFER		m_pSoundBuffer;
	DSBUFFERDESC			m_tBuffInfo;
	int						m_iVolume;
};

