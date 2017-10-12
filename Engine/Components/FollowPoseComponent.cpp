#include "Precompiled.h"

//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "FollowPoseComponent.h"
#include "Core/GameObjects/IGameObject.h"
namespace engine
{

//=============================================================================
// CLASS FollowPoseComponent
//=============================================================================
//-----------------------------------------------------------------------------
//
void FollowPoseComponent::follow( const GameObjectRef &iGameObject)
{
	_followedGO = iGameObject;
	updatePose();
}

//-----------------------------------------------------------------------------
//
GameObjectRef FollowPoseComponent::followed()
{
	return _followedGO.lock();
}

//-----------------------------------------------------------------------------
//
physx::PxTransform FollowPoseComponent::pose()
{
	_lastPose = updatePose();
	return _lastPose;
}

//-----------------------------------------------------------------------------
//
void FollowPoseComponent::setPose( const physx::PxTransform &iPose )
{
	// ignored
}

//-----------------------------------------------------------------------------
//
void FollowPoseComponent::setPoseAdjustment( AdjustPoseCb iPoseAdjustment )
{
	_poseAdjustment = iPoseAdjustment;
}

//-----------------------------------------------------------------------------
//
physx::PxTransform FollowPoseComponent::updatePose()
{
	GameObjectRef wTargetGO = followed();
	if (wTargetGO == nullptr)
		return _lastPose;

	IPoseInterfaceRef wPoseInterface = wTargetGO->as<IPoseInterface>();
	if (wPoseInterface == nullptr)
		return _lastPose;

	physx::PxTransform wPose = wPoseInterface->pose();
	if (_poseAdjustment == nullptr)
		return wPose;

	wPose = _poseAdjustment(wPose);
	return wPose;
}

FollowPoseComponent::FollowPoseComponent() : _poseAdjustment(nullptr)
	, _followedGO()
	, _lastPose(physx::PxIdentity)
{

}

} // namespace engine
