#include "MENU_Base.h"
#include "MENU_BaseObject.h"

MENU_Base::MENU_Base( void )
{
	m_vMenuObjects= NULL;
}

MENU_Base::~MENU_Base( void )
{
	while ( m_vMenuObjects->size() )
		RemoveObject(0);

	delete m_vMenuObjects;
	m_vMenuObjects= NULL;
}

void MENU_Base::Init( void )
{
	m_vMenuObjects= new vector<MENU_BaseObject*>();
}

void MENU_Base::Update( float fTime )
{
	for (unsigned int unCurrent= 0; unCurrent < m_vMenuObjects->size(); ++unCurrent)
		((*m_vMenuObjects)[unCurrent])->Update(fTime);
}

void MENU_Base::Render( void )
{
	for (unsigned int unCurrent= 0; unCurrent < m_vMenuObjects->size(); ++unCurrent)
		((*m_vMenuObjects)[unCurrent])->Render();	
}

void MENU_Base::AddObject( MENU_BaseObject* pObject )
{
	if (!pObject)
		return;

	m_vMenuObjects->push_back(pObject);
}

void MENU_Base::RemoveObject( int nIndex )
{
	if (nIndex >= int(m_vMenuObjects->size()))
		return;

	delete (*m_vMenuObjects)[nIndex];
	m_vMenuObjects->erase(m_vMenuObjects->begin() + nIndex);
}

void MENU_Base::RemoveObject( MENU_BaseObject* pObject )
{
	for (unsigned int unCurrent= 0; unCurrent < m_vMenuObjects->size(); ++unCurrent)
		if (pObject == (*m_vMenuObjects)[unCurrent])
		{
			RemoveObject(unCurrent);
			break;
		}
}

int MENU_Base::FindObject( MENU_BaseObject* pObject )
{
	for (unsigned int unCurrent= 0; unCurrent < m_vMenuObjects->size(); ++unCurrent)
		if (pObject == (*m_vMenuObjects)[unCurrent])
			return unCurrent;

	return -1;
}

bool MENU_Base::ObjectExists( MENU_BaseObject* pObject )
{
	if (FindObject(pObject) >= 0)
		return true;
	else
		return false;
}

void MENU_Base::DisplayDialogBox( LPSTR szText, DialogType eDialogType/*= DR_DECISION*/, bool bAutoScaling/*= true*/, void (*pFunc)(void)/*= NULL*/ )
{

}
