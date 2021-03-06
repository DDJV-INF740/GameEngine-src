#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "ComponentObject.h"
#include <Core/StaticAsserts.h>

namespace engine
{

//=============================================================================
// CLASS ComponentObject<TObject, TComponentFactory>
//=============================================================================

//-----------------------------------------------------------------------------
//
template<class TObject, class TComponentFactory>
ComponentObject<TObject, TComponentFactory>::~ComponentObject()
{
	removeAllComponents();
}

//-----------------------------------------------------------------------------
//
template<class TObject, class TComponentFactory>
void ComponentObject<TObject, TComponentFactory>::removeAllComponents()
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
template<class TObject, class TComponentFactory>
std::shared_ptr<IComponent> ComponentObject<TObject, TComponentFactory>::getComponent(IdType type)
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
template<class TObject, class TComponentFactory>
std::shared_ptr<IComponent> ComponentObject<TObject, TComponentFactory>::createComponent(IdType type)
{
	ASSERT(getComponent(type) == nullptr);
	std::shared_ptr<IComponent> wComponent = TComponentFactory::Instance().resolve(type);
	_components[type] = wComponent;
	LOG_INFO("[go:0x%p] + component %s (0x%p)", this, type.toString().c_str(), wComponent.get());

	for (IdType wInterface : wComponent->interfaces())
	{
		registerInterface(wInterface, std::dynamic_pointer_cast<IComponentInterface>(wComponent));
		LOG_INFO("[go:0x%p]     + interface %s (0x%p)", this, wInterface.toString().c_str(), wComponent.get());
	}

	wComponent->onAttached(dynamic_cast<TObject*>(this)->ref());

	return wComponent;
}

//-----------------------------------------------------------------------------
//
template<class TObject, class TComponentFactory>
void ComponentObject<TObject, TComponentFactory>::removeComponent(IdType type)
{
	LOG_INFO("[go:0x%p] - component %s", this, type.toString().c_str());
	auto wComponentFound = _components.find(type);
	ASSERT(wComponentFound != _components.end());
	std::shared_ptr<IComponent> component = wComponentFound->second;
	_components.erase(wComponentFound);
	component->onDetached(dynamic_cast<TObject*>(this)->ref());
	for (IdType wInterface : component->interfaces())
	{
		LOG_INFO("[go:0x%p]     - interface %s", this, wInterface.toString().c_str());
		unregisterInterface(wInterface);
	}
}

//-----------------------------------------------------------------------------
//
template<class TObject, class TComponentFactory>
std::shared_ptr<IComponentInterface> ComponentObject<TObject, TComponentFactory>::getInterface(const IdType &type)
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
template<class TObject, class TComponentFactory>
std::shared_ptr<IComponentInterface> ComponentObject<TObject, TComponentFactory>::registerInterface(const IdType &iType, const std::shared_ptr<IComponentInterface> &iInterface)
{
	ASSERT(getInterface(iType) == nullptr);
	ASSERT(iInterface != nullptr);

	_interfaces[iType] = iInterface;
	return iInterface;
}

//-----------------------------------------------------------------------------
//
template<class TObject, class TComponentFactory>
void ComponentObject<TObject, TComponentFactory>::unregisterInterface(IdType iType)
{
	auto wFound = _interfaces.find(iType);
	ASSERT(wFound != _interfaces.end());
	_interfaces.erase(wFound);
}

//-----------------------------------------------------------------------------
//
template<class TObject, class TComponentFactory>
void ComponentObject<TObject, TComponentFactory>::assert_has_ref_method()
{
	static_assert(_internal::has_ref_method<TObject>::value, "Object must have a ref() method that returns a shared_ptr of itself");
}


} // namespace engine
