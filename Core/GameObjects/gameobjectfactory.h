#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/GameObjects/IGameObjectData.h"
#include "Core/GameObjects/IGameObject.h"

//=============================================================================
// CLASS GameObjectFactory
//=============================================================================
class GameObjectFactory
{
public:
	typedef IGameObject::IdType GameObjectId;
	typedef IGameObject* (*CreateInstanceProc)(const IGameObjectDataRef &aDataRef);
	typedef IGameObjectData* (*CreateDataProc)();

public:
	static void registerGameObjectType(const GameObjectId &aGameObjectID, CreateInstanceProc aCreateGameObjectProc, CreateDataProc aCreateGameObjectDataProc);
	static void unregisterGameObjectType(const GameObjectId &aGameObjectID);

	static GameObjectRef createInstance(const GameObjectId &aGameObjectID);
};

//=============================================================================
// CLASS RegisterGameObjectType<T>
//=============================================================================
template<class T>
class RegisterGameObjectType
{
public:
	RegisterGameObjectType()
	{
		GameObjectFactory::registerGameObjectType(T::TypeId(), &T::createInstance, &T::loadData);
	}

	~RegisterGameObjectType()
	{
		GameObjectFactory::unregisterGameObjectType(T::TypeId());
	}
};
