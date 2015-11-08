#include "Precompiled.h"

#include "Core/GameObjects/IGameObject.h"
#include "Core/Components/IColliderInterface.h"
#include "Core/GameManagers/IGameLoopManager.h"
#include "Core/GameManagers/ITimeManager.h"
#include "Core/Game/Game.h"

#include "SimulationManager.h"
#include "PxPhysicsAPI.h"

using namespace physx;

namespace engine {

//=============================================================================
// PRIVATE FUNCTIONS
//=============================================================================
class SimulationEventCallback: public PxSimulationEventCallback
{
public:
	virtual void onConstraintBreak(PxConstraintInfo* constraints, PxU32 count) override
	{}

	virtual void onWake(PxActor** actors, PxU32 count) override
	{}

	virtual void onSleep(PxActor** actors, PxU32 count) override
	{}

	virtual void onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pairs, PxU32 nbPairs) override
	{
		IGameObject *actor0 = nullptr;
		if (!(pairHeader.flags & PxContactPairHeaderFlag::eDELETED_ACTOR_0))
			actor0 = static_cast<IGameObject*>(pairHeader.actors[0]->userData);

		IGameObject *actor1 = nullptr;
		if (!(pairHeader.flags & PxContactPairHeaderFlag::eDELETED_ACTOR_1))
			actor1 = static_cast<IGameObject*>(pairHeader.actors[1]->userData);


		for (int i = 0; i < (int)nbPairs; ++i)
		{
			if (actor0)
				actor0->as<IColliderInterface>()->onContact(pairs[i]);

			if (actor1)
				actor1->as<IColliderInterface>()->onContact(pairs[i]);
		}
	}

	virtual void onTrigger(PxTriggerPair* pairs, PxU32 count) override
	{
		for (int i = 0; i < (int)count; ++i)
		{
			bool triggerEnter = false;
			if (pairs->status == PxPairFlag::eNOTIFY_TOUCH_FOUND)
				triggerEnter = true;
			else if (pairs->status == PxPairFlag::eNOTIFY_TOUCH_LOST)
				triggerEnter = false;
			else
				continue;

			IGameObject *trigger = nullptr;
			if (!(pairs->flags & PxTriggerPairFlag::eDELETED_SHAPE_TRIGGER))
				trigger = static_cast<IGameObject*>(pairs[i].triggerShape->getActor()->userData);

			IGameObject *other = nullptr;
			if (!(pairs->flags & PxTriggerPairFlag::eDELETED_SHAPE_OTHER))
				other = static_cast<IGameObject*>(pairs[i].otherShape->getActor()->userData);

			if (trigger)
				trigger->as<IColliderInterface>()->onTrigger(triggerEnter, pairs[i].triggerShape, other ? pairs[i].otherShape : nullptr);

			if (other)
				other->as<IColliderInterface>()->onTrigger(triggerEnter, pairs[i].otherShape, trigger ? pairs[i].triggerShape : nullptr);
		}
	}

};


static PxDefaultErrorCallback gDefaultErrorCallback;
static PxDefaultAllocator gDefaultAllocatorCallback;
static SimulationEventCallback gDefaultSimulationCallback;

class SimulationManager::SimulationManagerImp
{

public:
	//-------------------------------------------------------------------------
	//
	physx::PxPhysics& physics()
	{
		return *_physics;
	}

	//-------------------------------------------------------------------------
	//
	physx::PxScene& scene()
	{
		return *_scene;
	}
	
	//-------------------------------------------------------------------------
	//
	void fatalError(const char *str)
	{
		printf("%s", str);
		Game<IGameLoopManager>()->requestExit(true);
	}

	//-------------------------------------------------------------------------
	//
	void initialize()
	{
		_foundation = PxCreateFoundation(PX_PHYSICS_VERSION, gDefaultAllocatorCallback, gDefaultErrorCallback);
		if(!_foundation)
			fatalError("PxCreateFoundation failed!");

		bool recordMemoryAllocations = true;
		_profileZoneManager = &PxProfileZoneManager::createProfileZoneManager(_foundation);
		if(!_profileZoneManager)
			fatalError("PxProfileZoneManager::createProfileZoneManager failed!");

#ifdef PX_WINDOWS
		PxCudaContextManagerDesc cudaContextManagerDesc;
		_cudaContextManager = PxCreateCudaContextManager(*_foundation, cudaContextManagerDesc, _profileZoneManager);
		if( _cudaContextManager )
		{
			if( !_cudaContextManager->contextIsValid() )
			{
				_cudaContextManager->release();
				_cudaContextManager = NULL;
			}
		}
#endif

		_physics = PxCreatePhysics(PX_PHYSICS_VERSION, *_foundation,
			PxTolerancesScale(), recordMemoryAllocations, _profileZoneManager );
		if(!_physics)
			fatalError("PxCreatePhysics failed!");


		if (!PxInitExtensions(*_physics))
			fatalError("PxInitExtensions failed!");


		if (_physics->getPvdConnectionManager() != nullptr)
		{
			PxVisualDebuggerConnectionFlags connectionFlags(PxVisualDebuggerExt::getAllConnectionFlags());
			_visualDebuggerConnection = PxVisualDebuggerExt::createConnection(_physics->getPvdConnectionManager(), 
				"localhost", 5425, 100, connectionFlags);
			if (_visualDebuggerConnection == nullptr)
				printf("    NOT CONNECTED!\n");
			else
				printf("    CONNECTED!\n");
		}



		//-------------------------------------------------------------
		// create the scene
		PxSceneDesc sceneDesc(_physics->getTolerancesScale());
		customizeSceneDesc(&sceneDesc);

		if(!sceneDesc.cpuDispatcher)
		{
			_cpuDispatcher = PxDefaultCpuDispatcherCreate(1);
			if(!_cpuDispatcher)
				fatalError("PxDefaultCpuDispatcherCreate failed!");
			sceneDesc.cpuDispatcher    = _cpuDispatcher;
		}
		if(!sceneDesc.filterShader)
			sceneDesc.filterShader    = PxDefaultSimulationFilterShader;

#ifdef PX_WINDOWS
		if(!sceneDesc.gpuDispatcher && _cudaContextManager)
		{
			sceneDesc.gpuDispatcher = _cudaContextManager->getGpuDispatcher();
		}
#endif

		_scene = _physics->createScene(sceneDesc);
		if (!_scene)
			fatalError("createScene failed!");

		_scene->setSimulationEventCallback(&gDefaultSimulationCallback);
	}

