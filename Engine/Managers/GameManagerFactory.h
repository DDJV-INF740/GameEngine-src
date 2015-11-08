#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================

#include "Core/Game/IGameManager.h"
#include "Core/Factories/ObjectFactory.h"
#include <typeinfo>

namespace engine {

//=============================================================================
// CLASS GameManagerFactory
//=============================================================================
class GameManagerFactory: public ObjectFactory<IGameManager>
{
public:
	static GameManagerFactory& Instance();
};

//=============================================================================
// CLASS RegisterGameManagerType<T>
//=============================================================================
template<class T>
class RegisterGameManagerType
{
public:
	RegisterGameManagerType()
	{
		GameManagerFactory::Instance().registerType<T>();
	}

	~RegisterGameManagerType()
	{
		GameManagerFactory::Instance().unregisterType<T>();
	}
};
} // namespace engine
