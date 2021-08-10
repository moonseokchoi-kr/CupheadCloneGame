#pragma once
enum class KEY_STATE
{
	TAP,//막 누른시점
	HOLD,// 누르고 있는
	AWAY,// 막땐 시점
	NONE,// NONE
};

enum class KEY
{
	UP,
	DOWN,
	LEFT,
	RIGHT,

	Q,
	W,
	E,
	R,
	T,
	Y,
	U,
	I,
	O,
	P,
	A,
	S,
	D,
	F,
	G,
	H,
	Z,
	X,
	C,
	V,
	B,

	ALT,
	LCTRL,
	LSHIFT,
	SPACE,
	ENTER,
	DELT,
	ESC,

	MOUSE_MOVE,
	MOUSE_LBUTTON,
	MOUSE_RBUTTON,

	LAST,

};


struct tKeyInfo
{
	KEY_STATE	state;
	bool		bPrevPush; //이전 프레임에 눌렸는지.. 커맨드조합?
};

/// <summary>
/// 게임에서 사용자가 입력한 키의 이벤트처리를 담당하는 매니저 클래스
/// </summary>
/// 
/// 작성자: 최문석
/// 작성일시 : 2021-06-30
/// 버전:
///  1.0 기본적인 구조 작성
///	 1.1 비활성화시 사용자 입력이 안되도록 설정
class CKeyManager
{
	SINGLE(CKeyManager);

public:
	void Init();
	void Update();
	KEY_STATE GetKeyState(KEY _key) { return m_vecKey[(int)_key].state; }
	Vec2 GetMousePos() { return m_currentMousePos; }
private:
	vector<tKeyInfo> m_vecKey;

	Vec2 m_currentMousePos;
};

