#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/Components/IComponent.h"
#include "Core/GameManagers/IWindowManager.h"
#include "Engine/Game/GameComponent.h"
#include <windows.h>

namespace engine {

//=============================================================================
// CLASS WindowManager
//=============================================================================
class WindowManager
	: public GameComponent<WindowManager>
	, virtual public IWindowManager
{
public:
	static IComponent::IdType TypeId();
	static IComponentInterface::IdType* Interfaces()
	{
		static IComponentInterface::IdType sInterfaces[] = {
			IWindowManager::TypeId(),
			0
		};

		return sInterfaces;
	}

public: // IComponent
	virtual void onAttached(const GameEngineRef &iGameEngine) override;
	virtual void onDetached(const GameEngineRef &iGameEngine) override;

public: // IWindowManager
	virtual HWND window() override;

public:
	LRESULT windowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
		
private:
	HWND _hWnd;
};
} // namespace engine
