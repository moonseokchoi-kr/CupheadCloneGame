#include "pch.h"
#include "CSlimeAttackBox.h"

CSlimeAttackBox::CSlimeAttackBox()
	:m_attackCount(0)
{
}

CSlimeAttackBox::~CSlimeAttackBox()
{
}

void CSlimeAttackBox::Update()
{
	//���� ƨ��� 5ȸ���� �÷��̾ �ִ� �������� ƨ��
	//Ȧ��ȸ�� ����
	//¦��ȸ�� �� ����
	//�ָ��� ���� ����
	//������ 1���� ���� ����
	//������ 2���� ���η� �ξ� ���� ������ �ָ��� ����

	if (m_attackCount >4)
	{
		m_attackCount = 0;

	}
}

void CSlimeAttackBox::Fire()
{
}

void CSlimeAttackBox::Render(HDC _dc)
{
}
