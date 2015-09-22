#pragma once

//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/Components/IFollowPoseInterface.h"
#include "Engine/GameObjects/GameObjectComponent.h"

//=============================================================================
// CLASS FollowPoseComponent
//=============================================================================
class FollowPoseComponent: 
	public GameObjectComponent<FollowPoseComponent>, 
	virtual public IFollowPoseInterface,
	virtual public IPoseInterface
{
public:
	static IComponent::IdType TypeId();

	static IComponentInterface::IdType* Interfaces()
	{
		static IComponentInterface::IdType sInterfaces[] = {
			IFollowPoseInterface::TypeId(),
			IPoseInterface::TypeId(),
			0
		};

		return sInterfaces;
	}

public:
	physx::PxTransform updatePose();

public: // IFollowPoseInterface
	virtual void follow(const GameObjectRef &iGameObject) override;

	virtual GameObjectRef followed() override;
	virtual void setPoseAdjustment(AdjustPoseCb iPoseAdjustment) override;

public: // IPoseInterface
	virtual physx::PxTransform pose() override;
	virtual void setPose(const physx::PxTransform &iPose) override;

public:
	FollowPoseComponent();

private:
	AdjustPoseCb _poseAdjustment;
	GameObjectWeakRef _followedGO;
	physx::PxTransform _lastPose;
};


