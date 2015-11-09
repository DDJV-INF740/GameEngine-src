#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/Components/IComponent.h"
#include "Core/Factories/ObjectFactory.h"
#include <typeinfo>

namespace engine {

//=============================================================================
// CLASS ComponentFactory
//=============================================================================
// This class is used to create component objects based on their ID at runtime.
class ComponentFactory : public ObjectFactory<IComponent>
{
public:
	static ComponentFactory& Instance();
	~ComponentFactory() = default;

private:
	ComponentFactory() = default;
	ComponentFactory(const ComponentFactory &) = delete;
	ComponentFactory& operator=(const ComponentFactory&) = delete;
	ComponentFactory& operator=(const ComponentFactory&&) = delete;
};

//=============================================================================
// CLASS RegisterComponentType<T>
//=============================================================================
template<class T>
class RegisterComponentType
{
public:
	RegisterComponentType()
	{
		ComponentFactory::Instance().registerType<T>();
	}

	~RegisterComponentType()
	{
		ComponentFactory::Instance().unregisterType<T>();
	}
};

} // namespace engine
