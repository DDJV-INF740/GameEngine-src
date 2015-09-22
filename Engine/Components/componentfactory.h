#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================

#include "Core/Components/IComponent.h"
#include "Core/Factories/ObjectFactory.h"
#include <typeinfo>

//=============================================================================
// CLASS ComponentFactory
//=============================================================================
class ComponentFactory: public ObjectFactory<IComponent>
{

public:
	static ComponentFactory& Instance();
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
