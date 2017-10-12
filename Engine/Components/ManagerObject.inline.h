#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "ComponentObject.h"
#include <Core/StaticAsserts.h>

namespace engine
{

//=============================================================================
// CLASS ManagerObject<TObject, TManagerFactory>
//=============================================================================

//-----------------------------------------------------------------------------
//
template<class TObject, class TManagerFactory>
ManagerObject<TObject, TManagerFactory>::~ManagerObject()
{
	removeAllManagers();
}

//-----------------------------------------------------------------------------
//
template<class TObject, class TManagerFactory>
void ManagerObject<TObject, TManagerFactory>::removeAllManagers()
{
	for (auto &entry : _interfaces)
	{
		LOG_INFO("[go:0x%p]    - interface %s (0x%p)", this, entry.first.toString().c_str(), entry.second.get());
	}
	_interfaces.clear();

	for (auto iter = _components.begin(); iter != _components.end(); ++iter)
	{
		LOG_INFO("[go:0x%p] - component %s (0x%p)", this, iter->first.toString().c_str(), iter->second.get());
		iter->second->onDetached(dynamic_cast<TObject*>(this)->ref());
	}
	_components.clear();
}

//-----------------------------------------------------------------------------
//
template<class TObject, class TManagerFactory>
std::shared_ptr<IManagerComponent> ManagerObject<TObject, TManagerFactory>::getManager(const IdType &type)
{
	auto wFound = _components.find(type);
	if (wFound != _components.end())
	{
		return wFound->second;
	}
	return nullptr;
}

//-----------------------------------------------------------------------------
//
template<class TObject, class TManagerFactory>
std::shared_ptr<IManagerComponent> ManagerObject<TObject, TManagerFactory>::createManager(const IdType &type)
{
	ASSERT(getManager(type) == nullptr);
	std::shared_ptr<IManagerComponent> wManager = TManagerFactory::Instance().resolve(type);
	_components[type] = wManager;
	LOG_INFO("[go:0x%p] + component %s (0x%p)", this, type.toString().c_str(), wManager.get());

	for (IdType wInterface : wManager->interfaces())
	{
		registerInterface(wInterface, std::dynamic_pointer_cast<IManager>(wManager));
		LOG_INFO("[go:0x%p]     + interface %s (0x%p)", this, wInterface.toString().c_str(), wManager.get());
	}

	wManager->onAttached(dynamic_cast<TObject*>(this)->ref());

	return wManager;
}

//-----------------------------------------------------------------------------
//
template<class TObject, class TManagerFactory>
void ManagerObject<TObject, TManagerFactory>::removeManager(IdType type)
{
	LOG_INFO("[go:0x%p] - component %s", this, type.toString().c_str());
	auto wManagerFound = _components.find(type);
	ASSERT(wManagerFound != _components.end());
	std::shared_ptr<IManagerComponent> component = wManagerFound->second;
	_components.erase(wManagerFound);
	component->onDetached(dynamic_cast<TObject*>(this)->ref());
	for (IdType wInterface : component->interfaces())
	{
		LOG_INFO("[go:0x%p]     - interface %s", this, wInterface.toString().c_str());
		unregisterInterface(wInterface);
	}
}

//-----------------------------------------------------------------------------
//
template<class TObject, class TManagerFactory>
std::shared_ptr<IManager> ManagerObject<TObject, TManagerFactory>::getInterface(const IdType &type)
{
	auto wFound = _interfaces.find(type);
	if (wFound != _interfaces.end())
	{
		return wFound->second;
	}
	return nullptr;
}

//-----------------------------------------------------------------------------
//
template<class TObject, class TManagerFactory>
std::shared_ptr<IManager> ManagerObject<TObject, TManagerFactory>::registerInterface(const IdType &iType, const std::shared_ptr<IManager> &iInterface)
{
	ASSERT(getInterface(iType) == nullptr);
	ASSERT(iInterface != nullptr);

	_interfaces[iType] = iInterface;
	return iInterface;
}

//-----------------------------------------------------------------------------
//
template<class TObject, class TManagerFactory>
void ManagerObject<TObject, TManagerFactory>::unregisterInterface(const IdType &iType)
{
	auto wFound = _interfaces.find(iType);
	ASSERT(wFound != _interfaces.end());
	_interfaces.erase(wFound);
}

//-----------------------------------------------------------------------------
//
template<class TObject, class TManagerFactory>
void ManagerObject<TObject, TManagerFactory>::assert_has_ref_method()
{
	static_assert(_internal::has_ref_method<TObject>::value, "Object must have a ref() method that returns a shared_ptr of itself");
}


} // namespace engine
