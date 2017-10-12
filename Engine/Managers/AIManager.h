#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/Components/IComponent.h"
#include "Core/GameManagers/IGameLoopManager.h"
#include "Core/GameManagers/IAIManager.h"
#include "Engine/Game/GameManager.h"
#include <vector>

namespace engine {

//=============================================================================
// CLASS AIManager
//=============================================================================
class AIManager
	: public GameManager<AIManager>
	, public IAIManager
{
public:
	static constexpr IdType TypeId = "AIManager";
	static constexpr IdType Interfaces[] = {
		IAIManager::TypeId
	};

public: // IComponent
	virtual void onAttached(const GameEngineRef &iGameEngine) override {}
	virtual void onDetached(const GameEngineRef &iGameEngine) override {}

public: // IAIManager
	void createComponent(IAIInterface *iAIInstance);
	void removeComponent(IAIInterface *iAIInstance);

	void update();

private:
	std::vector<IAIInterface*> _aiInstances;

};

} // namespace engine
