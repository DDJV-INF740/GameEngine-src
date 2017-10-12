#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "IGameObject.h"

namespace engine
{

//=============================================================================
// CLASS GameObjectProxy
//=============================================================================
// A GameObject proxy is a wrapper around a GameObject which points to an
// actual GameObject.  The purpose of such an object is, for example, to keep
// a reference on a GameObject while allowing somebody else to change the 
// actual pointee.  A Camera could, for instance, be instructed to "follow"
// a specific GameObject - for instance, the main player.  If the main player
// dies, until he respawns, we might want to tell the camera to follow another
// object. Instead of changing the target of the camera, we can instead 
// provide a GameObjectProxy to the camera and change the pointee of this
// proxy without the camera knowing.
//
// This can also be useful for NPCs which may have a target that would change
// depending on an AI component.  The NPC's target could be a Proxy and the
// AI component could switch the target of interest without the NPC knowing.
//
// The GameObjectProxy keeps a weak reference on the actual GameObject.  If
// the actual GameObject is destroyed, the proxy() method starts returning
// nullptr.
class GameObjectProxy : public IGameObject
{
public: // INTERFACE IGameObject
	static constexpr IdType TypeId = "GameObjectProxy";

	// will never really be spawned or unspawned
	virtual void onSpawn(const physx::PxTransform &aPose) override {}

	// will never really be spawned or unspawned
	virtual void onUnspawn() override {}

	virtual GameObjectRef ref() override;

public: // INTERFACE IComponentObject
	virtual IdType typeId() const override;
	virtual const char *debugName() const override;
	virtual std::shared_ptr<IComponent> getComponent(IdType type) override;
	virtual std::shared_ptr<IComponent> createComponent(IdType type) override;
	virtual void removeComponent(IdType type) override;
	virtual void removeAllComponents() override;
	virtual std::shared_ptr<IComponentInterface> getInterface(const IdType &type) override;

public:
	void setProxy(const GameObjectRef iIGameObject);
	GameObjectRef proxy() const;

private:
	GameObjectWeakRef _proxy;
};

using GameObjectProxyRef = std::shared_ptr<GameObjectProxy>;
using GameObjectProxyWeakRef = std::weak_ptr<GameObjectProxy>;

} // namespace engine
