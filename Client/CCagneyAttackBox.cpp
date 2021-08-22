#include "pch.h"
#include "CCagneyAttackBox.h"
#include "CFaceAttack.h"
#include "CSeedBullet.h"
#include "CMonSeedBullet.h"

#include "CCollider.h"
CCagneyAttackBox::CCagneyAttackBox()
	:m_currnetPatt(ATTACK_PATT::END)
	, m_seedBulletCount(0)
{
	m_faceAttack = new CFaceAttack;
	CreateObject(m_faceAttack, GROUP_TYPE::MONSTER_BULLET);
}

CCagneyAttackBox::~CCagneyAttackBox()
{
	delete m_faceAttack;
}

void CCagneyAttackBox::Update()
{
	CAttackBox::Update();
}

void CCagneyAttackBox::Fire()
{
	CBullet* bullet = nullptr;
	CBullet* cloneBullet = nullptr;
	if (!m_faceAttack->isAttackFinish())
		return;
	else
	{
		switch (m_currnetPatt)
		{
		case ATTACK_PATT::PATT1:
		{
			SetPos(Vec2(-GetOwner()->GetScale().x / 2.f, -GetOwner()->GetScale().y / 4.f));
			m_faceAttack->SetPos(Vec2(GetFinalPos().x, GetFinalPos().y));
		}
			break;
		case ATTACK_PATT::PATT2:
		{

			SetPos(Vec2(-GetOwner()->GetScale().x / 2.f, GetOwner()->GetScale().y / 4.f));
			m_faceAttack->SetPos(Vec2(GetFinalPos().x, GetFinalPos().y));
		}
			break;
		default:
			break;
		}
	}
	switch (m_currnetPatt)
	{
	case ATTACK_PATT::PATT1:
	{
		
		m_faceAttack->GetCollider()->SetAvaCollide(true);
	}
		break;
	case ATTACK_PATT::PATT2:
	{
		
		m_faceAttack->GetCollider()->SetAvaCollide(true);
	}
		break;
	case ATTACK_PATT::PATT3:
	{
		SetPos(Vec2(-GetOwner()->GetScale().x/2.f-200.f,-50.f+(m_seedBulletCount*50.f)));
		bullet = new CSeedBullet;
		cloneBullet = ((CSeedBullet*)bullet)->Clone();
		cloneBullet->SetPos(Vec2(GetFinalPos().x, GetFinalPos().y));
		cloneBullet->Start();
		CreateObject(cloneBullet, GROUP_TYPE::MONSTER_BULLET);
		++m_seedBulletCount;
		if (m_seedBulletCount >= 1)
		{
			m_seedBulletCount = 0;
		}
	}
		break;
	case ATTACK_PATT::PATT4:
	{
		bullet = new CMonSeedBullet;
		cloneBullet = ((CMonSeedBullet*)bullet)->Clone();
		cloneBullet->SetPos(Vec2(setXPos(), -100));
		cloneBullet->Start();
		CreateObject(cloneBullet, GROUP_TYPE::MONSTER_BULLET);
	}
		break;
	default:
		break;
	}
}

void CCagneyAttackBox::ChangeAttack()
{


}

int CCagneyAttackBox::setXPos()
{
	float scaleX = GetOwner()->GetScale().x;
	float resolutionX = 1280;
	float dist = resolutionX - scaleX;

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution <int> dis(100, dist);

	return dis(gen);
}
