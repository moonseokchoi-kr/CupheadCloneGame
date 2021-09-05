#include "pch.h"
#include "CMonsterDebugPanel.h"
#include "CMonster.h"
#include "CTextUI.h"
#include "FSMAI.h"
#include "CSlime.h"
#include "CSlimAttackState.h"
#include "CCarrotBossAttackBox.h"
#include "CCore.h"
#include "CKeyManager.h"
#include "SelectGDI.h"
CMonsterDebugPanel::CMonsterDebugPanel()
	:CPanelUI(false)
	,m_owner(nullptr)
{

	SetScale(Vec2(500.f, 150.f));
	m_currnetPatt = new CTextUI(false);
	m_currnetPatt->SetPos(Vec2(100.f, 70.f));
	AddChild(m_currnetPatt);
	m_monsterHP = new CTextUI(false);
	m_monsterHP->SetPos(Vec2(100.f, 40.f));
	AddChild(m_monsterHP);
	m_monsterName = new CTextUI(false);
	m_monsterName->SetPos(Vec2(100.f, 10.f));
	AddChild(m_monsterName);
	CTextUI* debugText = new CTextUI(false);
	debugText->SetPos(Vec2(100.f, 100.f));
	debugText->SetText(L"F1: SetDebug, F2: SetBossDead, F3: ChangePhase");
	AddChild(debugText);
	CTextUI* clone = debugText->Clone();
	clone->SetPos(Vec2(100.f, 130.f));
	clone->SetText(L"F5:SetInfinite F4: ChangePatt, F7: NextScene");
	AddChild(clone);
	
}

CMonsterDebugPanel::~CMonsterDebugPanel()
{
}

void CMonsterDebugPanel::Update()
{
	if (nullptr == m_owner)
		return;
	if (!CCore::GetInst()->IsDebug())
		return;
	m_monsterName->SetText(L"Monster Name : " + m_owner->GetName());
	m_monsterHP->SetText(L"HP : " + to_wstring(m_owner->GetInfo().hp));
	if (m_owner->GetName() == L"Potato" || m_owner->GetName() == L"Onion")
	{
		m_currnetPatt->SetText(L"AttackPatt: Patt1");
	}
	else if (m_owner->GetName() == L"Slime")
	{
		CSlimAttackState* attackState = nullptr;
		if (((CSlime*)m_owner)->GetAi()->GetCurrentState()->GetState() == MON_STATE::ATTACK)
			attackState = static_cast<CSlimAttackState*>(((CSlime*)m_owner)->GetAi()->GetCurrentState());
		else
		{
			return;
		}
		if (KEY_TAP(KEY::F4))
		{
			switch (((CSlime*)m_owner)->GetCurrentPhase())
			{
			case PHASE::PHASE1:
			{
				if (attackState->GetCurrentPatt() == ATTACK_PATT::PATT1)
				{
					attackState->SetCurrentPatt(ATTACK_PATT::PATT2);
				}
				else
				{
					attackState->SetCurrentPatt(ATTACK_PATT::PATT1);
				}
			}
			break;
			case PHASE::PHASE2:
			{
				if (attackState->GetCurrentPatt() == ATTACK_PATT::PATT3)
				{
					attackState->SetCurrentPatt(ATTACK_PATT::PATT4);
				}
				else
				{
					attackState->SetCurrentPatt(ATTACK_PATT::PATT3);
				}
			}
			break;
			default:
				break;
			}
		}
		switch (attackState->GetCurrentPatt())
		{
		case ATTACK_PATT::PATT1:
		{
			m_currnetPatt->SetText(L"AttackPatt: Phase1 Pattern 1" );
		}
		break;
		case ATTACK_PATT::PATT2:
		{
			m_currnetPatt->SetText(L"AttackPatt: Phase1 Pattern 2");
		}
		break;
		case ATTACK_PATT::PATT3:
		{
			m_currnetPatt->SetText(L"AttackPatt: Phase2 Pattern 1");
		}
		break;
		case ATTACK_PATT::PATT4:
		{
			m_currnetPatt->SetText(L"AttackPatt: Phase2 Pattern 2");
		}
		break;
		default:
			break;
		}

		
	}
	else if (m_owner->GetName() == L"Carrot")
	{
		CCarrotBossAttackBox* attackBox = nullptr;
		if (((CSlime*)m_owner)->GetAi()->GetCurrentState()->GetState() == MON_STATE::ATTACK)
			attackBox = static_cast<CCarrotBossAttackBox*>(m_owner->GetAttackBox());
		else
		{
			return;
		}
		if (KEY_TAP(KEY::F4))
		{
			attackBox->ChangeAttack();
		}
	
		switch (attackBox->GetCurrentPatt())
		{
		case ATTACK_PATT::PATT1:
		{
			m_currnetPatt->SetText(L"AttackPatt: Pattern 1");
		}
		break;
		case ATTACK_PATT::PATT2:
		{
			m_currnetPatt->SetText(L"AttackPatt: Pattern 2");
		}
		default:
			break;
		}
	}
}

void CMonsterDebugPanel::Render(HDC _dc)
{
	if (CCore::GetInst()->IsDebug())
	{
		for (CUI* cui : GetChilds())
		{
			cui->Render(_dc);
		}
	}
	
}
