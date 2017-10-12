#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/Components/IPoseInterface.h"

namespace engine
{

//=============================================================================
// INTERFACE IFollowPoseInterface
//=============================================================================
class IFollowPoseInterface: virtual public IPoseInterface
{
public:
	static constexpr IdType TypeId = "IFollowPoseInterface";

public:
	using AdjustPoseCb = physx::PxTransform (*)(const physx::PxTransform &iPose);

public:
	virtual void follow(const GameObjectRef &iGameObject) = 0;
	virtual void setPoseAdjustment(AdjustPoseCb iPoseAdjustment) = 0;
	virtual GameObjectRef followed() = 0;
};

} // namespace engine
