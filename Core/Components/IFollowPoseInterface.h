#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/Components/IPoseInterface.h"

//=============================================================================
// INTERFACE IFollowPoseInterface
//=============================================================================
class IFollowPoseInterface: virtual public IPoseInterface
{
public:
	static IdType TypeId();

public:
	typedef physx::PxTransform (*AdjustPoseCb)(const physx::PxTransform &iPose);

public:
	virtual void follow(const GameObjectRef &iGameObject) = 0;
	virtual void setPoseAdjustment(AdjustPoseCb iPoseAdjustment) = 0;
	virtual GameObjectRef followed() = 0;
};