	//-------------------------------------------------------------------------
	//
	void customizeSceneDesc(PxSceneDesc *aSceneDesc)
	{
		aSceneDesc->gravity = PxVec3(0.0f, -9.81f, 0.0f);
		//aSceneDesc->gravity = PxVec3(0.0f, 0.0f, 0.0f);
		aSceneDesc->filterShader = &SimulationManagerImp::SimulationFilterShader;
	}

	//-------------------------------------------------------------------------
	//
	static PxFilterFlags SimulationFilterShader(	
		PxFilterObjectAttributes attributes0, PxFilterData filterData0, 
		PxFilterObjectAttributes attributes1, PxFilterData filterData1,
		PxPairFlags& pairFlags, const void* constantBlock, PxU32 constantBlockSize)
	{
		// let triggers through
		if(PxFilterObjectIsTrigger(attributes0) || PxFilterObjectIsTrigger(attributes1))
		{
			pairFlags = PxPairFlag::eTRIGGER_DEFAULT;
			return PxFilterFlag::eDEFAULT;
		}
		// generate contacts for all that were not filtered above
		pairFlags = PxPairFlag::eCONTACT_DEFAULT;

		// trigger the contact callback for pairs (A,B) where 
		// the filtermask of A contains the ID of B and vice versa.
		if((filterData0.word0 & filterData1.word1) || (filterData1.word0 & filterData0.word1))
		{
			pairFlags |= PxPairFlag::eNOTIFY_TOUCH_FOUND;
			return PxFilterFlag::eDEFAULT;
		}

		return PxFilterFlag::eSUPPRESS;
	}

	//-------------------------------------------------------------------------
	//
	void cleanup()
	{
		if (_scene)
		{
			_scene->release();
			_scene = nullptr;
		}

		if (_cpuDispatcher)
		{
			_cpuDispatcher->release();
			_cpuDispatcher = nullptr;
		}

		if (_visualDebuggerConnection)
		{
			_visualDebuggerConnection->release();
			_visualDebuggerConnection = nullptr;
		}

		if (_physics)
		{
			PxCloseExtensions();

			_physics->release();
			_physics = nullptr;
		}

		if (_cudaContextManager)
		{
			_cudaContextManager->release();
			_cudaContextManager = nullptr;
		}

		if (_profileZoneManager)
		{
			_profileZoneManager->release();
			_profileZoneManager = nullptr;
		}

		if (_foundation)
		{
			_foundation->release();
			_foundation = nullptr;
		}
	}

	void update()
	{
		PxReal remainingToSimulate = PxReal(Game<ITimeManager>()->currentTime() - Game<ITimeManager>()->lastFrameTime());

		while (remainingToSimulate > 0)
		{
			if (remainingToSimulate > 0.1f)
			{
				_scene->simulate(0.1f);
				remainingToSimulate -= 0.1f;
			}
			else
			{
				_scene->simulate(remainingToSimulate);
				remainingToSimulate = 0;
			}
			_scene->fetchResults(true);
		}
	}
private:
	PxFoundation *_foundation;
	PxProfileZoneManager *_profileZoneManager;
	PxPhysics *_physics;
	PxScene* _scene;
	PxDefaultCpuDispatcher *_cpuDispatcher;
	PxCudaContextManager *_cudaContextManager;
	debugger::comm::PvdConnection *_visualDebuggerConnection;
};

SimulationManager::SimulationManager()
	: _imp(new SimulationManagerImp)
{}

SimulationManager::~SimulationManager()
{
	delete _imp;
}

physx::PxPhysics& SimulationManager::physics()
{
	return _imp->physics();
}

physx::PxScene& SimulationManager::scene()
{
	return _imp->scene();
}



void SimulationManager::update()
{
	_imp->update();
}

void SimulationManager::onAttached( const GameEngineRef &iGameEngine )
{
	_imp->initialize();
}

void SimulationManager::onDetached( const GameEngineRef &iGameEngine )
{
	_imp->cleanup();
}
} // namespace engine

  //=============================================================================
  // COMPONENT REGISTRATION
  //=============================================================================
#include "Engine/Managers/GameManagerFactory.h"


namespace engine {

IComponent::IdType SimulationManager::TypeId() { return "SimulationManager"; }
RegisterGameManagerType<SimulationManager> gManagerRegistration;
} // namespace engine


