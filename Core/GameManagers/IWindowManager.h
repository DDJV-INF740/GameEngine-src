#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/Game/IManager.h"

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
	static IdType TypeId();

public:
	virtual HWND window() = 0;
};

} // namespace engine
