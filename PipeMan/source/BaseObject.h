/***********************************************
 * Filename:  		BaseObject.h
 * Date:      		7/21/2010
 * Mod. Date: 		7/21/2010
 * Mod. Initials:	BK
 * Author:    		Brian Kelsey
 * Purpose:   		Base class from which all game 
 *					objects will inherit
 ************************************************/
#ifndef _BASEOBJECT_H_
#define _BASEOBJECT_H_

#define RAND_FLOAT(min, max) ((float)rand() / (float)RAND_MAX * ((float)max - (float)min + 1) + (float)min)

#include "Vector2f.h"
#include "Rect.h"

class CTexture;

class CBaseObject
{
public:
	enum Type { EMPTY = 0, ASTEROID, PIPE, TOTAL };

protected:
	CTexture*	m_pTexture;
	CRect		m_rDrawRect;
	CVector2f	m_vPosition;
	CVector2f	m_vScale;
	DWORD		m_dwColor;
	CVector2f	m_vCenter;
	float		m_fRotAmount;
	int			m_nSoundID;
	int			m_nObjectID;
	bool		m_bReplaceable;
	
public:
	CBaseObject(void);
	virtual ~CBaseObject(void);

	/*****************************************************************
	* Initialize():			Sets all values to defaults here, also 
	*						allocate any mem for the class.
	*
	* Ins:					None
	*      		      
	*
	* Outs:					None
	*
	* Returns:				Void
	*****************************************************************/
	virtual void Initialize();

	/*****************************************************************
	* Shutdown():			Clear all initialized data
	*
	* Ins:					None
	*      		      
	*
	* Outs:					None
	*
	* Returns:				Void
	*****************************************************************/
	virtual void Shutdown();

	/*****************************************************************
	* Render():  Used for special case rendering of our game objects
	*			 For instance drawing the laser beam of our weapon.
	*
	* Ins:					None
	*      		      
	*
	* Outs:					None
	*
	* Returns:				Void
	*****************************************************************/
	virtual void Render();

	/*****************************************************************
	* Update():  Handles all changes over time for the object.
	*
	* Ins:					fElapsedTime
	*      		      
	*
	* Outs:					None
	*
	* Returns:				Void
	*****************************************************************/
	virtual void Update(float fElapsedTime);

	/*****************************************************************
	* HandleCollision():  Handles the collision response 
	*
	* Ins:					pObject
	*      		      
	*
	* Outs:					None
	*
	* Returns:				Void
	*****************************************************************/
	virtual void HandleCollision(CBaseObject* pObject);

	/*****************************************************************
	 *  Accessors
	 *****************************************************************/
	inline const CVector2f GetPosition() const		{ return m_vPosition; }
	inline const float GetPosX() const				{ return m_vPosition.GetX(); }
	inline const float GetPosY() const				{ return m_vPosition.GetY(); }
	inline const CRect GetDrawRect() const			{ return m_rDrawRect; }
	inline const long GetRectX() const				{ return m_rDrawRect.m_nX; }
	inline const long GetRectY() const				{ return m_rDrawRect.m_nY; }
	inline const long GetWidth() const				{ return m_rDrawRect.m_nWidth; }
	inline const long GetHeight() const				{ return m_rDrawRect.m_nHeight; }
	inline const CTexture* GetImageID() const		{ return m_pTexture; }
	inline const CVector2f GetScale() const			{ return m_vScale; }
	inline const float GetScaleX() const			{ return m_vScale.GetX(); }
	inline const float GetScaleY() const			{ return m_vScale.GetY(); }
	inline const DWORD GetColor() const				{ return m_dwColor; }
	inline const CVector2f GetCenter() const		{ return m_vCenter; }
	inline const float GetCenterX() const			{ return m_vCenter.GetX(); }
	inline const float GetCenterY() const			{ return m_vCenter.GetY(); }
	inline const float GetRotation() const			{ return m_fRotAmount; }
	inline const int GetSoundID() const				{ return m_nSoundID; }
	inline const int GetObjectID() const			{ return m_nObjectID; }
	inline const bool GetIsReplaceable() const		{ return m_bReplaceable; }

	/*****************************************************************
	 * Mutators
	 *****************************************************************/
	inline void SetPosition(CVector2f xv)			{ m_vPosition = xv; }
	inline void SetPosX(float fPosX)				{ m_vPosition.SetX(fPosX); }
	inline void SetPosY(float fPosY)				{ m_vPosition.SetY(fPosY); }
	inline void SetDrawRect(CRect rect)				{ m_rDrawRect = rect; }
	inline void SetRectX(long lx)					{ m_rDrawRect.m_nX = lx; }
	inline void SetRectY(long ly)					{ m_rDrawRect.m_nY = ly; }
	inline void SetWidth(long lWidth)				{ m_rDrawRect.m_nWidth = lWidth; }
	inline void SetHeight(long lHeight)				{ m_rDrawRect.m_nHeight = lHeight; }
	inline void SetImageID(CTexture* pTexture)		{ m_pTexture = pTexture; }
	inline void SetScale(CVector2f xvScale)			{ m_vScale = xvScale; }
	inline void SetScaleX(float fX)					{ m_vScale.SetX(fX); }
	inline void SetScaleY(float fY)					{ m_vScale.SetY(fY); }
	inline void SetColor(DWORD dwColor)				{ m_dwColor = dwColor; }
	inline void SetCenter(CVector2f xvCenter)		{ m_vCenter = xvCenter; }
	inline void SetCenterX(float fX)				{ m_vCenter.SetX(fX); }
	inline void SetCenterY(float fY)				{ m_vCenter.SetY(fY); }
	inline void SetRotation(float fRot)				{ m_fRotAmount = fRot; }
	inline void SetSoundID(int nID)					{ m_nSoundID = nID; }
	inline void SetObjectID(int nID)				{ m_nObjectID = nID; }
	inline void SetIsReplaceable(bool bReplace)		{ m_bReplaceable = bReplace; }
};
#endif 
