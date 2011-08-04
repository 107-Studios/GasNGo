/***********************************************
 * Filename:  		CharacterObject.h
 * Date:      		1/4/2011
 * Mod. Date: 		1/4/2011
 * Mod. Initials:	AD
 * Author:    		Anthony De La Rosa
 * Purpose:   		Base class from which all game 
 *					objects will inherit
 ************************************************/
#ifndef _CHARACTEROBJECT_H_
#define _CHARACTEROBJECT_H_

#include "PipeObject.h"
#include "Vector2f.h"
#include "RectangleF.h"


enum ShipType { FRIGATE = 0, DESTROYER, BATTLE_CRUISER, WARSHIP, AIRCRAFT_CARRIER};

class CCharacterObject : public CBaseObject
{
protected:
	enum StartPosition {LEFT = 0, RIGHT, TOP, BOTTOM, TOTAL};
	CVector2f m_vDirection;
	CVector2f m_vTargetPosition;
	CPipeObject** m_pPipes;
	float m_fCurSpeed;
	float m_fMaxSpeed;
	float m_fAcceleration;
	float m_fRotSpeed;
	float m_fHealth;
	float m_fFuel;
	int m_nPatiencelvl;
	ShipType m_eType;

protected:
	typedef void (CCharacterObject::*FuncPointer)(float);
	FuncPointer m_fpMove;

public:
	CCharacterObject();
	CCharacterObject(ShipType, CVector2f);
	~CCharacterObject();
	
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
	inline const float GetHealth() const			{ return m_fHealth; }
	inline const float GetFuel() const				{ return m_fFuel; }
	inline const int GetPatienceLevel() const		{ return m_nPatiencelvl; }
	inline const CVector2f GetDirection() const		{ return m_vDirection; }
	inline const CVector2f GetTarget() const		{ return m_vTargetPosition; }

	/*****************************************************************
	 * Mutators
	 *****************************************************************/
	inline void SetHealth(float fHealth)			{ m_fHealth = fHealth; }
	inline void SetFuel(float fFuel)				{ m_fFuel = fFuel; }
	inline void SetPatienceLevel(int nPatience)		{ m_nPatiencelvl = nPatience; }
	inline void SetDirection(CVector2f vDirection)	{ m_vDirection = vDirection; }
	inline void SetTarget(CVector2f vTarget)		{ m_vTargetPosition = vTarget; }

protected:
	/*****************************************************************
	* Accelerate():			Increases the objects velocity until the
	*						maximum velocity is reached.
	*
	* Returns:				Void
	*****************************************************************/
	void Accelerate(float fTime);

	/*****************************************************************
	* Coast():				Coasts at maximum speed until objects
	*						is within a certain distance of its target.
	*
	* Returns:				Void
	*****************************************************************/
	void Coast(float fTime);

	/*****************************************************************
	* Deccelerate():		Decreases the objects velocity as it reaches
	*						its target position
	*
	* Returns:				Void
	*****************************************************************/
	void Deccelerate(float fTime);

	/*****************************************************************
	* Stop():				Stops the object at the target position
	*
	* Returns:				Void
	*****************************************************************/
	void Stop(float fTime);

	void StartLeft();
	void StartRight();
	void StartTop();
	void StartBottom();
};

#endif