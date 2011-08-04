#include "Frigate.h"

CFrigate::CFrigate()
{
	Initialize();
}

CFrigate::CFrigate(CVector2f vTarget) : CCharacterObject(FRIGATE, vTarget)
{
	Initialize();
}

CFrigate::~CFrigate()
{
	delete m_pPipes;
}

void CFrigate::Initialize()
{
	m_fRotSpeed = 3.00f;
	m_fMaxSpeed = 150.0f;
	m_fAcceleration = 45.0f;
	m_fHealth = 0;
	m_fFuel = 0;
	m_nPatiencelvl = 0;
	m_vCenter = CVector2f(0.0f, 0.0f);

	m_pPipes = new CPipeObject(END_PIPE);
	m_pPipes->SetConnector(0, 0);
}

void CFrigate::Render()
{

}

void CFrigate::Update(float fElapsedTime)
{
	CCharacterObject::Update(fElapsedTime);
}

void CFrigate::HandleCollision(CBaseObject* pObject)
{

}