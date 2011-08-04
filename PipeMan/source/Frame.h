////////////////////////////////////////////////////////////////////////////////////////////////////
// File:		Frame.h
// Author:		Samuel Ratledge Jr.
// Date:		December 13, 2010
// Purpose:		The basic class for each frame.
// Revisions:	(Add Date Revised)
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _FRAME_H_
#define _FRAME_H_

// Header Files
#include <Windows.h>
#include <WinDef.h>
#include <D3dx9math.h>
#include <d3d9types.h>
#include <vector>
using std::vector;

#include "Rect.h"

// Forward Declaration
class CTexture;


class CFrame
{
private:	// Private Structures
	struct tAnchorData
	{
		bool bHasAnchor;
		int  nX;
		int  nY;

		tAnchorData( void )
		{
			bHasAnchor = false;
			nX = -1;
			nY = -1;
		}
	};

public:		// Public Structures
	struct tCollisionData
	{
		bool			bHasCollision;
		CRect			rCollision;
		vector<char*>	arrTriggers;

		tCollisionData(void)
		{
			bHasCollision = false;
			memset(&rCollision, NULL, sizeof(CRect));
			arrTriggers.clear();
		}

		~tCollisionData(void)
		{
			ClearList();
		}

		void SetRect(bool const _bHasRect, CRect const _rRect)
		{
			bHasCollision = _bHasRect;
			memcpy(&rCollision, &_rRect, sizeof(CRect));
		}

		void AddTrigger(char const * _szTrigger)
		{
			if(NULL != _szTrigger)
			{
				int nLength = strlen(_szTrigger)+1;
				char * szTrigger = new char[nLength];
				strcpy_s(szTrigger, nLength, _szTrigger);
				arrTriggers.push_back(szTrigger);
			}
		}

		void ClearList(void)
		{
			int const nSize = arrTriggers.size();
			for(int nIndex = 0; nIndex < nSize; ++nIndex)
				delete[] arrTriggers[nIndex];

			arrTriggers.clear();
		}
	};

private:	// Private Data
	vector<tCollisionData*>	m_arrCollisionData;
	CRect					m_rDimensions;
	tAnchorData				m_AnchorData;
	int						m_nIndex;
	float					m_fTimeDelay;

public:		// Accessors
	inline CRect GetRect(void) const { return m_rDimensions; }
	inline int GetIndex(void) const { return m_nIndex; }
	inline float GetTimeDelay(void) const { return m_fTimeDelay; }
	inline tAnchorData GetAnchorData(void) const { return m_AnchorData; }
	inline vector<tCollisionData*> & GetCollisionData(void) { return m_arrCollisionData; }

public:		// Mutators
	inline void SetIndex(int const _nIndex) { m_nIndex = _nIndex; }
	inline void SetTimeDelay(float const _fTime) { m_fTimeDelay = _fTime; }
	inline void SetRect(CRect const _rDimensions)
		{ memcpy(&m_rDimensions, &_rDimensions, sizeof(CRect)); }

public:		// Public Functions
	CFrame(void);
	~CFrame(void);

	////////////////////////////////////////////////////////////////////////////////////////////////
	// Function:		SetAnchorData
	// Parameter(s):	bool const _bHasAnchor	- Specifies whether this frame has an anchor
	//					int const _nX			- Position along the x-axis
	//					int const _nY			- Position along the y-axis
	// Return:			void
	// Purpose:			Essentially an accessor; set the anchor position.
	////////////////////////////////////////////////////////////////////////////////////////////////
	void SetAnchorData(bool const _bHasAnchor, int const _nX, int const _nY);

	////////////////////////////////////////////////////////////////////////////////////////////////
	// Function:		AddCollisionRect
	// Parameter(s):	tCollisionData * _pData	- Collision Data for this frame
	// Return:			void
	// Purpose:			Appends tCollisionData which contains all the data for each collision rect.
	////////////////////////////////////////////////////////////////////////////////////////////////
	void AddCollisionData(tCollisionData * _pData);

	////////////////////////////////////////////////////////////////////////////////////////////////
	// Function:		CheckCollision
	// Parameter(s):	CRect const _rRect		- Rect to check against
	// Return:			bool			Returns true is there is collision, false otherwise
	// Purpose:			Checks for collision against all the rects for this frame.
	////////////////////////////////////////////////////////////////////////////////////////////////
	bool CheckCollision(CRect const _rRect);
};

#endif