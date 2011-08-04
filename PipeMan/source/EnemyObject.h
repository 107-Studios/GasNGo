#ifndef _ENEMYOBJECT_H
#define _ENEMYOBJECT_H

#include "BaseObject.h"

class CEnemyObject : public CBaseObject
{
protected:
	int		m_nLevel;
	int		m_nAffectedAreas;

public:

	CEnemyObject();
	~CEnemyObject();

	// accessors
	int Level( void ) { return m_nLevel; }
	int AffectedAreas( void ) { return m_nAffectedAreas; }

	// mutators
	void Level( int nLevel ) { m_nLevel= nLevel; }
	void AffectedAreas( int nAffecetedAreas ) { m_nAffectedAreas= nAffecetedAreas; }

	void Update(float fElapsedTime);
};
#endif