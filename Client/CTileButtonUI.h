#pragma once
#include "CButtonUI.h"


typedef void(CScene::* SCENE_MEM_FUNC)(int);
class CTexture;

/// <summary>
/// 타일의 종류를 지정하는 버튼 UI
/// </summary>
class CTileButtonUI :
    public CButtonUI
{
public:
	CTileButtonUI(bool _cameraAffected);
	~CTileButtonUI();
public:

	virtual void Render(HDC _dc);
	virtual void MouseOn();
	virtual void MouseLButtonDown();
	virtual void MouseLButtonUp();
	virtual void MouseLButtonClicked();
public:

	void SetClickedCallBack(CScene* _scene, SCENE_MEM_FUNC _pfunc)
	{
		m_callBackFuction = _pfunc;
		m_sceneInst = _scene;
	}
	int GetTileidx() { return m_idx; }
	void SetTileidx(int _idx) { m_idx = _idx; }
	CLONE(CTileButtonUI);

private:
	SCENE_MEM_FUNC m_callBackFuction;
	CScene* m_sceneInst;
	int m_idx;
	CTexture* m_tex;
};

