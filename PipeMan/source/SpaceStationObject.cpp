#include "SpaceStationObject.h"
#include "PipeObject.h"

CSpaceStation::CSpaceStation()
{
	Initialize();
}

CSpaceStation::~CSpaceStation()
{
	Shutdown();
}

void CSpaceStation::Initialize()
{
	m_nNumRepairBots = 0;
	m_nFuelFillRate = 0;
	m_nObjectID = -1;
	m_nSoundID = -1;

	/************************************************************************/
	/*			Width Width Width                                           */
	/* Height		                                                        */
	/* Height                                                               */
	/************************************************************************/
	for (int height = 0; height < STATION_HEIGHT; ++height)
	{
		for (int width = 0; width < STATION_WIDTH; ++width)
		{
			m_pStationPorts[height][width] = new CPipeObject();
			m_pStationPorts[height][width]->SetObjectID(CBaseObject::END);
		}
	}
}

void CSpaceStation::Shutdown()
{
	for (int height = 0; height < STATION_HEIGHT; ++height)
	{
		for (int width = 0; width < STATION_WIDTH; ++width)
		{
			delete m_pStationPorts[height][width];
			m_pStationPorts[height][width] = NULL;
		}
	}
}

void CSpaceStation::Render()
{

}

void CSpaceStation::Render_Debug()
{

}

void CSpaceStation::Update(float fElapsedTime)
{

}

void CSpaceStation::HandleCollision(CBaseObject* pObject)
{

}