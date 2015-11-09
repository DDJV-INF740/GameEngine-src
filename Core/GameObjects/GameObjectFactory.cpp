//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Precompiled.h"
#include "GameObjectFactory.h"
#include <map>

namespace engine
{

//=============================================================================
// CLASS GameObjectFactoryEntry
//=============================================================================
struct GameObjectFactoryEntry
{
	GameObjectFactoryEntry(){}

	GameObjectFactoryEntry(GameObjectFactory::CreateInstanceProc aCreateGameObjectProc, GameObjectFactory::CreateDataProc aCreateGameObjectDataProc)
		: _createGameObjectProc(aCreateGameObjectProc)
		, _createGameObjectDataProc(aCreateGameObjectDataProc)
	{}

	GameObjectFactory::CreateInstanceProc _createGameObjectProc;
	GameObjectFactory::CreateDataProc _createGameObjectDataProc;
	std::weak_ptr<IGameObjectData> _data;
} ;

//-----------------------------------------------------------------------------
//
using GameObjectFactoryRegistry = std::map<GameObjectFactory::GameObjectId, GameObjectFactoryEntry>;

//=============================================================================
// CLASS GameObjectFactoryRegistry
//=============================================================================
static GameObjectFactoryRegistry& GetGameObjectFactoryRegistry()
{
	static GameObjectFactoryRegistry sRegistry;
	return sRegistry;
}

//=============================================================================
// CLASS GameObjectFactory
//=============================================================================
void GameObjectFactory::registerGameObjectType(const GameObjectId &aGameObjectId, CreateInstanceProc aCreateGameObjectProc, CreateDataProc aCreateGameObjectDataProc)
{
	GameObjectFactoryRegistry &reg = GetGameObjectFactoryRegistry();
	reg[aGameObjectId] = GameObjectFactoryEntry(aCreateGameObjectProc, aCreateGameObjectDataProc);
}

//-----------------------------------------------------------------------------
//
void GameObjectFactory::unregisterGameObjectType(const GameObjectId &aGameObjectId)
{
	GameObjectFactoryRegistry &reg = GetGameObjectFactoryRegistry();
	auto found = reg.find(aGameObjectId);
	if (found != reg.end())
		reg.erase(found);
}

//-----------------------------------------------------------------------------
//
GameObjectRef GameObjectFactory::createInstance(const GameObjectId &aGameObjectId)
{
	GameObjectFactoryRegistry &reg = GetGameObjectFactoryRegistry();
	auto found = reg.find(aGameObjectId);
	if (found == reg.end())
		return nullptr;

	GameObjectDataRef dataRef = found->second._data.lock();
	if (dataRef == nullptr)
	{
		dataRef = found->second._createGameObjectDataProc();
		found->second._data = dataRef;
	}
	
	GameObjectRef newGameObject(found->second._createGameObjectProc(dataRef));
	return newGameObject;
}

//-----------------------------------------------------------------------------
//
void GameObjectFactory::reset()
{
	GameObjectFactoryRegistry &reg = GetGameObjectFactoryRegistry();
	reg.clear();
}


} // namespace engine
