#include <Windows.h>
#include "SaveInfo.h"
#include <fstream>

using std::fstream;
using std::ios;

#define NULL 0

CSaveInfo* CSaveInfo::m_pInstance = NULL;

CSaveInfo::CSaveInfo()
{

	#ifdef _DEBUG
		m_bWindowed = true;
	#else
		m_bWindowed = false;
	#endif

	m_bVSync = false;
	m_nScreenWidth = 1024;
	m_nScreenHeight = 768;
	m_nNextLevel= 0;
	m_pInstance= NULL;
	m_nPlayerMoney= 0;
}

CSaveInfo::~CSaveInfo()
{

}

//////////////////////////////////////////////////////////////////////////
// GetInstance():		Gets the static instance of the saved information
//						returning a pointer to the instance
//
// Return:				CSaveInfo*
//////////////////////////////////////////////////////////////////////////
CSaveInfo* CSaveInfo::GetInstance()
{
	return m_pInstance;
}

//////////////////////////////////////////////////////////////////////////
//	DeleteInstance():	Deletes the instance of the save info
//
//	Return:				void
//////////////////////////////////////////////////////////////////////////
void CSaveInfo::DeleteInstance()
{
	Save();

	if ( m_pInstance )
	{
		delete m_pInstance;
		m_pInstance = NULL;
	}
}

//////////////////////////////////////////////////////////////////////////
// Initialize():		Inits the save info.  Reading information in
//						from a file
//
// Return:				CSaveInfo*
//////////////////////////////////////////////////////////////////////////
CSaveInfo* CSaveInfo::Initialize()
{
	if (!m_pInstance)
		m_pInstance = new CSaveInfo();

	m_pInstance->Load();
	return m_pInstance;
}

//////////////////////////////////////////////////////////////////////////
// Save():				Saves all information about the game
//
// Return:				void
//////////////////////////////////////////////////////////////////////////
void CSaveInfo::Save()
{
	fstream fileoutput("save.bin", ios::out | ios::trunc | ios::binary);

	if (fileoutput.is_open() && fileoutput.good() )
	{
		fileoutput.write((char*)&m_nNextLevel, sizeof(m_nNextLevel));
		fileoutput.write((char*)&m_nPlayerMoney, sizeof(m_nPlayerMoney));
	}

	fileoutput.close();
}

//////////////////////////////////////////////////////////////////////////
// Load():				Loads all information about the game from a
//						save file
//
// Return:				void
//////////////////////////////////////////////////////////////////////////
void CSaveInfo::Load()
{
	fstream fileinput("save.bin",  ios::in | ios::binary);

	if ( fileinput.is_open() && fileinput.good() )
	{
		fileinput.read((char*)&m_nNextLevel, sizeof(m_nNextLevel));
		fileinput.read((char*)&m_nPlayerMoney, sizeof(m_nPlayerMoney));
	}

	fileinput.close();
}