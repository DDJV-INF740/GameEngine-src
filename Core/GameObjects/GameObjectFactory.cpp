//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Precompiled.h"
#include "GameObjectFactory.h"
#include <map>

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
typedef std::map<GameObjectFactory::GameObjectId, GameObjectFactoryEntry> GameObjectFactoryRegistry;

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

	IGameObjectDataRef dataRef = found->second._data.lock();
	if (!dataRef)
	{
		dataRef.reset(found->second._createGameObjectDataProc());
		found->second._data = dataRef;
	}
	
	GameObjectRef newGameObject(found->second._createGameObjectProc(dataRef));
	newGameObject->setRef(newGameObject);
	return newGameObject;
}

