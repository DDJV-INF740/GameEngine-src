//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Precompiled.h"
#include "InputComponent.h"
#include "Managers/InputManager.h"
#include <windows.h>

namespace engine {

//=============================================================================
// PRIVATE FUNCTIONS
//=============================================================================
ControllerKey TranslateKey(int aVirtKey)
{
	switch(aVirtKey)
	{
	case(VK_UP):
	case('W'):
		return ControllerKey::KEY_UP;
	case(VK_DOWN):
	case('S'):
		return ControllerKey::KEY_DOWN;
	case('A'):
	case(VK_LEFT):
		return ControllerKey::KEY_LEFT;
	case('D'):
	case(VK_RIGHT):
		return ControllerKey::KEY_RIGHT;
	case(VK_SPACE):
		return ControllerKey::KEY_ABUTTON;
	case(VK_SHIFT):
		return ControllerKey::KEY_SHIFTBUTTON;
	case(VK_CONTROL):
		return ControllerKey::KEY_CTRLBUTTON;
	}
	return ControllerKey::KEY_NONE;
}

//=============================================================================
// CLASS KeyboardController
//=============================================================================
void KeyboardInputComponent::onKeyDown(int aVirtKey)
{
	setKey(TranslateKey(aVirtKey), true);
}

//-----------------------------------------------------------------------------
//
void KeyboardInputComponent::onKeyUp(int aVirtKey)
{
	setKey(TranslateKey(aVirtKey), false);
}

//=============================================================================
// CLASS Controller
//=============================================================================
bool KeyboardInputComponent::isPressed( ControllerKey aKey ) const
{
	if (aKey != ControllerKey::KEY_NONE)
		return _keys[(int)aKey];
	return false;
}

//-----------------------------------------------------------------------------
//
void KeyboardInputComponent::setKey( ControllerKey aKey, bool aIsPressed )
{
	if (aKey != ControllerKey::KEY_NONE)
		_keys[(int)aKey] = aIsPressed;
}

//-----------------------------------------------------------------------------
//
void KeyboardInputComponent::onAttached( const GameObjectRef &iGameObject )
{
	_go = iGameObject;
	InputManager::Instance.createComponent(this);
}

//-----------------------------------------------------------------------------
//
void KeyboardInputComponent::onDetached( const GameObjectRef &iGameObject )
{
	InputManager::Instance.removeComponent(this);
	_go.reset();
}
} // namespace engine

