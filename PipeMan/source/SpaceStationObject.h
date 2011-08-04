/***********************************************
 * Filename:  		SpaceStationObject.h
 * Date:      		1/4/2011
 * Mod. Date: 		1/4/2011
 * Mod. Initials:	AD
 * Author:    		Anthony De La Rosa
 * Purpose:   		Base class from which all game 
 *					objects will inherit
 ************************************************/
#ifndef _SPACESTATION_H_
#define _SPACESTATION_H_

#include "BaseObject.h"

class CPipeObject;

#define STATION_WIDTH 3
#define STATION_HEIGHT 2

class CSpaceStation : public CBaseObject
{
protected:
	CPipeObject * m_pStationPorts[STATION_WIDTH][STATION_HEIGHT];
	float m_nFuelFillRate;
	float m_nRepairRate;
	int m_nNumRepairBots;

public:
	CSpaceStation();
	~CSpaceStation();

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
	* Shutdown():			Clear all initialized data
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
	* Render_Debug():	Used for rendering debug information about the
	*					specific object, this peice of code will only be 
	*					run if the game is in debug mode.
	*
	* Ins:					None
	*      		      
	*
	* Outs:					None
	*
	* Returns:				Void
	*****************************************************************/
	void Render_Debug();

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
	* HandleCollision():  Handles the collision response 
	*
	* Ins:					pObject
	*      		      
	*
	* Outs:					None
	*
	* Returns:				Void
	*****************************************************************/
	void HandleCollision(CBaseObject* pObject);

	/*****************************************************************
	 *  Accessors
	 *****************************************************************/
	inline const int GetHeight()				const { return STATION_HEIGHT; }
	inline const int GetWidth()					const { return STATION_WIDTH; }
	inline const float GetFuelRate()			const { return m_nFuelFillRate; }
	inline const float GetRepairRate()			const { return m_nRepairRate; }
	inline const int   GetNumberofRepairBots()	const { return m_nNumRepairBots; }
	inline CPipeObject* GetPort(int row, int col)	  { return m_pStationPorts[col][row]; }

	/*****************************************************************
	 * Mutators
	 *****************************************************************/
	inline void SetFuelRate(float nFuelRate)			{ m_nFuelFillRate = nFuelRate; }
	inline void SetRepairRate(float nRepairRate)		{ m_nRepairRate = nRepairRate; }
	inline void SetNumberofRepairBots(int nRepairBots)	{ m_nNumRepairBots = nRepairBots; }
	inline void SetPort(CPipeObject* port, int col, int row) { m_pStationPorts[col][row] = port; }
};
#endif