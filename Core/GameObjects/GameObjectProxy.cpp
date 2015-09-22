#include "Precompiled.h"
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "GameObjectProxy.h"
#include <string>

//=============================================================================
// CLASS GameObjectProxy
//=============================================================================

void GameObjectProxy::setProxy( const GameObjectRef iIGameObject )
{
	_proxy = iIGameObject;
}

const char * GameObjectProxy::debugName() const
{
	GameObjectRef wGameObject = proxy();
	if (wGameObject != nullptr)
	{
		return (std::string(wGameObject->debugName()) + std::string(" [BY PROXY]")).c_str();
	}
	else
	{
		return "NULL PROXY";
	}
}

GameObjectRef GameObjectProxy::proxy() const
{
	return _proxy.lock();
}

IGameObject::IdType GameObjectProxy::typeId() const 
{
	GameObjectRef wProxy = proxy();
	return wProxy == nullptr ? "GameObjectProxy" : wProxy->typeId();
}

std::shared_ptr<IComponent> GameObjectProxy::getComponentType( ComponentIdType type )
{
	GameObjectRef wProxy = proxy();
	return wProxy == nullptr ? nullptr : wProxy->getComponentType(type);
}

std::shared_ptr<IComponent> GameObjectProxy::addComponentType( ComponentIdType type )
{
	GameObjectRef wProxy = proxy();
	return wProxy == nullptr ? nullptr : wProxy->addComponentType(type);
}

void GameObjectProxy::removeComponentType( ComponentIdType type )
{
	GameObjectRef wProxy = proxy();
	if (wProxy != nullptr)
	{
		wProxy->removeComponentType(type);
	}
}

std::shared_ptr<IComponentInterface> GameObjectProxy::getInterfaceType( InterfaceIdType type )
{
	GameObjectRef wProxy = proxy();
	return wProxy == nullptr ? nullptr : wProxy->getInterfaceType(type);
}

std::shared_ptr<IComponentInterface> GameObjectProxy::addInterfaceType( InterfaceIdType iType, const std::shared_ptr<IComponentInterface> &iInterface )
{
	GameObjectRef wProxy = proxy();
	return wProxy == nullptr ? nullptr : wProxy->addInterfaceType(iType, iInterface);
}

void GameObjectProxy::removeInterfaceType( InterfaceIdType iType )
{
	GameObjectRef wProxy = proxy();
	if (wProxy != nullptr)
	{
		wProxy->removeInterfaceType(iType);
	}
}

void GameObjectProxy::removeAllComponents()
{
	GameObjectRef wProxy = proxy();
	if (wProxy != nullptr)
	{
		wProxy->removeAllComponents();
	}
}

GameObjectRef GameObjectProxy::ref()
{
	GameObjectRef wProxy = proxy();
	return wProxy == nullptr ? nullptr : wProxy->ref();
}

