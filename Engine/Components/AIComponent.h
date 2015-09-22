#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/Components/IComponent.h"
#include "Core/Components/IIAInterface.h"
#include "Core/GameObjects/IBehaviour.h"
#include "Engine/Managers/AIManager.h"
#include "Engine/GameObjects/GameObjectComponent.h"
#include <memory>

//=============================================================================
// CLASS AIComponent
//=============================================================================
class AIComponent
	: public GameObjectComponent<AIComponent>
	, virtual public IAIInterface
{
public:
	static IComponent::IdType TypeId();
	static IComponentInterface::IdType* Interfaces()
	{
		static IComponentInterface::IdType sInterfaces[] = {
			IAIInterface::TypeId(),
			0
		};

		return sInterfaces;
	}

	void setBehaviour(const IBehaviourRef &iBehaviour);

public: // IComponent
	virtual void onAttached(const GameObjectRef &iGameObject) override;
	virtual void onDetached(const GameObjectRef &iGameObject) override;

public: // IAIInterface
	virtual void updateAI() override;

private:
	GameObjectWeakRef _go;
	IBehaviourRef _behaviour;
};