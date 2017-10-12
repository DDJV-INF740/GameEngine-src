#pragma once

//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/Components/IComponent.h"
#include "Core/Components/IInputInterface.h"
#include "Core/Components/IKeyboardInputInterface.h"
#include "Engine/GameObjects/GameObjectComponent.h"
#include "Core/GameObjects/IGameObject.h"

#include <bitset>

namespace engine {

//=============================================================================
// CLASS KeyboardController
//=============================================================================
class KeyboardInputComponent
	: public GameObjectComponent<KeyboardInputComponent>
	, virtual public IKeyboardInputInterface
{
public:
	static constexpr IdType TypeId = "KeyboardInputComponent";
	static constexpr IdType Interfaces[] = {
		IKeyboardInputInterface::TypeId,
		IInputInterface::TypeId
	};


public:
	KeyboardInputComponent()
		: _keys()
		, _go()
	{}


	virtual void onKeyDown(int aVirtKey) override;
	virtual void onKeyUp(int aVirtKey) override;

	virtual bool isPressed(ControllerKey aKey) const override;
	virtual void setKey(ControllerKey aKey, bool aIsPressed) override;

	virtual void onAttached(const GameObjectRef &iGameObject) override;
	virtual void onDetached(const GameObjectRef &iGameObject) override;

protected:
	std::bitset<(int)ControllerKey::KEY_COUNT> _keys;
	GameObjectWeakRef _go;
};
} // namespace engine
