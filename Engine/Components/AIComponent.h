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

namespace engine
{ 
//=============================================================================
// CLASS AIComponent
//=============================================================================
class AIComponent
	: public GameObjectComponent<AIComponent>
	, virtual public IAIInterface
{
public:
	static constexpr IdType TypeId = "AIComponent";
	static constexpr IdType Interfaces[] = {
		IAIInterface::TypeId
	};

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

} // namespace engine
