#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/Game/IManager.h"
#include "Core/GameObjects/IGameObject.h"
#include "Core/Components/IdType.h"
#include "Core/GameObjects/GameObjectProxy.h"

namespace engine
{

//=============================================================================
// CLASS IPlayerManager
//=============================================================================
class ICameraManager: virtual public IManager
{
public:
	static constexpr IdType TypeId = "ICameraManager";

public:
	virtual int cameraCount() = 0;
	virtual GameObjectRef camera(int index) = 0;
	virtual GameObjectProxyRef mainCamera() = 0;
	virtual void addCamera(const GameObjectRef &aCamera) = 0;
	virtual void setMainCamera(const GameObjectRef &aCamera) = 0;
	virtual void removeCamera(const GameObjectRef &aCamera) = 0;

	virtual void render() = 0;
};
} // namespace engine
