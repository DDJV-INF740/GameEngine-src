#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/Game/IGameInterface.h"
#include "Core/GameObjects/IGameObject.h"
#include "Core/GameObjects/GameObjectProxy.h"

namespace engine
{

//=============================================================================
// CLASS IPlayerManager
//=============================================================================
class ICameraManager: virtual public IGameInterface
{
public:
	static IdType TypeId();

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
