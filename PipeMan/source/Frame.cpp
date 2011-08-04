////////////////////////////////////////////////////////////////////////////////////////////////////
// File:		Frame.cpp
// Author:		Samuel Ratledge Jr.
// Date:		December 13, 2010
// Purpose:		The basic class for each frame.
// Revisions:	(Add Date Revised)
////////////////////////////////////////////////////////////////////////////////////////////////////
#include "Frame.h"


CFrame::CFrame( void )
{
	m_arrCollisionData.clear();
	memset(&m_rDimensions, NULL, sizeof(CRect));
	memset(&m_AnchorData, NULL, sizeof(tAnchorData));
	m_nIndex	 = 0;
	m_fTimeDelay = 0.0f;
}

CFrame::~CFrame( void )
{
	int const nSize = m_arrCollisionData.size();
	for(int nIndex = 0; nIndex < nSize; ++nIndex)
		m_arrCollisionData[nIndex]->ClearList();
}

void CFrame::SetAnchorData( bool const _bHasAnchor, int const _nX, int const _nY )
{
	m_AnchorData.bHasAnchor = _bHasAnchor;
	m_AnchorData.nX = _nX;
	m_AnchorData.nY = _nY;
}

void CFrame::AddCollisionData( tCollisionData * _pData )
{
	m_arrCollisionData.push_back(_pData);
}

bool CFrame::CheckCollision( CRect const _rRect )
{
	int const nNumRects = m_arrCollisionData.size();
	for(int nIndex = 0; nIndex < nNumRects; ++nIndex)
	{
		CRect temp = m_arrCollisionData[nIndex]->rCollision;

		// TODO: Finish function

	}

	return false;
}