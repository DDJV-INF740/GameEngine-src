#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/Components/IComponent.h"
#include "Core/GameManagers/IGameCameras.h"
#include "Core/GameObjects/IGameObject.h"
#include "Engine/Game/GameComponent.h"
#include <vector>


//=============================================================================
// CLASS CameraManager
//=============================================================================
class CameraManager
	: public GameComponent<CameraManager>
	, public IGameCameras
{
public:
	static IComponent::IdType TypeId();
	static IComponentInterface::IdType* Interfaces()
	{
		static IComponentInterface::IdType sInterfaces[] = {
			IGameCameras::TypeId(),
			0
		};

		return sInterfaces;
	}

public: // IGameCameras
	virtual int cameraCount() override;
	virtual GameObjectRef camera(int index) override;
	virtual GameObjectProxyRef mainCamera() override;
	virtual void addCamera(const GameObjectRef &aCamera) override;
	virtual void setMainCamera(const GameObjectRef &aCamera) override;
	virtual void removeCamera(const GameObjectRef &aCamera) override;
	virtual void render() override;

public:
	CameraManager();
	virtual ~CameraManager();

private:
	class CameraManagerImp;
	CameraManagerImp *_imp;
};