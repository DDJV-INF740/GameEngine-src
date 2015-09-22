#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "ComponentObject.h"

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
	_interfaces.clear();

	for (auto iter = _components.begin(); iter != _components.end(); ++iter)
	{
		iter->second->onDetached(dynamic_cast<TObject*>(this)->ref());
	}
	_components.clear();
}

//-----------------------------------------------------------------------------
//
template<class TObject, class TComponent, class TComponentInterface, class TComponentFactory>
std::shared_ptr<TComponent> ComponentObject<TObject, TComponent, TComponentInterface, TComponentFactory>::getComponentType(ComponentIdType type)
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
std::shared_ptr<TComponent> ComponentObject<TObject, TComponent, TComponentInterface, TComponentFactory>::addComponentType(ComponentIdType type)
{
	ASSERT(getComponentType(type) == nullptr);
	std::shared_ptr<TComponent> wComponent = TComponentFactory::Instance().resolve(type);
	_components[type] = wComponent;

	InterfaceIdType *wInterfaces = wComponent->interfaces();
	while (*wInterfaces != TComponentInterface::NullId)
	{
		addInterfaceType(*wInterfaces, std::dynamic_pointer_cast<TComponentInterface>(wComponent));
		++wInterfaces;
	}

	wComponent->onAttached(dynamic_cast<TObject*>(this)->ref());

	return wComponent;
}

//-----------------------------------------------------------------------------
//
template<class TObject, class TComponent, class TComponentInterface, class TComponentFactory>
void ComponentObject<TObject, TComponent, TComponentInterface, TComponentFactory>::removeComponentType(ComponentIdType type)
{
	auto wComponentFound = _components.find(type);
	ASSERT(wComponentFound != _components.end());
	std::shared_ptr<TComponent> component = wComponentFound->second;
	_components.erase(wComponentFound);
	component->onDetached(dynamic_cast<TObject*>(this)->ref());
	InterfaceIdType *wInterfaces = component->interfaces();
	while (*wInterfaces != TComponentInterface::NullId)
	{
		removeInterfaceType(*wInterfaces);
		++wInterfaces;
	}
}

//-----------------------------------------------------------------------------
//
template<class TObject, class TComponent, class TComponentInterface, class TComponentFactory>
std::shared_ptr<TComponentInterface> ComponentObject<TObject, TComponent, TComponentInterface, TComponentFactory>::getInterfaceType(InterfaceIdType type)
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
std::shared_ptr<TComponentInterface> ComponentObject<TObject, TComponent, TComponentInterface, TComponentFactory>::addInterfaceType(InterfaceIdType iType, const std::shared_ptr<TComponentInterface> &iInterface)
{
	ASSERT(getInterfaceType(iType) == nullptr);
	ASSERT(iInterface != nullptr);

	_interfaces[iType] = iInterface;
	return iInterface;
}

//-----------------------------------------------------------------------------
//
template<class TObject, class TComponent, class TComponentInterface, class TComponentFactory>
void ComponentObject<TObject, TComponent, TComponentInterface, TComponentFactory>::removeInterfaceType(InterfaceIdType iType)
{
	auto wFound = _interfaces.find(iType);
	ASSERT(wFound != _interfaces.end());
	_interfaces.erase(wFound);
}

