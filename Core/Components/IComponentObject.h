#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include <memory>

namespace engine
{
	
//=============================================================================
// INTERFACE IComponentObject
//=============================================================================
// An IComponentObject is an object that can be decorated by other objects 
// (components).  Each component provides implementation to one or many interfaces
// which can then be accessed using ->as<>() on the ComponentObject.
//
// Components can be added and removed at runtime.
//
// Components use a name (typeid) for identification, making it
// possible to request a component based on its name rather than its type.
template<class TComponent, class TComponentInterface>
class IComponentObject
{
public:
	virtual ~IComponentObject() = default;

public:
	using ComponentIdType = typename TComponent::IdType;
	using InterfaceIdType = typename TComponentInterface::IdType;

public:
	// Get an existing component by type identifier
	virtual std::shared_ptr<TComponent> getComponent(ComponentIdType type) = 0;

	// Add a new component to this object
	virtual std::shared_ptr<TComponent> createComponent(ComponentIdType type) = 0;

	// remove an existing component
	virtual void removeComponent(ComponentIdType type) = 0;

	// removes all the components on this object
	virtual void removeAllComponents() = 0;

	// returns an existing component interface
	virtual std::shared_ptr<TComponentInterface> getInterface(InterfaceIdType type) = 0;

public:

	// returns an existing component matching type T
	template<class T>
	std::shared_ptr<T> component()
	{
		static_assert(std::is_base_of<TComponent, T>::value, "T must be a subclass of TComponent");

		return std::dynamic_pointer_cast<T>(getComponent(T::TypeId()));
	}

	// decorate this object with a new component of type T
	template<class T>
	std::shared_ptr<T> createComponent()
	{
		static_assert(std::is_base_of<TComponent, T>::value, "T must be a subclass of TComponent");

		return std::dynamic_pointer_cast<T>(createComponent(T::TypeId()));
	}

	// creates a component only if it does not already exist
	template<class T>
	std::shared_ptr<T> ensureComponent()
	{
		static_assert(std::is_base_of<TComponent, T>::value, "T must be a subclass of TComponent");

		std::shared_ptr<T> c = component<T>();
		if (c == nullptr)
			c = createComponent<T>();

		return c;
	}

	// removes the component of type T from this object
	template<class T>
	void removeComponent()
	{
		static_assert(std::is_base_of<TComponent, T>::value, "T must be a subclass of TComponent");

		removeComponent(T::TypeId());
	}

	// returns the component interface T if found on this object
	template<class T>
	std::shared_ptr<T> as()
	{	
		static_assert(std::is_base_of<TComponentInterface, T>::value, "T must be a subclass of TComponent");

		return std::dynamic_pointer_cast<T>(getInterface(T::TypeId()));
	}
};

} // namespace engine
