#include "CharacterObject.h"
#include <iostream>

CCharacterObject::CCharacterObject()
{
	m_fRotSpeed = 3.00f;
	m_fCurSpeed = 150.0f;
	m_fMaxSpeed = 150.0f;
	m_fAcceleration = 45.0f;

	m_fHealth = 0;
	m_fFuel = 0;
	m_nPatiencelvl = 0;
	m_vTargetPosition = CVector2f(0, 0);
	m_vDirection = CVector2f(1, 0);
	m_fpMove = &CCharacterObject::Accelerate;
	m_vCenter = CVector2f(0.0f, 0.0f);
}

CCharacterObject::CCharacterObject(ShipType type, CVector2f vTargetPosition)
{	
	m_eType = type;
	// Choose starting position
	switch(rand() % TOTAL)
	{
		case LEFT:
			StartLeft();
			break;
		case RIGHT:
			StartRight();
			break;
		case TOP:
			StartTop();
			break;
		case BOTTOM:
			StartBottom();
			break;
		default:
			break;
	}
	
	m_vTargetPosition = vTargetPosition;
	m_vDirection = (vTargetPosition - m_vPosition).Normalize();
	m_fCurSpeed = m_fMaxSpeed;
	m_fpMove = &CCharacterObject::Coast;
}

CCharacterObject::~CCharacterObject()
{

}

void CCharacterObject::Initialize()
{

}

void CCharacterObject::Render()
{

}

void CCharacterObject::Update(float fElapsedTime)
{
	// Target position - ship position
	CVector2f targetNormal = m_vTargetPosition - (m_vPosition + m_vCenter);
	// Normalize
	targetNormal = targetNormal.Normalize();
	// Ship normal dot normalized
	float angle = m_vDirection.AngleDegs(targetNormal);
	if (angle < -0.000001 || angle > 0.000001)
	{
		// Dot the ships axes with the target normal
		float rotDirection = m_vDirection.Cross().Dot(targetNormal);
		// Calculate the rotation amount
		float rotAmount = m_fRotSpeed * fElapsedTime;
		
		if (rotDirection > 0)
		{
			rotAmount = -rotAmount;
		}

		// Rotate the ships new direction
		m_vDirection = m_vDirection.Rotate(rotAmount);
		m_fRotAmount += rotAmount;
	}
	else
	{
		// Since were facing the target just turn towards it
		m_vDirection = (m_vTargetPosition - m_vPosition).Normalize();
	}
	// Update the ships position
	m_vPosition = m_vDirection * m_fCurSpeed * fElapsedTime + m_vPosition;
	// Update based on movement function
	(this->*m_fpMove)(fElapsedTime);
}

void CCharacterObject::HandleCollision(CBaseObject* pObject)
{

}

void CCharacterObject::Accelerate(float fTime)
{
	m_fCurSpeed += m_fAcceleration * fTime;
	if (m_fCurSpeed >= m_fMaxSpeed)
	{
		m_fCurSpeed = m_fMaxSpeed;
		m_fpMove = &CCharacterObject::Coast;
	}
}

void CCharacterObject::Coast(float fTime)
{
	float fDistance = (m_vTargetPosition - m_vPosition).Norm();
	float totalTime = m_fMaxSpeed / m_fAcceleration;
	if (fDistance <= (m_fMaxSpeed * totalTime - 0.5f * m_fAcceleration * totalTime * totalTime))
	{
		m_fpMove = &CCharacterObject::Deccelerate;
	}
}

void CCharacterObject::Deccelerate(float fTime)
{
	m_fCurSpeed -= m_fAcceleration * fTime;

	if (m_fCurSpeed <= 0.0f)
	{
		m_vPosition = m_vTargetPosition;
		m_fpMove = &CCharacterObject::Stop;
	}
}

void CCharacterObject::Stop(float fTime)
{

}

void CCharacterObject::StartLeft()
{
	float x = RAND_FLOAT(-100, -50);
	float y = RAND_FLOAT(-100, 868);
	m_vPosition = CVector2f(x, y);
}

void CCharacterObject::StartRight()
{
	float x = RAND_FLOAT(1074, 1124);
	float y = RAND_FLOAT(-100, 868);
	m_vPosition = CVector2f(x, y);
}

void CCharacterObject::StartTop()
{
	float x = RAND_FLOAT(-100, 1124);
	float y = RAND_FLOAT(-100, -50);
	m_vPosition = CVector2f(x, y);
}

void CCharacterObject::StartBottom()
{
	float x = RAND_FLOAT(-100, 1124);
	float y = RAND_FLOAT(868, 918);
	m_vPosition = CVector2f(x, y);
}