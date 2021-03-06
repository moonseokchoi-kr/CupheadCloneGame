#pragma once
#include "CUI.h"
#include "CScene.h"

typedef void(*BTN_FUNC) (DWORD_PTR, DWORD_PTR);
typedef void(CScene::* SCENE_MEM_FUNC_VOID)(void);
typedef void(CScene::* SCENE_MEM_FUNC_INT)(int);
typedef void(*SCENE_MEM_FUNC_SCENE_TYPE)(SCENE_TYPE);
typedef void(*SCENE_MEM_FUNC_STATIC_VOID)(void);
/// <summary>
/// ui에서 버튼의 기능을 담당하는 ui
/// 
/// 작성자 : 최문석
/// 
/// 버전
/// 1.0 - 버튼 ui 작성 2021-07-22
/// </summary>

class CTexture;
class CSound;
class CButtonUI :
    public CUI
{

public:
	CButtonUI(bool _cameraAffeted);
	~CButtonUI();

public:
	virtual void Render(HDC _dc);
	virtual void MouseOn();
	virtual void MouseLButtonDown();
	virtual void MouseLButtonUp();
	virtual void MouseLButtonClicked();
public:

	void SetClickedCallBack(BTN_FUNC _pfunc, DWORD_PTR _param1, DWORD_PTR _param2)
	{
		m_callBackFuction = _pfunc;
		m_param2 = _param2;
		m_param1 = _param1;
	}

	void SetClickedCallBack(CScene* _scene, SCENE_MEM_FUNC_VOID _pfunc)
	{
		m_sceneFunction = _pfunc;
		m_sceneInst = _scene;
	}

	void SetClickedCallBack(CScene* _scene, SCENE_MEM_FUNC_INT _pfunc, DWORD_PTR _param1)
	{
		m_sceneIntFunction = _pfunc;
		m_sceneInst = _scene;
		m_param1 = _param1;
	}
	void SetClickedCallBack(SCENE_MEM_FUNC_SCENE_TYPE _pfunc, DWORD_PTR _param1)
	{
		m_sceneTypeFunction = _pfunc;
		m_param1 = _param1;
	}
	void SetClickedCallBack(SCENE_MEM_FUNC_STATIC_VOID _pfunc)
	{
		m_sceneVoidFunction = _pfunc;
	}
	void SetTex(CTexture* _tex) { m_tex = _tex; }

	CLONE(CButtonUI);
private:
	BTN_FUNC	m_callBackFuction;
	SCENE_MEM_FUNC_VOID m_sceneFunction;
	SCENE_MEM_FUNC_INT m_sceneIntFunction;
	SCENE_MEM_FUNC_SCENE_TYPE m_sceneTypeFunction;
	SCENE_MEM_FUNC_STATIC_VOID m_sceneVoidFunction;
	CSound* m_sfx;
	CScene* m_sceneInst;
	DWORD_PTR	m_param1;
	DWORD_PTR	m_param2;
	CTexture* m_tex;
};

