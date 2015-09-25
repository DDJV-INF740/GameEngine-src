#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "SimulationComponent.h"
#include "Core/Game/Game.h"
#include "Core/GameManagers/IGameSimulation.h"

//=============================================================================
// CLASS SimulationComponentBase
//=============================================================================
template<class TDerived>
void SimulationComponentBase<TDerived>::onAttached( const GameObjectRef &iGameObject )
{
	_go = iGameObject;
	_pxActor = TDerived::createPxActor();
	_pxActor->userData = static_cast<IGameObject*>(_go.lock().get());
	Game<IGameSimulation>()->scene().addActor(*_pxActor);
}

template<class TDerived>
void SimulationComponentBase<TDerived>::onDetached( const GameObjectRef &iGameObject )
{
	if (_pxActor)
	{
		_pxActor->release();
		_pxActor = nullptr;
	}
}

template<class TDerived>
void SimulationComponentBase<TDerived>::onContact( const physx::PxContactPair &aContactPair )
{
	if (_collisionHandler)
	{
		_collisionHandler->onContact(aContactPair);
	}
}

template<class TDerived>
void SimulationComponentBase<TDerived>::onTrigger( bool triggerEnter, physx::PxShape *actorShape, physx::PxShape *contactShape )
{
	if (_collisionHandler)
	{
		_collisionHandler->onTrigger(triggerEnter, actorShape, contactShape);
	}
}

template<class TDerived>
void SimulationComponentBase<TDerived>::setHandler( ICollisionHandlerRef iHandler )
{
	_collisionHandler = iHandler;
}


