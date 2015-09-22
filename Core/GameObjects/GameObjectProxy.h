#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "IGameObject.h"

//=============================================================================
// CLASS GameObjectProxy
//=============================================================================
class GameObjectProxy : public IGameObject
{
public:
	virtual void onSpawn(const physx::PxTransform &aPose) override {}
	virtual void onUnspawn() override {}
	virtual IdType typeId() const override;

	virtual const char *debugName() const override;

	virtual std::shared_ptr<IComponent> getComponentType(ComponentIdType type) override;
	virtual std::shared_ptr<IComponent> addComponentType(ComponentIdType type) override;
	virtual void removeComponentType(ComponentIdType type) override;
	virtual std::shared_ptr<IComponentInterface> getInterfaceType(InterfaceIdType type) override;
	virtual std::shared_ptr<IComponentInterface> addInterfaceType(InterfaceIdType iType, const std::shared_ptr<IComponentInterface> &iInterface) override;
	virtual void removeInterfaceType(InterfaceIdType iType) override;
	virtual void removeAllComponents() override;

	virtual GameObjectRef ref() override;
	virtual void setRef(const GameObjectRef &aRef) override {}


public:
	void setProxy(const GameObjectRef iIGameObject);
	GameObjectRef proxy() const;

private:
	GameObjectWeakRef _proxy;
};

typedef std::shared_ptr<GameObjectProxy> GameObjectProxyRef;
typedef std::weak_ptr<GameObjectProxy> GameObjectProxyWeakRef;

