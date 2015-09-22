#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include <memory>

//=============================================================================
// INTERFACE IComponentObject
//=============================================================================
template<class TComponent, class TComponentInterface>
class IComponentObject
{
public:
	virtual ~IComponentObject()	{}

public:
	typedef typename TComponent::IdType ComponentIdType;
	typedef typename TComponentInterface::IdType InterfaceIdType;

public:
	virtual std::shared_ptr<TComponent> getComponentType(ComponentIdType type) = 0;
	virtual std::shared_ptr<TComponent> addComponentType(ComponentIdType type) = 0;
	virtual void removeComponentType(ComponentIdType type) = 0;
	virtual std::shared_ptr<TComponentInterface> getInterfaceType(InterfaceIdType type) = 0;
	virtual std::shared_ptr<TComponentInterface> addInterfaceType(InterfaceIdType iType, const std::shared_ptr<TComponentInterface> &iInterface) = 0;
	virtual void removeInterfaceType(InterfaceIdType iType) = 0;

public:
	template<class T>
	std::shared_ptr<T> component()
	{	return dynamic_cast<T*>(getComponentType(T::TypeId())); 	}

	template<typename T>
	std::shared_ptr<T> addComponent()
	{	return std::dynamic_pointer_cast<T>(addComponentType(T::TypeId())); }

	template<class T>
	void removeComponent()
	{	removeComponentType(T::TypeId()); }

	template<class T>
	std::shared_ptr<T> as()
	{	
		return std::dynamic_pointer_cast<T>(getInterfaceType(T::TypeId()));
	}

	template<class T>
	std::shared_ptr<T> addInterface(const std::shared_ptr<T> &iInterface)
	{	return dynamic_cast<T*>(addInterfaceType(typename T::TypeId(), iInterface)); }

	template<class T>
	void removeInterface()
	{	removeInterfaceType(T::TypeId()); }

	virtual void removeAllComponents() = 0;
};

