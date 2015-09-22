#pragma once

//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/Components/IComponentInterface.h"

//=============================================================================
// CONSTANTS
//=============================================================================
typedef enum
{
	KEY_UP,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_DOWN,
	KEY_ABUTTON,
	KEY_SHIFTBUTTON,
	KEY_CTRLBUTTON,
	KEY_COUNT,
	KEY_NONE = KEY_COUNT
} ControllerKey;

//=============================================================================
// CLASS InputInterface
//=============================================================================
class IInputInterface: virtual public IComponentInterface
{
public:
	static IInputInterface::IdType TypeId();

public:
	virtual bool isPressed(ControllerKey aKey) const = 0;
	virtual void setKey(ControllerKey aKey, bool aIsPressed) = 0;
};
