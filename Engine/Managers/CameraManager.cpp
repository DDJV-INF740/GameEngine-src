#include "Precompiled.h"
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "CameraManager.h"
#include "Core/GameObjects/IGameObject.h"
#include "Core/Components/IRenderViewInterface.h"
#include "Core/GameObjects/GameObjectProxy.h"

#include <algorithm>

class CameraManager::CameraManagerImp
{
public:
	CameraManagerImp()
		: _cameras()
		, _mainCamera(new GameObjectProxy)
	{}

public:
	std::vector<GameObjectRef> _cameras;
	GameObjectProxyRef _mainCamera;
};

//=============================================================================
// CLASS CameraManager
//=============================================================================
//-----------------------------------------------------------------------------
//
int CameraManager::cameraCount()
{
	return (int)_imp->_cameras.size();
}

//-----------------------------------------------------------------------------
//
GameObjectRef CameraManager::camera( int index )
{
	return _imp->_cameras[index];
}

//-----------------------------------------------------------------------------
//
GameObjectProxyRef CameraManager::mainCamera()
{
	return  _imp->_mainCamera;
}

//-----------------------------------------------------------------------------
//
void CameraManager::addCamera( const GameObjectRef &aCamera )
{
	_imp->_cameras.push_back(aCamera);
	if (_imp->_mainCamera->proxy() == nullptr)
	{
		_imp->_mainCamera->setProxy(aCamera);
	}
}

//-----------------------------------------------------------------------------
//
void CameraManager::setMainCamera( const GameObjectRef &aCamera )
{
	removeCamera(aCamera);
	_imp->_cameras.insert(_imp->_cameras.begin(), aCamera);
	_imp->_mainCamera->setProxy(aCamera);
}

//-----------------------------------------------------------------------------
//
void CameraManager::removeCamera( const GameObjectRef &aCamera )
{
	auto wFound = std::find(_imp->_cameras.begin(), _imp->_cameras.end(), aCamera);
	if (wFound != _imp->_cameras.end())
	{
		_imp->_cameras.erase(wFound);
	}

	if (_imp->_mainCamera->proxy() == nullptr && !_imp->_cameras.empty())
	{
		_imp->_mainCamera->setProxy(_imp->_cameras[0]);
	}
}

//-----------------------------------------------------------------------------
//
void CameraManager::render()
{
	for (auto iter = _imp->_cameras.rbegin(); iter != _imp->_cameras.rend(); ++iter)
	{
		(*iter)->as<IRenderViewInterface>()->renderView();
	}
}

IComponent::IdType CameraManager::TypeId()
{
	return "CameraManager";
}

CameraManager::CameraManager()
	: _imp(new CameraManagerImp)
{}

CameraManager::~CameraManager()
{
	delete _imp;
}

#include "Engine/Managers/GameManagerFactory.h"
RegisterGameManagerType<CameraManager> gCameraManagerRegistration;
