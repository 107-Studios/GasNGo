#ifndef _MENU_BASE_H_
#define _MENU_BASE_H_

#include "ObjectManager.h"
#include "MENU_DialogBox.h"

class MENU_BaseObject;

class MENU_Base
{
protected:
	vector<MENU_BaseObject*>* m_vMenuObjects;
	MENU_DialogBox* m_pDialogBox;

public:

	// constructors/destructor
	MENU_Base(void);
	~MENU_Base(void);

	// Methods
	void Init(void);
	virtual void Update(float fTime);
	virtual void Render(void);
	bool ObjectExists(MENU_BaseObject* pObject);
	int FindObject(MENU_BaseObject* pObject);
	void AddObject(MENU_BaseObject* pObject);
	void RemoveObject(MENU_BaseObject* pObject);
	void RemoveObject(int nIndex);
	void DisplayDialogBox(LPSTR szText, DialogType eDialogType= DT_DECISION, bool bAutoScaling= true, void (*pFunc)(void)= NULL);
};

#endif