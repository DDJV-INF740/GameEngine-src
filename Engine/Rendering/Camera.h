#pragma once

//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/GameObjects/IGameObject.h"
#include "Engine/GameObjects/GameObject.h"

namespace engine {

//=============================================================================
// CLASS Camera
//=============================================================================
class Camera
	: public GameObject<Camera>
{
public:
	static constexpr IdType TypeId = "Camera";

	Camera(const GameObjectDataRef &aDataRef);

	virtual void onSpawn(const physx::PxTransform &aPose) override;
	virtual void onUnspawn() override;
};

} // namespace engine

