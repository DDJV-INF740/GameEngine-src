#pragma once

//=============================================================================
// INTERFACE IModel
//=============================================================================
class IModel
{
public:
	virtual ~IModel() {}
	virtual void render() const = 0;
};