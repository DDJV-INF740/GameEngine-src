#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include <memory>
#include <map>

//=============================================================================
// CLASS ObjectFactory
//=============================================================================
template<class TBase>
class ObjectFactory
{
public:
	typedef const char* IdType;
	typedef std::shared_ptr<TBase> (*InjectionMethod)();

	//=========================================================================
	// CLASS NewInjectionMethod
	//=========================================================================
	template<class T>
	class NewInjectionMethod
	{
	public:
		static std::shared_ptr<TBase> resolve()
		{
			return std::shared_ptr<TBase>(new T());
		}
	};

public:
	template<class T>
	void registerType()
	{
		registerType<T>(NewInjectionMethod<T>::resolve);
	}

	template<class T>
	void registerType(InjectionMethod iInjectionMethod)
	{
		_registeredTypes[T::TypeId()] = iInjectionMethod;
	}

	template<class T>
	void unregisterType()
	{
		auto wFound = _registeredTypes.find(T::TypeId());
		if (wFound != _registeredTypes.end())
		{
			_registeredTypes.erase(wFound);
		}
	}

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
	std::map<IdType, InjectionMethod> _registeredTypes;
};


