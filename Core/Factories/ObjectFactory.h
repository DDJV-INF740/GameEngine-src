#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include <memory>
#include <map>

namespace engine
{

	namespace _internal
	{
		template <typename T>
		class has_typeid_static_method
		{
			typedef char one;
			typedef long two;

			template <typename C> static one test(decltype(C::TypeId()));
			template <typename C> static two test(...);

		public:
			enum { value = sizeof(test<T>("")) == sizeof(one) };
		};
	}

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

	public:
		//-------------------------------------------------------------------------
		// Register a type with the default allocator
		// The type must have a static method called TypeId() which returns
		// the ID of this type.
		template<class T>
		void registerType()
		{
			static_assert(_internal::has_typeid_static_method<T>::value, "has no operator");
			registerType<T>(AllocateInstanceWithNewStrategy<T>::resolve);
		}

		//-------------------------------------------------------------------------
		// Register a type with a custom allocator
		// The type must have a static method called TypeId() which returns
		// the ID of this type.
		template<class T>
		void registerType(AllocationStrategy iAllocationStrategy)
		{
			_registeredTypes[T::TypeId()] = iAllocationStrategy;
		}

		//-------------------------------------------------------------------------
		// Unregisters a previously registered type
		template<class T>
		void unregisterType()
		{
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

	private:
		std::map<IdType, AllocationStrategy> _registeredTypes;
	};



} // game namespace
