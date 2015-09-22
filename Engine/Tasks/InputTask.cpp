//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Precompiled.h"
#include "InputTask.h"
#include "Core/Game/Game.h"
#include "Components/InputComponent.h"
#include "Managers/PlayerManager.h"
#include "Managers/InputManager.h"
#include "Core/GameManagers/IGameLoop.h"
#include "Core/GameManagers/IGameTime.h"
#include <windows.h>

//=============================================================================
// CLASS InputTask
//=============================================================================
void InputTask::update()
{
	MSG msg;
    while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);

		if(msg.message == WM_QUIT)
		{
			Game<IGameLoop>()->requestExit(true);
	        break;
		}
		else if (msg.message == WM_KEYDOWN || msg.message == WM_KEYUP)
		{
			bool isDown = msg.message == WM_KEYDOWN;
			int nVirtKey = (int)msg.wParam;

			if (isDown)
				InputManager::Instance.onKeyDown(nVirtKey);
			else
				InputManager::Instance.onKeyUp(nVirtKey);

			switch(nVirtKey)
			{
			case(VK_TAB):
				Game<IGameTime>()->setGameRate(isDown ? 0.1f : 1.0f);
				break;
			}
		}
    }
}

//-----------------------------------------------------------------------------
//
void InputTask::init()
{}

//-----------------------------------------------------------------------------
//
void InputTask::cleanup()
{}
