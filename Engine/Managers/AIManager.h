#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/Components/IComponent.h"
#include "Core/GameManagers/IGameLoopManager.h"
#include "Core/GameManagers/IAIManager.h"
#include "Engine/Game/GameComponent.h"
#include <vector>

//=============================================================================
// CLASS AIManager
//=============================================================================
class AIManager
	: public GameComponent<AIManager>
	, public IAIManager
{
public:
	static IComponent::IdType TypeId();
	static IComponentInterface::IdType* Interfaces()
	{
		static IComponentInterface::IdType sInterfaces[] = {
			IAIManager::TypeId(),
			0
		};

		return sInterfaces;
	}

public: // IComponent
	virtual void onAttached(const GameEngineRef &iGameEngine) override {}
	virtual void onDetached(const GameEngineRef &iGameEngine) override {}

public: // IAIManager
	void addComponent(IAIInterface *iAIInstance);
	void removeComponent(IAIInterface *iAIInstance);

	void update();

private:
	std::vector<IAIInterface*> _aiInstances;

};

