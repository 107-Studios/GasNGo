#ifndef _PIPEOBJECT_H_
#define _PIPEOBJECT_H_

#include "BaseObject.h"
#include "Texture.h"

enum PipeID {START_PIPE = -3, END_PIPE, EMPTY_PIPE, STRAIGHT = 0, CORNER, CROSS, T_PIPE, PIPE_TYPE_MAX};

class CPipeObject : public CBaseObject
{
protected:
	int		m_nConnectors[4];
	int		m_nFuelEntrance;
	PipeID	m_nPipeType;

public:
	CPipeObject();
	CPipeObject(PipeID);
	CPipeObject(PipeID, CTexture*);
	~CPipeObject();

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
	* FillPipe():			Fills the pipe with fuel.  
	*
	* Returns:				void
	*****************************************************************/
	virtual void FillPipe();

	/*****************************************************************
	 *  Accessors
	 *****************************************************************/
	inline const int GetConnector(int arrPos) const		{ return m_nConnectors[arrPos]; }
	inline const int GetPipeType() const				{ return m_nPipeType; }

	/*****************************************************************
	 * Mutators
	 *****************************************************************/
	inline void SetConnector(int arrPos, int conPos)		{ m_nConnectors[arrPos] = conPos; }
	inline void SetPipeType(PipeID type)					{ m_nPipeType = type; }
};

#endif