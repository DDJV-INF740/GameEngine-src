#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/Components/IComponent.h"
#include "Core/GameManagers/IGameSimulation.h"
#include "Engine/Game/GameComponent.h"

//=============================================================================
// CLASS SimulationManager
//=============================================================================
class SimulationManager
	: public GameComponent<SimulationManager>
	, public IGameSimulation
{
public:
	static IComponent::IdType TypeId();
	static IComponentInterface::IdType* Interfaces()
	{
		static IComponentInterface::IdType sInterfaces[] = {
			IGameSimulation::TypeId(),
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

public: // IGameSimulation
	virtual physx::PxPhysics& physics();
	virtual physx::PxScene& scene();

public:
	void update();

private:
	class SimulationManagerImp;
	SimulationManagerImp *_imp;
};