#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include <memory>
#include <map>
#include "../StaticAsserts.h"

namespace engine
{

//=============================================================================
// CLASS ObjectFactory
//=============================================================================
// This class can be used to construct new objects based on a registered ID.
// For instance, call registerType at some point to associated your type with
// an ID, and later call resolve to construct a new object based on an ID. The
// allocation method can be provided when registering - by default a new
// instance is created each time resolve() is called.
template<class TBase>
class ObjectFactory
{
public:
	using IdType = const char*;
	using AllocationStrategy = std::shared_ptr<TBase>(*)();

	//=========================================================================
	// CLASS AllocateInstanceWithNewStrategy
	//=========================================================================
	// Default allocation, using new
	template<class T>
	class AllocateInstanceWithNewStrategy
	{
	public:
		static std::shared_ptr<TBase> resolve()
		{
			return std::make_shared<T>();
		}
	};

private:
	template<class T>
	void assert_has_typeid_method()
	{
		static_assert(_internal::has_typeid_static_method<T>::value, "The type provided does not have a TypeId() method");
	}

public:
	ObjectFactory() = default;
	~ObjectFactory() = default;

public:
	//-------------------------------------------------------------------------
	// Register a type with the default allocator
	// The type must have a static method called TypeId() which returns
	// the ID of this type.
	template<class T>
	void registerType()
	{
		assert_has_typeid_method<T>();
		registerType<T>(AllocateInstanceWithNewStrategy<T>::resolve);
	}

	//-------------------------------------------------------------------------
	// Register a type with a custom allocator
	// The type must have a static method called TypeId() which returns
	// the ID of this type.
	template<class T>
	void registerType(AllocationStrategy iAllocationStrategy)
	{
		assert_has_typeid_method<T>();
		_registeredTypes[T::TypeId()] = iAllocationStrategy;
	}

	//-------------------------------------------------------------------------
	// Unregisters a previously registered type
	template<class T>
	void unregisterType()
	{
		assert_has_typeid_method<T>();
		auto wFound = _registeredTypes.find(T::TypeId());
		if (wFound != _registeredTypes.end())
		{
			_registeredTypes.erase(wFound);
		}
	}

	//-------------------------------------------------------------------------
	// Obtains an instance of the specified type from the configured allocator
	template<class T>
	std::shared_ptr<T> resolve()
	{
		assert_has_typeid_method<T>();
		auto wFound = _registeredTypes.find(T::TypeId());
		if (wFound != _registeredTypes.end())
		{
			return wFound->second().dynamic_pointer_cast<T>();
		}

		return std::shared_ptr<T>();
	}

	//-------------------------------------------------------------------------
	// Obtains an instance of the specified type from the configured allocator
	std::shared_ptr<TBase> resolve(IdType iTypeId)
	{
		auto wFound = _registeredTypes.find(iTypeId);
		if (wFound != _registeredTypes.end())
		{
			return wFound->second();
		}

		return std::shared_ptr<TBase>();
	}

	void reset()
	{
		_registeredTypes.clear();
	}

private:
	std::map<IdType, AllocationStrategy> _registeredTypes;

private:

	ObjectFactory(const ObjectFactory &) = delete;
	ObjectFactory& operator=(const ObjectFactory&) = delete;
	ObjectFactory& operator=(const ObjectFactory&&) = delete;
};



} // game namespace
