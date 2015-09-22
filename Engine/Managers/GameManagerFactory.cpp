//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Precompiled.h"
#include "GameManagerFactory.h"
#include <map>

//=============================================================================
// CLASS GameManagerFactory
//=============================================================================
GameManagerFactory& GameManagerFactory::Instance()
{
	static GameManagerFactory sInstance;
	return sInstance;
}


