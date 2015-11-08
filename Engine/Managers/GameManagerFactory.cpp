//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Precompiled.h"
#include "GameManagerFactory.h"
#include <map>

namespace engine {

//=============================================================================
// CLASS GameManagerFactory
//=============================================================================
GameManagerFactory& GameManagerFactory::Instance()
{
	static GameManagerFactory sInstance;
	return sInstance;
}


} // namespace engine
