#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/Game/IGameInterface.h"

//=============================================================================
// FORWARD DECLARATIONS
//=============================================================================
typedef struct HWND__ *HWND;

namespace engine
{

//=============================================================================
// CLASS IWindowManager
//=============================================================================
class IWindowManager: virtual public IGameInterface
{
public:
	static IdType TypeId();

public:
	virtual HWND window() = 0;
};

} // namespace engine
