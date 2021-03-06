#include "Precompiled.h"
#include "Core/Components/IIAInterface.h"

#include "AIManager.h"
#include <algorithm>
#include <assert.h>

namespace engine {

void AIManager::createComponent( IAIInterface *iAIInstance )
{
	_aiInstances.emplace_back(iAIInstance);
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
} // namespace engine

