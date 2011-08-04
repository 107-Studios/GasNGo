#include "PipeObject.h"

CPipeObject::CPipeObject()
{
	for (int i = 0; i < 4; i++)
		m_nConnectors[i] = -1;

	m_nFuelEntrance = -1;
	m_nPipeType = EMPTY_PIPE;
}

CPipeObject::CPipeObject( PipeID ePipe )
{
	for (int i = 0; i < 4; i++)
		m_nConnectors[i] = -1;

	m_nFuelEntrance = -1;
	m_nPipeType = ePipe;
}

CPipeObject::CPipeObject( PipeID ePipe, CTexture* pTexture)
{
	for (int i = 0; i < 4; i++)
		m_nConnectors[i] = -1;

	m_nFuelEntrance = -1;
	m_nPipeType = ePipe;

	SetImageID(pTexture);
}

CPipeObject::~CPipeObject()
{

}

void CPipeObject::Update(float fElapsedTime)
{

}

void CPipeObject::Render()
{

}

void CPipeObject::HandleCollision(CBaseObject* pObject)
{

}

void CPipeObject::FillPipe()
{

}