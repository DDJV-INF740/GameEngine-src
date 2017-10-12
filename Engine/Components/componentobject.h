#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/Components/IComponentObject.h"
#include "Core/Components/IComponent.h"
#include "Core/Logging/Logger.h"
#include <map>

namespace engine
{
//=============================================================================
// CLASS ComponentObject<TObject, TComponentFactory>
// Template parameters:
//		- TObject:				The object on which components will be attached and detached
//		- TComponentFactory:	The factory to use to create components
//=============================================================================
template<class TObject, class TComponentFactory>
class ComponentObject: virtual public IComponentObject<IComponent, IComponentInterface>
{
private:
	using Super = IComponentObject<IComponent, IComponentInterface>;
public:
	virtual ~ComponentObject();
	virtual void removeAllComponents() override;

public:
	virtual std::shared_ptr<IComponent> getComponent(IdType type) override;
	virtual std::shared_ptr<IComponent> createComponent(IdType type) override;

	template<class T>
	std::shared_ptr<T> createComponent()
	{
		return Super::createComponent<T>();
	}

	virtual void removeComponent(IdType type) override;
	virtual std::shared_ptr<IComponentInterface> getInterface(const IdType &type) override;

private:
	virtual std::shared_ptr<IComponentInterface> registerInterface(const IdType &iType, const std::shared_ptr<IComponentInterface> &iInterface);
	virtual void unregisterInterface(IdType iType);

public:
	ComponentObject()
	{
		assert_has_ref_method();
	}

private:
	void assert_has_ref_method();

private:
	std::map<IdType, std::shared_ptr<IComponent>> _components;
	std::map<IdType, std::shared_ptr<IComponentInterface>> _interfaces;

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
