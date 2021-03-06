#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/GameObjects/IGameObject.h"
#include "Core/GameObjects/IGameObjectData.h"
#include "Core/Components/IComponent.h"
#include "Engine/Components/ComponentObject.h"
#include "Engine/Components/ComponentFactory.h"
#include <map>

#pragma warning( disable : 4250 )
namespace engine  {

//=============================================================================
// CLASS GameObjectBase
//=============================================================================
class GameObjectBase
	: virtual public IGameObject
	, public ComponentObject<IGameObject, ComponentFactory>
{
public:
	virtual void onSpawn(const physx::PxTransform &aPose) override {}
	virtual void onUnspawn() override {}

	virtual const char *debugName() const override;
};

//=============================================================================
// CLASS GameObjectWithNoData
//=============================================================================
class GameObjectWithNoData: public IGameObjectData
{
public:
	void load() {}
};


//=============================================================================
// CLASS Actor
//=============================================================================
template<class TDerived, class TDataType = GameObjectWithNoData, class TParent=GameObjectBase>
class GameObject: public TParent
{
public:
	GameObject(const GameObjectDataRef &aDataRef)
		: _data(std::static_pointer_cast<TDataType>(aDataRef))
	{}

	virtual ~GameObject() {}

public:
	using DataRef = std::shared_ptr<TDataType>;

public:
	//-------------------------------------------------------------------------
	//
	static GameObjectRef createInstance(const GameObjectDataRef &aDataRef)
	{
		std::shared_ptr<TDerived> wGameObject = std::make_shared<TDerived>(aDataRef);
		wGameObject->setRef(wGameObject);
		return wGameObject;
	}

	//-------------------------------------------------------------------------
	//
	static std::shared_ptr<IGameObjectData> loadData()
	{
		std::shared_ptr<TDataType> data = std::make_shared<TDataType>();
		data->load();
		return data;
	}

	//-------------------------------------------------------------------------
	//
	virtual IdType typeId() const override
	{
		return TDerived::TypeId;
	}

	//-------------------------------------------------------------------------
	//
	GameObjectRef ref() override
	{
		return _ref.lock();
	}

protected:
	//-------------------------------------------------------------------------
	//
	void setRef(const GameObjectRef &aRef)
	{
		_ref = aRef;
	}

protected:
	std::shared_ptr<TDataType> _data;
	GameObjectWeakRef _ref;
};

} // namespace engine
