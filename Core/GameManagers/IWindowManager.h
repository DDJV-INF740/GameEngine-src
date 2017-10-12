#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/Game/IManager.h"
#include "Core/Components/IdType.h"

//=============================================================================
// FORWARD DECLARATIONS
//=============================================================================
typedef struct HWND__ *HWND;

namespace engine
{

//=============================================================================
// CLASS IWindowManager
//=============================================================================
class IWindowManager: virtual public IManager
{
public:
	static constexpr IdType TypeId = "IWindowManager";

public:
	virtual HWND window() = 0;
};

} // namespace engine
