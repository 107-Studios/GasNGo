#ifndef _AIRCRAFTCARRIER_H_
#define _AIRCRAFTCARRIER_H_

#include "CharacterObject.h"

class CAircraftCarrier : public CCharacterObject
{
protected:
	CPipeObject* m_pPipes[2][3];

public:
	CAircraftCarrier();
	CAircraftCarrier(CVector2f);
	~CAircraftCarrier();
	
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
};

#endif