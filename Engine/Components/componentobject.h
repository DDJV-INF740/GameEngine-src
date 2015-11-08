#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/Components/IComponentObject.h"
#include <map>

namespace engine
{

//=============================================================================
// CLASS ComponentObject<TObject, TComponent, TComponentInterface, TComponentFactory>
// Template parameters:
//		- TObject:				The object on which components will be attached and detached
//		- TComponent:			The base class of any component
//		- TComponentInterface:	The base class of any component interface
//		- TComponentFactory:	The factory to use to create components
//=============================================================================
template<class TObject, class TComponent, class TComponentInterface, class TComponentFactory>
class ComponentObject: virtual public IComponentObject<TComponent, TComponentInterface>
{
public:
	virtual ~ComponentObject();
	virtual void removeAllComponents() override;

public:
	virtual std::shared_ptr<TComponent> getComponentType(ComponentIdType type) override;
	virtual std::shared_ptr<TComponent> addComponentType(ComponentIdType type) override;
	virtual void removeComponentType(ComponentIdType type) override;
	virtual std::shared_ptr<TComponentInterface> getInterfaceType(InterfaceIdType type) override;
	virtual std::shared_ptr<TComponentInterface> addInterfaceType(InterfaceIdType iType, const std::shared_ptr<TComponentInterface> &iInterface) override;
	virtual void removeInterfaceType(InterfaceIdType iType) override;

private:
	std::map<ComponentIdType, std::shared_ptr<TComponent>> _components;
	std::map<InterfaceIdType, std::shared_ptr<TComponentInterface>> _interfaces;
};
} // namespace engine

//=============================================================================
// TEMPLATE IMPLEMENTATION
//=============================================================================
#include "ComponentObject.inline.h"
