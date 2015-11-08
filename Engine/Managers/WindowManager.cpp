#include "Precompiled.h"

//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "WindowManager.h"
#include <windows.h>

namespace engine {


#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

//=============================================================================
// PRIVATE FUNCTIONS
//=============================================================================
// this is the main message handler for the program
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	WindowManager* wManager = reinterpret_cast<WindowManager*>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));
	return wManager->windowProc(hWnd, message, wParam, lParam);
}

//=============================================================================
// CLASS WindowManager
//=============================================================================


HWND WindowManager::window()
{
	return _hWnd;
}


LRESULT WindowManager::windowProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	switch(message)
	{
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		} break;
	}

	return DefWindowProc (hWnd, message, wParam, lParam);
}

void WindowManager::onAttached( const GameEngineRef &iGameEngine )
{
	WNDCLASSEX wc;
	HINSTANCE hInstance = GetModuleHandle(NULL);

	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszClassName = _T("WindowClass");

	RegisterClassEx(&wc);

	_hWnd = CreateWindowEx(NULL, _T("WindowClass"), _T("Our Direct3D Program"),
		WS_OVERLAPPEDWINDOW, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT,
		NULL, NULL, hInstance, NULL);

	::SetWindowLongPtr(_hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

	ShowWindow(_hWnd, SW_SHOWDEFAULT/*nCmdShow*/);
}

void WindowManager::onDetached( const GameEngineRef &iGameEngine )
{
	if (_hWnd != nullptr)
	{
		::DestroyWindow(_hWnd);
		_hWnd = nullptr;
	}
}

IComponent::IdType WindowManager::TypeId()
{
	return "WindowManager";
}
} // namespace engine

#include "Engine/Managers/GameManagerFactory.h"
namespace engine {

RegisterGameManagerType<WindowManager> gWindowManagerRegistration;
} // namespace engine
