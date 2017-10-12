#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/Components/IComponent.h"
#include "Core/GameManagers/IWindowManager.h"
#include "Engine/Game/GameManager.h"
#include <windows.h>

namespace engine {

//=============================================================================
// CLASS WindowManager
//=============================================================================
class WindowManager
	: public GameManager<WindowManager>
	, virtual public IWindowManager
{
public:
	static constexpr IdType TypeId = "WindowManager";
	static constexpr IdType Interfaces[] = {
		IWindowManager::TypeId,
	};

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
