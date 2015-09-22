#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/Components/IComponent.h"
#include "Core/GameManagers/IGameWindow.h"
#include "Engine/Game/GameComponent.h"
#include <windows.h>

//=============================================================================
// CLASS WindowManager
//=============================================================================
class WindowManager
	: public GameComponent<WindowManager>
	, virtual public IGameWindow
{
public:
	static IComponent::IdType TypeId();
	static IComponentInterface::IdType* Interfaces()
	{
		static IComponentInterface::IdType sInterfaces[] = {
			IGameWindow::TypeId(),
			0
		};

		return sInterfaces;
	}

public: // IComponent
	virtual void onAttached(const GameEngineRef &iGameEngine) override;
	virtual void onDetached(const GameEngineRef &iGameEngine) override;

public: // IGameWindow
	virtual HWND window() override;

public:
	LRESULT windowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
		
private:
	HWND _hWnd;
};