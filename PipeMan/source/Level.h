/***********************************************
 * Filename:  		Level.h
 * Date:      		1/5/2011
 * Mod. Date: 		1/5/2011
 * Mod. Initials:	AD
 * Author:    		Anthony De La Rosa
 * Purpose:   		The "Game Board"
 ************************************************/
#ifndef _LEVEL_H_
#define _LEVEL_H_

#include "SpaceStationObject.h"
#include "PipeObject.h"
#include <list>
using std::list;

class CLevel
{
protected:
	list<CPipeObject> m_lUpcomingPipes;
	CSpaceStation* m_pSpaceStation;
	CLevel* m_pthis;
	//CMoralBar m_pMoralBar
	CBaseObject* m_pLevelObjects[1][1];
	float m_fTimeRemaining;

private:
	CLevel();
	CLevel(const CLevel&);
	CLevel& operator=(const CLevel&);
public:
	~CLevel();

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
	void Initialize();

	/*****************************************************************
	* CalculatePath():		Calculates the path of the Pipes that are	
	*						being placed.
	*
	* Ins:					CBaseObject* - ???
	*      		      
	*
	* Outs:					None
	*
	* Returns:				Void
	*****************************************************************/
	void CalculatePath();

	/*****************************************************************
	* GetInstance():		Returns the Instance of this object	
	*						
	*
	* Ins:					None
	* 
	*
	* Outs:					None
	*
	* Returns:				Void
	*****************************************************************/
	static CLevel& GetInstance() {static CLevel singleton; return singleton;}

	/*****************************************************************
	* CleanUp():			DeAllocaties any remaining allocated Memory	
	*						
	*
	* Ins:					None
	* 
	*
	* Outs:					None
	*
	* Returns:				Void
	*****************************************************************/
	void CleanUp();

	/*****************************************************************
	* Shutdown():			???	
	*						
	*
	* Ins:					None
	* 
	*
	* Outs:					None
	*
	* Returns:				Void
	*****************************************************************/
	void Shutdown();

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
	void Update(float fElapsedTime);

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
	void Render();

	/*****************************************************************
	* LoadLevel():  Used for special case rendering of our game objects
	*			 For instance drawing the laser beam of our weapon.
	*
	* Ins:					char* - filename of level you wish to load
	*      		      
	*
	* Outs:					None
	*
	* Returns:				Void
	*****************************************************************/
	void LoadLevel();

	/*****************************************************************
	 *  Accessors
	 *****************************************************************/
	const float GetTimeRemaining() const { return m_fTimeRemaining; }

	/*****************************************************************
	 * Mutators
	 *****************************************************************/
	void SetTimeRemaining(float fTimeRemaining) { m_fTimeRemaining = fTimeRemaining; }
};

#endif