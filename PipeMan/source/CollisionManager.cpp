#include "CollisionManager.h"
#include "BaseObject.h"
#include "InputManager.h"

CCollisionManager* CCollisionManager::m_pInstance = NULL;

CCollisionManager* CCollisionManager::Initialize()
{
	if (m_pInstance == NULL)
		m_pInstance = new CCollisionManager();

	return m_pInstance;
}

void CCollisionManager::Shutdown()
{
	m_vObjectList.clear();
	if (m_pInstance)
		delete m_pInstance;

	m_pInstance = NULL;
}

void CCollisionManager::Update(const float fTime)
{

}

void CCollisionManager::Input()
{
	CInputManager* pInput = CInputManager::GetInstance();

	// If the left mouse button was clicked
	if (pInput->MouseClickedBuffered(0))
	{
		// Start at the end of the list to get the top most item that was clicked
		vector<CBaseObject*>::iterator iter = --m_vObjectList.end();
		POINT mousePos = pInput->GetCursorPosition();

		for(; *iter != NULL; --iter)
		{
			int x = (int)(*iter)->GetPosX();
			int y = (int)(*iter)->GetPosY();
			int width = x + (*iter)->GetWidth();
			int height = y + (*iter)->GetHeight();

			// Find the item that was clicked
			if (mousePos.x >= x && mousePos.x < width)
			{
				if (mousePos.y >= y && mousePos.y < height)
				{
					// Have it handle the collision with the mouse
					(*iter)->HandleCollision(NULL);
					break;
				}
			}
		}
	}
}

void CCollisionManager::RemoveObject(CBaseObject* pObject)
{
	//	Check for valid object pointer
	if (pObject == NULL)
		return;

	vector<CBaseObject*>::iterator iter = m_vObjectList.begin();

	for (;iter != m_vObjectList.end(); iter++)
	{
		// if this is the object we are looking for.
		if (&(*iter) == &pObject)
		{
			// Remove the object from the list
			RemoveObject(iter);
			break;
		}
	}
}