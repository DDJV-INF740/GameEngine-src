#include "Precompiled.h"
#include "Core/Components/IIAInterface.h"

#include "AIManager.h"
#include <algorithm>
#include <assert.h>

void AIManager::addComponent( IAIInterface *iAIInstance )
{
	_aiInstances.push_back(iAIInstance);
}

void AIManager::removeComponent( IAIInterface *iAIInstance )
{
	auto wFound = std::find(_aiInstances.begin(), _aiInstances.end(), iAIInstance);
	ASSERT(wFound != _aiInstances.end());
	_aiInstances.erase(wFound);
}


void AIManager::update()
{
	for (auto iter = _aiInstances.begin(); iter != _aiInstances.end(); ++iter)
	{
		(*iter)->updateAI();
	}
}

//=============================================================================
// COMPONENT REGISTRATION
//=============================================================================
#include "Engine/Managers/GameManagerFactory.h"
IComponent::IdType AIManager::TypeId() { return "AIManager"; }
static RegisterGameManagerType<AIManager> gRegisteredComponent;


