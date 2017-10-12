#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/Components/IComponentObject.h"
#include "Core/Logging/Logger.h"
#include <map>

namespace engine
{
//=============================================================================
// CLASS ManagerObject<TObject, TManagerFactory>
// Template parameters:
//		- TObject:				The object on which Managers will be attached and detached
//		- TManagerFactory:		The factory to use to create Managers
//=============================================================================
template<class TObject, class TManagerFactory>
class ManagerObject : virtual public IManagerObject
{
private:
	using Super = IManagerObject;
public:
	virtual ~ManagerObject();
	virtual void removeAllManagers() override;

public:
	virtual std::shared_ptr<IManagerComponent> getManager(const IdType &type) override;
	virtual std::shared_ptr<IManagerComponent> createManager(const IdType &type) override;

	template<class T>
	std::shared_ptr<T> createManager()
	{
		return Super::createManager<T>();
	}

	virtual void removeManager(IdType type) override;
	virtual std::shared_ptr<IManager> getInterface(const IdType &type) override;

private:
	virtual std::shared_ptr<IManager> registerInterface(const IdType &iType, const std::shared_ptr<IManager> &iInterface);
	virtual void unregisterInterface(const IdType &iType);

public:
	ManagerObject()
	{
		assert_has_ref_method();
	}

private:
	void assert_has_ref_method();

private:
	std::map<IdType, std::shared_ptr<IManagerComponent>> _components;
	std::map<IdType, std::shared_ptr<IManager>> _interfaces;

private:
	ManagerObject(const ManagerObject &) = delete;
	ManagerObject& operator=(const ManagerObject&) = delete;
	ManagerObject& operator=(const ManagerObject&&) = delete;
};
	

} // namespace engine

//=============================================================================
// TEMPLATE IMPLEMENTATION
//=============================================================================
#include "ManagerObject.inline.h"
