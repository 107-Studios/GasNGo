/***********************************************
 * Filename:  		BaseObject.cpp
 * Date:      		3/16/2010
 * Mod. Date: 		3/20/2010
 * Mod. Initials:	RC
 * Author:    		Ricky Crane
 * Purpose:   		Base class from which all game 
 *						objects will inherit
 *			
 ************************************************/
#include "BaseObject.h"
#define NULL 0

CBaseObject::CBaseObject()
{
	m_pTexture = NULL;
	m_rDrawRect = CRect(0, 0, 0, 0);
	m_vPosition = CVector2f(0.0f, 0.0f);
	m_vScale = CVector2f(0.0f, 0.0f);
	m_dwColor = 0xFFFFFFFF;
	m_vCenter = CVector2f(0.0f, 0.0f);
	m_fRotAmount = 0.0f;
	m_nSoundID = -1;
	m_nObjectID = EMPTY;
	m_bReplaceable = false;
}

CBaseObject::~CBaseObject()
{
	m_pTexture = NULL;
}

//set all your values to defaults here, also allocate any mem for the class.
void CBaseObject::Initialize()
{

}

//clear what you did in init in here
void CBaseObject::Shutdown()
{

}

void CBaseObject::Update(float fElapsedTime)
{
	
}

void CBaseObject::Render()
{

}

void CBaseObject::HandleCollision(CBaseObject* pObject)
{

}