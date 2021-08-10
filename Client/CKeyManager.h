#pragma once
enum class KEY_STATE
{
	TAP,//�� ��������
	HOLD,// ������ �ִ�
	AWAY,// ���� ����
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
	bool		bPrevPush; //���� �����ӿ� ���ȴ���.. Ŀ�ǵ�����?
};

/// <summary>
/// ���ӿ��� ����ڰ� �Է��� Ű�� �̺�Ʈó���� ����ϴ� �Ŵ��� Ŭ����
/// </summary>
/// 
/// �ۼ���: �ֹ���
/// �ۼ��Ͻ� : 2021-06-30
/// ����:
///  1.0 �⺻���� ���� �ۼ�
///	 1.1 ��Ȱ��ȭ�� ����� �Է��� �ȵǵ��� ����
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

