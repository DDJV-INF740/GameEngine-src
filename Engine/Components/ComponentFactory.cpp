//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Precompiled.h"
#include "ComponentFactory.h"
#include <map>

namespace engine
{

//=============================================================================
// CLASS ComponentFactory
//=============================================================================
ComponentFactory& ComponentFactory::Instance()
{
	static ComponentFactory sInstance;
	return sInstance;
}


} // namespace engine
