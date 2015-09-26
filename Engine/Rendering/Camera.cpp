#include "Precompiled.h"

//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Camera.h"
#include "Engine/GameObjects/GameObject.h"
#include "Engine/Components/FollowPoseComponent.h"
#include "Core/Game/Game.h"
#include "Core/GameManagers/IGamePlayers.h"
#include "Core/Components/IPlayerInterface.h"
#include "Engine/Components/RenderViewComponent.h"
#include "Core/GameManagers/IGameCameras.h"

#define M_PI       3.14159265358979323846

using namespace physx;

//=============================================================================
// CLASS Camera
//=============================================================================
class Camera
	: virtual public ICamera
	, public GameObject<Camera>
{
public:
	//-------------------------------------------------------------------------
	//
	Camera(const IGameObjectDataRef &aDataRef)
		: GameObject(aDataRef)
	{}

	static PxTransform AdjustCameraPosition(const PxTransform &iPlayerPose)
	{
		PxVec3 cameraDist = iPlayerPose.q.rotate(PxVec3(0, 2.0f, 10.0f));
		
		PxTransform wCameraPose;
		wCameraPose.q = iPlayerPose.q * PxQuat(float(M_PI), PxVec3(0.0f, 1.0f, 0.0f)) * PxQuat(float(M_PI) / 16, PxVec3(1, 0, 0)); // for now...
		PxVec3 wFront(0, 0, 1);
		wFront = wCameraPose.q.rotate(wFront);
		wCameraPose.p = iPlayerPose.p - 10*wFront + PxVec3(0, 1, 0);
		return wCameraPose;
	}
	//-------------------------------------------------------------------------
	//
	static IdType TypeId() { return "Camera"; }

	//-------------------------------------------------------------------------
	//
	virtual void onSpawn(const PxTransform &aPose) override
	{
		auto wPoseComponent = addComponent<FollowPoseComponent>();
		wPoseComponent->follow(Game<IGamePlayers>()->mainGameObject());
		wPoseComponent->setPoseAdjustment(AdjustCameraPosition);

		auto wRenderViewComponent = addComponent<RenderViewComponent>();

		Game<IGameCameras>()->addCamera(ref());
	}

	//-------------------------------------------------------------------------
	//
	virtual void onUnspawn() override
	{
		Game<IGameCameras>()->removeCamera(ref());
	}

};



//-----------------------------------------------------------------------------
//
#include "Core/GameObjects/GameObjectFactory.h"
IGameObject::IdType ICamera::TypeId() {	return Camera::TypeId(); }
RegisterGameObjectType<Camera> gRegisterGameObject;

