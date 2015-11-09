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
private:
	using Super = IComponentObject<TComponent, TComponentInterface>;
public:
	virtual ~ComponentObject();
	virtual void removeAllComponents() override;

public:
	virtual std::shared_ptr<TComponent> getComponent(ComponentIdType type) override;
	virtual std::shared_ptr<TComponent> createComponent(ComponentIdType type) override;

	template<class T>
	std::shared_ptr<T> createComponent()
	{
		return Super::createComponent<T>();
	}

	virtual void removeComponent(ComponentIdType type) override;
	virtual std::shared_ptr<TComponentInterface> getInterface(InterfaceIdType type) override;

private:
	virtual std::shared_ptr<TComponentInterface> registerInterface(InterfaceIdType iType, const std::shared_ptr<TComponentInterface> &iInterface);
	virtual void unregisterInterface(InterfaceIdType iType);

public:
	ComponentObject()
	{
		assert_has_ref_method();
	}

private:
	void assert_has_ref_method();

private:
	std::map<ComponentIdType, std::shared_ptr<TComponent>> _components;
	std::map<InterfaceIdType, std::shared_ptr<TComponentInterface>> _interfaces;

private:
	ComponentObject(const ComponentObject &) = delete;
	ComponentObject& operator=(const ComponentObject&) = delete;
	ComponentObject& operator=(const ComponentObject&&) = delete;
};
} // namespace engine

//=============================================================================
// TEMPLATE IMPLEMENTATION
//=============================================================================
#include "ComponentObject.inline.h"
