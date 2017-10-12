#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/Components/IComponent.h"
#include "Core/GameManagers/ISimulationManager.h"
#include "Engine/Game/GameManager.h"

namespace engine {

//=============================================================================
// CLASS SimulationManager
//=============================================================================
class SimulationManager
	: public GameManager<SimulationManager>
	, public ISimulationManager
{
public:
	static constexpr IdType TypeId = "SimulationManager";
	static constexpr IdType Interfaces[] = {
		ISimulationManager::TypeId
	};

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
