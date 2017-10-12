#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/GameObjects/IGameObjectData.h"
#include "Core/GameObjects/IGameObject.h"

namespace engine
{

//=============================================================================
// CLASS GameObjectFactory
//=============================================================================
// Factory to create GameObjects based on their ID.  GameObjects are created
// with shared data following a flyweight pattern - data is initialized once
// when the first GameObject requiring this data is initialized and reused
// for all subsequent GameObjects of the same type.  The content of the shared
// data must thus be read-only.  Textures and mesh are good candidates for
// GameObject Data.
class GameObjectFactory
{
public:
	using GameObjectId = IdType ;
	using CreateInstanceProc = GameObjectRef (*)(const GameObjectDataRef &aDataRef);
	using CreateDataProc = GameObjectDataRef (*)();

private:
	GameObjectFactory(const GameObjectFactory&) = delete;
	GameObjectFactory& operator=(const GameObjectFactory&) = delete;
	GameObjectFactory& operator=(const GameObjectFactory&&) = delete;

public:
	GameObjectFactory() = default;

	// When registering a type of GameObject, you must provide 
	//  - the object ID
	//  - a method to instantiate the GameObject which takes a GameObjectDataRef as a parameter
	//  - a method to load a new GameObjectDataRef (that will be shared across all GameObjects)
	static void registerGameObjectType(const GameObjectId &aGameObjectID, CreateInstanceProc aCreateGameObjectProc, CreateDataProc aCreateGameObjectDataProc);

	// Unregisters a previously registered GameObject type
	static void unregisterGameObjectType(const GameObjectId &aGameObjectID);

	// creates a new instance of the specified GameObject
	static GameObjectRef createInstance(const GameObjectId &aGameObjectID);

	// release all memory
	static void reset();
};

} // namespace engine
