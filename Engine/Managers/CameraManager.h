#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/Components/IComponent.h"
#include "Core/GameManagers/ICameraManager.h"
#include "Core/GameObjects/IGameObject.h"
#include "Engine/Game/GameManager.h"
#include <vector>

namespace engine {


//=============================================================================
// CLASS CameraManager
//=============================================================================
class CameraManager
	: public GameManager<CameraManager>
	, public ICameraManager
{
public:
	static constexpr IdType TypeId = "CameraManager";
	static constexpr IdType Interfaces[] = {
		ICameraManager::TypeId
	};

public: // ICameraManager
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
} // namespace engine
