#include "Warship.h"

CWarship::CWarship()
{
	Initialize();
}

CWarship::CWarship(CVector2f vTarget) : CCharacterObject(WARSHIP, vTarget)
{
	Initialize();
}

CWarship::~CWarship()
{

}

void CWarship::Initialize()
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
	m_pPipes[2] = new CPipeObject(END_PIPE);

	m_pPipes[0]->SetConnector(0, 0);
	m_pPipes[1]->SetConnector(0, 0);
}

void CWarship::Render()
{

}

void CWarship::Update(float fElapsedTime)
{
	CCharacterObject::Update(fElapsedTime);
}

void CWarship::HandleCollision(CBaseObject* pObject)
{

}