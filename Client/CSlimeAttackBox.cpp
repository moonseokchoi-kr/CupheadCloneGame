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
	//°øÀÌ Æ¨±âµí 5È¸Á¤µµ ÇÃ·¹ÀÌ¾î°¡ ÀÖ´Â ¹æÇâÀ¸·Î Æ¨±è
	//È¦¼öÈ¸´Â ³·°Ô
	//Â¦¼öÈ¸´Â Á» ³ô°Ô
	//ÁÖ¸ÔÀ» »¸´Â ÆÐÅÏ
	//ÆäÀÌÁî 1¿¡´Â ¾ó±¼À» »¸À½
	//ÆäÀÌÁî 2¿¡´Â °¡·Î·Î ÈÎ¾À ³ÐÀº ¹üÀ§ÀÇ ÁÖ¸ÔÀ» »¸À½

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
