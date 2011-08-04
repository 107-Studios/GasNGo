////////////////////////////////////////////////////////////////////////////////////////////////////
// File:		Animation.cpp
// Author:		Samuel Ratledge Jr.
// Date:		December 08, 2010
// Purpose:		The classes needed to run by the animation manager.
// Revisions:	(Add Date Revised)
////////////////////////////////////////////////////////////////////////////////////////////////////
#include "Animation.h"


CAnimation::CAnimation( void )
{
	m_szName = NULL;
	m_fCurrentTime = 0.0f;
	m_nCurrentFrame = 0;
	m_arrFrames.clear();
}

CAnimation::~CAnimation( void )
{
	ClearName();
	ClearList();
}

void CAnimation::ClearName( void )
{
	if(m_szName)
	{
		delete[] m_szName;
		m_szName = NULL;
	}
}

void CAnimation::ClearList( void )
{
	int const nArraySize = m_arrFrames.size();
	for(int nIndex = 0; nIndex < nArraySize; ++nIndex)
		delete m_arrFrames[nIndex];

	m_arrFrames.clear();
}

void CAnimation::SetName( char const * _szName )
{
	if(_szName)
	{
		ClearName();
		int const nLength = strlen(_szName)+1;
		m_szName = new char[nLength];
		strcpy_s(m_szName, nLength, _szName);
	}
}

void CAnimation::AddFrame( CFrame * _pFrame )
{
	m_arrFrames.push_back(_pFrame);
}

void CAnimation::Update( float const _fTime )
{
	m_fCurrentTime += _fTime;

	if(m_fCurrentTime > m_arrFrames[m_nCurrentFrame]->GetTimeDelay())
	{
		m_fCurrentTime = 0.0f;

		if(++m_nCurrentFrame >= (int)m_arrFrames.size())
			m_nCurrentFrame = 0;
	}
}