#include "AircraftCarrier.h"

CAircraftCarrier::CAircraftCarrier()
{
	Initialize();
}

CAircraftCarrier::CAircraftCarrier(CVector2f vTarget) : CCharacterObject(AIRCRAFT_CARRIER, vTarget)
{
	Initialize();
}

CAircraftCarrier::~CAircraftCarrier()
{

}

void CAircraftCarrier::Initialize()
{
	m_fRotSpeed = 3.00f;
	m_fMaxSpeed = 150.0f;
	m_fAcceleration = 45.0f;
	m_fHealth = 0;
	m_fFuel = 0;
	m_nPatiencelvl = 0;
	m_vCenter = CVector2f(0.0f, 0.0f);

	m_pPipes[0][0] = new CPipeObject(END_PIPE);
	m_pPipes[0][1] = new CPipeObject(END_PIPE);
	m_pPipes[0][2] = new CPipeObject(END_PIPE);
	m_pPipes[1][0] = new CPipeObject(END_PIPE);
	m_pPipes[1][1] = new CPipeObject(END_PIPE);
	m_pPipes[1][2] = new CPipeObject(END_PIPE);

	m_pPipes[0][0]->SetConnector(0, 0);
	m_pPipes[0][1]->SetConnector(0, 0);
	m_pPipes[1][0]->SetConnector(2, 2);
	m_pPipes[1][1]->SetConnector(2, 2);
}

void CAircraftCarrier::Render()
{

}

void CAircraftCarrier::Update(float fElapsedTime)
{
	CCharacterObject::Update(fElapsedTime);
}

void CAircraftCarrier::HandleCollision(CBaseObject* pObject)
{

}