#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include <memory>
#include <Core/Game/IManager.h>
#include <Core/Game/IManagerComponent.h>
namespace engine
{

//=============================================================================
// INTERFACE IManagerObject
//=============================================================================
// An IManagerObject is an object that can be decorated by other objects 
// (components).  Each component provides implementation to one or many interfaces
// which can then be accessed using ->as<>() on the ManagerObject.
//
// Managers can be added and removed at runtime.
//
// Managers use a name (typeid) for identification, making it
// possible to request a component based on its name rather than its type.
class IManagerObject
{
public:
	virtual ~IManagerObject() = default;

public:
	// Get an existing component by type identifier
	virtual std::shared_ptr<IManagerComponent> getManager(const IdType &type) = 0;

	// Add a new manager to this object
	virtual std::shared_ptr<IManagerComponent> createManager(const IdType &type) = 0;

	// remove an existing component
	virtual void removeManager(IdType type) = 0;

	// removes all the components on this object
	virtual void removeAllManagers() = 0;

	// returns an existing component interface
	virtual std::shared_ptr<IManager> getInterface(const IdType &type) = 0;

public:

	// returns an existing component matching type T
	template<class T>
	std::shared_ptr<T> component()
	{
		static_assert(std::is_base_of<IManagerComponent, T>::value, "T must be a subclass of IManagerComponent");

		return std::dynamic_pointer_cast<T>(getManager(T::TypeId));
	}

	// decorate this object with a new component of type T
	template<class T>
	std::shared_ptr<T> createManager()
	{
		static_assert(std::is_base_of<IManagerComponent, T>::value, "T must be a subclass of IManagerComponent");

		return std::dynamic_pointer_cast<T>(createManager(T::TypeId));
	}

	// creates a component only if it does not already exist
	template<class T>
	std::shared_ptr<T> ensureManager()
	{
		static_assert(std::is_base_of<IManagerComponent, T>::value, "T must be a subclass of TManager");

		std::shared_ptr<T> c = component<T>();
		if (c == nullptr)
			c = createManager<T>();

		return c;
	}

	// removes the component of type T from this object
	template<class T>
	void removeManager()
	{
		static_assert(std::is_base_of<IManagerComponent, T>::value, "T must be a subclass of TManager");

		removeManager(T::TypeId);
	}

	// returns the component interface T if found on this object
	template<class T>
	std::shared_ptr<T> as()
	{
		static_assert(std::is_base_of<IManager, T>::value, "T must be a subclass of TManager");

		return std::dynamic_pointer_cast<T>(getInterface(T::TypeId));
	}
};

} // namespace engine
