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
	, public ComponentObject<IGameObject, IComponent, IComponentInterface, ComponentFactory>
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
	GameObject(const IGameObjectDataRef &aDataRef)
		: _data(std::static_pointer_cast<TDataType>(aDataRef))
	{}

	virtual ~GameObject() {}

public:
	typedef std::shared_ptr<TDataType> DataRef;

public:
	//-------------------------------------------------------------------------
	//
	static IGameObject* createInstance(const IGameObjectDataRef &aDataRef)
	{
		IGameObject *wGameObject = new TDerived(aDataRef);
		return wGameObject;
	}

	//-------------------------------------------------------------------------
	//
	static IGameObjectData* loadData()
	{
		TDataType *data = new TDataType;
		data->load();
		return data;
	}

	//-------------------------------------------------------------------------
	//
	virtual typename TParent::IdType typeId() const override
	{
		return TDerived::TypeId();
	}

	//-------------------------------------------------------------------------
	//
	void setRef(const GameObjectRef &aRef) override
	{
		_ref = aRef;
	}

	//-------------------------------------------------------------------------
	//
	GameObjectRef ref() override
	{
		return _ref.lock();
	}

protected:
	std::shared_ptr<TDataType> _data;
	GameObjectWeakRef _ref;
};

} // namespace engine
