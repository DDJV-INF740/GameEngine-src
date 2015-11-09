#include "Precompiled.h"
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "SimulationComponent.h"
#include "Components/ComponentFactory.h"
#include "PxPhysicsAPI.h"

namespace engine {


//=============================================================================
// CLASS DynamicSimulationComponent
//=============================================================================
//-----------------------------------------------------------------------------
//
physx::PxRigidDynamic& DynamicSimulationComponent::pxActor()
{
	return *_pxActor;
}

//-----------------------------------------------------------------------------
//
physx::PxTransform DynamicSimulationComponent::pose()
{
	return pxActor().getGlobalPose();
}

//-----------------------------------------------------------------------------
//
void DynamicSimulationComponent::setPose(const physx::PxTransform &iPose)
{
	pxActor().setGlobalPose(iPose);
}

//-----------------------------------------------------------------------------
//
physx::unique_ptr<physx::PxRigidDynamic> DynamicSimulationComponent::createPxActor()
{
	return physx::unique_ptr<physx::PxRigidDynamic>(
		Game<ISimulationManager>()->physics().createRigidDynamic(physx::PxTransform::createIdentity())
		);
}


//=============================================================================
// CLASS StaticSimulationComponent
//=============================================================================
//-----------------------------------------------------------------------------
//
physx::PxTransform StaticSimulationComponent::pose()
{
	return pxActor().getGlobalPose();
}

//-----------------------------------------------------------------------------
//
void StaticSimulationComponent::setPose(const physx::PxTransform &iPose)
{
	pxActor().setGlobalPose(iPose);
}

//-----------------------------------------------------------------------------
//
physx::PxRigidStatic& StaticSimulationComponent::pxActor()
{
	return *_pxActor;
}

//-----------------------------------------------------------------------------
//
physx::unique_ptr<physx::PxRigidStatic> StaticSimulationComponent::createPxActor()
{
	return physx::unique_ptr<physx::PxRigidStatic>(
		Game<ISimulationManager>()->physics().createRigidStatic(physx::PxTransform::createIdentity())
		);
}

} // namespace engine

//=============================================================================
// COMPONENT REGISTRATION
//=============================================================================
namespace engine {
IComponent::IdType DynamicSimulationComponent::TypeId() { return "DynamicSimulationComponent"; }
IComponent::IdType StaticSimulationComponent::TypeId() { return "StaticSimulationComponent"; }

RegisterComponentType<DynamicSimulationComponent>* gRegisterPxRigidDynamicSimulationComponent = new RegisterComponentType<DynamicSimulationComponent>();
RegisterComponentType<StaticSimulationComponent>* gRegisterPxRigidStaticSimulationComponent = new RegisterComponentType<StaticSimulationComponent>();
}