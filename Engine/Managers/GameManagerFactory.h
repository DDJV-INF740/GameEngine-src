#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================

#include "Core/Game/IManagerComponent.h"
#include "Core/Factories/ObjectFactory.h"
#include <typeinfo>

namespace engine {

//=============================================================================
// CLASS GameManagerFactory
//=============================================================================
class GameManagerFactory: public ObjectFactory<IManagerComponent>
{
public:
	static GameManagerFactory& Instance();
};

} // namespace engine
