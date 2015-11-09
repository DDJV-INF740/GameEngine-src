#pragma once

namespace engine
{

//=============================================================================
// INTERFACE IModel
//=============================================================================
class IModel
{
public:
	virtual ~IModel() = default;
	virtual void render() const = 0;
};
} // namespace engine
