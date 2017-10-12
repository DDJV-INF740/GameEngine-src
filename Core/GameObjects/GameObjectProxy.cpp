#include "Precompiled.h"
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "GameObjectProxy.h"
#include <string>

namespace engine
{

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

IdType GameObjectProxy::typeId() const 
{
	GameObjectRef wProxy = proxy();
	return wProxy == nullptr ? TypeId : wProxy->typeId();
}

std::shared_ptr<IComponent> GameObjectProxy::getComponent(IdType type )
{
	GameObjectRef wProxy = proxy();
	return wProxy == nullptr ? nullptr : wProxy->getComponent(type);
}

std::shared_ptr<IComponent> GameObjectProxy::createComponent(IdType type )
{
	GameObjectRef wProxy = proxy();
	return wProxy == nullptr ? nullptr : wProxy->createComponent(type);
}

void GameObjectProxy::removeComponent(IdType type )
{
	GameObjectRef wProxy = proxy();
	if (wProxy != nullptr)
	{
		wProxy->removeComponent(type);
	}
}

std::shared_ptr<IComponentInterface> GameObjectProxy::getInterface(const IdType &type)
{
	GameObjectRef wProxy = proxy();
	return wProxy == nullptr ? nullptr : wProxy->getInterface(type);
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

} // namespace engine
