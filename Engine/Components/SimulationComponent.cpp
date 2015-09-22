#include "Precompiled.h"
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "SimulationComponent.h"
#include "Components/ComponentFactory.h"
#include "PxPhysicsAPI.h"

//=============================================================================
// CLASS DynamicSimulationComponent
//=============================================================================
//-----------------------------------------------------------------------------
//
physx::PxRigidDynamic& DynamicSimulationComponent::pxActor()
{
	return (physx::PxRigidDynamic&)*_pxActor;
}

//-----------------------------------------------------------------------------
//
void DynamicSimulationComponent::setPxActor(physx::PxRigidDynamic *iPxActor)
{
 	base::setPxActor(iPxActor);
}

//-----------------------------------------------------------------------------
//
physx::PxTransform DynamicSimulationComponent::pose()
{
	return pxActor().getGlobalPose();
}

//-----------------------------------------------------------------------------
//
void DynamicSimulationComponent::setPose( const physx::PxTransform &iPose )
{
	pxActor().setGlobalPose(iPose);
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
void StaticSimulationComponent::setPose( const physx::PxTransform &iPose )
{
	pxActor().setGlobalPose(iPose);
}

//-----------------------------------------------------------------------------
//
void StaticSimulationComponent::setPxActor(physx::PxRigidStatic *iPxActor)
{
	base::setPxActor(iPxActor);
}

//-----------------------------------------------------------------------------
//
physx::PxRigidStatic& StaticSimulationComponent::pxActor()
{
	return (physx::PxRigidStatic&)*_pxActor;
}

//=============================================================================
// COMPONENT REGISTRATION
//=============================================================================
IComponent::IdType DynamicSimulationComponent::TypeId() { return "DynamicSimulationComponent"; }
IComponent::IdType StaticSimulationComponent::TypeId() { return "StaticSimulationComponent"; }

RegisterComponentType<DynamicSimulationComponent>* gRegisterPxRigidDynamicSimulationComponent = new RegisterComponentType<DynamicSimulationComponent>();
RegisterComponentType<StaticSimulationComponent>* gRegisterPxRigidStaticSimulationComponent = new RegisterComponentType<StaticSimulationComponent>();
