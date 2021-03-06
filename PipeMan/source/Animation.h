////////////////////////////////////////////////////////////////////////////////////////////////////
// File:		Animation.h
// Author:		Samuel Ratledge Jr.
// Date:		December 13, 2010
// Purpose:		The class that holds all animation data.
// Revisions:	(Add Date Revised)
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include "Frame.h"


class CAnimation
{
private:	// Private Data
	char *			m_szName;
	float			m_fCurrentTime;
	int				m_nCurrentFrame;
	vector<CFrame*>	m_arrFrames;

public:		// Accessors
	inline char * GetName(void) const			{ return m_szName; }
	inline int GetCurrentFrameIndex(void) const { return m_nCurrentFrame; }
	inline CFrame * GetCurrentFrame(void) const { return m_arrFrames[m_nCurrentFrame]; }
	inline vector<CFrame*> & GetFrames( void)	{ return m_arrFrames; }

public:		// Public Functions
	CAnimation(void);
	~CAnimation(void);

	////////////////////////////////////////////////////////////////////////////////////////////////
	// Function:		SetName
	// Parameter(s):	char const * _szName	- Sets the name of this animation
	// Return:			void
	// Purpose:			Essentially an accessor; sets the name of this animation.
	////////////////////////////////////////////////////////////////////////////////////////////////
	void SetName(char const * _szName);

	////////////////////////////////////////////////////////////////////////////////////////////////
	// Function:		AddFrame
	// Parameter(s):	CFrame * _pFrame		- Appends frame to list
	// Return:			void
	// Purpose:			Appends frame to list.
	////////////////////////////////////////////////////////////////////////////////////////////////
	void AddFrame(CFrame * _pFrame);

	////////////////////////////////////////////////////////////////////////////////////////////////
	// Function:		Update
	// Parameter(s):	float const _fTime		- Time since last update
	// Return:			void
	// Purpose:			Updates the current frame to the next frame in the list. Starts back at the
	//					front of the list if the current frame is the last one in the list.
	////////////////////////////////////////////////////////////////////////////////////////////////
	void Update(float const _fTime);

	////////////////////////////////////////////////////////////////////////////////////////////////
	// Function:		GetCurrentRect
	// Parameter(s):	void
	// Return:			CRect *
	// Purpose:			Returns the current frames rect for rendering.
	////////////////////////////////////////////////////////////////////////////////////////////////
	CRect * GetCurrentRect(void) const;

private:	// Private Functions
	////////////////////////////////////////////////////////////////////////////////////////////////
	// Function:		ClearName
	// Parameter(s):	void
	// Return:			void
	// Purpose:			Deletes any allocated memory for the name.
	////////////////////////////////////////////////////////////////////////////////////////////////
	void ClearName(void);

	////////////////////////////////////////////////////////////////////////////////////////////////
	// Function:		ClearList
	// Parameter(s):	void
	// Return:			void
	// Purpose:			Deletes any allocated memory for the list and clears the list.
	////////////////////////////////////////////////////////////////////////////////////////////////
	void ClearList(void);
};

#endif