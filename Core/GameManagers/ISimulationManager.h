#pragma once

#include "Core/Game/IManager.h"
#include "core/Components/IdType.h"
#include "Core/physx/PxPhysicsAPI.forward.h"

namespace engine
{

class ISimulationManager: virtual public IManager
{
public:
	static constexpr IdType TypeId = "ISimulationManager";
	
public:
	virtual physx::PxPhysics& physics() = 0;
	virtual physx::PxScene& scene() = 0;

	virtual void update() = 0;
};

using ISimulationManagerRef = std::shared_ptr<ISimulationManager>;
using ISimulationManagerWeakRef = std::weak_ptr<ISimulationManager>;

} // namespace engine
