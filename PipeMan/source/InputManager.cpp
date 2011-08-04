#include "InputManager.h"
#include "SaveInfo.h"
#include <assert.h>
#include <iostream>

extern HINSTANCE	app;
extern HWND			wnd;

CInputManager* CInputManager::m_pInstance = NULL;

CInputManager::CInputManager()
{
	m_pInput = NULL;
	m_pKeyboard = NULL;
	m_pMouse = NULL;
}

CInputManager* CInputManager::GetInstance()
{
	return m_pInstance;
}

CInputManager* CInputManager::CreateInstance( HWND wnd )
{
	if (m_pInstance != NULL)
		return m_pInstance;

	m_pInstance = new CInputManager();
	m_pInstance->Initialize(wnd);

	return m_pInstance;
}

void CInputManager::Initialize( HWND wnd )
{
	DirectInput8Create(app, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL);

	m_pInput->CreateDevice(GUID_SysMouse, &m_pMouse, NULL);
	m_pInput->CreateDevice(GUID_SysKeyboard, &m_pKeyboard, NULL);

	m_pMouse->SetCooperativeLevel(wnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	m_pKeyboard->SetCooperativeLevel(wnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	m_pMouse->SetDataFormat(&c_dfDIMouse);
	m_pKeyboard->SetDataFormat(&c_dfDIKeyboard);

	if (m_pKeyboard->Acquire() == DI_OK)
		std::cout << "Keyboard Success\n";
	
	if (m_pMouse->Acquire() == DI_OK)
		std::cout << "Mouse Success\n";

	ZeroMemory(&m_tInput, sizeof(tInput));

	m_vMousePrevPosition = POINT();
	m_vMousePosition = POINT();
	m_Wnd = wnd;
}

void CInputManager::Shutdown()
{
	m_pKeyboard->Release();
	m_pMouse->Release();
	m_pInput->Release();

	m_pInput = NULL;
	m_pMouse = NULL;
	m_pKeyboard = NULL;

	delete m_pInstance;
	m_pInstance = NULL;	
}

void CInputManager::Update()
{
	memcpy_s(m_tInput.prevKeyboard, 256, m_tInput.curKeyboard, 256);
	memcpy_s(&m_tInput.prevMouseState, sizeof(DIMOUSESTATE), &m_tInput.curMouseState, sizeof(DIMOUSESTATE));

	m_pMouse->GetDeviceState(sizeof(DIMOUSESTATE), &m_tInput.curMouseState);
	m_pKeyboard->GetDeviceState(256, &m_tInput.curKeyboard);

	m_vMousePrevPosition = m_vMousePosition;
	
	RECT pRect;
	GetCursorPos( &m_vMousePosition );
	GetWindowRect( m_Wnd, &pRect);

	if(CSaveInfo::GetInstance()->GetIsWindowed())
	{
		//Need to offset the position more because of the borders around the window
		m_vMousePosition.x -= pRect.left + 7;
		m_vMousePosition.y -= pRect.top + 30;
	}
	else
	{
		m_vMousePosition.x -= pRect.left;
		m_vMousePosition.y -= pRect.top;
	}
}

void CInputManager::RegainControl()
{
	m_pKeyboard->Release();
	m_pMouse->Release();
	m_pInput->Release();

	Initialize(m_Wnd);
}

bool CInputManager::MouseReleased(short sButton) const
{
	return !m_tInput.curMouseState.rgbButtons[sButton];
}

bool CInputManager::MouseReleasedBuffered(short sButton) const
{
	return !m_tInput.curMouseState.rgbButtons[sButton] && m_tInput.prevMouseState.rgbButtons[sButton];
}

bool CInputManager::MouseClicked(short sButton) const
{
	return 0 != m_tInput.curMouseState.rgbButtons[sButton];
}

bool CInputManager::MouseClickedBuffered(short sButton) const
{
	return m_tInput.curMouseState.rgbButtons[sButton] && !m_tInput.prevMouseState.rgbButtons[sButton];
}

bool CInputManager::KeyPressed(short sButton) const
{
	return 0 != (m_tInput.curKeyboard[sButton] & 0x80);
}

bool CInputManager::KeyPressedBuffered(short sButton) const
{
	return (m_tInput.curKeyboard[sButton] & 0x80) && !(m_tInput.prevKeyboard[sButton] & 0x80);
}


bool CInputManager::KeyReleased(short sButton) const
{
	return !(m_tInput.curKeyboard[sButton] & 0x80);
}

bool CInputManager::KeyReleasedBuffered(short sButton) const
{
	return !(m_tInput.curKeyboard[sButton] & 0x80) && (m_tInput.prevKeyboard[sButton] & 0x80);
}