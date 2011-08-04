#include "Destroyer.h"

CDestroyer::CDestroyer()
{
	Initialize();
}

CDestroyer::CDestroyer(CVector2f vTarget) : CCharacterObject(DESTROYER, vTarget)
{
	Initialize();
}

CDestroyer::~CDestroyer()
{

}

void CDestroyer::Initialize()
{
	m_fRotSpeed = 3.00f;
	m_fMaxSpeed = 150.0f;
	m_fAcceleration = 45.0f;
	m_fHealth = 0;
	m_fFuel = 0;
	m_nPatiencelvl = 0;
	m_vCenter = CVector2f(0.0f, 0.0f);

	m_pPipes[0] = new CPipeObject(END_PIPE);
	m_pPipes[1] = new CPipeObject(END_PIPE);
	m_pPipes[0]->SetConnector(0, 0);
	m_pPipes[0]->SetConnector(2, 2);
}

void CDestroyer::Render()
{

}

void CDestroyer::Update(float fElapsedTime)
{
	CCharacterObject::Update(fElapsedTime);
}

void CDestroyer::HandleCollision(CBaseObject* pObject)
{

}