#include <windows.h>
#include <stdio.h>
#include <dbghelp.h>
#pragma comment(lib, "dbghelp.lib")

#include "Game.h"
#include "SaveInfo.h"
#include <time.h>

#include <string>
using std::string;
//Instance 
HINSTANCE   app;
//Window handle
HWND wnd;

FILE* stream;
CSaveInfo* pSI;

#define GAME_NAME "Pipe Man (Title Pending)"

int WINAPI WinMain(HINSTANCE hInstance,		// handle to application
				   HINSTANCE hPrevInstance,	// handle to previous app
				   LPTSTR lpCmdLine,		// command line string
				   int nCmdShow );			// show window value

LRESULT CALLBACK WndProc(HWND hWnd,				// handle to window
						 UINT message,			// incoming message
						 WPARAM wparam,			// message info
						 LPARAM lparam );		// message info

bool InitWindow(void);						// initialize window

LONG WINAPI errorFunc(_EXCEPTION_POINTERS *pExceptionInfo);

int WINAPI WinMain(HINSTANCE hInstance,		// handle to application
				   HINSTANCE hPrevInstance,	// handle to previous app
				   LPTSTR lpCmdLine,		// command line string
				   int nCmdShow )			// show window value
{

	app = hInstance;

	srand(unsigned int(time(0)));	//randomize!
	pSI = CSaveInfo::Initialize();

	//////////////////////////////////////////////////////////////////////////
	// Creation of console window
	AllocConsole() ;
	AttachConsole( GetCurrentProcessId() ) ;
	freopen_s(&stream, "CON", "w", stdout ) ;
	//////////////////////////////////////////////////////////////////////////

    InitWindow();					// get window
	//InitGame();						// initialize game
	CGame::GetInstance()->Initialize(wnd);

	// Main message loop:
	MSG msg; ZeroMemory( &msg, sizeof( msg ) );

#ifndef _DEBUG
	SetUnhandledExceptionFilter(errorFunc);
#endif

	bool bRunning = true;
	while (msg.message != WM_QUIT)
	{
		// Call the gameloop once per frame
		//LoopGame();
		if( bRunning )
		{ 
			bRunning = CGame::GetInstance()->Run();
			if( false == bRunning ) //game runs until it returns false;
				PostQuitMessage(0);
		}

		if (PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	//EndGame();						// clean up after game ends
	CGame::GetInstance()->Shutdown();
	// window cleanup
	SetWindowText(wnd, GAME_NAME);
	UnregisterClass( GAME_NAME, app ); // unregister window

	//////////////////////////////////////////////////////////////////////////
	// Deletion of console window
	FreeConsole();
	//////////////////////////////////////////////////////////////////////////

	return 0;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_ACTIVATEAPP:
		{
			if (wParam)
				CGame::GetInstance()->Reset(false);
			break;
		}
		case WM_SETFOCUS:
			{
				// temp fix for input loss on alt-tab
				CGame::GetInstance()->Reset(false);
			}
			break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

//CONTROLS THE WINDOW IF RESIZED
void ResizeWindow(HWND hWnd, int width, int height)
{  
	// get the size of the current client area
	RECT rcClient;
	GetClientRect(hWnd, &rcClient);
  
	// get the size of the containing window
	RECT rcWindow;
	GetWindowRect(hWnd, &rcWindow);
  
	// determine the difference between the two
	POINT diff;
	diff.x = (rcWindow.right - rcWindow.left) - rcClient.right;
	diff.y = (rcWindow.bottom - rcWindow.top) - rcClient.bottom;
	// resize the client area
	MoveWindow(hWnd,rcWindow.left, rcWindow.top, width + diff.x, height + diff.y, TRUE);
}

//CREATES THE DX WINDOW
bool InitWindow( void )
{   
    WNDCLASSEX  wndClass;

    // register a new type of window
    ZeroMemory( &wndClass, sizeof( wndClass ) );
    wndClass.cbSize         = sizeof( WNDCLASSEX );             // size of window structure
    wndClass.lpfnWndProc    = ( WNDPROC )WndProc;               // message callback
    wndClass.lpszClassName  = GAME_NAME;			            // class name
    wndClass.hInstance      = app;			                    // handle to application
	wndClass.hIcon			= NULL;								//LoadIcon(app, MAKEINTRESOURCE(IDI_ICON1));
    wndClass.hCursor        = LoadCursor( NULL, IDC_ARROW );    // default cursor
    wndClass.hbrBackground  = ( HBRUSH )( COLOR_WINDOWFRAME );  // background brush
	RegisterClassEx( &wndClass );



	// Setup window style flags
	DWORD dwWindowStyleFlags = WS_VISIBLE;

	if (pSI->GetIsWindowed())
	{
		dwWindowStyleFlags |= WS_OVERLAPPEDWINDOW;
	}
	else
	{
		dwWindowStyleFlags |= WS_POPUP;
		ShowCursor(FALSE);	// Stop showing the mouse cursor
	}

    // create window of registered type
    wnd = CreateWindow(
        GAME_NAME, GAME_NAME,     // class name, window title 
		dwWindowStyleFlags,										// window style
        CW_USEDEFAULT, CW_USEDEFAULT,                           // x & y coordinates
        pSI->GetScreenWidth(), pSI->GetScreenHeight(),                            // width & height of window
        NULL, NULL,                                             // parent window & menu
        app,													// handle to application
        NULL );

	ResizeWindow(wnd, pSI->GetScreenWidth(), pSI->GetScreenHeight());
    ShowWindow( wnd, SW_SHOW );                           // technically should be nCmdShow
    UpdateWindow( wnd );

	
    return true;
}

LONG WINAPI errorFunc(_EXCEPTION_POINTERS *pExceptionInfo)
{
	time_t rawtime;
	struct tm timeinfo;

	time ( &rawtime );
	localtime_s(&timeinfo, &rawtime );

	char fileName[256];
	asctime_s(fileName, 256, &timeinfo);
	fileName[13] = '.';
	fileName[16] = '.';
	fileName[24] = '.';
	strcat_s(fileName, 256, "mdmp");

	HANDLE hFile = ::CreateFile(fileName, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL, NULL );

	if (hFile!=INVALID_HANDLE_VALUE)
	{
		_MINIDUMP_EXCEPTION_INFORMATION ExInfo;

		ExInfo.ThreadId = ::GetCurrentThreadId();
		ExInfo.ExceptionPointers = pExceptionInfo;
		ExInfo.ClientPointers = NULL;
		MiniDumpWriteDump( GetCurrentProcess(), GetCurrentProcessId(), hFile, MiniDumpNormal, &ExInfo, NULL, NULL );
		//MessageBox("Dump File Saved look x directory please email to developer at the following email adress crashdmp@gmail.com with the subject Gamename - Version ");
		::CloseHandle(hFile);
	}

	return 0;
} 
