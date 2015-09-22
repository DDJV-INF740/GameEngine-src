#pragma once

//=============================================================================
// INTERFACE IGameTask
//=============================================================================
class IGameTask
{
public:
	virtual ~IGameTask() {}
public:
	virtual void init()  = 0;
	virtual void cleanup() = 0;
	virtual void update() = 0;
};