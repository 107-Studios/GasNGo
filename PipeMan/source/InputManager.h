#ifndef _INPUTMANAGER_H_
#define _INPUTMANAGER_H_

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <XInput.h>
#include <windows.h>

struct tInput
{
	DIMOUSESTATE curMouseState;
	DIMOUSESTATE prevMouseState;

	char		 curKeyboard[256];
	char		 prevKeyboard[256];
};

class CInputManager
{
private:
	IDirectInput8*			m_pInput;
	IDirectInputDevice8*	m_pMouse;
	IDirectInputDevice8*	m_pKeyboard;
	tInput					m_tInput; 

	POINT					m_vMousePosition;		//Current mouse position
	POINT					m_vMousePrevPosition;	//Previous mouse position
	HWND					m_Wnd;					//To get the rect of the window to offset mouse position

	static CInputManager* m_pInstance;

	CInputManager();
	~CInputManager() {}
	CInputManager(const CInputManager& ipm);
	CInputManager& operator=(const CInputManager& ipm) { return *this; }

	//////////////////////////////////////////////////////////////////////////
	// Initialize():		Initializes the input devices.
	//						A helper function for the static instance
	//
	// Returns:				void
	//////////////////////////////////////////////////////////////////////////
	void Initialize( HWND Wnd );

public:
	enum MouseButtons {LEFT_CLICK = 0, RIGHT_CLICK, MIDDLE_CLICK, MOUSE4};
	//////////////////////////////////////////////////////////////////////////
	// CreateInstance():	Creates an instance of the input manager
	//
	// Returns:				CInputManager*
	//////////////////////////////////////////////////////////////////////////
	static CInputManager* CreateInstance( HWND wnd );
	
	//////////////////////////////////////////////////////////////////////////
	// GetInstance():		Returns the instance of the input manager
	//
	// Returns:				CInputManager*
	//////////////////////////////////////////////////////////////////////////
	static CInputManager* GetInstance();

	//////////////////////////////////////////////////////////////////////////
	// Shutdown():			Cleans up the devices and static instance
	//
	// Returns:				void
	//////////////////////////////////////////////////////////////////////////
	void Shutdown();

	void Update();
	void RegainControl();

	bool MouseReleased(short sButton) const;
	bool MouseReleasedBuffered(short sButton) const;

	bool MouseClicked(short sButton) const;
	bool MouseClickedBuffered(short sButton) const;

	bool KeyPressed(short sButton) const;
	bool KeyPressedBuffered(short sButton) const;

	bool KeyReleased(short sButton) const;
	bool KeyReleasedBuffered(short sButton) const;

	inline POINT const & GetCursorPosition() const			{ return m_vMousePosition; }
	inline void SetCursorPosition( POINT const & vPoint )	{ m_vMousePosition = vPoint; }

	inline POINT const & GetCursorPrevPosition() const			{ return m_vMousePrevPosition; }
	inline void SetCursorPrevPosition( POINT const & vPoint )	{ m_vMousePrevPosition = vPoint; }
	
};
#endif