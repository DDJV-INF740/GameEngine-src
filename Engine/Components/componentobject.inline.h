#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "ComponentObject.h"
#include <Core/StaticAsserts.h>

namespace engine
{
//=============================================================================
// CLASS ComponentObject<TObject, TComponent, TComponentInterface, TComponentFactory>
//=============================================================================

//-----------------------------------------------------------------------------
//
template<class TObject, class TComponent, class TComponentInterface, class TComponentFactory>
ComponentObject<TObject, TComponent, TComponentInterface, TComponentFactory>::~ComponentObject()
{
	removeAllComponents();
}

//-----------------------------------------------------------------------------
//
template<class TObject, class TComponent, class TComponentInterface, class TComponentFactory>
void ComponentObject<TObject, TComponent, TComponentInterface, TComponentFactory>::removeAllComponents()
{
	for (auto &entry : _interfaces)
	{
		LOG_INFO("[go:0x%p]    - interface %s (0x%p)", this, entry.first, entry.second.get());
	}
	_interfaces.clear();

	for (auto iter = _components.begin(); iter != _components.end(); ++iter)
	{
		LOG_INFO("[go:0x%p] - component %s (0x%p)", this, iter->first, iter->second.get());
		iter->second->onDetached(dynamic_cast<TObject*>(this)->ref());
	}
	_components.clear();
}

//-----------------------------------------------------------------------------
//
template<class TObject, class TComponent, class TComponentInterface, class TComponentFactory>
std::shared_ptr<TComponent> ComponentObject<TObject, TComponent, TComponentInterface, TComponentFactory>::getComponent(ComponentIdType type)
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
template<class TObject, class TComponent, class TComponentInterface, class TComponentFactory>
std::shared_ptr<TComponent> ComponentObject<TObject, TComponent, TComponentInterface, TComponentFactory>::createComponent(ComponentIdType type)
{
	ASSERT(getComponent(type) == nullptr);
	std::shared_ptr<TComponent> wComponent = TComponentFactory::Instance().resolve(type);
	_components[type] = wComponent;
	LOG_INFO("[go:0x%p] + component %s (0x%p)", this, type, wComponent.get());

	InterfaceIdType *wInterfaces = wComponent->interfaces();
	while (*wInterfaces != TComponentInterface::NullId)
	{
		registerInterface(*wInterfaces, std::dynamic_pointer_cast<TComponentInterface>(wComponent));
		LOG_INFO("[go:0x%p]     + interface %s (0x%p)", this, *wInterfaces, wComponent.get());
		++wInterfaces;
	}

	wComponent->onAttached(dynamic_cast<TObject*>(this)->ref());

	return wComponent;
}

//-----------------------------------------------------------------------------
//
template<class TObject, class TComponent, class TComponentInterface, class TComponentFactory>
void ComponentObject<TObject, TComponent, TComponentInterface, TComponentFactory>::removeComponent(ComponentIdType type)
{
	LOG_INFO("[go:0x%p] - component %s", this, type);
	auto wComponentFound = _components.find(type);
	ASSERT(wComponentFound != _components.end());
	std::shared_ptr<TComponent> component = wComponentFound->second;
	_components.erase(wComponentFound);
	component->onDetached(dynamic_cast<TObject*>(this)->ref());
	InterfaceIdType *wInterfaces = component->interfaces();
	while (*wInterfaces != TComponentInterface::NullId)
	{
		LOG_INFO("[go:0x%p]     - interface %s", this, *wInterfaces);
		unregisterInterface(*wInterfaces);
		++wInterfaces;
	}
}

//-----------------------------------------------------------------------------
//
template<class TObject, class TComponent, class TComponentInterface, class TComponentFactory>
std::shared_ptr<TComponentInterface> ComponentObject<TObject, TComponent, TComponentInterface, TComponentFactory>::getInterface(InterfaceIdType type)
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
template<class TObject, class TComponent, class TComponentInterface, class TComponentFactory>
std::shared_ptr<TComponentInterface> ComponentObject<TObject, TComponent, TComponentInterface, TComponentFactory>::registerInterface(InterfaceIdType iType, const std::shared_ptr<TComponentInterface> &iInterface)
{
	ASSERT(getInterface(iType) == nullptr);
	ASSERT(iInterface != nullptr);

	_interfaces[iType] = iInterface;
	return iInterface;
}

//-----------------------------------------------------------------------------
//
template<class TObject, class TComponent, class TComponentInterface, class TComponentFactory>
void ComponentObject<TObject, TComponent, TComponentInterface, TComponentFactory>::unregisterInterface(InterfaceIdType iType)
{
	auto wFound = _interfaces.find(iType);
	ASSERT(wFound != _interfaces.end());
	_interfaces.erase(wFound);
}

//-----------------------------------------------------------------------------
//
template<class TObject, class TComponent, class TComponentInterface, class TComponentFactory>
void ComponentObject<TObject, TComponent, TComponentInterface, TComponentFactory>::assert_has_ref_method()
{
	static_assert(_internal::has_ref_method<TObject>::value, "Object must have a ref() method that returns a shared_ptr of itself");
}


} // namespace engine
