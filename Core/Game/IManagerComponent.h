#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/Game/IManager.h"
#include <memory>

namespace engine
{

//=============================================================================
// FORWARD DECLARATIONS
//=============================================================================
class IGameEngine;
using GameEngineRef = std::shared_ptr<IGameEngine>;
using GameEngineWeakRef = std::weak_ptr<IGameEngine>;


//=============================================================================
// INTERFACE IManagerComponent
//=============================================================================
class IManagerComponent
{
public:
	virtual ~IManagerComponent() {}

public:
	using IdType = const char*;
	static IdType NullId;

public:
	virtual IManager::IdType* interfaces() = 0;
	virtual void onAttached(const GameEngineRef &iGameEngine) = 0;
	virtual void onDetached(const GameEngineRef &iGameEngine) = 0;
};
} // namespace engine
