#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/Components/IComponent.h"
#include "Core/GameManagers/ISimulationManager.h"
#include "Engine/Game/GameComponent.h"

namespace engine {

//=============================================================================
// CLASS SimulationManager
//=============================================================================
class SimulationManager
	: public GameComponent<SimulationManager>
	, public ISimulationManager
{
public:
	static IComponent::IdType TypeId();
	static IComponentInterface::IdType* Interfaces()
	{
		static IComponentInterface::IdType sInterfaces[] = {
			ISimulationManager::TypeId(),
			0
		};

		return sInterfaces;
	}

public:
	SimulationManager();
	virtual ~SimulationManager();

public: // IComponen
	virtual void onAttached(const GameEngineRef &iGameEngine) override;
	virtual void onDetached(const GameEngineRef &iGameEngine) override;

public: // ISimulationManager
	virtual physx::PxPhysics& physics();
	virtual physx::PxScene& scene();

public:
	void update();

private:
	class SimulationManagerImp;
	SimulationManagerImp *_imp;
};
} // namespace engine
