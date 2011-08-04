#ifndef _MENU_DIALOGBOX_H_
#define _MENU_DIALOGBOX_H_

#include "MENU_BaseObject.h"
#include "MENU_Button.h"

#define BAR_OFFSET 40.0f

enum DialogResponse {DR_OK, DR_CANCEL, DR_NULL};
enum DialogStatus {DS_OPENING, DS_CLOSING, DS_OPENED, DS_CLOSED, DS_MOVING, DS_HIDDEN, DS_NOTHIDDEN};
enum DialogType {DT_DECISION, DT_NOTIFICATION};

class MENU_DialogBox : public MENU_BaseObject
{
protected:
	MENU_Button *m_pOk;
	MENU_Button *m_pCancel;

	CRectangleF m_rBodyDrawRect;
	D3DCOLOR m_d3dBodyColor;

	DialogType m_eDialogType;
	DialogResponse m_eDialogResponse;
	DialogStatus m_eDialogStatus;

	LPTSTR m_szDialogText;

public:
	// methods
	virtual void Init(void);
	void Display(LPSTR, DialogType= DT_DECISION, bool= true, void (*pFunc)(void)= NULL);
	virtual void Update(float fTime);
	virtual void Render(void);
	static MENU_DialogBox* GetInstance(void) {static MENU_DialogBox pDialog; return &pDialog;}

	// mutators
	void OK_ButtonText(LPTSTR);
	void OK_ButtonEnabled(bool bEnabled) { m_pOk->Enabled(bEnabled);}
	void OK_ClickAction( void (*pFunc)(void) ) { m_pOk->ClickAction(pFunc); }
	void Cancel_ButtonText(LPTSTR);
	void Cancel_ButtonEnabled(bool bEnabled) { m_pCancel->Enabled(bEnabled);}
	void Text(LPTSTR szText) { if (m_szDialogText) delete m_szDialogText; m_szDialogText= szText; }

	// accessors
	DialogStatus CurrentStatus(void) { return m_eDialogStatus; }
	bool OK_ButtonEnabled( void ) { return m_pOk->Enabled(); }
	bool Cancel_ButtonEnabled( void ) { return m_pCancel->Enabled(); }

private:
	// constructors
	MENU_DialogBox();
	MENU_DialogBox(const MENU_DialogBox& pDialogBox);
	MENU_DialogBox& operator=(const MENU_DialogBox& pDialogBox);
	~MENU_DialogBox();

	//methods
	virtual void Resize(void);
	virtual void ModeSwitch(DialogType);
};

#endif