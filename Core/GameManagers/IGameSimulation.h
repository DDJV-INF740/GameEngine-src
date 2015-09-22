#pragma once

#include "Core/Game/IGameInterface.h"
#include "Core/physx/PxPhysicsAPI.forward.h"

class IGameSimulation: virtual public IGameInterface
{
public:
	static IdType TypeId();
	
public:
	virtual physx::PxPhysics& physics() = 0;
	virtual physx::PxScene& scene() = 0;

	virtual void update() = 0;
};