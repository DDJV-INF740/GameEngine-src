//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Precompiled.h"
#include "InputComponent.h"
#include "Managers/InputManager.h"
#include <windows.h>

//=============================================================================
// PRIVATE FUNCTIONS
//=============================================================================
ControllerKey TranslateKey(int aVirtKey)
{
	switch(aVirtKey)
	{
	case(VK_UP):
	case('W'):
		return KEY_UP;
	case(VK_DOWN):
	case('S'):
		return KEY_DOWN;
	case('A'):
	case(VK_LEFT):
		return KEY_LEFT;
	case('D'):
	case(VK_RIGHT):
		return KEY_RIGHT;
	case(VK_SPACE):
		return KEY_ABUTTON;
	case(VK_SHIFT):
		return KEY_SHIFTBUTTON;
	case(VK_CONTROL):
		return KEY_CTRLBUTTON;
	}
	return KEY_NONE;
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
	if (aKey != KEY_NONE)
		return _keys[aKey];
	return false;
}

//-----------------------------------------------------------------------------
//
void KeyboardInputComponent::setKey( ControllerKey aKey, bool aIsPressed )
{
	if (aKey != KEY_NONE)
		_keys[aKey] = aIsPressed;
}

//-----------------------------------------------------------------------------
//
void KeyboardInputComponent::onAttached( const GameObjectRef &iGameObject )
{
	_go = iGameObject;
	InputManager::Instance.addComponent(this);
}

//-----------------------------------------------------------------------------
//
void KeyboardInputComponent::onDetached( const GameObjectRef &iGameObject )
{
	InputManager::Instance.removeComponent(this);
	_go.reset();
}

//=============================================================================
// COMPONENT REGISTRATION
//=============================================================================
#include "Components/ComponentFactory.h"
IComponent::IdType KeyboardInputComponent::TypeId() { return "KeyboardInputComponent"; }
RegisterComponentType<KeyboardInputComponent> *gRegisterKeyboardInputComponent = new RegisterComponentType<KeyboardInputComponent>();

