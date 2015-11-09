#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include <memory>

namespace engine
{
//=============================================================================
// INTERFACE IGameObjectData
//=============================================================================
// IGameObjectData is used to share read-only data across multiple GameObjects
// of the same type.
class IGameObjectData
{
private:
	IGameObjectData(const IGameObjectData&) = delete;
	IGameObjectData& operator=(const IGameObjectData&) = delete;
	IGameObjectData& operator=(const IGameObjectData&&) = delete;

public:
	IGameObjectData() = default;
	virtual ~IGameObjectData() = default;
};

//=============================================================================
// TYPE DEFINITION
//=============================================================================
using GameObjectDataRef = std::shared_ptr<IGameObjectData>;

} // namespace engine
