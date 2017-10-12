#pragma once

//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/Components/IComponentInterface.h"
#include "Core/Components//IInputInterface.h"

namespace engine
{

//=============================================================================
// CLASS IKeyboardInputComponent
//=============================================================================
class IKeyboardInputInterface : virtual public IInputInterface
{
public:
	static constexpr IdType TypeId = "IKeyboardInputComponent";

public:
	virtual void onKeyDown(int aVirtKey) = 0;
	virtual void onKeyUp(int aVirtKey) = 0;
};
} // namespace engine
